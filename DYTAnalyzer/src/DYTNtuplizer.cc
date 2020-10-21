//
// Package:    DYTNtuplizer
// Class:      DYTNtuplizer
//
/**\class DYTNtuplizer DYTNtuplizer.cc Analysis/DYTAnalyzer/src/DYTNtuplizer.cc

 Description: Simple Flat Ntuplizer for DYT and HighPt Muon studies

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Claudio Caputo, UCLouvain
//         Created:  Wed May 8 10:58:01 CEST 2019
// $Id$
//
//


#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/DYTInfo.h"
#include "DataFormats/TrackReco/interface/TrackToTrackMap.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TTree.h"
#include "TObject.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > LorentzVector;

namespace utils{

  template <class T, class U>
  void initMap(std::map<T,U> map){
    for (auto & x : map){
      *(x.second) = 0;// string's value
    }
  }

  template <class T, class U, class V>
  void fillMap(std::map<T,U> map, int idx, V value){
    for (auto & x : map){
      if(x.first == idx){
        *(x.second) = value;// string's value
      }
    }
  }


  class MuonTrack: public TObject {
    public:
      LorentzVector momentum;
      int charge;
      double ptError, qoverp, qoverpError;

      MuonTrack(){
         charge = 0; ptError = 0; qoverp = 0;
      }
      void setMuonTrackValues(reco::TrackRef &track){
       charge = track->charge();
       ptError = track->ptError();
       qoverp  = track->qoverp();
       qoverpError = track->qoverpError();
       momentum = LorentzVector(track->pt(), track->eta(), track->phi(), track->p());
      }
  //   ClassDef(MuonTrack,1)
   };
//ClassImp(MuonTrack)
};

class DYTNtuplizer : public edm::EDAnalyzer {
public:
  explicit DYTNtuplizer(const edm::ParameterSet&);
  ~DYTNtuplizer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

 private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

   inline bool isTrackerHighPtMuonNoVtx(const reco::Muon& muon){
      bool muID =   muon.isTrackerMuon() && muon.track().isNonnull() && (muon.numberOfMatchedStations() > 1);
      if(!muID) return false;

      bool hits = muon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 &&
                  muon.innerTrack()->hitPattern().numberOfValidPixelHits() > 0;

      bool momQuality = muon.tunePMuonBestTrack()->ptError()/muon.tunePMuonBestTrack()->pt() < 0.3;

      // bool ip = fabs(muon.innerTrack()->dxy(vtx.position())) < 0.2 && fabs(muon.innerTrack()->dz(vtx.position())) < 0.5;
      bool ip = true;

      return muID && hits && momQuality && ip;
   }


  inline bool isHighPtMuonNoVtx(const reco::Muon& muon/*, const reco::Vertex& vtx*/){
   if(!muon.isGlobalMuon()) return false;

   bool muValHits = ( muon.globalTrack()->hitPattern().numberOfValidMuonHits()>0 ||
                      muon.tunePMuonBestTrack()->hitPattern().numberOfValidMuonHits()>0 );

   bool muMatchedSt = muon.numberOfMatchedStations()>1;
   if(!muMatchedSt) {
     if( muon.isTrackerMuon() && muon.numberOfMatchedStations()==1 ) {
       if( muon.expectedNnumberOfMatchedStations()<2 ||
           !(muon.stationMask()==1 || muon.stationMask()==16) ||
           muon.numberOfMatchedRPCLayers()>2
         )
         muMatchedSt = true;
     }
   }

   bool muID = muValHits && muMatchedSt;

   bool hits = muon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 &&
     muon.innerTrack()->hitPattern().numberOfValidPixelHits() > 0;

   bool momQuality = muon.tunePMuonBestTrack()->ptError()/muon.tunePMuonBestTrack()->pt() < 0.3;

   // bool ip = fabs(muon.innerTrack()->dxy(vtx.position())) < 0.2 && fabs(muon.innerTrack()->dz(vtx.position())) < 0.5;
   bool ip = true;

   return muID && hits && momQuality && ip;

  }

  typedef edm::ValueMap<reco::DYTInfo> DYTestimators;
  double psim;
  double ptsim;
  double pgen;
  double ptgen;
  bool useSelections;


  edm::EDGetTokenT<reco::MuonCollection> muon_label_;
  edm::EDGetTokenT<std::vector<reco::Vertex>> vertex_label_;
  edm::EDGetTokenT<reco::GenParticleCollection> gpar_label_;
  edm::EDGetTokenT<DYTestimators> dytInfoToken;


  //TTree Variable
  TTree* ntuple;
  unsigned int  treeEventId;
  unsigned int  treeLumiId;
  unsigned int  treeRunId;
  int treeTunePMuonBestTrackType, treeMuonCharge, treeQ_gen;
  int treeNumberOfShowers;
  unsigned int treeMuonSubDetID_1,treeMuonSubDetID_2,treeMuonSubDetID_3,treeMuonSubDetID_4;
  bool treeMuonSubDetShowering_1,treeMuonSubDetShowering_2,treeMuonSubDetShowering_3,treeMuonSubDetShowering_4;
  double treeDYTEst_1,treeDYTEst_2,treeDYTEst_3,treeDYTEst_4;

  float treeP_gen, treePt_gen;
  unsigned int treeMuonSelectors;
  bool treeTrackerHighPtIDNoVtx;
  bool treeHighPtMuonIDNoVtx;
  LorentzVector treeMuon, treeMuonTuneP, treeMuonDyT, treeMuonPicky;
  float  treeMuonDyT_ptError, treeMuonPicky_ptError;
  float  treeMuonDyT_qoverp, treeMuonPicky_qoverp;
  float  treeMuonDyT_qoverpError, treeMuonPicky_qoverpError;
  //utils::MuonTrack muonDYT;
};

