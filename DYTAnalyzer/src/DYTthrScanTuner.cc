// -*- C++ -*-
//
// Package:    Analysis/DYTthrScanTuner
// Class:      DYTthrScanTuner
// 
/**\class DYTthrScanTuner DYTthrScanTuner.cc Analysis/DYTthrScanTuner/plugins/DYTthrScanTuner.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  root
//         Created:  Thu, 04 May 2017 09:23:10 GMT
//
//



#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/DYTInfo.h"
#include "DataFormats/TrackReco/interface/TrackToTrackMap.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHitFwd.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "SimMuon/MCTruth/interface/MuonToSimAssociatorBase.h"
#include "SimMuon/MCTruth/interface/MuonAssociatorByHits.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimTracker/TrackAssociation/plugins/ParametersDefinerForTPESProducer.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/Associations/interface/TrackToTrackingParticleAssociator.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/PatternTools/interface/TSCBLBuilderNoMaterial.h"
#include "SimTracker/TrackAssociation/plugins/ParametersDefinerForTPESProducer.h"
#include "SimTracker/TrackAssociation/plugins/CosmicParametersDefinerForTPESProducer.h"
#include "SimDataFormats/Associations/interface/TrackToTrackingParticleAssociator.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "RecoTracker/NuclearSeedGenerator/interface/TrackCandidateToTrajectoryMap.h"
#include "TrackingTools/PatternTools/interface/TrajectoryMeasurement.h"
#include "RecoTracker/NuclearSeedGenerator/interface/TrajectoryToSeedMap.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "RecoTracker/NuclearSeedGenerator/interface/NuclearTrackCorrector.h"
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"
#include "DataFormats/CSCRecHit/interface/CSCRecHit2D.h"
#include "DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCSegment.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"
#include "Geometry/DTGeometry/interface/DTChamber.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2D.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/DTRecHit/interface/DTChamberRecSegment2D.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4D.h"
#include "DataFormats/DTRecHit/interface/DTRecHit1D.h"
#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "Geometry/CSCGeometry/interface/CSCChamber.h"
#include "Geometry/CSCGeometry/interface/CSCLayer.h"
#include "Geometry/CSCGeometry/interface/CSCLayerGeometry.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/DTGeometry/interface/DTChamber.h"
#include "Geometry/DTGeometry/interface/DTLayer.h"
#include "Geometry/DTGeometry/interface/DTLayerType.h"
#include "Geometry/DTGeometry/interface/DTSuperLayer.h"
#include "Geometry/DTGeometry/interface/DTTopology.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TLorentzVector.h"

class DYTthrScanTuner : public edm::one::EDAnalyzer<edm::one::SharedResources>  {

   public:
      DYTthrScanTuner(const edm::ParameterSet& pset, edm::ConsumesCollector iC) : DYTthrScanTuner(pset)
      {
		track_collection_Token    = iC.consumes<edm::View<reco::Track> >(label_track_coll); 
		rh_csc_Token              = iC.consumes<CSCRecHit2DCollection>(label_recHit_csc);
		sh_csc_Token              = iC.consumes<edm::PSimHitContainer>(label_simHit_csc);
		se_csc_Token              = iC.consumes<CSCSegmentCollection>(label_seg_csc);	
		rh_dt_Token               = iC.consumes<DTRecHitCollection>(label_recHit_dt);	
		sh_dt_Token               = iC.consumes<edm::PSimHitContainer>(label_simHit_dt);
		se_dt_Token               = iC.consumes<DTRecSegment4DCollection>(label_seg_dt); 
		gen_collection_Token      = iC.consumes<edm::View<reco::GenParticle> >(label_gen_coll);
      };

      explicit DYTthrScanTuner(const edm::ParameterSet&);
      LocalPoint meanPoint(LocalPoint InfPoint, LocalPoint SupPoint);
      ~DYTthrScanTuner(); 
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      typedef edm::Ref<TrajectoryCollection> TrajectoryRef;

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
 
      typedef edm::ValueMap<reco::DYTInfo> DYTestimators;
      double psim; 
      double mass = 0.1056583745; // Muon mass in GeV;
      double muon_p, muon_pt, muon_eta;

      //Edm Handle stuff
      edm::InputTag     label_track_coll;
      edm::InputTag     label_recHit_csc;
      edm::InputTag     label_simHit_csc;
      edm::InputTag        label_seg_csc;
      edm::InputTag      label_recHit_dt;
      edm::InputTag      label_simHit_dt;
      edm::InputTag         label_seg_dt;
      edm::InputTag       label_gen_coll;

      edm::EDGetTokenT<edm::View<reco::Track>>       track_collection_Token;
      edm::EDGetTokenT<CSCRecHit2DCollection>                  rh_csc_Token;
      edm::EDGetTokenT<edm::PSimHitContainer>                  sh_csc_Token;
      edm::EDGetTokenT<CSCSegmentCollection>                   se_csc_Token;
      edm::EDGetTokenT<DTRecHitCollection>                      rh_dt_Token;
      edm::EDGetTokenT<edm::PSimHitContainer>                   sh_dt_Token;
      edm::EDGetTokenT<DTRecSegment4DCollection>                se_dt_Token;
      edm::EDGetTokenT<edm::View<reco::GenParticle>>   gen_collection_Token;

      //Definition the Histos
      //General Kinematical Property
      TH1F         *h1_Track_P,        *h1_Track_P_08,        *h1_Track_P_12,        *h1_Track_P_20,        *h1_Track_P_22,     *h1_Track_P_24;
      TH1F      *h1_Track_1OvP,     *h1_Track_1OvP_08,     *h1_Track_1OvP_12,     *h1_Track_1OvP_20,     *h1_Track_1OvP_22,  *h1_Track_1OvP_24;
      //TH2F  *h2_Track_P_Vs_Eta, *h2_Track_P_Vs_Eta_08, *h2_Track_P_Vs_Eta_12, *h2_Track_P_Vs_Eta_20, *h2_Track_P_Vs_Eta_24;
      TH1F *h1_Track_PtCut_Eta, *h1_Track_PtCut_Eta_08, *h1_Track_PtCut_Eta_12, *h1_Track_PtCut_Eta_20, *h1_Track_PtCut_Eta_24;
      TH1F       *h1_Track_Eta;
      //Energy Loss by Station
      TH1F  *h1_DeltaESim_DT_St1,  *h1_DeltaESim_DT_St2,  *h1_DeltaESim_DT_St3,  *h1_DeltaESim_DT_St4;
      TH1F *h1_DeltaESim_CSC_St1, *h1_DeltaESim_CSC_St2, *h1_DeltaESim_CSC_St3, *h1_DeltaESim_CSC_St4;
      TH1F  *h1_DeltaERec_DT_St1,  *h1_DeltaERec_DT_St2,  *h1_DeltaERec_DT_St3,  *h1_DeltaERec_DT_St4;
      TH1F *h1_DeltaERec_CSC_St1, *h1_DeltaERec_CSC_St2, *h1_DeltaERec_CSC_St3, *h1_DeltaERec_CSC_St4;
      //Comparison Energy Loss Sim Vs Reco by Station
      TH2F *h2_DeltaSim_DeltaRec_CSC_St1, *h2_DeltaSim_DeltaRec_CSC_St2, *h2_DeltaSim_DeltaRec_CSC_St3, *h2_DeltaSim_DeltaRec_CSC_St4;
      TH2F  *h2_DeltaSim_DeltaRec_DT_St1,  *h2_DeltaSim_DeltaRec_DT_St2,  *h2_DeltaSim_DeltaRec_DT_St3,  *h2_DeltaSim_DeltaRec_DT_St4;
      //Comparison 1/Energy Loss Sim Vs 1/Energy Loss Reco
      TH2F *h2_1DeltaSim_1DeltaRec_CSC_St1, *h2_1DeltaSim_1DeltaRec_CSC_St2, *h2_1DeltaSim_1DeltaRec_CSC_St3, *h2_1DeltaSim_1DeltaRec_CSC_St4;
      TH2F  *h2_1DeltaSim_1DeltaRec_DT_St1,  *h2_1DeltaSim_1DeltaRec_DT_St2,  *h2_1DeltaSim_1DeltaRec_DT_St3,  *h2_1DeltaSim_1DeltaRec_DT_St4;

      //Energy Loss by Eta Region
      TH1F  *h1_DeltaESim_08, *h1_DeltaESim_12, *h1_DeltaESim_20, *h1_DeltaESim_24;
      TH1F  *h1_DeltaERec_08, *h1_DeltaERec_12, *h1_DeltaERec_20, *h1_DeltaERec_24;
      //Comparison Enegy Loss Sim Vs Reco by Eta Region
      TH2F *h2_DeltaSim_DeltaRec_08, *h2_DeltaSim_DeltaRec_12, *h2_DeltaSim_DeltaRec_20, *h2_DeltaSim_DeltaRec_24;
      //Comparison 1/Enegy Loss Sim Vs 1/Reco by Eta Region
      TH2F *h2_1DeltaSim_1DeltaRec_08, *h2_1DeltaSim_1DeltaRec_12, *h2_1DeltaSim_1DeltaRec_20, *h2_1DeltaSim_1DeltaRec_24;

      //Bias in the local position of the segment
      TH1F *h1_DeltaX_CSC_St1, *h1_DeltaX_CSC_St2, *h1_DeltaX_CSC_St3, *h1_DeltaX_CSC_St4;
      TH1F *h1_DeltaY_CSC_St1, *h1_DeltaY_CSC_St2, *h1_DeltaY_CSC_St3, *h1_DeltaY_CSC_St4;
      TH1F  *h1_DeltaX_DT_St1,  *h1_DeltaX_DT_St2,  *h1_DeltaX_DT_St3,  *h1_DeltaX_DT_St4;
      TH1F  *h1_DeltaY_DT_St1,  *h1_DeltaY_DT_St2,  *h1_DeltaY_DT_St3,  *h1_DeltaY_DT_St4;

      TH1F      *h1_DeltaX_08,      *h1_DeltaX_12,      *h1_DeltaX_20,      *h1_DeltaX_24;
      TH1F      *h1_DeltaY_08,      *h1_DeltaY_12,      *h1_DeltaY_20,      *h1_DeltaY_24;

      TH2F *h2_RecX_SimX_CSC_St1, *h2_RecX_SimX_CSC_St2, *h2_RecX_SimX_CSC_St3, *h2_RecX_SimX_CSC_St4;
      TH2F *h2_RecY_SimY_CSC_St1, *h2_RecY_SimY_CSC_St2, *h2_RecY_SimY_CSC_St3, *h2_RecY_SimY_CSC_St4;
      TH2F  *h2_RecX_SimX_DT_St1,  *h2_RecX_SimX_DT_St2,  *h2_RecX_SimX_DT_St3,  *h2_RecX_SimX_DT_St4;
      TH2F  *h2_RecY_SimY_DT_St1,  *h2_RecY_SimY_DT_St2,  *h2_RecY_SimY_DT_St3,  *h2_RecY_SimY_DT_St4;

      TH2F      *h2_RecX_SimX_08,      *h2_RecX_SimX_12,      *h2_RecX_SimX_20,      *h2_RecX_SimX_24;
      TH2F      *h2_RecY_SimY_08,      *h2_RecY_SimY_12,      *h2_RecY_SimY_20,      *h2_RecY_SimY_24;

      //Bias in the local direction of the segment
      TH1F *h1_DeltadX_CSC_St1, *h1_DeltadX_CSC_St2, *h1_DeltadX_CSC_St3, *h1_DeltadX_CSC_St4;
      TH1F *h1_DeltadY_CSC_St1, *h1_DeltadY_CSC_St2, *h1_DeltadY_CSC_St3, *h1_DeltadY_CSC_St4;
      TH1F  *h1_DeltadX_DT_St1,  *h1_DeltadX_DT_St2,  *h1_DeltadX_DT_St3,  *h1_DeltadX_DT_St4;
      TH1F  *h1_DeltadY_DT_St1,  *h1_DeltadY_DT_St2,  *h1_DeltadY_DT_St3,  *h1_DeltadY_DT_St4;

      TH1F      *h1_DeltadX_08,      *h1_DeltadX_12,      *h1_DeltadX_20,      *h1_DeltadX_24;
      TH1F      *h1_DeltadY_08,      *h1_DeltadY_12,      *h1_DeltadY_20,      *h1_DeltadY_24;

      TH2F *h2_RecdX_SimdX_CSC_St1, *h2_RecdX_SimdX_CSC_St2, *h2_RecdX_SimdX_CSC_St3, *h2_RecdX_SimdX_CSC_St4;
      TH2F *h2_RecdY_SimdY_CSC_St1, *h2_RecdY_SimdY_CSC_St2, *h2_RecdY_SimdY_CSC_St3, *h2_RecdY_SimdY_CSC_St4;
      TH2F  *h2_RecdX_SimdX_DT_St1,  *h2_RecdX_SimdX_DT_St2,  *h2_RecdX_SimdX_DT_St3,  *h2_RecdX_SimdX_DT_St4;
      TH2F  *h2_RecdY_SimdY_DT_St1,  *h2_RecdY_SimdY_DT_St2,  *h2_RecdY_SimdY_DT_St3,  *h2_RecdY_SimdY_DT_St4;

      TH2F      *h2_RecdX_SimdX_08,      *h2_RecdX_SimdX_12,      *h2_RecdX_SimdX_20,      *h2_RecdX_SimdX_24;
      TH2F      *h2_RecdY_SimdY_08,      *h2_RecdY_SimdY_12,      *h2_RecdY_SimdY_20,      *h2_RecdY_SimdY_24;

      //Local Position of the Semgent both Reco and Sim
      TH2F  *h2_RecX_RecY_DT_St1, *h2_RecX_RecY_DT_St2, *h2_RecX_RecY_DT_St3, *h2_RecX_RecY_DT_St4;
      TH2F  *h2_SimX_SimY_DT_St1, *h2_SimX_SimY_DT_St2, *h2_SimX_SimY_DT_St3, *h2_SimX_SimY_DT_St4;

      TH2F *h2_RecX_RecY_CSC_St1, *h2_RecX_RecY_CSC_St2, *h2_RecX_RecY_CSC_St3, *h2_RecX_RecY_CSC_St4;
      TH2F *h2_SimX_SimY_CSC_St1, *h2_SimX_SimY_CSC_St2, *h2_SimX_SimY_CSC_St3, *h2_SimX_SimY_CSC_St4;

      TH2F *h2_RecX_RecY_08, *h2_RecX_RecY_12, *h2_RecX_RecY_20, *h2_RecX_RecY_24;
      TH2F *h2_SimX_SimY_08, *h2_SimX_SimY_12, *h2_SimX_SimY_20, *h2_SimX_SimY_24;

      //Local Direction of the Segment both Reco and Sim
      TH2F  *h2_RecdX_RecdY_DT_St1, *h2_RecdX_RecdY_DT_St2, *h2_RecdX_RecdY_DT_St3, *h2_RecdX_RecdY_DT_St4;
      TH2F  *h2_SimdX_SimdY_DT_St1, *h2_SimdX_SimdY_DT_St2, *h2_SimdX_SimdY_DT_St3, *h2_SimdX_SimdY_DT_St4;

      TH2F *h2_RecdX_RecdY_CSC_St1, *h2_RecdX_RecdY_CSC_St2, *h2_RecdX_RecdY_CSC_St3, *h2_RecdX_RecdY_CSC_St4;
      TH2F *h2_SimdX_SimdY_CSC_St1, *h2_SimdX_SimdY_CSC_St2, *h2_SimdX_SimdY_CSC_St3, *h2_SimdX_SimdY_CSC_St4;

      TH2F *h2_RecdX_RecdY_08, *h2_RecdX_RecdY_12, *h2_RecdX_RecdY_20, *h2_RecdX_RecdY_24;
      TH2F *h2_SimdX_SimdY_08, *h2_SimdX_SimdY_12, *h2_SimdX_SimdY_20, *h2_SimdX_SimdY_24;

      //Plot to compare the mean behaviour of the segments
      TH1F       *h1_all_DeltaX_08,       *h1_all_DeltaX_12,       *h1_all_DeltaX_20,       *h1_all_DeltaX_24;
      TH1F       *h1_all_DeltaY_08,       *h1_all_DeltaY_12,       *h1_all_DeltaY_20,       *h1_all_DeltaY_24;
      TH1F      *h1_all_DeltadX_08,      *h1_all_DeltadX_12,      *h1_all_DeltadX_20,      *h1_all_DeltadX_24;
      TH1F      *h1_all_DeltadY_08,      *h1_all_DeltadY_12,      *h1_all_DeltadY_20,      *h1_all_DeltadY_24;

      //Number of Segments in the chamber
      TH1F   *h1_all_Nseg_08,   *h1_all_Nseg_12,   * h1_all_Nseg_20,   *h1_all_Nseg_24;

      //Plot to describe and understand what is going on in the tail
      //Position
      TH1F   *h1_RecX_DT_St1_Wh0, *h1_RecX_DT_St1_Wh1, *h1_RecX_DT_St1_Wh2;
      TH1F   *h1_RecX_DT_St2_Wh0, *h1_RecX_DT_St2_Wh1, *h1_RecX_DT_St2_Wh2;
      TH1F   *h1_RecX_DT_St3_Wh0, *h1_RecX_DT_St3_Wh1, *h1_RecX_DT_St3_Wh2;
      TH1F   *h1_RecX_DT_St4_Wh0, *h1_RecX_DT_St4_Wh1, *h1_RecX_DT_St4_Wh2;

      TH1F   *h1_RecX_DT_PtCut_St1_Wh0, *h1_RecX_DT_PtCut_St1_Wh1, *h1_RecX_DT_PtCut_St1_Wh2;
      TH1F   *h1_RecX_DT_PtCut_St2_Wh0, *h1_RecX_DT_PtCut_St2_Wh1, *h1_RecX_DT_PtCut_St2_Wh2;
      TH1F   *h1_RecX_DT_PtCut_St3_Wh0, *h1_RecX_DT_PtCut_St3_Wh1, *h1_RecX_DT_PtCut_St3_Wh2;
      TH1F   *h1_RecX_DT_PtCut_St4_Wh0, *h1_RecX_DT_PtCut_St4_Wh1, *h1_RecX_DT_PtCut_St4_Wh2;

      TH1F   *h1_RecY_DT_St1_Wh0, *h1_RecY_DT_St1_Wh1, *h1_RecY_DT_St1_Wh2;
      TH1F   *h1_RecY_DT_St2_Wh0, *h1_RecY_DT_St2_Wh1, *h1_RecY_DT_St2_Wh2;
      TH1F   *h1_RecY_DT_St3_Wh0, *h1_RecY_DT_St3_Wh1, *h1_RecY_DT_St3_Wh2;
      TH1F   *h1_RecY_DT_St4_Wh0, *h1_RecY_DT_St4_Wh1, *h1_RecY_DT_St4_Wh2;

      TH1F   *h1_RecY_DT_PtCut_St1_Wh0, *h1_RecY_DT_PtCut_St1_Wh1, *h1_RecY_DT_PtCut_St1_Wh2;
      TH1F   *h1_RecY_DT_PtCut_St2_Wh0, *h1_RecY_DT_PtCut_St2_Wh1, *h1_RecY_DT_PtCut_St2_Wh2;
      TH1F   *h1_RecY_DT_PtCut_St3_Wh0, *h1_RecY_DT_PtCut_St3_Wh1, *h1_RecY_DT_PtCut_St3_Wh2;
      TH1F   *h1_RecY_DT_PtCut_St4_Wh0, *h1_RecY_DT_PtCut_St4_Wh1, *h1_RecY_DT_PtCut_St4_Wh2;

      TH1F   *h1_RecX_CSC_St1_Rg1, *h1_RecX_CSC_St1_Rg2, *h1_RecX_CSC_St1_Rg3;
      TH1F   *h1_RecX_CSC_St2_Rg1, *h1_RecX_CSC_St2_Rg2;
      TH1F   *h1_RecX_CSC_St3_Rg1, *h1_RecX_CSC_St3_Rg2;
      TH1F   *h1_RecX_CSC_St4_Rg1, *h1_RecX_CSC_St4_Rg2;

      TH1F   *h1_RecX_CSC_PtCut_St1_Rg1, *h1_RecX_CSC_PtCut_St1_Rg2, *h1_RecX_CSC_PtCut_St1_Rg3;
      TH1F   *h1_RecX_CSC_PtCut_St2_Rg1, *h1_RecX_CSC_PtCut_St2_Rg2;
      TH1F   *h1_RecX_CSC_PtCut_St3_Rg1, *h1_RecX_CSC_PtCut_St3_Rg2;
      TH1F   *h1_RecX_CSC_PtCut_St4_Rg1, *h1_RecX_CSC_PtCut_St4_Rg2;

      TH1F   *h1_RecY_CSC_St1_Rg1, *h1_RecY_CSC_St1_Rg2, *h1_RecY_CSC_St1_Rg3;
      TH1F   *h1_RecY_CSC_St2_Rg1, *h1_RecY_CSC_St2_Rg2;
      TH1F   *h1_RecY_CSC_St3_Rg1, *h1_RecY_CSC_St3_Rg2;
      TH1F   *h1_RecY_CSC_St4_Rg1, *h1_RecY_CSC_St4_Rg2;

      TH1F   *h1_RecY_CSC_PtCut_St1_Rg1, *h1_RecY_CSC_PtCut_St1_Rg2, *h1_RecY_CSC_PtCut_St1_Rg3;
      TH1F   *h1_RecY_CSC_PtCut_St2_Rg1, *h1_RecY_CSC_PtCut_St2_Rg2;
      TH1F   *h1_RecY_CSC_PtCut_St3_Rg1, *h1_RecY_CSC_PtCut_St3_Rg2;
      TH1F   *h1_RecY_CSC_PtCut_St4_Rg1, *h1_RecY_CSC_PtCut_St4_Rg2;

      //Residuo
      TH1F   *h1_ResRecX_DT_St1_Wh0, *h1_ResRecX_DT_St1_Wh1, *h1_ResRecX_DT_St1_Wh2;
      TH1F   *h1_ResRecX_DT_St2_Wh0, *h1_ResRecX_DT_St2_Wh1, *h1_ResRecX_DT_St2_Wh2;
      TH1F   *h1_ResRecX_DT_St3_Wh0, *h1_ResRecX_DT_St3_Wh1, *h1_ResRecX_DT_St3_Wh2;
      TH1F   *h1_ResRecX_DT_St4_Wh0, *h1_ResRecX_DT_St4_Wh1, *h1_ResRecX_DT_St4_Wh2;

      TH1F   *h1_ResRecX_DT_PtCut_St1_Wh0, *h1_ResRecX_DT_PtCut_St1_Wh1, *h1_ResRecX_DT_PtCut_St1_Wh2;
      TH1F   *h1_ResRecX_DT_PtCut_St2_Wh0, *h1_ResRecX_DT_PtCut_St2_Wh1, *h1_ResRecX_DT_PtCut_St2_Wh2;
      TH1F   *h1_ResRecX_DT_PtCut_St3_Wh0, *h1_ResRecX_DT_PtCut_St3_Wh1, *h1_ResRecX_DT_PtCut_St3_Wh2;
      TH1F   *h1_ResRecX_DT_PtCut_St4_Wh0, *h1_ResRecX_DT_PtCut_St4_Wh1, *h1_ResRecX_DT_PtCut_St4_Wh2;

      TH1F   *h1_ResRecY_DT_St1_Wh0, *h1_ResRecY_DT_St1_Wh1, *h1_ResRecY_DT_St1_Wh2;
      TH1F   *h1_ResRecY_DT_St2_Wh0, *h1_ResRecY_DT_St2_Wh1, *h1_ResRecY_DT_St2_Wh2;
      TH1F   *h1_ResRecY_DT_St3_Wh0, *h1_ResRecY_DT_St3_Wh1, *h1_ResRecY_DT_St3_Wh2;
      TH1F   *h1_ResRecY_DT_St4_Wh0, *h1_ResRecY_DT_St4_Wh1, *h1_ResRecY_DT_St4_Wh2;

      TH1F   *h1_ResRecY_DT_PtCut_St1_Wh0, *h1_ResRecY_DT_PtCut_St1_Wh1, *h1_ResRecY_DT_PtCut_St1_Wh2;
      TH1F   *h1_ResRecY_DT_PtCut_St2_Wh0, *h1_ResRecY_DT_PtCut_St2_Wh1, *h1_ResRecY_DT_PtCut_St2_Wh2;
      TH1F   *h1_ResRecY_DT_PtCut_St3_Wh0, *h1_ResRecY_DT_PtCut_St3_Wh1, *h1_ResRecY_DT_PtCut_St3_Wh2;
      TH1F   *h1_ResRecY_DT_PtCut_St4_Wh0, *h1_ResRecY_DT_PtCut_St4_Wh1, *h1_ResRecY_DT_PtCut_St4_Wh2;

      TH1F   *h1_RecResX_CSC_St1_Rg1, *h1_RecResX_CSC_St1_Rg2, *h1_RecResX_CSC_St1_Rg3;
      TH1F   *h1_RecResX_CSC_St2_Rg1, *h1_RecResX_CSC_St2_Rg2;
      TH1F   *h1_RecResX_CSC_St3_Rg1, *h1_RecResX_CSC_St3_Rg2;
      TH1F   *h1_RecResX_CSC_St4_Rg1, *h1_RecResX_CSC_St4_Rg2;

      TH1F   *h1_RecResX_CSC_PtCut_St1_Rg1, *h1_RecResX_CSC_PtCut_St1_Rg2, *h1_RecResX_CSC_PtCut_St1_Rg3;
      TH1F   *h1_RecResX_CSC_PtCut_St2_Rg1, *h1_RecResX_CSC_PtCut_St2_Rg2;
      TH1F   *h1_RecResX_CSC_PtCut_St3_Rg1, *h1_RecResX_CSC_PtCut_St3_Rg2;
      TH1F   *h1_RecResX_CSC_PtCut_St4_Rg1, *h1_RecResX_CSC_PtCut_St4_Rg2;

      TH1F   *h1_RecResY_CSC_St1_Rg1, *h1_RecResY_CSC_St1_Rg2, *h1_RecResY_CSC_St1_Rg3;
      TH1F   *h1_RecResY_CSC_St2_Rg1, *h1_RecResY_CSC_St2_Rg2;
      TH1F   *h1_RecResY_CSC_St3_Rg1, *h1_RecResY_CSC_St3_Rg2;
      TH1F   *h1_RecResY_CSC_St4_Rg1, *h1_RecResY_CSC_St4_Rg2;

      TH1F   *h1_RecResY_CSC_PtCut_St1_Rg1, *h1_RecResY_CSC_PtCut_St1_Rg2, *h1_RecResY_CSC_PtCut_St1_Rg3;
      TH1F   *h1_RecResY_CSC_PtCut_St2_Rg1, *h1_RecResY_CSC_PtCut_St2_Rg2;
      TH1F   *h1_RecResY_CSC_PtCut_St3_Rg1, *h1_RecResY_CSC_PtCut_St3_Rg2;
      TH1F   *h1_RecResY_CSC_PtCut_St4_Rg1, *h1_RecResY_CSC_PtCut_St4_Rg2;

      //Direction
      TH1F   *h1_RecdX_DT_St1_Wh0, *h1_RecdX_DT_St1_Wh1, *h1_RecdX_DT_St1_Wh2;
      TH1F   *h1_RecdX_DT_St2_Wh0, *h1_RecdX_DT_St2_Wh1, *h1_RecdX_DT_St2_Wh2;
      TH1F   *h1_RecdX_DT_St3_Wh0, *h1_RecdX_DT_St3_Wh1, *h1_RecdX_DT_St3_Wh2;
      TH1F   *h1_RecdX_DT_St4_Wh0, *h1_RecdX_DT_St4_Wh1, *h1_RecdX_DT_St4_Wh2;

      TH1F   *h1_RecdX_DT_PtCut_St1_Wh0, *h1_RecdX_DT_PtCut_St1_Wh1, *h1_RecdX_DT_PtCut_St1_Wh2;
      TH1F   *h1_RecdX_DT_PtCut_St2_Wh0, *h1_RecdX_DT_PtCut_St2_Wh1, *h1_RecdX_DT_PtCut_St2_Wh2;
      TH1F   *h1_RecdX_DT_PtCut_St3_Wh0, *h1_RecdX_DT_PtCut_St3_Wh1, *h1_RecdX_DT_PtCut_St3_Wh2;
      TH1F   *h1_RecdX_DT_PtCut_St4_Wh0, *h1_RecdX_DT_PtCut_St4_Wh1, *h1_RecdX_DT_PtCut_St4_Wh2;

      TH1F   *h1_RecdY_DT_St1_Wh0, *h1_RecdY_DT_St1_Wh1, *h1_RecdY_DT_St1_Wh2;
      TH1F   *h1_RecdY_DT_St2_Wh0, *h1_RecdY_DT_St2_Wh1, *h1_RecdY_DT_St2_Wh2;
      TH1F   *h1_RecdY_DT_St3_Wh0, *h1_RecdY_DT_St3_Wh1, *h1_RecdY_DT_St3_Wh2;
      TH1F   *h1_RecdY_DT_St4_Wh0, *h1_RecdY_DT_St4_Wh1, *h1_RecdY_DT_St4_Wh2;

      TH1F   *h1_RecdY_DT_PtCut_St1_Wh0, *h1_RecdY_DT_PtCut_St1_Wh1, *h1_RecdY_DT_PtCut_St1_Wh2;
      TH1F   *h1_RecdY_DT_PtCut_St2_Wh0, *h1_RecdY_DT_PtCut_St2_Wh1, *h1_RecdY_DT_PtCut_St2_Wh2;
      TH1F   *h1_RecdY_DT_PtCut_St3_Wh0, *h1_RecdY_DT_PtCut_St3_Wh1, *h1_RecdY_DT_PtCut_St3_Wh2;
      TH1F   *h1_RecdY_DT_PtCut_St4_Wh0, *h1_RecdY_DT_PtCut_St4_Wh1, *h1_RecdY_DT_PtCut_St4_Wh2;

      TH1F   *h1_RecdX_CSC_St1_Rg1, *h1_RecdX_CSC_St1_Rg2, *h1_RecdX_CSC_St1_Rg3;
      TH1F   *h1_RecdX_CSC_St2_Rg1, *h1_RecdX_CSC_St2_Rg2;
      TH1F   *h1_RecdX_CSC_St3_Rg1, *h1_RecdX_CSC_St3_Rg2;
      TH1F   *h1_RecdX_CSC_St4_Rg1, *h1_RecdX_CSC_St4_Rg2;

      TH1F   *h1_RecdX_CSC_PtCut_St1_Rg1, *h1_RecdX_CSC_PtCut_St1_Rg2, *h1_RecdX_CSC_PtCut_St1_Rg3;
      TH1F   *h1_RecdX_CSC_PtCut_St2_Rg1, *h1_RecdX_CSC_PtCut_St2_Rg2;
      TH1F   *h1_RecdX_CSC_PtCut_St3_Rg1, *h1_RecdX_CSC_PtCut_St3_Rg2;
      TH1F   *h1_RecdX_CSC_PtCut_St4_Rg1, *h1_RecdX_CSC_PtCut_St4_Rg2;

      TH1F   *h1_RecdY_CSC_St1_Rg1, *h1_RecdY_CSC_St1_Rg2, *h1_RecdY_CSC_St1_Rg3;
      TH1F   *h1_RecdY_CSC_St2_Rg1, *h1_RecdY_CSC_St2_Rg2;
      TH1F   *h1_RecdY_CSC_St3_Rg1, *h1_RecdY_CSC_St3_Rg2;
      TH1F   *h1_RecdY_CSC_St4_Rg1, *h1_RecdY_CSC_St4_Rg2;

      TH1F   *h1_RecdY_CSC_PtCut_St1_Rg1, *h1_RecdY_CSC_PtCut_St1_Rg2, *h1_RecdY_CSC_PtCut_St1_Rg3;
      TH1F   *h1_RecdY_CSC_PtCut_St2_Rg1, *h1_RecdY_CSC_PtCut_St2_Rg2;
      TH1F   *h1_RecdY_CSC_PtCut_St3_Rg1, *h1_RecdY_CSC_PtCut_St3_Rg2;
      TH1F   *h1_RecdY_CSC_PtCut_St4_Rg1, *h1_RecdY_CSC_PtCut_St4_Rg2;

      //Residui direzione
      TH1F   *h1_ResRecdX_DT_St1_Wh0, *h1_ResRecdX_DT_St1_Wh1, *h1_ResRecdX_DT_St1_Wh2;
      TH1F   *h1_ResRecdX_DT_St2_Wh0, *h1_ResRecdX_DT_St2_Wh1, *h1_ResRecdX_DT_St2_Wh2;
      TH1F   *h1_ResRecdX_DT_St3_Wh0, *h1_ResRecdX_DT_St3_Wh1, *h1_ResRecdX_DT_St3_Wh2;
      TH1F   *h1_ResRecdX_DT_St4_Wh0, *h1_ResRecdX_DT_St4_Wh1, *h1_ResRecdX_DT_St4_Wh2;

      TH1F   *h1_ResRecdX_DT_PtCut_St1_Wh0, *h1_ResRecdX_DT_PtCut_St1_Wh1, *h1_ResRecdX_DT_PtCut_St1_Wh2;
      TH1F   *h1_ResRecdX_DT_PtCut_St2_Wh0, *h1_ResRecdX_DT_PtCut_St2_Wh1, *h1_ResRecdX_DT_PtCut_St2_Wh2;
      TH1F   *h1_ResRecdX_DT_PtCut_St3_Wh0, *h1_ResRecdX_DT_PtCut_St3_Wh1, *h1_ResRecdX_DT_PtCut_St3_Wh2;
      TH1F   *h1_ResRecdX_DT_PtCut_St4_Wh0, *h1_ResRecdX_DT_PtCut_St4_Wh1, *h1_ResRecdX_DT_PtCut_St4_Wh2;

      TH1F   *h1_ResRecdY_DT_St1_Wh0, *h1_ResRecdY_DT_St1_Wh1, *h1_ResRecdY_DT_St1_Wh2;
      TH1F   *h1_ResRecdY_DT_St2_Wh0, *h1_ResRecdY_DT_St2_Wh1, *h1_ResRecdY_DT_St2_Wh2;
      TH1F   *h1_ResRecdY_DT_St3_Wh0, *h1_ResRecdY_DT_St3_Wh1, *h1_ResRecdY_DT_St3_Wh2;
      TH1F   *h1_ResRecdY_DT_St4_Wh0, *h1_ResRecdY_DT_St4_Wh1, *h1_ResRecdY_DT_St4_Wh2;

      TH1F   *h1_ResRecdY_DT_PtCut_St1_Wh0, *h1_ResRecdY_DT_PtCut_St1_Wh1, *h1_ResRecdY_DT_PtCut_St1_Wh2;
      TH1F   *h1_ResRecdY_DT_PtCut_St2_Wh0, *h1_ResRecdY_DT_PtCut_St2_Wh1, *h1_ResRecdY_DT_PtCut_St2_Wh2;
      TH1F   *h1_ResRecdY_DT_PtCut_St3_Wh0, *h1_ResRecdY_DT_PtCut_St3_Wh1, *h1_ResRecdY_DT_PtCut_St3_Wh2;
      TH1F   *h1_ResRecdY_DT_PtCut_St4_Wh0, *h1_ResRecdY_DT_PtCut_St4_Wh1, *h1_ResRecdY_DT_PtCut_St4_Wh2;

      TH1F   *h1_RecResdX_CSC_St1_Rg1, *h1_RecResdX_CSC_St1_Rg2, *h1_RecResdX_CSC_St1_Rg3;
      TH1F   *h1_RecResdX_CSC_St2_Rg1, *h1_RecResdX_CSC_St2_Rg2;
      TH1F   *h1_RecResdX_CSC_St3_Rg1, *h1_RecResdX_CSC_St3_Rg2;
      TH1F   *h1_RecResdX_CSC_St4_Rg1, *h1_RecResdX_CSC_St4_Rg2;

      TH1F   *h1_RecResdX_CSC_PtCut_St1_Rg1, *h1_RecResdX_CSC_PtCut_St1_Rg2, *h1_RecResdX_CSC_PtCut_St1_Rg3;
      TH1F   *h1_RecResdX_CSC_PtCut_St2_Rg1, *h1_RecResdX_CSC_PtCut_St2_Rg2;
      TH1F   *h1_RecResdX_CSC_PtCut_St3_Rg1, *h1_RecResdX_CSC_PtCut_St3_Rg2;
      TH1F   *h1_RecResdX_CSC_PtCut_St4_Rg1, *h1_RecResdX_CSC_PtCut_St4_Rg2;

      TH1F   *h1_RecResdY_CSC_St1_Rg1, *h1_RecResdY_CSC_St1_Rg2, *h1_RecResdY_CSC_St1_Rg3;
      TH1F   *h1_RecResdY_CSC_St2_Rg1, *h1_RecResdY_CSC_St2_Rg2;
      TH1F   *h1_RecResdY_CSC_St3_Rg1, *h1_RecResdY_CSC_St3_Rg2;
      TH1F   *h1_RecResdY_CSC_St4_Rg1, *h1_RecResdY_CSC_St4_Rg2;

      TH1F   *h1_RecResdY_CSC_PtCut_St1_Rg1, *h1_RecResdY_CSC_PtCut_St1_Rg2, *h1_RecResdY_CSC_PtCut_St1_Rg3;
      TH1F   *h1_RecResdY_CSC_PtCut_St2_Rg1, *h1_RecResdY_CSC_PtCut_St2_Rg2;
      TH1F   *h1_RecResdY_CSC_PtCut_St3_Rg1, *h1_RecResdY_CSC_PtCut_St3_Rg2;
      TH1F   *h1_RecResdY_CSC_PtCut_St4_Rg1, *h1_RecResdY_CSC_PtCut_St4_Rg2;

      //Differance in position and direction
      TH1F  *h1_DeltaX_DT_St1_Wh0, *h1_DeltaX_DT_St1_Wh1, *h1_DeltaX_DT_St1_Wh2; 
      TH1F  *h1_DeltaX_DT_St2_Wh0, *h1_DeltaX_DT_St2_Wh1, *h1_DeltaX_DT_St2_Wh2; 
      TH1F  *h1_DeltaX_DT_St3_Wh0, *h1_DeltaX_DT_St3_Wh1, *h1_DeltaX_DT_St3_Wh2;
      TH1F  *h1_DeltaX_DT_St4_Wh0, *h1_DeltaX_DT_St4_Wh1, *h1_DeltaX_DT_St4_Wh2;

      TH1F  *h1_DeltaY_DT_St1_Wh0, *h1_DeltaY_DT_St1_Wh1, *h1_DeltaY_DT_St1_Wh2; 
      TH1F  *h1_DeltaY_DT_St2_Wh0, *h1_DeltaY_DT_St2_Wh1, *h1_DeltaY_DT_St2_Wh2; 
      TH1F  *h1_DeltaY_DT_St3_Wh0, *h1_DeltaY_DT_St3_Wh1, *h1_DeltaY_DT_St3_Wh2; 
      TH1F  *h1_DeltaY_DT_St4_Wh0, *h1_DeltaY_DT_St4_Wh1, *h1_DeltaY_DT_St4_Wh2;

      TH1F *h1_DeltaX_CSC_St1_Rg1, *h1_DeltaX_CSC_St1_Rg2, *h1_DeltaX_CSC_St1_Rg3; 
      TH1F *h1_DeltaX_CSC_St2_Rg1, *h1_DeltaX_CSC_St2_Rg2;
      TH1F *h1_DeltaX_CSC_St3_Rg1, *h1_DeltaX_CSC_St3_Rg2;
      TH1F *h1_DeltaX_CSC_St4_Rg1, *h1_DeltaX_CSC_St4_Rg2;

      TH1F *h1_DeltaY_CSC_St1_Rg1, *h1_DeltaY_CSC_St1_Rg2, *h1_DeltaY_CSC_St1_Rg3;
      TH1F *h1_DeltaY_CSC_St2_Rg1, *h1_DeltaY_CSC_St2_Rg2;
      TH1F *h1_DeltaY_CSC_St3_Rg1, *h1_DeltaY_CSC_St3_Rg2;
      TH1F *h1_DeltaY_CSC_St4_Rg1, *h1_DeltaY_CSC_St4_Rg2;

      TH1F  *h1_DeltadX_DT_St1_Wh0, *h1_DeltadX_DT_St1_Wh1, *h1_DeltadX_DT_St1_Wh2;
      TH1F  *h1_DeltadX_DT_St2_Wh0, *h1_DeltadX_DT_St2_Wh1, *h1_DeltadX_DT_St2_Wh2;
      TH1F  *h1_DeltadX_DT_St3_Wh0, *h1_DeltadX_DT_St3_Wh1, *h1_DeltadX_DT_St3_Wh2;
      TH1F  *h1_DeltadX_DT_St4_Wh0, *h1_DeltadX_DT_St4_Wh1, *h1_DeltadX_DT_St4_Wh2;

      TH1F  *h1_DeltadY_DT_St1_Wh0, *h1_DeltadY_DT_St1_Wh1, *h1_DeltadY_DT_St1_Wh2;
      TH1F  *h1_DeltadY_DT_St2_Wh0, *h1_DeltadY_DT_St2_Wh1, *h1_DeltadY_DT_St2_Wh2;
      TH1F  *h1_DeltadY_DT_St3_Wh0, *h1_DeltadY_DT_St3_Wh1, *h1_DeltadY_DT_St3_Wh2;
      TH1F  *h1_DeltadY_DT_St4_Wh0, *h1_DeltadY_DT_St4_Wh1, *h1_DeltadY_DT_St4_Wh2;

      TH1F *h1_DeltadX_CSC_St1_Rg1, *h1_DeltadX_CSC_St1_Rg2, *h1_DeltadX_CSC_St1_Rg3;
      TH1F *h1_DeltadX_CSC_St2_Rg1, *h1_DeltadX_CSC_St2_Rg2;
      TH1F *h1_DeltadX_CSC_St3_Rg1, *h1_DeltadX_CSC_St3_Rg2;
      TH1F *h1_DeltadX_CSC_St4_Rg1, *h1_DeltadX_CSC_St4_Rg2;

      TH1F *h1_DeltadY_CSC_St1_Rg1, *h1_DeltadY_CSC_St1_Rg2, *h1_DeltadY_CSC_St1_Rg3;
      TH1F *h1_DeltadY_CSC_St2_Rg1, *h1_DeltadY_CSC_St2_Rg2;
      TH1F *h1_DeltadY_CSC_St3_Rg1, *h1_DeltadY_CSC_St3_Rg2;
      TH1F *h1_DeltadY_CSC_St4_Rg1, *h1_DeltadY_CSC_St4_Rg2;

      //Err position
      TH1F   *h1_ErrX_DT_St1_Wh0, *h1_ErrX_DT_St1_Wh1, *h1_ErrX_DT_St1_Wh2;
      TH1F   *h1_ErrX_DT_St2_Wh0, *h1_ErrX_DT_St2_Wh1, *h1_ErrX_DT_St2_Wh2;
      TH1F   *h1_ErrX_DT_St3_Wh0, *h1_ErrX_DT_St3_Wh1, *h1_ErrX_DT_St3_Wh2;
      TH1F   *h1_ErrX_DT_St4_Wh0, *h1_ErrX_DT_St4_Wh1, *h1_ErrX_DT_St4_Wh2;

      TH1F   *h1_ErrY_DT_St1_Wh0, *h1_ErrY_DT_St1_Wh1, *h1_ErrY_DT_St1_Wh2;
      TH1F   *h1_ErrY_DT_St2_Wh0, *h1_ErrY_DT_St2_Wh1, *h1_ErrY_DT_St2_Wh2;
      TH1F   *h1_ErrY_DT_St3_Wh0, *h1_ErrY_DT_St3_Wh1, *h1_ErrY_DT_St3_Wh2;
      TH1F   *h1_ErrY_DT_St4_Wh0, *h1_ErrY_DT_St4_Wh1, *h1_ErrY_DT_St4_Wh2;

      TH1F   *h1_ErrX_CSC_St1_Rg1, *h1_ErrX_CSC_St1_Rg2, *h1_ErrX_CSC_St1_Rg3;
      TH1F   *h1_ErrX_CSC_St2_Rg1, *h1_ErrX_CSC_St2_Rg2;
      TH1F   *h1_ErrX_CSC_St3_Rg1, *h1_ErrX_CSC_St3_Rg2;
      TH1F   *h1_ErrX_CSC_St4_Rg1, *h1_ErrX_CSC_St4_Rg2;

      TH1F   *h1_ErrY_CSC_St1_Rg1, *h1_ErrY_CSC_St1_Rg2, *h1_ErrY_CSC_St1_Rg3;
      TH1F   *h1_ErrY_CSC_St2_Rg1, *h1_ErrY_CSC_St2_Rg2;
      TH1F   *h1_ErrY_CSC_St3_Rg1, *h1_ErrY_CSC_St3_Rg2;
      TH1F   *h1_ErrY_CSC_St4_Rg1, *h1_ErrY_CSC_St4_Rg2;

      //Err Position Pt Cut
      TH1F   *h1_ErrX_DT_PtCut_St1_Wh0, *h1_ErrX_DT_PtCut_St1_Wh1, *h1_ErrX_DT_PtCut_St1_Wh2;
      TH1F   *h1_ErrX_DT_PtCut_St2_Wh0, *h1_ErrX_DT_PtCut_St2_Wh1, *h1_ErrX_DT_PtCut_St2_Wh2;
      TH1F   *h1_ErrX_DT_PtCut_St3_Wh0, *h1_ErrX_DT_PtCut_St3_Wh1, *h1_ErrX_DT_PtCut_St3_Wh2;
      TH1F   *h1_ErrX_DT_PtCut_St4_Wh0, *h1_ErrX_DT_PtCut_St4_Wh1, *h1_ErrX_DT_PtCut_St4_Wh2;

      TH1F   *h1_ErrY_DT_PtCut_St1_Wh0, *h1_ErrY_DT_PtCut_St1_Wh1, *h1_ErrY_DT_PtCut_St1_Wh2;
      TH1F   *h1_ErrY_DT_PtCut_St2_Wh0, *h1_ErrY_DT_PtCut_St2_Wh1, *h1_ErrY_DT_PtCut_St2_Wh2;
      TH1F   *h1_ErrY_DT_PtCut_St3_Wh0, *h1_ErrY_DT_PtCut_St3_Wh1, *h1_ErrY_DT_PtCut_St3_Wh2;
      TH1F   *h1_ErrY_DT_PtCut_St4_Wh0, *h1_ErrY_DT_PtCut_St4_Wh1, *h1_ErrY_DT_PtCut_St4_Wh2;

      TH1F   *h1_ErrX_CSC_PtCut_St1_Rg1, *h1_ErrX_CSC_PtCut_St1_Rg2, *h1_ErrX_CSC_PtCut_St1_Rg3;
      TH1F   *h1_ErrX_CSC_PtCut_St2_Rg1, *h1_ErrX_CSC_PtCut_St2_Rg2;
      TH1F   *h1_ErrX_CSC_PtCut_St3_Rg1, *h1_ErrX_CSC_PtCut_St3_Rg2;
      TH1F   *h1_ErrX_CSC_PtCut_St4_Rg1, *h1_ErrX_CSC_PtCut_St4_Rg2;

      TH1F   *h1_ErrY_CSC_PtCut_St1_Rg1, *h1_ErrY_CSC_PtCut_St1_Rg2, *h1_ErrY_CSC_PtCut_St1_Rg3;
      TH1F   *h1_ErrY_CSC_PtCut_St2_Rg1, *h1_ErrY_CSC_PtCut_St2_Rg2;
      TH1F   *h1_ErrY_CSC_PtCut_St3_Rg1, *h1_ErrY_CSC_PtCut_St3_Rg2;
      TH1F   *h1_ErrY_CSC_PtCut_St4_Rg1, *h1_ErrY_CSC_PtCut_St4_Rg2;

      //Err distribution direction
      TH1F   *h1_ErrdX_DT_St1_Wh0, *h1_ErrdX_DT_St1_Wh1, *h1_ErrdX_DT_St1_Wh2;
      TH1F   *h1_ErrdX_DT_St2_Wh0, *h1_ErrdX_DT_St2_Wh1, *h1_ErrdX_DT_St2_Wh2;
      TH1F   *h1_ErrdX_DT_St3_Wh0, *h1_ErrdX_DT_St3_Wh1, *h1_ErrdX_DT_St3_Wh2;
      TH1F   *h1_ErrdX_DT_St4_Wh0, *h1_ErrdX_DT_St4_Wh1, *h1_ErrdX_DT_St4_Wh2;

      TH1F   *h1_ErrdY_DT_St1_Wh0, *h1_ErrdY_DT_St1_Wh1, *h1_ErrdY_DT_St1_Wh2;
      TH1F   *h1_ErrdY_DT_St2_Wh0, *h1_ErrdY_DT_St2_Wh1, *h1_ErrdY_DT_St2_Wh2;
      TH1F   *h1_ErrdY_DT_St3_Wh0, *h1_ErrdY_DT_St3_Wh1, *h1_ErrdY_DT_St3_Wh2;
      TH1F   *h1_ErrdY_DT_St4_Wh0, *h1_ErrdY_DT_St4_Wh1, *h1_ErrdY_DT_St4_Wh2;

      TH1F   *h1_ErrdX_CSC_St1_Rg1, *h1_ErrdX_CSC_St1_Rg2, *h1_ErrdX_CSC_St1_Rg3;
      TH1F   *h1_ErrdX_CSC_St2_Rg1, *h1_ErrdX_CSC_St2_Rg2;
      TH1F   *h1_ErrdX_CSC_St3_Rg1, *h1_ErrdX_CSC_St3_Rg2;
      TH1F   *h1_ErrdX_CSC_St4_Rg1, *h1_ErrdX_CSC_St4_Rg2;

      TH1F   *h1_ErrdY_CSC_St1_Rg1, *h1_ErrdY_CSC_St1_Rg2, *h1_ErrdY_CSC_St1_Rg3;
      TH1F   *h1_ErrdY_CSC_St2_Rg1, *h1_ErrdY_CSC_St2_Rg2;
      TH1F   *h1_ErrdY_CSC_St3_Rg1, *h1_ErrdY_CSC_St3_Rg2;
      TH1F   *h1_ErrdY_CSC_St4_Rg1, *h1_ErrdY_CSC_St4_Rg2;

      //Err distribution Pt Cut
      TH1F   *h1_ErrdX_DT_PtCut_St1_Wh0, *h1_ErrdX_DT_PtCut_St1_Wh1, *h1_ErrdX_DT_PtCut_St1_Wh2;
      TH1F   *h1_ErrdX_DT_PtCut_St2_Wh0, *h1_ErrdX_DT_PtCut_St2_Wh1, *h1_ErrdX_DT_PtCut_St2_Wh2;
      TH1F   *h1_ErrdX_DT_PtCut_St3_Wh0, *h1_ErrdX_DT_PtCut_St3_Wh1, *h1_ErrdX_DT_PtCut_St3_Wh2;
      TH1F   *h1_ErrdX_DT_PtCut_St4_Wh0, *h1_ErrdX_DT_PtCut_St4_Wh1, *h1_ErrdX_DT_PtCut_St4_Wh2;

      TH1F   *h1_ErrdY_DT_PtCut_St1_Wh0, *h1_ErrdY_DT_PtCut_St1_Wh1, *h1_ErrdY_DT_PtCut_St1_Wh2;
      TH1F   *h1_ErrdY_DT_PtCut_St2_Wh0, *h1_ErrdY_DT_PtCut_St2_Wh1, *h1_ErrdY_DT_PtCut_St2_Wh2;
      TH1F   *h1_ErrdY_DT_PtCut_St3_Wh0, *h1_ErrdY_DT_PtCut_St3_Wh1, *h1_ErrdY_DT_PtCut_St3_Wh2;
      TH1F   *h1_ErrdY_DT_PtCut_St4_Wh0, *h1_ErrdY_DT_PtCut_St4_Wh1, *h1_ErrdY_DT_PtCut_St4_Wh2;

      TH1F   *h1_ErrdX_CSC_PtCut_St1_Rg1, *h1_ErrdX_CSC_PtCut_St1_Rg2, *h1_ErrdX_CSC_PtCut_St1_Rg3;
      TH1F   *h1_ErrdX_CSC_PtCut_St2_Rg1, *h1_ErrdX_CSC_PtCut_St2_Rg2;
      TH1F   *h1_ErrdX_CSC_PtCut_St3_Rg1, *h1_ErrdX_CSC_PtCut_St3_Rg2;
      TH1F   *h1_ErrdX_CSC_PtCut_St4_Rg1, *h1_ErrdX_CSC_PtCut_St4_Rg2;

      TH1F   *h1_ErrdY_CSC_PtCut_St1_Rg1, *h1_ErrdY_CSC_PtCut_St1_Rg2, *h1_ErrdY_CSC_PtCut_St1_Rg3;
      TH1F   *h1_ErrdY_CSC_PtCut_St2_Rg1, *h1_ErrdY_CSC_PtCut_St2_Rg2;
      TH1F   *h1_ErrdY_CSC_PtCut_St3_Rg1, *h1_ErrdY_CSC_PtCut_St3_Rg2;
      TH1F   *h1_ErrdY_CSC_PtCut_St4_Rg1, *h1_ErrdY_CSC_PtCut_St4_Rg2;

      //Correlation between error and differace between reco and Sim
      TH2F   *h2_RecResdX_ErrdX_DT_St1_Wh0, *h2_RecResdX_ErrdX_DT_St1_Wh1, *h2_RecResdX_ErrdX_DT_St1_Wh2;
      TH2F   *h2_RecResdX_ErrdX_DT_St2_Wh0, *h2_RecResdX_ErrdX_DT_St2_Wh1, *h2_RecResdX_ErrdX_DT_St2_Wh2;
      TH2F   *h2_RecResdX_ErrdX_DT_St3_Wh0, *h2_RecResdX_ErrdX_DT_St3_Wh1, *h2_RecResdX_ErrdX_DT_St3_Wh2;
      TH2F   *h2_RecResdX_ErrdX_DT_St4_Wh0, *h2_RecResdX_ErrdX_DT_St4_Wh1, *h2_RecResdX_ErrdX_DT_St4_Wh2;

      TH2F   *h2_RecResdY_ErrdY_DT_St1_Wh0, *h2_RecResdY_ErrdY_DT_St1_Wh1, *h2_RecResdY_ErrdY_DT_St1_Wh2;
      TH2F   *h2_RecResdY_ErrdY_DT_St2_Wh0, *h2_RecResdY_ErrdY_DT_St2_Wh1, *h2_RecResdY_ErrdY_DT_St2_Wh2;
      TH2F   *h2_RecResdY_ErrdY_DT_St3_Wh0, *h2_RecResdY_ErrdY_DT_St3_Wh1, *h2_RecResdY_ErrdY_DT_St3_Wh2;
      TH2F   *h2_RecResdY_ErrdY_DT_St4_Wh0, *h2_RecResdY_ErrdY_DT_St4_Wh1, *h2_RecResdY_ErrdY_DT_St4_Wh2;

      TH2F   *h2_RecResdX_ErrdX_CSC_St1_Rg1, *h2_RecResdX_ErrdX_CSC_St1_Rg2, *h2_RecResdX_ErrdX_CSC_St1_Rg3;
      TH2F   *h2_RecResdX_ErrdX_CSC_St2_Rg1, *h2_RecResdX_ErrdX_CSC_St2_Rg2;
      TH2F   *h2_RecResdX_ErrdX_CSC_St3_Rg1, *h2_RecResdX_ErrdX_CSC_St3_Rg2;
      TH2F   *h2_RecResdX_ErrdX_CSC_St4_Rg1, *h2_RecResdX_ErrdX_CSC_St4_Rg2;

      TH2F   *h2_RecResdY_ErrdY_CSC_St1_Rg1, *h2_RecResdY_ErrdY_CSC_St1_Rg2, *h2_RecResdY_ErrdY_CSC_St1_Rg3;
      TH2F   *h2_RecResdY_ErrdY_CSC_St2_Rg1, *h2_RecResdY_ErrdY_CSC_St2_Rg2;
      TH2F   *h2_RecResdY_ErrdY_CSC_St3_Rg1, *h2_RecResdY_ErrdY_CSC_St3_Rg2;
      TH2F   *h2_RecResdY_ErrdY_CSC_St4_Rg1, *h2_RecResdY_ErrdY_CSC_St4_Rg2;

      //Track the segments situation
      TH1F   *h1_1Seg_DT, *h1_1Seg_CSC;
      TH2F   *h2_2Seg_DT, *h2_2Seg_CSC, *h2_1Seg_DT_1Seg_CSC;
      TH1F   *h1_3Seg_DT, *h1_3Seg_CSC;

      //Scatter plot Diff and Err
      TH2F   *h2_RecResdX_ErrdX_UpStation1_DirZ_1_CSC_St1_Rg1;
      TH2F   *h2_RecResdY_ErrdY_UpStation1_DirZ_1_CSC_St1_Rg1;
      TH2F   *h2_RecResdX_ErrdX_DwStation1_DirZ_1_CSC_St1_Rg1;
      TH2F   *h2_RecResdY_ErrdY_DwStation1_DirZ_1_CSC_St1_Rg1;

      TH2F   *h2_RecResdX_ErrdX_UpStation1_DirZ_m1_CSC_St1_Rg1;
      TH2F   *h2_RecResdY_ErrdY_UpStation1_DirZ_m1_CSC_St1_Rg1;
      TH2F   *h2_RecResdX_ErrdX_DwStation1_DirZ_m1_CSC_St1_Rg1;
      TH2F   *h2_RecResdY_ErrdY_DwStation1_DirZ_m1_CSC_St1_Rg1;

      TH2F   *h2_SimX_SimY_DwStation1_DirZ_1_CSC_St1_Rg1;
      TH2F   *h2_SimX_SimY_DwStation1_DirZ_m1_CSC_St1_Rg1;

      TH2F   *h2_RecX_RecY_DwStation1_DirZ_1_CSC_St1_Rg1;
      TH2F   *h2_RecX_RecY_DwStation1_DirZ_m1_CSC_St1_Rg1;

};

DYTthrScanTuner::DYTthrScanTuner(const edm::ParameterSet& pset) 
{

   psim = pset.getParameter<double>("psim");
   
   label_track_coll  = pset.getParameter< edm::InputTag >("label_track_coll"); 
   label_recHit_csc  = pset.getParameter< edm::InputTag >("label_recHit_CSC");
   label_simHit_csc  = pset.getParameter< edm::InputTag >("label_simHit_CSC");
   label_seg_csc     = pset.getParameter< edm::InputTag >("label_seg_CSC");
   label_recHit_dt   = pset.getParameter< edm::InputTag >("label_recHit_DT");
   label_simHit_dt   = pset.getParameter< edm::InputTag >("label_simHit_DT");
   label_seg_dt      = pset.getParameter< edm::InputTag >("label_seg_DT");
   label_gen_coll    = pset.getParameter< edm::InputTag >("label_gen_coll");

   track_collection_Token    = consumes<edm::View<reco::Track> >(label_track_coll);
   rh_csc_Token              = consumes<CSCRecHit2DCollection>(label_recHit_csc);
   sh_csc_Token              = consumes<edm::PSimHitContainer>(label_simHit_csc);
   se_csc_Token              = consumes<CSCSegmentCollection>(label_seg_csc); 
   rh_dt_Token               = consumes<DTRecHitCollection>(label_recHit_dt); 
   sh_dt_Token               = consumes<edm::PSimHitContainer>(label_simHit_dt);
   se_dt_Token               = consumes<DTRecSegment4DCollection>(label_seg_dt);
   gen_collection_Token      = consumes<edm::View<reco::GenParticle> >(label_gen_coll);
 
   usesResource("TFileService");

}


DYTthrScanTuner::~DYTthrScanTuner(){}

void DYTthrScanTuner::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  using namespace std;
  using namespace edm;
  using namespace reco;

  //Generator Collection
  edm::Handle<edm::View<reco::GenParticle> > gen;
  iEvent.getByToken(gen_collection_Token, gen);  

  //Track Collection
  edm::Handle<edm::View<Track> > trackCollection;
  iEvent.getByToken(track_collection_Token, trackCollection); 

  //Muon Geometry
  edm::ESHandle<CSCGeometry> cscGeom;
  iSetup.get<MuonGeometryRecord>().get(cscGeom);

  ESHandle<DTGeometry> dtGeom;
  iSetup.get<MuonGeometryRecord>().get(dtGeom);

  //CSC
  edm::Handle<CSCRecHit2DCollection> recCSCHits;
  iEvent.getByToken( rh_csc_Token, recCSCHits );

  edm::Handle<edm::PSimHitContainer> simCSCHits;
  iEvent.getByToken( sh_csc_Token, simCSCHits );

  edm::Handle<CSCSegmentCollection> cscSegments;
  iEvent.getByToken( se_csc_Token, cscSegments );

  //DT
  edm::Handle<DTRecHitCollection> recDTHits;
  iEvent.getByToken( rh_dt_Token, recDTHits );

  edm::Handle<edm::PSimHitContainer> simDTHits;
  iEvent.getByToken( sh_dt_Token, simDTHits );

  edm::Handle<DTRecSegment4DCollection> dtSegments;
  iEvent.getByToken( se_dt_Token, dtSegments);

  //Loop on the Track
  for(edm::View<Track>::size_type i=0; i < trackCollection->size(); ++i){

	//std::cout << " " << std::endl;
	//std::cout << "//////////////" << std::endl;
	//std::cout << "// New Muon //" << std::endl;	
	//std::cout << "//////////////" << std::endl;
	//std::cout << " " << std::endl;
	//Initialization Kinematical Variable
	muon_p=0; muon_pt=0; muon_eta=0;

	//Track studies
    RefToBase<Track> DYTtrack(trackCollection, i);
	muon_p = DYTtrack->p(); muon_pt =  DYTtrack->pt(); muon_eta = DYTtrack->eta();
	TLorentzVector DYTtrackVector;
	double DYTenergy = std::sqrt( std::pow(mass,2) + std::pow(muon_p,2) );
	DYTtrackVector.SetPtEtaPhiE(muon_pt,muon_eta,DYTtrack->phi(),DYTenergy);



	auto const & trajParams = DYTtrack->extra()->trajParams();
	assert( trajParams.size()==DYTtrack->recHitsSize() );

	//understand the segment distribution
	if( muon_p>(psim+psim/5) ){	
		if( DYTtrack->recHitsSize() == 1 ){	
			auto hit1 = DYTtrack->recHit(0);
			if( !hit1->isValid() ) continue;	
			DetId id = hit1->geographicalId();
			if( id.det() != DetId::Muon) continue;	
			int subDet = id.subdetId();
			if( subDet==1 ){ DTChamberId isDTRec(id); h1_1Seg_DT->Fill( isDTRec.station() ); } 
			else if( subDet==2 ){ CSCDetId isCSCRec(id); h1_1Seg_CSC->Fill( isCSCRec.station() ); }
		} else if( DYTtrack->recHitsSize() == 2 ){	
                	auto hit1 = DYTtrack->recHit(0); auto hit2 = DYTtrack->recHit(1);
			if( !hit1->isValid() && !hit2->isValid() ) continue;
			DetId id1 = hit1->geographicalId(); DetId id2 = hit2->geographicalId();
			if( id1.det() != DetId::Muon && id2.det() != DetId::Muon ) continue;
			int subDet1 = id1.subdetId(); int subDet2 = id2.subdetId();
			if( subDet1 == 1 && subDet2 == 1 ){ 
				DTChamberId isDTRec1(id1); DTChamberId isDTRec2(id2);
				h2_2Seg_DT->Fill( isDTRec1.station(), isDTRec2.station());
			} else if( subDet1 == 2 && subDet2 == 2 ){ 
				CSCDetId isCSCRec1(id1); CSCDetId isCSCRec2(id2);
				h2_2Seg_CSC->Fill( isCSCRec1.station(), isCSCRec2.station());
			} else if( subDet1 == 1 && subDet2 == 2 ){
				DTChamberId isDTRec1(id1); CSCDetId isCSCRec2(id2);
				h2_1Seg_DT_1Seg_CSC->Fill( isDTRec1.station(), isCSCRec2.station());
			} else if( subDet1 == 2 && subDet2 == 1 ){
				CSCDetId isCSCRec1(id1); DTChamberId isDTRec2(id2);
                        	h2_1Seg_DT_1Seg_CSC->Fill( isDTRec2.station(), isCSCRec1.station());
			}
		} else if( DYTtrack->recHitsSize() == 3 ){	
			auto hit1 = DYTtrack->recHit(0); auto hit2 = DYTtrack->recHit(1); auto hit3 = DYTtrack->recHit(2);
			if( !hit1->isValid() && !hit2->isValid() && !hit3->isValid() ) continue;
			DetId id1 = hit1->geographicalId(); DetId id2 = hit2->geographicalId(); DetId id3 = hit3->geographicalId();
			if( id1.det() != DetId::Muon && id2.det() != DetId::Muon && id3.det() != DetId::Muon ) continue;
			int subDet1 = id1.subdetId(); int subDet2 = id2.subdetId(); int subDet3 = id3.subdetId();
			if( subDet1 == 1 && subDet2 == 1 && subDet1 == 1 ){ 
				DTChamberId isDTRec1(id1); DTChamberId isDTRec2(id2); DTChamberId isDTRec3(id3);
				int st1 = isDTRec1.station(); int st2 = isDTRec2.station(); int st3 = isDTRec3.station();
				if( ( st1 == 1 && st2 == 2 && st3 == 3 ) ||
				    ( st1 == 2 && st2 == 3 && st3 == 1 ) ||
				    ( st1 == 3 && st2 == 1 && st3 == 2 ) ){ h1_3Seg_DT->Fill( 4 );}
				else if ( ( st1 == 1 && st2 == 2 && st3 == 4 ) ||
                                          ( st1 == 2 && st2 == 4 && st3 == 1 ) ||
                                          ( st1 == 4 && st2 == 1 && st3 == 2 ) ){ h1_3Seg_DT->Fill( 3 ); }
				else if ( ( st1 == 1 && st2 == 3 && st3 == 4 ) ||
                                          ( st1 == 3 && st2 == 4 && st3 == 1 ) ||
                                          ( st1 == 4 && st2 == 1 && st3 == 3 ) ){ h1_3Seg_DT->Fill( 2 ); }
                                else if ( ( st1 == 2 && st2 == 3 && st3 == 4 ) ||
                                          ( st1 == 3 && st2 == 4 && st3 == 2 ) ||
                                          ( st1 == 4 && st2 == 2 && st3 == 3 ) ){ h1_3Seg_DT->Fill( 1 ); }
			} else if( subDet1 == 2 && subDet2 == 2 && subDet1 == 2 ){
				CSCDetId isCSCRec1(id1); CSCDetId isCSCRec2(id2); CSCDetId isCSCRec3(id3);
				int st1 = isCSCRec1.station(); int st2 = isCSCRec2.station(); int st3 = isCSCRec3.station();
                                if( ( st1 == 1 && st2 == 2 && st3 == 3 ) ||
                                    ( st1 == 2 && st2 == 3 && st3 == 1 ) ||
                                    ( st1 == 3 && st2 == 1 && st3 == 2 ) ){ h1_3Seg_CSC->Fill( 4 );}
                                else if ( ( st1 == 1 && st2 == 2 && st3 == 4 ) ||
                                          ( st1 == 2 && st2 == 4 && st3 == 1 ) ||
                                          ( st1 == 4 && st2 == 1 && st3 == 2 ) ){ h1_3Seg_CSC->Fill( 3 ); }
                                else if ( ( st1 == 1 && st2 == 3 && st3 == 4 ) ||
                                          ( st1 == 3 && st2 == 4 && st3 == 1 ) ||
                                          ( st1 == 4 && st2 == 1 && st3 == 3 ) ){ h1_3Seg_CSC->Fill( 2 ); }
                                else if ( ( st1 == 2 && st2 == 3 && st3 == 4 ) ||
                                          ( st1 == 3 && st2 == 4 && st3 == 2 ) ||
                                          ( st1 == 4 && st2 == 2 && st3 == 3 ) ){ h1_3Seg_CSC->Fill( 1 ); }
			}

		} 
	} 

	//Loop on Track recHit
	for(unsigned int h=0;h<DYTtrack->recHitsSize();h++){
		
      	auto hit = DYTtrack->recHit(h); //In una Track recHits individua il Segmento
		//Select Valid Hits
      	if (!hit->isValid()) continue;
      	
        DetId id = hit->geographicalId();
	 	LocalPoint rhitlocal = hit->localPosition();
		//Local Position of the Segment in the Chamber Local Frame
		float xHitRec = rhitlocal.x(); float yHitRec = rhitlocal.y();	
		
        //Select Muon Chamber	
		if(id.det() != DetId::Muon) continue; 
        
        int subDet = id.subdetId(); //1 == DT, 2 == CSC 	
		if(ubDet==2){ 
			CSCDetId isCSCRec(id);
			int cscStation = isCSCRec.station();
			int SegCounter = 0;
			
            //Loop on CSCSegment	
			for(CSCSegmentCollection::const_iterator segIt=cscSegments->begin(); segIt != cscSegments->end(); segIt++){
				CSCDetId idCSCSeg  = (CSCDetId)(*segIt).cscDetId();
				AlgebraicVector    posSegInfo = (*segIt).parameters();
				AlgebraicSymMatrix  posSegErr = (*segIt).parametersError();
				//Local Position of the Segment coming from the CSC segment collection in the Local Chamber Frame
				LocalPoint InitSegPoint; LocalPoint FinSegPoint;
				float  xSegRec = posSegInfo[2]; float  ySegRec = posSegInfo[3];
                float dxSegRec = posSegInfo[0]; float dySegRec = posSegInfo[1];	
				float  xSegErr = std::sqrt(posSegErr(3,3)); float  ySegErr = std::sqrt(posSegErr(4,4));	
				float dxSegErr = std::sqrt(posSegErr(1,1)); float dySegErr = std::sqrt(posSegErr(2,2));
                                      
			    if( idCSCSeg == isCSCRec ){
				    float  xsimSeg = 0;    float  ysimSeg = 0;
				    float dxSimSeg = 0;    float dySimSeg = 0;
				    int st = idCSCSeg.station(); int rg = idCSCSeg.ring(); int zdir = idCSCSeg.zendcap();
			 	    SegCounter++;	
				    //Match between Seg and recHit using DetId and LocalPosition	
				    if( idCSCSeg == isCSCRec && (abs(xHitRec-xSegRec)/abs(xHitRec))<0.01 && (abs(yHitRec-ySegRec)/abs(ySegRec))<0.01){	
					    float   absMin = 1E11; float   absMax = 0; 	
					    bool hitMatch(false);
					    int hitMatchedCounter = 0;	
					    for(unsigned int hitSeg=0; hitSeg<(*segIt).specificRecHits().size(); hitSeg++){
						    auto segHit = (*segIt).specificRecHits().at(hitSeg);
						    CSCDetId recHitId = segHit.cscDetId();
						    //Change of the referance Frame from Layer to Chamber
						    LocalPoint segHitlocal       = segHit.localPosition();
						    const CSCLayer* cscReclayer  = cscGeom->layer( recHitId );
                            GlobalPoint shitRecGlobal    = cscReclayer->toGlobal(segHitlocal);
                            const CSCChamber* cscchamber = cscGeom->chamber(idCSCSeg);
                            LocalPoint shitReclocalCh    = cscchamber->toLocal(shitRecGlobal);
						    float xHitSeg = shitReclocalCh.x(); float yHitSeg = shitReclocalCh.y();	
						    //Loop on CSC SimHit		
						    for( unsigned int csch=0; csch<simCSCHits->size(); csch++){
							    CSCDetId simHitId = (CSCDetId)simCSCHits->at(csch).detUnitId();
							    //Change of the referance Frame from Layer to Chamber
							    LocalPoint shitSimlocal      = simCSCHits->at(csch).localPosition();
				                const CSCLayer* cscSimlayer  = cscGeom->layer(simHitId);
                                GlobalPoint shitSimGlobal    = cscSimlayer->toGlobal(shitSimlocal);
                                const CSCChamber* cscchamber = cscGeom->chamber(idCSCSeg);
                                LocalPoint shitSimlocalCh    = cscchamber->toLocal(shitSimGlobal);
							    float xsim = shitSimlocalCh.x(); float ysim = shitSimlocalCh.y();
									
							    if(recHitId == simHitId && abs(simCSCHits->at(csch).particleType()) == 13 ){	
								    float TrjEnergy = std::sqrt( std::pow(mass,2) + std::pow(trajParams.at(h).momentum().mag(),2));
								    float SimEnergy = std::sqrt( std::pow(mass,2) + std::pow(simCSCHits->at(csch).pabs(),2));
                                    //std::cout << "CSC ==> Ring " << simHitId.ring() << " Chamber " << simHitId.chamber() << " Station " << simHitId.station() << " Layer " << simHitId.layer() << " X Local " << xsim << " Y Local " << ysim << " Energy " << SimEnergy << std::endl;
								    if( SimEnergy < 1 ) continue;	

									float tmpAbs = shitSimGlobal.mag();
									hitMatch =  true; hitMatchedCounter++;
                                    if( tmpAbs < absMin ){
                                    	absMin = tmpAbs;
                                    	InitSegPoint = shitSimlocalCh;
                                    }
                                    if( tmpAbs > absMax ){
                                    	absMax = tmpAbs;
                                    	FinSegPoint = shitSimlocalCh;
                                    }				
										
									//Energy Loss By Station
						        	if(cscStation==1){
									    double ElossReco_CSC_St1 = psim - TrjEnergy;
									    double ElossSim_CSC_St1  = psim - SimEnergy;
									    h1_DeltaESim_CSC_St1->Fill(ElossSim_CSC_St1);
									    h1_DeltaERec_CSC_St1->Fill(ElossReco_CSC_St1);
									    h2_DeltaSim_DeltaRec_CSC_St1->Fill(ElossReco_CSC_St1,ElossSim_CSC_St1);	
									}else if(cscStation==2){
										double ElossReco_CSC_St2 = psim - TrjEnergy;
                                        double ElossSim_CSC_St2  = psim - SimEnergy;
                                        h1_DeltaESim_CSC_St2->Fill(ElossSim_CSC_St2);
                                        h1_DeltaERec_CSC_St2->Fill(ElossReco_CSC_St2);
                                        h2_DeltaSim_DeltaRec_CSC_St2->Fill(ElossReco_CSC_St2,ElossSim_CSC_St2);
									}else if(cscStation==3){
										double ElossReco_CSC_St3 = psim - TrjEnergy;
                                        double ElossSim_CSC_St3  = psim - SimEnergy;	
                                        h1_DeltaESim_CSC_St3->Fill(ElossSim_CSC_St3);
                                        h1_DeltaERec_CSC_St3->Fill(ElossReco_CSC_St3);
                                        h2_DeltaSim_DeltaRec_CSC_St3->Fill(ElossReco_CSC_St3,ElossSim_CSC_St3);
									}else if(cscStation==4){
										double ElossReco_CSC_St4 = psim - TrjEnergy;
                                        double ElossSim_CSC_St4  = psim - SimEnergy;
                                        h1_DeltaESim_CSC_St4->Fill(ElossSim_CSC_St4);
                                        h1_DeltaERec_CSC_St4->Fill(ElossReco_CSC_St4);
                                        h2_DeltaSim_DeltaRec_CSC_St4->Fill(ElossReco_CSC_St4,ElossSim_CSC_St4);
									}

									//Energy Loss By Eta
        							if(std::abs(muon_eta)<=0.8){
                						double ElossReco_CSC_08 = psim - TrjEnergy;
                                        double ElossSim_CSC_08  = psim - SimEnergy;	
										h1_DeltaESim_08->Fill(ElossSim_CSC_08); 
										h1_DeltaERec_08->Fill(ElossReco_CSC_08);
										h2_DeltaSim_DeltaRec_08->Fill(ElossReco_CSC_08,ElossSim_CSC_08);	
        							} else if(std::abs(muon_eta)>0.8 && std::abs(muon_eta)<=1.2){	
                                        double ElossReco_CSC_12 = psim - TrjEnergy;
                                        double ElossSim_CSC_12  = psim - SimEnergy; 
                                        h1_DeltaESim_12->Fill(ElossSim_CSC_12);
                                        h1_DeltaERec_12->Fill(ElossReco_CSC_12);
                       				    h2_DeltaSim_DeltaRec_12->Fill(ElossReco_CSC_12,ElossSim_CSC_12); 
        							} else if(std::abs(muon_eta)>1.2 && std::abs(muon_eta)<=2.0){
                                        double ElossReco_CSC_20 = psim - TrjEnergy;
                                        double ElossSim_CSC_20  = psim - SimEnergy;
                                        h1_DeltaESim_20->Fill(ElossSim_CSC_20);
										h1_DeltaERec_20->Fill(ElossReco_CSC_20);
                                        h2_DeltaSim_DeltaRec_20->Fill(ElossReco_CSC_20,ElossSim_CSC_20);
        							} else if(std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4){
                                        double ElossReco_CSC_24 = psim - TrjEnergy;
                                        double ElossSim_CSC_24  = psim - SimEnergy;
                                        h1_DeltaESim_24->Fill(ElossSim_CSC_24);
                                        h1_DeltaERec_24->Fill(ElossReco_CSC_24);
                                        h2_DeltaSim_DeltaRec_24->Fill(ElossReco_CSC_24,ElossSim_CSC_24);
        							}
							    } // End matching SimHit RecHit					
						    }// END Loop on CSC SimHit
					    } //END loop on Segment's RecHit
	
					if( hitMatch == false) continue; 
					if( hitMatchedCounter < 2 ) continue;

					//Mean Position of Sim Segment		
                                        LocalPoint MeanPosition = meanPoint(InitSegPoint,FinSegPoint);
					//std::cout << "Mean X " << MeanPosition.x() << " Y " << MeanPosition.y() << std::endl;
					if( MeanPosition.z() == -1E10 && MeanPosition.x() == -1E10 && MeanPosition.y() == -1E10 ){
                                        	xsimSeg = xSegRec; 
                                        	ysimSeg = ySegRec;
					} else {
						xsimSeg = MeanPosition.x();
						ysimSeg = MeanPosition.y();
					}	
					//Direction of the SimSegment
                                        dxSimSeg = (InitSegPoint.x()-FinSegPoint.x())/(InitSegPoint.z()-FinSegPoint.z());
                                        dySimSeg = (InitSegPoint.y()-FinSegPoint.y())/(InitSegPoint.z()-FinSegPoint.z());	
 
					//std::cout << "##############################" << std::endl; 
					//std::cout << "dxSegRec: " << dxSegRec << "; dxSimSeg: " << dxSimSeg << std::endl;
					//std::cout << "dySegRec: " << dySegRec << "; dySimSeg: " << dySimSeg << std::endl;
                                        //std::cout << "dxSegErr: " << dxSegErr << "; dySegErr: " << dySegErr << std::endl;
					//std::cout << "(dxSegRec-dxSimSeg)/dxSegErr: " << (dxSegRec-dxSimSeg)/dxSegErr << "; (dySegRec-dySimSeg)/dySegErr): " << (dySegRec-dySimSeg)/dySegErr << std::endl;
 
					//Filling Histo for Position Studies by Station
					if(cscStation==1){
						h1_DeltaX_CSC_St1->Fill(xSegRec - xsimSeg);
						h1_DeltaY_CSC_St1->Fill(ySegRec - ysimSeg);
						h2_RecX_SimX_CSC_St1->Fill( xSegRec, xsimSeg);
						h2_RecY_SimY_CSC_St1->Fill( ySegRec, ysimSeg);
						h2_RecX_RecY_CSC_St1->Fill( xSegRec, ySegRec);
						h2_SimX_SimY_CSC_St1->Fill( xsimSeg, ysimSeg);

                                                h1_DeltadX_CSC_St1->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St1->Fill(dySegRec-dySimSeg);
                                                h2_RecdX_SimdX_CSC_St1->Fill(dxSegRec,dxSimSeg);
                                                h2_RecdY_SimdY_CSC_St1->Fill(dySegRec,dySimSeg);
						h2_RecdX_RecdY_CSC_St1->Fill(dxSegRec,dySegRec);
						h2_SimdX_SimdY_CSC_St1->Fill(dxSimSeg,dySimSeg);
					} else if(cscStation==2){
                                                h1_DeltaX_CSC_St2->Fill(xSegRec - xsimSeg);
                                                h1_DeltaY_CSC_St2->Fill(ySegRec - ysimSeg);
                                                h2_RecX_SimX_CSC_St2->Fill( xSegRec, xsimSeg);
                                                h2_RecY_SimY_CSC_St2->Fill( ySegRec, ysimSeg);
                                                h2_RecX_RecY_CSC_St2->Fill( xSegRec, ySegRec);
                                                h2_SimX_SimY_CSC_St2->Fill( xsimSeg, ysimSeg);

                                                h1_DeltadX_CSC_St2->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St2->Fill(dySegRec-dySimSeg);
                                                h2_RecdX_SimdX_CSC_St2->Fill(dxSegRec,dxSimSeg);
                                                h2_RecdY_SimdY_CSC_St2->Fill(dySegRec,dySimSeg);
                                                h2_RecdX_RecdY_CSC_St2->Fill(dxSegRec,dySegRec);
                                                h2_SimdX_SimdY_CSC_St2->Fill(dxSimSeg,dySimSeg); 
					} else if(cscStation==3){
                                                h1_DeltaX_CSC_St3->Fill(xSegRec - xsimSeg);
                                                h1_DeltaY_CSC_St3->Fill(ySegRec - ysimSeg);
                                                h2_RecX_SimX_CSC_St3->Fill( xSegRec, xsimSeg);
                                                h2_RecY_SimY_CSC_St3->Fill( ySegRec, ysimSeg);
                                                h2_RecX_RecY_CSC_St3->Fill( xSegRec, ySegRec);
                                                h2_SimX_SimY_CSC_St3->Fill( xsimSeg, ysimSeg);

                                                h1_DeltadX_CSC_St3->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St3->Fill(dySegRec-dySimSeg);
                                                h2_RecdX_SimdX_CSC_St3->Fill(dxSegRec,dxSimSeg);
                                                h2_RecdY_SimdY_CSC_St3->Fill(dySegRec,dySimSeg); 
                                                h2_RecdX_RecdY_CSC_St3->Fill(dxSegRec,dySegRec);
                                                h2_SimdX_SimdY_CSC_St3->Fill(dxSimSeg,dySimSeg); 
					} else if(cscStation==4){
                                                h1_DeltaX_CSC_St4->Fill(xSegRec - xsimSeg);
                                                h1_DeltaY_CSC_St4->Fill(ySegRec - ysimSeg);
                                                h2_RecX_SimX_CSC_St4->Fill( xSegRec, xsimSeg);
                                                h2_RecY_SimY_CSC_St4->Fill( ySegRec, ysimSeg);
                                                h2_RecX_RecY_CSC_St4->Fill( xSegRec, ySegRec);
                                                h2_SimX_SimY_CSC_St4->Fill( xsimSeg, ysimSeg);

                                                h1_DeltadX_CSC_St4->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St4->Fill(dySegRec-dySimSeg);
                                                h2_RecdX_SimdX_CSC_St4->Fill(dxSegRec,dxSimSeg);
                                                h2_RecdY_SimdY_CSC_St4->Fill(dySegRec,dySimSeg);
                                                h2_RecdX_RecdY_CSC_St4->Fill(dxSegRec,dySegRec);
                                                h2_SimdX_SimdY_CSC_St4->Fill(dxSimSeg,dySimSeg); 
					}
 
					//Filling Histo for Position by Eta
					if(std::abs(muon_eta)<=0.8){
						h1_DeltaX_08->Fill(xSegRec - xsimSeg);
						h1_DeltaY_08->Fill(ySegRec - ysimSeg);
						h2_RecX_SimX_08->Fill( xSegRec, xsimSeg);
						h2_RecY_SimY_08->Fill( ySegRec, ysimSeg);
						h2_RecX_RecY_08->Fill( xSegRec, ySegRec);
						h2_SimX_SimY_08->Fill( xsimSeg, ysimSeg);

                                                h1_DeltadX_08->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_08->Fill(dySegRec-dySimSeg);
                                                h2_RecdX_SimdX_08->Fill(dxSegRec,dxSimSeg);
                                                h2_RecdY_SimdY_08->Fill(dySegRec,dySimSeg);
						h2_RecdX_RecdY_08->Fill(dxSegRec,dySegRec);
						h2_SimdX_SimdY_08->Fill(dxSimSeg,dxSimSeg);
					} else if(std::abs(muon_eta)>0.8 && std::abs(muon_eta)<=1.2){
                                                h1_DeltaX_12->Fill(xSegRec - xsimSeg);
                                                h1_DeltaY_12->Fill(ySegRec - ysimSeg);
                                                h2_RecX_SimX_12->Fill( xSegRec, xsimSeg);
                                                h2_RecY_SimY_12->Fill( ySegRec, ysimSeg);
                                                h2_RecX_RecY_12->Fill( xSegRec, ySegRec);
                                                h2_SimX_SimY_12->Fill( xsimSeg, ysimSeg); 

                                                h1_DeltadX_12->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_12->Fill(dySegRec-dySimSeg);
                                                h2_RecdX_SimdX_12->Fill(dxSegRec,dxSimSeg);
                                                h2_RecdY_SimdY_12->Fill(dySegRec,dySimSeg);
                                                h2_RecdX_RecdY_12->Fill(dxSegRec,dySegRec);
                                                h2_SimdX_SimdY_12->Fill(dxSimSeg,dxSimSeg);
					} else if(std::abs(muon_eta)>1.2 && std::abs(muon_eta)<=2.0){
                                                h1_DeltaX_20->Fill(xSegRec - xsimSeg);
                                                h1_DeltaY_20->Fill(ySegRec - ysimSeg);
                                                h2_RecX_SimX_20->Fill( xSegRec, xsimSeg);
                                                h2_RecY_SimY_20->Fill( ySegRec, ysimSeg);
                                                h2_RecX_RecY_20->Fill( xSegRec, ySegRec);
                                                h2_SimX_SimY_20->Fill( xsimSeg, ysimSeg); 

                                                h1_DeltadX_20->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_20->Fill(dySegRec-dySimSeg);
                                                h2_RecdX_SimdX_20->Fill(dxSegRec,dxSimSeg);
                                                h2_RecdY_SimdY_20->Fill(dySegRec,dySimSeg);
                                                h2_RecdX_RecdY_20->Fill(dxSegRec,dySegRec);
                                                h2_SimdX_SimdY_20->Fill(dxSimSeg,dxSimSeg);
					} else if(std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4){
                                                h1_DeltaX_24->Fill(xSegRec - xsimSeg);
                                                h1_DeltaY_24->Fill(ySegRec - ysimSeg);
                                                h2_RecX_SimX_24->Fill( xSegRec, xsimSeg);
                                                h2_RecY_SimY_24->Fill( ySegRec, ysimSeg);
                                                h2_RecX_RecY_24->Fill( xSegRec, ySegRec);
                                                h2_SimX_SimY_24->Fill( xsimSeg, ysimSeg); 

                                                h1_DeltadX_24->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_24->Fill(dySegRec-dySimSeg);
                                                h2_RecdX_SimdX_24->Fill(dxSegRec,dxSimSeg);
                                                h2_RecdY_SimdY_24->Fill(dySegRec,dySimSeg);
                                                h2_RecdX_RecdY_24->Fill(dxSegRec,dySegRec);
                                                h2_SimdX_SimdY_24->Fill(dxSimSeg,dxSimSeg);
					}

				
					if( st==1 && rg==1 && std::abs(muon_eta)>1.6 && std::abs(muon_eta)<=2.0 ){

						if( zdir == 1 ){
      							h2_RecResdX_ErrdX_UpStation1_DirZ_1_CSC_St1_Rg1->Fill((dxSegRec-dxSimSeg),dxSegErr);
      							h2_RecResdY_ErrdY_UpStation1_DirZ_1_CSC_St1_Rg1->Fill((dySegRec-dySimSeg),dySegErr);
						} else if( zdir == -1 ){
							h2_RecResdX_ErrdX_UpStation1_DirZ_m1_CSC_St1_Rg1->Fill((dxSegRec-dxSimSeg),dxSegErr);
							h2_RecResdY_ErrdY_UpStation1_DirZ_m1_CSC_St1_Rg1->Fill((dySegRec-dySimSeg),dySegErr);
						}
                                               
					}	
					//Plot to study if there is some local bias in the position of the segments
					if( st==1 && rg==1 && std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){
						
						h1_RecX_CSC_St1_Rg1->Fill(xSegRec); h1_RecY_CSC_St1_Rg1->Fill(ySegRec);
						h1_RecResX_CSC_St1_Rg1->Fill((xSegRec-xsimSeg)/xSegErr);
						h1_RecResY_CSC_St1_Rg1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                h1_ErrX_CSC_St1_Rg1->Fill(xSegErr);
                                                h1_ErrY_CSC_St1_Rg1->Fill(ySegErr);

                                                h1_RecdX_CSC_St1_Rg1->Fill(dxSegRec); h1_RecdY_CSC_St1_Rg1->Fill(dySegRec);
                                                h1_RecResdX_CSC_St1_Rg1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St1_Rg1->Fill((dySegRec-dySimSeg)/dySegErr);

						h1_ErrdX_CSC_St1_Rg1->Fill(dxSegErr);
						h1_ErrdY_CSC_St1_Rg1->Fill(dySegErr);

                                                h2_RecResdX_ErrdX_CSC_St1_Rg1->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St1_Rg1->Fill((dySegRec-dySimSeg),dySegErr);

						h1_DeltaX_CSC_St1_Rg1->Fill(xSegRec-xsimSeg);
						h1_DeltaY_CSC_St1_Rg1->Fill(ySegRec-ysimSeg);

						h1_DeltadX_CSC_St1_Rg1->Fill(dxSegRec-dxSimSeg);
						h1_DeltadY_CSC_St1_Rg1->Fill(dySegRec-dySimSeg);

						if( zdir==1 ){ 
							if( (dxSegRec-dxSimSeg) < 0 ) { h2_SimX_SimY_DwStation1_DirZ_1_CSC_St1_Rg1->Fill(xSegRec, ySegRec);
											h2_RecX_RecY_DwStation1_DirZ_1_CSC_St1_Rg1->Fill(xsimSeg, ysimSeg); } 
      							h2_RecResdX_ErrdX_DwStation1_DirZ_1_CSC_St1_Rg1->Fill((dxSegRec-dxSimSeg),dxSegErr);
      							h2_RecResdY_ErrdY_DwStation1_DirZ_1_CSC_St1_Rg1->Fill((dySegRec-dySimSeg),dySegErr); 
						} else if( zdir == -1 ){
                                                        if( (dxSegRec-dxSimSeg) < 0 ) { h2_SimX_SimY_DwStation1_DirZ_m1_CSC_St1_Rg1->Fill(xSegRec, ySegRec);
                                                        				h2_RecX_RecY_DwStation1_DirZ_m1_CSC_St1_Rg1->Fill(xsimSeg, ysimSeg); }
							h2_RecResdX_ErrdX_DwStation1_DirZ_m1_CSC_St1_Rg1->Fill((dxSegRec-dxSimSeg),dxSegErr);
							h2_RecResdY_ErrdY_DwStation1_DirZ_m1_CSC_St1_Rg1->Fill((dySegRec-dySimSeg),dySegErr);
						}

						if( muon_p>(psim+psim/5) && std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){
							
							h1_RecX_CSC_PtCut_St1_Rg1->Fill(xSegRec); h1_RecY_CSC_PtCut_St1_Rg1->Fill(ySegRec);
							h1_RecResX_CSC_PtCut_St1_Rg1->Fill((xSegRec-xsimSeg)/xSegErr);
							h1_RecResY_CSC_PtCut_St1_Rg1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St1_Rg1->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St1_Rg1->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St1_Rg1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St1_Rg1->Fill((dySegRec-dySimSeg)/dySegErr);

							h1_ErrX_CSC_PtCut_St1_Rg1->Fill(xSegErr);
							h1_ErrY_CSC_PtCut_St1_Rg1->Fill(ySegErr);

							h1_ErrdX_CSC_PtCut_St1_Rg1->Fill(dxSegErr);
							h1_ErrdY_CSC_PtCut_St1_Rg1->Fill(dySegErr);
						}
					} else if( st==1 && rg==2 ){ 
						
						h1_RecX_CSC_St1_Rg2->Fill(xSegRec); h1_RecY_CSC_St1_Rg2->Fill(ySegRec);
                                                h1_RecResX_CSC_St1_Rg2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                h1_RecResY_CSC_St1_Rg2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                h1_ErrX_CSC_St1_Rg2->Fill(xSegErr);
                                                h1_ErrY_CSC_St1_Rg2->Fill(ySegErr);
 
                                                h1_RecdX_CSC_St1_Rg2->Fill(dxSegRec); h1_RecdY_CSC_St1_Rg2->Fill(dySegRec);
                                                h1_RecResdX_CSC_St1_Rg2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St1_Rg2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                h1_ErrdX_CSC_St1_Rg2->Fill(dxSegErr);
                                                h1_ErrdY_CSC_St1_Rg2->Fill(dySegErr);

                                                h2_RecResdX_ErrdX_CSC_St1_Rg2->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St1_Rg2->Fill((dySegRec-dySimSeg),dySegErr);

                                                h1_DeltaX_CSC_St1_Rg2->Fill(xSegRec-xsimSeg);
                                                h1_DeltaY_CSC_St1_Rg2->Fill(ySegRec-ysimSeg);

                                                h1_DeltadX_CSC_St1_Rg2->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St1_Rg2->Fill(dySegRec-dySimSeg);

						if( muon_p>(psim+psim/5) ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
							
							h1_RecX_CSC_PtCut_St1_Rg2->Fill(xSegRec); h1_RecY_CSC_PtCut_St1_Rg2->Fill(ySegRec);
                                                        h1_RecResX_CSC_PtCut_St1_Rg2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_RecResY_CSC_PtCut_St1_Rg2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St1_Rg2->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St1_Rg2->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St1_Rg2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St1_Rg2->Fill((dySegRec-dySimSeg)/dySegErr);
                                                 
						        h1_ErrX_CSC_PtCut_St1_Rg2->Fill(xSegErr);
                                                        h1_ErrY_CSC_PtCut_St1_Rg2->Fill(ySegErr);
                                                
                                                        h1_ErrdX_CSC_PtCut_St1_Rg2->Fill(dxSegErr);
                                                        h1_ErrdY_CSC_PtCut_St1_Rg2->Fill(dySegErr);

						}
					} else if( st==1 && rg==3 ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
						
						h1_RecX_CSC_St1_Rg3->Fill(xSegRec); h1_RecY_CSC_St1_Rg3->Fill(ySegRec);
                                                h1_RecResX_CSC_St1_Rg3->Fill((xSegRec-xsimSeg)/xSegErr);
                                                h1_RecResY_CSC_St1_Rg3->Fill((ySegRec-ysimSeg)/ySegErr);

                                                h1_ErrX_CSC_St1_Rg3->Fill(xSegErr);
                                                h1_ErrY_CSC_St1_Rg3->Fill(ySegErr); 

                                                h1_RecdX_CSC_St1_Rg3->Fill(dxSegRec); h1_RecY_CSC_St1_Rg3->Fill(dySegRec);
                                                h1_RecResdX_CSC_St1_Rg3->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St1_Rg3->Fill((dySegRec-dySimSeg)/dySegErr);

                                                h1_ErrdX_CSC_St1_Rg3->Fill(dxSegErr);
                                                h1_ErrdY_CSC_St1_Rg3->Fill(dySegErr);

                                                h2_RecResdX_ErrdX_CSC_St1_Rg3->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St1_Rg3->Fill((dySegRec-dySimSeg),dySegErr);

                                                h1_DeltaX_CSC_St1_Rg3->Fill(xSegRec-xsimSeg);
                                                h1_DeltaY_CSC_St1_Rg3->Fill(ySegRec-ysimSeg);

                                                h1_DeltadX_CSC_St1_Rg3->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St1_Rg3->Fill(dySegRec-dySimSeg);

						if( muon_p>(psim+psim/5) ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
							
							h1_RecX_CSC_PtCut_St1_Rg3->Fill(xSegRec); h1_RecY_CSC_PtCut_St1_Rg3->Fill(ySegRec);
                                                        h1_RecResX_CSC_PtCut_St1_Rg3->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_RecResY_CSC_PtCut_St1_Rg3->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St1_Rg3->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St1_Rg3->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St1_Rg3->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St1_Rg3->Fill((dySegRec-dySimSeg)/dySegErr);
                                                        
                                                        h1_ErrX_CSC_PtCut_St1_Rg3->Fill(xSegErr);
                                                        h1_ErrY_CSC_PtCut_St1_Rg3->Fill(ySegErr);
                                                
                                                        h1_ErrdX_CSC_PtCut_St1_Rg3->Fill(dxSegErr);
                                                        h1_ErrdY_CSC_PtCut_St1_Rg3->Fill(dySegErr);
						}
					} else if( st==2 && rg==1 && std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){
						
						h1_RecX_CSC_St2_Rg1->Fill(xSegRec); h1_RecY_CSC_St2_Rg1->Fill(ySegRec); 
                                                h1_RecResX_CSC_St2_Rg1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                h1_RecResY_CSC_St2_Rg1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                h1_ErrX_CSC_St2_Rg1->Fill(xSegErr);
                                                h1_ErrY_CSC_St2_Rg1->Fill(ySegErr);

                                                h1_RecdX_CSC_St2_Rg1->Fill(dxSegRec); h1_RecdY_CSC_St2_Rg1->Fill(dySegRec);
                                                h1_RecResdX_CSC_St2_Rg1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St2_Rg1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                h1_ErrdX_CSC_St2_Rg1->Fill(dxSegErr);
                                                h1_ErrdY_CSC_St2_Rg1->Fill(dySegErr);

                                                h2_RecResdX_ErrdX_CSC_St2_Rg1->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St2_Rg1->Fill((dySegRec-dySimSeg),dySegErr);

                                                h1_DeltaX_CSC_St2_Rg1->Fill(xSegRec-xsimSeg);
                                                h1_DeltaY_CSC_St2_Rg1->Fill(ySegRec-ysimSeg);

                                                h1_DeltadX_CSC_St2_Rg1->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St2_Rg1->Fill(dySegRec-dySimSeg);

						if( muon_p>(psim+psim/5) && std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){
							
							h1_RecX_CSC_PtCut_St2_Rg1->Fill(xSegRec); h1_RecY_CSC_PtCut_St2_Rg1->Fill(ySegRec); 
                                                        h1_RecResX_CSC_PtCut_St2_Rg1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_RecResY_CSC_PtCut_St2_Rg1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St2_Rg1->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St2_Rg1->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St2_Rg1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St2_Rg1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        
                                                        h1_ErrX_CSC_PtCut_St2_Rg1->Fill(xSegErr);
                                                        h1_ErrY_CSC_PtCut_St2_Rg1->Fill(ySegErr);
                                                
                                                        h1_ErrdX_CSC_PtCut_St2_Rg1->Fill(dxSegErr);
                                                        h1_ErrdY_CSC_PtCut_St2_Rg1->Fill(dySegErr);

						} 
					} else if( st==2 && rg==2 ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
						
						h1_RecX_CSC_St2_Rg2->Fill(xSegRec); h1_RecY_CSC_St2_Rg2->Fill(ySegRec);
                                                h1_RecResX_CSC_St2_Rg2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                h1_RecResY_CSC_St2_Rg2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                h1_ErrX_CSC_St2_Rg2->Fill(xSegErr);
                                                h1_ErrY_CSC_St2_Rg2->Fill(ySegErr);

                                                h1_RecdX_CSC_St2_Rg2->Fill(dxSegRec); h1_RecdY_CSC_St2_Rg2->Fill(dySegRec);
                                                h1_RecResdX_CSC_St2_Rg2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St2_Rg2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                h1_ErrdX_CSC_St2_Rg2->Fill(dxSegErr);
                                                h1_ErrdY_CSC_St2_Rg2->Fill(dySegErr); 

                                                h2_RecResdX_ErrdX_CSC_St2_Rg2->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St2_Rg2->Fill((dySegRec-dySimSeg),dySegErr);

                                                h1_DeltaX_CSC_St2_Rg2->Fill(xSegRec-xsimSeg);
                                                h1_DeltaY_CSC_St2_Rg2->Fill(ySegRec-ysimSeg);

                                                h1_DeltadX_CSC_St2_Rg2->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St2_Rg2->Fill(dySegRec-dySimSeg);

						if( muon_p>(psim+psim/5) ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
							h1_RecX_CSC_PtCut_St2_Rg2->Fill(xSegRec); h1_RecY_CSC_PtCut_St2_Rg2->Fill(ySegRec);
                                                        h1_RecResX_CSC_PtCut_St2_Rg2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_RecResY_CSC_PtCut_St2_Rg2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St2_Rg2->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St2_Rg2->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St2_Rg2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St2_Rg2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrX_CSC_PtCut_St2_Rg2->Fill(xSegErr);
                                                        h1_ErrY_CSC_PtCut_St2_Rg2->Fill(ySegErr);

                                                        h1_ErrdX_CSC_PtCut_St2_Rg2->Fill(dxSegErr);
                                                        h1_ErrdY_CSC_PtCut_St2_Rg2->Fill(dySegErr);
						}
					} else if( st==3 && rg==1 && std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){
						
						h1_RecX_CSC_St3_Rg1->Fill(xSegRec); h1_RecY_CSC_St3_Rg1->Fill(ySegRec);
                                                h1_RecResX_CSC_St3_Rg1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                h1_RecResY_CSC_St3_Rg1->Fill((ySegRec-ysimSeg)/ySegErr); 

                                                h1_ErrX_CSC_St3_Rg1->Fill(xSegErr);
                                                h1_ErrY_CSC_St3_Rg1->Fill(ySegErr);

                                                h1_RecdX_CSC_St3_Rg1->Fill(dxSegRec); h1_RecdY_CSC_St3_Rg1->Fill(dySegRec);
                                                h1_RecResdX_CSC_St3_Rg1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St3_Rg1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                h1_ErrdX_CSC_St3_Rg1->Fill(dxSegErr);
                                                h1_ErrdY_CSC_St3_Rg1->Fill(dySegErr);

                                                h2_RecResdX_ErrdX_CSC_St3_Rg1->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St3_Rg1->Fill((dySegRec-dySimSeg),dySegErr);

                                                h1_DeltaX_CSC_St3_Rg1->Fill(xSegRec-xsimSeg);
                                                h1_DeltaY_CSC_St3_Rg1->Fill(ySegRec-ysimSeg);

                                                h1_DeltadX_CSC_St3_Rg1->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St3_Rg1->Fill(dySegRec-dySimSeg);

						if( muon_p>(psim+psim/5) && std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
							h1_RecX_CSC_PtCut_St3_Rg1->Fill(xSegRec); h1_RecY_CSC_PtCut_St3_Rg1->Fill(ySegRec);
                                                        h1_RecResX_CSC_PtCut_St3_Rg1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_RecResY_CSC_PtCut_St3_Rg1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St3_Rg1->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St3_Rg1->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St3_Rg1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St3_Rg1->Fill((dySegRec-dySimSeg)/dySegErr);


                                                        h1_ErrX_CSC_PtCut_St3_Rg1->Fill(xSegErr);
                                                        h1_ErrY_CSC_PtCut_St3_Rg1->Fill(ySegErr);

                                                        h1_ErrdX_CSC_PtCut_St3_Rg1->Fill(dxSegErr);
                                                        h1_ErrdY_CSC_PtCut_St3_Rg1->Fill(dySegErr);
						}
					} else if( st==3 && rg==2 ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){
						
						h1_RecX_CSC_St3_Rg2->Fill(xSegRec); h1_RecY_CSC_St3_Rg2->Fill(ySegRec); 
                                                h1_RecResX_CSC_St3_Rg2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                h1_RecResY_CSC_St3_Rg2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                h1_ErrX_CSC_St3_Rg2->Fill(xSegErr);
                                                h1_ErrY_CSC_St3_Rg2->Fill(ySegErr);

                                                h1_RecdX_CSC_St3_Rg2->Fill(dxSegRec); h1_RecdY_CSC_St3_Rg2->Fill(dySegRec);
                                                h1_RecResdX_CSC_St3_Rg2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St3_Rg2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                h1_ErrdX_CSC_St3_Rg2->Fill(dxSegErr);
                                                h1_ErrdY_CSC_St3_Rg2->Fill(dySegErr);

                                                h2_RecResdX_ErrdX_CSC_St3_Rg2->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St3_Rg2->Fill((dySegRec-dySimSeg),dySegErr);

                                                h1_DeltaX_CSC_St3_Rg2->Fill(xSegRec-xsimSeg);
                                                h1_DeltaY_CSC_St3_Rg2->Fill(ySegRec-ysimSeg);

                                                h1_DeltadX_CSC_St3_Rg2->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St3_Rg2->Fill(dySegRec-dySimSeg);

						if( muon_p>(psim+psim/5) ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
							h1_RecX_CSC_PtCut_St3_Rg2->Fill(xSegRec); h1_RecY_CSC_PtCut_St3_Rg2->Fill(ySegRec);
                                                        h1_RecResX_CSC_PtCut_St3_Rg2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_RecResY_CSC_PtCut_St3_Rg2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St3_Rg2->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St3_Rg2->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St3_Rg2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St3_Rg2->Fill((dySegRec-dySimSeg)/dySegErr);


                                                        h1_ErrX_CSC_PtCut_St3_Rg2->Fill(xSegErr);
                                                        h1_ErrY_CSC_PtCut_St3_Rg2->Fill(ySegErr);

                                                        h1_ErrdX_CSC_PtCut_St3_Rg2->Fill(dxSegErr);
                                                        h1_ErrdY_CSC_PtCut_St3_Rg2->Fill(dySegErr);
						}
					} else if( st==4 && rg==1 && std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){
						
						h1_RecX_CSC_St4_Rg1->Fill(xSegRec); h1_RecY_CSC_St4_Rg1->Fill(ySegRec);
                                                h1_RecResX_CSC_St4_Rg1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                h1_RecResY_CSC_St4_Rg1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                h1_ErrX_CSC_St4_Rg1->Fill(xSegErr);
                                                h1_ErrY_CSC_St4_Rg1->Fill(ySegErr);

                                                h1_RecdX_CSC_St4_Rg1->Fill(dxSegRec); h1_RecdY_CSC_St4_Rg1->Fill(dySegRec);
                                                h1_RecResdX_CSC_St4_Rg1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St4_Rg1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                h1_ErrdX_CSC_St4_Rg1->Fill(dxSegErr);
                                                h1_ErrdY_CSC_St4_Rg1->Fill(dySegErr);

                                                h2_RecResdX_ErrdX_CSC_St4_Rg1->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St4_Rg1->Fill((dySegRec-dySimSeg),dySegErr);

                                                h1_DeltaX_CSC_St4_Rg1->Fill(xSegRec-xsimSeg);
                                                h1_DeltaY_CSC_St4_Rg1->Fill(ySegRec-ysimSeg);

                                                h1_DeltadX_CSC_St4_Rg1->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St4_Rg1->Fill(dySegRec-dySimSeg);
 
						if( muon_p>(psim+psim/5) && std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
							h1_RecX_CSC_PtCut_St4_Rg1->Fill(xSegRec); h1_RecY_CSC_PtCut_St4_Rg1->Fill(ySegRec);
                                                        h1_RecResX_CSC_PtCut_St4_Rg1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_RecResY_CSC_PtCut_St4_Rg1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St4_Rg1->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St4_Rg1->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St4_Rg1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St4_Rg1->Fill((dySegRec-dySimSeg)/dySegErr);


                                                        h1_ErrX_CSC_PtCut_St4_Rg1->Fill(xSegErr);
                                                        h1_ErrY_CSC_PtCut_St4_Rg1->Fill(ySegErr);

                                                        h1_ErrdX_CSC_PtCut_St4_Rg1->Fill(dxSegErr);
                                                        h1_ErrdY_CSC_PtCut_St4_Rg1->Fill(dySegErr);
						}
					} else if( st==4 && rg==2 ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){
						
						h1_RecX_CSC_St4_Rg2->Fill(xSegRec); h1_RecY_CSC_St4_Rg2->Fill(ySegRec);
                                                h1_RecResX_CSC_St4_Rg2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                h1_RecResY_CSC_St4_Rg2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                h1_ErrX_CSC_St4_Rg2->Fill(xSegErr);
                                                h1_ErrY_CSC_St4_Rg2->Fill(ySegErr);

                                                h1_RecdX_CSC_St4_Rg2->Fill(dxSegRec); h1_RecdY_CSC_St4_Rg2->Fill(dySegRec);
                                                h1_RecResdX_CSC_St4_Rg2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                h1_RecResdY_CSC_St4_Rg2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                h1_ErrdX_CSC_St4_Rg2->Fill(dxSegErr);
                                                h1_ErrdY_CSC_St4_Rg2->Fill(dySegErr); 

                                                h2_RecResdX_ErrdX_CSC_St4_Rg2->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                h2_RecResdY_ErrdY_CSC_St4_Rg2->Fill((dySegRec-dySimSeg),dySegErr);

                                                h1_DeltaX_CSC_St4_Rg2->Fill(xSegRec-xsimSeg);
                                                h1_DeltaY_CSC_St4_Rg2->Fill(ySegRec-ysimSeg);

                                                h1_DeltadX_CSC_St4_Rg2->Fill(dxSegRec-dxSimSeg);
                                                h1_DeltadY_CSC_St4_Rg2->Fill(dySegRec-dySimSeg);

						if( muon_p>(psim+psim/5) ){ //&& std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4 ){ 
							h1_RecX_CSC_PtCut_St4_Rg2->Fill(xSegRec); h1_RecY_CSC_PtCut_St4_Rg2->Fill(ySegRec);
                                                        h1_RecResX_CSC_PtCut_St4_Rg2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_RecResY_CSC_PtCut_St4_Rg2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_RecdX_CSC_PtCut_St4_Rg2->Fill(dxSegRec); h1_RecdY_CSC_PtCut_St4_Rg2->Fill(dySegRec);
                                                        h1_RecResdX_CSC_PtCut_St4_Rg2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_RecResdY_CSC_PtCut_St4_Rg2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrX_CSC_PtCut_St4_Rg2->Fill(xSegErr);
                                                        h1_ErrY_CSC_PtCut_St4_Rg2->Fill(ySegErr);

                                                        h1_ErrdX_CSC_PtCut_St4_Rg2->Fill(dxSegErr);
                                                        h1_ErrdY_CSC_PtCut_St4_Rg2->Fill(dySegErr);
						}
					}


				} //if( idCSCSeg == isCSCRec && (abs(xHitRec-xSegRec)/abs(xHitRec))<0.01 && (abs(yHitRec-ySegRec)/abs(ySegRec))<0.0)

				//Filling histo with all the segment in the chamber
                                if(std::abs(muon_eta)<=0.8){
                                    h1_all_DeltaX_08->Fill(xSegRec - xsimSeg);
                                    h1_all_DeltaY_08->Fill(ySegRec - ysimSeg);

                                    h1_all_DeltadX_08->Fill(dxSegRec-dxSimSeg);
                                    h1_all_DeltadY_08->Fill(dySegRec-dySimSeg);
                                } else if(std::abs(muon_eta)>0.8 && std::abs(muon_eta)<=1.2){
                                    h1_all_DeltaX_12->Fill(xSegRec - xsimSeg);
                                    h1_all_DeltaY_12->Fill(ySegRec - ysimSeg);

                                    h1_all_DeltadX_12->Fill(dxSegRec-dxSimSeg);
                                    h1_all_DeltadY_12->Fill(dySegRec-dySimSeg);
                                } else if(std::abs(muon_eta)>1.2 && std::abs(muon_eta)<=2.0){
                                    h1_all_DeltaX_20->Fill(xSegRec - xsimSeg);
                                    h1_all_DeltaY_20->Fill(ySegRec - ysimSeg);

                                    h1_all_DeltadX_20->Fill(dxSegRec-dxSimSeg);
                                    h1_all_DeltadY_20->Fill(dySegRec-dySimSeg);
                                } else if(std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4){
                                    h1_all_DeltaX_24->Fill(xSegRec - xsimSeg);
                                    h1_all_DeltaY_24->Fill(ySegRec - ysimSeg);

                                    h1_all_DeltadX_24->Fill(dxSegRec-dxSimSeg);
                                    h1_all_DeltadY_24->Fill(dySegRec-dySimSeg);
                                }

			      }//idCSCSeg == isCSCRec	
			    }//for(CSCSegmentCollection::const_iterator segIt=cscSegments->begin(); segIt != cscSegments->end(); segIt++)

                            if(std::abs(muon_eta)<=0.8){
                            	h1_all_Nseg_08->Fill(SegCounter);
                            } else if(std::abs(muon_eta)>0.8 && std::abs(muon_eta)<=1.2){
                                h1_all_Nseg_12->Fill(SegCounter);
                            } else if(std::abs(muon_eta)>1.2 && std::abs(muon_eta)<=2.0){
                                h1_all_Nseg_20->Fill(SegCounter);
                            } else if(std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4){
                                h1_all_Nseg_24->Fill(SegCounter);
                            }

			} else if( subDet==1 ){
				DTChamberId isDTRec(id);
				int dtStation = isDTRec.station();
				int st = isDTRec.station();
				int wh = isDTRec.wheel();
				int SegCounter = 0;
				//Loop on DTSegment	
                                for(DTRecSegment4DCollection::const_iterator segIt=dtSegments->begin(); segIt != dtSegments->end(); segIt++){
                                        DTChamberId idDTSeg = (DTChamberId)(*segIt).chamberId();	
					AlgebraicVector posSegInfo = (*segIt).parameters();
					AlgebraicSymMatrix  posSegErr = (*segIt).parametersError();	
					LocalPoint InitSegPoint; LocalPoint FinSegPoint; 
                                        float  xSegRec = posSegInfo[2]; float  ySegRec = posSegInfo[3];
                                        float dxSegRec = posSegInfo[0]; float dySegRec = posSegInfo[1];
					float  xSegErr = std::sqrt(posSegErr(3,3)); float  ySegErr = std::sqrt(posSegErr(4,4));
					float dxSegErr = std::sqrt(posSegErr(1,1)); float dySegErr = std::sqrt(posSegErr(2,2));	
					bool hitMatch(false);
                                        int hitMatchedCounter = 0;
				   if( idDTSeg == isDTRec ){
					SegCounter++;
					//Definition of the 
                                        float  xsimSeg = 0; float  ysimSeg = 0;
                                        float dxSimSeg = 0; float dySimSeg = 0;	
					
					//Match between Seg and recHit using DetId and LocalPosition
                                        if(idDTSeg == isDTRec && (abs(xHitRec-xSegRec)/abs(xHitRec))<0.01 && (abs(yHitRec-ySegRec)/abs(ySegRec))<0.01){
						//Variable used to identify and reconstruct the Sim Segment.	
						float absMin = 1E11; float absMax = 0;	 	
						//Loop on recHits of the Segment are the SL                    
                                        	for(unsigned int hitSeg=0; hitSeg<(*segIt).recHits().size(); hitSeg++){
                                                	auto segHit = (*segIt).recHits().at(hitSeg);
							DTChamberId recHitChId(segHit->geographicalId());	
							DTLayerId  recHitLyId(segHit->geographicalId());
							DTSuperLayerId recHitSLyId(segHit->geographicalId());	 	
							for( unsigned int hitSL=0; hitSL<segHit->recHits().size(); hitSL++){	
								const DTRecHit1D* lHit = dynamic_cast<const DTRecHit1D*>(segHit->recHits().at(hitSL));
								DTWireId wireId = lHit->wireId();
								DTLayerId layerId = wireId.layerId();
								DTSuperLayerId slayerId = layerId.superlayerId();
								DTChamberId chamberId = slayerId.chamberId();

                                                                LocalPoint  hitSLlocalLy     = lHit->localPosition();
                                                                const DTLayer* dtSLlayer     = dtGeom->layer( layerId ); 
                                                                GlobalPoint shitSLGlobalLy   = dtSLlayer->toGlobal( hitSLlocalLy );
                                                                const DTChamber* dtSLchamber = dtGeom->chamber( chamberId ); 
                                                                LocalPoint  shitSLlocalCh    = dtSLchamber->toLocal( shitSLGlobalLy );

								int counterSimHit=0; 
								float xhitSl = shitSLlocalCh.x(); float yhitSl = shitSLlocalCh.y(); 
                                                		for( unsigned int dth=0; dth<simDTHits->size(); dth++){
									auto simDTHit = simDTHits->at(dth);
                                                        		DTChamberId simHitChId(simDTHit.detUnitId());
									DTLayerId  simHitLyId(simDTHit.detUnitId());
									DTSuperLayerId simHitSLyId(simDTHit.detUnitId());
									DTWireId simHitWrId(simDTHit.detUnitId());	

                                                                        LocalPoint simHitlocalLy       = simDTHit.localPosition();
                                                                        const DTLayer* dtSimlayer      = dtGeom->layer( simHitLyId );
                                                                        GlobalPoint shitSimGlobalLy    = dtSimlayer->toGlobal(simHitlocalLy);
                                                                        const DTChamber* dtSimchamber  = dtGeom->chamber(simHitChId);
                                                                        LocalPoint shitSimlocalCh      = dtSimchamber->toLocal(shitSimGlobalLy);
                                                                        float xsim = shitSimlocalCh.x(); float ysim = shitSimlocalCh.y(); 
									//if( wireId == simHitWrId  && layerId == simHitLyId && slayerId == simHitSLyId && chamberId == simHitChId && abs(simDTHits->at(dth).particleType()) == 13 && (abs(xhitSl-xsim)/abs(xhitSl)) < 0.05 && (abs(yhitSl - ysim)/abs(yhitSl)) < 0.05 ){	
									if( layerId == simHitLyId && slayerId == simHitSLyId && chamberId == simHitChId && abs(simDTHits->at(dth).particleType()) == 13 ){
                                                                			
                                                                                float TrjEnergy = std::sqrt( std::pow(mass,2) + std::pow(trajParams.at(h).momentum().mag(),2));
                                                                                float SimEnergy = std::sqrt( std::pow(mass,2) + std::pow(simDTHits->at(dth).pabs(),2));
										counterSimHit++;
										//std::cout << " " << std::endl;	
										//std::cout << "##################" << std::endl;
										//std::cout << "Sim Hit DT Chamber" << std::endl;
										//std::cout << "##################" << std::endl;	
										//std::cout << " " << std::endl;
										//std::cout << "DT ==> Wheel " << simHitChId.wheel() << " Station " << simHitChId.station() << " Sector " << simHitChId.sector() << " SyperLayer " << simHitSLyId.superLayer() << " Layer " << simHitLyId.layer() << " Wire " << simHitWrId.wire() << " X Local " << xsim << " Y Local " << ysim << " Energy " << SimEnergy <<  std::endl;

										if( SimEnergy < 1 ) continue;
										if( counterSimHit > 1 ) continue; 
										hitMatch =  true; hitMatchedCounter++;	
										//Find the boudaries on the collected hit to reconstruct an homemade segment
										float tmpAbs = shitSimGlobalLy.mag();	
										if( tmpAbs < absMin ){
											absMin = tmpAbs;
											InitSegPoint = shitSimlocalCh;	
										}
										if( tmpAbs > absMax ){
											absMax = tmpAbs;
											FinSegPoint = shitSimlocalCh;	
										}
	 
										//Energy Loss By Station
                                                        			if(dtStation==1){
                                                                			double ElossReco_DT_St1 = psim - TrjEnergy;
                                                                			double ElossSim_DT_St1  = psim - SimEnergy;
                                                                			h1_DeltaESim_DT_St1->Fill(ElossSim_DT_St1);
                                                                			h1_DeltaERec_DT_St1->Fill(ElossReco_DT_St1);
                                                                			h2_DeltaSim_DeltaRec_DT_St1->Fill(ElossReco_DT_St1,ElossSim_DT_St1);
                                                        			} else if(dtStation==2){
                                                                			double ElossReco_DT_St2 = psim - TrjEnergy;
                                                                			double ElossSim_DT_St2  = psim - SimEnergy;
                                                               				h1_DeltaESim_DT_St2->Fill(ElossSim_DT_St2);
                                                            		    		h1_DeltaERec_DT_St2->Fill(ElossReco_DT_St2);
                                                                			h2_DeltaSim_DeltaRec_DT_St2->Fill(ElossReco_DT_St2,ElossSim_DT_St2);
                                                       				} else if(dtStation==3){
                                                                			double ElossReco_DT_St3 = psim - TrjEnergy;
                                                                			double ElossSim_DT_St3  = psim - SimEnergy;
                                                                			h1_DeltaESim_DT_St3->Fill(ElossSim_DT_St3);
                                                                			h1_DeltaERec_DT_St3->Fill(ElossReco_DT_St3);
                                                                			h2_DeltaSim_DeltaRec_DT_St3->Fill(ElossReco_DT_St3,ElossSim_DT_St3);
                                                        			} else if(dtStation==4){ 
                                                                			double ElossReco_DT_St4 = psim - TrjEnergy;
                                                                			double ElossSim_DT_St4  = psim - SimEnergy;
                                                                			h1_DeltaESim_DT_St4->Fill(ElossSim_DT_St4);
                                                                			h1_DeltaERec_DT_St4->Fill(ElossReco_DT_St4);
                                                                			h2_DeltaSim_DeltaRec_DT_St4->Fill(ElossReco_DT_St4,ElossSim_DT_St4);
										}
 
										//Energy Loss By Eta
                                                      		  		if(std::abs(muon_eta)<=0.8){
                                                               		 		double ElossReco_DT_08 = psim - TrjEnergy;
                                                               	 			double ElossSim_DT_08  = psim - SimEnergy;
                                                                			h1_DeltaESim_08->Fill(ElossSim_DT_08);
                                                                			h1_DeltaERec_08->Fill(ElossReco_DT_08);
                                                                			h2_DeltaSim_DeltaRec_08->Fill(ElossReco_DT_08,ElossSim_DT_08);
                                                        			} else if(std::abs(muon_eta)>0.8 && std::abs(muon_eta)<=1.2){
                                                                			double ElossReco_DT_12 = psim - TrjEnergy;
                                                                			double ElossSim_DT_12  = psim - SimEnergy;
                                                                			h1_DeltaESim_12->Fill(ElossSim_DT_12);
                                                               				h1_DeltaERec_12->Fill(ElossReco_DT_12);
                                                                			h2_DeltaSim_DeltaRec_12->Fill(ElossReco_DT_12,ElossSim_DT_12);
                                                        			} else if(std::abs(muon_eta)>1.2 && std::abs(muon_eta)<=2.0){
                                                                			double ElossReco_DT_20 = psim - TrjEnergy;
                                                                			double ElossSim_DT_20  = psim - SimEnergy;
                                                                			h1_DeltaESim_20->Fill(ElossSim_DT_20);
                                                                			h1_DeltaERec_20->Fill(ElossReco_DT_20);
                                                                			h2_DeltaSim_DeltaRec_20->Fill(ElossReco_DT_20,ElossSim_DT_20);
                                                       				} else if(std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4){
                                                                			double ElossReco_DT_24 = psim - TrjEnergy;
                                                                			double ElossSim_DT_24  = psim - SimEnergy;
                                                                			h1_DeltaESim_24->Fill(ElossSim_DT_24);
                                                                			h1_DeltaERec_24->Fill(ElossReco_DT_24);
                                                                			h2_DeltaSim_DeltaRec_24->Fill(ElossReco_DT_24,ElossSim_DT_24);	
										}
									}//if(segHitId == simWireId && abs(simDTHits->at(dth).particleType()) == 13
								}//for( unsigned int dth=0; dth<simDTHits->size(); dth++)		
								//}				
							}//for( unsigned int hitSL=0; hitSL<segHit->recHits().size(); hitSL++)
                             			}//for(unsigned int hitSeg=0; hitSeg<(*segIt).specificRecHits().size(); hitSeg++)	

                                        	if( hitMatch == false) continue;
                                        	if( hitMatchedCounter < 2 ) continue;

						//Mean Position of Sim Segment
                                                LocalPoint MeanPosition = meanPoint(InitSegPoint,FinSegPoint);
                                        	if( MeanPosition.z() == -1E10 && MeanPosition.x() == -1E10 && MeanPosition.y() == -1E10 ){
                                               		xsimSeg = xSegRec;
                                                	ysimSeg = ySegRec;
                                        	} else {
                                                	xsimSeg = MeanPosition.x();
                                                	ysimSeg = MeanPosition.y();
                                        	} 
						//Direction of the SimSegment
						dxSimSeg = (InitSegPoint.x()-FinSegPoint.x())/(InitSegPoint.z()-FinSegPoint.z());
						dySimSeg = (InitSegPoint.y()-FinSegPoint.y())/(InitSegPoint.z()-FinSegPoint.z());
					
						//Filling Segment Position by Station	
	                                        if(dtStation==1){
        	                                         h1_DeltaX_DT_St1->Fill(xSegRec - xsimSeg);
               		                                 h1_DeltaY_DT_St1->Fill(ySegRec - ysimSeg);
               		                                 h2_RecX_SimX_DT_St1->Fill( xSegRec, xsimSeg);
                        	                         h2_RecY_SimY_DT_St1->Fill( ySegRec, ysimSeg);
							 h2_RecX_RecY_DT_St1->Fill( xSegRec, ySegRec);
							 h2_SimX_SimY_DT_St1->Fill( xsimSeg, ysimSeg);

 	                                                 h1_DeltadX_DT_St1->Fill(dxSegRec-dxSimSeg);
         	                                         h1_DeltadY_DT_St1->Fill(dySegRec-dySimSeg);
                	                                 h2_RecdX_SimdX_DT_St1->Fill(dxSegRec,dxSimSeg);
                        	                         h2_RecdY_SimdY_DT_St1->Fill(dySegRec,dySimSeg);
                                                	 h2_RecdX_RecdY_DT_St1->Fill(dxSegRec,dySegRec);
                                                	 h2_SimdX_SimdY_DT_St1->Fill(dxSimSeg,dySimSeg); 
                        	                 } else if(dtStation==2){
                               		                 h1_DeltaX_DT_St2->Fill(xSegRec - xsimSeg);
                                       		         h1_DeltaY_DT_St2->Fill(ySegRec - ysimSeg);
                                                         h2_RecX_SimX_DT_St2->Fill( xSegRec, xsimSeg);
                                                         h2_RecY_SimY_DT_St2->Fill( ySegRec, ysimSeg);
                                                         h2_RecX_RecY_DT_St2->Fill( xSegRec, ySegRec);
                                                         h2_SimX_SimY_DT_St2->Fill( xsimSeg, ysimSeg); 

                                                         h1_DeltadX_DT_St2->Fill(dxSegRec-dxSimSeg);
                                                         h1_DeltadY_DT_St2->Fill(dySegRec-dySimSeg);
                                                         h2_RecdX_SimdX_DT_St2->Fill(dxSegRec,dxSimSeg);
                                                         h2_RecdY_SimdY_DT_St2->Fill(dySegRec,dySimSeg);
                                                         h2_RecdX_RecdY_DT_St2->Fill(dxSegRec,dySegRec);
                                                         h2_SimdX_SimdY_DT_St2->Fill(dxSimSeg,dySimSeg); 
                                        	 } else if(dtStation==3){
                                                	 h1_DeltaX_DT_St3->Fill(xSegRec - xsimSeg);
                                                	 h1_DeltaY_DT_St3->Fill(ySegRec - ysimSeg);
                                                         h2_RecX_SimX_DT_St3->Fill( xSegRec, xsimSeg);
                                                         h2_RecY_SimY_DT_St3->Fill( ySegRec, ysimSeg);
                                                         h2_RecX_RecY_DT_St3->Fill( xSegRec, ySegRec);
                                                         h2_SimX_SimY_DT_St3->Fill( xsimSeg, ysimSeg);	 
                                                	 
							 h1_DeltadX_DT_St3->Fill(dxSegRec-dxSimSeg);
                                                         h1_DeltadY_DT_St3->Fill(dySegRec-dySimSeg);
                                                         h2_RecdX_SimdX_DT_St3->Fill(dxSegRec,dxSimSeg);
                                                         h2_RecdY_SimdY_DT_St3->Fill(dySegRec,dySimSeg);      
                                                         h2_RecdX_RecdY_DT_St3->Fill(dxSegRec,dySegRec);
                                                         h2_SimdX_SimdY_DT_St3->Fill(dxSimSeg,dySimSeg); 
                                       	 	 } else if(dtStation==4){
                                                	 h1_DeltaX_DT_St4->Fill(xSegRec - xsimSeg);
                                                	 h1_DeltaY_DT_St4->Fill(ySegRec - ysimSeg);
                                                         h2_RecX_SimX_DT_St4->Fill( xSegRec, xsimSeg);
                                                         h2_RecY_SimY_DT_St4->Fill( ySegRec, ysimSeg);
                                                         h2_RecX_RecY_DT_St4->Fill( xSegRec, ySegRec);
                                                         h2_SimX_SimY_DT_St4->Fill( xsimSeg, ysimSeg);	

                                                         h1_DeltadX_DT_St4->Fill(dxSegRec-dxSimSeg);
                                                         h1_DeltadY_DT_St4->Fill(dySegRec-dySimSeg);
                                                         h2_RecdX_SimdX_DT_St4->Fill(dxSegRec,dxSimSeg);
                                                         h2_RecdY_SimdY_DT_St4->Fill(dySegRec,dySimSeg); 
                                                         h2_RecdX_RecdY_DT_St4->Fill(dxSegRec,dySegRec);
                                                         h2_SimdX_SimdY_DT_St4->Fill(dxSimSeg,dySimSeg);
                                        	 }

						 //Filling Segment Position by Eta
                                        	 if(std::abs(muon_eta)<=0.8){
                                                   	 h1_DeltaX_08->Fill(xSegRec - xsimSeg);
                                        	         h1_DeltaY_08->Fill(ySegRec - ysimSeg);	
	                                                 h2_RecX_SimX_08->Fill( xSegRec, xsimSeg);
        	                                         h2_RecY_SimY_08->Fill( ySegRec, ysimSeg);
                	                                 h2_RecX_RecY_08->Fill( xSegRec, ySegRec);
                        	                         h2_SimX_SimY_08->Fill( xsimSeg, ysimSeg);

                                                         h1_DeltadX_08->Fill(dxSegRec-dxSimSeg);
                                                         h1_DeltadY_08->Fill(dySegRec-dySimSeg);
                                                         h2_RecdX_SimdX_08->Fill(dxSegRec,dxSimSeg);
                                                         h2_RecdY_SimdY_08->Fill(dySegRec,dySimSeg);
                                                	 h2_RecdX_RecdY_08->Fill(dxSegRec,dySegRec);
                                                 	 h2_SimdX_SimdY_08->Fill(dxSimSeg,dxSimSeg);
                                         	 } else if(std::abs(muon_eta)>0.8 && std::abs(muon_eta)<=1.2){
                                                	 h1_DeltaX_12->Fill(xSegRec - xsimSeg);
                                                	 h1_DeltaY_12->Fill(ySegRec - ysimSeg);
                                                	 h2_RecX_SimX_12->Fill( xSegRec, xsimSeg);
                                                	 h2_RecY_SimY_12->Fill( ySegRec, ysimSeg);
                                                	 h2_RecX_RecY_12->Fill( xSegRec, ySegRec);
                                                	 h2_SimX_SimY_12->Fill( xsimSeg, ysimSeg);

                                                         h1_DeltadX_12->Fill(dxSegRec-dxSimSeg);
                                                         h1_DeltadY_12->Fill(dySegRec-dySimSeg);
                                                         h2_RecdX_SimdX_12->Fill(dxSegRec,dxSimSeg);
                                                         h2_RecdY_SimdY_12->Fill(dySegRec,dySimSeg);
                                                         h2_RecdX_RecdY_12->Fill(dxSegRec,dySegRec);
                                                         h2_SimdX_SimdY_12->Fill(dxSimSeg,dxSimSeg);
                                        	 } else if(std::abs(muon_eta)>1.2 && std::abs(muon_eta)<=2.0){
                                                	 h1_DeltaX_20->Fill(xSegRec - xsimSeg);
                                                	 h1_DeltaY_20->Fill(ySegRec - ysimSeg);
                                                	 h2_RecX_SimX_20->Fill( xSegRec, xsimSeg);
                                                	 h2_RecY_SimY_20->Fill( ySegRec, ysimSeg);
                                                	 h2_RecX_RecY_20->Fill( xSegRec, ySegRec);
                                                	 h2_SimX_SimY_20->Fill( xsimSeg, ysimSeg);	

                                                         h1_DeltadX_20->Fill(dxSegRec-dxSimSeg);
                                                         h1_DeltadY_20->Fill(dySegRec-dySimSeg);
                                                         h2_RecdX_SimdX_20->Fill(dxSegRec,dxSimSeg);
                                                         h2_RecdY_SimdY_20->Fill(dySegRec,dySimSeg);
                                                         h2_RecdX_RecdY_20->Fill(dxSegRec,dySegRec);
                                                         h2_SimdX_SimdY_20->Fill(dxSimSeg,dxSimSeg);
                                       		 } else if(std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4){
                                               		 h1_DeltaX_24->Fill(xSegRec - xsimSeg);
                                                	 h1_DeltaY_24->Fill(ySegRec - ysimSeg);
                                                	 h2_RecX_SimX_24->Fill( xSegRec, xsimSeg);
                                                	 h2_RecY_SimY_24->Fill( ySegRec, ysimSeg);
                                                	 h2_RecX_RecY_24->Fill( xSegRec, ySegRec);
                                                	 h2_SimX_SimY_24->Fill( xsimSeg, ysimSeg);

                                                         h1_DeltadX_24->Fill(dxSegRec-dxSimSeg);
                                                         h1_DeltadY_24->Fill(dySegRec-dySimSeg);
                                                         h2_RecdX_SimdX_24->Fill(dxSegRec,dxSimSeg);
                                                         h2_RecdY_SimdY_24->Fill(dySegRec,dySimSeg);
                                                         h2_RecdX_RecdY_24->Fill(dxSegRec,dySegRec);
                                                         h2_SimdX_SimdY_24->Fill(dxSimSeg,dxSimSeg);
                                        	 }

						 
						 //Plot to find if there is a bias in the DT chamber
						if( st==1 && std::abs(wh)==0 ){
							
							h1_RecX_DT_St1_Wh0->Fill(xSegRec); h1_RecY_DT_St1_Wh0->Fill(ySegRec);
							h1_ResRecX_DT_St1_Wh0->Fill((xSegRec-xsimSeg)/xSegErr);
							h1_ResRecY_DT_St1_Wh0->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St1_Wh0->Fill(xSegErr);
                                                        h1_ErrY_DT_St1_Wh0->Fill(ySegErr);

                                                        h1_RecdX_DT_St1_Wh0->Fill(dxSegRec); h1_RecdY_DT_St1_Wh0->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St1_Wh0->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St1_Wh0->Fill((dySegRec-dySimSeg)/dySegErr);

							h1_ErrdX_DT_St1_Wh0->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St1_Wh0->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St1_Wh0->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St1_Wh0->Fill((dySegRec-dySimSeg),dySegErr);

							h1_DeltaX_DT_St1_Wh0->Fill(xSegRec-xsimSeg);
							h1_DeltaY_DT_St1_Wh0->Fill(ySegRec-ysimSeg);

							h1_DeltadX_DT_St1_Wh0->Fill(dxSegRec-dxSimSeg);
							h1_DeltadY_DT_St1_Wh0->Fill(dySegRec-dySimSeg);

							if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St1_Wh0->Fill(xSegRec); h1_RecY_DT_PtCut_St1_Wh0->Fill(ySegRec);
								h1_ResRecX_DT_PtCut_St1_Wh0->Fill((xSegRec-xsimSeg)/xSegErr);
								h1_ResRecY_DT_PtCut_St1_Wh0->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St1_Wh0->Fill(dxSegRec); h1_RecdY_DT_PtCut_St1_Wh0->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St1_Wh0->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St1_Wh0->Fill((dySegRec-dySimSeg)/dySegErr);

								h1_ErrX_DT_PtCut_St1_Wh0->Fill(xSegErr);
								h1_ErrY_DT_PtCut_St1_Wh0->Fill(ySegErr);

								h1_ErrdX_DT_PtCut_St1_Wh0->Fill(dxSegErr);
								h1_ErrdY_DT_PtCut_St1_Wh0->Fill(dySegErr);

							}
						} else if( st==1 && std::abs(wh)==1 ){	
							
                                                        h1_RecX_DT_St1_Wh1->Fill(xSegRec); h1_RecY_DT_St1_Wh1->Fill(ySegRec);
                                                        h1_ResRecX_DT_St1_Wh1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St1_Wh1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St1_Wh1->Fill(xSegErr);
                                                        h1_ErrY_DT_St1_Wh1->Fill(ySegErr);

                                                        h1_RecdX_DT_St1_Wh1->Fill(dxSegRec); h1_RecdY_DT_St1_Wh1->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St1_Wh1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St1_Wh1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St1_Wh1->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St1_Wh1->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St1_Wh1->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St1_Wh1->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St1_Wh1->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St1_Wh1->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St1_Wh1->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St1_Wh1->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St1_Wh1->Fill(xSegRec); h1_RecY_DT_PtCut_St1_Wh1->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St1_Wh1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St1_Wh1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St1_Wh1->Fill(dxSegRec); h1_RecdY_DT_PtCut_St1_Wh1->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St1_Wh1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St1_Wh1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St1_Wh1->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St1_Wh1->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St1_Wh1->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St1_Wh1->Fill(dySegErr);
							}
                                                } else if( st==1 && std::abs(wh)==2 ){
							
                                                        h1_RecX_DT_St1_Wh2->Fill(xSegRec); h1_RecY_DT_St1_Wh2->Fill(ySegRec);
                                                        h1_ResRecX_DT_St1_Wh2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St1_Wh2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St1_Wh2->Fill(xSegErr);
                                                        h1_ErrY_DT_St1_Wh2->Fill(ySegErr);

                                                        h1_RecdX_DT_St1_Wh2->Fill(dxSegRec); h1_RecdY_DT_St1_Wh2->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St1_Wh2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St1_Wh2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St1_Wh2->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St1_Wh2->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St1_Wh2->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St1_Wh2->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St1_Wh2->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St1_Wh2->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St1_Wh2->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St1_Wh2->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St1_Wh2->Fill(xSegRec); h1_RecY_DT_PtCut_St1_Wh2->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St1_Wh2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St1_Wh2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St1_Wh2->Fill(dxSegRec); h1_RecdY_DT_PtCut_St1_Wh2->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St1_Wh2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St1_Wh2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St1_Wh2->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St1_Wh2->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St1_Wh2->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St1_Wh2->Fill(dySegErr);

							}
                                                } else if( st==2 && std::abs(wh)==0 ){
							
                                                        h1_RecX_DT_St2_Wh0->Fill(xSegRec); h1_RecY_DT_St2_Wh0->Fill(ySegRec);
                                                        h1_ResRecX_DT_St2_Wh0->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St2_Wh0->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St2_Wh0->Fill(xSegErr);
                                                        h1_ErrY_DT_St2_Wh0->Fill(ySegErr);

                                                        h1_RecdX_DT_St2_Wh0->Fill(dxSegRec); h1_RecdY_DT_St2_Wh0->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St2_Wh0->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St2_Wh0->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St2_Wh0->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St2_Wh0->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St2_Wh0->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St2_Wh0->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St2_Wh0->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St2_Wh0->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St2_Wh0->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St2_Wh0->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St2_Wh0->Fill(xSegRec); h1_RecY_DT_PtCut_St2_Wh0->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St2_Wh0->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St2_Wh0->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St2_Wh0->Fill(dxSegRec); h1_RecdY_DT_PtCut_St2_Wh0->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St2_Wh0->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St2_Wh0->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St2_Wh0->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St2_Wh0->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St2_Wh0->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St2_Wh0->Fill(dySegErr);
							}
                                                } else if( st==2 && std::abs(wh)==1 ){
							
                                                        h1_RecX_DT_St2_Wh1->Fill(xSegRec); h1_RecY_DT_St2_Wh1->Fill(ySegRec);
                                                        h1_ResRecX_DT_St2_Wh1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St2_Wh1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St2_Wh1->Fill(xSegErr);
                                                        h1_ErrY_DT_St2_Wh1->Fill(ySegErr);

                                                        h1_RecdX_DT_St2_Wh1->Fill(dxSegRec); h1_RecdY_DT_St2_Wh1->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St2_Wh1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St2_Wh1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St2_Wh1->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St2_Wh1->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St2_Wh1->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St2_Wh1->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St2_Wh1->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St2_Wh1->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St2_Wh1->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St2_Wh1->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St2_Wh1->Fill(xSegRec); h1_RecY_DT_PtCut_St2_Wh1->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St2_Wh1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St2_Wh1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St2_Wh1->Fill(dxSegRec); h1_RecdY_DT_PtCut_St2_Wh1->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St2_Wh1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St2_Wh1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St2_Wh1->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St2_Wh1->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St2_Wh1->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St2_Wh1->Fill(dySegErr);
							}
                                                } else if( st==2 && std::abs(wh)==2 ){	
							
                                                        h1_RecX_DT_St2_Wh2->Fill(xSegRec); h1_RecY_DT_St2_Wh2->Fill(ySegRec);
                                                        h1_ResRecX_DT_St2_Wh2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St2_Wh2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St2_Wh2->Fill(xSegErr);
                                                        h1_ErrY_DT_St2_Wh2->Fill(ySegErr);

                                                        h1_RecdX_DT_St2_Wh2->Fill(dxSegRec); h1_RecdY_DT_St2_Wh2->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St2_Wh2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St2_Wh2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St2_Wh2->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St2_Wh2->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St2_Wh2->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St2_Wh2->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St2_Wh2->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St2_Wh2->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St2_Wh2->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St2_Wh2->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St2_Wh2->Fill(xSegRec); h1_RecY_DT_PtCut_St2_Wh2->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St2_Wh2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St2_Wh2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St2_Wh2->Fill(dxSegRec); h1_RecdY_DT_PtCut_St2_Wh2->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St2_Wh2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St2_Wh2->Fill((dySegRec-dySimSeg)/dySegErr);


                                                                h1_ErrX_DT_PtCut_St2_Wh2->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St2_Wh2->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St2_Wh2->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St2_Wh2->Fill(dySegErr);
							}
                                                } else if( st==3 && std::abs(wh)==0 ){	
							
                                                        h1_RecX_DT_St3_Wh0->Fill(xSegRec); h1_RecY_DT_St3_Wh0->Fill(ySegRec);
                                                        h1_ResRecX_DT_St3_Wh0->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St3_Wh0->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St3_Wh0->Fill(xSegErr);
                                                        h1_ErrY_DT_St3_Wh0->Fill(ySegErr);

                                                        h1_RecdX_DT_St3_Wh0->Fill(dxSegRec); h1_RecdY_DT_St3_Wh0->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St3_Wh0->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St3_Wh0->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St3_Wh0->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St3_Wh0->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St3_Wh0->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St3_Wh0->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St3_Wh0->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St3_Wh0->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St3_Wh0->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St3_Wh0->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St3_Wh0->Fill(xSegRec); h1_RecY_DT_PtCut_St3_Wh0->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St3_Wh0->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St3_Wh0->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St3_Wh0->Fill(dxSegRec); h1_RecdY_DT_PtCut_St3_Wh0->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St3_Wh0->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St3_Wh0->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St3_Wh0->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St3_Wh0->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St3_Wh0->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St3_Wh0->Fill(dySegErr);
							}
                                                } else if( st==3 && std::abs(wh)==1 ){
							
                                                        h1_RecX_DT_St3_Wh1->Fill(xSegRec); h1_RecY_DT_St3_Wh1->Fill(ySegRec);
                                                        h1_ResRecX_DT_St3_Wh1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St3_Wh1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St3_Wh1->Fill(xSegErr);
                                                        h1_ErrY_DT_St3_Wh1->Fill(ySegErr);

                                                        h1_RecdX_DT_St3_Wh1->Fill(dxSegRec); h1_RecdY_DT_St3_Wh1->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St3_Wh1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St3_Wh1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St3_Wh1->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St3_Wh1->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St3_Wh1->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St3_Wh1->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St3_Wh1->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St3_Wh1->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St3_Wh1->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St3_Wh1->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St3_Wh1->Fill(xSegRec); h1_RecY_DT_PtCut_St3_Wh1->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St3_Wh1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St3_Wh1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St3_Wh1->Fill(dxSegRec); h1_RecdY_DT_PtCut_St3_Wh1->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St3_Wh1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St3_Wh1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St3_Wh1->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St3_Wh1->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St3_Wh1->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St3_Wh1->Fill(dySegErr);
							}
                                                } else if( st==3 && std::abs(wh)==2 ){
							
                                                        h1_RecX_DT_St3_Wh2->Fill(xSegRec); h1_RecY_DT_St3_Wh2->Fill(ySegRec);
                                                        h1_ResRecX_DT_St3_Wh2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St3_Wh2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St3_Wh2->Fill(xSegErr);
                                                        h1_ErrY_DT_St3_Wh2->Fill(ySegErr);

                                                        h1_RecdX_DT_St3_Wh2->Fill(dxSegRec); h1_RecdY_DT_St3_Wh2->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St3_Wh2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St3_Wh2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St3_Wh2->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St3_Wh2->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St3_Wh2->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St3_Wh2->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St3_Wh2->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St3_Wh2->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St3_Wh2->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St3_Wh2->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St3_Wh2->Fill(xSegRec); h1_RecY_DT_PtCut_St3_Wh2->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St3_Wh2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St3_Wh2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St3_Wh2->Fill(dxSegRec); h1_RecdY_DT_PtCut_St3_Wh2->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St3_Wh2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St3_Wh2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St3_Wh2->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St3_Wh2->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St3_Wh2->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St3_Wh2->Fill(dySegErr);
							}
						} else if( st==4 && std::abs(wh)==0 ){
							
                                                        h1_RecX_DT_St4_Wh0->Fill(xSegRec); h1_RecY_DT_St4_Wh0->Fill(ySegRec);
                                                        h1_ResRecX_DT_St4_Wh0->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St4_Wh0->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St4_Wh0->Fill(xSegErr);
                                                        h1_ErrY_DT_St4_Wh0->Fill(ySegErr);

                                                        h1_RecdX_DT_St4_Wh0->Fill(dxSegRec); h1_RecdY_DT_St4_Wh0->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St4_Wh0->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St4_Wh0->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St4_Wh0->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St4_Wh0->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St4_Wh0->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St4_Wh0->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St4_Wh0->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St4_Wh0->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St4_Wh0->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St4_Wh0->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St4_Wh0->Fill(xSegRec); h1_RecY_DT_PtCut_St4_Wh0->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St4_Wh0->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St4_Wh0->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St4_Wh0->Fill(dxSegRec); h1_RecdY_DT_PtCut_St4_Wh0->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St4_Wh0->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St4_Wh0->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St4_Wh0->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St4_Wh0->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St4_Wh0->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St4_Wh0->Fill(dySegErr);
							}
                                                } else if( st==4 && std::abs(wh)==1 ){
							
                                                        h1_RecX_DT_St4_Wh1->Fill(xSegRec); h1_RecY_DT_St4_Wh1->Fill(ySegRec);
                                                        h1_ResRecX_DT_St4_Wh1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St4_Wh1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St4_Wh1->Fill(xSegErr);
                                                        h1_ErrY_DT_St4_Wh1->Fill(ySegErr);

                                                        h1_RecdX_DT_St4_Wh1->Fill(dxSegRec); h1_RecdY_DT_St4_Wh1->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St4_Wh1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St4_Wh1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St4_Wh1->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St4_Wh1->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St4_Wh1->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St4_Wh1->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St4_Wh1->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St4_Wh1->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St4_Wh1->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St4_Wh1->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St4_Wh1->Fill(xSegRec); h1_RecY_DT_PtCut_St4_Wh1->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St4_Wh1->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St4_Wh1->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St4_Wh1->Fill(dxSegRec); h1_RecdY_DT_PtCut_St4_Wh1->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St4_Wh1->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St4_Wh1->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St4_Wh1->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St4_Wh1->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St4_Wh1->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St4_Wh1->Fill(dySegErr);
							}
                                                } else if( st==4 && std::abs(wh)==2 ){
							
                                                        h1_RecX_DT_St4_Wh2->Fill(xSegRec); h1_RecY_DT_St4_Wh2->Fill(ySegRec);
                                                        h1_ResRecX_DT_St4_Wh2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                        h1_ResRecY_DT_St4_Wh2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                        h1_ErrX_DT_St4_Wh2->Fill(xSegErr);
                                                        h1_ErrY_DT_St4_Wh2->Fill(ySegErr);

                                                        h1_RecdX_DT_St4_Wh2->Fill(dxSegRec); h1_RecdY_DT_St4_Wh2->Fill(dySegRec);
                                                        h1_ResRecdX_DT_St4_Wh2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                        h1_ResRecdY_DT_St4_Wh2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                        h1_ErrdX_DT_St4_Wh2->Fill(dxSegErr);
                                                        h1_ErrdY_DT_St4_Wh2->Fill(dySegErr);

                                                        h2_RecResdX_ErrdX_DT_St4_Wh2->Fill((dxSegRec-dxSimSeg),dxSegErr);
                                                        h2_RecResdY_ErrdY_DT_St4_Wh2->Fill((dySegRec-dySimSeg),dySegErr);

                                                        h1_DeltaX_DT_St4_Wh2->Fill(xSegRec-xsimSeg);
                                                        h1_DeltaY_DT_St4_Wh2->Fill(ySegRec-ysimSeg);

                                                        h1_DeltadX_DT_St4_Wh2->Fill(dxSegRec-dxSimSeg);
                                                        h1_DeltadY_DT_St4_Wh2->Fill(dySegRec-dySimSeg);

                                                        if( muon_p>(psim+psim/5) ){ 
								h1_RecX_DT_PtCut_St4_Wh2->Fill(xSegRec); h1_RecY_DT_PtCut_St4_Wh2->Fill(ySegRec);
                                                                h1_ResRecX_DT_PtCut_St4_Wh2->Fill((xSegRec-xsimSeg)/xSegErr);
                                                                h1_ResRecY_DT_PtCut_St4_Wh2->Fill((ySegRec-ysimSeg)/ySegErr);

                                                                h1_RecdX_DT_PtCut_St4_Wh2->Fill(dxSegRec); h1_RecdY_DT_PtCut_St4_Wh2->Fill(dySegRec);
                                                                h1_ResRecdX_DT_PtCut_St4_Wh2->Fill((dxSegRec-dxSimSeg)/dxSegErr);
                                                                h1_ResRecdY_DT_PtCut_St4_Wh2->Fill((dySegRec-dySimSeg)/dySegErr);

                                                                h1_ErrX_DT_PtCut_St4_Wh2->Fill(xSegErr);
                                                                h1_ErrY_DT_PtCut_St4_Wh2->Fill(ySegErr);

                                                                h1_ErrdX_DT_PtCut_St4_Wh2->Fill(dxSegErr);
                                                                h1_ErrdY_DT_PtCut_St4_Wh2->Fill(dySegErr);
							}
                                                } 

					}//idDTSeg == isDTRec && (abs(xHitRec-xSegRec)/abs(xHitRec))<0.01

					//Filling the histo
                                        if(std::abs(muon_eta)<=0.8){
                                            h1_all_DeltaX_08->Fill(xSegRec - xsimSeg);
                                            h1_all_DeltaY_08->Fill(ySegRec - ysimSeg);
                                         
                                            h1_all_DeltadX_08->Fill(dxSegRec-dxSimSeg);
                                            h1_all_DeltadY_08->Fill(dySegRec-dySimSeg);
                                        } else if(std::abs(muon_eta)>0.8 && std::abs(muon_eta)<=1.2){
                                            h1_all_DeltaX_12->Fill(xSegRec - xsimSeg);
                                            h1_all_DeltaY_12->Fill(ySegRec - ysimSeg);

                                            h1_all_DeltadX_12->Fill(dxSegRec-dxSimSeg);
                                            h1_all_DeltadY_12->Fill(dySegRec-dySimSeg);                                               
                                        } else if(std::abs(muon_eta)>1.2 && std::abs(muon_eta)<=2.0){
                                            h1_all_DeltaX_20->Fill(xSegRec - xsimSeg);
                                            h1_all_DeltaY_20->Fill(ySegRec - ysimSeg);

                                            h1_all_DeltadX_20->Fill(dxSegRec-dxSimSeg);
                                            h1_all_DeltadY_20->Fill(dySegRec-dySimSeg);
                                        } else if(std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4){
                                            h1_all_DeltaX_24->Fill(xSegRec - xsimSeg);
                                            h1_all_DeltaY_24->Fill(ySegRec - ysimSeg);

                                            h1_all_DeltadX_24->Fill(dxSegRec-dxSimSeg);
                                            h1_all_DeltadY_24->Fill(dySegRec-dySimSeg);
                                        }

				     }// if( idDTSeg == isDTRec )
				}//for(DTRecSegment2DCollection::const_iterator segIt=dtSegments->begin();

				if(std::abs(muon_eta)<=0.8){
					h1_all_Nseg_08->Fill(SegCounter);
				} else if(std::abs(muon_eta)>0.8 && std::abs(muon_eta)<=1.2){
					h1_all_Nseg_12->Fill(SegCounter);
				} else if(std::abs(muon_eta)>1.2 && std::abs(muon_eta)<=2.0){
					h1_all_Nseg_20->Fill(SegCounter);
				} else if(std::abs(muon_eta)>2.0 && std::abs(muon_eta)<=2.4){
					h1_all_Nseg_24->Fill(SegCounter);
				}

			}//else if( subDet==1 )		
	}//for(unsigned int h=0;h<DYTtrack->recHitsSize();h++)
    } //for(edm::View<Track>::size_type i=0; i < trackCollection->size(); ++i){

    //Fix Histo Style
    h1_Track_P->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_P->GetYaxis()->SetTitle("Events");  
    h1_Track_P_08->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_P_08->GetYaxis()->SetTitle("Events");
    h1_Track_P_12->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_P_12->GetYaxis()->SetTitle("Events");
    h1_Track_P_20->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_P_20->GetYaxis()->SetTitle("Events");
    h1_Track_P_22->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_P_22->GetYaxis()->SetTitle("Events");
    h1_Track_P_24->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_P_24->GetYaxis()->SetTitle("Events");
    h1_Track_Eta->GetXaxis()->SetTitle("#eta_{Reco}");  h1_Track_Eta->GetYaxis()->SetTitle("Events");

    h1_Track_PtCut_Eta->GetXaxis()->SetTitle("#eta_{Reco}");       h1_Track_PtCut_Eta->GetYaxis()->SetTitle("Events");
    h1_Track_PtCut_Eta_08->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_PtCut_Eta_08->GetYaxis()->SetTitle("Events"); 
    h1_Track_PtCut_Eta_12->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_PtCut_Eta_12->GetYaxis()->SetTitle("Events");
    h1_Track_PtCut_Eta_20->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_PtCut_Eta_20->GetYaxis()->SetTitle("Events");
    h1_Track_PtCut_Eta_24->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h1_Track_PtCut_Eta_24->GetYaxis()->SetTitle("Events");
    
    h1_Track_1OvP->GetXaxis()->SetTitle("1/P_{Reco} [GeV]"); h1_Track_1OvP->GetYaxis()->SetTitle("Events");
    h1_Track_1OvP_08->GetXaxis()->SetTitle("1/P_{Reco} [GeV]"); h1_Track_1OvP_08->GetYaxis()->SetTitle("Events");
    h1_Track_1OvP_12->GetXaxis()->SetTitle("1/P_{Reco} [GeV]"); h1_Track_1OvP_12->GetYaxis()->SetTitle("Events");
    h1_Track_1OvP_20->GetXaxis()->SetTitle("1/P_{Reco} [GeV]"); h1_Track_1OvP_20->GetYaxis()->SetTitle("Events");
    h1_Track_1OvP_22->GetXaxis()->SetTitle("1/P_{Reco} [GeV]"); h1_Track_1OvP_22->GetYaxis()->SetTitle("Events");
    h1_Track_1OvP_24->GetXaxis()->SetTitle("1/P_{Reco} [GeV]"); h1_Track_1OvP_24->GetYaxis()->SetTitle("Events");

    h2_Track_P_Vs_Eta->GetXaxis()->SetTitle("P_{Reco} [GeV]");  h2_Track_P_Vs_Eta->GetYaxis()->SetTitle("#eta_{Reco}");
    h2_Track_P_Vs_Eta_08->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h2_Track_P_Vs_Eta_08->GetYaxis()->SetTitle("#eta_{Reco}");
    h2_Track_P_Vs_Eta_12->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h2_Track_P_Vs_Eta_12->GetYaxis()->SetTitle("#eta_{Reco}");
    h2_Track_P_Vs_Eta_20->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h2_Track_P_Vs_Eta_20->GetYaxis()->SetTitle("#eta_{Reco}");
    h2_Track_P_Vs_Eta_24->GetXaxis()->SetTitle("P_{Reco} [GeV]"); h2_Track_P_Vs_Eta_24->GetYaxis()->SetTitle("#eta_{Reco}");

    h1_DeltaESim_DT_St1->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");  h1_DeltaESim_DT_St1->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_DT_St2->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");  h1_DeltaESim_DT_St2->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_DT_St3->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");  h1_DeltaESim_DT_St3->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_DT_St4->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");  h1_DeltaESim_DT_St4->GetYaxis()->SetTitle("Events");
    
    h1_DeltaESim_CSC_St1->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); h1_DeltaESim_CSC_St1->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_CSC_St2->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); h1_DeltaESim_CSC_St2->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_CSC_St3->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); h1_DeltaESim_CSC_St3->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_CSC_St4->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); h1_DeltaESim_CSC_St4->GetYaxis()->SetTitle("Events");
    
    h1_DeltaERec_DT_St1->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]");  h1_DeltaERec_DT_St1->GetYaxis()->SetTitle("Events");
    h1_DeltaERec_DT_St2->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]");  h1_DeltaERec_DT_St2->GetYaxis()->SetTitle("Events");
    h1_DeltaERec_DT_St3->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]");  h1_DeltaERec_DT_St3->GetYaxis()->SetTitle("Events");
    h1_DeltaERec_DT_St4->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]");  h1_DeltaERec_DT_St4->GetYaxis()->SetTitle("Events");

    h1_DeltaERec_CSC_St1->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h1_DeltaERec_CSC_St1->GetYaxis()->SetTitle("Events");  
    h1_DeltaERec_CSC_St2->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h1_DeltaERec_CSC_St2->GetYaxis()->SetTitle("Events");
    h1_DeltaERec_CSC_St3->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h1_DeltaERec_CSC_St3->GetYaxis()->SetTitle("Events");
    h1_DeltaERec_CSC_St4->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h1_DeltaERec_CSC_St4->GetYaxis()->SetTitle("Events");

    h1_DeltaESim_08->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); h1_DeltaESim_08->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_12->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); h1_DeltaESim_12->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_20->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); h1_DeltaESim_20->GetYaxis()->SetTitle("Events");
    h1_DeltaESim_24->GetXaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); h1_DeltaESim_24->GetYaxis()->SetTitle("Events");

    h1_DeltaERec_08->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h1_DeltaERec_08->GetYaxis()->SetTitle("Events");
    h1_DeltaERec_12->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h1_DeltaERec_12->GetYaxis()->SetTitle("Events");  
    h1_DeltaERec_20->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h1_DeltaERec_20->GetYaxis()->SetTitle("Events");
    h1_DeltaERec_24->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h1_DeltaERec_24->GetYaxis()->SetTitle("Events");

    h2_DeltaSim_DeltaRec_CSC_St1->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_CSC_St1->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");
    h2_DeltaSim_DeltaRec_CSC_St2->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_CSC_St2->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");
    h2_DeltaSim_DeltaRec_CSC_St3->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_CSC_St3->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");
    h2_DeltaSim_DeltaRec_CSC_St4->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_CSC_St4->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");

    h2_DeltaSim_DeltaRec_DT_St1->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_DT_St1->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]"); 
    h2_DeltaSim_DeltaRec_DT_St2->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_DT_St2->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");
    h2_DeltaSim_DeltaRec_DT_St3->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_DT_St3->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");
    h2_DeltaSim_DeltaRec_DT_St4->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_DT_St4->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");

    h2_DeltaSim_DeltaRec_08->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_08->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");
    h2_DeltaSim_DeltaRec_12->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_12->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");
    h2_DeltaSim_DeltaRec_20->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_20->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");
    h2_DeltaSim_DeltaRec_24->GetXaxis()->SetTitle("E_{Rec}-E_{Gen} [GeV]"); h2_DeltaSim_DeltaRec_24->GetYaxis()->SetTitle("E_{Sim}-E_{Gen} [GeV]");

    h1_DeltaX_CSC_St1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_CSC_St2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St2->GetYaxis()->SetTitle("Events");
    h1_DeltaX_CSC_St3->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St3->GetYaxis()->SetTitle("Events");
    h1_DeltaX_CSC_St4->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St4->GetYaxis()->SetTitle("Events");

    h1_DeltaY_CSC_St1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_CSC_St2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St2->GetYaxis()->SetTitle("Events"); 
    h1_DeltaY_CSC_St3->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St3->GetYaxis()->SetTitle("Events");
    h1_DeltaY_CSC_St4->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St4->GetYaxis()->SetTitle("Events");

    h1_DeltaX_DT_St1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St2->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St3->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St3->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St4->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St4->GetYaxis()->SetTitle("Events");

    h1_DeltaY_DT_St1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St2->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St3->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St3->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St4->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St4->GetYaxis()->SetTitle("Events");

    h1_DeltaX_08->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_08->GetYaxis()->SetTitle("Events");
    h1_DeltaX_12->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_12->GetYaxis()->SetTitle("Events");
    h1_DeltaX_20->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_20->GetYaxis()->SetTitle("Events");
    h1_DeltaX_24->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_24->GetYaxis()->SetTitle("Events");

    h1_DeltaY_08->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_08->GetYaxis()->SetTitle("Events");
    h1_DeltaY_12->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_12->GetYaxis()->SetTitle("Events");
    h1_DeltaY_20->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_20->GetYaxis()->SetTitle("Events");
    h1_DeltaY_24->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_24->GetYaxis()->SetTitle("Events");

    h2_RecX_SimX_CSC_St1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_CSC_St1->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_CSC_St2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_CSC_St2->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_CSC_St3->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_CSC_St3->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_CSC_St4->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_CSC_St4->GetYaxis()->SetTitle("X_{Sim}^{Loc}");

    h2_RecY_SimY_CSC_St1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_CSC_St1->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_CSC_St2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_CSC_St2->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_CSC_St3->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_CSC_St3->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_CSC_St4->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_CSC_St4->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");

    h2_RecX_SimX_DT_St1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_DT_St1->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_DT_St2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_DT_St2->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_DT_St3->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_DT_St3->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_DT_St4->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_DT_St4->GetYaxis()->SetTitle("X_{Sim}^{Loc}");

    h2_RecY_SimY_DT_St1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_DT_St1->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_DT_St2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_DT_St2->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_DT_St3->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_DT_St3->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_DT_St4->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_DT_St4->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");

    h2_RecX_SimX_08->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_08->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_12->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_12->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_20->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_20->GetYaxis()->SetTitle("X_{Sim}^{Loc}");
    h2_RecX_SimX_24->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_SimX_24->GetYaxis()->SetTitle("X_{Sim}^{Loc}");

    h2_RecY_SimY_08->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_08->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_12->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_12->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_20->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_20->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_RecY_SimY_24->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h2_RecY_SimY_24->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");

    //Bias in the direction
    h1_DeltadX_CSC_St1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_CSC_St2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St2->GetYaxis()->SetTitle("Events");
    h1_DeltadX_CSC_St3->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St3->GetYaxis()->SetTitle("Events"); 
    h1_DeltadX_CSC_St4->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St4->GetYaxis()->SetTitle("Events");

    h1_DeltadY_CSC_St1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_CSC_St2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St2->GetYaxis()->SetTitle("Events");
    h1_DeltadY_CSC_St3->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St3->GetYaxis()->SetTitle("Events");
    h1_DeltadY_CSC_St4->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St4->GetYaxis()->SetTitle("Events");

    h1_DeltadX_DT_St1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St2->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St3->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St3->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St4->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St4->GetYaxis()->SetTitle("Events");

    h1_DeltadY_DT_St1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St2->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St3->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St3->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St4->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St4->GetYaxis()->SetTitle("Events");

    h1_DeltadX_08->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_08->GetYaxis()->SetTitle("Events");
    h1_DeltadX_12->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_12->GetYaxis()->SetTitle("Events");
    h1_DeltadX_20->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_20->GetYaxis()->SetTitle("Events");
    h1_DeltadX_24->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_24->GetYaxis()->SetTitle("Events");

    h1_DeltadY_08->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_08->GetYaxis()->SetTitle("Events");
    h1_DeltadY_12->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_12->GetYaxis()->SetTitle("Events");
    h1_DeltadY_20->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_20->GetYaxis()->SetTitle("Events");
    h1_DeltadY_24->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_24->GetYaxis()->SetTitle("Events");

    h2_RecdX_SimdX_CSC_St1->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_CSC_St1->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_CSC_St2->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_CSC_St2->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_CSC_St3->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_CSC_St3->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_CSC_St4->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_CSC_St4->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");

    h2_RecdY_SimdY_CSC_St1->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_CSC_St1->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_CSC_St2->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_CSC_St2->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_CSC_St3->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_CSC_St3->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_CSC_St4->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_CSC_St4->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");

    h2_RecdX_SimdX_DT_St1->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_DT_St1->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_DT_St2->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_DT_St2->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_DT_St3->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_DT_St3->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_DT_St4->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_DT_St4->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");

    h2_RecdY_SimdY_DT_St1->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_DT_St1->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_DT_St2->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_DT_St2->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_DT_St3->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_DT_St3->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_DT_St4->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_DT_St4->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");

    h2_RecdX_SimdX_08->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_08->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_12->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_12->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_20->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_20->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");
    h2_RecdX_SimdX_24->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_SimdX_24->GetYaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}");

    h2_RecdY_SimdY_08->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_08->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_12->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_12->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_20->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_20->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_RecdY_SimdY_24->GetXaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}"); h2_RecdY_SimdY_24->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");

    h2_RecX_RecY_DT_St1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_DT_St1->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_DT_St2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_DT_St2->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_DT_St3->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_DT_St3->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_DT_St4->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_DT_St4->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");

    h2_SimX_SimY_DT_St1->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_DT_St1->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_DT_St2->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_DT_St2->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_DT_St3->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_DT_St3->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_DT_St4->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_DT_St4->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");

    h2_RecX_RecY_CSC_St1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_CSC_St1->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_CSC_St2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_CSC_St2->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_CSC_St3->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_CSC_St3->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_CSC_St4->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_CSC_St4->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");

    h2_SimX_SimY_CSC_St1->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_CSC_St1->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_CSC_St2->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_CSC_St2->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_CSC_St3->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_CSC_St3->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_CSC_St4->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_CSC_St4->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");

    h2_RecX_RecY_08->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_08->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_12->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_12->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_20->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_20->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
    h2_RecX_RecY_24->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_24->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");

    h2_SimX_SimY_08->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_08->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_12->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_12->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_20->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_20->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
    h2_SimX_SimY_24->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_24->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");

    h2_RecdX_RecdY_DT_St1->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_DT_St1->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");
    h2_RecdX_RecdY_DT_St2->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_DT_St2->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");
    h2_RecdX_RecdY_DT_St3->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_DT_St3->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");
    h2_RecdX_RecdY_DT_St4->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_DT_St4->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");

    h2_SimdX_SimdY_DT_St1->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_DT_St1->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_DT_St2->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_DT_St2->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_DT_St3->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_DT_St3->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_DT_St4->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_DT_St4->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");    

    h2_RecdX_RecdY_CSC_St1->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_CSC_St1->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");  
    h2_RecdX_RecdY_CSC_St2->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_CSC_St2->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");
    h2_RecdX_RecdY_CSC_St3->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_CSC_St3->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");
    h2_RecdX_RecdY_CSC_St4->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_CSC_St4->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");

    h2_SimdX_SimdY_CSC_St1->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_CSC_St1->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_CSC_St2->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_CSC_St2->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_CSC_St3->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_CSC_St3->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_CSC_St4->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_CSC_St4->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");   
 
    h2_RecdX_RecdY_08->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_08->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");
    h2_RecdX_RecdY_12->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_12->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");
    h2_RecdX_RecdY_20->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_20->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");
    h2_RecdX_RecdY_24->GetXaxis()->SetTitle("(dX/dZ)_{Rec}^{Loc}"); h2_RecdX_RecdY_24->GetYaxis()->SetTitle("(dY/dZ)_{Rec}^{Loc}");

    h2_SimdX_SimdY_08->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_08->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_12->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_12->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_20->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_20->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");
    h2_SimdX_SimdY_24->GetXaxis()->SetTitle("(dX/dZ)_{Sim}^{Loc}"); h2_SimdX_SimdY_24->GetYaxis()->SetTitle("(dY/dZ)_{Sim}^{Loc}");

    //Histo contaning the comparison of all the segment inside a chamber
    h1_all_DeltaX_08->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_all_DeltaX_08->GetYaxis()->SetTitle("Events");
    h1_all_DeltaX_12->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_all_DeltaX_12->GetYaxis()->SetTitle("Events");
    h1_all_DeltaX_20->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_all_DeltaX_20->GetYaxis()->SetTitle("Events");
    h1_all_DeltaX_24->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_all_DeltaX_24->GetYaxis()->SetTitle("Events");

    h1_all_DeltaY_08->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_all_DeltaY_08->GetYaxis()->SetTitle("Events");
    h1_all_DeltaY_12->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_all_DeltaY_12->GetYaxis()->SetTitle("Events");
    h1_all_DeltaY_20->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_all_DeltaY_20->GetYaxis()->SetTitle("Events");
    h1_all_DeltaY_24->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_all_DeltaY_24->GetYaxis()->SetTitle("Events");

    h1_all_DeltadX_08->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_all_DeltadX_08->GetYaxis()->SetTitle("Events");
    h1_all_DeltadX_12->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_all_DeltadX_12->GetYaxis()->SetTitle("Events");
    h1_all_DeltadX_20->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_all_DeltadX_20->GetYaxis()->SetTitle("Events");
    h1_all_DeltadX_24->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_all_DeltadX_24->GetYaxis()->SetTitle("Events");

    h1_all_DeltadY_08->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_all_DeltadY_08->GetYaxis()->SetTitle("Events");
    h1_all_DeltadY_12->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_all_DeltadY_12->GetYaxis()->SetTitle("Events");
    h1_all_DeltadY_20->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_all_DeltadY_20->GetYaxis()->SetTitle("Events");
    h1_all_DeltadY_24->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_all_DeltadY_24->GetYaxis()->SetTitle("Events");

    //Number of Segment in the chamber
    h1_all_Nseg_08->GetXaxis()->SetTitle("#Seg_{Rec}"); h1_all_Nseg_08->GetYaxis()->SetTitle("Events");
    h1_all_Nseg_12->GetXaxis()->SetTitle("#Seg_{Rec}"); h1_all_Nseg_12->GetYaxis()->SetTitle("Events");
    h1_all_Nseg_20->GetXaxis()->SetTitle("#Seg_{Rec}"); h1_all_Nseg_20->GetYaxis()->SetTitle("Events");
    h1_all_Nseg_24->GetXaxis()->SetTitle("#Seg_{Rec}"); h1_all_Nseg_24->GetYaxis()->SetTitle("Events");

    //Studying some bias in the position of the segment
    h1_RecX_DT_St1_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_St1_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_St1_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecX_DT_St2_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_St2_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_St2_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecX_DT_St3_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_St3_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_St3_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecX_DT_St4_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_St4_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_St4_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecX_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecX_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecX_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecX_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecX_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecY_DT_St1_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_St1_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_St1_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecY_DT_St2_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_St2_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_St2_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecY_DT_St3_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_St3_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_St3_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecY_DT_St4_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_St4_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_St4_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_St4_Wh2->GetYaxis()->SetTitle("Events");      
     
    h1_RecY_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecY_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecY_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecY_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecY_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events"); 
   
    h1_RecX_CSC_St1_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_St1_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_St1_Rg3->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecX_CSC_St2_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_St2_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecX_CSC_St3_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_St3_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecX_CSC_St4_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_St4_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecX_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");
    
    h1_RecX_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_PtCut_St2_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecX_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecX_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecX_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h1_RecX_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecY_CSC_St1_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_St1_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_St1_Rg3->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");
    
    h1_RecY_CSC_St2_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_St2_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecY_CSC_St3_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_St3_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecY_CSC_St4_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_St4_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecY_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");
      
    h1_RecY_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_PtCut_St2_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St2_Rg2->GetYaxis()->SetTitle("Events");
      
    h1_RecY_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");
      
    h1_RecY_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecY_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc}"); h1_RecY_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    //Resolution on the position
    h1_ResRecX_DT_St1_Wh0->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_St1_Wh1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_St1_Wh2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecX_DT_St2_Wh0->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_St2_Wh1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_St2_Wh2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecX_DT_St3_Wh0->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_St3_Wh1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_St3_Wh2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecX_DT_St4_Wh0->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_St4_Wh1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_St4_Wh2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecX_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecX_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecX_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecX_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecX_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecX_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecY_DT_St1_Wh0->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_St1_Wh1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_St1_Wh2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecY_DT_St2_Wh0->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_St2_Wh1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_St2_Wh2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecY_DT_St3_Wh0->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_St3_Wh1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_St3_Wh2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecY_DT_St4_Wh0->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_St4_Wh1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_St4_Wh2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_ResRecY_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecY_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecY_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecY_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecY_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecY_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_ResRecY_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecResX_CSC_St1_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_St1_Rg2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_St1_Rg3->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecResX_CSC_St2_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_St2_Rg2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResX_CSC_St3_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_St3_Rg2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResX_CSC_St4_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_St4_Rg2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResX_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");
    
    h1_RecResX_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");

    h1_RecResX_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResX_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResX_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("(X_{Rec}^{Loc} - X_{Sim}^{Loc})/#deltaX_{Rec}^{Loc}"); h1_RecResX_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResY_CSC_St1_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_St1_Rg2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_St1_Rg3->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");
    
    h1_RecResY_CSC_St2_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_St2_Rg2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResY_CSC_St3_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_St3_Rg2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResY_CSC_St4_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_St4_Rg2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResY_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecResY_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");

    h1_RecResY_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResY_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResY_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("(Y_{Rec}^{Loc} - Y_{Sim}^{Loc})/#deltaY_{Rec}^{Loc}"); h1_RecResY_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    //Direction Plots
    h1_RecdX_DT_St1_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_St1_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_St1_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdX_DT_St2_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_St2_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_St2_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdX_DT_St3_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_St3_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_St3_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdX_DT_St4_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_St4_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_St4_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdX_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdX_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdX_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdX_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdX_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdY_DT_St1_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_St1_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_St1_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdY_DT_St2_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_St2_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_St2_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdY_DT_St3_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_St3_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_St3_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdY_DT_St4_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_St4_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_St4_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdY_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdY_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdY_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdY_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_RecdY_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecdX_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_St1_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_St1_Rg3->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecdX_CSC_St2_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_St2_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdX_CSC_St3_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_St3_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdX_CSC_St4_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_St4_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdX_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecdX_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_PtCut_St2_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdX_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdX_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdX_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc}"); h1_RecdX_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdY_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_St1_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_St1_Rg3->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecdY_CSC_St2_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_St2_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdY_CSC_St3_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_St3_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdY_CSC_St4_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_St4_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdY_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecdY_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_PtCut_St2_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdY_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecdY_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecdY_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc}"); h1_RecdY_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    //Resolution 
    h1_ResRecdX_DT_St1_Wh0->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_St1_Wh1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_St1_Wh2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdX_DT_St2_Wh0->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_St2_Wh1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_St2_Wh2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdX_DT_St3_Wh0->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_St3_Wh1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_St3_Wh2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdX_DT_St4_Wh0->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_St4_Wh1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_St4_Wh2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdX_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdX_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdX_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdX_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdX_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_ResRecdX_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdY_DT_St1_Wh0->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_St1_Wh1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_St1_Wh2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdY_DT_St2_Wh0->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_St2_Wh1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_St2_Wh2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdY_DT_St3_Wh0->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_St3_Wh1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_St3_Wh2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St3_Wh2->GetYaxis()->SetTitle("Events");
    
    h1_ResRecdY_DT_St4_Wh0->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_St4_Wh1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_St4_Wh2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdY_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdY_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdY_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ResRecdY_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ResRecdY_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_ResRecdY_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_RecResdX_CSC_St1_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_St1_Rg2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_St1_Rg3->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecResdX_CSC_St2_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_St2_Rg2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdX_CSC_St3_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_St3_Rg2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdX_CSC_St4_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_St4_Rg2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdX_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecResdX_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");

    h1_RecResdX_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdX_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdX_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("((#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc})/#delta((#frac{dX}{dZ})_{Rec}^{Loc})"); h1_RecResdX_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdY_CSC_St1_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_St1_Rg2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_St1_Rg3->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecResdY_CSC_St2_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_St2_Rg2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdY_CSC_St3_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_St3_Rg2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdY_CSC_St4_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_St4_Rg2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdY_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_RecResdY_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");

    h1_RecResdY_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_RecResdY_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_RecResdY_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("((#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc})/#delta((#frac{dY}{dZ})_{Rec}^{Loc})"); h1_RecResdY_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    //Differance in position and Direction divided by Wheel
    h1_DeltaX_DT_St1_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St1_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St1_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltaX_DT_St2_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St2_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St2_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltaX_DT_St3_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St3_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St3_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltaX_DT_St4_Wh0->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St4_Wh1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_DT_St4_Wh2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltaY_DT_St1_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St1_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St1_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltaY_DT_St2_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St2_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St2_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltaY_DT_St3_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St3_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St3_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltaY_DT_St4_Wh0->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St4_Wh1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_DT_St4_Wh2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltaX_CSC_St1_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_CSC_St1_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_DeltaX_CSC_St1_Rg3->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_DeltaX_CSC_St2_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_CSC_St2_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltaX_CSC_St3_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_CSC_St3_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltaX_CSC_St4_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltaX_CSC_St4_Rg2->GetXaxis()->SetTitle("X_{Rec}^{Loc} - X_{Sim}^{Loc}"); h1_DeltaX_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltaY_CSC_St1_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_CSC_St1_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_DeltaY_CSC_St1_Rg3->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");
    
    h1_DeltaY_CSC_St2_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_CSC_St2_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltaY_CSC_St3_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_CSC_St3_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");
    
    h1_DeltaY_CSC_St4_Rg1->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltaY_CSC_St4_Rg2->GetXaxis()->SetTitle("Y_{Rec}^{Loc} - Y_{Sim}^{Loc}"); h1_DeltaY_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltadX_DT_St1_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St1_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St1_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltadX_DT_St2_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St2_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St2_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltadX_DT_St3_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St3_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St3_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltadX_DT_St4_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St4_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_DT_St4_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltadY_DT_St1_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St1_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St1_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltadY_DT_St2_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St2_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St2_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltadY_DT_St3_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St3_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St3_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltadY_DT_St4_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St4_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_DT_St4_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_DeltadX_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_CSC_St1_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_DeltadX_CSC_St1_Rg3->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_DeltadX_CSC_St2_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_CSC_St2_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltadX_CSC_St3_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_CSC_St3_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltadX_CSC_St4_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltadX_CSC_St4_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h1_DeltadX_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltadY_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_CSC_St1_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_DeltadY_CSC_St1_Rg3->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");
    
    h1_DeltadY_CSC_St2_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_CSC_St2_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltadY_CSC_St3_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_CSC_St3_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_DeltadY_CSC_St4_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_DeltadY_CSC_St4_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h1_DeltadY_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    //Error Position
    h1_ErrX_DT_St1_Wh0->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_St1_Wh1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_St1_Wh2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrX_DT_St2_Wh0->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_St2_Wh1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_St2_Wh2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrX_DT_St3_Wh0->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_St3_Wh1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_St3_Wh2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrX_DT_St4_Wh0->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_St4_Wh1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_St4_Wh2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrY_DT_St1_Wh0->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_St1_Wh1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_St1_Wh2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrY_DT_St2_Wh0->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_St2_Wh1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_St2_Wh2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrY_DT_St3_Wh0->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_St3_Wh1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_St3_Wh2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrY_DT_St4_Wh0->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_St4_Wh1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_St4_Wh2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrX_CSC_St1_Rg1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_St1_Rg2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_St1_Rg3->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_ErrX_CSC_St2_Rg1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_St2_Rg2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrX_CSC_St3_Rg1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_St3_Rg2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrX_CSC_St4_Rg1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_St4_Rg2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrY_CSC_St1_Rg1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_St1_Rg2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_St1_Rg3->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_ErrY_CSC_St2_Rg1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_St2_Rg2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrY_CSC_St3_Rg1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_St3_Rg2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrY_CSC_St4_Rg1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_St4_Rg2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    //Err Position Pt Cut
    h1_ErrX_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrX_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrX_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrX_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrX_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrY_DT_PtCut_St1_Wh0->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_PtCut_St1_Wh1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_PtCut_St1_Wh2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrY_DT_PtCut_St2_Wh0->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_PtCut_St2_Wh1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_PtCut_St2_Wh2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrY_DT_PtCut_St3_Wh0->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_PtCut_St3_Wh1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_PtCut_St3_Wh2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrY_DT_PtCut_St4_Wh0->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_PtCut_St4_Wh1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrY_DT_PtCut_St4_Wh2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_DT_PtCut_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrX_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_ErrX_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_PtCut_St2_Rg2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrX_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrX_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrX_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("Err_{X}"); h1_ErrX_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrY_CSC_PtCut_St1_Rg1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_PtCut_St1_Rg2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_PtCut_St1_Rg3->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_ErrY_CSC_PtCut_St2_Rg1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_PtCut_St2_Rg2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrY_CSC_PtCut_St3_Rg1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_PtCut_St3_Rg2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrY_CSC_PtCut_St4_Rg1->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrY_CSC_PtCut_St4_Rg2->GetXaxis()->SetTitle("Err_{Y}"); h1_ErrY_CSC_PtCut_St4_Rg2->GetYaxis()->SetTitle("Events");

    //Error Matrixi direction
    h1_ErrdX_DT_St1_Wh0->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrdX_DT_St1_Wh1->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrdX_DT_St1_Wh2->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrdX_DT_St2_Wh0->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrdX_DT_St2_Wh1->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrdX_DT_St2_Wh2->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrdX_DT_St3_Wh0->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrdX_DT_St3_Wh1->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrdX_DT_St3_Wh2->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrdX_DT_St4_Wh0->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrdX_DT_St4_Wh1->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrdX_DT_St4_Wh2->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrdY_DT_St1_Wh0->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St1_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrdY_DT_St1_Wh1->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St1_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrdY_DT_St1_Wh2->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St1_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrdY_DT_St2_Wh0->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St2_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrdY_DT_St2_Wh1->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St2_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrdY_DT_St2_Wh2->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St2_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrdY_DT_St3_Wh0->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St3_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrdY_DT_St3_Wh1->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St3_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrdY_DT_St3_Wh2->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St3_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrdY_DT_St4_Wh0->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St4_Wh0->GetYaxis()->SetTitle("Events");
    h1_ErrdY_DT_St4_Wh1->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St4_Wh1->GetYaxis()->SetTitle("Events");
    h1_ErrdY_DT_St4_Wh2->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_DT_St4_Wh2->GetYaxis()->SetTitle("Events");

    h1_ErrdX_CSC_St1_Rg1->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrdX_CSC_St1_Rg2->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_ErrdX_CSC_St1_Rg3->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_ErrdX_CSC_St2_Rg1->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrdX_CSC_St2_Rg2->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrdX_CSC_St3_Rg1->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrdX_CSC_St3_Rg2->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrdX_CSC_St4_Rg1->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrdX_CSC_St4_Rg2->GetXaxis()->SetTitle("Err_{dX/dZ}"); h1_ErrdX_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrdY_CSC_St1_Rg1->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St1_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrdY_CSC_St1_Rg2->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St1_Rg2->GetYaxis()->SetTitle("Events");
    h1_ErrdY_CSC_St1_Rg3->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St1_Rg3->GetYaxis()->SetTitle("Events");

    h1_ErrdY_CSC_St2_Rg1->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St2_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrdY_CSC_St2_Rg2->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St2_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrdY_CSC_St3_Rg1->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St3_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrdY_CSC_St3_Rg2->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St3_Rg2->GetYaxis()->SetTitle("Events");

    h1_ErrdY_CSC_St4_Rg1->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St4_Rg1->GetYaxis()->SetTitle("Events");
    h1_ErrdY_CSC_St4_Rg2->GetXaxis()->SetTitle("Err_{dY/dZ}"); h1_ErrdY_CSC_St4_Rg2->GetYaxis()->SetTitle("Events");

  //2D Plots for errors and discrepancies between Reco and Sim
  h2_RecResdX_ErrdX_DT_St1_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St1_Wh0->GetYaxis()->SetTitle("Err_{dX/dZ}");
  h2_RecResdX_ErrdX_DT_St1_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St1_Wh1->GetYaxis()->SetTitle("Err_{dX/dZ}");
  h2_RecResdX_ErrdX_DT_St1_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St1_Wh2->GetYaxis()->SetTitle("Err_{dX/dZ}");

  h2_RecResdX_ErrdX_DT_St2_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St2_Wh0->GetYaxis()->SetTitle("Err_{dX/dZ}");
  h2_RecResdX_ErrdX_DT_St2_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St2_Wh1->GetYaxis()->SetTitle("Err_{dX/dZ}");
  h2_RecResdX_ErrdX_DT_St2_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St2_Wh2->GetYaxis()->SetTitle("Err_{dX/dZ}");

  h2_RecResdX_ErrdX_DT_St3_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St3_Wh0->GetYaxis()->SetTitle("Err_{dX/dZ}");
  h2_RecResdX_ErrdX_DT_St3_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St3_Wh1->GetYaxis()->SetTitle("Err_{dX/dZ}");
  h2_RecResdX_ErrdX_DT_St3_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St3_Wh2->GetYaxis()->SetTitle("Err_{dX/dZ}");

  h2_RecResdX_ErrdX_DT_St4_Wh0->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St4_Wh0->GetYaxis()->SetTitle("Err_{dX/dZ}");
  h2_RecResdX_ErrdX_DT_St4_Wh1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St4_Wh1->GetYaxis()->SetTitle("Err_{dX/dZ}");
  h2_RecResdX_ErrdX_DT_St4_Wh2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DT_St4_Wh2->GetYaxis()->SetTitle("Err_{dX/dZ}");

  h2_RecResdY_ErrdY_DT_St1_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St1_Wh0->GetYaxis()->SetTitle("Err_{dY/dZ}");
  h2_RecResdY_ErrdY_DT_St1_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St1_Wh1->GetYaxis()->SetTitle("Err_{dY/dZ}");
  h2_RecResdY_ErrdY_DT_St1_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St1_Wh2->GetYaxis()->SetTitle("Err_{dY/dZ}");

  h2_RecResdY_ErrdY_DT_St2_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St2_Wh0->GetYaxis()->SetTitle("Err_{dY/dZ}");
  h2_RecResdY_ErrdY_DT_St2_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St2_Wh1->GetYaxis()->SetTitle("Err_{dY/dZ}");
  h2_RecResdY_ErrdY_DT_St2_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St2_Wh2->GetYaxis()->SetTitle("Err_{dY/dZ}");
  
  h2_RecResdY_ErrdY_DT_St3_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St3_Wh0->GetYaxis()->SetTitle("Err_{dY/dZ}");
  h2_RecResdY_ErrdY_DT_St3_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St3_Wh1->GetYaxis()->SetTitle("Err_{dY/dZ}");
  h2_RecResdY_ErrdY_DT_St3_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St3_Wh2->GetYaxis()->SetTitle("Err_{dY/dZ}");

  h2_RecResdY_ErrdY_DT_St4_Wh0->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St4_Wh0->GetYaxis()->SetTitle("Err_{dY/dZ}");
  h2_RecResdY_ErrdY_DT_St4_Wh1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St4_Wh1->GetYaxis()->SetTitle("Err_{dY/dZ}");
  h2_RecResdY_ErrdY_DT_St4_Wh2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DT_St4_Wh2->GetYaxis()->SetTitle("Err_{dY/dZ}");

h2_RecResdX_ErrdX_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dX/dZ}");
h2_RecResdX_ErrdX_CSC_St1_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St1_Rg2->GetYaxis()->SetTitle("Err_{dX/dZ}");
h2_RecResdX_ErrdX_CSC_St1_Rg3->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St1_Rg3->GetYaxis()->SetTitle("Err_{dX/dZ}");

h2_RecResdX_ErrdX_CSC_St2_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St2_Rg1->GetYaxis()->SetTitle("Err_{dX/dZ}");
h2_RecResdX_ErrdX_CSC_St2_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St2_Rg2->GetYaxis()->SetTitle("Err_{dX/dZ}");

h2_RecResdX_ErrdX_CSC_St3_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St3_Rg1->GetYaxis()->SetTitle("Err_{dX/dZ}");
h2_RecResdX_ErrdX_CSC_St3_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St3_Rg2->GetYaxis()->SetTitle("Err_{dX/dZ}");

h2_RecResdX_ErrdX_CSC_St4_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St4_Rg1->GetYaxis()->SetTitle("Err_{dX/dZ}");
h2_RecResdX_ErrdX_CSC_St4_Rg2->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_CSC_St4_Rg2->GetYaxis()->SetTitle("Err_{dX/dZ}");

h2_RecResdY_ErrdY_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dY/dZ}");
h2_RecResdY_ErrdY_CSC_St1_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St1_Rg2->GetYaxis()->SetTitle("Err_{dY/dZ}");
h2_RecResdY_ErrdY_CSC_St1_Rg3->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St1_Rg3->GetYaxis()->SetTitle("Err_{dY/dZ}");

h2_RecResdY_ErrdY_CSC_St2_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St2_Rg1->GetYaxis()->SetTitle("Err_{dY/dZ}");
h2_RecResdY_ErrdY_CSC_St2_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St2_Rg2->GetYaxis()->SetTitle("Err_{dY/dZ}");

h2_RecResdY_ErrdY_CSC_St3_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St3_Rg1->GetYaxis()->SetTitle("Err_{dY/dZ}");
h2_RecResdY_ErrdY_CSC_St3_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St3_Rg2->GetYaxis()->SetTitle("Err_{dY/dZ}");

h2_RecResdY_ErrdY_CSC_St4_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St4_Rg1->GetYaxis()->SetTitle("Err_{dY/dZ}");
h2_RecResdY_ErrdY_CSC_St4_Rg2->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_CSC_St4_Rg2->GetYaxis()->SetTitle("Err_{dY/dZ}");


h2_RecResdX_ErrdX_UpStation1_DirZ_1_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_UpStation1_DirZ_1_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dX/dZ}"); 
h2_RecResdY_ErrdY_UpStation1_DirZ_1_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_UpStation1_DirZ_1_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dY/dZ}");
h2_RecResdX_ErrdX_DwStation1_DirZ_1_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DwStation1_DirZ_1_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dX/dZ}");
h2_RecResdY_ErrdY_DwStation1_DirZ_1_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DwStation1_DirZ_1_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dY/dZ}");

h2_RecResdX_ErrdX_UpStation1_DirZ_m1_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_UpStation1_DirZ_m1_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dX/dZ}");
h2_RecResdY_ErrdY_UpStation1_DirZ_m1_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_UpStation1_DirZ_m1_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dY/dZ}");
h2_RecResdX_ErrdX_DwStation1_DirZ_m1_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dX}{dZ})_{Rec}^{Loc} - (#frac{dX}{dZ})_{Sim}^{Loc}"); h2_RecResdX_ErrdX_DwStation1_DirZ_m1_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dX/dZ}");
h2_RecResdY_ErrdY_DwStation1_DirZ_m1_CSC_St1_Rg1->GetXaxis()->SetTitle("(#frac{dY}{dZ})_{Rec}^{Loc} - (#frac{dY}{dZ})_{Sim}^{Loc}"); h2_RecResdY_ErrdY_DwStation1_DirZ_m1_CSC_St1_Rg1->GetYaxis()->SetTitle("Err_{dY/dZ}");

h2_SimX_SimY_DwStation1_DirZ_1_CSC_St1_Rg1->GetXaxis()->SetTitle("X_{Sim}^{Loc}");  h2_SimX_SimY_DwStation1_DirZ_1_CSC_St1_Rg1->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");
h2_SimX_SimY_DwStation1_DirZ_m1_CSC_St1_Rg1->GetXaxis()->SetTitle("X_{Sim}^{Loc}"); h2_SimX_SimY_DwStation1_DirZ_m1_CSC_St1_Rg1->GetYaxis()->SetTitle("Y_{Sim}^{Loc}");

h2_RecX_RecY_DwStation1_DirZ_1_CSC_St1_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}");  h2_RecX_RecY_DwStation1_DirZ_1_CSC_St1_Rg1->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");
h2_RecX_RecY_DwStation1_DirZ_m1_CSC_St1_Rg1->GetXaxis()->SetTitle("X_{Rec}^{Loc}"); h2_RecX_RecY_DwStation1_DirZ_m1_CSC_St1_Rg1->GetYaxis()->SetTitle("Y_{Rec}^{Loc}");

    //To track station situation
    h1_1Seg_DT->GetXaxis()->SetTitle("DT Station");           h1_1Seg_DT->GetYaxis()->SetTitle("Events"); 
    h1_1Seg_CSC->GetXaxis()->SetTitle("CSC Station");         h1_1Seg_CSC->GetYaxis()->SetTitle("Events");

    h2_2Seg_DT->GetXaxis()->SetTitle("DT Station");           h2_2Seg_DT->GetYaxis()->SetTitle("DT Station");
    h2_2Seg_CSC->GetXaxis()->SetTitle("CSC Station");         h2_2Seg_CSC->GetYaxis()->SetTitle("CSC Station");

    h2_1Seg_DT_1Seg_CSC->GetXaxis()->SetTitle("DT Station");  h2_1Seg_DT_1Seg_CSC->GetYaxis()->SetTitle("CSC Station");

    h1_3Seg_DT->GetXaxis()->SetTitle("DT Station");           h1_3Seg_DT->GetYaxis()->SetTitle("Events"); 
    h1_3Seg_CSC->GetXaxis()->SetTitle("CSC Station");         h1_3Seg_CSC->GetYaxis()->SetTitle("Events");

} //void DYTthrScanTuner::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)

void DYTthrScanTuner::beginJob(){

  edm::Service<TFileService> fs;

  //General Kinematical Property
  h1_Track_P    = fs->make<TH1F>(     "DYT_p",                                       "DYT - P_{Rec}",  2*psim,    0.,  2*psim);
  h1_Track_P_08 = fs->make<TH1F>(   "DYT_p08",   "DYT - P_{Rec} - 0 < #lbar #eta_{Rec} #cbar <= 0.8",  2*psim,    0.,  2*psim);
  h1_Track_P_12 = fs->make<TH1F>(   "DYT_p12", "DYT - P_{Rec} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2",  2*psim,    0.,  2*psim);
  h1_Track_P_20 = fs->make<TH1F>(   "DYT_p20", "DYT - P_{Rec} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0",  2*psim,    0.,  2*psim);
  h1_Track_P_22 = fs->make<TH1F>(   "DYT_p22", "DYT - P_{Rec} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.2",  2*psim,    0.,  2*psim);
  h1_Track_P_24 = fs->make<TH1F>(   "DYT_p24", "DYT - P_{Rec} - 2.2 < #lbar #eta_{Rec} #cbar <= 2.4",  2*psim,    0.,  2*psim);
  h1_Track_Eta  = fs->make<TH1F>(   "DYT_eta",                                    "DYT - #eta_{Rec}",     520,  -2.6,     2.6);

  int nbins = (10000-(psim+psim/5));
  h1_Track_PtCut_Eta    = fs->make<TH1F>(   "DYT_PtCut_eta",                                     "P Cut, DYT - #eta_{Rec}",    520,           -2.6,   2.6);
  h1_Track_PtCut_Eta_08 = fs->make<TH1F>(   "DYT_PtCut_p08",    "P Cut, DYT - P_{Rec} - 0 < #lbar #eta_{Rec} #cbar <= 0.8",  nbins,  (psim+psim/5), 10000);
  h1_Track_PtCut_Eta_12 = fs->make<TH1F>(   "DYT_PtCut_p12",  "P Cut, DYT - P_{Rec} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2",  nbins,  (psim+psim/5), 10000);
  h1_Track_PtCut_Eta_20 = fs->make<TH1F>(   "DYT_PtCut_p20",  "P Cut, DYT - P_{Rec} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0",  nbins,  (psim+psim/5), 10000);
  h1_Track_PtCut_Eta_24 = fs->make<TH1F>(   "DYT_PtCut_p24",  "P Cut, DYT - P_{Rec} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4",  nbins,  (psim+psim/5), 10000);

  h1_Track_1OvP    = fs->make<TH1F>(    "DYT_Invp",                                       "DYT - 1/P_{Rec}", 25000, 0, 0.0025); 
  h1_Track_1OvP_08 = fs->make<TH1F>(   "DYT_InvpB",   "DYT - 1/P_{Rec} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 25000, 0, 0.0025);
  h1_Track_1OvP_12 = fs->make<TH1F>( "DYT_InvpE12", "DYT - 1/P_{Rec} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 25000, 0, 0.0025);
  h1_Track_1OvP_20 = fs->make<TH1F>( "DYT_InvpE20", "DYT - 1/P_{Rec} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 25000, 0, 0.0025);
  h1_Track_1OvP_22 = fs->make<TH1F>( "DYT_InvpE22", "DYT - 1/P_{Rec} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.2", 25000, 0, 0.0025);
  h1_Track_1OvP_24 = fs->make<TH1F>( "DYT_InvpE24", "DYT - 1/P_{Rec} - 2.2 < #lbar #eta_{Rec} #cbar <= 2.4", 25000, 0, 0.0025);

  h2_Track_P_Vs_Eta    = fs->make<TH2F>(   "DYT_PvsEta",                          "P_{Rec} Vs #eta_{Rec}",  2*psim,  0.,  2*psim, 520,  -2.6,  2.6); 
  h2_Track_P_Vs_Eta_08 = fs->make<TH2F>( "DYT_PvsEta08",   "P_{Rec} Vs 0 < #lbar #eta_{Rec} #cbar <= 0.8",  2*psim,  0.,  2*psim, 520,  -2.6,  2.6);
  h2_Track_P_Vs_Eta_12 = fs->make<TH2F>( "DYT_PvsEta12", "P_{Rec} Vs 0.8 < #lbar #eta_{Rec} #cbar <= 1.2",  2*psim,  0.,  2*psim, 520,  -2.6,  2.6);
  h2_Track_P_Vs_Eta_20 = fs->make<TH2F>( "DYT_PvsEta20", "P_{Rec} Vs 1.2 < #lbar #eta_{Rec} #cbar <= 2.0",  2*psim,  0.,  2*psim, 520,  -2.6,  2.6);
  h2_Track_P_Vs_Eta_24 = fs->make<TH2F>( "DYT_PvsEta24", "P_{Rec} Vs 2.0 < #lbar #eta_{Rec} #cbar <= 2.4",  2*psim,  0.,  2*psim, 520,  -2.6,  2.6);
  
  //Energy Loss by Station
  h1_DeltaESim_DT_St1 = fs->make<TH1F>( "DeltaESim_DT_St1", "#DeltaE_{Sim} - Station 1 - DT", 20000, -1000, 1000);
  h1_DeltaESim_DT_St2 = fs->make<TH1F>( "DeltaESim_DT_St2", "#DeltaE_{Sim} - Station 2 - DT", 20000, -1000, 1000); 
  h1_DeltaESim_DT_St3 = fs->make<TH1F>( "DeltaESim_DT_St3", "#DeltaE_{Sim} - Station 3 - DT", 20000, -1000, 1000);
  h1_DeltaESim_DT_St4 = fs->make<TH1F>( "DeltaESim_DT_St4", "#DeltaE_{Sim} - Station 4 - DT", 20000, -1000, 1000);

  h1_DeltaESim_CSC_St1 = fs->make<TH1F>( "DeltaESim_CSC_St1", "#DeltaE_{Sim} - Station 1 - CSC", 20000, -1000, 1000);
  h1_DeltaESim_CSC_St2 = fs->make<TH1F>( "DeltaESim_CSC_St2", "#DeltaE_{Sim} - Station 2 - CSC", 20000, -1000, 1000);
  h1_DeltaESim_CSC_St3 = fs->make<TH1F>( "DeltaESim_CSC_St3", "#DeltaE_{Sim} - Station 3 - CSC", 20000, -1000, 1000);
  h1_DeltaESim_CSC_St4 = fs->make<TH1F>( "DeltaESim_CSC_St4", "#DeltaE_{Sim} - Station 4 - CSC", 20000, -1000, 1000);

  h1_DeltaERec_DT_St1 = fs->make<TH1F>( "DeltaERec_DT_St1", "#DeltaE_{Rec} - Station 1 - DT", 20000, -1000, 1000);
  h1_DeltaERec_DT_St2 = fs->make<TH1F>( "DeltaERec_DT_St2", "#DeltaE_{Rec} - Station 2 - DT", 20000, -1000, 1000);
  h1_DeltaERec_DT_St3 = fs->make<TH1F>( "DeltaERec_DT_St3", "#DeltaE_{Rec} - Station 3 - DT", 20000, -1000, 1000);
  h1_DeltaERec_DT_St4 = fs->make<TH1F>( "DeltaERec_DT_St4", "#DeltaE_{Rec} - Station 4 - DT", 20000, -1000, 1000);

  h1_DeltaERec_CSC_St1 = fs->make<TH1F>( "DeltaERec_CSC_St1", "#DeltaE_{Rec} - Station 1 - CSC", 20000, -1000, 1000);
  h1_DeltaERec_CSC_St2 = fs->make<TH1F>( "DeltaERec_CSC_St2", "#DeltaE_{Rec} - Station 2 - CSC", 20000, -1000, 1000);
  h1_DeltaERec_CSC_St3 = fs->make<TH1F>( "DeltaERec_CSC_St3", "#DeltaE_{Rec} - Station 3 - CSC", 20000, -1000, 1000);
  h1_DeltaERec_CSC_St4 = fs->make<TH1F>( "DeltaERec_CSC_St4", "#DeltaE_{Rec} - Station 4 - CSC", 20000, -1000, 1000);

  //Energy Loss by Eta Region
  h1_DeltaESim_08 = fs->make<TH1F>( "DeltaESim_08",   "#DeltaE_{Sim} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 20000, -1000, 1000);
  h1_DeltaESim_12 = fs->make<TH1F>( "DeltaESim_12", "#DeltaE_{Sim} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 20000, -1000, 1000);
  h1_DeltaESim_20 = fs->make<TH1F>( "DeltaESim_20", "#DeltaE_{Sim} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 20000, -1000, 1000);
  h1_DeltaESim_24 = fs->make<TH1F>( "DeltaESim_24", "#DeltaE_{Sim} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 20000, -1000, 1000);

  h1_DeltaERec_08 = fs->make<TH1F>( "DeltaERec_08",   "#DeltaE_{Rec} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 20000, -1000, 1000);
  h1_DeltaERec_12 = fs->make<TH1F>( "DeltaERec_12", "#DeltaE_{Rec} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 20000, -1000, 1000);
  h1_DeltaERec_20 = fs->make<TH1F>( "DeltaERec_20", "#DeltaE_{Rec} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 20000, -1000, 1000);
  h1_DeltaERec_24 = fs->make<TH1F>( "DeltaERec_24", "#DeltaE_{Rec} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 20000, -1000, 1000);

  //Comparison Energy Loss Sim Vs Reco by Station
  h2_DeltaSim_DeltaRec_CSC_St1 = fs->make<TH2F>( "DeltaESimVsDeltaERec_CSC_St1", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - Station 1 - CSC", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_CSC_St2 = fs->make<TH2F>( "DeltaESimVsDeltaERec_CSC_St2", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - Station 2 - CSC", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_CSC_St3 = fs->make<TH2F>( "DeltaESimVsDeltaERec_CSC_St3", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - Station 3 - CSC", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_CSC_St4 = fs->make<TH2F>( "DeltaESimVsDeltaERec_CSC_St4", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - Station 4 - CSC", 2000, -1000, 1000, 2000, -1000, 1000);

  h2_DeltaSim_DeltaRec_DT_St1 = fs->make<TH2F>( "DeltaESimVsDeltaERec_DT_St1", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - Station 1 - DT", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_DT_St2 = fs->make<TH2F>( "DeltaESimVsDeltaERec_DT_St2", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - Station 2 - DT", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_DT_St3 = fs->make<TH2F>( "DeltaESimVsDeltaERec_DT_St3", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - Station 3 - DT", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_DT_St4 = fs->make<TH2F>( "DeltaESimVsDeltaERec_DT_St4", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - Station 4 - DT", 2000, -1000, 1000, 2000, -1000, 1000);

  //Comparison 1/Energy Loss Sim Vs 1/Energy Loss Reco
  h2_1DeltaSim_1DeltaRec_CSC_St1 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_CSC_St1", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - Station 1 - CSC", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_CSC_St2 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_CSC_St2", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - Station 2 - CSC", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_CSC_St3 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_CSC_St3", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - Station 3 - CSC", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_CSC_St4 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_CSC_St4", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - Station 4 - CSC", 1000, -1, 1, 1000, -1, 1);

  h2_1DeltaSim_1DeltaRec_DT_St1 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_DT_St1", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - Station 1 - DT", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_DT_St2 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_DT_St2", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - Station 2 - DT", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_DT_St3 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_DT_St3", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - Station 3 - DT", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_DT_St4 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_DT_St4", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - Station 4 - DT", 1000, -1, 1, 1000, -1, 1);

  //Comparison Enegy Loss Sim Vs Reco by Eta Region
  h2_DeltaSim_DeltaRec_08 = fs->make<TH2F>( "DeltaESimVsDeltaERec_08",   "#DeltaE_{Sim} Vs #DeltaE_{Rec} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_12 = fs->make<TH2F>( "DeltaESimVsDeltaERec_12", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_20 = fs->make<TH2F>( "DeltaESimVsDeltaERec_20", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 2000, -1000, 1000, 2000, -1000, 1000);
  h2_DeltaSim_DeltaRec_24 = fs->make<TH2F>( "DeltaESimVsDeltaERec_24", "#DeltaE_{Sim} Vs #DeltaE_{Rec} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 2000, -1000, 1000, 2000, -1000, 1000);

  //Comparison 1/Energy Loss Sim Vs 1/Reco by Eta Region
  h2_1DeltaSim_1DeltaRec_08 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_08",   "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_12 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_12", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_20 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_20", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 1000, -1, 1, 1000, -1, 1);
  h2_1DeltaSim_1DeltaRec_24 = fs->make<TH2F>( "1DeltaESimVs1DeltaERec_24", "1/#DeltaE_{Sim} Vs 1/#DeltaE_{Rec} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 1000, -1, 1, 1000, -1, 1);

  //Bias in the position
  h1_DeltaX_CSC_St1 = fs->make<TH1F>( "DeltaX_CSC_St1", "#DeltaX - Station 1 - CSC", 20000, -10, 10); 
  h1_DeltaX_CSC_St2 = fs->make<TH1F>( "DeltaX_CSC_St2", "#DeltaX - Station 2 - CSC", 20000, -10, 10);
  h1_DeltaX_CSC_St3 = fs->make<TH1F>( "DeltaX_CSC_St3", "#DeltaX - Station 3 - CSC", 20000, -10, 10); 
  h1_DeltaX_CSC_St4 = fs->make<TH1F>( "DeltaX_CSC_St4", "#DeltaX - Station 4 - CSC", 20000, -10, 10);
  
  h1_DeltaY_CSC_St1 = fs->make<TH1F>( "DeltaY_CSC_St1", "#DeltaY - Station 1 - CSC", 20000, -10, 10);
  h1_DeltaY_CSC_St2 = fs->make<TH1F>( "DeltaY_CSC_St2", "#DeltaY - Station 2 - CSC", 20000, -10, 10); 
  h1_DeltaY_CSC_St3 = fs->make<TH1F>( "DeltaY_CSC_St3", "#DeltaY - Station 3 - CSC", 20000, -10, 10); 
  h1_DeltaY_CSC_St4 = fs->make<TH1F>( "DeltaY_CSC_St4", "#DeltaY - Station 4 - CSC", 20000, -10, 10);

  h1_DeltaX_DT_St1 = fs->make<TH1F>( "DeltaX_DT_St1", "#DeltaX - Station 1 - DT", 20000, -10, 10);
  h1_DeltaX_DT_St2 = fs->make<TH1F>( "DeltaX_DT_St2", "#DeltaX - Station 2 - DT", 20000, -10, 10);  
  h1_DeltaX_DT_St3 = fs->make<TH1F>( "DeltaX_DT_St3", "#DeltaX - Station 3 - DT", 20000, -10, 10);  
  h1_DeltaX_DT_St4 = fs->make<TH1F>( "DeltaX_DT_St4", "#DeltaX - Station 4 - DT", 20000, -10, 10);

  h1_DeltaY_DT_St1 = fs->make<TH1F>( "DeltaY_DT_St1", "#DeltaY - Station 1 - DT", 20000, -10, 10);  
  h1_DeltaY_DT_St2 = fs->make<TH1F>( "DeltaY_DT_St2", "#DeltaY - Station 2 - DT", 20000, -10, 10);  
  h1_DeltaY_DT_St3 = fs->make<TH1F>( "DeltaY_DT_St3", "#DeltaY - Station 3 - DT", 20000, -10, 10);  
  h1_DeltaY_DT_St4 = fs->make<TH1F>( "DeltaY_DT_St4", "#DeltaY - Station 4 - DT", 20000, -10, 10);

  h1_DeltaX_08 = fs->make<TH1F>( "DeltaX_08",   "#DeltaX - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 20000, -10, 10);      
  h1_DeltaX_12 = fs->make<TH1F>( "DeltaX_12", "#DeltaX - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 20000, -10, 10);      
  h1_DeltaX_20 = fs->make<TH1F>( "DeltaX_20", "#DeltaX - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 20000, -10, 10);      
  h1_DeltaX_24 = fs->make<TH1F>( "DeltaX_24", "#DeltaX - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 20000, -10, 10);
  
  h1_DeltaY_08 = fs->make<TH1F>( "DeltaY_08",   "#DeltaY - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 20000, -10, 10);      
  h1_DeltaY_12 = fs->make<TH1F>( "DeltaY_12", "#DeltaY - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 20000, -10, 10);      
  h1_DeltaY_20 = fs->make<TH1F>( "DeltaY_20", "#DeltaY - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 20000, -10, 10);      
  h1_DeltaY_24 = fs->make<TH1F>( "DeltaY_24", "#DeltaY - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 20000, -10, 10);

  h2_RecX_SimX_CSC_St1 = fs->make<TH2F>( "RecX_SimX_CSC_St1", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - Station 1 - CSC", 2000, -10, 10, 2000, -10, 10);
  h2_RecX_SimX_CSC_St2 = fs->make<TH2F>( "RecX_SimX_CSC_St2", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - Station 2 - CSC", 2000, -10, 10, 2000, -10, 10); 
  h2_RecX_SimX_CSC_St3 = fs->make<TH2F>( "RecX_SimX_CSC_St3", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - Station 3 - CSC", 2000, -10, 10, 2000, -10, 10); 
  h2_RecX_SimX_CSC_St4 = fs->make<TH2F>( "RecX_SimX_CSC_St4", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - Station 4 - CSC", 2000, -10, 10, 2000, -10, 10);

  h2_RecY_SimY_CSC_St1 = fs->make<TH2F>( "RecY_SimY_CSC_St1", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - Station 1 - CSC", 2000, -10, 10, 2000, -10, 10); 
  h2_RecY_SimY_CSC_St2 = fs->make<TH2F>( "RecY_SimY_CSC_St2", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - Station 2 - CSC", 2000, -10, 10, 2000, -10, 10); 
  h2_RecY_SimY_CSC_St3 = fs->make<TH2F>( "RecY_SimY_CSC_St3", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - Station 3 - CSC", 2000, -10, 10, 2000, -10, 10); 
  h2_RecY_SimY_CSC_St4 = fs->make<TH2F>( "RecY_SimY_CSC_St4", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - Station 4 - CSC", 2000, -10, 10, 2000, -10, 10);

  h2_RecX_SimX_DT_St1 = fs->make<TH2F>( "RecX_SimX_DT_St1", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - Station 1 - DT", 2000, -10, 10, 2000, -10, 10);  
  h2_RecX_SimX_DT_St2 = fs->make<TH2F>( "RecX_SimX_DT_St2", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - Station 2 - DT", 2000, -10, 10, 2000, -10, 10); 
  h2_RecX_SimX_DT_St3 = fs->make<TH2F>( "RecX_SimX_DT_St3", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - Station 3 - DT", 2000, -10, 10, 2000, -10, 10);  
  h2_RecX_SimX_DT_St4 = fs->make<TH2F>( "RecX_SimX_DT_St4", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - Station 4 - DT", 2000, -10, 10, 2000, -10, 10);

  h2_RecY_SimY_DT_St1 = fs->make<TH2F>( "RecY_SimY_DT_St1", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - Station 1 - DT", 2000, -10, 10, 2000, -10, 10);  
  h2_RecY_SimY_DT_St2 = fs->make<TH2F>( "RecY_SimY_DT_St2", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - Station 2 - DT", 2000, -10, 10, 2000, -10, 10);  
  h2_RecY_SimY_DT_St3 = fs->make<TH2F>( "RecY_SimY_DT_St3", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - Station 3 - DT", 2000, -10, 10, 2000, -10, 10);  
  h2_RecY_SimY_DT_St4 = fs->make<TH2F>( "RecY_SimY_DT_St4", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - Station 4 - DT", 2000, -10, 10, 2000, -10, 10);

  h2_RecX_SimX_08 = fs->make<TH2F>( "RecX_SimX_08",   "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 2000, -10, 10, 2000, -10, 10);   
  h2_RecX_SimX_12 = fs->make<TH2F>( "RecX_SimX_12", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 2000, -10, 10, 2000, -10, 10);    
  h2_RecX_SimX_20 = fs->make<TH2F>( "RecX_SimX_20", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 2000, -10, 10, 2000, -10, 10);    
  h2_RecX_SimX_24 = fs->make<TH2F>( "RecX_SimX_24", "X_{Rec}^{Loc} Vs X_{Sim}^{Loc} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 2000, -10, 10, 2000, -10, 10);

  h2_RecY_SimY_08 = fs->make<TH2F>( "RecY_SimY_08",   "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 2000, -10, 10, 2000, -10, 10);      
  h2_RecY_SimY_12 = fs->make<TH2F>( "RecY_SimY_12", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 2000, -10, 10, 2000, -10, 10);      
  h2_RecY_SimY_20 = fs->make<TH2F>( "RecY_SimY_20", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 2000, -10, 10, 2000, -10, 10);      
  h2_RecY_SimY_24 = fs->make<TH2F>( "RecY_SimY_24", "Y_{Rec}^{Loc} Vs Y_{Sim}^{Loc} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 2000, -10, 10, 2000, -10, 10);

  //Plot Direzione Segmento
  h1_DeltadX_CSC_St1 = fs->make<TH1F>( "DeltadX_CSC_St1", "#Delta(#frac{dX}{dZ}) - Station 1 - CSC", 10000, -5, 5);
  h1_DeltadX_CSC_St2 = fs->make<TH1F>( "DeltadX_CSC_St2", "#Delta(#frac{dX}{dZ}) - Station 2 - CSC", 10000, -5, 5);
  h1_DeltadX_CSC_St3 = fs->make<TH1F>( "DeltadX_CSC_St3", "#Delta(#frac{dX}{dZ}) - Station 3 - CSC", 10000, -5, 5);
  h1_DeltadX_CSC_St4 = fs->make<TH1F>( "DeltadX_CSC_St4", "#Delta(#frac{dX}{dZ}) - Station 4 - CSC", 10000, -5, 5);

  h1_DeltadY_CSC_St1 = fs->make<TH1F>( "DeltadY_CSC_St1", "#Delta(#frac{dY}{dZ}) - Station 1 - CSC", 10000, -5, 5);
  h1_DeltadY_CSC_St2 = fs->make<TH1F>( "DeltadY_CSC_St2", "#Delta(#frac{dY}{dZ}) - Station 2 - CSC", 10000, -5, 5);
  h1_DeltadY_CSC_St3 = fs->make<TH1F>( "DeltadY_CSC_St3", "#Delta(#frac{dY}{dZ}) - Station 3 - CSC", 10000, -5, 5);
  h1_DeltadY_CSC_St4 = fs->make<TH1F>( "DeltadY_CSC_St4", "#Delta(#frac{dY}{dZ}) - Station 4 - CSC", 10000, -5, 5);

  h1_DeltadX_DT_St1 = fs->make<TH1F>( "DeltadX_DT_St1", "#Delta(#frac{dX}{dZ}) - Station 1 - DT", 10000, -5, 5);
  h1_DeltadX_DT_St2 = fs->make<TH1F>( "DeltadX_DT_St2", "#Delta(#frac{dX}{dZ}) - Station 2 - DT", 10000, -5, 5);
  h1_DeltadX_DT_St3 = fs->make<TH1F>( "DeltadX_DT_St3", "#Delta(#frac{dX}{dZ}) - Station 3 - DT", 10000, -5, 5);
  h1_DeltadX_DT_St4 = fs->make<TH1F>( "DeltadX_DT_St4", "#Delta(#frac{dX}{dZ}) - Station 4 - DT", 10000, -5, 5);

  h1_DeltadY_DT_St1 = fs->make<TH1F>( "DeltadY_DT_St1", "#Delta(#frac{dY}{dZ}) - Station 1 - DT", 10000, -5, 5);
  h1_DeltadY_DT_St2 = fs->make<TH1F>( "DeltadY_DT_St2", "#Delta(#frac{dY}{dZ}) - Station 2 - DT", 10000, -5, 5);
  h1_DeltadY_DT_St3 = fs->make<TH1F>( "DeltadY_DT_St3", "#Delta(#frac{dY}{dZ}) - Station 3 - DT", 10000, -5, 5);
  h1_DeltadY_DT_St4 = fs->make<TH1F>( "DeltadY_DT_St4", "#Delta(#frac{dY}{dZ}) - Station 4 - DT", 10000, -5, 5);

  h1_DeltadX_08 = fs->make<TH1F>( "DeltadX_08",   "#Delta(#frac{dX}{dZ}) - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 10000, -5, 5);
  h1_DeltadX_12 = fs->make<TH1F>( "DeltadX_12", "#Delta(#frac{dX}{dZ}) - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 10000, -5, 5);
  h1_DeltadX_20 = fs->make<TH1F>( "DeltadX_20", "#Delta(#frac{dX}{dZ}) - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 10000, -5, 5);
  h1_DeltadX_24 = fs->make<TH1F>( "DeltadX_24", "#Delta(#frac{dX}{dZ}) - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 10000, -5, 5);

  h1_DeltadY_08 = fs->make<TH1F>( "DeltadY_08",   "#Delta(#frac{dY}{dZ}) - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 10000, -5, 5);
  h1_DeltadY_12 = fs->make<TH1F>( "DeltadY_12", "#Delta(#frac{dY}{dZ}) - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 10000, -5, 5);
  h1_DeltadY_20 = fs->make<TH1F>( "DeltadY_20", "#Delta(#frac{dY}{dZ}) - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 10000, -5, 5);
  h1_DeltadY_24 = fs->make<TH1F>( "DeltadY_24", "#Delta(#frac{dY}{dZ}) - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 10000, -5, 5);

  h2_RecdX_SimdX_CSC_St1 = fs->make<TH2F>( "RecdX_SimdX_CSC_St1", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - Station 1 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_CSC_St2 = fs->make<TH2F>( "RecdX_SimdX_CSC_St2", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - Station 2 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_CSC_St3 = fs->make<TH2F>( "RecdX_SimdX_CSC_St3", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - Station 3 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_CSC_St4 = fs->make<TH2F>( "RecdX_SimdX_CSC_St4", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - Station 4 - CSC", 1000, -5, 5, 1000, -5, 5);

  h2_RecdY_SimdY_CSC_St1 = fs->make<TH2F>( "RecdY_SimdY_CSC_St1", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 1 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_CSC_St2 = fs->make<TH2F>( "RecdY_SimdY_CSC_St2", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 2 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_CSC_St3 = fs->make<TH2F>( "RecdY_SimdY_CSC_St3", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 3 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_CSC_St4 = fs->make<TH2F>( "RecdY_SimdY_CSC_St4", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 4 - CSC", 1000, -5, 5, 1000, -5, 5);

  h2_RecdX_SimdX_DT_St1 = fs->make<TH2F>( "RecdX_SimdX_DT_St1", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - Station 1 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_DT_St2 = fs->make<TH2F>( "RecdX_SimdX_DT_St2", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - Station 2 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_DT_St3 = fs->make<TH2F>( "RecdX_SimdX_DT_St3", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - Station 3 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_DT_St4 = fs->make<TH2F>( "RecdX_SimdX_DT_St4", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - Station 4 - DT", 1000, -5, 5, 1000, -5, 5);
  
  h2_RecdY_SimdY_DT_St1 = fs->make<TH2F>( "RecdY_SimdY_DT_St1", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 1 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_DT_St2 = fs->make<TH2F>( "RecdY_SimdY_DT_St2", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 2 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_DT_St3 = fs->make<TH2F>( "RecdY_SimdY_DT_St3", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 3 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_DT_St4 = fs->make<TH2F>( "RecdY_SimdY_DT_St4", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 4 - DT", 1000, -5, 5, 1000, -5, 5);

  h2_RecdX_SimdX_08 = fs->make<TH2F>( "RecdX_SimdX_08",   "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_12 = fs->make<TH2F>( "RecdX_SimdX_12", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_20 = fs->make<TH2F>( "RecdX_SimdX_20", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_SimdX_24 = fs->make<TH2F>( "RecdX_SimdX_24", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dX}{dZ})_{Sim}^{Loc} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 1000, -5, 5, 1000, -5, 5);

  h2_RecdY_SimdY_08 = fs->make<TH2F>( "RecdY_SimdY_08",   "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_12 = fs->make<TH2F>( "RecdY_SimdY_12", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_20 = fs->make<TH2F>( "RecdY_SimdY_20", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 1000, -5, 5, 1000, -5, 5);
  h2_RecdY_SimdY_24 = fs->make<TH2F>( "RecdY_SimdY_24", "(#frac{dY}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 1000, -5, 5, 1000, -5, 5);

  h2_RecX_RecY_DT_St1 = fs->make<TH2F>( "RecX_RecY_DT_St1", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - Station 1 - DT", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_DT_St2 = fs->make<TH2F>( "RecX_RecY_DT_St2", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - Station 2 - DT", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_DT_St3 = fs->make<TH2F>( "RecX_RecY_DT_St3", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - Station 3 - DT", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_DT_St4 = fs->make<TH2F>( "RecX_RecY_DT_St4", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - Station 4 - DT", 2000, -100, 100, 2000, -100, 100);

  h2_SimX_SimY_DT_St1 = fs->make<TH2F>( "SimX_SimY_DT_St1", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - Station 1 - DT", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_DT_St2 = fs->make<TH2F>( "SimX_SimY_DT_St2", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - Station 2 - DT", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_DT_St3 = fs->make<TH2F>( "SimX_SimY_DT_St3", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - Station 3 - DT", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_DT_St4 = fs->make<TH2F>( "SimX_SimY_DT_St4", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - Station 4 - DT", 2000, -100, 100, 2000, -100, 100);

  h2_RecX_RecY_CSC_St1 = fs->make<TH2F>( "RecX_RecY_CSC_St1", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - Station 1 - CSC", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_CSC_St2 = fs->make<TH2F>( "RecX_RecY_CSC_St2", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - Station 2 - CSC", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_CSC_St3 = fs->make<TH2F>( "RecX_RecY_CSC_St3", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - Station 3 - CSC", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_CSC_St4 = fs->make<TH2F>( "RecX_RecY_CSC_St4", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - Station 4 - CSC", 2000, -100, 100, 2000, -100, 100);

  h2_SimX_SimY_CSC_St1 = fs->make<TH2F>( "SimX_SimY_CSC_St1", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - Station 1 - CSC", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_CSC_St2 = fs->make<TH2F>( "SimX_SimY_CSC_St2", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - Station 2 - CSC", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_CSC_St3 = fs->make<TH2F>( "SimX_SimY_CSC_St3", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - Station 3 - CSC", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_CSC_St4 = fs->make<TH2F>( "SimX_SimY_CSC_St4", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - Station 4 - CSC", 2000, -100, 100, 2000, -100, 100);

  h2_RecX_RecY_08 = fs->make<TH2F>( "RecX_RecY_08",   "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_12 = fs->make<TH2F>( "RecX_RecY_12", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_20 = fs->make<TH2F>( "RecX_RecY_20", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_24 = fs->make<TH2F>( "RecX_RecY_24", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 2000, -100, 100, 2000, -100, 100);

  h2_SimX_SimY_08 = fs->make<TH2F>( "SimX_SimY_08",   "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_12 = fs->make<TH2F>( "SimX_SimY_12", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_20 = fs->make<TH2F>( "SimX_SimY_20", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_24 = fs->make<TH2F>( "SimX_SimY_24", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 2000, -100, 100, 2000, -100, 100);

  h2_RecdX_RecdY_DT_St1 = fs->make<TH2F>( "RecdX_RecdY_DT_St1", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - Station 1 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_RecdY_DT_St2 = fs->make<TH2F>( "RecdX_RecdY_DT_St2", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - Station 2 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_RecdY_DT_St3 = fs->make<TH2F>( "RecdX_RecdY_DT_St3", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - Station 3 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_RecdY_DT_St4 = fs->make<TH2F>( "RecdX_RecdY_DT_St4", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - Station 4 - DT", 1000, -5, 5, 1000, -5, 5);

  h2_SimdX_SimdY_DT_St1 = fs->make<TH2F>( "SimdX_SimdY_DT_St1", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 1 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_DT_St2 = fs->make<TH2F>( "SimdX_SimdY_DT_St2", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 2 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_DT_St3 = fs->make<TH2F>( "SimdX_SimdY_DT_St3", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 3 - DT", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_DT_St4 = fs->make<TH2F>( "SimdX_SimdY_DT_St4", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 4 - DT", 1000, -5, 5, 1000, -5, 5);

  h2_RecdX_RecdY_CSC_St1 = fs->make<TH2F>( "RecdX_RecdY_CSC_St1", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - Station 1 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_RecdY_CSC_St2 = fs->make<TH2F>( "RecdX_RecdY_CSC_St2", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - Station 2 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_RecdY_CSC_St3 = fs->make<TH2F>( "RecdX_RecdY_CSC_St3", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - Station 3 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_RecdY_CSC_St4 = fs->make<TH2F>( "RecdX_RecdY_CSC_St4", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - Station 4 - CSC", 1000, -5, 5, 1000, -5, 5);

  h2_SimdX_SimdY_CSC_St1 = fs->make<TH2F>( "SimdX_SimdY_CSC_St1", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 1 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_CSC_St2 = fs->make<TH2F>( "SimdX_SimdY_CSC_St2", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 2 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_CSC_St3 = fs->make<TH2F>( "SimdX_SimdY_CSC_St3", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 3 - CSC", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_CSC_St4 = fs->make<TH2F>( "SimdX_SimdY_CSC_St4", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - Station 4 - CSC", 1000, -5, 5, 1000, -5, 5);

  h2_RecdX_RecdY_08 = fs->make<TH2F>( "RecdX_RecdY_08",   "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 1000, -5, 5, 1000, -5, 5); 
  h2_RecdX_RecdY_12 = fs->make<TH2F>( "RecdX_RecdY_12", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_RecdY_20 = fs->make<TH2F>( "RecdX_RecdY_20", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 1000, -5, 5, 1000, -5, 5);
  h2_RecdX_RecdY_24 = fs->make<TH2F>( "RecdX_RecdY_24", "(#frac{dX}{dZ})_{Rec}^{Loc} Vs (#frac{dY}{dZ})_{Rec}^{Loc} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 1000, -5, 5, 1000, -5, 5);

  h2_SimdX_SimdY_08 = fs->make<TH2F>( "SimdX_SimdY_08",   "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_12 = fs->make<TH2F>( "SimdX_SimdY_12", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_20 = fs->make<TH2F>( "SimdX_SimdY_20", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 1000, -5, 5, 1000, -5, 5);
  h2_SimdX_SimdY_24 = fs->make<TH2F>( "SimdX_SimdY_24", "(#frac{dX}{dZ})_{Sim}^{Loc} Vs (#frac{dY}{dZ})_{Sim}^{Loc} - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 1000, -5, 5, 1000, -5, 5);


  h1_all_DeltaX_08 = fs->make<TH1F>( "DeltaX_all_08",   "#DeltaX - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 20000, -10, 10);
  h1_all_DeltaX_12 = fs->make<TH1F>( "DeltaX_all_12", "#DeltaX - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 20000, -10, 10);
  h1_all_DeltaX_20 = fs->make<TH1F>( "DeltaX_all_20", "#DeltaX - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 20000, -10, 10);
  h1_all_DeltaX_24 = fs->make<TH1F>( "DeltaX_all_24", "#DeltaX - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 20000, -10, 10);

  h1_all_DeltaY_08 = fs->make<TH1F>( "DeltaY_all_08",   "#DeltaY - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 20000, -10, 10);
  h1_all_DeltaY_12 = fs->make<TH1F>( "DeltaY_all_12", "#DeltaY - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 20000, -10, 10);
  h1_all_DeltaY_20 = fs->make<TH1F>( "DeltaY_all_20", "#DeltaY - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 20000, -10, 10);
  h1_all_DeltaY_24 = fs->make<TH1F>( "DeltaY_all_24", "#DeltaY - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 20000, -10, 10);

  h1_all_DeltadX_08 = fs->make<TH1F>( "DeltadX_all_08",   "#Delta(#frac{dX}{dZ}) - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 10000, -5, 5);
  h1_all_DeltadX_12 = fs->make<TH1F>( "DeltadX_all_12", "#Delta(#frac{dX}{dZ}) - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 10000, -5, 5);
  h1_all_DeltadX_20 = fs->make<TH1F>( "DeltadX_all_20", "#Delta(#frac{dX}{dZ}) - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 10000, -5, 5);
  h1_all_DeltadX_24 = fs->make<TH1F>( "DeltadX_all_24", "#Delta(#frac{dX}{dZ}) - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 10000, -5, 5);

  h1_all_DeltadY_08 = fs->make<TH1F>( "DeltadY_all_08",   "#Delta(#frac{dY}{dZ}) - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 10000, -5, 5);
  h1_all_DeltadY_12 = fs->make<TH1F>( "DeltadY_all_12", "#Delta(#frac{dY}{dZ}) - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 10000, -5, 5);
  h1_all_DeltadY_20 = fs->make<TH1F>( "DeltadY_all_20", "#Delta(#frac{dY}{dZ}) - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 10000, -5, 5);
  h1_all_DeltadY_24 = fs->make<TH1F>( "DeltadY_all_24", "#Delta(#frac{dY}{dZ}) - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 10000, -5, 5);

  h1_all_Nseg_08 = fs->make<TH1F>( "NumSeg_Rec_08",   "Num.Seg - 0 < #lbar #eta_{Rec} #cbar <= 0.8", 200, 0, 200);
  h1_all_Nseg_12 = fs->make<TH1F>( "NumSeg_Rec_12", "Num.Seg - 0.8 < #lbar #eta_{Rec} #cbar <= 1.2", 200, 0, 200);
  h1_all_Nseg_20 = fs->make<TH1F>( "NumSeg_Rec_20", "Num.Seg - 1.2 < #lbar #eta_{Rec} #cbar <= 2.0", 200, 0, 200);
  h1_all_Nseg_24 = fs->make<TH1F>( "NumSeg_Rec_24", "Num.Seg - 2.0 < #lbar #eta_{Rec} #cbar <= 2.4", 200, 0, 200);

  //Debug distributions
  h1_RecX_DT_St1_Wh0 = fs->make<TH1F>( "RecX_DT_St1_Wh0",   "X_{Rec}^{Loc}, Station = 1, Wheel = 0", 4000, -200, 200);
  h1_RecX_DT_St1_Wh1 = fs->make<TH1F>( "RecX_DT_St1_Wh1",   "X_{Rec}^{Loc}, Station = 1, Wheel = 1", 4000, -200, 200);
  h1_RecX_DT_St1_Wh2 = fs->make<TH1F>( "RecX_DT_St1_Wh2",   "X_{Rec}^{Loc}, Station = 1, Wheel = 2", 4000, -200, 200);
  h1_RecX_DT_St2_Wh0 = fs->make<TH1F>( "RecX_DT_St2_Wh0",   "X_{Rec}^{Loc}, Station = 2, Wheel = 0", 4000, -200, 200);
  h1_RecX_DT_St2_Wh1 = fs->make<TH1F>( "RecX_DT_St2_Wh1",   "X_{Rec}^{Loc}, Station = 2, Wheel = 1", 4000, -200, 200);
  h1_RecX_DT_St2_Wh2 = fs->make<TH1F>( "RecX_DT_St2_Wh2",   "X_{Rec}^{Loc}, Station = 2, Wheel = 2", 4000, -200, 200);

  h1_RecX_DT_St3_Wh0 = fs->make<TH1F>( "RecX_DT_St3_Wh0",   "X_{Rec}^{Loc}, Station = 3, Wheel = 0", 4000, -200, 200);
  h1_RecX_DT_St3_Wh1 = fs->make<TH1F>( "RecX_DT_St3_Wh1",   "X_{Rec}^{Loc}, Station = 3, Wheel = 1", 4000, -200, 200);
  h1_RecX_DT_St3_Wh2 = fs->make<TH1F>( "RecX_DT_St3_Wh2",   "X_{Rec}^{Loc}, Station = 3, Wheel = 2", 4000, -200, 200);

  h1_RecX_DT_St4_Wh0 = fs->make<TH1F>( "RecX_DT_St4_Wh0",   "X_{Rec}^{Loc}, Station = 4, Wheel = 0", 4000, -200, 200);
  h1_RecX_DT_St4_Wh1 = fs->make<TH1F>( "RecX_DT_St4_Wh1",   "X_{Rec}^{Loc}, Station = 4, Wheel = 1", 4000, -200, 200);
  h1_RecX_DT_St4_Wh2 = fs->make<TH1F>( "RecX_DT_St4_Wh2",   "X_{Rec}^{Loc}, Station = 4, Wheel = 2", 4000, -200, 200);

  h1_RecX_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "RecX_DT_PtCut_St1_Wh0",   "X_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 0", 4000, -200, 200);
  h1_RecX_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "RecX_DT_PtCut_St1_Wh1",   "X_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 1", 4000, -200, 200);
  h1_RecX_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "RecX_DT_PtCut_St1_Wh2",   "X_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 2", 4000, -200, 200);
      
  h1_RecX_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "RecX_DT_PtCut_St2_Wh0",   "X_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 0", 4000, -200, 200);
  h1_RecX_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "RecX_DT_PtCut_St2_Wh1",   "X_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 1", 4000, -200, 200);
  h1_RecX_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "RecX_DT_PtCut_St2_Wh2",   "X_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 2", 4000, -200, 200);
      
  h1_RecX_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "RecX_DT_PtCut_St3_Wh0",   "X_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 0", 4000, -200, 200);
  h1_RecX_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "RecX_DT_PtCut_St3_Wh1",   "X_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 1", 4000, -200, 200);
  h1_RecX_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "RecX_DT_PtCut_St3_Wh2",   "X_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 2", 4000, -200, 200);
      
  h1_RecX_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "RecX_DT_PtCut_St4_Wh0",   "X_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 0", 4000, -200, 200);
  h1_RecX_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "RecX_DT_PtCut_St4_Wh1",   "X_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 1", 4000, -200, 200);
  h1_RecX_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "RecX_DT_PtCut_St4_Wh2",   "X_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 2", 4000, -200, 200);

  h1_RecY_DT_St1_Wh0 = fs->make<TH1F>( "RecY_DT_St1_Wh0",   "Y_{Rec}^{Loc}, Station = 1, Wheel = 0", 4000, -200, 200);
  h1_RecY_DT_St1_Wh1 = fs->make<TH1F>( "RecY_DT_St1_Wh1",   "Y_{Rec}^{Loc}, Station = 1, Wheel = 1", 4000, -200, 200);
  h1_RecY_DT_St1_Wh2 = fs->make<TH1F>( "RecY_DT_St1_Wh2",   "Y_{Rec}^{Loc}, Station = 1, Wheel = 2", 4000, -200, 200);

  h1_RecY_DT_St2_Wh0 = fs->make<TH1F>( "RecY_DT_St2_Wh0",   "Y_{Rec}^{Loc}, Station = 2, Wheel = 0", 4000, -200, 200);
  h1_RecY_DT_St2_Wh1 = fs->make<TH1F>( "RecY_DT_St2_Wh1",   "Y_{Rec}^{Loc}, Station = 2, Wheel = 1", 4000, -200, 200);
  h1_RecY_DT_St2_Wh2 = fs->make<TH1F>( "RecY_DT_St2_Wh2",   "Y_{Rec}^{Loc}, Station = 2, Wheel = 2", 4000, -200, 200);

  h1_RecY_DT_St3_Wh0 = fs->make<TH1F>( "RecY_DT_St3_Wh0",   "Y_{Rec}^{Loc}, Station = 3, Wheel = 0", 4000, -200, 200);
  h1_RecY_DT_St3_Wh1 = fs->make<TH1F>( "RecY_DT_St3_Wh1",   "Y_{Rec}^{Loc}, Station = 3, Wheel = 1", 4000, -200, 200);
  h1_RecY_DT_St3_Wh2 = fs->make<TH1F>( "RecY_DT_St3_Wh2",   "Y_{Rec}^{Loc}, Station = 3, Wheel = 2", 4000, -200, 200);

  h1_RecY_DT_St4_Wh0 = fs->make<TH1F>( "RecY_DT_St4_Wh0",   "Y_{Rec}^{Loc}, Station = 4, Wheel = 0", 4000, -200, 200);
  h1_RecY_DT_St4_Wh1 = fs->make<TH1F>( "RecY_DT_St4_Wh1",   "Y_{Rec}^{Loc}, Station = 4, Wheel = 1", 4000, -200, 200);
  h1_RecY_DT_St4_Wh2 = fs->make<TH1F>( "RecY_DT_St4_Wh2",   "Y_{Rec}^{Loc}, Station = 4, Wheel = 2", 4000, -200, 200);

  h1_RecY_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "RecY_DT_PtCut_St1_Wh0",   "Y_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 0", 4000, -200, 200);
  h1_RecY_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "RecY_DT_PtCut_St1_Wh1",   "Y_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 1", 4000, -200, 200);
  h1_RecY_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "RecY_DT_PtCut_St1_Wh2",   "Y_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 2", 4000, -200, 200);

  h1_RecY_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "RecY_DT_PtCut_St2_Wh0",   "Y_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 0", 4000, -200, 200);
  h1_RecY_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "RecY_DT_PtCut_St2_Wh1",   "Y_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 1", 4000, -200, 200);
  h1_RecY_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "RecY_DT_PtCut_St2_Wh2",   "Y_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 2", 4000, -200, 200);

  h1_RecY_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "RecY_DT_PtCut_St3_Wh0",   "Y_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 0", 4000, -200, 200);
  h1_RecY_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "RecY_DT_PtCut_St3_Wh1",   "Y_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 1", 4000, -200, 200);
  h1_RecY_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "RecY_DT_PtCut_St3_Wh2",   "Y_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 2", 4000, -200, 200);

  h1_RecY_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "RecY_DT_PtCut_St4_Wh0",   "Y_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 0", 4000, -200, 200);
  h1_RecY_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "RecY_DT_PtCut_St4_Wh1",   "Y_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 1", 4000, -200, 200);
  h1_RecY_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "RecY_DT_PtCut_St4_Wh2",   "Y_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 2", 4000, -200, 200);

  h1_RecX_CSC_St1_Rg1 = fs->make<TH1F>( "RecX_CSC_St1_Rg1",  "X_{Rec}^{Loc}, Station = 1, Ring  = 1", 4000, -200, 200);
  h1_RecX_CSC_St1_Rg2 = fs->make<TH1F>( "RecX_CSC_St1_Rg2",  "X_{Rec}^{Loc}, Station = 1, Ring  = 2", 4000, -200, 200);
  h1_RecX_CSC_St1_Rg3 = fs->make<TH1F>( "RecX_CSC_St1_Rg3",  "X_{Rec}^{Loc}, Station = 1, Ring  = 3", 4000, -200, 200);

  h1_RecX_CSC_St2_Rg1 = fs->make<TH1F>( "RecX_CSC_St2_Rg1",  "X_{Rec}^{Loc}, Station = 2, Ring  = 1", 4000, -200, 200);
  h1_RecX_CSC_St2_Rg2 = fs->make<TH1F>( "RecX_CSC_St2_Rg2",  "X_{Rec}^{Loc}, Station = 2, Ring  = 2", 4000, -200, 200);

  h1_RecX_CSC_St3_Rg1 = fs->make<TH1F>( "RecX_CSC_St3_Rg1",  "X_{Rec}^{Loc}, Station = 3, Ring  = 1", 4000, -200, 200);
  h1_RecX_CSC_St3_Rg2 = fs->make<TH1F>( "RecX_CSC_St3_Rg2",  "X_{Rec}^{Loc}, Station = 3, Ring  = 2", 4000, -200, 200);

  h1_RecX_CSC_St4_Rg1 = fs->make<TH1F>( "RecX_CSC_St4_Rg1",  "X_{Rec}^{Loc}, Station = 4, Ring  = 1", 4000, -200, 200);
  h1_RecX_CSC_St4_Rg2 = fs->make<TH1F>( "RecX_CSC_St4_Rg2",  "X_{Rec}^{Loc}, Station = 4, Ring  = 2", 4000, -200, 200);

  h1_RecX_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "RecX_CSC_PtCut_St1_Rg1",  "X_{Rec}^{Loc}, Pt Cut, Station = 1, Ring  = 1", 4000, -200, 200);
  h1_RecX_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "RecX_CSC_PtCut_St1_Rg2",  "X_{Rec}^{Loc}, Pt Cut, Station = 1, Ring  = 2", 4000, -200, 200);
  h1_RecX_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "RecX_CSC_PtCut_St1_Rg3",  "X_{Rec}^{Loc}, Pt Cut, Station = 1, Ring  = 3", 4000, -200, 200);

  h1_RecX_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "RecX_CSC_PtCut_St2_Rg1",  "X_{Rec}^{Loc}, Pt Cut, Station = 2, Ring  = 1", 4000, -200, 200);
  h1_RecX_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "RecX_CSC_PtCut_St2_Rg2",  "X_{Rec}^{Loc}, Pt Cut, Station = 2, Ring  = 2", 4000, -200, 200);

  h1_RecX_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "RecX_CSC_PtCut_St3_Rg1",  "X_{Rec}^{Loc}, Pt Cut, Station = 3, Ring  = 1", 4000, -200, 200);
  h1_RecX_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "RecX_CSC_PtCut_St3_Rg2",  "X_{Rec}^{Loc}, Pt Cut, Station = 3, Ring  = 2", 4000, -200, 200);

  h1_RecX_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "RecX_CSC_PtCut_St4_Rg1",  "X_{Rec}^{Loc}, Pt Cut, Station = 4, Ring  = 1", 4000, -200, 200);
  h1_RecX_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "RecX_CSC_PtCut_St4_Rg2",  "X_{Rec}^{Loc}, Pt Cut, Station = 4, Ring  = 2", 4000, -200, 200);

  h1_RecY_CSC_St1_Rg1 = fs->make<TH1F>( "RecY_CSC_St1_Rg1",  "Y_{Rec}^{Loc}, Station = 1, Ring  = 1", 4000, -200, 200);
  h1_RecY_CSC_St1_Rg2 = fs->make<TH1F>( "RecY_CSC_St1_Rg2",  "Y_{Rec}^{Loc}, Station = 1, Ring  = 2", 4000, -200, 200);
  h1_RecY_CSC_St1_Rg3 = fs->make<TH1F>( "RecY_CSC_St1_Rg3",  "Y_{Rec}^{Loc}, Station = 1, Ring  = 3", 4000, -200, 200);

  h1_RecY_CSC_St2_Rg1 = fs->make<TH1F>( "RecY_CSC_St2_Rg1",  "Y_{Rec}^{Loc}, Station = 2, Ring  = 1", 4000, -200, 200);
  h1_RecY_CSC_St2_Rg2 = fs->make<TH1F>( "RecY_CSC_St2_Rg2",  "Y_{Rec}^{Loc}, Station = 2, Ring  = 2", 4000, -200, 200);

  h1_RecY_CSC_St3_Rg1 = fs->make<TH1F>( "RecY_CSC_St3_Rg1",  "Y_{Rec}^{Loc}, Station = 3, Ring  = 1", 4000, -200, 200);
  h1_RecY_CSC_St3_Rg2 = fs->make<TH1F>( "RecY_CSC_St3_Rg2",  "Y_{Rec}^{Loc}, Station = 3, Ring  = 2", 4000, -200, 200);

  h1_RecY_CSC_St4_Rg1 = fs->make<TH1F>( "RecY_CSC_St4_Rg1",  "Y_{Rec}^{Loc}, Station = 4, Ring  = 1", 4000, -200, 200);
  h1_RecY_CSC_St4_Rg2 = fs->make<TH1F>( "RecY_CSC_St4_Rg2",  "Y_{Rec}^{Loc}, Station = 4, Ring  = 2", 4000, -200, 200);

  h1_RecY_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "RecY_CSC_PtCut_St1_Rg1",  "Y_{Rec}^{Loc}, Pt Cut, Station = 1, Ring  = 1", 4000, -200, 200);
  h1_RecY_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "RecY_CSC_PtCut_St1_Rg2",  "Y_{Rec}^{Loc}, Pt Cut, Station = 1, Ring  = 2", 4000, -200, 200);
  h1_RecY_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "RecY_CSC_PtCut_St1_Rg3",  "Y_{Rec}^{Loc}, Pt Cut, Station = 1, Ring  = 3", 4000, -200, 200);

  h1_RecY_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "RecY_CSC_PtCut_St2_Rg1",  "Y_{Rec}^{Loc}, Pt Cut, Station = 2, Ring  = 1", 4000, -200, 200);
  h1_RecY_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "RecY_CSC_PtCut_St2_Rg2",  "Y_{Rec}^{Loc}, Pt Cut, Station = 2, Ring  = 2", 4000, -200, 200);

  h1_RecY_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "RecY_CSC_PtCut_St3_Rg1",  "Y_{Rec}^{Loc}, Pt Cut, Station = 3, Ring  = 1", 4000, -200, 200);
  h1_RecY_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "RecY_CSC_PtCut_St3_Rg2",  "Y_{Rec}^{Loc}, Pt Cut, Station = 3, Ring  = 2", 4000, -200, 200);

  h1_RecY_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "RecY_CSC_PtCut_St4_Rg1",  "Y_{Rec}^{Loc}, Pt Cut, Station = 4, Ring  = 1", 4000, -200, 200);
  h1_RecY_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "RecY_CSC_PtCut_St4_Rg2",  "Y_{Rec}^{Loc}, Pt Cut, Station = 4, Ring  = 2", 4000, -200, 200);
     
  //Histo related to resolution
  h1_ResRecX_DT_St1_Wh0 = fs->make<TH1F>( "RecResX_DT_St1_Wh0", "#DeltaX/#deltaX, Station = 1, Wheel = 0", 600, -15, 15);
  h1_ResRecX_DT_St1_Wh1 = fs->make<TH1F>( "RecResX_DT_St1_Wh1", "#DeltaX/#deltaX, Station = 1, Wheel = 1", 600, -15, 15);
  h1_ResRecX_DT_St1_Wh2 = fs->make<TH1F>( "RecResX_DT_St1_Wh2", "#DeltaX/#deltaX, Station = 1, Wheel = 2", 600, -15, 15);

  h1_ResRecX_DT_St2_Wh0 = fs->make<TH1F>( "RecResX_DT_St2_Wh0", "#DeltaX/#deltaX, Station = 2, Wheel = 0", 600, -15, 15);
  h1_ResRecX_DT_St2_Wh1 = fs->make<TH1F>( "RecResX_DT_St2_Wh1", "#DeltaX/#deltaX, Station = 2, Wheel = 1", 600, -15, 15);
  h1_ResRecX_DT_St2_Wh2 = fs->make<TH1F>( "RecResX_DT_St2_Wh2", "#DeltaX/#deltaX, Station = 2, Wheel = 2", 600, -15, 15);

  h1_ResRecX_DT_St3_Wh0 = fs->make<TH1F>( "RecResX_DT_St3_Wh0", "#DeltaX/#deltaX, Station = 3, Wheel = 0", 600, -15, 15);
  h1_ResRecX_DT_St3_Wh1 = fs->make<TH1F>( "RecResX_DT_St3_Wh1", "#DeltaX/#deltaX, Station = 3, Wheel = 1", 600, -15, 15);
  h1_ResRecX_DT_St3_Wh2 = fs->make<TH1F>( "RecResX_DT_St3_Wh2", "#DeltaX/#deltaX, Station = 3, Wheel = 2", 600, -15, 15);

  h1_ResRecX_DT_St4_Wh0 = fs->make<TH1F>( "RecResX_DT_St4_Wh0", "#DeltaX/#deltaX, Station = 4, Wheel = 0", 600, -15, 15);
  h1_ResRecX_DT_St4_Wh1 = fs->make<TH1F>( "RecResX_DT_St4_Wh1", "#DeltaX/#deltaX, Station = 4, Wheel = 1", 600, -15, 15);
  h1_ResRecX_DT_St4_Wh2 = fs->make<TH1F>( "RecResX_DT_St4_Wh2", "#DeltaX/#deltaX, Station = 4, Wheel = 2",  600, -15, 15);

  h1_ResRecX_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "RecResX_DT_PtCut_St1_Wh0", "#DeltaX/#deltaX, Pt Cut, Station = 1, Wheel = 0", 600, -15, 15);
  h1_ResRecX_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "RecResX_DT_PtCut_St1_Wh1", "#DeltaX/#deltaX, Pt Cut, Station = 1, Wheel = 1", 600, -15, 15);
  h1_ResRecX_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "RecResX_DT_PtCut_St1_Wh2", "#DeltaX/#deltaX, Pt Cut, Station = 1, Wheel = 2", 600, -15, 15);

  h1_ResRecX_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "RecResX_DT_PtCut_St2_Wh0", "#DeltaX/#deltaX, Pt Cut, Station = 2, Wheel = 0", 600, -15, 15);
  h1_ResRecX_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "RecResX_DT_PtCut_St2_Wh1", "#DeltaX/#deltaX, Pt Cut, Station = 2, Wheel = 1", 600, -15, 15);
  h1_ResRecX_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "RecResX_DT_PtCut_St2_Wh2", "#DeltaX/#deltaX, Pt Cut, Station = 2, Wheel = 2", 600, -15, 15);

  h1_ResRecX_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "RecResX_DT_PtCut_St3_Wh0", "#DeltaX/#deltaX, Pt Cut, Station = 3, Wheel = 0", 600, -15, 15);
  h1_ResRecX_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "RecResX_DT_PtCut_St3_Wh1", "#DeltaX/#deltaX, Pt Cut, Station = 3, Wheel = 1", 600, -15, 15);
  h1_ResRecX_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "RecResX_DT_PtCut_St3_Wh2", "#DeltaX/#deltaX, Pt Cut, Station = 3, Wheel = 2", 600, -15, 15);

  h1_ResRecX_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "RecResX_DT_PtCut_St4_Wh0", "#DeltaX/#deltaX, Pt Cut, Station = 4, Wheel = 0", 600, -15, 15);
  h1_ResRecX_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "RecResX_DT_PtCut_St4_Wh1", "#DeltaX/#deltaX, Pt Cut, Station = 4, Wheel = 1", 600, -15, 15);
  h1_ResRecX_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "RecResX_DT_PtCut_St4_Wh2", "#DeltaX/#deltaX, Pt Cut, Station = 4, Wheel = 2", 600, -15, 15);

  h1_ResRecY_DT_St1_Wh0 = fs->make<TH1F>( "RecResY_DT_St1_Wh0", "#DeltaY/#deltaY, Station = 1, Wheel = 0", 600, -15, 15);
  h1_ResRecY_DT_St1_Wh1 = fs->make<TH1F>( "RecResY_DT_St1_Wh1", "#DeltaY/#deltaY, Station = 1, Wheel = 1", 600, -15, 15);
  h1_ResRecY_DT_St1_Wh2 = fs->make<TH1F>( "RecResY_DT_St1_Wh2", "#DeltaY/#deltaY, Station = 1, Wheel = 2", 600, -15, 15);

  h1_ResRecY_DT_St2_Wh0 = fs->make<TH1F>( "RecResY_DT_St2_Wh0", "#DeltaY/#deltaY, Station = 2, Wheel = 0", 600, -15, 15);
  h1_ResRecY_DT_St2_Wh1 = fs->make<TH1F>( "RecResY_DT_St2_Wh1", "#DeltaY/#deltaY, Station = 2, Wheel = 1", 600, -15, 15);
  h1_ResRecY_DT_St2_Wh2 = fs->make<TH1F>( "RecResY_DT_St2_Wh2", "#DeltaY/#deltaY, Station = 2, Wheel = 2", 600, -15, 15);

  h1_ResRecY_DT_St3_Wh0 = fs->make<TH1F>( "RecResY_DT_St3_Wh0", "#DeltaY/#deltaY, Station = 3, Wheel = 0", 600, -15, 15);
  h1_ResRecY_DT_St3_Wh1 = fs->make<TH1F>( "RecResY_DT_St3_Wh1", "#DeltaY/#deltaY, Station = 3, Wheel = 1", 600, -15, 15);
  h1_ResRecY_DT_St3_Wh2 = fs->make<TH1F>( "RecResY_DT_St3_Wh2", "#DeltaY/#deltaY, Station = 3, Wheel = 2", 600, -15, 15);

  h1_ResRecY_DT_St4_Wh0 = fs->make<TH1F>( "RecResY_DT_St4_Wh0", "#DeltaY/#deltaY, Station = 4, Wheel = 0", 600, -15, 15);
  h1_ResRecY_DT_St4_Wh1 = fs->make<TH1F>( "RecResY_DT_St4_Wh1", "#DeltaY/#deltaY, Station = 4, Wheel = 1", 600, -15, 15);
  h1_ResRecY_DT_St4_Wh2 = fs->make<TH1F>( "RecResY_DT_St4_Wh2", "#DeltaY/#deltaY, Station = 4, Wheel = 2", 600, -15, 15);

  h1_ResRecY_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "RecResY_DT_PtCut_St1_Wh0", "#DeltaY/#deltaY, Pt Cut, Station = 1, Wheel = 0", 600, -15, 15); 
  h1_ResRecY_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "RecResY_DT_PtCut_St1_Wh1", "#DeltaY/#deltaY, Pt Cut, Station = 1, Wheel = 1", 600, -15, 15);
  h1_ResRecY_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "RecResY_DT_PtCut_St1_Wh2", "#DeltaY/#deltaY, Pt Cut, Station = 1, Wheel = 2", 600, -15, 15);

  h1_ResRecY_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "RecResY_DT_PtCut_St2_Wh0", "#DeltaY/#deltaY, Pt Cut, Station = 2, Wheel = 0", 600, -15, 15);
  h1_ResRecY_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "RecResY_DT_PtCut_St2_Wh1", "#DeltaY/#deltaY, Pt Cut, Station = 2, Wheel = 1", 600, -15, 15);
  h1_ResRecY_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "RecResY_DT_PtCut_St2_Wh2", "#DeltaY/#deltaY, Pt Cut, Station = 2, Wheel = 2", 600, -15, 15);

  h1_ResRecY_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "RecResY_DT_PtCut_St3_Wh0", "#DeltaY/#deltaY, Pt Cut, Station = 3, Wheel = 0", 600, -15, 15);
  h1_ResRecY_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "RecResY_DT_PtCut_St3_Wh1", "#DeltaY/#deltaY, Pt Cut, Station = 3, Wheel = 1", 600, -15, 15);
  h1_ResRecY_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "RecResY_DT_PtCut_St3_Wh2", "#DeltaY/#deltaY, Pt Cut, Station = 3, Wheel = 2", 600, -15, 15);

  h1_ResRecY_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "RecResY_DT_PtCut_St4_Wh0", "#DeltaY/#deltaY, Pt Cut, Station = 4, Wheel = 0", 600, -15, 15);
  h1_ResRecY_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "RecResY_DT_PtCut_St4_Wh1", "#DeltaY/#deltaY, Pt Cut, Station = 4, Wheel = 1", 600, -15, 15);
  h1_ResRecY_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "RecResY_DT_PtCut_St4_Wh2", "#DeltaY/#deltaY, Pt Cut, Station = 4, Wheel = 2", 600, -15, 15);

  h1_RecResX_CSC_St1_Rg1 = fs->make<TH1F>( "RecResX_CSC_St1_Rg1", "#DeltaX/#deltaX, Station = 1, Ring = 1", 600, -15, 15);
  h1_RecResX_CSC_St1_Rg2 = fs->make<TH1F>( "RecResX_CSC_St1_Rg2", "#DeltaX/#deltaX, Station = 1, Ring = 2", 600, -15, 15);
  h1_RecResX_CSC_St1_Rg3 = fs->make<TH1F>( "RecResX_CSC_St1_Rg3", "#DeltaX/#deltaX, Station = 1, Ring = 3", 600, -15, 15);

  h1_RecResX_CSC_St2_Rg1 = fs->make<TH1F>( "RecResX_CSC_St2_Rg1", "#DeltaX/#deltaX, Station = 2, Ring = 1", 600, -15, 15);
  h1_RecResX_CSC_St2_Rg2 = fs->make<TH1F>( "RecResX_CSC_St2_Rg2", "#DeltaX/#deltaX, Station = 2, Ring = 2", 600, -15, 15);

  h1_RecResX_CSC_St3_Rg1 = fs->make<TH1F>( "RecResX_CSC_St3_Rg1", "#DeltaX/#deltaX, Station = 3, Ring = 1", 600, -15, 15);
  h1_RecResX_CSC_St3_Rg2 = fs->make<TH1F>( "RecResX_CSC_St3_Rg2", "#DeltaX/#deltaX, Station = 3, Ring = 2", 600, -15, 15);

  h1_RecResX_CSC_St4_Rg1 = fs->make<TH1F>( "RecResX_CSC_St4_Rg1", "#DeltaX/#deltaX, Station = 4, Ring = 1", 600, -15, 15);
  h1_RecResX_CSC_St4_Rg2 = fs->make<TH1F>( "RecResX_CSC_St4_Rg2", "#DeltaX/#deltaX, Station = 4, Ring = 2", 600, -15, 15);

  h1_RecResX_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "RecResX_CSC_PtCut_St1_Rg1", "#DeltaX/#deltaX, Station = 1, Ring = 1", 600, -15, 15);
  h1_RecResX_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "RecResX_CSC_PtCut_St1_Rg2", "#DeltaX/#deltaX, Station = 1, Ring = 2", 600, -15, 15);
  h1_RecResX_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "RecResX_CSC_PtCut_St1_Rg3", "#DeltaX/#deltaX, Station = 1, Ring = 3", 600, -15, 15);

  h1_RecResX_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "RecResX_CSC_PtCut_St2_Rg1", "#DeltaX/#deltaX, Station = 2, Ring = 1", 600, -15, 15);
  h1_RecResX_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "RecResX_CSC_PtCut_St2_Rg2", "#DeltaX/#deltaX, Station = 2, Ring = 2", 600, -15, 15);

  h1_RecResX_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "RecResX_CSC_PtCut_St3_Rg1", "#DeltaX/#deltaX, Station = 3, Ring = 1", 600, -15, 15);
  h1_RecResX_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "RecResX_CSC_PtCut_St3_Rg2", "#DeltaX/#deltaX, Station = 3, Ring = 2", 600, -15, 15);

  h1_RecResX_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "RecResX_CSC_PtCut_St4_Rg1", "#DeltaX/#deltaX, Station = 4, Ring = 1", 600, -15, 15);
  h1_RecResX_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "RecResX_CSC_PtCut_St4_Rg2", "#DeltaX/#deltaX, Station = 4, Ring = 2", 600, -15, 15);

  h1_RecResY_CSC_St1_Rg1 = fs->make<TH1F>( "RecResY_CSC_St1_Rg1", "#DeltaY/#deltaY, Station = 1, Ring = 1", 600, -15, 15);
  h1_RecResY_CSC_St1_Rg2 = fs->make<TH1F>( "RecResY_CSC_St1_Rg2", "#DeltaY/#deltaY, Station = 1, Ring = 2", 600, -15, 15);
  h1_RecResY_CSC_St1_Rg3 = fs->make<TH1F>( "RecResY_CSC_St1_Rg3", "#DeltaY/#deltaY, Station = 1, Ring = 3", 600, -15, 15);

  h1_RecResY_CSC_St2_Rg1 = fs->make<TH1F>( "RecResY_CSC_St2_Rg1", "#DeltaY/#deltaY, Station = 2, Ring = 1", 600, -15, 15);
  h1_RecResY_CSC_St2_Rg2 = fs->make<TH1F>( "RecResY_CSC_St2_Rg2", "#DeltaY/#deltaY, Station = 2, Ring = 2", 600, -15, 15);

  h1_RecResY_CSC_St3_Rg1 = fs->make<TH1F>( "RecResY_CSC_St3_Rg1", "#DeltaY/#deltaY, Station = 3, Ring = 1", 600, -15, 15);
  h1_RecResY_CSC_St3_Rg2 = fs->make<TH1F>( "RecResY_CSC_St3_Rg2", "#DeltaY/#deltaY, Station = 3, Ring = 2", 600, -15, 15);

  h1_RecResY_CSC_St4_Rg1 = fs->make<TH1F>( "RecResY_CSC_St4_Rg1", "#DeltaY/#deltaY, Station = 4, Ring = 1", 600, -15, 15);
  h1_RecResY_CSC_St4_Rg2 = fs->make<TH1F>( "RecResY_CSC_St4_Rg2", "#DeltaY/#deltaY, Station = 4, Ring = 2", 600, -15, 15);

  h1_RecResY_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "RecResY_CSC_PtCut_St1_Rg1", "#DeltaY/#deltaY, Station = 1, Ring = 1", 600, -15, 15);
  h1_RecResY_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "RecResY_CSC_PtCut_St1_Rg2", "#DeltaY/#deltaY, Station = 1, Ring = 2", 600, -15, 15);
  h1_RecResY_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "RecResY_CSC_PtCut_St1_Rg3", "#DeltaY/#deltaY, Station = 1, Ring = 3", 600, -15, 15);
      
  h1_RecResY_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "RecResY_CSC_PtCut_St2_Rg1", "#DeltaY/#deltaY, Station = 2, Ring = 1", 600, -15, 15);
  h1_RecResY_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "RecResY_CSC_PtCut_St2_Rg2", "#DeltaY/#deltaY, Station = 2, Ring = 2", 600, -15, 15);
      
  h1_RecResY_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "RecResY_CSC_PtCut_St3_Rg1", "#DeltaY/#deltaY, Station = 3, Ring = 1", 600, -15, 15);
  h1_RecResY_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "RecResY_CSC_PtCut_St3_Rg2", "#DeltaY/#deltaY, Station = 3, Ring = 2", 600, -15, 15);
     
  h1_RecResY_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "RecResY_CSC_PtCut_St4_Rg1", "#DeltaY/#deltaY, Station = 4, Ring = 1", 600, -15, 15);
  h1_RecResY_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "RecResY_CSC_PtCut_St4_Rg2", "#DeltaY/#deltaY, Station = 4, Ring = 2", 600, -15, 15);

  //Plot related to the direction
  h1_RecdX_DT_St1_Wh0 = fs->make<TH1F>( "RecdX_DT_St1_Wh0",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 1, Wheel = 0", 1000, -5, 5);
  h1_RecdX_DT_St1_Wh1 = fs->make<TH1F>( "RecdX_DT_St1_Wh1",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 1, Wheel = 1", 1000, -5, 5);
  h1_RecdX_DT_St1_Wh2 = fs->make<TH1F>( "RecdX_DT_St1_Wh2",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 1, Wheel = 2", 1000, -5, 5);

  h1_RecdX_DT_St2_Wh0 = fs->make<TH1F>( "RecdX_DT_St2_Wh0",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 2, Wheel = 0", 1000, -5, 5);
  h1_RecdX_DT_St2_Wh1 = fs->make<TH1F>( "RecdX_DT_St2_Wh1",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 2, Wheel = 1", 1000, -5, 5);
  h1_RecdX_DT_St2_Wh2 = fs->make<TH1F>( "RecdX_DT_St2_Wh2",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 2, Wheel = 2", 1000, -5, 5);

  h1_RecdX_DT_St3_Wh0 = fs->make<TH1F>( "RecdX_DT_St3_Wh0",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 3, Wheel = 0", 1000, -5, 5);
  h1_RecdX_DT_St3_Wh1 = fs->make<TH1F>( "RecdX_DT_St3_Wh1",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 3, Wheel = 1", 1000, -5, 5);
  h1_RecdX_DT_St3_Wh2 = fs->make<TH1F>( "RecdX_DT_St3_Wh2",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 3, Wheel = 2", 1000, -5, 5);

  h1_RecdX_DT_St4_Wh0 = fs->make<TH1F>( "RecdX_DT_St4_Wh0",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 4, Wheel = 0", 1000, -5, 5);
  h1_RecdX_DT_St4_Wh1 = fs->make<TH1F>( "RecdX_DT_St4_Wh1",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 4, Wheel = 1", 1000, -5, 5);
  h1_RecdX_DT_St4_Wh2 = fs->make<TH1F>( "RecdX_DT_St4_Wh2",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 4, Wheel = 2", 1000, -5, 5);

  h1_RecdX_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "RecdX_DT_PtCut_St1_Wh0",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 0", 1000, -5, 5);
  h1_RecdX_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "RecdX_DT_PtCut_St1_Wh1",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 1", 1000, -5, 5);
  h1_RecdX_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "RecdX_DT_PtCut_St1_Wh2",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 2", 1000, -5, 5);

  h1_RecdX_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "RecdX_DT_PtCut_St2_Wh0",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 0", 1000, -5, 5);
  h1_RecdX_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "RecdX_DT_PtCut_St2_Wh1",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 1", 1000, -5, 5);
  h1_RecdX_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "RecdX_DT_PtCut_St2_Wh2",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 2", 1000, -5, 5);

  h1_RecdX_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "RecdX_DT_PtCut_St3_Wh0",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 0", 1000, -5, 5);
  h1_RecdX_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "RecdX_DT_PtCut_St3_Wh1",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 1", 1000, -5, 5);
  h1_RecdX_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "RecdX_DT_PtCut_St3_Wh2",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 2", 1000, -5, 5);

  h1_RecdX_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "RecdX_DT_PtCut_St4_Wh0",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 0", 1000, -5, 5);
  h1_RecdX_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "RecdX_DT_PtCut_St4_Wh1",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 1", 1000, -5, 5);
  h1_RecdX_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "RecdX_DT_PtCut_St4_Wh2",   "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 2", 1000, -5, 5);

  h1_RecdY_DT_St1_Wh0 = fs->make<TH1F>( "RecdY_DT_St1_Wh0",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 1, Wheel = 0", 1000, -5, 5);
  h1_RecdY_DT_St1_Wh1 = fs->make<TH1F>( "RecdY_DT_St1_Wh1",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 1, Wheel = 1", 1000, -5, 5);
  h1_RecdY_DT_St1_Wh2 = fs->make<TH1F>( "RecdY_DT_St1_Wh2",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 1, Wheel = 2", 1000, -5, 5);

  h1_RecdY_DT_St2_Wh0 = fs->make<TH1F>( "RecdY_DT_St2_Wh0",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 2, Wheel = 0", 1000, -5, 5);
  h1_RecdY_DT_St2_Wh1 = fs->make<TH1F>( "RecdY_DT_St2_Wh1",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 2, Wheel = 1", 1000, -5, 5);
  h1_RecdY_DT_St2_Wh2 = fs->make<TH1F>( "RecdY_DT_St2_Wh2",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 2, Wheel = 2", 1000, -5, 5);

  h1_RecdY_DT_St3_Wh0 = fs->make<TH1F>( "RecdY_DT_St3_Wh0",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 3, Wheel = 0", 1000, -5, 5);
  h1_RecdY_DT_St3_Wh1 = fs->make<TH1F>( "RecdY_DT_St3_Wh1",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 3, Wheel = 1", 1000, -5, 5);
  h1_RecdY_DT_St3_Wh2 = fs->make<TH1F>( "RecdY_DT_St3_Wh2",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 3, Wheel = 2", 1000, -5, 5);

  h1_RecdY_DT_St4_Wh0 = fs->make<TH1F>( "RecdY_DT_St4_Wh0",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 4, Wheel = 0", 1000, -5, 5);
  h1_RecdY_DT_St4_Wh1 = fs->make<TH1F>( "RecdY_DT_St4_Wh1",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 4, Wheel = 1", 1000, -5, 5);
  h1_RecdY_DT_St4_Wh2 = fs->make<TH1F>( "RecdY_DT_St4_Wh2",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 4, Wheel = 2", 1000, -5, 5);

  h1_RecdY_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "RecdY_DT_PtCut_St1_Wh0",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 0", 1000, -5, 5);
  h1_RecdY_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "RecdY_DT_PtCut_St1_Wh1",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 1", 1000, -5, 5);
  h1_RecdY_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "RecdY_DT_PtCut_St1_Wh2",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Wheel = 2", 1000, -5, 5);

  h1_RecdY_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "RecdY_DT_PtCut_St2_Wh0",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 0", 1000, -5, 5);
  h1_RecdY_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "RecdY_DT_PtCut_St2_Wh1",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 1", 1000, -5, 5);
  h1_RecdY_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "RecdY_DT_PtCut_St2_Wh2",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Wheel = 2", 1000, -5, 5);

  h1_RecdY_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "RecdY_DT_PtCut_St3_Wh0",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 0", 1000, -5, 5);
  h1_RecdY_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "RecdY_DT_PtCut_St3_Wh1",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 1", 1000, -5, 5);
  h1_RecdY_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "RecdY_DT_PtCut_St3_Wh2",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Wheel = 2", 1000, -5, 5);

  h1_RecdY_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "RecdY_DT_PtCut_St4_Wh0",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 0", 1000, -5, 5);
  h1_RecdY_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "RecdY_DT_PtCut_St4_Wh1",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 1", 1000, -5, 5);
  h1_RecdY_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "RecdY_DT_PtCut_St4_Wh2",   "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Wheel = 2", 1000, -5, 5);

  h1_RecdX_CSC_St1_Rg1 = fs->make<TH1F>( "RecdX_CSC_St1_Rg1",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 1, Ring = 1", 1000, -5, 5);
  h1_RecdX_CSC_St1_Rg2 = fs->make<TH1F>( "RecdX_CSC_St1_Rg2",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 1, Ring = 2", 1000, -5, 5);
  h1_RecdX_CSC_St1_Rg3 = fs->make<TH1F>( "RecdX_CSC_St1_Rg3",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 1, Ring = 3", 1000, -5, 5);

  h1_RecdX_CSC_St2_Rg1 = fs->make<TH1F>( "RecdX_CSC_St2_Rg1",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 2, Ring = 1", 1000, -5, 5);
  h1_RecdX_CSC_St2_Rg2 = fs->make<TH1F>( "RecdX_CSC_St2_Rg2",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 2, Ring = 2", 1000, -5, 5);

  h1_RecdX_CSC_St3_Rg1 = fs->make<TH1F>( "RecdX_CSC_St3_Rg1",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 3, Ring = 1", 1000, -5, 5);
  h1_RecdX_CSC_St3_Rg2 = fs->make<TH1F>( "RecdX_CSC_St3_Rg2",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 3, Ring = 2", 1000, -5, 5);

  h1_RecdX_CSC_St4_Rg1 = fs->make<TH1F>( "RecdX_CSC_St4_Rg1",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 4, Ring = 1", 1000, -5, 5);
  h1_RecdX_CSC_St4_Rg2 = fs->make<TH1F>( "RecdX_CSC_St4_Rg2",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Station = 4, Ring = 2", 1000, -5, 5);

  h1_RecdX_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "RecdX_CSC_PtCut_St1_Rg1",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Ring = 1", 1000, -5, 5);
  h1_RecdX_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "RecdX_CSC_PtCut_St1_Rg2",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Ring = 2", 1000, -5, 5);
  h1_RecdX_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "RecdX_CSC_PtCut_St1_Rg3",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Ring = 3", 1000, -5, 5);

  h1_RecdX_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "RecdX_CSC_PtCut_St2_Rg1",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Ring = 1", 1000, -5, 5);
  h1_RecdX_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "RecdX_CSC_PtCut_St2_Rg2",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Ring = 2", 1000, -5, 5);

  h1_RecdX_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "RecdX_CSC_PtCut_St3_Rg1",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Ring = 1", 1000, -5, 5);
  h1_RecdX_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "RecdX_CSC_PtCut_St3_Rg2",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Ring = 2", 1000, -5, 5);

  h1_RecdX_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "RecdX_CSC_PtCut_St4_Rg1",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Ring = 1", 1000, -5, 5);
  h1_RecdX_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "RecdX_CSC_PtCut_St4_Rg2",  "(#frac{dX}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Ring = 2", 1000, -5, 5);

  h1_RecdY_CSC_St1_Rg1 = fs->make<TH1F>( "RecdY_CSC_St1_Rg1",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 1, Ring = 1", 1000, -5, 5);
  h1_RecdY_CSC_St1_Rg2 = fs->make<TH1F>( "RecdY_CSC_St1_Rg2",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 1, Ring = 2", 1000, -5, 5);
  h1_RecdY_CSC_St1_Rg3 = fs->make<TH1F>( "RecdY_CSC_St1_Rg3",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 1, Ring = 3", 1000, -5, 5);

  h1_RecdY_CSC_St2_Rg1 = fs->make<TH1F>( "RecdY_CSC_St2_Rg1",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 2, Ring = 1", 1000, -5, 5);
  h1_RecdY_CSC_St2_Rg2 = fs->make<TH1F>( "RecdY_CSC_St2_Rg2",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 2, Ring = 2", 1000, -5, 5);

  h1_RecdY_CSC_St3_Rg1 = fs->make<TH1F>( "RecdY_CSC_St3_Rg1",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 3, Ring = 1", 1000, -5, 5);
  h1_RecdY_CSC_St3_Rg2 = fs->make<TH1F>( "RecdY_CSC_St3_Rg2",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 3, Ring = 2", 1000, -5, 5);

  h1_RecdY_CSC_St4_Rg1 = fs->make<TH1F>( "RecdY_CSC_St4_Rg1",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 4, Ring = 1", 1000, -5, 5);
  h1_RecdY_CSC_St4_Rg2 = fs->make<TH1F>( "RecdY_CSC_St4_Rg2",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Station = 4, Ring = 2", 1000, -5, 5);

  h1_RecdY_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "RecdY_CSC_PtCut_St1_Rg1",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Ring = 1", 1000, -5, 5);
  h1_RecdY_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "RecdY_CSC_PtCut_St1_Rg2",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Ring = 2", 1000, -5, 5);
  h1_RecdY_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "RecdY_CSC_PtCut_St1_Rg3",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 1, Ring = 3", 1000, -5, 5);

  h1_RecdY_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "RecdY_CSC_PtCut_St2_Rg1",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Ring = 1", 1000, -5, 5);
  h1_RecdY_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "RecdY_CSC_PtCut_St2_Rg2",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 2, Ring = 2", 1000, -5, 5);

  h1_RecdY_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "RecdY_CSC_PtCut_St3_Rg1",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Ring = 1", 1000, -5, 5);
  h1_RecdY_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "RecdY_CSC_PtCut_St3_Rg2",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 3, Ring = 2", 1000, -5, 5);

  h1_RecdY_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "RecdY_CSC_PtCut_St4_Rg1",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Ring = 1", 1000, -5, 5);
  h1_RecdY_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "RecdY_CSC_PtCut_St4_Rg2",  "(#frac{dY}{dZ})_{Rec}^{Loc}, Pt Cut, Station = 4, Ring = 2", 1000, -5, 5);

  h1_ResRecdX_DT_St1_Wh0 = fs->make<TH1F>( "RecResdX_DT_St1_Wh0", "#DeltadX/#deltadX, Station = 1, Wheel = 0", 600, -15, 15);
  h1_ResRecdX_DT_St1_Wh1 = fs->make<TH1F>( "RecResdX_DT_St1_Wh1", "#DeltadX/#deltadX, Station = 1, Wheel = 1", 600, -15, 15);
  h1_ResRecdX_DT_St1_Wh2 = fs->make<TH1F>( "RecResdX_DT_St1_Wh2", "#DeltadX/#deltadX, Station = 1, Wheel = 2", 600, -15, 15);

  h1_ResRecdX_DT_St2_Wh0 = fs->make<TH1F>( "RecResdX_DT_St2_Wh0", "#DeltadX/#deltadX, Station = 2, Wheel = 0", 600, -15, 15);
  h1_ResRecdX_DT_St2_Wh1 = fs->make<TH1F>( "RecResdX_DT_St2_Wh1", "#DeltadX/#deltadX, Station = 2, Wheel = 1", 600, -15, 15);
  h1_ResRecdX_DT_St2_Wh2 = fs->make<TH1F>( "RecResdX_DT_St2_Wh2", "#DeltadX/#deltadX, Station = 2, Wheel = 2", 600, -15, 15);

  h1_ResRecdX_DT_St3_Wh0 = fs->make<TH1F>( "RecResdX_DT_St3_Wh0", "#DeltadX/#deltadX, Station = 3, Wheel = 0", 600, -15, 15);
  h1_ResRecdX_DT_St3_Wh1 = fs->make<TH1F>( "RecResdX_DT_St3_Wh1", "#DeltadX/#deltadX, Station = 3, Wheel = 1", 600, -15, 15);
  h1_ResRecdX_DT_St3_Wh2 = fs->make<TH1F>( "RecResdX_DT_St3_Wh2", "#DeltadX/#deltadX, Station = 3, Wheel = 2", 600, -15, 15);

  h1_ResRecdX_DT_St4_Wh0 = fs->make<TH1F>( "RecResdX_DT_St4_Wh0", "#DeltadX/#deltadX, Station = 4, Wheel = 0", 600, -15, 15);
  h1_ResRecdX_DT_St4_Wh1 = fs->make<TH1F>( "RecResdX_DT_St4_Wh1", "#DeltadX/#deltadX, Station = 4, Wheel = 1", 600, -15, 15);
  h1_ResRecdX_DT_St4_Wh2 = fs->make<TH1F>( "RecResdX_DT_St4_Wh2", "#DeltadX/#deltadX, Station = 4, Wheel = 2", 600, -15, 15);

  h1_ResRecdX_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "RecResdX_DT_PtCut_St1_Wh0", "#DeltadX/#deltadX, Pt Cut, Station = 1, Wheel = 0", 600, -15, 15);
  h1_ResRecdX_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "RecResdX_DT_PtCut_St1_Wh1", "#DeltadX/#deltadX, Pt Cut, Station = 1, Wheel = 1", 600, -15, 15);
  h1_ResRecdX_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "RecResdX_DT_PtCut_St1_Wh2", "#DeltadX/#deltadX, Pt Cut, Station = 1, Wheel = 2", 600, -15, 15);

  h1_ResRecdX_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "RecResdX_DT_PtCut_St2_Wh0", "#DeltadX/#deltadX, Pt Cut, Station = 2, Wheel = 0", 600, -15, 15);
  h1_ResRecdX_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "RecResdX_DT_PtCut_St2_Wh1", "#DeltadX/#deltadX, Pt Cut, Station = 2, Wheel = 1", 600, -15, 15);
  h1_ResRecdX_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "RecResdX_DT_PtCut_St2_Wh2", "#DeltadX/#deltadX, Pt Cut, Station = 2, Wheel = 2", 600, -15, 15);

  h1_ResRecdX_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "RecResdX_DT_PtCut_St3_Wh0", "#DeltadX/#deltadX, Pt Cut, Station = 3, Wheel = 0", 600, -15, 15);
  h1_ResRecdX_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "RecResdX_DT_PtCut_St3_Wh1", "#DeltadX/#deltadX, Pt Cut, Station = 3, Wheel = 1", 600, -15, 15);
  h1_ResRecdX_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "RecResdX_DT_PtCut_St3_Wh2", "#DeltadX/#deltadX, Pt Cut, Station = 3, Wheel = 2", 600, -15, 15);

  h1_ResRecdX_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "RecResdX_DT_PtCut_St4_Wh0", "#DeltadX/#deltadX, Pt Cut, Station = 4, Wheel = 0", 600, -15, 15);
  h1_ResRecdX_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "RecResdX_DT_PtCut_St4_Wh1", "#DeltadX/#deltadX, Pt Cut, Station = 4, Wheel = 1", 600, -15, 15);
  h1_ResRecdX_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "RecResdX_DT_PtCut_St4_Wh2", "#DeltadX/#deltadX, Pt Cut, Station = 4, Wheel = 2", 600, -15, 15);

  h1_ResRecdY_DT_St1_Wh0 = fs->make<TH1F>( "RecResdY_DT_St1_Wh0", "#DeltadY/#deltadY, Station = 1, Wheel = 0", 600, -15, 15);
  h1_ResRecdY_DT_St1_Wh1 = fs->make<TH1F>( "RecResdY_DT_St1_Wh1", "#DeltadY/#deltadY, Station = 1, Wheel = 1", 600, -15, 15);
  h1_ResRecdY_DT_St1_Wh2 = fs->make<TH1F>( "RecResdY_DT_St1_Wh2", "#DeltadY/#deltadY, Station = 1, Wheel = 2", 600, -15, 15);

  h1_ResRecdY_DT_St2_Wh0 = fs->make<TH1F>( "RecResdY_DT_St2_Wh0", "#DeltadY/#deltadY, Station = 2, Wheel = 0", 600, -15, 15);
  h1_ResRecdY_DT_St2_Wh1 = fs->make<TH1F>( "RecResdY_DT_St2_Wh1", "#DeltadY/#deltadY, Station = 2, Wheel = 1", 600, -15, 15);
  h1_ResRecdY_DT_St2_Wh2 = fs->make<TH1F>( "RecResdY_DT_St2_Wh2", "#DeltadY/#deltadY, Station = 2, Wheel = 2", 600, -15, 15);

  h1_ResRecdY_DT_St3_Wh0 = fs->make<TH1F>( "RecResdY_DT_St3_Wh0", "#DeltadY/#deltadY, Station = 3, Wheel = 0", 600, -15, 15);
  h1_ResRecdY_DT_St3_Wh1 = fs->make<TH1F>( "RecResdY_DT_St3_Wh1", "#DeltadY/#deltadY, Station = 3, Wheel = 1", 600, -15, 15);
  h1_ResRecdY_DT_St3_Wh2 = fs->make<TH1F>( "RecResdY_DT_St3_Wh2", "#DeltadY/#deltadY, Station = 3, Wheel = 2", 600, -15, 15);

  h1_ResRecdY_DT_St4_Wh0 = fs->make<TH1F>( "RecResdY_DT_St4_Wh0", "#DeltadY/#deltadY, Station = 4, Wheel = 0", 600, -15, 15);
  h1_ResRecdY_DT_St4_Wh1 = fs->make<TH1F>( "RecResdY_DT_St4_Wh1", "#DeltadY/#deltadY, Station = 4, Wheel = 1", 600, -15, 15);
  h1_ResRecdY_DT_St4_Wh2 = fs->make<TH1F>( "RecResdY_DT_St4_Wh2", "#DeltadY/#deltadY, Station = 4, Wheel = 2", 600, -15, 15);

  h1_ResRecdY_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "RecResdY_DT_PtCut_St1_Wh0", "#DeltadY/#deltadY, Pt Cut, Station = 1, Wheel = 0", 600, -15, 15);
  h1_ResRecdY_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "RecResdY_DT_PtCut_St1_Wh1", "#DeltadY/#deltadY, Pt Cut, Station = 1, Wheel = 1", 600, -15, 15);
  h1_ResRecdY_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "RecResdY_DT_PtCut_St1_Wh2", "#DeltadY/#deltadY, Pt Cut, Station = 1, Wheel = 2", 600, -15, 15);

  h1_ResRecdY_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "RecResdY_DT_PtCut_St2_Wh0", "#DeltadY/#deltadY, Pt Cut, Station = 2, Wheel = 0", 600, -15, 15);
  h1_ResRecdY_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "RecResdY_DT_PtCut_St2_Wh1", "#DeltadY/#deltadY, Pt Cut, Station = 2, Wheel = 1", 600, -15, 15);
  h1_ResRecdY_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "RecResdY_DT_PtCut_St2_Wh2", "#DeltadY/#deltadY, Pt Cut, Station = 2, Wheel = 2", 600, -15, 15);

  h1_ResRecdY_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "RecResdY_DT_PtCut_St3_Wh0", "#DeltadY/#deltadY, Pt Cut, Station = 3, Wheel = 0", 600, -15, 15);
  h1_ResRecdY_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "RecResdY_DT_PtCut_St3_Wh1", "#DeltadY/#deltadY, Pt Cut, Station = 3, Wheel = 1", 600, -15, 15);
  h1_ResRecdY_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "RecResdY_DT_PtCut_St3_Wh2", "#DeltadY/#deltadY, Pt Cut, Station = 3, Wheel = 2", 600, -15, 15);

  h1_ResRecdY_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "RecResdY_DT_PtCut_St4_Wh0", "#DeltadY/#deltadY, Pt Cut, Station = 4, Wheel = 0", 600, -15, 15);
  h1_ResRecdY_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "RecResdY_DT_PtCut_St4_Wh1", "#DeltadY/#deltadY, Pt Cut, Station = 4, Wheel = 1", 600, -15, 15);
  h1_ResRecdY_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "RecResdY_DT_PtCut_St4_Wh2", "#DeltadY/#deltadY, Pt Cut, Station = 4, Wheel = 2", 600, -15, 15);

  h1_RecResdX_CSC_St1_Rg1 = fs->make<TH1F>( "RecResdX_CSC_St1_Rg1", "#DeltadX/#deltadX, Station = 1, Ring = 1", 600, -15, 15);
  h1_RecResdX_CSC_St1_Rg2 = fs->make<TH1F>( "RecResdX_CSC_St1_Rg2", "#DeltadX/#deltadX, Station = 1, Ring = 2", 600, -15, 15);
  h1_RecResdX_CSC_St1_Rg3 = fs->make<TH1F>( "RecResdX_CSC_St1_Rg3", "#DeltadX/#deltadX, Station = 1, Ring = 3", 600, -15, 15);

  h1_RecResdX_CSC_St2_Rg1 = fs->make<TH1F>( "RecResdX_CSC_St2_Rg1", "#DeltadX/#deltadX, Station = 2, Ring = 1", 600, -15, 15);
  h1_RecResdX_CSC_St2_Rg2 = fs->make<TH1F>( "RecResdX_CSC_St2_Rg2", "#DeltadX/#deltadX, Station = 2, Ring = 2", 600, -15, 15);

  h1_RecResdX_CSC_St3_Rg1 = fs->make<TH1F>( "RecResdX_CSC_St3_Rg1", "#DeltadX/#deltadX, Station = 3, Ring = 1", 600, -15, 15);
  h1_RecResdX_CSC_St3_Rg2 = fs->make<TH1F>( "RecResdX_CSC_St3_Rg2", "#DeltadX/#deltadX, Station = 3, Ring = 2", 600, -15, 15);

  h1_RecResdX_CSC_St4_Rg1 = fs->make<TH1F>( "RecResdX_CSC_St4_Rg1", "#DeltadX/#deltadX, Station = 4, Ring = 1", 600, -15, 15);
  h1_RecResdX_CSC_St4_Rg2 = fs->make<TH1F>( "RecResdX_CSC_St4_Rg2", "#DeltadX/#deltadX, Station = 4, Ring = 2", 600, -15, 15);

  h1_RecResdX_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St1_Rg1", "#DeltadX/#deltadX, Station = 1, Ring = 1", 600, -15, 15);
  h1_RecResdX_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St1_Rg2", "#DeltadX/#deltadX, Station = 1, Ring = 2", 600, -15, 15);
  h1_RecResdX_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St1_Rg3", "#DeltadX/#deltadX, Station = 1, Ring = 3", 600, -15, 15);

  h1_RecResdX_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St2_Rg1", "#DeltadX/#deltadX, Station = 2, Ring = 1", 600, -15, 15);
  h1_RecResdX_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St2_Rg2", "#DeltadX/#deltadX, Station = 2, Ring = 2", 600, -15, 15);

  h1_RecResdX_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St3_Rg1", "#DeltadX/#deltadX, Station = 3, Ring = 1", 600, -15, 15);
  h1_RecResdX_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St3_Rg2", "#DeltadX/#deltadX, Station = 3, Ring = 2", 600, -15, 15);

  h1_RecResdX_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St4_Rg1", "#DeltadX/#deltadX, Station = 4, Ring = 1", 600, -15, 15);
  h1_RecResdX_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "RecResdX_CSC_PtCut_St4_Rg2", "#DeltadX/#deltadX, Station = 4, Ring = 2", 600, -15, 15);

  h1_RecResdY_CSC_St1_Rg1 = fs->make<TH1F>( "RecResdY_CSC_St1_Rg1", "#DeltadY/#deltadY, Station = 1, Ring = 1", 600, -15, 15);
  h1_RecResdY_CSC_St1_Rg2 = fs->make<TH1F>( "RecResdY_CSC_St1_Rg2", "#DeltadY/#deltadY, Station = 1, Ring = 2", 600, -15, 15);
  h1_RecResdY_CSC_St1_Rg3 = fs->make<TH1F>( "RecResdY_CSC_St1_Rg3", "#DeltadY/#deltadY, Station = 1, Ring = 3", 600, -15, 15);

  h1_RecResdY_CSC_St2_Rg1 = fs->make<TH1F>( "RecResdY_CSC_St2_Rg1", "#DeltadY/#deltadY, Station = 2, Ring = 1", 600, -15, 15);
  h1_RecResdY_CSC_St2_Rg2 = fs->make<TH1F>( "RecResdY_CSC_St2_Rg2", "#DeltadY/#deltadY, Station = 2, Ring = 2", 600, -15, 15);

  h1_RecResdY_CSC_St3_Rg1 = fs->make<TH1F>( "RecResdY_CSC_St3_Rg1", "#DeltadY/#deltadY, Station = 3, Ring = 1", 600, -15, 15);
  h1_RecResdY_CSC_St3_Rg2 = fs->make<TH1F>( "RecResdY_CSC_St3_Rg2", "#DeltadY/#deltadY, Station = 3, Ring = 2", 600, -15, 15);

  h1_RecResdY_CSC_St4_Rg1 = fs->make<TH1F>( "RecResdY_CSC_St4_Rg1", "#DeltadY/#deltadY, Station = 4, Ring = 1", 600, -15, 15);
  h1_RecResdY_CSC_St4_Rg2 = fs->make<TH1F>( "RecResdY_CSC_St4_Rg2", "#DeltadY/#deltadY, Station = 4, Ring = 2", 600, -15, 15);

  h1_RecResdY_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St1_Rg1", "#DeltadY/#deltadY, Station = 1, Ring = 1", 600, -15, 15);
  h1_RecResdY_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St1_Rg2", "#DeltadY/#deltadY, Station = 1, Ring = 2", 600, -15, 15);
  h1_RecResdY_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St1_Rg3", "#DeltadY/#deltadY, Station = 1, Ring = 3", 600, -15, 15);

  h1_RecResdY_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St2_Rg1", "#DeltadY/#deltadY, Station = 2, Ring = 1", 600, -15, 15);
  h1_RecResdY_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St2_Rg2", "#DeltadY/#deltadY, Station = 2, Ring = 2", 600, -15, 15);

  h1_RecResdY_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St3_Rg1", "#DeltadY/#deltadY, Station = 3, Ring = 1", 600, -15, 15);
  h1_RecResdY_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St3_Rg2", "#DeltadY/#deltadY, Station = 3, Ring = 2", 600, -15, 15);

  h1_RecResdY_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St4_Rg1", "#DeltadY/#deltadY, Station = 4, Ring = 1", 600, -15, 15);
  h1_RecResdY_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "RecResdY_CSC_PtCut_St4_Rg2", "#DeltadY/#deltadY, Station = 4, Ring = 2", 600, -15, 15);

  //Bias devide by Wheels and Rings
  h1_DeltaX_DT_St1_Wh0 = fs->make<TH1F>( "DeltaX_DT_St1_Wh0", "#DeltaX, Station = 1, Wheel = 0", 10000, -5, 5);
  h1_DeltaX_DT_St1_Wh1 = fs->make<TH1F>( "DeltaX_DT_St1_Wh1", "#DeltaX, Station = 1, Wheel = 1", 10000, -5, 5);
  h1_DeltaX_DT_St1_Wh2 = fs->make<TH1F>( "DeltaX_DT_St1_Wh2", "#DeltaX, Station = 1, Wheel = 2", 10000, -5, 5);

  h1_DeltaX_DT_St2_Wh0 = fs->make<TH1F>( "DeltaX_DT_St2_Wh0", "#DeltaX, Station = 2, Wheel = 0", 10000, -5, 5);
  h1_DeltaX_DT_St2_Wh1 = fs->make<TH1F>( "DeltaX_DT_St2_Wh1", "#DeltaX, Station = 2, Wheel = 1", 10000, -5, 5);
  h1_DeltaX_DT_St2_Wh2 = fs->make<TH1F>( "DeltaX_DT_St2_Wh2", "#DeltaX, Station = 2, Wheel = 2", 10000, -5, 5);

  h1_DeltaX_DT_St3_Wh0 = fs->make<TH1F>( "DeltaX_DT_St3_Wh0", "#DeltaX, Station = 3, Wheel = 0", 10000, -5, 5);
  h1_DeltaX_DT_St3_Wh1 = fs->make<TH1F>( "DeltaX_DT_St3_Wh1", "#DeltaX, Station = 3, Wheel = 1", 10000, -5, 5);
  h1_DeltaX_DT_St3_Wh2 = fs->make<TH1F>( "DeltaX_DT_St3_Wh2", "#DeltaX, Station = 3, Wheel = 2", 10000, -5, 5);

  h1_DeltaX_DT_St4_Wh0 = fs->make<TH1F>( "DeltaX_DT_St4_Wh0", "#DeltaX, Station = 4, Wheel = 0", 10000, -5, 5);
  h1_DeltaX_DT_St4_Wh1 = fs->make<TH1F>( "DeltaX_DT_St4_Wh1", "#DeltaX, Station = 4, Wheel = 1", 10000, -5, 5);
  h1_DeltaX_DT_St4_Wh2 = fs->make<TH1F>( "DeltaX_DT_St4_Wh2", "#DeltaX, Station = 4, Wheel = 2", 10000, -5, 5);
 
  h1_DeltaY_DT_St1_Wh0 = fs->make<TH1F>( "DeltaY_DT_St1_Wh0", "#DeltaY, Station = 1, Wheel = 0", 10000, -5, 5);
  h1_DeltaY_DT_St1_Wh1 = fs->make<TH1F>( "DeltaY_DT_St1_Wh1", "#DeltaY, Station = 1, Wheel = 1", 10000, -5, 5);
  h1_DeltaY_DT_St1_Wh2 = fs->make<TH1F>( "DeltaY_DT_St1_Wh2", "#DeltaY, Station = 1, Wheel = 2", 10000, -5, 5);

  h1_DeltaY_DT_St2_Wh0 = fs->make<TH1F>( "DeltaY_DT_St2_Wh0", "#DeltaY, Station = 2, Wheel = 0", 10000, -5, 5);
  h1_DeltaY_DT_St2_Wh1 = fs->make<TH1F>( "DeltaY_DT_St2_Wh1", "#DeltaY, Station = 2, Wheel = 1", 10000, -5, 5);
  h1_DeltaY_DT_St2_Wh2 = fs->make<TH1F>( "DeltaY_DT_St2_Wh2", "#DeltaY, Station = 2, Wheel = 2", 10000, -5, 5);

  h1_DeltaY_DT_St3_Wh0 = fs->make<TH1F>( "DeltaY_DT_St3_Wh0", "#DeltaY, Station = 3, Wheel = 0", 10000, -5, 5);
  h1_DeltaY_DT_St3_Wh1 = fs->make<TH1F>( "DeltaY_DT_St3_Wh1", "#DeltaY, Station = 3, Wheel = 1", 10000, -5, 5);
  h1_DeltaY_DT_St3_Wh2 = fs->make<TH1F>( "DeltaY_DT_St3_Wh2", "#DeltaY, Station = 3, Wheel = 2", 10000, -5, 5);

  h1_DeltaY_DT_St4_Wh0 = fs->make<TH1F>( "DeltaY_DT_St4_Wh0", "#DeltaY, Station = 4, Wheel = 0", 10000, -5, 5);
  h1_DeltaY_DT_St4_Wh1 = fs->make<TH1F>( "DeltaY_DT_St4_Wh1", "#DeltaY, Station = 4, Wheel = 1", 10000, -5, 5);
  h1_DeltaY_DT_St4_Wh2 = fs->make<TH1F>( "DeltaY_DT_St4_Wh2", "#DeltaY, Station = 4, Wheel = 2", 10000, -5, 5);

  h1_DeltaX_CSC_St1_Rg1 = fs->make<TH1F>( "DeltaX_CSC_St1_Rg1", "#DeltaX, Station 1, Ring = 1", 10000, -5, 5);
  h1_DeltaX_CSC_St1_Rg2 = fs->make<TH1F>( "DeltaX_CSC_St1_Rg2", "#DeltaX, Station 1, Ring = 2", 10000, -5, 5);
  h1_DeltaX_CSC_St1_Rg3 = fs->make<TH1F>( "DeltaX_CSC_St1_Rg3", "#DeltaX, Station 1, Ring = 3", 10000, -5, 5);

  h1_DeltaX_CSC_St2_Rg1 = fs->make<TH1F>( "DeltaX_CSC_St2_Rg1", "#DeltaX, Station 2, Ring = 1", 10000, -5, 5);
  h1_DeltaX_CSC_St2_Rg2 = fs->make<TH1F>( "DeltaX_CSC_St2_Rg2", "#DeltaX, Station 2, Ring = 2", 10000, -5, 5);

  h1_DeltaX_CSC_St3_Rg1 = fs->make<TH1F>( "DeltaX_CSC_St3_Rg1", "#DeltaX, Station 3, Ring = 1", 10000, -5, 5);
  h1_DeltaX_CSC_St3_Rg2 = fs->make<TH1F>( "DeltaX_CSC_St3_Rg2", "#DeltaX, Station 3, Ring = 2", 10000, -5, 5);

  h1_DeltaX_CSC_St4_Rg1 = fs->make<TH1F>( "DeltaX_CSC_St4_Rg1", "#DeltaX, Station 4, Ring = 1", 10000, -5, 5);
  h1_DeltaX_CSC_St4_Rg2 = fs->make<TH1F>( "DeltaX_CSC_St4_Rg2", "#DeltaX, Station 4, Ring = 2", 10000, -5, 5);

  h1_DeltaY_CSC_St1_Rg1 = fs->make<TH1F>( "DeltaY_CSC_St1_Rg1", "#DeltaY, Station 1, Ring = 1", 10000, -5, 5);
  h1_DeltaY_CSC_St1_Rg2 = fs->make<TH1F>( "DeltaY_CSC_St1_Rg2", "#DeltaY, Station 1, Ring = 2", 10000, -5, 5);
  h1_DeltaY_CSC_St1_Rg3 = fs->make<TH1F>( "DeltaY_CSC_St1_Rg3", "#DeltaY, Station 1, Ring = 3", 10000, -5, 5);

  h1_DeltaY_CSC_St2_Rg1 = fs->make<TH1F>( "DeltaY_CSC_St2_Rg1", "#DeltaY, Station 2, Ring = 1", 10000, -5, 5);
  h1_DeltaY_CSC_St2_Rg2 = fs->make<TH1F>( "DeltaY_CSC_St2_Rg2", "#DeltaY, Station 2, Ring = 2", 10000, -5, 5);

  h1_DeltaY_CSC_St3_Rg1 = fs->make<TH1F>( "DeltaY_CSC_St3_Rg1", "#DeltaY, Station 3, Ring = 1", 10000, -5, 5);
  h1_DeltaY_CSC_St3_Rg2 = fs->make<TH1F>( "DeltaY_CSC_St3_Rg2", "#DeltaY, Station 3, Ring = 2", 10000, -5, 5);

  h1_DeltaY_CSC_St4_Rg1 = fs->make<TH1F>( "DeltaY_CSC_St4_Rg1", "#DeltaY, Station 4, Ring = 1", 10000, -5, 5);
  h1_DeltaY_CSC_St4_Rg2 = fs->make<TH1F>( "DeltaY_CSC_St4_Rg2", "#DeltaY, Station 4, Ring = 2", 10000, -5, 5);

  //Bias for the Direction
  h1_DeltadX_DT_St1_Wh0 = fs->make<TH1F>( "DeltadX_DT_St1_Wh0", "#DeltadX, Station = 1, Wheel = 0", 10000, -1, 1);
  h1_DeltadX_DT_St1_Wh1 = fs->make<TH1F>( "DeltadX_DT_St1_Wh1", "#DeltadX, Station = 1, Wheel = 1", 10000, -1, 1);
  h1_DeltadX_DT_St1_Wh2 = fs->make<TH1F>( "DeltadX_DT_St1_Wh2", "#DeltadX, Station = 1, Wheel = 2", 10000, -1, 1);

  h1_DeltadX_DT_St2_Wh0 = fs->make<TH1F>( "DeltadX_DT_St2_Wh0", "#DeltadX, Station = 2, Wheel = 0", 10000, -1, 1);
  h1_DeltadX_DT_St2_Wh1 = fs->make<TH1F>( "DeltadX_DT_St2_Wh1", "#DeltadX, Station = 2, Wheel = 1", 10000, -1, 1);
  h1_DeltadX_DT_St2_Wh2 = fs->make<TH1F>( "DeltadX_DT_St2_Wh2", "#DeltadX, Station = 2, Wheel = 2", 10000, -1, 1);

  h1_DeltadX_DT_St3_Wh0 = fs->make<TH1F>( "DeltadX_DT_St3_Wh0", "#DeltadX, Station = 3, Wheel = 0", 10000, -1, 1);
  h1_DeltadX_DT_St3_Wh1 = fs->make<TH1F>( "DeltadX_DT_St3_Wh1", "#DeltadX, Station = 3, Wheel = 1", 10000, -1, 1);
  h1_DeltadX_DT_St3_Wh2 = fs->make<TH1F>( "DeltadX_DT_St3_Wh2", "#DeltadX, Station = 3, Wheel = 2", 10000, -1, 1);

  h1_DeltadX_DT_St4_Wh0 = fs->make<TH1F>( "DeltadX_DT_St4_Wh0", "#DeltadX, Station = 4, Wheel = 0", 10000, -1, 1);
  h1_DeltadX_DT_St4_Wh1 = fs->make<TH1F>( "DeltadX_DT_St4_Wh1", "#DeltadX, Station = 4, Wheel = 1", 10000, -1, 1);
  h1_DeltadX_DT_St4_Wh2 = fs->make<TH1F>( "DeltadX_DT_St4_Wh2", "#DeltadX, Station = 4, Wheel = 2", 10000, -1, 1);

  h1_DeltadY_DT_St1_Wh0 = fs->make<TH1F>( "DeltadY_DT_St1_Wh0", "#DeltadY, Station = 1, Wheel = 0", 10000, -1, 1);
  h1_DeltadY_DT_St1_Wh1 = fs->make<TH1F>( "DeltadY_DT_St1_Wh1", "#DeltadY, Station = 1, Wheel = 1", 10000, -1, 1);
  h1_DeltadY_DT_St1_Wh2 = fs->make<TH1F>( "DeltadY_DT_St1_Wh2", "#DeltadY, Station = 1, Wheel = 2", 10000, -1, 1);

  h1_DeltadY_DT_St2_Wh0 = fs->make<TH1F>( "DeltadY_DT_St2_Wh0", "#DeltadY, Station = 2, Wheel = 0", 10000, -1, 1);
  h1_DeltadY_DT_St2_Wh1 = fs->make<TH1F>( "DeltadY_DT_St2_Wh1", "#DeltadY, Station = 2, Wheel = 1", 10000, -1, 1);
  h1_DeltadY_DT_St2_Wh2 = fs->make<TH1F>( "DeltadY_DT_St2_Wh2", "#DeltadY, Station = 2, Wheel = 2", 10000, -1, 1);

  h1_DeltadY_DT_St3_Wh0 = fs->make<TH1F>( "DeltadY_DT_St3_Wh0", "#DeltadY, Station = 3, Wheel = 0", 10000, -1, 1);
  h1_DeltadY_DT_St3_Wh1 = fs->make<TH1F>( "DeltadY_DT_St3_Wh1", "#DeltadY, Station = 3, Wheel = 1", 10000, -1, 1);
  h1_DeltadY_DT_St3_Wh2 = fs->make<TH1F>( "DeltadY_DT_St3_Wh2", "#DeltadY, Station = 3, Wheel = 2", 10000, -1, 1);

  h1_DeltadY_DT_St4_Wh0 = fs->make<TH1F>( "DeltadY_DT_St4_Wh0", "#DeltadY, Station = 4, Wheel = 0", 10000, -1, 1);
  h1_DeltadY_DT_St4_Wh1 = fs->make<TH1F>( "DeltadY_DT_St4_Wh1", "#DeltadY, Station = 4, Wheel = 1", 10000, -1, 1);
  h1_DeltadY_DT_St4_Wh2 = fs->make<TH1F>( "DeltadY_DT_St4_Wh2", "#DeltadY, Station = 4, Wheel = 2", 10000, -1, 1);

  h1_DeltadX_CSC_St1_Rg1 = fs->make<TH1F>( "DeltadX_CSC_St1_Rg1", "#DeltadX, Station 1, Ring = 1", 10000, -1, 1);
  h1_DeltadX_CSC_St1_Rg2 = fs->make<TH1F>( "DeltadX_CSC_St1_Rg2", "#DeltadX, Station 1, Ring = 2", 10000, -1, 1);
  h1_DeltadX_CSC_St1_Rg3 = fs->make<TH1F>( "DeltadX_CSC_St1_Rg3", "#DeltadX, Station 1, Ring = 3", 10000, -1, 1);

  h1_DeltadX_CSC_St2_Rg1 = fs->make<TH1F>( "DeltadX_CSC_St2_Rg1", "#DeltadX, Station 2, Ring = 1", 10000, -1, 1);
  h1_DeltadX_CSC_St2_Rg2 = fs->make<TH1F>( "DeltadX_CSC_St2_Rg2", "#DeltadX, Station 2, Ring = 2", 10000, -1, 1);

  h1_DeltadX_CSC_St3_Rg1 = fs->make<TH1F>( "DeltadX_CSC_St3_Rg1", "#DeltadX, Station 3, Ring = 1", 10000, -1, 1);
  h1_DeltadX_CSC_St3_Rg2 = fs->make<TH1F>( "DeltadX_CSC_St3_Rg2", "#DeltadX, Station 3, Ring = 2", 10000, -1, 1);

  h1_DeltadX_CSC_St4_Rg1 = fs->make<TH1F>( "DeltadX_CSC_St4_Rg1", "#DeltadX, Station 4, Ring = 1", 10000, -1, 1);
  h1_DeltadX_CSC_St4_Rg2 = fs->make<TH1F>( "DeltadX_CSC_St4_Rg2", "#DeltadX, Station 4, Ring = 2", 10000, -1, 1);

  h1_DeltadY_CSC_St1_Rg1 = fs->make<TH1F>( "DeltadY_CSC_St1_Rg1", "#DeltadY, Station 1, Ring = 1", 10000, -1, 1);
  h1_DeltadY_CSC_St1_Rg2 = fs->make<TH1F>( "DeltadY_CSC_St1_Rg2", "#DeltadY, Station 1, Ring = 2", 10000, -1, 1);
  h1_DeltadY_CSC_St1_Rg3 = fs->make<TH1F>( "DeltadY_CSC_St1_Rg3", "#DeltadY, Station 1, Ring = 3", 10000, -1, 1);

  h1_DeltadY_CSC_St2_Rg1 = fs->make<TH1F>( "DeltadY_CSC_St2_Rg1", "#DeltadY, Station 2, Ring = 1", 10000, -1, 1);
  h1_DeltadY_CSC_St2_Rg2 = fs->make<TH1F>( "DeltadY_CSC_St2_Rg2", "#DeltadY, Station 2, Ring = 2", 10000, -1, 1);

  h1_DeltadY_CSC_St3_Rg1 = fs->make<TH1F>( "DeltadY_CSC_St3_Rg1", "#DeltadY, Station 3, Ring = 1", 10000, -1, 1);
  h1_DeltadY_CSC_St3_Rg2 = fs->make<TH1F>( "DeltadY_CSC_St3_Rg2", "#DeltadY, Station 3, Ring = 2", 10000, -1, 1);

  h1_DeltadY_CSC_St4_Rg1 = fs->make<TH1F>( "DeltadY_CSC_St4_Rg1", "#DeltadY, Station 4, Ring = 1", 10000, -1, 1);
  h1_DeltadY_CSC_St4_Rg2 = fs->make<TH1F>( "DeltadY_CSC_St4_Rg2", "#DeltadY, Station 4, Ring = 2", 10000, -1, 1);

  //Error Position
  h1_ErrX_DT_St1_Wh0 = fs->make<TH1F>( "ErrX_DT_St1_Wh0", "Error X, Station = 1, Wheel = 0", 10000, 0, 1);
  h1_ErrX_DT_St1_Wh1 = fs->make<TH1F>( "ErrX_DT_St1_Wh1", "Error X, Station = 1, Wheel = 1", 10000, 0, 1);
  h1_ErrX_DT_St1_Wh2 = fs->make<TH1F>( "ErrX_DT_St1_Wh2", "Error X, Station = 1, Wheel = 2", 10000, 0, 1);

  h1_ErrX_DT_St2_Wh0 = fs->make<TH1F>( "ErrX_DT_St2_Wh0", "Error X, Station = 2, Wheel = 0", 10000, 0, 1);
  h1_ErrX_DT_St2_Wh1 = fs->make<TH1F>( "ErrX_DT_St2_Wh1", "Error X, Station = 2, Wheel = 1", 10000, 0, 1);
  h1_ErrX_DT_St2_Wh2 = fs->make<TH1F>( "ErrX_DT_St2_Wh2", "Error X, Station = 2, Wheel = 2", 10000, 0, 1);

  h1_ErrX_DT_St3_Wh0 = fs->make<TH1F>( "ErrX_DT_St3_Wh0", "Error X, Station = 3, Wheel = 0", 10000, 0, 1);
  h1_ErrX_DT_St3_Wh1 = fs->make<TH1F>( "ErrX_DT_St3_Wh1", "Error X, Station = 3, Wheel = 1", 10000, 0, 1);
  h1_ErrX_DT_St3_Wh2 = fs->make<TH1F>( "ErrX_DT_St3_Wh2", "Error X, Station = 3, Wheel = 2", 10000, 0, 1);

  h1_ErrX_DT_St4_Wh0 = fs->make<TH1F>( "ErrX_DT_St4_Wh0", "Error X, Station = 4, Wheel = 0", 10000, 0, 1);
  h1_ErrX_DT_St4_Wh1 = fs->make<TH1F>( "ErrX_DT_St4_Wh1", "Error X, Station = 4, Wheel = 1", 10000, 0, 1);
  h1_ErrX_DT_St4_Wh2 = fs->make<TH1F>( "ErrX_DT_St4_Wh2", "Error X, Station = 4, Wheel = 2", 10000, 0, 1);

  h1_ErrY_DT_St1_Wh0 = fs->make<TH1F>( "ErrY_DT_St1_Wh0", "Error Y, Station = 1, Wheel = 0", 10000, 0, 1);
  h1_ErrY_DT_St1_Wh1 = fs->make<TH1F>( "ErrY_DT_St1_Wh1", "Error Y, Station = 1, Wheel = 1", 10000, 0, 1);
  h1_ErrY_DT_St1_Wh2 = fs->make<TH1F>( "ErrY_DT_St1_Wh2", "Error Y, Station = 1, Wheel = 2", 10000, 0, 1);

  h1_ErrY_DT_St2_Wh0 = fs->make<TH1F>( "ErrY_DT_St2_Wh0", "Error Y, Station = 2, Wheel = 0", 10000, 0, 1);
  h1_ErrY_DT_St2_Wh1 = fs->make<TH1F>( "ErrY_DT_St2_Wh1", "Error Y, Station = 2, Wheel = 1", 10000, 0, 1);
  h1_ErrY_DT_St2_Wh2 = fs->make<TH1F>( "ErrY_DT_St2_Wh2", "Error Y, Station = 2, Wheel = 2", 10000, 0, 1);

  h1_ErrY_DT_St3_Wh0 = fs->make<TH1F>( "ErrY_DT_St3_Wh0", "Error Y, Station = 3, Wheel = 0", 10000, 0, 1);
  h1_ErrY_DT_St3_Wh1 = fs->make<TH1F>( "ErrY_DT_St3_Wh1", "Error Y, Station = 3, Wheel = 1", 10000, 0, 1);
  h1_ErrY_DT_St3_Wh2 = fs->make<TH1F>( "ErrY_DT_St3_Wh2", "Error Y, Station = 3, Wheel = 2", 10000, 0, 1);

  h1_ErrY_DT_St4_Wh0 = fs->make<TH1F>( "ErrY_DT_St4_Wh0", "Error Y, Station = 4, Wheel = 0", 10000, 0, 1);
  h1_ErrY_DT_St4_Wh1 = fs->make<TH1F>( "ErrY_DT_St4_Wh1", "Error Y, Station = 4, Wheel = 1", 10000, 0, 1);
  h1_ErrY_DT_St4_Wh2 = fs->make<TH1F>( "ErrY_DT_St4_Wh2", "Error Y, Station = 4, Wheel = 2", 10000, 0, 1);

  h1_ErrX_CSC_St1_Rg1 = fs->make<TH1F>( "ErrX_CSC_St1_Rg1", "Error X, Station = 1, Ring = 1", 10000, 0, 1);
  h1_ErrX_CSC_St1_Rg2 = fs->make<TH1F>( "ErrX_CSC_St1_Rg2", "Error X, Station = 1, Ring = 2", 10000, 0, 1);
  h1_ErrX_CSC_St1_Rg3 = fs->make<TH1F>( "ErrX_CSC_St1_Rg3", "Error X, Station = 1, Ring = 3", 10000, 0, 1);

  h1_ErrX_CSC_St2_Rg1 = fs->make<TH1F>( "ErrX_CSC_St2_Rg1", "Error X, Station = 2, Ring = 1", 10000, 0, 1);
  h1_ErrX_CSC_St2_Rg2 = fs->make<TH1F>( "ErrX_CSC_St2_Rg2", "Error X, Station = 2, Ring = 2", 10000, 0, 1);

  h1_ErrX_CSC_St3_Rg1 = fs->make<TH1F>( "ErrX_CSC_St3_Rg1", "Error X, Station = 3, Ring = 1", 10000, 0, 1);
  h1_ErrX_CSC_St3_Rg2 = fs->make<TH1F>( "ErrX_CSC_St3_Rg2", "Error X, Station = 3, Ring = 2", 10000, 0, 1);

  h1_ErrX_CSC_St4_Rg1 = fs->make<TH1F>( "ErrX_CSC_St4_Rg1", "Error X, Station = 4, Ring = 1", 10000, 0, 1);
  h1_ErrX_CSC_St4_Rg2 = fs->make<TH1F>( "ErrX_CSC_St4_Rg2", "Error X, Station = 4, Ring = 2", 10000, 0, 1);

  h1_ErrY_CSC_St1_Rg1 = fs->make<TH1F>( "ErrY_CSC_St1_Rg1", "Error Y, Station = 1, Ring = 1", 10000, 0, 5);
  h1_ErrY_CSC_St1_Rg2 = fs->make<TH1F>( "ErrY_CSC_St1_Rg2", "Error Y, Station = 1, Ring = 2", 10000, 0, 5);
  h1_ErrY_CSC_St1_Rg3 = fs->make<TH1F>( "ErrY_CSC_St1_Rg3", "Error Y, Station = 1, Ring = 3", 10000, 0, 5);

  h1_ErrY_CSC_St2_Rg1 = fs->make<TH1F>( "ErrY_CSC_St2_Rg1", "Error Y, Station = 2, Ring = 1", 10000, 0, 5);
  h1_ErrY_CSC_St2_Rg2 = fs->make<TH1F>( "ErrY_CSC_St2_Rg2", "Error Y, Station = 2, Ring = 2", 10000, 0, 5);

  h1_ErrY_CSC_St3_Rg1 = fs->make<TH1F>( "ErrY_CSC_St3_Rg1", "Error Y, Station = 3, Ring = 1", 10000, 0, 5);
  h1_ErrY_CSC_St3_Rg2 = fs->make<TH1F>( "ErrY_CSC_St3_Rg2", "Error Y, Station = 3, Ring = 2", 10000, 0, 5);

  h1_ErrY_CSC_St4_Rg1 = fs->make<TH1F>( "ErrY_CSC_St4_Rg1", "Error Y, Station = 4, Ring = 1", 10000, 0, 5);
  h1_ErrY_CSC_St4_Rg2 = fs->make<TH1F>( "ErrY_CSC_St4_Rg2", "Error Y, Station = 4, Ring = 2", 10000, 0, 5);

  //Error postion with Pt Cut
  h1_ErrX_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "ErrX_DT_PtCut_St1_Wh0", "Pt Cut, Error X, Station = 1, Wheel = 0", 10000, 0, 1);
  h1_ErrX_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "ErrX_DT_PtCut_St1_Wh1", "Pt Cut, Error X, Station = 1, Wheel = 1", 10000, 0, 1);
  h1_ErrX_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "ErrX_DT_PtCut_St1_Wh2", "Pt Cut, Error X, Station = 1, Wheel = 2", 10000, 0, 1);

  h1_ErrX_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "ErrX_DT_PtCut_St2_Wh0", "Pt Cut, Error X, Station = 2, Wheel = 0", 10000, 0, 1);
  h1_ErrX_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "ErrX_DT_PtCut_St2_Wh1", "Pt Cut, Error X, Station = 2, Wheel = 1", 10000, 0, 1);
  h1_ErrX_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "ErrX_DT_PtCut_St2_Wh2", "Pt Cut, Error X, Station = 2, Wheel = 2", 10000, 0, 1);

  h1_ErrX_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "ErrX_DT_PtCut_St3_Wh0", "Pt Cut, Error X, Station = 3, Wheel = 0", 10000, 0, 1);
  h1_ErrX_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "ErrX_DT_PtCut_St3_Wh1", "Pt Cut, Error X, Station = 3, Wheel = 1", 10000, 0, 1);
  h1_ErrX_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "ErrX_DT_PtCut_St3_Wh2", "Pt Cut, Error X, Station = 3, Wheel = 2", 10000, 0, 1);

  h1_ErrX_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "ErrX_DT_PtCut_St4_Wh0", "Pt Cut, Error X, Station = 4, Wheel = 0", 10000, 0, 1);
  h1_ErrX_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "ErrX_DT_PtCut_St4_Wh1", "Pt Cut, Error X, Station = 4, Wheel = 1", 10000, 0, 1);
  h1_ErrX_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "ErrX_DT_PtCut_St4_Wh2", "Pt Cut, Error X, Station = 4, Wheel = 2", 10000, 0, 1);

  h1_ErrY_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "ErrY_DT_PtCut_St1_Wh0", "Pt Cut, Error Y, Station = 1, Wheel = 0", 10000, 0, 1);
  h1_ErrY_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "ErrY_DT_PtCut_St1_Wh1", "Pt Cut, Error Y, Station = 1, Wheel = 1", 10000, 0, 1);
  h1_ErrY_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "ErrY_DT_PtCut_St1_Wh2", "Pt Cut, Error Y, Station = 1, Wheel = 2", 10000, 0, 1);

  h1_ErrY_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "ErrY_DT_PtCut_St2_Wh0", "Pt Cut, Error Y, Station = 2, Wheel = 0", 10000, 0, 1);
  h1_ErrY_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "ErrY_DT_PtCut_St2_Wh1", "Pt Cut, Error Y, Station = 2, Wheel = 1", 10000, 0, 1);
  h1_ErrY_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "ErrY_DT_PtCut_St2_Wh2", "Pt Cut, Error Y, Station = 2, Wheel = 2", 10000, 0, 1);

  h1_ErrY_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "ErrY_DT_PtCut_St3_Wh0", "Pt Cut, Error Y, Station = 3, Wheel = 0", 10000, 0, 1);
  h1_ErrY_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "ErrY_DT_PtCut_St3_Wh1", "Pt Cut, Error Y, Station = 3, Wheel = 1", 10000, 0, 1);
  h1_ErrY_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "ErrY_DT_PtCut_St3_Wh2", "Pt Cut, Error Y, Station = 3, Wheel = 2", 10000, 0, 1);

  h1_ErrY_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "ErrY_DT_PtCut_St4_Wh0", "Pt Cut, Error Y, Station = 4, Wheel = 0", 10000, 0, 1);
  h1_ErrY_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "ErrY_DT_PtCut_St4_Wh1", "Pt Cut, Error Y, Station = 4, Wheel = 1", 10000, 0, 1);
  h1_ErrY_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "ErrY_DT_PtCut_St4_Wh2", "Pt Cut, Error Y, Station = 4, Wheel = 2", 10000, 0, 1);

  h1_ErrX_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "ErrX_CSC_PtCut_St1_Rg1", "Pt Cut, Error X, Station = 1, Ring = 1", 10000, 0, 1);
  h1_ErrX_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "ErrX_CSC_PtCut_St1_Rg2", "Pt Cut, Error X, Station = 1, Ring = 2", 10000, 0, 1);
  h1_ErrX_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "ErrX_CSC_PtCut_St1_Rg3", "Pt Cut, Error X, Station = 1, Ring = 3", 10000, 0, 1);

  h1_ErrX_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "ErrX_CSC_PtCut_St2_Rg1", "Pt Cut, Error X, Station = 2, Ring = 1", 10000, 0, 1);
  h1_ErrX_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "ErrX_CSC_PtCut_St2_Rg2", "Pt Cut, Error X, Station = 2, Ring = 2", 10000, 0, 1);

  h1_ErrX_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "ErrX_CSC_PtCut_St3_Rg1", "Pt Cut, Error X, Station = 3, Ring = 1", 10000, 0, 1);
  h1_ErrX_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "ErrX_CSC_PtCut_St3_Rg2", "Pt Cut, Error X, Station = 3, Ring = 2", 10000, 0, 1);

  h1_ErrX_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "ErrX_CSC_PtCut_St4_Rg1", "Pt Cut, Error X, Station = 4, Ring = 1", 10000, 0, 1);
  h1_ErrX_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "ErrX_CSC_PtCut_St4_Rg2", "Pt Cut, Error X, Station = 4, Ring = 2", 10000, 0, 1);

  h1_ErrY_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "ErrY_CSC_PtCut_St1_Rg1", "Pt Cut, Error Y, Station = 1, Ring = 1", 10000, 0, 5);
  h1_ErrY_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "ErrY_CSC_PtCut_St1_Rg2", "Pt Cut, Error Y, Station = 1, Ring = 2", 10000, 0, 5);
  h1_ErrY_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "ErrY_CSC_PtCut_St1_Rg3", "Pt Cut, Error Y, Station = 1, Ring = 3", 10000, 0, 5);

  h1_ErrY_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "ErrY_CSC_PtCut_St2_Rg1", "Pt Cut, Error Y, Station = 2, Ring = 1", 10000, 0, 5);
  h1_ErrY_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "ErrY_CSC_PtCut_St2_Rg2", "Pt Cut, Error Y, Station = 2, Ring = 2", 10000, 0, 5);

  h1_ErrY_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "ErrY_CSC_PtCut_St3_Rg1", "Pt Cut, Error Y, Station = 3, Ring = 1", 10000, 0, 5);
  h1_ErrY_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "ErrY_CSC_PtCut_St3_Rg2", "Pt Cut, Error Y, Station = 3, Ring = 2", 10000, 0, 5);

  h1_ErrY_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "ErrY_CSC_PtCut_St4_Rg1", "Pt Cut, Error Y, Station = 4, Ring = 1", 10000, 0, 5);
  h1_ErrY_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "ErrY_CSC_PtCut_St4_Rg2", "Pt Cut, Error Y, Station = 4, Ring = 2", 10000, 0, 5);

  //Error plots direction
  h1_ErrdX_DT_St1_Wh0 = fs->make<TH1F>( "ErrdX_DT_St1_Wh0", "Error dX/dZ, Station = 1, Wheel = 0", 10000, 0, 0.005);
  h1_ErrdX_DT_St1_Wh1 = fs->make<TH1F>( "ErrdX_DT_St1_Wh1", "Error dX/dZ, Station = 1, Wheel = 1", 10000, 0, 0.005);
  h1_ErrdX_DT_St1_Wh2 = fs->make<TH1F>( "ErrdX_DT_St1_Wh2", "Error dX/dZ, Station = 1, Wheel = 2", 10000, 0, 0.005);

  h1_ErrdX_DT_St2_Wh0 = fs->make<TH1F>( "ErrdX_DT_St2_Wh0", "Error dX/dZ, Station = 2, Wheel = 0", 10000, 0, 0.005);
  h1_ErrdX_DT_St2_Wh1 = fs->make<TH1F>( "ErrdX_DT_St2_Wh1", "Error dX/dZ, Station = 2, Wheel = 1", 10000, 0, 0.005);
  h1_ErrdX_DT_St2_Wh2 = fs->make<TH1F>( "ErrdX_DT_St2_Wh2", "Error dX/dZ, Station = 2, Wheel = 2", 10000, 0, 0.005);

  h1_ErrdX_DT_St3_Wh0 = fs->make<TH1F>( "ErrdX_DT_St3_Wh0", "Error dX/dZ, Station = 3, Wheel = 0", 10000, 0, 0.005);
  h1_ErrdX_DT_St3_Wh1 = fs->make<TH1F>( "ErrdX_DT_St3_Wh1", "Error dX/dZ, Station = 3, Wheel = 1", 10000, 0, 0.005);
  h1_ErrdX_DT_St3_Wh2 = fs->make<TH1F>( "ErrdX_DT_St3_Wh2", "Error dX/dZ, Station = 3, Wheel = 2", 10000, 0, 0.005);

  h1_ErrdX_DT_St4_Wh0 = fs->make<TH1F>( "ErrdX_DT_St4_Wh0", "Error dX/dZ, Station = 4, Wheel = 0", 10000, 0, 0.005);
  h1_ErrdX_DT_St4_Wh1 = fs->make<TH1F>( "ErrdX_DT_St4_Wh1", "Error dX/dZ, Station = 4, Wheel = 1", 10000, 0, 0.005);
  h1_ErrdX_DT_St4_Wh2 = fs->make<TH1F>( "ErrdX_DT_St4_Wh2", "Error dX/dZ, Station = 4, Wheel = 2", 10000, 0, 0.005);

  h1_ErrdY_DT_St1_Wh0 = fs->make<TH1F>( "ErrdY_DT_St1_Wh0", "Error dY/dZ, Station = 1, Wheel = 0", 10000, 0, 0.05);
  h1_ErrdY_DT_St1_Wh1 = fs->make<TH1F>( "ErrdY_DT_St1_Wh1", "Error dY/dZ, Station = 1, Wheel = 1", 10000, 0, 0.05);
  h1_ErrdY_DT_St1_Wh2 = fs->make<TH1F>( "ErrdY_DT_St1_Wh2", "Error dY/dZ, Station = 1, Wheel = 2", 10000, 0, 0.05);

  h1_ErrdY_DT_St2_Wh0 = fs->make<TH1F>( "ErrdY_DT_St2_Wh0", "Error dY/dZ, Station = 2, Wheel = 0", 10000, 0, 0.05);
  h1_ErrdY_DT_St2_Wh1 = fs->make<TH1F>( "ErrdY_DT_St2_Wh1", "Error dY/dZ, Station = 2, Wheel = 1", 10000, 0, 0.05);
  h1_ErrdY_DT_St2_Wh2 = fs->make<TH1F>( "ErrdY_DT_St2_Wh2", "Error dY/dZ, Station = 2, Wheel = 2", 10000, 0, 0.05);

  h1_ErrdY_DT_St3_Wh0 = fs->make<TH1F>( "ErrdY_DT_St3_Wh0", "Error dY/dZ, Station = 3, Wheel = 0", 10000, 0, 0.05);
  h1_ErrdY_DT_St3_Wh1 = fs->make<TH1F>( "ErrdY_DT_St3_Wh1", "Error dY/dZ, Station = 3, Wheel = 1", 10000, 0, 0.05);
  h1_ErrdY_DT_St3_Wh2 = fs->make<TH1F>( "ErrdY_DT_St3_Wh2", "Error dY/dZ, Station = 3, Wheel = 2", 10000, 0, 0.05);

  h1_ErrdY_DT_St4_Wh0 = fs->make<TH1F>( "ErrdY_DT_St4_Wh0", "Error dY/dZ, Station = 4, Wheel = 0", 10000, 0, 0.05);
  h1_ErrdY_DT_St4_Wh1 = fs->make<TH1F>( "ErrdY_DT_St4_Wh1", "Error dY/dZ, Station = 4, Wheel = 1", 10000, 0, 0.05);
  h1_ErrdY_DT_St4_Wh2 = fs->make<TH1F>( "ErrdY_DT_St4_Wh2", "Error dY/dZ, Station = 4, Wheel = 2", 10000, 0, 0.05);

  h1_ErrdX_CSC_St1_Rg1 = fs->make<TH1F>( "ErrdX_CSC_St1_Rg1", "Error dX/dZ, Station = 1, Ring = 1", 10000, 0, 0.05);
  h1_ErrdX_CSC_St1_Rg2 = fs->make<TH1F>( "ErrdX_CSC_St1_Rg2", "Error dX/dZ, Station = 1, Ring = 2", 10000, 0, 0.05);
  h1_ErrdX_CSC_St1_Rg3 = fs->make<TH1F>( "ErrdX_CSC_St1_Rg3", "Error dX/dZ, Station = 1, Ring = 3", 10000, 0, 0.05);

  h1_ErrdX_CSC_St2_Rg1 = fs->make<TH1F>( "ErrdX_CSC_St2_Rg1", "Error dX/dZ, Station = 2, Ring = 1", 10000, 0, 0.05);
  h1_ErrdX_CSC_St2_Rg2 = fs->make<TH1F>( "ErrdX_CSC_St2_Rg2", "Error dX/dZ, Station = 2, Ring = 2", 10000, 0, 0.05);

  h1_ErrdX_CSC_St3_Rg1 = fs->make<TH1F>( "ErrdX_CSC_St3_Rg1", "Error dX/dZ, Station = 3, Ring = 1", 10000, 0, 0.05);
  h1_ErrdX_CSC_St3_Rg2 = fs->make<TH1F>( "ErrdX_CSC_St3_Rg2", "Error dX/dZ, Station = 3, Ring = 2", 10000, 0, 0.05);

  h1_ErrdX_CSC_St4_Rg1 = fs->make<TH1F>( "ErrdX_CSC_St4_Rg1", "Error dX/dZ, Station = 4, Ring = 1", 10000, 0, 0.05);
  h1_ErrdX_CSC_St4_Rg2 = fs->make<TH1F>( "ErrdX_CSC_St4_Rg2", "Error dX/dZ, Station = 4, Ring = 2", 10000, 0, 0.05);

  h1_ErrdY_CSC_St1_Rg1 = fs->make<TH1F>( "ErrdY_CSC_St1_Rg1", "Error dY/dZ, Station = 1, Ring = 1", 10000, 0, 0.5);
  h1_ErrdY_CSC_St1_Rg2 = fs->make<TH1F>( "ErrdY_CSC_St1_Rg2", "Error dY/dZ, Station = 1, Ring = 2", 10000, 0, 0.5);
  h1_ErrdY_CSC_St1_Rg3 = fs->make<TH1F>( "ErrdY_CSC_St1_Rg3", "Error dY/dZ, Station = 1, Ring = 3", 10000, 0, 0.5);

  h1_ErrdY_CSC_St2_Rg1 = fs->make<TH1F>( "ErrdY_CSC_St2_Rg1", "Error dY/dZ, Station = 2, Ring = 1", 10000, 0, 0.5);
  h1_ErrdY_CSC_St2_Rg2 = fs->make<TH1F>( "ErrdY_CSC_St2_Rg2", "Error dY/dZ, Station = 2, Ring = 2", 10000, 0, 0.5);

  h1_ErrdY_CSC_St3_Rg1 = fs->make<TH1F>( "ErrdY_CSC_St3_Rg1", "Error dY/dZ, Station = 3, Ring = 1", 10000, 0, 0.5);
  h1_ErrdY_CSC_St3_Rg2 = fs->make<TH1F>( "ErrdY_CSC_St3_Rg2", "Error dY/dZ, Station = 3, Ring = 2", 10000, 0, 0.5);

  h1_ErrdY_CSC_St4_Rg1 = fs->make<TH1F>( "ErrdY_CSC_St4_Rg1", "Error dY/dZ, Station = 4, Ring = 1", 10000, 0, 0.5);
  h1_ErrdY_CSC_St4_Rg2 = fs->make<TH1F>( "ErrdY_CSC_St4_Rg2", "Error dY/dZ, Station = 4, Ring = 2", 10000, 0, 0.5);

  //Error direction Pt Cut
  h1_ErrdX_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "ErrdX_DT_PtCut_St1_Wh0", "Pt Cut, Error dX/dZ, Station = 1, Wheel = 0", 10000, 0, 0.005);
  h1_ErrdX_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "ErrdX_DT_PtCut_St1_Wh1", "Pt Cut, Error dX/dZ, Station = 1, Wheel = 1", 10000, 0, 0.005);
  h1_ErrdX_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "ErrdX_DT_PtCut_St1_Wh2", "Pt Cut, Error dX/dZ, Station = 1, Wheel = 2", 10000, 0, 0.005);

  h1_ErrdX_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "ErrdX_DT_PtCut_St2_Wh0", "Pt Cut, Error dX/dZ, Station = 2, Wheel = 0", 10000, 0, 0.005);
  h1_ErrdX_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "ErrdX_DT_PtCut_St2_Wh1", "Pt Cut, Error dX/dZ, Station = 2, Wheel = 1", 10000, 0, 0.005);
  h1_ErrdX_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "ErrdX_DT_PtCut_St2_Wh2", "Pt Cut, Error dX/dZ, Station = 2, Wheel = 2", 10000, 0, 0.005);

  h1_ErrdX_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "ErrdX_DT_PtCut_St3_Wh0", "Pt Cut, Error dX/dZ, Station = 3, Wheel = 0", 10000, 0, 0.005);
  h1_ErrdX_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "ErrdX_DT_PtCut_St3_Wh1", "Pt Cut, Error dX/dZ, Station = 3, Wheel = 1", 10000, 0, 0.005);
  h1_ErrdX_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "ErrdX_DT_PtCut_St3_Wh2", "Pt Cut, Error dX/dZ, Station = 3, Wheel = 2", 10000, 0, 0.005);

  h1_ErrdX_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "ErrdX_DT_PtCut_St4_Wh0", "Pt Cut, Error dX/dZ, Station = 4, Wheel = 0", 10000, 0, 0.005);
  h1_ErrdX_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "ErrdX_DT_PtCut_St4_Wh1", "Pt Cut, Error dX/dZ, Station = 4, Wheel = 1", 10000, 0, 0.005);
  h1_ErrdX_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "ErrdX_DT_PtCut_St4_Wh2", "Pt Cut, Error dX/dZ, Station = 4, Wheel = 2", 10000, 0, 0.005);

  h1_ErrdY_DT_PtCut_St1_Wh0 = fs->make<TH1F>( "ErrdY_DT_PtCut_St1_Wh0", "Pt Cut, Error dY/dZ, Station = 1, Wheel = 0", 10000, 0, 0.05);
  h1_ErrdY_DT_PtCut_St1_Wh1 = fs->make<TH1F>( "ErrdY_DT_PtCut_St1_Wh1", "Pt Cut, Error dY/dZ, Station = 1, Wheel = 1", 10000, 0, 0.05);
  h1_ErrdY_DT_PtCut_St1_Wh2 = fs->make<TH1F>( "ErrdY_DT_PtCut_St1_Wh2", "Pt Cut, Error dY/dZ, Station = 1, Wheel = 2", 10000, 0, 0.05);

  h1_ErrdY_DT_PtCut_St2_Wh0 = fs->make<TH1F>( "ErrdY_DT_PtCut_St2_Wh0", "Pt Cut, Error dY/dZ, Station = 2, Wheel = 0", 10000, 0, 0.05);
  h1_ErrdY_DT_PtCut_St2_Wh1 = fs->make<TH1F>( "ErrdY_DT_PtCut_St2_Wh1", "Pt Cut, Error dY/dZ, Station = 2, Wheel = 1", 10000, 0, 0.05);
  h1_ErrdY_DT_PtCut_St2_Wh2 = fs->make<TH1F>( "ErrdY_DT_PtCut_St2_Wh2", "Pt Cut, Error dY/dZ, Station = 2, Wheel = 2", 10000, 0, 0.05);

  h1_ErrdY_DT_PtCut_St3_Wh0 = fs->make<TH1F>( "ErrdY_DT_PtCut_St3_Wh0", "Pt Cut, Error dY/dZ, Station = 3, Wheel = 0", 10000, 0, 0.05);
  h1_ErrdY_DT_PtCut_St3_Wh1 = fs->make<TH1F>( "ErrdY_DT_PtCut_St3_Wh1", "Pt Cut, Error dY/dZ, Station = 3, Wheel = 1", 10000, 0, 0.05);
  h1_ErrdY_DT_PtCut_St3_Wh2 = fs->make<TH1F>( "ErrdY_DT_PtCut_St3_Wh2", "Pt Cut, Error dY/dZ, Station = 3, Wheel = 2", 10000, 0, 0.05);

  h1_ErrdY_DT_PtCut_St4_Wh0 = fs->make<TH1F>( "ErrdY_DT_PtCut_St4_Wh0", "Pt Cut, Error dY/dZ, Station = 4, Wheel = 0", 10000, 0, 0.05);
  h1_ErrdY_DT_PtCut_St4_Wh1 = fs->make<TH1F>( "ErrdY_DT_PtCut_St4_Wh1", "Pt Cut, Error dY/dZ, Station = 4, Wheel = 1", 10000, 0, 0.05);
  h1_ErrdY_DT_PtCut_St4_Wh2 = fs->make<TH1F>( "ErrdY_DT_PtCut_St4_Wh2", "Pt Cut, Error dY/dZ, Station = 4, Wheel = 2", 10000, 0, 0.05);

  h1_ErrdX_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St1_Rg1", "Pt Cut, Error dX/dZ, Station = 1, Ring = 1", 10000, 0, 0.05);
  h1_ErrdX_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St1_Rg2", "Pt Cut, Error dX/dZ, Station = 1, Ring = 2", 10000, 0, 0.05);
  h1_ErrdX_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St1_Rg3", "Pt Cut, Error dX/dZ, Station = 1, Ring = 3", 10000, 0, 0.05);

  h1_ErrdX_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St2_Rg1", "Pt Cut, Error dX/dZ, Station = 2, Ring = 1", 10000, 0, 0.05);
  h1_ErrdX_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St2_Rg2", "Pt Cut, Error dX/dZ, Station = 2, Ring = 2", 10000, 0, 0.05);

  h1_ErrdX_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St3_Rg1", "Pt Cut, Error dX/dZ, Station = 3, Ring = 1", 10000, 0, 0.05);
  h1_ErrdX_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St3_Rg2", "Pt Cut, Error dX/dZ, Station = 3, Ring = 2", 10000, 0, 0.05);

  h1_ErrdX_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St4_Rg1", "Pt Cut, Error dX/dZ, Station = 4, Ring = 1", 10000, 0, 0.05);
  h1_ErrdX_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "ErrdX_CSC_PtCut_St4_Rg2", "Pt Cut, Error dX/dZ, Station = 4, Ring = 2", 10000, 0, 0.05);

  h1_ErrdY_CSC_PtCut_St1_Rg1 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St1_Rg1", "Pt Cut, Error dY/dZ, Station = 1, Ring = 1", 10000, 0, 0.5);
  h1_ErrdY_CSC_PtCut_St1_Rg2 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St1_Rg2", "Pt Cut, Error dY/dZ, Station = 1, Ring = 2", 10000, 0, 0.5);
  h1_ErrdY_CSC_PtCut_St1_Rg3 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St1_Rg3", "Pt Cut, Error dY/dZ, Station = 1, Ring = 3", 10000, 0, 0.5);

  h1_ErrdY_CSC_PtCut_St2_Rg1 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St2_Rg1", "Pt Cut, Error dY/dZ, Station = 2, Ring = 1", 10000, 0, 0.5);
  h1_ErrdY_CSC_PtCut_St2_Rg2 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St2_Rg2", "Pt Cut, Error dY/dZ, Station = 2, Ring = 2", 10000, 0, 0.5);

  h1_ErrdY_CSC_PtCut_St3_Rg1 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St3_Rg1", "Pt Cut, Error dY/dZ, Station = 3, Ring = 1", 10000, 0, 0.5);
  h1_ErrdY_CSC_PtCut_St3_Rg2 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St3_Rg2", "Pt Cut, Error dY/dZ, Station = 3, Ring = 2", 10000, 0, 0.5);

  h1_ErrdY_CSC_PtCut_St4_Rg1 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St4_Rg1", "Pt Cut, Error dY/dZ, Station = 4, Ring = 1", 10000, 0, 0.5);
  h1_ErrdY_CSC_PtCut_St4_Rg2 = fs->make<TH1F>( "ErrdY_CSC_PtCut_St4_Rg2", "Pt Cut, Error dY/dZ, Station = 4, Ring = 2", 10000, 0, 0.5);

  //Errors Vs Reco-Sim
  h2_RecResdX_ErrdX_DT_St1_Wh0 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St1_Wh0", "Station = 1, Wheel = 0", 10000, -5, 5, 10000, 0, 0.005);
  h2_RecResdX_ErrdX_DT_St1_Wh1 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St1_Wh1", "Station = 1, Wheel = 1", 10000, -5, 5, 10000, 0, 0.005);
  h2_RecResdX_ErrdX_DT_St1_Wh2 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St1_Wh2", "Station = 1, Wheel = 2", 10000, -5, 5, 10000, 0, 0.005);

  h2_RecResdX_ErrdX_DT_St2_Wh0 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St2_Wh0", "Station = 2, Wheel = 0", 10000, -5, 5, 10000, 0, 0.005);
  h2_RecResdX_ErrdX_DT_St2_Wh1 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St2_Wh1", "Station = 2, Wheel = 1", 10000, -5, 5, 10000, 0, 0.005);
  h2_RecResdX_ErrdX_DT_St2_Wh2 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St2_Wh2", "Station = 2, Wheel = 2", 10000, -5, 5, 10000, 0, 0.005);

  h2_RecResdX_ErrdX_DT_St3_Wh0 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St3_Wh0", "Station = 3, Wheel = 0", 10000, -5, 5, 10000, 0, 0.005);
  h2_RecResdX_ErrdX_DT_St3_Wh1 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St3_Wh1", "Station = 3, Wheel = 1", 10000, -5, 5, 10000, 0, 0.005);
  h2_RecResdX_ErrdX_DT_St3_Wh2 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St3_Wh2", "Station = 3, Wheel = 2", 10000, -5, 5, 10000, 0, 0.005);

  h2_RecResdX_ErrdX_DT_St4_Wh0 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St4_Wh0", "Station = 4, Wheel = 0", 10000, -5, 5, 10000, 0, 0.005);
  h2_RecResdX_ErrdX_DT_St4_Wh1 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St4_Wh1", "Station = 4, Wheel = 1", 10000, -5, 5, 10000, 0, 0.005);
  h2_RecResdX_ErrdX_DT_St4_Wh2 =  fs->make<TH2F>( "RecResdX_ErrdX_DT_St4_Wh2", "Station = 4, Wheel = 2", 10000, -5, 5, 10000, 0, 0.005);

  h2_RecResdY_ErrdY_DT_St1_Wh0 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St1_Wh0", "Station = 1, Wheel = 0", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DT_St1_Wh1 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St1_Wh1", "Station = 1, Wheel = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DT_St1_Wh2 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St1_Wh2", "Station = 1, Wheel = 2", 10000, -5, 5, 10000, 0, 0.05);

  h2_RecResdY_ErrdY_DT_St2_Wh0 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St2_Wh0", "Station = 2, Wheel = 0", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DT_St2_Wh1 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St2_Wh1", "Station = 2, Wheel = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DT_St2_Wh2 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St2_Wh2", "Station = 2, Wheel = 2", 10000, -5, 5, 10000, 0, 0.05);

  h2_RecResdY_ErrdY_DT_St3_Wh0 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St3_Wh0", "Station = 3, Wheel = 0", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DT_St3_Wh1 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St3_Wh1", "Station = 3, Wheel = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DT_St3_Wh2 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St3_Wh2", "Station = 3, Wheel = 2", 10000, -5, 5, 10000, 0, 0.05);
  
  h2_RecResdY_ErrdY_DT_St4_Wh0 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St4_Wh0", "Station = 4, Wheel = 0", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DT_St4_Wh1 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St4_Wh1", "Station = 4, Wheel = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DT_St4_Wh2 =  fs->make<TH2F>( "RecResdY_ErrdY_DT_St4_Wh2", "Station = 4, Wheel = 2", 10000, -5, 5, 10000, 0, 0.05);

  h2_RecResdX_ErrdX_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdX_ErrdX_CSC_St1_Rg2 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St1_Rg2", "Station = 1, Ring = 2", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdX_ErrdX_CSC_St1_Rg3 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St1_Rg3", "Station = 1, Ring = 3", 10000, -5, 5, 10000, 0, 0.05);

  h2_RecResdX_ErrdX_CSC_St2_Rg1 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St2_Rg1", "Station = 2, Ring = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdX_ErrdX_CSC_St2_Rg2 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St2_Rg2", "Station = 2, Ring = 2", 10000, -5, 5, 10000, 0, 0.05);

  h2_RecResdX_ErrdX_CSC_St3_Rg1 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St3_Rg1", "Station = 3, Ring = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdX_ErrdX_CSC_St3_Rg2 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St3_Rg2", "Station = 3, Ring = 2", 10000, -5, 5, 10000, 0, 0.05);

  h2_RecResdX_ErrdX_CSC_St4_Rg1 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St4_Rg1", "Station = 4, Ring = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdX_ErrdX_CSC_St4_Rg2 = fs->make<TH2F>( "RecResdX_ErrdX_CSC_St4_Rg2", "Station = 4, Ring = 2", 10000, -5, 5, 10000, 0, 0.05);

  h2_RecResdY_ErrdY_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.5);
  h2_RecResdY_ErrdY_CSC_St1_Rg2 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St1_Rg2", "Station = 1, Ring = 2", 10000, -5, 5, 10000, 0, 0.5);
  h2_RecResdY_ErrdY_CSC_St1_Rg3 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St1_Rg3", "Station = 1, Ring = 3", 10000, -5, 5, 10000, 0, 0.5);

  h2_RecResdY_ErrdY_CSC_St2_Rg1 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St2_Rg1", "Station = 2, Ring = 1", 10000, -5, 5, 10000, 0, 0.5);
  h2_RecResdY_ErrdY_CSC_St2_Rg2 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St2_Rg2", "Station = 2, Ring = 2", 10000, -5, 5, 10000, 0, 0.5);

  h2_RecResdY_ErrdY_CSC_St3_Rg1 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St3_Rg1", "Station = 3, Ring = 1", 10000, -5, 5, 10000, 0, 0.5);
  h2_RecResdY_ErrdY_CSC_St3_Rg2 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St3_Rg2", "Station = 3, Ring = 2", 10000, -5, 5, 10000, 0, 0.5);

  h2_RecResdY_ErrdY_CSC_St4_Rg1 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St4_Rg1", "Station = 4, Ring = 1", 10000, -5, 5, 10000, 0, 0.5);
  h2_RecResdY_ErrdY_CSC_St4_Rg2 = fs->make<TH2F>( "RecResdY_ErrdY_CSC_St4_Rg2", "Station = 4, Ring = 2", 10000, -5, 5, 10000, 0, 0.5);

  //Other plots to track the station 1, ring 1 of the CSC
  h2_RecResdX_ErrdX_UpStation1_DirZ_1_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdX_ErrdX_UpStation1_DirZ_1_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_UpStation1_DirZ_1_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdY_ErrdY_UpStation1_DirZ_1_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.5);
  h2_RecResdX_ErrdX_DwStation1_DirZ_1_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdX_ErrdX_DwStation1_DirZ_1_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DwStation1_DirZ_1_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdY_ErrdY_DwStation1_DirZ_1_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.5);

  h2_RecResdX_ErrdX_UpStation1_DirZ_m1_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdX_ErrdX_UpStation1_DirZ_m1_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_UpStation1_DirZ_m1_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdY_ErrdY_UpStation1_DirZ_m1_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.5);
  h2_RecResdX_ErrdX_DwStation1_DirZ_m1_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdX_ErrdX_DwStation1_DirZ_m1_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.05);
  h2_RecResdY_ErrdY_DwStation1_DirZ_m1_CSC_St1_Rg1 = fs->make<TH2F>( "RecResdY_ErrdY_DwStation1_DirZ_m1_CSC_St1_Rg1", "Station = 1, Ring = 1", 10000, -5, 5, 10000, 0, 0.5);

  h2_SimX_SimY_DwStation1_DirZ_1_CSC_St1_Rg1  = fs->make<TH2F>(  "SimX_SimY_DwStation1_DirZ_1_CSC_St1_Rg1", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc}, Station = 1, Ring = 1, CSC", 2000, -100, 100, 2000, -100, 100);
  h2_SimX_SimY_DwStation1_DirZ_m1_CSC_St1_Rg1 = fs->make<TH2F>( "SimX_SimY_DwStation1_DirZ_m1_CSC_St1_Rg1", "X_{Sim}^{Loc} Vs Y_{Sim}^{Loc}, Station = 1, Ring = 1, CSC", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_DwStation1_DirZ_1_CSC_St1_Rg1  = fs->make<TH2F>(  "RecX_RecY_DwStation1_DirZ_1_CSC_St1_Rg1", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc}, Station = 1, Ring = 1, CSC", 2000, -100, 100, 2000, -100, 100);
  h2_RecX_RecY_DwStation1_DirZ_m1_CSC_St1_Rg1 = fs->make<TH2F>( "RecX_RecY_DwStation1_DirZ_m1_CSC_St1_Rg1", "X_{Rec}^{Loc} Vs Y_{Rec}^{Loc}, Station = 1, Ring = 1, CSC", 2000, -100, 100, 2000, -100, 100);

  //Track segment situation
  h1_1Seg_DT  = fs->make<TH1F>(  "1Seg_DT", "Segment Used in the Track", 4, 1, 5);
  h1_1Seg_CSC = fs->make<TH1F>( "1Seg_CSC", "Segment Used in the Track", 4, 1, 5);

  h2_2Seg_DT  = fs->make<TH2F>(   "2Seg_DT", "Segments Used in the Track", 4, 1, 5, 4, 1, 5);
  h2_2Seg_CSC = fs->make<TH2F>(  "2Seg_CSC", "Segments Used in the Track", 4, 1, 5, 4, 1, 5);

  h2_1Seg_DT_1Seg_CSC = fs->make<TH2F>(  "1Seg_DT_1Seg_CSC", "Segments Used in the Track", 4, 1, 5, 4, 1, 5);

  h1_3Seg_DT  = fs->make<TH1F>(  "3Seg_DT", "Segment Used in the Track", 4, 1, 5);
  h1_3Seg_CSC = fs->make<TH1F>( "3Seg_CSC", "Segment Used in the Track", 4, 1, 5);
 
}

void DYTthrScanTuner::endJob()  {}

void DYTthrScanTuner::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

LocalPoint DYTthrScanTuner::meanPoint(LocalPoint InfPoint, LocalPoint SupPoint){

	//initialization parameters
	float a = 0; float b = 0; float c = 0;
	float x1 = 0; float y1 = 0; float z1 = 0;
	float meanX = 0; float meanY = 0; float meanZ = 0;
	
	//Assignement
	a = InfPoint.x() - SupPoint.x(); 
	b = InfPoint.y() - SupPoint.y(); 
	c = InfPoint.z() - SupPoint.z();
	x1 = InfPoint.x(); 
	y1 = InfPoint.y(); 
	z1 = InfPoint.z();

	//Computation of the coordinates for the simSegment in the local frame of the chamber for Z=0; the coordinate are obtained using the cartesian solution.
	//Considering the local framwork of the Chambers it is not supposed to have c=0 because the track travels in the inside-out direction which is the direction and versus of the z local axis.
	//If it happens it means that something is wrong.
	if( c == 0 ){ std::cout << "Ooooppsss...something wrong happens in the local frame..." << std::endl; meanX = -1E10; meanY = -1E10; meanZ = -1E10; }
	if( a != 0 && b != 0 ){ meanX = x1 - (a/c)*z1; meanY = y1 - (b/c)*z1; meanZ = 0.; } 
	else if( a == 0 && b != 0 ){ meanX = x1; meanY = y1 - (b/c)*z1; meanZ = 0.; }
	else if( a != 0 && b == 0 ){ meanX = x1 - (a/c)*z1; meanY = y1; meanZ = 0.; } 
	else if( a == 0 && b == 0 ){ meanX = x1; meanY = y1; meanZ = 0; } 

	LocalPoint meanPoint( meanX, meanY, meanZ); 

	return meanPoint;
}

DEFINE_FWK_MODULE(DYTthrScanTuner);