DYTNtuplizer::DYTNtuplizer(const edm::ParameterSet& iConfig)
{
  psim = iConfig.getParameter<double>("psim");
  useSelections = iConfig.getParameter<bool>("useSelections");
  ptsim = 5*psim;

  muon_label_   = consumes<reco::MuonCollection>(edm::InputTag("muons"));
  vertex_label_ = consumes< std::vector<reco::Vertex> >(edm::InputTag("offlinePrimaryVertices"));
  gpar_label_   = consumes<reco::GenParticleCollection>(edm::InputTag("genParticles"));
  dytInfoToken  = consumes<DYTestimators>(edm::InputTag("tevMuons", "dytInfo"));


}

DYTNtuplizer::~DYTNtuplizer()
{}

void DYTNtuplizer::beginJob()
{

  edm::Service<TFileService> fs;

  ntuple  = fs->make<TTree>("Muons","Muons");

  ntuple->Branch("eventId", &treeEventId , "eventId/i");
  ntuple->Branch("lumiId" , &treeLumiId  , "lumiId/i" );
  ntuple->Branch("runId"  , &treeRunId   , "runId/i"  );
  ntuple->Branch("numberOfShowers"  , &treeNumberOfShowers   , "numberOfShowers/i"  );

  ntuple->Branch("tunePMuonBestTrackType"  , &treeTunePMuonBestTrackType   , "tunePMuonBestTrackType/i" );
  ntuple->Branch("muonSelectors"  , &treeMuonSelectors   , "muonSelectors/i" );
  ntuple->Branch("trackerHighPtIDNoVtx"   , &treeTrackerHighPtIDNoVtx  , "trackerHighPtIDNoVtx/b"  );
  ntuple->Branch("highPtMuonIDNoVtx"   , &treeHighPtMuonIDNoVtx  , "highPtMuonIDNoVtx/f"  );
  ntuple->Branch("p_gen"   , &treeP_gen  , "p_gen/f"  );
  ntuple->Branch("pt_gen"  , &treePt_gen , "pt_gen/f"  );
  ntuple->Branch("q_gen"  , &treeQ_gen , "q_gen/i"  );
  ntuple->Branch("muonCharge"  , &treeMuonCharge , "muonCharge/i"  );
  ntuple->Branch("muonCandidate",     &treeMuon );
  ntuple->Branch("muonCandidateTuneP",     &treeMuonTuneP );
  ntuple->Branch("muonCandidateDyT",     &treeMuonDyT );
  ntuple->Branch("muonCandidatePicky",     &treeMuonPicky );
  //ntuple->Branch("muonTrackDYT", &muonDYT);
  ntuple->Branch("muonSubDetID_1", &treeMuonSubDetID_1, "muonSubDetID_1/i" );
  ntuple->Branch("DYTEst_1", &treeDYTEst_1 , "DYTEst_1/D");
  ntuple->Branch("muonSubDetShowering_1", &treeMuonSubDetShowering_1, "muonSubDetShowering_1/b" );

  ntuple->Branch("muonSubDetID_2", &treeMuonSubDetID_2, "muonSubDetID_2/i" );
  ntuple->Branch("DYTEst_2", &treeDYTEst_2 , "DYTEst_2/D");
  ntuple->Branch("muonSubDetShowering_2", &treeMuonSubDetShowering_2, "muonSubDetShowering_2/b" );

  ntuple->Branch("muonSubDetID_3", &treeMuonSubDetID_3, "muonSubDetID_3/i" );
  ntuple->Branch("DYTEst_3", &treeDYTEst_3 , "DYTEst_3/D");
  ntuple->Branch("muonSubDetShowering_3", &treeMuonSubDetShowering_3, "muonSubDetShowering_3/b" );

  ntuple->Branch("muonSubDetID_4", &treeMuonSubDetID_4, "muonSubDetID_4/i" );
  ntuple->Branch("DYTEst_4", &treeDYTEst_4 , "DYTEst_4/D");
  ntuple->Branch("muonSubDetShowering_4", &treeMuonSubDetShowering_4, "muonSubDetShowering_4/i" );

  ntuple->Branch("muonCandidateDyT_ptError"   , &treeMuonDyT_ptError  , "muonCandidateDyT_ptError/f"  );
  ntuple->Branch("muonCandidateDyt_qoverp"   , &treeMuonDyT_qoverp  , "muonCandidateDyT_qoverp/f"  );
  ntuple->Branch("muonCandidateDyT_qoverpError"   , &treeMuonDyT_qoverpError  , "muonCandidateDyT_qoverpError/f"  );
  ntuple->Branch("muonCandidatePicky_ptError"   , &treeMuonPicky_ptError  , "muonCandidatePicky_ptError/f"  );
  ntuple->Branch("muonCandidateDyT_qoverp"   , &treeMuonPicky_qoverp  , "muonCandidatePicky_qoverp/f"  );
  ntuple->Branch("muonCandidateDyT_qoverpError"   , &treeMuonPicky_qoverpError  , "muonCandidatePicky_qoverpError/f"  );

}


void DYTNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace std;
    using namespace edm;
    using namespace reco;

    LorentzVector null_p4(0., 0., 0., 0.);

    std::map< int, bool* > detectorShoweringMap{ {0,&treeMuonSubDetShowering_1},
                                                 {1,&treeMuonSubDetShowering_2},
                                                 {2,&treeMuonSubDetShowering_3},
                                                 {3,&treeMuonSubDetShowering_4}};

    std::map< int, unsigned int* > detectorIDMap{ {0,&treeMuonSubDetID_1},
                                                  {1,&treeMuonSubDetID_2},
                                                  {2,&treeMuonSubDetID_3},
                                                  {3,&treeMuonSubDetID_4}};

    std::map< int, double* > DYTEstimatorMap{ {0,&treeDYTEst_1},
                                              {1,&treeDYTEst_2},
                                              {2,&treeDYTEst_3},
                                              {3,&treeDYTEst_4}};


    edm::Handle<reco::MuonCollection> muonsHandle;
    iEvent.getByToken( muon_label_, muonsHandle );
    auto muons = muonsHandle.product();

    edm::Handle< std::vector<reco::Vertex> > verteciesHandle;
    iEvent.getByToken( vertex_label_, verteciesHandle );
    auto vtx = verteciesHandle.product()->at(0);

    Handle<reco::GenParticleCollection> genP;
    iEvent.getByToken(gpar_label_,genP);

    Handle<DYTestimators> dytInfoH;
    iEvent.getByToken(dytInfoToken, dytInfoH);
    const DYTestimators& dytInfoC = *dytInfoH;

    treeEventId   = iEvent.eventAuxiliary().event();
    treeLumiId    = iEvent.eventAuxiliary().luminosityBlock();
    treeRunId     = iEvent.eventAuxiliary().run();


    for (auto& muon: *muons){
      //try{
        // Initialaising muon variables
        treeP_gen = 0;
        treePt_gen = 0;
        treeQ_gen = 0;
        treeNumberOfShowers = 0;
        utils::initMap(detectorShoweringMap);
        utils::initMap(detectorIDMap);
        utils::initMap(DYTEstimatorMap);

        for(auto& particle: *genP){
          if ( reco::deltaR2(particle, muon) < 0.01) {
            treeP_gen   = particle.p();
            treePt_gen  = particle.pt();
            treeQ_gen   = particle.charge();
          }
        }

        //std::cout<<"Muon num showers:  "<<muon.numberOfShowers()<<"\n";

        treeNumberOfShowers = muon.numberOfShowers();

        const TrackRef& tkRef = muon.globalTrack();
        if (dytInfoC.contains(tkRef.id())) {
          DYTInfo dytInfo = dytInfoC[muon.globalTrack()];
          vector<double> estimators = dytInfo.DYTEstimators();
          vector<DetId> ids = dytInfo.IdChambers();

          for (int j = 0; j < 4; j++) {
            if (ids[j].null())
              continue;
            DetId chamberId = ids[j];
            double estValue = estimators[j];
            //std::cout<< estValue <<"-"<<chamberId.rawId()
            //         << " -  station "<< j << " - detectorIDMap[j] = " << detectorIDMap[j]
            //         << " - DYTEstimatorMap[j] = " << DYTEstimatorMap[j]
            //         << " - treeDYTEst_1 = "<< treeDYTEst_1 << "\n";

            utils::fillMap(detectorIDMap, j, chamberId.rawId());
            utils::fillMap(DYTEstimatorMap, j, estValue);
            // detectorIDMap[j] = chamberId.rawId();
            // DYTEstimatorMap[j] = estValue;

            //std::cout<< " After filling "<< j << " - detectorIDMap[j] = " << detectorIDMap[j]
            //         << " - DYTEstimatorMap[j] = " << DYTEstimatorMap[j]
            //         << " - treeDYTEst_1 = "<< treeDYTEst_1 << "\n";

            bool hasShower = false;
            if (chamberId.subdetId() == MuonSubdetId::DT) {
              int station = DTChamberId(chamberId).station();
              hasShower = muon.hasShowerInStation(station,chamberId);
              utils::fillMap(detectorShoweringMap, j, hasShower);
            }
            if (chamberId.subdetId() == MuonSubdetId::CSC) {
              int station = CSCDetId(chamberId).station();
              hasShower = muon.hasShowerInStation(station,chamberId);
              utils::fillMap(detectorShoweringMap, j, hasShower);
            }

            //std::cout<< estValue <<"-"<<chamberId.rawId()<<"  ("<< (hasShower? "True" : "False")<<")---"<< "\t";
          }
        } else {
          continue;
        }
        std::cout<<"\n";

        treeTunePMuonBestTrackType = -1;
        treeMuon      = null_p4;
        treeMuonTuneP = null_p4;
        treeMuonDyT   = null_p4;
        treeMuonPicky = null_p4;
        treeMuonCharge = 0;
        treeMuonSelectors = -1;

        reco::TrackRef dyt        = muon.dytTrack();
        reco::TrackRef picky      = muon.pickyTrack();
        reco::TrackRef tunePTrack = muon.tunePMuonBestTrack();

        treeMuonCharge = muon.charge();
	treeTrackerHighPtIDNoVtx = isTrackerHighPtMuonNoVtx(muon);
	treeHighPtMuonIDNoVtx    = isHighPtMuonNoVtx(muon);
        treeTunePMuonBestTrackType = static_cast<int>(muon.tunePMuonBestTrackType());
        treeMuonSelectors = muon.selectors();
        treeMuon      = LorentzVector(muon.pt(), muon.eta(), muon.phi(), muon.p());
        if ( dyt.isNonnull() ) {
           treeMuonDyT   = LorentzVector(dyt->pt(), dyt->eta(), dyt->phi(), dyt->p());
           treeMuonDyT_ptError = dyt->ptError();
           treeMuonDyT_qoverp  = dyt->qoverp();
           treeMuonDyT_qoverpError = dyt->qoverpError();
        }//muonDYT.setMuonTrackValues(dyt);
        if ( picky.isNonnull() ) {
           treeMuonPicky   = LorentzVector(picky->pt(), picky->eta(), picky->phi(), picky->p());

           treeMuonPicky_ptError = picky->ptError();
           treeMuonPicky_qoverp  = picky->qoverp();
           treeMuonPicky_qoverpError = picky->qoverpError();
        }
        treeMuonTuneP = LorentzVector(tunePTrack->pt(), tunePTrack->eta(), tunePTrack->phi(), tunePTrack->p());
        ntuple->Fill();

      //} catch (...) {continue;}
    }
}


void DYTNtuplizer::endJob()
{

}


void DYTNtuplizer::beginRun(edm::Run const&, edm::EventSetup const&)
{}


void DYTNtuplizer::endRun(edm::Run const&, edm::EventSetup const&)
{}


void DYTNtuplizer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{}


void DYTNtuplizer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{}

void DYTNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
DEFINE_FWK_MODULE(DYTNtuplizer);
