
//
// Package:    DYTAnalyzer
// Class:      DYTAnalyzer
//
/**\class DYTAnalyzer DYTAnalyzer.cc Analysis/DYTAnalyzer/src/DYTAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Davide Pagano (Collaboration with G. Bruno)
//         Created:  Tue Jun 12 16:03:01 CEST 2012
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
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/DYTInfo.h"
#include "DataFormats/TrackReco/interface/TrackToTrackMap.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

class DYTAnalyzer : public edm::EDAnalyzer {
public:
  explicit DYTAnalyzer(const edm::ParameterSet&);
  ~DYTAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  inline bool isHighPtMuon(const reco::Muon& muon, const reco::Vertex& vtx){
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

   bool ip = fabs(muon.innerTrack()->dxy(vtx.position())) < 0.2 && fabs(muon.innerTrack()->dz(vtx.position())) < 0.5;

   return muID && hits && momQuality && ip;

  }

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

  typedef edm::ValueMap<reco::DYTInfo> DYTestimators;
  double psim;
  double ptsim;
  double pgen;
  double ptgen;
  bool useSelections;
  int cntest = 0;

  edm::EDGetTokenT<reco::MuonCollection> muon_label_;
  edm::EDGetTokenT<std::vector<reco::Vertex>> vertex_label_;
  edm::EDGetTokenT<reco::GenParticleCollection> gpar_label_;

  //Estimator Vs Momentum
  TH2F *EstVsMomentum1, *EstVsMomentum1B, *EstVsMomentum1E;
  TH2F *EstVsMomentum2, *EstVsMomentum2B, *EstVsMomentum2E;
  TH2F *EstVsMomentum3, *EstVsMomentum3B, *EstVsMomentum3E;
  TH2F *EstVsMomentum4, *EstVsMomentum4B, *EstVsMomentum4E;

  TH2F *EstVsMomentumPreFit1, *EstVsMomentumPreFit1B, *EstVsMomentumPreFit1E;
  TH2F *EstVsMomentumPreFit2, *EstVsMomentumPreFit2B, *EstVsMomentumPreFit2E;
  TH2F *EstVsMomentumPreFit3, *EstVsMomentumPreFit3B, *EstVsMomentumPreFit3E;
  TH2F *EstVsMomentumPreFit4, *EstVsMomentumPreFit4B, *EstVsMomentumPreFit4E;

  //Definition Estimator Histo
  TH1F *Ests1,       *Ests2,        *Ests3,    *Ests4;
  TH1F *Ests1B,      *Ests2B,       *Ests3B,   *Ests4B;
  TH1F *Ests1E,      *Ests2E,       *Ests3E,   *Ests4E;
  TH1F *Tester;

  //Definition of the Estimator (mean value) for different bin of eta (the scan is the same of the Residui, they are filled inside the if condition for the estimation of the Efficency)
  TH1F *Ests_M24,  *Ests_M21,  *Ests_M18,  *Ests_M15,  *Ests_M12,  *Ests_M09,  *Ests_M06,  *Ests_M03;
  TH1F *Ests_M0,   *Ests_P03,  *Ests_P06,  *Ests_P09,  *Ests_P12,  *Ests_P15,  *Ests_P18,  *Ests_P21;

  //Definition of Histo to study the fit curve for the Estimator
  TH1F *Ests1_0,   *Ests2_0,   *Ests3_0,   *Ests4_0;
  TH1F *Ests1_08,  *Ests2_08,  *Ests3_08,  *Ests4_08;
  TH1F *Ests1_12,  *Ests2_12,  *Ests3_12,  *Ests4_12;
  TH1F *Ests1_16,  *Ests2_16,  *Ests3_16,  *Ests4_16;
  TH1F *Ests1_20,  *Ests2_20,  *Ests3_20,  *Ests4_20;

  TH1F *NStUs,       *NStUsB,       *NStUsE;

  //Definition HighPtID eff
  TH1F *eff_pt_HighPtID_den,      *eff_pt_HighPtID_denB,      *eff_pt_HighPtID_denE;
  TH1F *eff_pt_HighPtID_num,      *eff_pt_HighPtID_numB,      *eff_pt_HighPtID_numE;
  TH1F *eff_eta_HighPtID_den,      *eff_eta_HighPtID_denB,      *eff_eta_HighPtID_denE;
  TH1F *eff_eta_HighPtID_num,      *eff_eta_HighPtID_numB,      *eff_eta_HighPtID_numE;

  //Definition number of Hists
  TH1F *NHits_StdA,      *NHits_GLB,     *NHits_Picky,     *NHits_TuneP,     *NHits_DYT,    *NHits_TrkM;
  TH1F *NHits_StdA_B,    *NHits_GLB_B,   *NHits_Picky_B,   *NHits_TuneP_B,   *NHits_DYT_B,  *NHits_TrkM_B;
  TH1F *NHits_StdA_E,    *NHits_GLB_E,   *NHits_Picky_E,   *NHits_TuneP_E,   *NHits_DYT_E,  *NHits_TrkM_E;

  // Definition TuneP Muon track type
  TH1F *TuneP_MuonTrackType;
  TH1F *TuneP_MuonTrackTypeB;
  TH1F *TuneP_MuonTrackTypeE;

  //Definition difference of transverse momentum reco and gen
  TH1F *InvDYT_pt,   *InvDYT_ptB,   *InvDYT_ptE;
  TH1F *InvTuneP_pt, *InvTuneP_ptB, *InvTuneP_ptE;
  TH1F *InvPicky_pt, *InvPicky_ptB, *InvPicky_ptE;
  TH1F *InvGLB_pt,   *InvGLB_ptB,   *InvGLB_ptE;
  TH1F *InvStdA_pt,  *InvStdA_ptB,  *InvStdA_ptE;
  TH1F *InvTrkM_pt,  *InvTrkM_ptB,  *InvTrkM_ptE;

  //Definition of P Histo
  TH1F *DYT_p,      *DYT_pB,      *DYT_pE;
  TH1F *TuneP_p,    *TuneP_pB,    *TuneP_pE;
  TH1F *TuneP_onlyDyT_p,    *TuneP_onlyDyT_pB,    *TuneP_onlyDyT_pE;
  TH1F *TuneP_onlyDyT_Res_Invp, *TuneP_onlyDyT_Res_InvpB, *TuneP_onlyDyT_Res_InvpE;
  TH1F *Picky_p,    *Picky_pB,    *Picky_pE;
  TH1F *GLB_p,      *GLB_pB,      *GLB_pE;
  TH1F *StdA_p,     *StdA_pB,     *StdA_pE;

  //Definition of P Spectrum in eta bins
  TH1F *DYT_sp,    *DYT_spE08,    *DYT_spE12,  *DYT_spE20, *DYT_spE22,  *DYT_spE24;
  TH1F *TuneP_spE08,    *TuneP_spE12,  *TuneP_spE20, *TuneP_spE22,  *TuneP_spE24;
  TH1F *DYT_Res_InvpE08,    *DYT_Res_InvpE12,  *DYT_Res_InvpE20, *DYT_Res_InvpE22,  *DYT_Res_InvpE24;
  TH1F *TuneP_Res_InvpE08,    *TuneP_Res_InvpE12,  *TuneP_Res_InvpE20, *TuneP_Res_InvpE22,  *TuneP_Res_InvpE24;

  //Definition of P OverFlow Histo
  TH1F *DYT_pOv,      *DYT_pBOv,      *DYT_pEOv;
  TH1F *TuneP_pOv,    *TuneP_pBOv,    *TuneP_pEOv;
  TH1F *Picky_pOv,    *Picky_pBOv,    *Picky_pEOv;
  TH1F *GLB_pOv,      *GLB_pBOv,      *GLB_pEOv;
  TH1F *StdA_pOv,     *StdA_pBOv,     *StdA_pEOv;

  //Definition pT Histo
  TH1F *DYT_pt,      *DYT_ptB,      *DYT_ptE;
  TH1F *TuneP_pt,    *TuneP_ptB,    *TuneP_ptE;
  TH1F *Picky_pt,    *Picky_ptB,    *Picky_ptE;
  TH1F *GLB_pt,      *GLB_ptB,      *GLB_ptE;
  TH1F *StdA_pt,     *StdA_ptB,     *StdA_ptE;
  TH1F *TrkM_pt,     *TrkM_ptB,     *TrkM_ptE;

  //Definition Eta and Phi Histo
  TH1F *DYT_eta,     *DYT_phi;
  TH1F *TuneP_eta,   *TuneP_phi;
  TH1F *Picky_eta,   *Picky_phi;
  TH1F *GLB_eta,     *GLB_phi;
  TH1F *StdA_eta,    *StdA_phi;
  TH1F *TrkM_eta,    *TrkM_phi;

  //Sigma di q/p
  TH1F  *DYT_SqP,    *DYT_SqPB,    *DYT_SqPE;
  TH1F  *TuneP_SqP,  *TuneP_SqPB,  *TuneP_SqPE;
  TH1F  *Picky_SqP,  *Picky_SqPB,  *Picky_SqPE;
  TH1F  *GLB_SqP,    *GLB_SqPB,    *GLB_SqPE;
  TH1F  *StdA_SqP,   *StdA_SqPB,   *StdA_SqPE;

  //Sigma di q/p
  TH1F  *DYT_SqInvPt,    *DYT_SqInvPtB,    *DYT_SqInvPtE;
  TH1F  *TuneP_SqInvPt,  *TuneP_SqInvPtB,  *TuneP_SqInvPtE;
  TH1F  *Picky_SqInvPt,  *Picky_SqInvPtB,  *Picky_SqInvPtE;
  TH1F  *GLB_SqInvPt,    *GLB_SqInvPtB,    *GLB_SqInvPtE;
  TH1F  *StdA_SqInvPt,   *StdA_SqInvPtB,   *StdA_SqInvPtE;

  //Sigma_pt over pt
  TH1F  *DYT_SPtOverPt,    *DYT_SPtOverPtB,    *DYT_SPtOverPtE;
  TH1F  *TuneP_SPtOverPt,  *TuneP_SPtOverPtB,  *TuneP_SPtOverPtE;
  TH1F  *Picky_SPtOverPt,  *Picky_SPtOverPtB,  *Picky_SPtOverPtE;
  TH1F  *GLB_SPtOverPt,    *GLB_SPtOverPtB,    *GLB_SPtOverPtE;
  TH1F  *StdA_SPtOverPt,   *StdA_SPtOverPtB,   *StdA_SPtOverPtE;

  //Sigma_InvPt ove InvPt
  TH1F  *DYT_SInvPOverP,    *DYT_SInvPOverPB,    *DYT_SInvPOverPE;
  TH1F  *TuneP_SInvPOverP,  *TuneP_SInvPOverPB,  *TuneP_SInvPOverPE;
  TH1F  *Picky_SInvPOverP,  *Picky_SInvPOverPB,  *Picky_SInvPOverPE;
  TH1F  *GLB_SInvPOverP,    *GLB_SInvPOverPB,    *GLB_SInvPOverPE;
  TH1F  *StdA_SInvPOverP,   *StdA_SInvPOverPB,   *StdA_SInvPOverPE;

  //Definition Chi Square
  TH1F *Chi2N_StdA,        *Chi2N_GLB,      *Chi2N_Picky,     *Chi2N_TuneP,       *Chi2N_DYT,      *Chi2N_TrkM;
  TH1F *Chi2N_StdA_B,      *Chi2N_GLB_B,    *Chi2N_Picky_B,   *Chi2N_TuneP_B,     *Chi2N_DYT_B,    *Chi2N_TrkM_B;
  TH1F *Chi2N_StdA_E,      *Chi2N_GLB_E,    *Chi2N_Picky_E,   *Chi2N_TuneP_E,     *Chi2N_DYT_E,    *Chi2N_TrkM_E;

  //Definition of Resolution for Inverse Pt tra -2.4 e 0 (Eta, width 0.3)
  TH1F *ResInvPt_Eta_DYT_M24,     *ResInvPt_Eta_DYT_M21,     *ResInvPt_Eta_DYT_M18,      *ResInvPt_Eta_DYT_M15,     *ResInvPt_Eta_DYT_M12,    *ResInvPt_Eta_DYT_M09,    *ResInvPt_Eta_DYT_M06,    *ResInvPt_Eta_DYT_M03,    *ResInvPt_Eta_DYT_M0;
  TH1F *ResInvPt_Eta_TuneP_M24,   *ResInvPt_Eta_TuneP_M21,   *ResInvPt_Eta_TuneP_M18,    *ResInvPt_Eta_TuneP_M15,   *ResInvPt_Eta_TuneP_M12,  *ResInvPt_Eta_TuneP_M09,  *ResInvPt_Eta_TuneP_M06,  *ResInvPt_Eta_TuneP_M03,  *ResInvPt_Eta_TuneP_M0;
  TH1F *ResInvPt_Eta_Picky_M24,   *ResInvPt_Eta_Picky_M21,   *ResInvPt_Eta_Picky_M18,    *ResInvPt_Eta_Picky_M15,   *ResInvPt_Eta_Picky_M12,  *ResInvPt_Eta_Picky_M09,  *ResInvPt_Eta_Picky_M06,  *ResInvPt_Eta_Picky_M03,  *ResInvPt_Eta_Picky_M0;
  TH1F *ResInvPt_Eta_GLB_M24,     *ResInvPt_Eta_GLB_M21,     *ResInvPt_Eta_GLB_M18,      *ResInvPt_Eta_GLB_M15,     *ResInvPt_Eta_GLB_M12,    *ResInvPt_Eta_GLB_M09,    *ResInvPt_Eta_GLB_M06,    *ResInvPt_Eta_GLB_M03,    *ResInvPt_Eta_GLB_M0;
  TH1F *ResInvPt_Eta_StdA_M24,    *ResInvPt_Eta_StdA_M21,    *ResInvPt_Eta_StdA_M18,     *ResInvPt_Eta_StdA_M15,    *ResInvPt_Eta_StdA_M12,   *ResInvPt_Eta_StdA_M09,   *ResInvPt_Eta_StdA_M06,   *ResInvPt_Eta_StdA_M03,   *ResInvPt_Eta_StdA_M0;

  //Definition of Resolution for Inverse Pt tra 0.3 e 2.4 (Eta, width 0.3)
  TH1F *ResInvPt_Eta_DYT_P03,     *ResInvPt_Eta_DYT_P06,     *ResInvPt_Eta_DYT_P09,      *ResInvPt_Eta_DYT_P12,     *ResInvPt_Eta_DYT_P15,    *ResInvPt_Eta_DYT_P18,    *ResInvPt_Eta_DYT_P21;
  TH1F *ResInvPt_Eta_TuneP_P03,   *ResInvPt_Eta_TuneP_P06,   *ResInvPt_Eta_TuneP_P09,    *ResInvPt_Eta_TuneP_P12,   *ResInvPt_Eta_TuneP_P15,  *ResInvPt_Eta_TuneP_P18,  *ResInvPt_Eta_TuneP_P21;
  TH1F *ResInvPt_Eta_Picky_P03,   *ResInvPt_Eta_Picky_P06,   *ResInvPt_Eta_Picky_P09,    *ResInvPt_Eta_Picky_P12,   *ResInvPt_Eta_Picky_P15,  *ResInvPt_Eta_Picky_P18,  *ResInvPt_Eta_Picky_P21;
  TH1F *ResInvPt_Eta_GLB_P03,     *ResInvPt_Eta_GLB_P06,     *ResInvPt_Eta_GLB_P09,      *ResInvPt_Eta_GLB_P12,     *ResInvPt_Eta_GLB_P15,    *ResInvPt_Eta_GLB_P18,    *ResInvPt_Eta_GLB_P21;
  TH1F *ResInvPt_Eta_StdA_P03,    *ResInvPt_Eta_StdA_P06,    *ResInvPt_Eta_StdA_P09,     *ResInvPt_Eta_StdA_P12,    *ResInvPt_Eta_StdA_P15,   *ResInvPt_Eta_StdA_P18,   *ResInvPt_Eta_StdA_P21;

  //Definition of Resolution for Inverse Pt tra -3.6 e 0 (Phi, width 0.4)
  TH1F *ResInvPt_Phi_DYT_M36,     *ResInvPt_Phi_DYT_M32,     *ResInvPt_Phi_DYT_M28,     *ResInvPt_Phi_DYT_M24,     *ResInvPt_Phi_DYT_M20,      *ResInvPt_Phi_DYT_M16,      *ResInvPt_Phi_DYT_M12,     *ResInvPt_Phi_DYT_M08,     *ResInvPt_Phi_DYT_M04,     *ResInvPt_Phi_DYT_M0;
  TH1F *ResInvPt_Phi_TuneP_M36,   *ResInvPt_Phi_TuneP_M32,   *ResInvPt_Phi_TuneP_M28,   *ResInvPt_Phi_TuneP_M24,   *ResInvPt_Phi_TuneP_M20,    *ResInvPt_Phi_TuneP_M16,    *ResInvPt_Phi_TuneP_M12,   *ResInvPt_Phi_TuneP_M08,   *ResInvPt_Phi_TuneP_M04,   *ResInvPt_Phi_TuneP_M0;
  TH1F *ResInvPt_Phi_Picky_M36,   *ResInvPt_Phi_Picky_M32,   *ResInvPt_Phi_Picky_M28,   *ResInvPt_Phi_Picky_M24,   *ResInvPt_Phi_Picky_M20,    *ResInvPt_Phi_Picky_M16,    *ResInvPt_Phi_Picky_M12,   *ResInvPt_Phi_Picky_M08,   *ResInvPt_Phi_Picky_M04,   *ResInvPt_Phi_Picky_M0;
  TH1F *ResInvPt_Phi_GLB_M36,     *ResInvPt_Phi_GLB_M32,     *ResInvPt_Phi_GLB_M28,     *ResInvPt_Phi_GLB_M24,     *ResInvPt_Phi_GLB_M20,      *ResInvPt_Phi_GLB_M16,      *ResInvPt_Phi_GLB_M12,     *ResInvPt_Phi_GLB_M08,     *ResInvPt_Phi_GLB_M04,     *ResInvPt_Phi_GLB_M0;
  TH1F *ResInvPt_Phi_StdA_M36,    *ResInvPt_Phi_StdA_M32,    *ResInvPt_Phi_StdA_M28,    *ResInvPt_Phi_StdA_M24,    *ResInvPt_Phi_StdA_M20,     *ResInvPt_Phi_StdA_M16,     *ResInvPt_Phi_StdA_M12,    *ResInvPt_Phi_StdA_M08,    *ResInvPt_Phi_StdA_M04,    *ResInvPt_Phi_StdA_M0;

  //Definition of Resolution for Inverse Pt tra 0 e 3.6 (Phi, width 0.4)
  TH1F *ResInvPt_Phi_DYT_P04,     *ResInvPt_Phi_DYT_P08,     *ResInvPt_Phi_DYT_P12,     *ResInvPt_Phi_DYT_P16,     *ResInvPt_Phi_DYT_P20,      *ResInvPt_Phi_DYT_P24,      *ResInvPt_Phi_DYT_P28,     *ResInvPt_Phi_DYT_P32,     *ResInvPt_Phi_DYT_P36;
  TH1F *ResInvPt_Phi_TuneP_P04,   *ResInvPt_Phi_TuneP_P08,   *ResInvPt_Phi_TuneP_P12,   *ResInvPt_Phi_TuneP_P16,   *ResInvPt_Phi_TuneP_P20,    *ResInvPt_Phi_TuneP_P24,    *ResInvPt_Phi_TuneP_P28,   *ResInvPt_Phi_TuneP_P32,   *ResInvPt_Phi_TuneP_P36;
  TH1F *ResInvPt_Phi_Picky_P04,   *ResInvPt_Phi_Picky_P08,   *ResInvPt_Phi_Picky_P12,   *ResInvPt_Phi_Picky_P16,   *ResInvPt_Phi_Picky_P20,    *ResInvPt_Phi_Picky_P24,    *ResInvPt_Phi_Picky_P28,   *ResInvPt_Phi_Picky_P32,   *ResInvPt_Phi_Picky_P36;
  TH1F *ResInvPt_Phi_GLB_P04,     *ResInvPt_Phi_GLB_P08,     *ResInvPt_Phi_GLB_P12,     *ResInvPt_Phi_GLB_P16,     *ResInvPt_Phi_GLB_P20,      *ResInvPt_Phi_GLB_P24,      *ResInvPt_Phi_GLB_P28,     *ResInvPt_Phi_GLB_P32,     *ResInvPt_Phi_GLB_P36;
  TH1F *ResInvPt_Phi_StdA_P04,    *ResInvPt_Phi_StdA_P08,    *ResInvPt_Phi_StdA_P12,    *ResInvPt_Phi_StdA_P16,    *ResInvPt_Phi_StdA_P20,     *ResInvPt_Phi_StdA_P24,     *ResInvPt_Phi_StdA_P28,    *ResInvPt_Phi_StdA_P32,    *ResInvPt_Phi_StdA_P36;

  //Definition of Resolution for Pt tra -2.4 e 0 (Eta, width 0.3)
  TH1F *ResPt_Eta_DYT_M24,     *ResPt_Eta_DYT_M21,     *ResPt_Eta_DYT_M18,      *ResPt_Eta_DYT_M15,     *ResPt_Eta_DYT_M12,    *ResPt_Eta_DYT_M09,    *ResPt_Eta_DYT_M06,    *ResPt_Eta_DYT_M03,    *ResPt_Eta_DYT_M0;
  TH1F *ResPt_Eta_TuneP_M24,   *ResPt_Eta_TuneP_M21,   *ResPt_Eta_TuneP_M18,    *ResPt_Eta_TuneP_M15,   *ResPt_Eta_TuneP_M12,  *ResPt_Eta_TuneP_M09,  *ResPt_Eta_TuneP_M06,  *ResPt_Eta_TuneP_M03,  *ResPt_Eta_TuneP_M0;
  TH1F *ResPt_Eta_Picky_M24,   *ResPt_Eta_Picky_M21,   *ResPt_Eta_Picky_M18,    *ResPt_Eta_Picky_M15,   *ResPt_Eta_Picky_M12,  *ResPt_Eta_Picky_M09,  *ResPt_Eta_Picky_M06,  *ResPt_Eta_Picky_M03,  *ResPt_Eta_Picky_M0;
  TH1F *ResPt_Eta_GLB_M24,     *ResPt_Eta_GLB_M21,     *ResPt_Eta_GLB_M18,      *ResPt_Eta_GLB_M15,     *ResPt_Eta_GLB_M12,    *ResPt_Eta_GLB_M09,    *ResPt_Eta_GLB_M06,    *ResPt_Eta_GLB_M03,    *ResPt_Eta_GLB_M0;
  TH1F *ResPt_Eta_StdA_M24,    *ResPt_Eta_StdA_M21,    *ResPt_Eta_StdA_M18,     *ResPt_Eta_StdA_M15,    *ResPt_Eta_StdA_M12,   *ResPt_Eta_StdA_M09,   *ResPt_Eta_StdA_M06,   *ResPt_Eta_StdA_M03,   *ResPt_Eta_StdA_M0;

  //Definition of Resolution for Pt tra 0.3 e 2.4 (Eta, width 0.3)
  TH1F *ResPt_Eta_DYT_P03,     *ResPt_Eta_DYT_P06,     *ResPt_Eta_DYT_P09,      *ResPt_Eta_DYT_P12,     *ResPt_Eta_DYT_P15,    *ResPt_Eta_DYT_P18,    *ResPt_Eta_DYT_P21;
  TH1F *ResPt_Eta_TuneP_P03,   *ResPt_Eta_TuneP_P06,   *ResPt_Eta_TuneP_P09,    *ResPt_Eta_TuneP_P12,   *ResPt_Eta_TuneP_P15,  *ResPt_Eta_TuneP_P18,  *ResPt_Eta_TuneP_P21;
  TH1F *ResPt_Eta_Picky_P03,   *ResPt_Eta_Picky_P06,   *ResPt_Eta_Picky_P09,    *ResPt_Eta_Picky_P12,   *ResPt_Eta_Picky_P15,  *ResPt_Eta_Picky_P18,  *ResPt_Eta_Picky_P21;
  TH1F *ResPt_Eta_GLB_P03,     *ResPt_Eta_GLB_P06,     *ResPt_Eta_GLB_P09,      *ResPt_Eta_GLB_P12,     *ResPt_Eta_GLB_P15,    *ResPt_Eta_GLB_P18,    *ResPt_Eta_GLB_P21;
  TH1F *ResPt_Eta_StdA_P03,    *ResPt_Eta_StdA_P06,    *ResPt_Eta_StdA_P09,     *ResPt_Eta_StdA_P12,    *ResPt_Eta_StdA_P15,   *ResPt_Eta_StdA_P18,   *ResPt_Eta_StdA_P21;

  //Definition of Resolution for Pt tra -3.6 e 0 (Phi, width 0.4)
  TH1F *ResPt_Phi_DYT_M36,     *ResPt_Phi_DYT_M32,     *ResPt_Phi_DYT_M28,     *ResPt_Phi_DYT_M24,     *ResPt_Phi_DYT_M20,      *ResPt_Phi_DYT_M16,      *ResPt_Phi_DYT_M12,     *ResPt_Phi_DYT_M08,     *ResPt_Phi_DYT_M04,     *ResPt_Phi_DYT_M0;
  TH1F *ResPt_Phi_TuneP_M36,   *ResPt_Phi_TuneP_M32,   *ResPt_Phi_TuneP_M28,   *ResPt_Phi_TuneP_M24,   *ResPt_Phi_TuneP_M20,    *ResPt_Phi_TuneP_M16,    *ResPt_Phi_TuneP_M12,   *ResPt_Phi_TuneP_M08,   *ResPt_Phi_TuneP_M04,   *ResPt_Phi_TuneP_M0;
  TH1F *ResPt_Phi_Picky_M36,   *ResPt_Phi_Picky_M32,   *ResPt_Phi_Picky_M28,   *ResPt_Phi_Picky_M24,   *ResPt_Phi_Picky_M20,    *ResPt_Phi_Picky_M16,    *ResPt_Phi_Picky_M12,   *ResPt_Phi_Picky_M08,   *ResPt_Phi_Picky_M04,   *ResPt_Phi_Picky_M0;
  TH1F *ResPt_Phi_GLB_M36,     *ResPt_Phi_GLB_M32,     *ResPt_Phi_GLB_M28,     *ResPt_Phi_GLB_M24,     *ResPt_Phi_GLB_M20,      *ResPt_Phi_GLB_M16,      *ResPt_Phi_GLB_M12,     *ResPt_Phi_GLB_M08,     *ResPt_Phi_GLB_M04,     *ResPt_Phi_GLB_M0;
  TH1F *ResPt_Phi_StdA_M36,    *ResPt_Phi_StdA_M32,    *ResPt_Phi_StdA_M28,    *ResPt_Phi_StdA_M24,    *ResPt_Phi_StdA_M20,     *ResPt_Phi_StdA_M16,     *ResPt_Phi_StdA_M12,    *ResPt_Phi_StdA_M08,    *ResPt_Phi_StdA_M04,    *ResPt_Phi_StdA_M0;

  //Definition of Resolution for Pt tra 0 e 3.6 (Phi, width 0.4)
  TH1F *ResPt_Phi_DYT_P04,     *ResPt_Phi_DYT_P08,     *ResPt_Phi_DYT_P12,     *ResPt_Phi_DYT_P16,     *ResPt_Phi_DYT_P20,      *ResPt_Phi_DYT_P24,      *ResPt_Phi_DYT_P28,     *ResPt_Phi_DYT_P32,     *ResPt_Phi_DYT_P36;
  TH1F *ResPt_Phi_TuneP_P04,   *ResPt_Phi_TuneP_P08,   *ResPt_Phi_TuneP_P12,   *ResPt_Phi_TuneP_P16,   *ResPt_Phi_TuneP_P20,    *ResPt_Phi_TuneP_P24,    *ResPt_Phi_TuneP_P28,   *ResPt_Phi_TuneP_P32,   *ResPt_Phi_TuneP_P36;
  TH1F *ResPt_Phi_Picky_P04,   *ResPt_Phi_Picky_P08,   *ResPt_Phi_Picky_P12,   *ResPt_Phi_Picky_P16,   *ResPt_Phi_Picky_P20,    *ResPt_Phi_Picky_P24,    *ResPt_Phi_Picky_P28,   *ResPt_Phi_Picky_P32,   *ResPt_Phi_Picky_P36;
  TH1F *ResPt_Phi_GLB_P04,     *ResPt_Phi_GLB_P08,     *ResPt_Phi_GLB_P12,     *ResPt_Phi_GLB_P16,     *ResPt_Phi_GLB_P20,      *ResPt_Phi_GLB_P24,      *ResPt_Phi_GLB_P28,     *ResPt_Phi_GLB_P32,     *ResPt_Phi_GLB_P36;
  TH1F *ResPt_Phi_StdA_P04,    *ResPt_Phi_StdA_P08,    *ResPt_Phi_StdA_P12,    *ResPt_Phi_StdA_P16,    *ResPt_Phi_StdA_P20,     *ResPt_Phi_StdA_P24,     *ResPt_Phi_StdA_P28,    *ResPt_Phi_StdA_P32,    *ResPt_Phi_StdA_P36;

  //Definition of Resolution for Pt tra -2.4 e 0 (Eta, width 0.3)
  TH1F *ResInvP_Eta_DYT_M24,     *ResInvP_Eta_DYT_M21,     *ResInvP_Eta_DYT_M18,      *ResInvP_Eta_DYT_M15,     *ResInvP_Eta_DYT_M12,    *ResInvP_Eta_DYT_M09,    *ResInvP_Eta_DYT_M06,    *ResInvP_Eta_DYT_M03,    *ResInvP_Eta_DYT_M0;
  TH1F *ResInvP_Eta_TuneP_M24,   *ResInvP_Eta_TuneP_M21,   *ResInvP_Eta_TuneP_M18,    *ResInvP_Eta_TuneP_M15,   *ResInvP_Eta_TuneP_M12,  *ResInvP_Eta_TuneP_M09,  *ResInvP_Eta_TuneP_M06,  *ResInvP_Eta_TuneP_M03,  *ResInvP_Eta_TuneP_M0;
  TH1F *ResInvP_Eta_Picky_M24,   *ResInvP_Eta_Picky_M21,   *ResInvP_Eta_Picky_M18,    *ResInvP_Eta_Picky_M15,   *ResInvP_Eta_Picky_M12,  *ResInvP_Eta_Picky_M09,  *ResInvP_Eta_Picky_M06,  *ResInvP_Eta_Picky_M03,  *ResInvP_Eta_Picky_M0;
  TH1F *ResInvP_Eta_GLB_M24,     *ResInvP_Eta_GLB_M21,     *ResInvP_Eta_GLB_M18,      *ResInvP_Eta_GLB_M15,     *ResInvP_Eta_GLB_M12,    *ResInvP_Eta_GLB_M09,    *ResInvP_Eta_GLB_M06,    *ResInvP_Eta_GLB_M03,    *ResInvP_Eta_GLB_M0;
  TH1F *ResInvP_Eta_StdA_M24,    *ResInvP_Eta_StdA_M21,    *ResInvP_Eta_StdA_M18,     *ResInvP_Eta_StdA_M15,    *ResInvP_Eta_StdA_M12,   *ResInvP_Eta_StdA_M09,   *ResInvP_Eta_StdA_M06,   *ResInvP_Eta_StdA_M03,   *ResInvP_Eta_StdA_M0;

  //Definition of Resolution for P tra 0.3 e 2.4 (Eta, width 0.3)
  TH1F *ResInvP_Eta_DYT_P03,     *ResInvP_Eta_DYT_P06,     *ResInvP_Eta_DYT_P09,      *ResInvP_Eta_DYT_P12,     *ResInvP_Eta_DYT_P15,    *ResInvP_Eta_DYT_P18,    *ResInvP_Eta_DYT_P21;
  TH1F *ResInvP_Eta_TuneP_P03,   *ResInvP_Eta_TuneP_P06,   *ResInvP_Eta_TuneP_P09,    *ResInvP_Eta_TuneP_P12,   *ResInvP_Eta_TuneP_P15,  *ResInvP_Eta_TuneP_P18,  *ResInvP_Eta_TuneP_P21;
  TH1F *ResInvP_Eta_Picky_P03,   *ResInvP_Eta_Picky_P06,   *ResInvP_Eta_Picky_P09,    *ResInvP_Eta_Picky_P12,   *ResInvP_Eta_Picky_P15,  *ResInvP_Eta_Picky_P18,  *ResInvP_Eta_Picky_P21;
  TH1F *ResInvP_Eta_GLB_P03,     *ResInvP_Eta_GLB_P06,     *ResInvP_Eta_GLB_P09,      *ResInvP_Eta_GLB_P12,     *ResInvP_Eta_GLB_P15,    *ResInvP_Eta_GLB_P18,    *ResInvP_Eta_GLB_P21;
  TH1F *ResInvP_Eta_StdA_P03,    *ResInvP_Eta_StdA_P06,    *ResInvP_Eta_StdA_P09,     *ResInvP_Eta_StdA_P12,    *ResInvP_Eta_StdA_P15,   *ResInvP_Eta_StdA_P18,   *ResInvP_Eta_StdA_P21;


  //Definition of the Resolution (q/p_reco - q/p_sim)/(q/p_sim)
  TH1F *DYT_Res_Invp,   *TuneP_Res_Invp,   *Picky_Res_Invp,   *GLB_Res_Invp,   *StdA_Res_Invp;
  TH1F *DYT_Res_InvpB,  *TuneP_Res_InvpB,  *Picky_Res_InvpB,  *GLB_Res_InvpB,  *StdA_Res_InvpB;
  TH1F *DYT_Res_InvpE,  *TuneP_Res_InvpE,  *Picky_Res_InvpE,  *GLB_Res_InvpE,  *StdA_Res_InvpE;

  //Definition of the Pull (q/p_reco - q/p_sim)/(q*P_reco_Err/p_sim)
  TH1F *DYT_Pull_Invp,   *TuneP_Pull_Invp,   *Picky_Pull_Invp,   *GLB_Pull_Invp,   *StdA_Pull_Invp;
  TH1F *DYT_Pull_InvpB,  *TuneP_Pull_InvpB,  *Picky_Pull_InvpB,  *GLB_Pull_InvpB,  *StdA_Pull_InvpB;
  TH1F *DYT_Pull_InvpE,  *TuneP_Pull_InvpE,  *Picky_Pull_InvpE,  *GLB_Pull_InvpE,  *StdA_Pull_InvpE;

  //Definition Pull pT
  TH1F *DYT_Pull_pt,  *TuneP_Pull_pt,   *Picky_Pull_pt,   *GLB_Pull_pt,   *StdA_Pull_pt;
  TH1F *DYT_Pull_ptB, *TuneP_Pull_ptB,  *Picky_Pull_ptB,  *GLB_Pull_ptB,  *StdA_Pull_ptB;
  TH1F *DYT_Pull_ptE, *TuneP_Pull_ptE,  *Picky_Pull_ptE,  *GLB_Pull_ptE,  *StdA_Pull_ptE;

};



DYTAnalyzer::DYTAnalyzer(const edm::ParameterSet& iConfig)
{
  psim          = iConfig.getParameter<double>("psim");
  useSelections = iConfig.getParameter<bool>("useSelections");
  ptsim = 5*psim;

  muon_label_   = consumes<reco::MuonCollection>(edm::InputTag("muons"));
  vertex_label_ = consumes< std::vector<reco::Vertex> >(edm::InputTag("offlinePrimaryVertices"));
  gpar_label_   = consumes<reco::GenParticleCollection>(edm::InputTag("genParticles"));

}


DYTAnalyzer::~DYTAnalyzer()
{}


void DYTAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  using namespace edm;
  using namespace reco;

  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByToken( muon_label_, muons );

  edm::Handle< std::vector<reco::Vertex> > verteciesHandle;
  iEvent.getByToken( vertex_label_, verteciesHandle );
  auto vtx = verteciesHandle.product()->at(0);

  Handle<reco::GenParticleCollection> genP;
  iEvent.getByToken(gpar_label_,genP);


  for(size_t i = 0; i != muons->size(); ++i) {

    try {
      //DYTInfo dytInfo = dytInfoC[muons->at(i).globalTrack()];
      //vector<double> estimators = {0.5,0.5,0.5,0.5}; //dytInfo.DYTEstimators();
      //vector<bool> usedSt = {"True","False","True","False"}; //dytInfo.UsedStations();
      //vector<double> thresholds = {0.5,0.5,0.5,0.5}; //dytInfo.Thresholds();

      // 2012 Muon ID - Top twiki: https://twiki.cern.ch/twiki/bin/view/CMS/TWikiTopRefEventSel
      // if (fabs(muons->at(i).eta()) >= 2.4) continue;
      // if (!muons->at(i).isPFMuon()) continue;
      // if (muons->at(i).globalTrack()->normalizedChi2() >= 10) continue;
      // if (muons->at(i).innerTrack()->hitPattern().trackerLayersWithMeasurement() <= 5) continue;
      // if (muons->at(i).innerTrack()->hitPattern().numberOfValidPixelHits() < 1) continue;

      // Tracker HighPt ID
      // if ( useSelections && !muons->at(i).passed(reco::Muon::CutBasedIdTrkHighPt) ) continue;
	if ( useSelections && !isTrackerHighPtMuonNoVtx(muons->at(i)) ) continue;

      //TrackToTrackMap::const_iterator pmrTrack_4 = pmrMap_4.find(muons->at(i).globalTrack());
      reco::TrackRef DYT = muons->at(i).dytTrack();

      //TuneP Muon track type
      int tuneP_trackType = static_cast<int>(muons->at(i).tunePMuonBestTrackType());
      //Particle Momentum
      double DytP     = DYT->p();
      double TunePP   = muons->at(i).tunePMuonBestTrack()->p();
      double PickyP   = muons->at(i).pickyTrack()->p();
      double GLBP     = muons->at(i).globalTrack()->p();
      double StdAP    = muons->at(i).outerTrack()->p();

      //Particle Transverse Momentum
      double DytPt    = DYT->pt();
      double TunePPt  = muons->at(i).tunePMuonBestTrack()->pt();
      double PickyPt  = muons->at(i).pickyTrack()->pt();
      double GLBPt    = muons->at(i).globalTrack()->pt();
      double StdAPt   = muons->at(i).outerTrack()->pt();
      double TrkMPt   = muons->at(i).innerTrack()->pt();

      //Particle Transverse Momentum Error
      double DytErr    = DYT->ptError();
      double TunePErr  = muons->at(i).tunePMuonBestTrack()->ptError();
      double PickyErr  = muons->at(i).pickyTrack()->ptError();
      double GLBErr    = muons->at(i).globalTrack()->ptError();
      double StdAErr   = muons->at(i).outerTrack()->ptError();
      //double TrkMErr   = muons->at(i).innerTrack()->ptError();

      //Particle Inv.Transverse Momentum
      /*double DytQPt    = DYT->qoverp();
      double TunePQPt  = muons->at(i).tunePMuonBestTrack()->qoverp();
      double PickyQPt  = muons->at(i).pickyTrack()->qoverp();
      double GLBQPt    = muons->at(i).globalTrack()->qoverp();
      double StdAQPt   = muons->at(i).outerTrack()->qoverp();*/

      //Particle Error Inv.Trasverse Momentum
      double DytInvErrPt   = DYT->qoverpError();
      double TunePInvErrPt = muons->at(i).tunePMuonBestTrack()->qoverpError();
      double PickyInvErrPt = muons->at(i).pickyTrack()->qoverpError();
      double GLBInvErrPt   = muons->at(i).globalTrack()->qoverpError();
      double StdAInvErrPt  = muons->at(i).outerTrack()->qoverpError();

      //Particle Chi2N (Normalized Chi Square)
      double DytChi2N    = DYT->normalizedChi2();
      double TunePChi2N  = muons->at(i).tunePMuonBestTrack()->normalizedChi2();
      double PickyChi2N  = muons->at(i).pickyTrack()->normalizedChi2();
      double GLBChi2N    = muons->at(i).globalTrack()->normalizedChi2();
      double StdAChi2N   = muons->at(i).outerTrack()->normalizedChi2();
      double TrkMChi2N   = muons->at(i).innerTrack()->normalizedChi2();

      //Particle Charge
      double DytCh    = DYT->charge();
      double TunePCh  = muons->at(i).tunePMuonBestTrack()->charge();
      double PickyCh  = muons->at(i).pickyTrack()->charge();
      double GLBCh    = muons->at(i).globalTrack()->charge();
      double StdACh   = muons->at(i).outerTrack()->charge();

      //Particle Eta
      double muonEta   = muons->at(i).eta();
      double DytEta    = DYT->eta();
      double TunePEta  = muons->at(i).tunePMuonBestTrack()->eta();
      double PickyEta  = muons->at(i).pickyTrack()->eta();
      double GLBEta    = muons->at(i).globalTrack()->eta();
      double StdAEta   = muons->at(i).outerTrack()->eta();
      double TrkMEta   = muons->at(i).innerTrack()->eta();

      //Particle Phi
      double DytPhi    = DYT->phi();
      double TunePPhi  = muons->at(i).tunePMuonBestTrack()->phi();
      double PickyPhi  = muons->at(i).pickyTrack()->phi();
      double GLBPhi    = muons->at(i).globalTrack()->phi();
      double StdAPhi   = muons->at(i).outerTrack()->phi();
      double TrkMPhi   = muons->at(i).innerTrack()->phi();


      for(auto& particle: *genP){
        //double eta_gen = particle.eta();
        //double phi_gen = particle.eta();
        double p_gen   = particle.p();
        double pt_gen  = particle.pt();
        pgen  = p_gen;
        ptgen = pt_gen;
        // double deltaEta2 = std::pow((eta_gen-DytEta),2);
        // double deltaPhi2 = std::pow((phi_gen-DytPhi),2);
        // double deltaR = std::sqrt(deltaEta2+deltaPhi2);
        // cout << "DeltaR btw Gen muons and Reco muon: "<< deltaR << endl;
        // cout << "\t p and pt gen values: "<< p_gen <<" "<<pt_gen << endl;
      }
      //Filling Estimator Vs Momentum
      /*EstVsMomentum1->Fill(estimators[0],DytP);
      EstVsMomentum2->Fill(estimators[1],DytP);
      EstVsMomentum3->Fill(estimators[2],DytP);
      EstVsMomentum4->Fill(estimators[3],DytP);

      //Filling Estimator
      Ests1->Fill(estimators[0]);
      Ests2->Fill(estimators[1]);
      Ests3->Fill(estimators[2]);
      Ests4->Fill(estimators[3]);
      Tester->Fill(estimators[1]);

      */

      //Filling eff plots for HighPtID
      if (muons->at(i).isGlobalMuon() or muons->at(i).isTrackerMuon()){

        // Fill eff denominator
        eff_pt_HighPtID_den->Fill(muons->at(i).pt());
        eff_eta_HighPtID_den->Fill(muons->at(i).eta());
        if( abs(muonEta) > 0.8 ){
          eff_pt_HighPtID_denE->Fill(muons->at(i).pt());
          eff_eta_HighPtID_denE->Fill(muons->at(i).eta());
        }
        if( abs(muonEta) <= 0.8 ){
          eff_pt_HighPtID_denB->Fill(muons->at(i).pt());
          eff_eta_HighPtID_denB->Fill(muons->at(i).eta());
        }

        //Build HighPtID
        if (isHighPtMuon(muons->at(i), vtx)){
          eff_pt_HighPtID_num->Fill(muons->at(i).pt());
          eff_eta_HighPtID_num->Fill(muons->at(i).eta());
          if( abs(muonEta) > 0.8 ){
            eff_pt_HighPtID_numE->Fill(muons->at(i).pt());
            eff_eta_HighPtID_numE->Fill(muons->at(i).eta());
          }
          if( abs(muonEta) <= 0.8 ){
            eff_pt_HighPtID_numB->Fill(muons->at(i).pt());
            eff_eta_HighPtID_numB->Fill(muons->at(i).eta());
          }
        }
      }

      //Filling Muon Track Tyoe used by TuneP
      TuneP_MuonTrackType->Fill(tuneP_trackType);
      if(fabs(muons->at(i).eta()) <= 1.2) TuneP_MuonTrackTypeB->Fill(tuneP_trackType);
      else TuneP_MuonTrackTypeE->Fill(tuneP_trackType);

      //Control Plots Momentum distribution in eta bins
      DYT_sp->Fill(DytP);
      if( abs(muonEta) <= 0.8 ){
        DYT_spE08->Fill(DytP);
        DYT_Res_InvpE08->Fill(pgen/DytP - 1);
        TuneP_spE08->Fill(TunePP);
        TuneP_Res_InvpE08->Fill(pgen/TunePP - 1);
      }
      else if( abs(muonEta) > 0.8 && abs(muonEta) <= 1.2 ){
        DYT_spE12->Fill(DytP);
        DYT_Res_InvpE12->Fill(pgen/DytP - 1);
        TuneP_spE12->Fill(TunePP);
        TuneP_Res_InvpE12->Fill(pgen/TunePP - 1);
      }
      else if( abs(muonEta) > 1.2 && abs(muonEta) <= 2.0 ){
        DYT_spE20->Fill(DytP);
        DYT_Res_InvpE20->Fill(pgen/DytP - 1);
        TuneP_spE20->Fill(TunePP);
        TuneP_Res_InvpE20->Fill(pgen/TunePP - 1);
      }
      else if( abs(muonEta) > 2.0 && abs(muonEta) <= 2.2 ){
        DYT_spE22->Fill(DytP);
        DYT_Res_InvpE22->Fill(pgen/DytP - 1);
        TuneP_spE22->Fill(TunePP);
        TuneP_Res_InvpE22->Fill(pgen/TunePP - 1);
      }
      else if( abs(muonEta) > 2.2 && abs(muonEta) <= 2.4 ){
        DYT_spE24->Fill(DytP);
        DYT_Res_InvpE24->Fill(pgen/DytP - 1);
        TuneP_spE24->Fill(TunePP);
        TuneP_Res_InvpE24->Fill(pgen/TunePP - 1);
      }

      // TuneP plots for DyT choice
      if( tuneP_trackType == 6){
        TuneP_onlyDyT_p->Fill(TunePP);
        TuneP_onlyDyT_Res_Invp->Fill(pgen/TunePP - 1);
        if( abs(muonEta) <= 0.8 ){
          TuneP_onlyDyT_pB->Fill(TunePP);
          TuneP_onlyDyT_Res_InvpB->Fill(pgen/TunePP - 1);
        }
        else {
          TuneP_onlyDyT_pE->Fill(TunePP);
          TuneP_onlyDyT_Res_InvpE->Fill(pgen/TunePP - 1);
        }
      }

      //Filling Number of Hits
      NHits_DYT->Fill(DYT->hitPattern().numberOfValidMuonHits());
      NHits_TuneP->Fill(muons->at(i).tunePMuonBestTrack()->hitPattern().numberOfValidMuonHits());
      NHits_Picky->Fill(muons->at(i).pickyTrack()->hitPattern().numberOfValidMuonHits());
      NHits_GLB->Fill(muons->at(i).globalTrack()->hitPattern().numberOfValidMuonHits());
      NHits_StdA->Fill(muons->at(i).outerTrack()->hitPattern().numberOfValidMuonHits());
      NHits_TrkM->Fill(muons->at(i).innerTrack()->hitPattern().numberOfValidMuonHits());

      //Filling pT()
      DYT_pt->Fill(DytPt);
      TuneP_pt->Fill(TunePPt);
      Picky_pt->Fill(PickyPt);
      GLB_pt->Fill(GLBPt);
      StdA_pt->Fill(StdAPt);
      TrkM_pt->Fill(TrkMPt);

      //Filling P()
      /*DYT_p->StatOverflows(kTRUE);
      TuneP_p->StatOverflows(kTRUE);
      Picky_p->StatOverflows(kTRUE);
      GLB_p->StatOverflows(kTRUE);
      StdA_p->StatOverflows(kTRUE);*/
      DYT_p->Fill(DytP);
      TuneP_p->Fill(TunePP);
      Picky_p->Fill(PickyP);
      GLB_p->Fill(GLBP);
      StdA_p->Fill(StdAP);

      //Filling P OverFlow
      if( DytP >= 2*psim ) DYT_pOv->Fill(DytP);
      if( TunePP >= 2*psim ) TuneP_pOv->Fill(TunePP);
      if( PickyP >= 2*psim ) Picky_pOv->Fill(PickyP);
      if( GLBP >= 2*psim ) GLB_pOv->Fill(GLBP);
      if( StdAP >= 2*psim ) StdA_pOv->Fill(StdAP);

      //Filling Eta()
      DYT_eta->Fill(DytEta);
      TuneP_eta->Fill(TunePEta);
      Picky_eta->Fill(PickyEta);
      GLB_eta->Fill(GLBEta);
      StdA_eta->Fill(StdAEta);
      TrkM_eta->Fill(TrkMEta);

      //Filling Phi()
      DYT_phi->Fill(DytPhi);
      TuneP_phi->Fill(TunePPhi);
      Picky_phi->Fill(PickyPhi);
      GLB_phi->Fill(GLBPhi);
      StdA_phi->Fill(StdAPhi);
      TrkM_phi->Fill(TrkMPhi);

      //Filling Relative Error pT()
      InvDYT_pt->Fill(1-ptgen/DytPt);
      InvTuneP_pt->Fill(1-ptgen/TunePPt);
      InvPicky_pt->Fill(1-ptgen/PickyPt);
      InvGLB_pt->Fill(1-ptgen/GLBPt);
      InvStdA_pt->Fill(1-ptgen/StdAPt);
      InvTrkM_pt->Fill(1-ptgen/TrkMPt);

      //Filling Chi2 Normalized
      Chi2N_DYT->Fill(DytChi2N);
      Chi2N_TuneP->Fill(TunePChi2N);
      Chi2N_Picky->Fill(PickyChi2N);
      Chi2N_GLB->Fill(GLBChi2N);
      Chi2N_StdA->Fill(StdAChi2N);
      Chi2N_TrkM->Fill(TrkMChi2N);


      //Filling Estimator for the fitting function (only five region in Eta)
      /*if(fabs(muons->at(i).eta())>= 0 && fabs(muons->at(i).eta()) < +0.8){
        Ests1_0->Fill(estimators[0]);
        Ests2_0->Fill(estimators[1]);
        Ests3_0->Fill(estimators[2]);
        Ests4_0->Fill(estimators[3]);
      } else if(fabs(muons->at(i).eta())>= +0.8 && fabs(muons->at(i).eta())< +1.2){
        Ests1_08->Fill(estimators[0]);
        Ests2_08->Fill(estimators[1]);
        Ests3_08->Fill(estimators[2]);
        Ests4_08->Fill(estimators[3]);
      } else if(fabs(muons->at(i).eta())>= +1.2 && fabs(muons->at(i).eta())< +1.6){
        Ests1_12->Fill(estimators[0]);
        Ests2_12->Fill(estimators[1]);
        Ests3_12->Fill(estimators[2]);
        Ests4_12->Fill(estimators[3]);
      } else if(fabs(muons->at(i).eta())>= +1.6 && fabs(muons->at(i).eta())< +2.0){
        Ests1_16->Fill(estimators[0]);
        Ests2_16->Fill(estimators[1]);
        Ests3_16->Fill(estimators[2]);
        Ests4_16->Fill(estimators[3]);
      } else if(fabs(muons->at(i).eta())>= +2.0 && fabs(muons->at(i).eta())< +2.4){
        Ests1_20->Fill(estimators[0]);
        Ests2_20->Fill(estimators[1]);
        Ests3_20->Fill(estimators[2]);
        Ests4_20->Fill(estimators[3]);
      }*/

      //Filling Resolution Vs Eta
      if(muons->at(i).eta() >= -2.4 && muons->at(i).eta() < -2.1){

        //Ests_M24->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution for Inverse Pt
        ResInvPt_Eta_DYT_M24->Fill(DytCh/DytPt - DytCh/ptgen);
	ResInvPt_Eta_TuneP_M24->Fill(TunePCh/TunePPt - TunePCh/ptgen);
	ResInvPt_Eta_Picky_M24->Fill(PickyCh/PickyPt - PickyCh/ptgen);
	ResInvPt_Eta_GLB_M24->Fill(GLBCh/GLBPt - GLBCh/ptgen);
	ResInvPt_Eta_StdA_M24->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution for Pt
        ResPt_Eta_DYT_M24->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M24->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M24->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M24->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M24->Fill(StdAPt - ptgen);
        //Resolution for Inverse P
        /*ResInvP_Eta_DYT_M24->Fill(DytCh/DytP - DytCh/ptsim);
        ResInvP_Eta_TuneP_M24->Fill(TunePCh/TunePP - TunePCh/ptsim);
        ResInvP_Eta_Picky_M24->Fill(PickyCh/PickyP - PickyCh/ptsim);
        ResInvP_Eta_GLB_M24->Fill(GLBCh/GLBP - GLBCh/ptsim);
        ResInvP_Eta_StdA_M24->Fill(StdACh/StdAP - StdACh/ptsim);*/

      } else if(muons->at(i).eta() >= -2.1 && muons->at(i).eta() < -1.8){

        //Ests_M21->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution for Inverse Pt
        ResInvPt_Eta_DYT_M21->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_M21->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_M21->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_M21->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_M21->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution for Pt
        ResPt_Eta_DYT_M21->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M21->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M21->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M21->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M21->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= -1.8 && muons->at(i).eta() < -1.5){

        //Ests_M18->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution for Inverse Pt
        ResInvPt_Eta_DYT_M18->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_M18->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_M18->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_M18->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_M18->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution for Pt
        ResPt_Eta_DYT_M18->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M18->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M18->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M18->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M18->Fill(StdAPt - ptgen);

      }  else if(muons->at(i).eta() >= -1.5 && muons->at(i).eta() < -1.2){

        //Ests_M15->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution for Inverse Pt
        ResInvPt_Eta_DYT_M15->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_M15->Fill(TunePCh/TunePPt - DytCh/ptgen);
        ResInvPt_Eta_Picky_M15->Fill(PickyCh/PickyPt - DytCh/ptgen);
        ResInvPt_Eta_GLB_M15->Fill(GLBCh/GLBPt - DytCh/ptgen);
        ResInvPt_Eta_StdA_M15->Fill(StdACh/StdAPt - DytCh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_M15->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M15->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M15->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M15->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M15->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= -1.2 && muons->at(i).eta() < -0.9){

        //Ests_M12->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_M12->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_M12->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_M12->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_M12->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_M12->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_M12->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M12->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M12->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M12->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M12->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= -0.9 && muons->at(i).eta() < -0.6){

        //Ests_M09->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_M09->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_M09->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_M09->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_M09->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_M09->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_M09->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M09->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M09->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M09->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M09->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= -0.6 && muons->at(i).eta() < -0.3){

        //Ests_M06->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_M06->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_M06->Fill(TunePCh/TunePPt - DytCh/ptgen);
        ResInvPt_Eta_Picky_M06->Fill(PickyCh/PickyPt - DytCh/ptgen);
        ResInvPt_Eta_GLB_M06->Fill(GLBCh/GLBPt - DytCh/ptgen);
        ResInvPt_Eta_StdA_M06->Fill(StdACh/StdAPt - DytCh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_M06->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M06->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M06->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M06->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M06->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= -0.3 && muons->at(i).eta() < 0){

        //Ests_M03->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_M03->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_M03->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_M03->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_M03->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_M03->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_M03->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M03->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M03->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M03->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M03->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= 0 && muons->at(i).eta() < +0.3){

        //Ests_M0->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_M0->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_M0->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_M0->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_M0->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_M0->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_M0->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_M0->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_M0->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_M0->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_M0->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= +0.3 && muons->at(i).eta() < +0.6){

        //Ests_P03->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_P03->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_P03->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_P03->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_P03->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_P03->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resoltuion of Pt
        ResPt_Eta_DYT_P03->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_P03->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_P03->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_P03->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_P03->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= +0.6 && muons->at(i).eta() < +0.9){

        //Ests_P06->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_P06->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_P06->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_P06->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_P06->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_P06->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_P06->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_P06->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_P06->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_P06->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_P06->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= +0.9 && muons->at(i).eta() < +1.2){

        //Ests_P09->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_P09->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_P09->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_P09->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_P09->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_P09->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_P09->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_P09->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_P09->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_P09->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_P09->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= +1.2 && muons->at(i).eta() < +1.5){

        //Ests_P12->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_P12->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_P12->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_P12->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_P12->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_P12->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_P12->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_P12->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_P12->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_P12->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_P12->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= +1.5 && muons->at(i).eta() < +1.8){

        //Ests_P15->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_P15->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_P15->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_P15->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_P15->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_P15->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_P15->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_P15->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_P15->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_P15->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_P15->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= +1.8 && muons->at(i).eta() < +2.1){

        //Ests_P18->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_P18->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_P18->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_P18->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_P18->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_P18->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_P18->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_P18->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_P18->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_P18->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_P18->Fill(StdAPt - ptgen);

      } else if(muons->at(i).eta() >= +2.1 && muons->at(i).eta() < +2.4){

        //Ests_P21->Fill((estimators[0]+estimators[1]+estimators[2]+estimators[3])/4);
        //Resolution of Inverse Pt
        ResInvPt_Eta_DYT_P21->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Eta_TuneP_P21->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Eta_Picky_P21->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Eta_GLB_P21->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Eta_StdA_P21->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Eta_DYT_P21->Fill(DytPt - ptgen);
        ResPt_Eta_TuneP_P21->Fill(TunePPt - ptgen);
        ResPt_Eta_Picky_P21->Fill(PickyPt - ptgen);
        ResPt_Eta_GLB_P21->Fill(GLBPt - ptgen);
        ResPt_Eta_StdA_P21->Fill(StdAPt - ptgen);

      }

      //Filling Histo Resolution respect Phi
      if(muons->at(i).phi() >= -3.6 && muons->at(i).phi() < -3.2){

        //Resolution pf Inverse Pt
	ResInvPt_Phi_DYT_M36->Fill(DytCh/DytPt - DytCh/ptgen);
	ResInvPt_Phi_TuneP_M36->Fill(TunePCh/TunePPt - TunePCh/ptgen);
	ResInvPt_Phi_Picky_M36->Fill(PickyCh/PickyPt - PickyCh/ptgen);
	ResInvPt_Phi_GLB_M36->Fill(GLBCh/GLBPt - GLBCh/ptgen);
	ResInvPt_Phi_StdA_M36->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M36->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M36->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M36->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M36->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M36->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= -3.2 && muons->at(i).phi() < -2.8){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_M32->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M32->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M32->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_M32->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M32->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M32->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M32->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M32->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M32->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M32->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= -2.8 && muons->at(i).phi() < -2.4){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_M28->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M28->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M28->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_M28->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M28->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M28->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M28->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M28->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M28->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M28->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= -2.4 && muons->at(i).phi() < -2.0){

       //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_M24->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M24->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M24->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_M24->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M24->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M24->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M24->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M24->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M24->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M24->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= -2.0 && muons->at(i).phi() < -1.6){

        //Resoltuion of Iverse Pt
        ResInvPt_Phi_DYT_M20->Fill(DytCh/DYT->pt() - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M20->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M20->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_M20->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M20->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M20->Fill(DYT->pt() - ptgen);
        ResPt_Phi_TuneP_M20->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M20->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M20->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M20->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= -1.6 && muons->at(i).phi() < -1.2){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_M16->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M16->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M16->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_M16->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M16->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M16->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M16->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M16->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M16->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M16->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= -1.2 && muons->at(i).phi() < -0.8){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_M12->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M12->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M12->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_M12->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M12->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M12->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M12->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M12->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M12->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M12->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= -0.8 && muons->at(i).phi() < -0.4){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_M08->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M08->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M08->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_M08->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M08->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M08->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M08->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M08->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M08->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M08->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= -0.4 && muons->at(i).phi() <  0.0){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_M04->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M04->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M04->Fill(PickyCh/PickyPt- PickyCh/ptgen);
        ResInvPt_Phi_GLB_M04->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M04->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M04->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M04->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M04->Fill(PickyPt- ptgen);
        ResPt_Phi_GLB_M04->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M04->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >=  0.0 && muons->at(i).phi() < +0.4){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_M0->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_M0->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_M0->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_M0->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_M0->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_M0->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_M0->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_M0->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_M0->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_M0->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= +0.4 && muons->at(i).phi() < +0.8){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_P04->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_P04->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_P04->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_P04->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_P04->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_P04->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_P04->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_P04->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_P04->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_P04->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= +0.8 && muons->at(i).phi() < +1.2){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_P08->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_P08->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_P08->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_P08->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_P08->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_P08->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_P08->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_P08->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_P08->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_P08->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= +1.2 && muons->at(i).phi() < +1.6){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_P12->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_P12->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_P12->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_P12->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_P12->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_P12->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_P12->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_P12->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_P12->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_P12->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= +1.6 && muons->at(i).phi() < +2.0){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_P16->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_P16->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_P16->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_P16->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_P16->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_P16->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_P16->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_P16->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_P16->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_P16->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= +2.0 && muons->at(i).phi() < +2.4){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_P20->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_P20->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_P20->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_P20->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_P20->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_P20->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_P20->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_P20->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_P20->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_P20->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= +2.4 && muons->at(i).phi() < +2.8){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_P24->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_P24->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_P24->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_P24->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_P24->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_P24->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_P24->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_P24->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_P24->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_P24->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= +2.8 && muons->at(i).phi() < +3.2){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_P28->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_P28->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_P28->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_P28->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_P28->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_P28->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_P28->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_P28->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_P28->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_P28->Fill(StdAPt - ptgen);

      } else if(muons->at(i).phi() >= +3.2 && muons->at(i).phi() < +3.6){

        //Resolution of Inverse Pt
        ResInvPt_Phi_DYT_P32->Fill(DytCh/DytPt - DytCh/ptgen);
        ResInvPt_Phi_TuneP_P32->Fill(TunePCh/TunePPt - TunePCh/ptgen);
        ResInvPt_Phi_Picky_P32->Fill(PickyCh/PickyPt - PickyCh/ptgen);
        ResInvPt_Phi_GLB_P32->Fill(GLBCh/GLBPt - GLBCh/ptgen);
        ResInvPt_Phi_StdA_P32->Fill(StdACh/StdAPt - StdACh/ptgen);
        //Resolution of Pt
        ResPt_Phi_DYT_P32->Fill(DytPt - ptgen);
        ResPt_Phi_TuneP_P32->Fill(TunePPt - ptgen);
        ResPt_Phi_Picky_P32->Fill(PickyPt - ptgen);
        ResPt_Phi_GLB_P32->Fill(GLBPt - ptgen);
        ResPt_Phi_StdA_P32->Fill(StdAPt - ptgen);

      }

      //Filling Histo Resolution (q/p_reco - q/p_sim)/(q/p_sim)
      DYT_Res_Invp->Fill(pgen/DytP - 1);
      TuneP_Res_Invp->Fill(pgen/TunePP - 1);
      Picky_Res_Invp->Fill(pgen/PickyP - 1);
      GLB_Res_Invp->Fill(pgen/GLBP - 1);
      StdA_Res_Invp->Fill(pgen/StdAP - 1);

      //Filling Histo Pull (q/p_reco - q/p_sim)/(q*p_reco_err/p_reco)
      DYT_Pull_Invp->Fill((DytCh/DytP - DytCh/pgen)/(DytInvErrPt));
      TuneP_Pull_Invp->Fill((TunePCh/TunePP - TunePCh/pgen)/(TunePInvErrPt));
      Picky_Pull_Invp->Fill((PickyCh/PickyP - PickyCh/pgen)/(PickyInvErrPt));
      GLB_Pull_Invp->Fill((GLBCh/GLBP - GLBCh/pgen)/(GLBInvErrPt));
      StdA_Pull_Invp->Fill((StdACh/StdAP - StdACh/pgen)/(StdAInvErrPt));

      //Filling Sigma Q/P
      DYT_SqP->Fill(DytInvErrPt);
      TuneP_SqP->Fill(TunePInvErrPt);
      Picky_SqP->Fill(PickyInvErrPt);
      GLB_SqP->Fill(GLBInvErrPt);
      StdA_SqP->Fill(StdAInvErrPt);

      //Filling Sigma Q/P
      DYT_SqInvPt->Fill((DytCh*DytErr)/DytPt);
      TuneP_SqInvPt->Fill((TunePCh*TunePErr)/TunePPt);
      Picky_SqInvPt->Fill((PickyCh*PickyErr)/PickyPt);
      GLB_SqInvPt->Fill((GLBCh*GLBErr)/GLBPt);
      StdA_SqInvPt->Fill((StdACh*StdAErr)/StdAPt);

      //Filling Sigm(Q/P)/|Q/P|
      DYT_SInvPOverP->Fill(DytP*DytInvErrPt);
      TuneP_SInvPOverP->Fill(TunePP*TunePInvErrPt);
      Picky_SInvPOverP->Fill(PickyP*PickyInvErrPt);
      GLB_SInvPOverP->Fill(GLBP*GLBInvErrPt);
      StdA_SInvPOverP->Fill(StdAP*StdAInvErrPt);

      //Filling Sigma(Pt)/Pt
      DYT_SPtOverPt->Fill(DytErr/DytPt);
      TuneP_SPtOverPt->Fill(TunePErr/TunePPt);
      Picky_SPtOverPt->Fill(PickyErr/PickyPt);
      GLB_SPtOverPt->Fill(GLBErr/GLBPt);
      StdA_SPtOverPt->Fill(StdAErr/StdAPt);

      //Filling Pull respect the pT
      DYT_Pull_pt->Fill((DytPt - ptgen)/DytErr);
      TuneP_Pull_pt->Fill((TunePPt - ptgen)/TunePErr);
      Picky_Pull_pt->Fill((PickyPt - ptgen)/PickyErr);
      GLB_Pull_pt->Fill((GLBPt - ptgen)/GLBErr);
      StdA_Pull_pt->Fill((StdAPt - ptgen)/StdAErr);


      //Barrel Region
      if (fabs(muons->at(i).eta()) <= 1.2) {


        //Estimator Vs Momentum
        /*EstVsMomentum1B->Fill(estimators[0],DytP);
        EstVsMomentum2B->Fill(estimators[1],DytP);
        EstVsMomentum3B->Fill(estimators[2],DytP);
        EstVsMomentum4B->Fill(estimators[3],DytP);

        //Filling Estimator
	Ests1B->Fill(estimators[0]);
	Ests2B->Fill(estimators[1]);
	Ests3B->Fill(estimators[2]);
	Ests4B->Fill(estimators[3]);*/

	//Filling Number of Stations Used
	NStUsB->Fill(4);

	//Filling Number of Hits
      	NHits_DYT_B->Fill(DYT->hitPattern().numberOfValidMuonDTHits());
     	NHits_TuneP_B->Fill(muons->at(i).tunePMuonBestTrack()->hitPattern().numberOfValidMuonDTHits());
      	NHits_Picky_B->Fill(muons->at(i).pickyTrack()->hitPattern().numberOfValidMuonDTHits());
      	NHits_GLB_B->Fill(muons->at(i).globalTrack()->hitPattern().numberOfValidMuonDTHits());
      	NHits_StdA_B->Fill(muons->at(i).outerTrack()->hitPattern().numberOfValidMuonDTHits());
      	NHits_TrkM_B->Fill(muons->at(i).innerTrack()->hitPattern().numberOfValidMuonDTHits());

	//Filling pT()
	DYT_ptB->Fill(DYT->pt());
	TuneP_ptB->Fill(muons->at(i).tunePMuonBestTrack()->pt());
	Picky_ptB->Fill(muons->at(i).pickyTrack()->pt());
	GLB_ptB->Fill(muons->at(i).globalTrack()->pt());
        StdA_ptB->Fill(muons->at(i).outerTrack()->pt());
        TrkM_ptB->Fill(muons->at(i).innerTrack()->pt());

        //Filling P()
        /*DYT_pB->StatOverflows(kTRUE);
        TuneP_pB->StatOverflows(kTRUE);
        Picky_pB->StatOverflows(kTRUE);
        GLB_pB->StatOverflows(kTRUE);
        StdA_pB->StatOverflows(kTRUE);*/
        DYT_pB->Fill(DytP);
        TuneP_pB->Fill(TunePP);
        Picky_pB->Fill(PickyP);
        GLB_pB->Fill(GLBP);
        StdA_pB->Fill(StdAP);

        //Filling P OverFlow Histo
        if( DytP >= 2*psim ) DYT_pBOv->Fill(DytP);
        if( TunePP >= 2*psim ) TuneP_pBOv->Fill(TunePP);
        if( PickyP >= 2*psim ) Picky_pBOv->Fill(PickyP);
        if( GLBP >= 2*psim ) GLB_pBOv->Fill(GLBP);
        if( StdAP >= 2*psim ) StdA_pBOv->Fill(StdAP);

	//Filling Relative Error pT()
	InvDYT_ptB->Fill(1-ptgen/DYT->pt());
	InvTuneP_ptB->Fill(1-ptgen/muons->at(i).tunePMuonBestTrack()->pt());
	InvPicky_ptB->Fill(1-ptgen/muons->at(i).pickyTrack()->pt());
	InvGLB_ptB->Fill(1-ptgen/muons->at(i).globalTrack()->pt());
        InvStdA_ptB->Fill(1-ptgen/muons->at(i).outerTrack()->pt());
        InvTrkM_ptB->Fill(1-ptgen/muons->at(i).innerTrack()->pt());

	//Filling Chi2 Normalized
	Chi2N_DYT_B->Fill(DYT->normalizedChi2());
	Chi2N_TuneP_B->Fill(muons->at(i).tunePMuonBestTrack()->normalizedChi2());
	Chi2N_Picky_B->Fill(muons->at(i).pickyTrack()->normalizedChi2());
	Chi2N_GLB_B->Fill(muons->at(i).globalTrack()->normalizedChi2());
	Chi2N_StdA_B->Fill(muons->at(i).outerTrack()->normalizedChi2());
	Chi2N_TrkM_B->Fill(muons->at(i).innerTrack()->normalizedChi2());

        //Filling Histo Resolution (q/p_reco - q/p_sim)/(q/p_sim)
       	DYT_Res_InvpB->Fill(pgen/DytP - 1);
       	TuneP_Res_InvpB->Fill(pgen/TunePP - 1);
       	Picky_Res_InvpB->Fill(pgen/PickyP - 1);
      	GLB_Res_InvpB->Fill(pgen/GLBP - 1);
       	StdA_Res_InvpB->Fill(pgen/StdAP - 1);

       	//Filling Histo Pull Inv P (q/p_reco - q/p_sim)/(q*p_reco_err/p_sim)
        DYT_Pull_InvpB->Fill((DytCh/DytP - DytCh/pgen)/(DytInvErrPt));
        TuneP_Pull_InvpB->Fill((TunePCh/TunePP - TunePCh/pgen)/(TunePInvErrPt));
        Picky_Pull_InvpB->Fill((PickyCh/PickyP - PickyCh/pgen)/(PickyInvErrPt));
        GLB_Pull_InvpB->Fill((GLBCh/GLBP - GLBCh/pgen)/(GLBInvErrPt));
        StdA_Pull_InvpB->Fill((StdACh/StdAP - StdACh/pgen)/(StdAInvErrPt));

        //Filling Pull respect the pT
        DYT_Pull_ptB->Fill((DYT->pt() - ptgen)/DYT->ptError());
        TuneP_Pull_ptB->Fill((muons->at(i).pickyTrack()->pt() - ptgen)/muons->at(i).pickyTrack()->ptError());
        Picky_Pull_ptB->Fill((muons->at(i).globalTrack()->pt() - ptgen)/muons->at(i).globalTrack()->ptError());
        GLB_Pull_ptB->Fill((muons->at(i).outerTrack()->pt() - ptgen)/muons->at(i).outerTrack()->ptError());
        StdA_Pull_ptB->Fill((muons->at(i).innerTrack()->pt() - ptgen)/muons->at(i).innerTrack()->ptError());

        //Filling Sigma Q/P
        DYT_SqInvPtB->Fill((DytCh*DytErr)/DytPt);
        TuneP_SqInvPtB->Fill((TunePCh*TunePErr)/TunePPt);
        Picky_SqInvPtB->Fill((PickyCh*PickyErr)/PickyPt);
        GLB_SqInvPtB->Fill((GLBCh*GLBErr)/GLBPt);
        StdA_SqInvPtB->Fill((StdACh*StdAErr)/StdAPt);

        //Filling Sigma Q/Pt
	DYT_SqPB->Fill(DytInvErrPt);
	TuneP_SqPB->Fill(TunePInvErrPt);
	Picky_SqPB->Fill(PickyInvErrPt);
	GLB_SqPB->Fill(GLBInvErrPt);
	StdA_SqPB->Fill(StdAInvErrPt);

	//Filling Sigm(Q/Pt)/|Q/Pt|
	DYT_SInvPOverPB->Fill(DytP*DytInvErrPt);
	TuneP_SInvPOverPB->Fill(TunePP*TunePInvErrPt);
	Picky_SInvPOverPB->Fill(PickyP*PickyInvErrPt);
	GLB_SInvPOverPB->Fill(GLBP*GLBInvErrPt);
	StdA_SInvPOverPB->Fill(StdAP*StdAInvErrPt);

	//Filling Sigma(Pt)/Pt
	DYT_SPtOverPtB->Fill(DytErr/DytPt);
	TuneP_SPtOverPtB->Fill(TunePErr/TunePPt);
	Picky_SPtOverPtB->Fill(PickyErr/PickyPt);
	GLB_SPtOverPtB->Fill(GLBErr/GLBPt);
	StdA_SPtOverPtB->Fill(StdAErr/StdAPt);

      }

      if(fabs(muons->at(i).eta()) > 1.2) {


        //Estimator Vs Momentum
        /*EstVsMomentum1E->Fill(estimators[0],DytP);
        EstVsMomentum2E->Fill(estimators[1],DytP);
        EstVsMomentum3E->Fill(estimators[2],DytP);
        EstVsMomentum4E->Fill(estimators[3],DytP);

        //Filling Estimator
	Ests1E->Fill(estimators[0]);
        Ests2E->Fill(estimators[1]);
        Ests3E->Fill(estimators[2]);
        Ests4E->Fill(estimators[3]);*/

	//Filling Number of Stations Used
	NStUsE->Fill(4);

	//Filling Number of Hits
      	NHits_DYT_E->Fill(DYT->hitPattern().numberOfValidMuonHits());
      	NHits_TuneP_E->Fill(muons->at(i).tunePMuonBestTrack()->hitPattern().numberOfValidMuonCSCHits());
      	NHits_Picky_E->Fill(muons->at(i).pickyTrack()->hitPattern().numberOfValidMuonCSCHits());
      	NHits_GLB_E->Fill(muons->at(i).globalTrack()->hitPattern().numberOfValidMuonCSCHits());
      	NHits_StdA_E->Fill(muons->at(i).outerTrack()->hitPattern().numberOfValidMuonCSCHits());
      	NHits_TrkM_E->Fill(muons->at(i).innerTrack()->hitPattern().numberOfValidMuonCSCHits());

	//Filling pT()
   	DYT_ptE->Fill(DYT->pt());
	TuneP_ptE->Fill(muons->at(i).tunePMuonBestTrack()->pt());
	Picky_ptE->Fill(muons->at(i).pickyTrack()->pt());
	GLB_ptE->Fill(muons->at(i).globalTrack()->pt());
        StdA_ptE->Fill(muons->at(i).outerTrack()->pt());
        TrkM_ptE->Fill(muons->at(i).innerTrack()->pt());

        //Filling P()
        /*DYT_pE->StatOverflows(kTRUE);
        TuneP_pE->StatOverflows(kTRUE);
        Picky_pE->StatOverflows(kTRUE);
        GLB_pE->StatOverflows(kTRUE);
        StdA_pE->StatOverflows(kTRUE);*/
        DYT_pE->Fill(DytP);
        TuneP_pE->Fill(TunePP);
        Picky_pE->Fill(PickyP);
        GLB_pE->Fill(GLBP);
        StdA_pE->Fill(StdAP);

        //Filling P OverFlow Histo
        if( DytP >= 2*psim ) DYT_pEOv->Fill(DytP);
        if( TunePP >= 2*psim ) TuneP_pEOv->Fill(TunePP);
        if( PickyP >= 2*psim ) Picky_pEOv->Fill(PickyP);
        if( GLBP >= 2*psim ) GLB_pEOv->Fill(GLBP);
        if( StdAP >= 2*psim ) StdA_pEOv->Fill(StdAP);

	//Filling Relative Error pT()
	InvDYT_ptE->Fill(1-ptgen/DYT->pt());
	InvTuneP_ptE->Fill(1-ptgen/muons->at(i).tunePMuonBestTrack()->pt());
	InvPicky_ptE->Fill(1-ptgen/muons->at(i).pickyTrack()->pt());
	InvGLB_ptE->Fill(1-ptgen/muons->at(i).globalTrack()->pt());
        InvStdA_ptE->Fill(1-ptgen/muons->at(i).outerTrack()->pt());
        InvTrkM_ptE->Fill(1-ptgen/muons->at(i).innerTrack()->pt());

	//Filling Chi2 Normalized
	Chi2N_DYT_E->Fill(DYT->normalizedChi2());
	Chi2N_TuneP_E->Fill(muons->at(i).tunePMuonBestTrack()->normalizedChi2());
	Chi2N_Picky_E->Fill(muons->at(i).pickyTrack()->normalizedChi2());
	Chi2N_GLB_E->Fill(muons->at(i).globalTrack()->normalizedChi2());
	Chi2N_StdA_E->Fill(muons->at(i).outerTrack()->normalizedChi2());
	Chi2N_TrkM_E->Fill(muons->at(i).innerTrack()->normalizedChi2());

	//Filling Histo Resoltion (q/p_reco - q/p_sim)/(q/p_sim)
        DYT_Res_InvpE->Fill(pgen/DytP - 1);
        TuneP_Res_InvpE->Fill(pgen/TunePP - 1);
        Picky_Res_InvpE->Fill(pgen/PickyP - 1);
        GLB_Res_InvpE->Fill(pgen/GLBP - 1);
        StdA_Res_InvpE->Fill(pgen/StdAP - 1);

        //Fillig Pull Histo Inv Pt (q/pT_reco - q/pT_sim)/(q*pT_reco_err/pt_reco)
        DYT_Pull_InvpE->Fill((DytCh/DytP - DytCh/pgen)/(DytInvErrPt));
        TuneP_Pull_InvpE->Fill((TunePCh/TunePP - TunePCh/pgen)/(TunePInvErrPt));
        Picky_Pull_InvpE->Fill((PickyCh/PickyP - PickyCh/pgen)/(PickyInvErrPt));
        GLB_Pull_InvpE->Fill((GLBCh/GLBP - GLBCh/pgen)/(GLBInvErrPt));
        StdA_Pull_InvpE->Fill((StdACh/StdAP - StdACh/pgen)/(StdAInvErrPt));

        //Filling Pull respect the pT
        DYT_Pull_ptE->Fill((DYT->pt() - ptgen)/DYT->ptError());
        TuneP_Pull_ptE->Fill((muons->at(i).pickyTrack()->pt() - ptgen)/muons->at(i).pickyTrack()->ptError());
        Picky_Pull_ptE->Fill((muons->at(i).globalTrack()->pt() - ptgen)/muons->at(i).globalTrack()->ptError());
        GLB_Pull_ptE->Fill((muons->at(i).outerTrack()->pt() - ptgen)/muons->at(i).outerTrack()->ptError());
        StdA_Pull_ptE->Fill((muons->at(i).innerTrack()->pt() - ptgen)/muons->at(i).innerTrack()->ptError());

        //Filling Sigma Q/P
        DYT_SqInvPtE->Fill((DytCh*DytErr)/DytPt);
        TuneP_SqInvPtE->Fill((TunePCh*TunePErr)/TunePPt);
        Picky_SqInvPtE->Fill((PickyCh*PickyErr)/PickyPt);
        GLB_SqInvPtE->Fill((GLBCh*GLBErr)/GLBPt);
        StdA_SqInvPtE->Fill((StdACh*StdAErr)/StdAPt);

        //Filling Sigma Q/Pt
        DYT_SqPE->Fill(DytInvErrPt);
        TuneP_SqPE->Fill(TunePInvErrPt);
        Picky_SqPE->Fill(PickyInvErrPt);
        GLB_SqPE->Fill(GLBInvErrPt);
        StdA_SqPE->Fill(StdAInvErrPt);

        //Filling Sigm(Q/P)/|Q/P|
        DYT_SInvPOverPE->Fill(DytP*DytInvErrPt);
        TuneP_SInvPOverPE->Fill(TunePP*TunePInvErrPt);
        Picky_SInvPOverPE->Fill(PickyP*PickyInvErrPt);
        GLB_SInvPOverPE->Fill(GLBP*GLBInvErrPt);
        StdA_SInvPOverPE->Fill(StdAP*StdAInvErrPt);

        //Filling Sigma(Pt)/Pt
        DYT_SPtOverPtE->Fill(DytErr/DytPt);
        TuneP_SPtOverPtE->Fill(TunePErr/TunePPt);
        Picky_SPtOverPtE->Fill(PickyErr/PickyPt);
        GLB_SPtOverPtE->Fill(GLBErr/GLBPt);
        StdA_SPtOverPtE->Fill(StdAErr/StdAPt);

      }
    } catch (...) {continue;}
  }



}


void DYTAnalyzer::beginJob()
{

  edm::Service<TFileService> fs;
  //Estimator
  Ests1        = fs->make<TH1F>("Ests1"    , "Ests1 - DT" , 1000,  0., 1000);
  Ests2        = fs->make<TH1F>("Ests2"    , "Ests2 - DT" , 1000,  0., 1000);
  Ests3        = fs->make<TH1F>("Ests3"    , "Ests3 - DT" , 1000,  0., 1000);
  Ests4        = fs->make<TH1F>("Ests4"    , "Ests4 - DT" , 1000,  0., 1000);

  Ests1B       = fs->make<TH1F>("Ests1B"   , "Ests1 - DT" , 1000,  0., 1000);
  Ests2B       = fs->make<TH1F>("Ests2B"   , "Ests2 - DT" , 1000,  0., 1000);
  Ests3B       = fs->make<TH1F>("Ests3B"   , "Ests3 - DT" , 1000,  0., 1000);
  Ests4B       = fs->make<TH1F>("Ests4B"   , "Ests4 - DT" , 1000,  0., 1000);

  Ests1E       = fs->make<TH1F>("Ests1E"   , "Ests1 - CSC", 1000,  0., 1000);
  Ests2E       = fs->make<TH1F>("Ests2E"   , "Ests2 - CSC", 1000,  0., 1000);
  Ests3E       = fs->make<TH1F>("Ests3E"   , "Ests3 - CSC", 1000,  0., 1000);
  Ests4E       = fs->make<TH1F>("Ests4E"   , "Ests4 - CSC", 1000,  0., 1000);

  Tester       = fs->make<TH1F>("Tester"   , "Tester"     , 2000,  -1000, 1000);

  //Estimator for the fitting function
  Ests1_0       = fs->make<TH1F>("Ests1_0"   , "Ests1  -   0 < |Eta| < 0.8", 1000,  0., 1000);
  Ests2_0       = fs->make<TH1F>("Ests2_0"   , "Ests2  -   0 < |Eta| < 0.8", 1000,  0., 1000);
  Ests3_0       = fs->make<TH1F>("Ests3_0"   , "Ests3  -   0 < |Eta| < 0.8", 1000,  0., 1000);
  Ests4_0       = fs->make<TH1F>("Ests4_0"   , "Ests4  -   0 < |Eta| < 0.8", 1000,  0., 1000);

  Ests1_08      = fs->make<TH1F>("Ests1_08"  , "Ests1  - 0.8 < |Eta| < 1.2", 1000,  0., 1000);
  Ests2_08      = fs->make<TH1F>("Ests2_08"  , "Ests2  - 0.8 < |Eta| < 1.2", 1000,  0., 1000);
  Ests3_08      = fs->make<TH1F>("Ests3_08"  , "Ests3  - 0.8 < |Eta| < 1.2", 1000,  0., 1000);
  Ests4_08      = fs->make<TH1F>("Ests4_08"  , "Ests4  - 0.8 < |Eta| < 1.2", 1000,  0., 1000);

  Ests1_12      = fs->make<TH1F>("Ests1_12"  , "Ests1  - 1.2 < |Eta| < 1.6", 1000,  0., 1000);
  Ests2_12      = fs->make<TH1F>("Ests2_12"  , "Ests2  - 1.2 < |Eta| < 1.6", 1000,  0., 1000);
  Ests3_12      = fs->make<TH1F>("Ests3_12"  , "Ests3  - 1.2 < |Eta| < 1.6", 1000,  0., 1000);
  Ests4_12      = fs->make<TH1F>("Ests4_12"  , "Ests4  - 1.2 < |Eta| < 1.6", 1000,  0., 1000);

  Ests1_16      = fs->make<TH1F>("Ests1_16"  , "Ests1  - 1.6 < |Eta| < 2.0", 1000,  0., 1000);
  Ests2_16      = fs->make<TH1F>("Ests2_16"  , "Ests2  - 1.6 < |Eta| < 2.0", 1000,  0., 1000);
  Ests3_16      = fs->make<TH1F>("Ests3_16"  , "Ests3  - 1.6 < |Eta| < 2.0", 1000,  0., 1000);
  Ests4_16      = fs->make<TH1F>("Ests4_16"  , "Ests4  - 1.6 < |Eta| < 2.0", 1000,  0., 1000);

  Ests1_20      = fs->make<TH1F>("Ests1_20"  , "Ests1  - 2.0 < |Eta| < 2.4", 1000,  0., 1000);
  Ests2_20      = fs->make<TH1F>("Ests2_20"  , "Ests2  - 2.0 < |Eta| < 2.4", 1000,  0., 1000);
  Ests3_20      = fs->make<TH1F>("Ests3_20"  , "Ests3  - 2.0 < |Eta| < 2.4", 1000,  0., 1000);
  Ests4_20      = fs->make<TH1F>("Ests4_20"  , "Ests4  - 2.0 < |Eta| < 2.4", 1000,  0., 1000);


  //Estimator binned
  Ests_M24     = fs->make<TH1F>("Ests_M24" , "Ests - -2.4 < Eta < -2.1" , 1000,  0., 1000);
  Ests_M21     = fs->make<TH1F>("Ests_M21" , "Ests - -2.1 < Eta < -1.8" , 1000,  0., 1000);
  Ests_M18     = fs->make<TH1F>("Ests_M18" , "Ests - -1.8 < Eta < -1.5" , 1000,  0., 1000);
  Ests_M15     = fs->make<TH1F>("Ests_M15" , "Ests - -1.5 < Eta < -1.2" , 1000,  0., 1000);
  Ests_M12     = fs->make<TH1F>("Ests_M12" , "Ests - -1.2 < Eta < -0.9" , 1000,  0., 1000);
  Ests_M09     = fs->make<TH1F>("Ests_M09" , "Ests - -0.9 < Eta < -0.6" , 1000,  0., 1000);
  Ests_M06     = fs->make<TH1F>("Ests_M06" , "Ests - -0.6 < Eta < -0.3" , 1000,  0., 1000);
  Ests_M03     = fs->make<TH1F>("Ests_M03" , "Ests - -0.3 < Eta <  0"   , 1000,  0., 1000);
  Ests_M0      = fs->make<TH1F>("Ests_M0"  , "Ests -    0 < Eta < +0.3" , 1000,  0., 1000);
  Ests_P03     = fs->make<TH1F>("Ests_P03" , "Ests - +0.3 < Eta < +0.6" , 1000,  0., 1000);
  Ests_P06     = fs->make<TH1F>("Ests_P06" , "Ests - +0.6 < Eta < +0.9" , 1000,  0., 1000);
  Ests_P09     = fs->make<TH1F>("Ests_P09" , "Ests - +0.9 < Eta < +1.2" , 1000,  0., 1000);
  Ests_P12     = fs->make<TH1F>("Ests_P12" , "Ests - +1.2 < Eta < +1.5" , 1000,  0., 1000);
  Ests_P15     = fs->make<TH1F>("Ests_P15" , "Ests - +1.5 < Eta < +1.8" , 1000,  0., 1000);
  Ests_P18     = fs->make<TH1F>("Ests_P18" , "Ests - +1.8 < Eta < +2.1" , 1000,  0., 1000);
  Ests_P21     = fs->make<TH1F>("Ests_P21" , "Ests - +2.1 < Eta < +2.4" , 1000,  0., 1000);

  //TuneP muon track type
  TuneP_MuonTrackType = fs->make<TH1F>("TuneP_MuonTrackType","TuneP - Muon Track Type",8, 0,8);
  TuneP_MuonTrackType->GetXaxis()->SetBinLabel(1,"None");
  TuneP_MuonTrackType->GetXaxis()->SetBinLabel(2,"InnerTrack");
  TuneP_MuonTrackType->GetXaxis()->SetBinLabel(3,"OuterTrack");
  TuneP_MuonTrackType->GetXaxis()->SetBinLabel(4,"CombinedTrack");
  TuneP_MuonTrackType->GetXaxis()->SetBinLabel(5,"TPFMS");
  TuneP_MuonTrackType->GetXaxis()->SetBinLabel(6,"Picky");
  TuneP_MuonTrackType->GetXaxis()->SetBinLabel(7,"DYT");
  TuneP_MuonTrackTypeB = fs->make<TH1F>("TuneP_MuonTrackTypeB","TuneP - Muon Track Type - |#eta| < 0.8",8, 0,8);
  TuneP_MuonTrackTypeB->GetXaxis()->SetBinLabel(1,"None");
  TuneP_MuonTrackTypeB->GetXaxis()->SetBinLabel(2,"InnerTrack");
  TuneP_MuonTrackTypeB->GetXaxis()->SetBinLabel(3,"OuterTrack");
  TuneP_MuonTrackTypeB->GetXaxis()->SetBinLabel(4,"CombinedTrack");
  TuneP_MuonTrackTypeB->GetXaxis()->SetBinLabel(5,"TPFMS");
  TuneP_MuonTrackTypeB->GetXaxis()->SetBinLabel(6,"Picky");
  TuneP_MuonTrackTypeB->GetXaxis()->SetBinLabel(7,"DYT");
  TuneP_MuonTrackTypeE = fs->make<TH1F>("TuneP_MuonTrackTypeE","TuneP - Muon Track Type - |#eta| > 0.8",8, 0,8);
  TuneP_MuonTrackTypeE->GetXaxis()->SetBinLabel(1,"None");
  TuneP_MuonTrackTypeE->GetXaxis()->SetBinLabel(2,"InnerTrack");
  TuneP_MuonTrackTypeE->GetXaxis()->SetBinLabel(3,"OuterTrack");
  TuneP_MuonTrackTypeE->GetXaxis()->SetBinLabel(4,"CombinedTrack");
  TuneP_MuonTrackTypeE->GetXaxis()->SetBinLabel(5,"TPFMS");
  TuneP_MuonTrackTypeE->GetXaxis()->SetBinLabel(6,"Picky");
  TuneP_MuonTrackTypeE->GetXaxis()->SetBinLabel(7,"DYT");

  // HighPtID eff histograms
  eff_pt_HighPtID_den  = fs->make<TH1F>("eff_pt_HighPtID_den"   , "HighPtID - pT"     , 2*ptsim,  0., 2*ptsim);
  eff_pt_HighPtID_denB = fs->make<TH1F>("eff_pt_HighPtID_denB"   , "HighPtID - pT"     , 2*ptsim,  0., 2*ptsim);
  eff_pt_HighPtID_denE = fs->make<TH1F>("eff_pt_HighPtID_denE"   , "HighPtID - pT"     , 2*ptsim,  0., 2*ptsim);
  eff_pt_HighPtID_num  = fs->make<TH1F>("eff_pt_HighPtID_num"   , "HighPtID - pT"     , 2*ptsim,  0., 2*ptsim);
  eff_pt_HighPtID_numB = fs->make<TH1F>("eff_pt_HighPtID_numB"   , "HighPtID - pT"     , 2*ptsim,  0., 2*ptsim);
  eff_pt_HighPtID_numE = fs->make<TH1F>("eff_pt_HighPtID_numE"   , "HighPtID - pT"     , 2*ptsim,  0., 2*ptsim);

  eff_eta_HighPtID_den = fs->make<TH1F>("eff_eta_HighPtID_den"     , "HighPtID - eta"     ,     520,            -2.6,            2.6);
  eff_eta_HighPtID_denB = fs->make<TH1F>("eff_eta_HighPtID_denB"     , "HighPtID - eta"     ,     520,            -2.6,            2.6);
  eff_eta_HighPtID_denE = fs->make<TH1F>("eff_eta_HighPtID_denE"     , "HighPtID - eta"     ,     520,            -2.6,            2.6);
  eff_eta_HighPtID_num  = fs->make<TH1F>("eff_eta_HighPtID_num"     , "HighPtID - eta"     ,     520,            -2.6,            2.6);
  eff_eta_HighPtID_numB = fs->make<TH1F>("eff_eta_HighPtID_numB"     , "HighPtID - eta"     ,     520,            -2.6,            2.6);
  eff_eta_HighPtID_numE = fs->make<TH1F>("eff_eta_HighPtID_numE"     , "HighPtID - eta"     ,     520,            -2.6,            2.6);


  //Number of Stations Used
  NStUs        = fs->make<TH1F>("NStUs"    , "NStUs"      ,    5,-0.5, 4.5);
  NStUsB       = fs->make<TH1F>("NStUsB"   , "NStUs"      ,    5,-0.5, 4.5);
  NStUsE       = fs->make<TH1F>("NStUsE"   , "NStUs"      ,    5,-0.5, 4.5);

  //Number of Hits
  NHits_DYT      = fs->make<TH1F>("DYT_NHits"       , "DYT - NHits"          , 70, 0, 70);
  NHits_DYT_B    = fs->make<TH1F>("DYT_NHitsB"      , "DYT - NHits Barrel"   , 70, 0, 70);
  NHits_DYT_E    = fs->make<TH1F>("DYT_NHitsE"      , "DYT - NHits EndCap"   , 70, 0, 70);

  NHits_TuneP    = fs->make<TH1F>("TuneP_NHits"     , "TuneP - NHits"          , 70, 0, 70);
  NHits_TuneP_B  = fs->make<TH1F>("TuneP_NHitsB"    , "TuneP - NHits Barrel"   , 70, 0, 70);
  NHits_TuneP_E  = fs->make<TH1F>("TuneP_NHitsE"    , "TuneP - NHits EndCap"   , 70, 0, 70);

  NHits_Picky    = fs->make<TH1F>("Picky_NHits"     , "Picky - NHits"          , 70, 0, 70);
  NHits_Picky_B  = fs->make<TH1F>("Picky_NHitsB"    , "Picky - NHits Barrel"   , 70, 0, 70);
  NHits_Picky_E  = fs->make<TH1F>("Picky_NHitsE"    , "Picky - NHits EndCap"   , 70, 0, 70);

  NHits_GLB      = fs->make<TH1F>("GLB_NHits"       , "GLB - NHits"          , 70, 0, 70);
  NHits_GLB_B    = fs->make<TH1F>("GLB_NHitsB"      , "GLB - NHits Barrel"   , 70, 0, 70);
  NHits_GLB_E    = fs->make<TH1F>("GLB_NHitsE"      , "GLB - NHits EndCap"   , 70, 0, 70);

  NHits_StdA     = fs->make<TH1F>("StdA_NHits"      , "StdA - NHits"          , 70, 0, 70);
  NHits_StdA_B   = fs->make<TH1F>("StdA_NHitsB"     , "StdA - NHits Barrel"   , 70, 0, 70);
  NHits_StdA_E   = fs->make<TH1F>("StdA_NHitsE"     , "StdA - NHits EndCap"   , 70, 0, 70);

  NHits_TrkM     = fs->make<TH1F>("TrkM_NHits"      , "TrkM - NHits"          , 70, 0, 70);
  NHits_TrkM_B   = fs->make<TH1F>("TrkM_NHitsB"     , "TrkM - NHits Barrel"   , 70, 0, 70);
  NHits_TrkM_E   = fs->make<TH1F>("TrkM_NHitsE"     , "TrkM - NHits EndCap"   , 70, 0, 70);

  //Transverse Momentum
  DYT_pt       = fs->make<TH1F>("DYT_pt"   , "DYT - pT"     , 2*ptsim,  0., 2*ptsim);
  DYT_ptB      = fs->make<TH1F>("DYT_ptB"  , "DYT - pT"     , 2*ptsim,  0., 2*ptsim);
  DYT_ptE      = fs->make<TH1F>("DYT_ptE"  , "DYT - pT"     , 2*ptsim,  0., 2*ptsim);

  TuneP_pt     = fs->make<TH1F>("TuneP_pt" , "TuneP - pT"   , 2*ptsim,  0., 2*ptsim);
  TuneP_ptB    = fs->make<TH1F>("TuneP_ptB", "TuneP - pT"   , 2*ptsim,  0., 2*ptsim);
  TuneP_ptE    = fs->make<TH1F>("TuneP_ptE", "TuneP - pT"   , 2*ptsim,  0., 2*ptsim);

  Picky_pt     = fs->make<TH1F>("Picky_pt" , "Picky - pT"   , 2*ptsim,  0., 2*ptsim);
  Picky_ptB    = fs->make<TH1F>("Picky_ptB", "Picky - pT"   , 2*ptsim,  0., 2*ptsim);
  Picky_ptE    = fs->make<TH1F>("Picky_ptE", "Picky - pT"   , 2*ptsim,  0., 2*ptsim);

  GLB_pt       = fs->make<TH1F>("GLB_pt"   , "GLB - pT"     , 2*ptsim,  0., 2*ptsim);
  GLB_ptB      = fs->make<TH1F>("GLB_ptB"  , "GLB - pT"     , 2*ptsim,  0., 2*ptsim);
  GLB_ptE      = fs->make<TH1F>("GLB_ptE"  , "GLB - pT"     , 2*ptsim,  0., 2*ptsim);

  StdA_pt      = fs->make<TH1F>("StdA_pt"   , "StdA - pT"   , 2*ptsim,  0., 2*ptsim);
  StdA_ptB     = fs->make<TH1F>("StdA_ptB"  , "StdA - pT"   , 2*ptsim,  0., 2*ptsim);
  StdA_ptE     = fs->make<TH1F>("StdA_ptE"  , "StdA - pT"   , 2*ptsim,  0., 2*ptsim);

  TrkM_pt      = fs->make<TH1F>("TrkM_pt"   , "TrkM - pT"   , 4*ptsim,  0., 4*ptsim);
  TrkM_ptB     = fs->make<TH1F>("TrkM_ptB"  , "TrkM - pT"   , 4*ptsim,  0., 4*ptsim);
  TrkM_ptE     = fs->make<TH1F>("TrkM_ptE"  , "TrkM - pT"   , 4*ptsim,  0., 4*ptsim);

  //Momentum
  DYT_p       = fs->make<TH1F>("DYT_p"   , "DYT - P"     , 2*psim,  0., 2*psim);
  DYT_pB      = fs->make<TH1F>("DYT_pB"  , "DYT - P"     , 2*psim,  0., 2*psim);
  DYT_pE      = fs->make<TH1F>("DYT_pE"  , "DYT - P"     , 2*psim,  0., 2*psim);

  TuneP_p     = fs->make<TH1F>("TuneP_p" , "TuneP - P"   , 2*psim,  0., 2*psim);
  TuneP_pB    = fs->make<TH1F>("TuneP_pB", "TuneP - P"   , 2*psim,  0., 2*psim);
  TuneP_pE    = fs->make<TH1F>("TuneP_pE", "TuneP - P"   , 2*psim,  0., 2*psim);
  TuneP_onlyDyT_p     = fs->make<TH1F>("TuneP_onlyDyT_p" , "TuneP (DyT choosen) - p"   , 2*ptsim,  0., 2*ptsim);
  TuneP_onlyDyT_pB    = fs->make<TH1F>("TuneP_onlyDyT_pB", "TuneP (DyT choosen) - p"   , 2*ptsim,  0., 2*ptsim);
  TuneP_onlyDyT_pE    = fs->make<TH1F>("TuneP_onlyDyT_pE", "TuneP (DyT choosen) - p"   , 2*ptsim,  0., 2*ptsim);
  TuneP_onlyDyT_Res_Invp  = fs->make<TH1F>("TuneP_onlyDyT_Res_Invp"    , "TuneP (DyT choosen) - Res_P"   , 1200,  -0.6,  0.6);
  TuneP_onlyDyT_Res_InvpB = fs->make<TH1F>("TuneP_onlyDyT_Res_InvpB"   , "TuneP (DyT choosen) - Res_P"   , 1200,  -0.6,  0.6);
  TuneP_onlyDyT_Res_InvpE = fs->make<TH1F>("TuneP_onlyDyT_Res_InvpE"   , "TuneP (DyT choosen) - Res_P"   , 1200,  -0.6,  0.6);

  Picky_p     = fs->make<TH1F>("Picky_p" , "Picky - P"   , 2*psim,  0., 2*psim);
  Picky_pB    = fs->make<TH1F>("Picky_pB", "Picky - P"   , 2*psim,  0., 2*psim);
  Picky_pE    = fs->make<TH1F>("Picky_pE", "Picky - P"   , 2*psim,  0., 2*psim);

  GLB_p       = fs->make<TH1F>("GLB_p"   , "GLB - P"     , 2*psim,  0., 2*psim);
  GLB_pB      = fs->make<TH1F>("GLB_pB"  , "GLB - P"     , 2*psim,  0., 2*psim);
  GLB_pE      = fs->make<TH1F>("GLB_pE"  , "GLB - P"     , 2*psim,  0., 2*psim);

  StdA_p      = fs->make<TH1F>("StdA_p"   , "StdA - P"   , 2*psim,  0., 2*psim);
  StdA_pB     = fs->make<TH1F>("StdA_pB"  , "StdA - P"   , 2*psim,  0., 2*psim);
  StdA_pE     = fs->make<TH1F>("StdA_pE"  , "StdA - P"   , 2*psim,  0., 2*psim);

  //Spectrum of Momentum in Eta Bins
  DYT_sp       = fs->make<TH1F>("DYT_sp"     , "DYT - P"     , 500000,  0., 50000);
  DYT_spE08    = fs->make<TH1F>("DYT_spE08"    , "DYT - P - 0 < #lbar #eta #cbar <= 0.8"       , 500000,  0., 50000);
  DYT_spE12    = fs->make<TH1F>("DYT_spE12"  , "DYT - P - 0.8 < #lbar #eta #cbar <= 1.2"     , 500000,  0., 50000);
  DYT_spE20    = fs->make<TH1F>("DYT_spE20"  , "DYT - P - 1.2 < #lbar #eta #cbar <= 2.0"     , 500000,  0., 50000);
  DYT_spE22    = fs->make<TH1F>("DYT_spE22"  , "DYT - P - 2.0 < #lbar #eta #cbar <= 2.2"     , 500000,  0., 50000);
  DYT_spE24    = fs->make<TH1F>("DYT_spE24"  , "DYT - P - 2.2 < #lbar #eta #cbar <= 2.4"     , 500000,  0., 50000);

  DYT_Res_InvpE08 = fs->make<TH1F>("DYT_Res_InvPE08"   , "DYT - Res_P - 0 < #lbar #eta #cbar <= 0.8"     , 1200,  -0.6,  0.6);
  DYT_Res_InvpE12 = fs->make<TH1F>("DYT_Res_InvPE12"   , "DYT - Res_P - 0.8 < #lbar #eta #cbar <= 1.2"   , 1200,  -0.6,  0.6);
  DYT_Res_InvpE20 = fs->make<TH1F>("DYT_Res_InvPE20"   , "DYT - Res_P - 1.2 < #lbar #eta #cbar <= 2.0"   , 1200,  -0.6,  0.6);
  DYT_Res_InvpE22 = fs->make<TH1F>("DYT_Res_InvPE22"   , "DYT - Res_P - 2.0 < #lbar #eta #cbar <= 2.2"   , 1200,  -0.6,  0.6);
  DYT_Res_InvpE24 = fs->make<TH1F>("DYT_Res_InvPE24"   , "DYT - Res_P - 2.2 < #lbar #eta #cbar <= 2.4"   , 1200,  -0.6,  0.6);

  TuneP_spE08    = fs->make<TH1F>("TuneP_spE08"    , "TuneP - P - 0 < #lbar #eta #cbar <= 0.8"     , 500000,  0., 50000);
  TuneP_spE12    = fs->make<TH1F>("TuneP_spE12"  , "TuneP - P - 0.8 < #lbar #eta #cbar <= 1.2"     , 500000,  0., 50000);
  TuneP_spE20    = fs->make<TH1F>("TuneP_spE20"  , "TuneP - P - 1.2 < #lbar #eta #cbar <= 2.0"     , 500000,  0., 50000);
  TuneP_spE22    = fs->make<TH1F>("TuneP_spE22"  , "TuneP - P - 2.0 < #lbar #eta #cbar <= 2.2"     , 500000,  0., 50000);
  TuneP_spE24    = fs->make<TH1F>("TuneP_spE24"  , "TuneP - P - 2.2 < #lbar #eta #cbar <= 2.4"     , 500000,  0., 50000);

  TuneP_Res_InvpE08 = fs->make<TH1F>("TuneP_Res_InvPE08"   , "TuneP - Res_P - 0 < #lbar #eta #cbar <= 0.8"     , 1200,  -0.6,  0.6);
  TuneP_Res_InvpE12 = fs->make<TH1F>("TuneP_Res_InvPE12"   , "TuneP - Res_P - 0.8 < #lbar #eta #cbar <= 1.2"   , 1200,  -0.6,  0.6);
  TuneP_Res_InvpE20 = fs->make<TH1F>("TuneP_Res_InvPE20"   , "TuneP - Res_P - 1.2 < #lbar #eta #cbar <= 2.0"   , 1200,  -0.6,  0.6);
  TuneP_Res_InvpE22 = fs->make<TH1F>("TuneP_Res_InvPE22"   , "TuneP - Res_P - 2.0 < #lbar #eta #cbar <= 2.2"   , 1200,  -0.6,  0.6);
  TuneP_Res_InvpE24 = fs->make<TH1F>("TuneP_Res_InvPE24"   , "TuneP - Res_P - 2.2 < #lbar #eta #cbar <= 2.4"   , 1200,  -0.6,  0.6);

  //Momentum OverFlow
  DYT_pOv       = fs->make<TH1F>("DYT_pOv"   , "DYT - P OvFlow"     , 4*psim,  2*psim, 6*psim);
  DYT_pBOv      = fs->make<TH1F>("DYT_pBOv"  , "DYT - P OvFlow"     , 4*psim,  2*psim, 6*psim);
  DYT_pEOv      = fs->make<TH1F>("DYT_pEOv"  , "DYT - P OvFlow"     , 4*psim,  2*psim, 6*psim);

  TuneP_pOv     = fs->make<TH1F>("TuneP_pOv" , "TuneP - P OvFlow"   , 4*psim,  2*psim, 6*psim);
  TuneP_pBOv    = fs->make<TH1F>("TuneP_pBOv", "TuneP - P OvFlow"   , 4*psim,  2*psim, 6*psim);
  TuneP_pEOv    = fs->make<TH1F>("TuneP_pEOv", "TuneP - P OvFlow"   , 4*psim,  2*psim, 6*psim);

  Picky_pOv     = fs->make<TH1F>("Picky_pOv" , "Picky - P OvFlow"   , 4*psim,  2*psim, 6*psim);
  Picky_pBOv    = fs->make<TH1F>("Picky_pBOv", "Picky - P OvFlow"   , 4*psim,  2*psim, 6*psim);
  Picky_pEOv    = fs->make<TH1F>("Picky_pEOv", "Picky - P OvFlow"   , 4*psim,  2*psim, 6*psim);

  GLB_pOv       = fs->make<TH1F>("GLB_pOv"   , "GLB - P OvFlow"     , 4*psim,  2*psim, 6*psim);
  GLB_pBOv      = fs->make<TH1F>("GLB_pBOv"  , "GLB - P OvFlow"     , 4*psim,  2*psim, 6*psim);
  GLB_pEOv      = fs->make<TH1F>("GLB_pEOv"  , "GLB - P OvFlow"     , 4*psim,  2*psim, 6*psim);

  StdA_pOv      = fs->make<TH1F>("StdA_pOv"   , "StdA - P OvFlow"   , 4*psim,  2*psim, 6*psim);
  StdA_pBOv     = fs->make<TH1F>("StdA_pBOv"  , "StdA - P OvFlow"   , 4*psim,  2*psim, 6*psim);
  StdA_pEOv     = fs->make<TH1F>("StdA_pEOv"  , "StdA - P OvFlow"   , 4*psim,  2*psim, 6*psim);

  //Pull Transverse Momentum
  DYT_Pull_pt       = fs->make<TH1F>("DYT_Pull_pt"   , "DYT - Pull_pT"     , 200,  -20,  20);
  DYT_Pull_ptB      = fs->make<TH1F>("DYT_Pull_ptB"  , "DYT - Pull_pT"     , 200,  -20,  20);
  DYT_Pull_ptE      = fs->make<TH1F>("DYT_Pull_ptE"  , "DYT - Pull_pT"     , 200,  -20,  20);

  TuneP_Pull_pt     = fs->make<TH1F>("TuneP_Pull_pt" , "TuneP - Pull_pT"   , 200,  -20,  20);
  TuneP_Pull_ptB    = fs->make<TH1F>("TuneP_Pull_ptB", "TuneP - Pull_pT"   , 200,  -20,  20);
  TuneP_Pull_ptE    = fs->make<TH1F>("TuneP_Pull_ptE", "TuneP - Pull_pT"   , 200,  -20,  20);

  Picky_Pull_pt     = fs->make<TH1F>("Picky_Pull_pt" , "Picky - Pull_pT"   , 200,  -20,  20);
  Picky_Pull_ptB    = fs->make<TH1F>("Picky_Pull_ptB", "Picky - Pull_pT"   , 200,  -20,  20);
  Picky_Pull_ptE    = fs->make<TH1F>("Picky_Pull_ptE", "Picky - Pull_pT"   , 200,  -20,  20);

  GLB_Pull_pt       = fs->make<TH1F>("GLB_Pull_pt"   , "GLB - Pull_pT"     , 200,  -20,  20);
  GLB_Pull_ptB      = fs->make<TH1F>("GLB_Pull_ptB"  , "GLB - Pull_pT"     , 200,  -20,  20);
  GLB_Pull_ptE      = fs->make<TH1F>("GLB_Pull_ptE"  , "GLB - Pull_pT"     , 200,  -20,  20);

  StdA_Pull_pt      = fs->make<TH1F>("StdA_Pull_pt"   , "StdA - Pull_pT"   , 200,  -20,  20);
  StdA_Pull_ptB     = fs->make<TH1F>("StdA_Pull_ptB"  , "StdA - Pull_pT"   , 200,  -20,  20);
  StdA_Pull_ptE     = fs->make<TH1F>("StdA_Pull_ptE"  , "StdA - Pull_pT"   , 200,  -20,  20);

  //Eta and Phi Distribution
  DYT_eta        = fs->make<TH1F>("DYT_eta"     , "DYT - eta"     ,     520,            -2.6,            2.6);
  TuneP_eta      = fs->make<TH1F>("TuneP_eta"   , "TuneP - eta"   ,     520,            -2.6,            2.6);
  Picky_eta      = fs->make<TH1F>("Picky_eta"   , "Picky - eta"   ,     520,            -2.6,            2.6);
  GLB_eta        = fs->make<TH1F>("GLB_eta"     , "GLB - eta"     ,     520,            -2.6,            2.6);
  StdA_eta       = fs->make<TH1F>("StdA_eta"    , "StdA - eta"    ,     520,            -2.6,            2.6);
  TrkM_eta       = fs->make<TH1F>("TrkM_eta"    , "TrkM - eta"    ,     520,            -2.6,            2.6);

  //Phi Distribution
  DYT_phi        = fs->make<TH1F>("DYT_phi"     , "DYT - phi"     ,     648,    -TMath::Pi(),    TMath::Pi());
  TuneP_phi      = fs->make<TH1F>("TuneP_phi"   , "TuneP - phi"   ,     648,    -TMath::Pi(),    TMath::Pi());
  Picky_phi      = fs->make<TH1F>("Picky_phi"   , "Picky - phi"   ,     648,    -TMath::Pi(),    TMath::Pi());
  GLB_phi        = fs->make<TH1F>("GLB_phi"     , "GLB - phi"     ,     648,    -TMath::Pi(),    TMath::Pi());
  StdA_phi       = fs->make<TH1F>("StdA_phi"    , "StdA - phi"    ,     648,    -TMath::Pi(),    TMath::Pi());
  TrkM_phi       = fs->make<TH1F>("TrkM_phi"    , "TrkM - phi"    ,     648,    -TMath::Pi(),    TMath::Pi());

  // ptsim(1/ptsim - 1/ptrec) = 1 - 1000/pt
  InvDYT_pt    = fs->make<TH1F>("InvDYT_pt"   , "InvDYT - pT"   , 2000, -1., 1);
  InvDYT_ptB   = fs->make<TH1F>("InvDYT_ptB"  , "InvDYT - pT"   , 2000, -1., 1);
  InvDYT_ptE   = fs->make<TH1F>("InvDYT_ptE"  , "InvDYT - pT"   , 2000, -1., 1);

  InvTuneP_pt  = fs->make<TH1F>("InvTuneP_pt" , "InvTuneP - pT" , 2000, -1., 1);
  InvTuneP_ptB = fs->make<TH1F>("InvTuneP_ptB", "InvTuneP - pT" , 2000, -1., 1);
  InvTuneP_ptE = fs->make<TH1F>("InvTuneP_ptE", "InvTuneP - pT" , 2000, -1., 1);

  InvPicky_pt  = fs->make<TH1F>("InvPicky_pt" , "InvPicky - pT" , 2000, -1., 1);
  InvPicky_ptB = fs->make<TH1F>("InvPicky_ptB", "InvPicky - pT" , 2000, -1., 1);
  InvPicky_ptE = fs->make<TH1F>("InvPicky_ptE", "InvPicky - pT" , 2000, -1., 1);

  InvGLB_pt    = fs->make<TH1F>("InvGLB_pt"   , "InvGLB - pT"   , 2000, -1., 1);
  InvGLB_ptB   = fs->make<TH1F>("InvGLB_ptB"  , "InvGLB - pT"   , 2000, -1., 1);
  InvGLB_ptE   = fs->make<TH1F>("InvGLB_ptE"  , "InvGLB - pT"   , 2000, -1., 1);

  InvStdA_pt   = fs->make<TH1F>("InvStdA_pt"  , "InvStdA - pT"   , 2000, -1., 1);
  InvStdA_ptB  = fs->make<TH1F>("InvStdA_ptB" , "InvStdA - pT"   , 2000, -1., 1);
  InvStdA_ptE  = fs->make<TH1F>("InvStdA_ptE" , "InvStdA - pT"   , 2000, -1., 1);

  InvTrkM_pt   = fs->make<TH1F>("InvTrkM_pt"  , "InvTrkM - pT"   , 2000, -1., 1);
  InvTrkM_ptB  = fs->make<TH1F>("InvTrkM_ptB" , "InvTrkM - pT"   , 2000, -1., 1);
  InvTrkM_ptE  = fs->make<TH1F>("InvTrkM_ptE" , "InvTrkM - pT"   , 2000, -1., 1);

  //Chi2 Normalized
  Chi2N_DYT      = fs->make<TH1F>("DYT_Chi2N",      "DYT - Chi2 Normalized",            3000, 0., 30);
  Chi2N_DYT_B    = fs->make<TH1F>("DYT_Chi2NB",     "DYT - Chi2 Normalized Barrel",     3000, 0., 30);
  Chi2N_DYT_E    = fs->make<TH1F>("DYT_Chi2NE",     "DYT - Chi2 Normalized EndCap",     3000, 0., 30);

  Chi2N_TuneP    = fs->make<TH1F>("TuneP_Chi2N",    "TuneP - Chi2 Normalized",          3000, 0., 30);
  Chi2N_TuneP_B  = fs->make<TH1F>("TuneP_Chi2NB",   "TuneP - Chi2 Normalized Barrel",   3000, 0., 30);
  Chi2N_TuneP_E  = fs->make<TH1F>("TuneP_Chi2NE",   "TuneP - Chi2 Normalized EndCap",   3000, 0., 30);

  Chi2N_Picky    = fs->make<TH1F>("Picky_Chi2N",    "Picky - Chi2 Normalized",          3000, 0., 30);
  Chi2N_Picky_B  = fs->make<TH1F>("Picky_Chi2NB",   "Picky - Chi2 Normalized Barrel",   3000, 0., 30);
  Chi2N_Picky_E  = fs->make<TH1F>("Picky_Chi2NE",   "Picky - Chi2 Normalized EndCap",   3000, 0., 30);

  Chi2N_GLB      = fs->make<TH1F>("GLB_Chi2N",      "GBL - Chi2 Normalized",            3000, 0., 30);
  Chi2N_GLB_B    = fs->make<TH1F>("GLB_Chi2NB",     "GBL - Chi2 Normalized Barrel",     3000, 0., 30);
  Chi2N_GLB_E    = fs->make<TH1F>("GLB_Chi2NE",     "GBL - Chi2 Normalized EndCap",     3000, 0., 30);

  Chi2N_StdA     = fs->make<TH1F>("StdA_Chi2N",     "StdA - Chi2 Normalized",           3000, 0., 30);
  Chi2N_StdA_B   = fs->make<TH1F>("StdA_Chi2NB",    "StdA - Chi2 Normalized Barrel",    3000, 0., 30);
  Chi2N_StdA_E   = fs->make<TH1F>("StdA_Chi2NE",    "StdA - Chi2 Normalized EndCap",    3000, 0., 30);

  Chi2N_TrkM     = fs->make<TH1F>("TrkM_Chi2N",     "TrkM - Chi2 Normalized",           3000, 0., 30);
  Chi2N_TrkM_B   = fs->make<TH1F>("TrkM_Chi2NB",    "TrkM - Chi2 Normalized Barrel",    3000, 0., 30);
  Chi2N_TrkM_E   = fs->make<TH1F>("TrkM_Chi2NE",    "TrkM - Chi2 Normalized EndCap",    3000, 0., 30);

  //Resolution  Inverse Pt Vs Eta
  ResInvPt_Eta_DYT_M24  = fs->make<TH1F>("DYT_ResInvPt_Eta_M24",    "DYT - Resolution Vs -2.4 < Eta < -2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_M21  = fs->make<TH1F>("DYT_ResInvPt_Eta_M21",    "DYT - Resolution Vs -2.1 < Eta < -1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_M18  = fs->make<TH1F>("DYT_ResInvPt_Eta_M18",    "DYT - Resolution Vs -1.8 < Eta < -1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_M15  = fs->make<TH1F>("DYT_ResInvPt_Eta_M15",    "DYT - Resolution Vs -1.5 < Eta < -1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_M12  = fs->make<TH1F>("DYT_ResInvPt_Eta_M12",    "DYT - Resolution Vs -1.2 < Eta < -0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_M09  = fs->make<TH1F>("DYT_ResInvPt_Eta_M09",    "DYT - Resolution Vs -0.9 < Eta < -0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_M06  = fs->make<TH1F>("DYT_ResInvPt_Eta_M06",    "DYT - Resolution Vs -0.6 < Eta < -0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_M03  = fs->make<TH1F>("DYT_ResInvPt_Eta_M03",    "DYT - Resolution Vs -0.3 < Eta <  0",     1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_M0   = fs->make<TH1F>("DYT_ResInvPt_Eta_M0",     "DYT - Resolution Vs    0 < Eta < +0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_P03  = fs->make<TH1F>("DYT_ResInvPt_Eta_P03",    "DYT - Resolution Vs +0.3 < Eta < +0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_P06  = fs->make<TH1F>("DYT_ResInvPt_Eta_P06",    "DYT - Resolution Vs +0.6 < Eta < +0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_P09  = fs->make<TH1F>("DYT_ResInvPt_Eta_P09",    "DYT - Resolution Vs +0.9 < Eta < +1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_P12  = fs->make<TH1F>("DYT_ResInvPt_Eta_P12",    "DYT - Resolution Vs +1.2 < Eta < +1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_P15  = fs->make<TH1F>("DYT_ResInvPt_Eta_P15",    "DYT - Resolution Vs +1.5 < Eta < +1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_P18  = fs->make<TH1F>("DYT_ResInvPt_Eta_P21",    "DYT - Resolution Vs +1.8 < Eta < +2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_DYT_P21  = fs->make<TH1F>("DYT_ResInvPt_Eta_P24",    "DYT - Resolution Vs +2.1 < Eta < +2.4",   1200,  -0.005,  +0.005);


  ResInvPt_Eta_TuneP_M24  = fs->make<TH1F>("TuneP_ResInvPt_Eta_M24", "TuneP - Resolution Vs -2.4 < Eta < -2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_M21  = fs->make<TH1F>("TuneP_ResInvPt_Eta_M21", "TuneP - Resolution Vs -2.1 < Eta < -1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_M18  = fs->make<TH1F>("TuneP_ResInvPt_Eta_M18", "TuneP - Resolution Vs -1.8 < Eta < -1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_M15  = fs->make<TH1F>("TuneP_ResInvPt_Eta_M15", "TuneP - Resolution Vs -1.5 < Eta < -1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_M12  = fs->make<TH1F>("TuneP_ResInvPt_Eta_M12", "TuneP - Resolution Vs -1.2 < Eta < -0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_M09  = fs->make<TH1F>("TuneP_ResInvPt_Eta_M09", "TuneP - Resolution Vs -0.9 < Eta < -0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_M06  = fs->make<TH1F>("TuneP_ResInvPt_Eta_M06", "TuneP - Resolution Vs -0.6 < Eta < -0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_M03  = fs->make<TH1F>("TuneP_ResInvPt_Eta_M03", "TuneP - Resolution Vs -0.3 < Eta <  0",     1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_M0   = fs->make<TH1F>("TuneP_ResInvPt_Eta_M0",  "TuneP - Resolution Vs    0 < Eta < +0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_P03  = fs->make<TH1F>("TuneP_ResInvPt_Eta_P03", "TuneP - Resolution Vs +0.3 < Eta < +0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_P06  = fs->make<TH1F>("TuneP_ResInvPt_Eta_P06", "TuneP - Resolution Vs +0.6 < Eta < +0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_P09  = fs->make<TH1F>("TuneP_ResInvPt_Eta_P09", "TuneP - Resolution Vs +0.9 < Eta < +1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_P12  = fs->make<TH1F>("TuneP_ResInvPt_Eta_P12", "TuneP - Resolution Vs +1.2 < Eta < +1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_P15  = fs->make<TH1F>("TuneP_ResInvPt_Eta_P15", "TuneP - Resolution Vs +1.5 < Eta < +1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_P18  = fs->make<TH1F>("TuneP_ResInvPt_Eta_P21", "TuneP - Resolution Vs +1.8 < Eta < +2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_TuneP_P21  = fs->make<TH1F>("TuneP_ResInvPt_Eta_P24", "TuneP - Resolution Vs +2.1 < Eta < +2.4",   1200,  -0.005,  +0.005);

  ResInvPt_Eta_Picky_M24  = fs->make<TH1F>("Picky_ResInvPt_Eta_M24", "Picky - Resolution Vs -2.4 < Eta < -2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_M21  = fs->make<TH1F>("Picky_ResInvPt_Eta_M21", "Picky - Resolution Vs -2.1 < Eta < -1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_M18  = fs->make<TH1F>("Picky_ResInvPt_Eta_M18", "Picky - Resolution Vs -1.8 < Eta < -1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_M15  = fs->make<TH1F>("Picky_ResInvPt_Eta_M15", "Picky - Resolution Vs -1.5 < Eta < -1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_M12  = fs->make<TH1F>("Picky_ResInvPt_Eta_M12", "Picky - Resolution Vs -1.2 < Eta < -0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_M09  = fs->make<TH1F>("Picky_ResInvPt_Eta_M09", "Picky - Resolution Vs -0.9 < Eta < -0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_M06  = fs->make<TH1F>("Picky_ResInvPt_Eta_M06", "Picky - Resolution Vs -0.6 < Eta < -0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_M03  = fs->make<TH1F>("Picky_ResInvPt_Eta_M03", "Picky - Resolution Vs -0.3 < Eta <  0",     1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_M0   = fs->make<TH1F>("Picky_ResInvPt_Eta_M0",  "Picky - Resolution Vs    0 < Eta < +0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_P03  = fs->make<TH1F>("Picky_ResInvPt_Eta_P03", "Picky - Resolution Vs +0.3 < Eta < +0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_P06  = fs->make<TH1F>("Picky_ResInvPt_Eta_P06", "Picky - Resolution Vs +0.6 < Eta < +0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_P09  = fs->make<TH1F>("Picky_ResInvPt_Eta_P09", "Picky - Resolution Vs +0.9 < Eta < +1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_P12  = fs->make<TH1F>("Picky_ResInvPt_Eta_P12", "Picky - Resolution Vs +1.2 < Eta < +1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_P15  = fs->make<TH1F>("Picky_ResInvPt_Eta_P15", "Picky - Resolution Vs +1.5 < Eta < +1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_P18  = fs->make<TH1F>("Picky_ResInvPt_Eta_P18", "Picky - Resolution Vs +1.8 < Eta < +2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_Picky_P21  = fs->make<TH1F>("Picky_ResInvPt_Eta_P21", "Picky - Resolution Vs +2.1 < Eta < +2.4",   1200,  -0.005,  +0.005);


  ResInvPt_Eta_GLB_M24    = fs->make<TH1F>("GLB_ResInvPt_Eta_M24",    "GLB - Resolution Vs -2.4 < Eta < -2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_M21    = fs->make<TH1F>("GLB_ResInvPt_Eta_M21",    "GLB - Resolution Vs -2.1 < Eta < -1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_M18    = fs->make<TH1F>("GLB_ResInvPt_Eta_M18",    "GLB - Resolution Vs -1.8 < Eta < -1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_M15    = fs->make<TH1F>("GLB_ResInvPt_Eta_M15",    "GLB - Resolution Vs -1.5 < Eta < -1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_M12    = fs->make<TH1F>("GLB_ResInvPt_Eta_M12",    "GLB - Resolution Vs -1.2 < Eta < -0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_M09    = fs->make<TH1F>("GLB_ResInvPt_Eta_M09",    "GLB - Resolution Vs -0.9 < Eta < -0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_M06    = fs->make<TH1F>("GLB_ResInvPt_Eta_M06",    "GLB - Resolution Vs -0.6 < Eta < -0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_M03    = fs->make<TH1F>("GLB_ResInvPt_Eta_M03",    "GLB - Resolution Vs -0.3 < Eta <  0",     1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_M0     = fs->make<TH1F>("GLB_ResInvPt_Eta_M0",     "GLB - Resolution Vs    0 < Eta < +0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_P03    = fs->make<TH1F>("GLB_ResInvPt_Eta_P03",    "GLB - Resolution Vs +0.3 < Eta < +0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_P06    = fs->make<TH1F>("GLB_ResInvPt_Eta_P06",    "GLB - Resolution Vs +0.6 < Eta < +0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_P09    = fs->make<TH1F>("GLB_ResInvPt_Eta_P09",    "GLB - Resolution Vs +0.9 < Eta < +1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_P12    = fs->make<TH1F>("GLB_ResInvPt_Eta_P12",    "GLB - Resolution Vs +1.2 < Eta < +1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_P15    = fs->make<TH1F>("GLB_ResInvPt_Eta_P15",    "GLB - Resolution Vs +1.5 < Eta < +1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_P18    = fs->make<TH1F>("GLB_ResInvPt_Eta_P18",    "GLB - Resolution Vs +1.8 < Eta < +2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_GLB_P21    = fs->make<TH1F>("GLB_ResInvPt_Eta_P21",    "GLB - Resolution Vs +2.1 < Eta < +2.4",   1200,  -0.005,  +0.005);

  ResInvPt_Eta_StdA_M24    = fs->make<TH1F>("StdA_ResInvPt_Eta_M24",    "StdA - Resolution Vs -2.4 < Eta < -2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_M21    = fs->make<TH1F>("StdA_ResInvPt_Eta_M21",    "StdA - Resolution Vs -2.1 < Eta < -1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_M18    = fs->make<TH1F>("StdA_ResInvPt_Eta_M18",    "StdA - Resolution Vs -1.8 < Eta < -1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_M15    = fs->make<TH1F>("StdA_ResInvPt_Eta_M15",    "StdA - Resolution Vs -1.5 < Eta < -1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_M12    = fs->make<TH1F>("StdA_ResInvPt_Eta_M12",    "StdA - Resolution Vs -1.2 < Eta < -0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_M09    = fs->make<TH1F>("StdA_ResInvPt_Eta_M09",    "StdA - Resolution Vs -0.9 < Eta < -0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_M06    = fs->make<TH1F>("StdA_ResInvPt_Eta_M06",    "StdA - Resolution Vs -0.6 < Eta < -0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_M03    = fs->make<TH1F>("StdA_ResInvPt_Eta_M03",    "StdA - Resolution Vs -0.3 < Eta <  0",     1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_M0     = fs->make<TH1F>("StdA_ResInvPt_Eta_M0",     "StdA - Resolution Vs    0 < Eta < +0.3",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_P03    = fs->make<TH1F>("StdA_ResInvPt_Eta_P03",    "StdA - Resolution Vs +0.3 < Eta < +0.6",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_P06    = fs->make<TH1F>("StdA_ResInvPt_Eta_P06",    "StdA - Resolution Vs +0.6 < Eta < +0.9",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_P09    = fs->make<TH1F>("StdA_ResInvPt_Eta_P09",    "StdA - Resolution Vs +0.9 < Eta < +1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_P12    = fs->make<TH1F>("StdA_ResInvPt_Eta_P12",    "StdA - Resolution Vs +1.2 < Eta < +1.5",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_P15    = fs->make<TH1F>("StdA_ResInvPt_Eta_P15",    "StdA - Resolution Vs +1.5 < Eta < +1.8",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_P18    = fs->make<TH1F>("StdA_ResInvPt_Eta_P18",    "StdA - Resolution Vs +1.8 < Eta < +2.1",   1200,  -0.005,  +0.005);
  ResInvPt_Eta_StdA_P21    = fs->make<TH1F>("StdA_ResInvPt_Eta_P21",    "StdA - Resolution Vs +2.1 < Eta < +2.4",   1200,  -0.005,  +0.005);

  //Resolution Vs Phi
  ResInvPt_Phi_DYT_M36       = fs->make<TH1F>("DYT_ResInvPt_Phi_M36", "DYT - Resolution Vs  -3.6 < Phi < -3.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M32       = fs->make<TH1F>("DYT_ResInvPt_Phi_M32", "DYT - Resolution Vs  -3.2 < Phi < -2.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M28       = fs->make<TH1F>("DYT_ResInvPt_Phi_M28", "DYT - Resolution Vs  -2.8 < Phi < -2.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M24       = fs->make<TH1F>("DYT_ResInvPt_Phi_M24", "DYT - Resolution Vs  -2.4 < Phi < -2.0",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M20       = fs->make<TH1F>("DYT_ResInvPt_Phi_M20", "DYT - Resolution Vs  -2.0 < Phi < -1.6",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M16       = fs->make<TH1F>("DYT_ResInvPt_Phi_M16", "DYT - Resolution Vs  -1.6 < Phi < -1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M12       = fs->make<TH1F>("DYT_ResInvPt_Phi_M12", "DYT - Resolution Vs  -1.2 < Phi < -0.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M08       = fs->make<TH1F>("DYT_ResInvPt_Phi_M08", "DYT - Resolution Vs  -0.8 < Phi < -0.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M04       = fs->make<TH1F>("DYT_ResInvPt_Phi_M04", "DYT - Resolution Vs  -0.4 < Phi < -0",     1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_M0        = fs->make<TH1F>("DYT_ResInvPt_Phi_M0",  "DYT - Resolution Vs     0 < Phi < +0.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_P04       = fs->make<TH1F>("DYT_ResInvPt_Phi_P04", "DYT - Resolution Vs  +0.4 < Phi < +0.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_P08       = fs->make<TH1F>("DYT_ResInvPt_Phi_P08", "DYT - Resolution Vs  +0.8 < Phi < +1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_P12       = fs->make<TH1F>("DYT_ResInvPt_Phi_P12", "DYT - Resolution Vs  +1.2 < Phi < +1.6",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_P16       = fs->make<TH1F>("DYT_ResInvPt_Phi_P16", "DYT - Resolution Vs  +1.6 < Phi < +2.0",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_P20       = fs->make<TH1F>("DYT_ResInvPt_Phi_P20", "DYT - Resolution Vs  +2.0 < Phi < +2.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_P24       = fs->make<TH1F>("DYT_ResInvPt_Phi_P24", "DYT - Resolution Vs  +2.4 < Phi < +2.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_P28       = fs->make<TH1F>("DYT_ResInvPt_Phi_P28", "DYT - Resolution Vs  +2.8 < Phi < +3.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_DYT_P32       = fs->make<TH1F>("DYT_ResInvPt_Phi_P32", "DYT - Resolution Vs  +3.2 < Phi < +3.6",   1200,  -0.005,  +0.005);

  ResInvPt_Phi_TuneP_M36     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M36","TuneP - Resolution Vs  -3.6 < Phi < -3.2",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M32     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M32","TuneP - Resolution Vs  -3.2 < Phi < -2.8",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M28     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M28","TuneP - Resolution Vs  -2.8 < Phi < -2.4",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M24     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M24","TuneP - Resolution Vs  -2.4 < Phi < -2.0",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M20     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M20","TuneP - Resolution Vs  -2.0 < Phi < -1.6",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M16     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M16","TuneP - Resolution Vs  -1.6 < Phi < -1.2",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M12     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M12","TuneP - Resolution Vs  -1.2 < Phi < -0.8",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M08     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M08","TuneP - Resolution Vs  -0.8 < Phi < -0.4",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M04     = fs->make<TH1F>("TuneP_ResInvPt_Phi_M04","TuneP - Resolution Vs  -0.4 < Phi < -0",    1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_M0      = fs->make<TH1F>("TuneP_ResInvPt_Phi_M0", "TuneP - Resolution Vs     0 < Phi < +0.4",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_P04     = fs->make<TH1F>("TuneP_ResInvPt_Phi_P04","TuneP - Resolution Vs  +0.4 < Phi < +0.8",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_P08     = fs->make<TH1F>("TuneP_ResInvPt_Phi_P08","TuneP - Resolution Vs  +0.8 < Phi < +1.2",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_P12     = fs->make<TH1F>("TuneP_ResInvPt_Phi_P12","TuneP - Resolution Vs  +1.2 < Phi < +1.6",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_P16     = fs->make<TH1F>("TuneP_ResInvPt_Phi_P16","TuneP - Resolution Vs  +1.6 < Phi < +2.0",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_P20     = fs->make<TH1F>("TuneP_ResInvPt_Phi_P20","TuneP - Resolution Vs  +2.0 < Phi < +2.4",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_P24     = fs->make<TH1F>("TuneP_ResInvPt_Phi_P24","TuneP - Resolution Vs  +2.4 < Phi < +2.8",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_P28     = fs->make<TH1F>("TuneP_ResInvPt_Phi_P28","TuneP - Resolution Vs  +2.8 < Phi < +3.2",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_TuneP_P32     = fs->make<TH1F>("TuneP_ResInvPt_Phi_P32","TuneP - Resolution Vs  +3.2 < Phi < +3.6",  1200,  -0.005,  +0.005);

  ResInvPt_Phi_Picky_M36     = fs->make<TH1F>("Picky_ResInvPt_Phi_M36","Picky - Resolution Vs  -3.6 < Phi < -3.2",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M32     = fs->make<TH1F>("Picky_ResInvPt_Phi_M32","Picky - Resolution Vs  -3.2 < Phi < -2.8",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M28     = fs->make<TH1F>("Picky_ResInvPt_Phi_M28","Picky - Resolution Vs  -2.8 < Phi < -2.4",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M24     = fs->make<TH1F>("Picky_ResInvPt_Phi_M24","Picky - Resolution Vs  -2.4 < Phi < -2.0",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M20     = fs->make<TH1F>("Picky_ResInvPt_Phi_M20","Picky - Resolution Vs  -2.0 < Phi < -1.6",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M16     = fs->make<TH1F>("Picky_ResInvPt_Phi_M16","Picky - Resolution Vs  -1.6 < Phi < -1.2",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M12     = fs->make<TH1F>("Picky_ResInvPt_Phi_M12","Picky - Resolution Vs  -1.2 < Phi < -0.8",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M08     = fs->make<TH1F>("Picky_ResInvPt_Phi_M08","Picky - Resolution Vs  -0.8 < Phi < -0.4",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M04     = fs->make<TH1F>("Picky_ResInvPt_Phi_M04","Picky - Resolution Vs  -0.4 < Phi < -0",    1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_M0      = fs->make<TH1F>("Picky_ResInvPt_Phi_M0", "Picky - Resolution Vs     0 < Phi < +0.4",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_P04     = fs->make<TH1F>("Picky_ResInvPt_Phi_P04","Picky - Resolution Vs  +0.4 < Phi < +0.8",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_P08     = fs->make<TH1F>("Picky_ResInvPt_Phi_P08","Picky - Resolution Vs  +0.8 < Phi < +1.2",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_P12     = fs->make<TH1F>("Picky_ResInvPt_Phi_P12","Picky - Resolution Vs  +1.2 < Phi < +1.6",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_P16     = fs->make<TH1F>("Picky_ResInvPt_Phi_P16","Picky - Resolution Vs  +1.6 < Phi < +2.0",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_P20     = fs->make<TH1F>("Picky_ResInvPt_Phi_P20","Picky - Resolution Vs  +2.0 < Phi < +2.4",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_P24     = fs->make<TH1F>("Picky_ResInvPt_Phi_P24","Picky - Resolution Vs  +2.4 < Phi < +2.8",  1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_P28     = fs->make<TH1F>("Picky_ResInvPt_Phi_P28","Picky - Resolution Vs  +2.8 < Phi < +3.2", 1200,  -0.005,  +0.005);
  ResInvPt_Phi_Picky_P32     = fs->make<TH1F>("Picky_ResInvPt_Phi_P32","Picky - Resolution Vs  +3.2 < Phi < +3.6",  1200,  -0.005,  +0.005);

  ResInvPt_Phi_GLB_M36       = fs->make<TH1F>("GLB_ResInvPt_Phi_M36",   "GLB - Resolution Vs  -3.6 < Phi < -3.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M32       = fs->make<TH1F>("GLB_ResInvPt_Phi_M32",   "GLB - Resolution Vs  -3.2 < Phi < -2.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M28       = fs->make<TH1F>("GLB_ResInvPt_Phi_M28",   "GLB - Resolution Vs  -2.8 < Phi < -2.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M24       = fs->make<TH1F>("GLB_ResInvPt_Phi_M24",   "GLB - Resolution Vs  -2.4 < Phi < -2.0",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M20       = fs->make<TH1F>("GLB_ResInvPt_Phi_M20",   "GLB - Resolution Vs  -2.0 < Phi < -1.6",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M16       = fs->make<TH1F>("GLB_ResInvPt_Phi_M16",   "GLB - Resolution Vs  -1.6 < Phi < -1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M12       = fs->make<TH1F>("GLB_ResInvPt_Phi_M12",   "GLB - Resolution Vs  -1.2 < Phi < -0.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M08       = fs->make<TH1F>("GLB_ResInvPt_Phi_M08",   "GLB - Resolution Vs  -0.8 < Phi < -0.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M04       = fs->make<TH1F>("GLB_ResInvPt_Phi_M04",   "GLB - Resolution Vs  -0.4 < Phi < -0",     1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_M0        = fs->make<TH1F>("GLB_ResInvPt_Phi_M0",    "GLB - Resolution Vs     0 < Phi < +0.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_P04       = fs->make<TH1F>("GLB_ResInvPt_Phi_P04",   "GLB - Resolution Vs  +0.4 < Phi < +0.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_P08       = fs->make<TH1F>("GLB_ResInvPt_Phi_P08",   "GLB - Resolution Vs  +0.8 < Phi < +1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_P12       = fs->make<TH1F>("GLB_ResInvPt_Phi_P12",   "GLB - Resolution Vs  +1.2 < Phi < +1.6",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_P16       = fs->make<TH1F>("GLB_ResInvPt_Phi_P16",   "GLB - Resolution Vs  +1.6 < Phi < +2.0",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_P20       = fs->make<TH1F>("GLB_ResInvPt_Phi_P20",   "GLB - Resolution Vs  +2.0 < Phi < +2.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_P24       = fs->make<TH1F>("GLB_ResInvPt_Phi_P24",   "GLB - Resolution Vs  +2.4 < Phi < +2.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_P28       = fs->make<TH1F>("GLB_ResInvPt_Phi_P28",   "GLB - Resolution Vs  +2.8 < Phi < +3.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_GLB_P32       = fs->make<TH1F>("GLB_ResInvPt_Phi_P32",   "GLB - Resolution Vs  +3.2 < Phi < +3.6",   1200,  -0.005,  +0.005);

  ResInvPt_Phi_StdA_M36      = fs->make<TH1F>("StdA_ResInvPt_Phi_M36", "StdA - Resolution Vs  -3.6 < Phi < -3.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M32      = fs->make<TH1F>("StdA_ResInvPt_Phi_M32", "StdA - Resolution Vs  -3.2 < Phi < -2.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M28      = fs->make<TH1F>("StdA_ResInvPt_Phi_M28", "StdA - Resolution Vs  -2.8 < Phi < -2.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M24      = fs->make<TH1F>("StdA_ResInvPt_Phi_M24", "StdA - Resolution Vs  -2.4 < Phi < -2.0",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M20      = fs->make<TH1F>("StdA_ResInvPt_Phi_M20", "StdA - Resolution Vs  -2.0 < Phi < -1.6",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M16      = fs->make<TH1F>("StdA_ResInvPt_Phi_M16", "StdA - Resolution Vs  -1.6 < Phi < -1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M12      = fs->make<TH1F>("StdA_ResInvPt_Phi_M12", "StdA - Resolution Vs  -1.2 < Phi < -0.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M08      = fs->make<TH1F>("StdA_ResInvPt_Phi_M08", "StdA - Resolution Vs  -0.8 < Phi < -0.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M04      = fs->make<TH1F>("StdA_ResInvPt_Phi_M04", "StdA - Resolution Vs  -0.4 < Phi < -0",     1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_M0       = fs->make<TH1F>("StdA_ResInvPt_Phi_M0",  "StdA - Resolution Vs     0 < Phi < +0.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_P04      = fs->make<TH1F>("StdA_ResInvPt_Phi_P04", "StdA - Resolution Vs  +0.4 < Phi < +0.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_P08      = fs->make<TH1F>("StdA_ResInvPt_Phi_P08", "StdA - Resolution Vs  +0.8 < Phi < +1.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_P12      = fs->make<TH1F>("StdA_ResInvPt_Phi_P12", "StdA - Resolution Vs  +1.2 < Phi < +1.6",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_P16      = fs->make<TH1F>("StdA_ResInvPt_Phi_P16", "StdA - Resolution Vs  +1.6 < Phi < +2.0",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_P20      = fs->make<TH1F>("StdA_ResInvPt_Phi_P20", "StdA - Resolution Vs  +2.0 < Phi < +2.4",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_P24      = fs->make<TH1F>("StdA_ResInvPt_Phi_P24", "StdA - Resolution Vs  +2.4 < Phi < +2.8",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_P28      = fs->make<TH1F>("StdA_ResInvPt_Phi_P28", "StdA - Resolution Vs  +2.8 < Phi < +3.2",   1200,  -0.005,  +0.005);
  ResInvPt_Phi_StdA_P32      = fs->make<TH1F>("StdA_ResInvPt_Phi_P32", "StdA - Resolution Vs  +3.2 < Phi < +3.6",   1200,  -0.005,  +0.005);

  //Resolution of Pt
  ResPt_Eta_DYT_M24  = fs->make<TH1F>("DYT_ResPt_Eta_M24",    "DYT - Resolution Vs -2.4 < Eta < -2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_M21  = fs->make<TH1F>("DYT_ResPt_Eta_M21",    "DYT - Resolution Vs -2.1 < Eta < -1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_M18  = fs->make<TH1F>("DYT_ResPt_Eta_M18",    "DYT - Resolution Vs -1.8 < Eta < -1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_M15  = fs->make<TH1F>("DYT_ResPt_Eta_M15",    "DYT - Resolution Vs -1.5 < Eta < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_M12  = fs->make<TH1F>("DYT_ResPt_Eta_M12",    "DYT - Resolution Vs -1.2 < Eta < -0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_M09  = fs->make<TH1F>("DYT_ResPt_Eta_M09",    "DYT - Resolution Vs -0.9 < Eta < -0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_M06  = fs->make<TH1F>("DYT_ResPt_Eta_M06",    "DYT - Resolution Vs -0.6 < Eta < -0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_M03  = fs->make<TH1F>("DYT_ResPt_Eta_M03",    "DYT - Resolution Vs -0.3 < Eta <  0",     2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_M0   = fs->make<TH1F>("DYT_ResPt_Eta_M0",     "DYT - Resolution Vs    0 < Eta < +0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_P03  = fs->make<TH1F>("DYT_ResPt_Eta_P03",    "DYT - Resolution Vs +0.3 < Eta < +0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_P06  = fs->make<TH1F>("DYT_ResPt_Eta_P06",    "DYT - Resolution Vs +0.6 < Eta < +0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_P09  = fs->make<TH1F>("DYT_ResPt_Eta_P09",    "DYT - Resolution Vs +0.9 < Eta < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_P12  = fs->make<TH1F>("DYT_ResPt_Eta_P12",    "DYT - Resolution Vs +1.2 < Eta < +1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_P15  = fs->make<TH1F>("DYT_ResPt_Eta_P15",    "DYT - Resolution Vs +1.5 < Eta < +1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_P18  = fs->make<TH1F>("DYT_ResPt_Eta_P21",    "DYT - Resolution Vs +1.8 < Eta < +2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_DYT_P21  = fs->make<TH1F>("DYT_ResPt_Eta_P24",    "DYT - Resolution Vs +2.1 < Eta < +2.4",   2000,  -10.005,  +10.005);

  ResPt_Eta_TuneP_M24  = fs->make<TH1F>("TuneP_ResPt_Eta_M24",  "TuneP - Resolution Vs -2.4 < Eta < -2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_M21  = fs->make<TH1F>("TuneP_ResPt_Eta_M21",  "TuneP - Resolution Vs -2.1 < Eta < -1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_M18  = fs->make<TH1F>("TuneP_ResPt_Eta_M18",  "TuneP - Resolution Vs -1.8 < Eta < -1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_M15  = fs->make<TH1F>("TuneP_ResPt_Eta_M15",  "TuneP - Resolution Vs -1.5 < Eta < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_M12  = fs->make<TH1F>("TuneP_ResPt_Eta_M12",  "TuneP - Resolution Vs -1.2 < Eta < -0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_M09  = fs->make<TH1F>("TuneP_ResPt_Eta_M09",  "TuneP - Resolution Vs -0.9 < Eta < -0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_M06  = fs->make<TH1F>("TuneP_ResPt_Eta_M06",  "TuneP - Resolution Vs -0.6 < Eta < -0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_M03  = fs->make<TH1F>("TuneP_ResPt_Eta_M03",  "TuneP - Resolution Vs -0.3 < Eta <  0",     2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_M0   = fs->make<TH1F>("TuneP_ResPt_Eta_M0",   "TuneP - Resolution Vs    0 < Eta < +0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_P03  = fs->make<TH1F>("TuneP_ResPt_Eta_P03",  "TuneP - Resolution Vs +0.3 < Eta < +0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_P06  = fs->make<TH1F>("TuneP_ResPt_Eta_P06",  "TuneP - Resolution Vs +0.6 < Eta < +0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_P09  = fs->make<TH1F>("TuneP_ResPt_Eta_P09",  "TuneP - Resolution Vs +0.9 < Eta < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_P12  = fs->make<TH1F>("TuneP_ResPt_Eta_P12",  "TuneP - Resolution Vs +1.2 < Eta < +1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_P15  = fs->make<TH1F>("TuneP_ResPt_Eta_P15",  "TuneP - Resolution Vs +1.5 < Eta < +1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_P18  = fs->make<TH1F>("TuneP_ResPt_Eta_P21",  "TuneP - Resolution Vs +1.8 < Eta < +2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_TuneP_P21  = fs->make<TH1F>("TuneP_ResPt_Eta_P24",  "TuneP - Resolution Vs +2.1 < Eta < +2.4",   2000,  -10.005,  +10.005);

  ResPt_Eta_Picky_M24  = fs->make<TH1F>("Picky_ResPt_Eta_M24",  "Picky - Resolution Vs -2.4 < Eta < -2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_M21  = fs->make<TH1F>("Picky_ResPt_Eta_M21",  "Picky - Resolution Vs -2.1 < Eta < -1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_M18  = fs->make<TH1F>("Picky_ResPt_Eta_M18",  "Picky - Resolution Vs -1.8 < Eta < -1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_M15  = fs->make<TH1F>("Picky_ResPt_Eta_M15",  "Picky - Resolution Vs -1.5 < Eta < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_M12  = fs->make<TH1F>("Picky_ResPt_Eta_M12",  "Picky - Resolution Vs -1.2 < Eta < -0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_M09  = fs->make<TH1F>("Picky_ResPt_Eta_M09",  "Picky - Resolution Vs -0.9 < Eta < -0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_M06  = fs->make<TH1F>("Picky_ResPt_Eta_M06",  "Picky - Resolution Vs -0.6 < Eta < -0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_M03  = fs->make<TH1F>("Picky_ResPt_Eta_M03",  "Picky - Resolution Vs -0.3 < Eta <  0",     2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_M0   = fs->make<TH1F>("Picky_ResPt_Eta_M0",   "Picky - Resolution Vs    0 < Eta < +0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_P03  = fs->make<TH1F>("Picky_ResPt_Eta_P03",  "Picky - Resolution Vs +0.3 < Eta < +0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_P06  = fs->make<TH1F>("Picky_ResPt_Eta_P06",  "Picky - Resolution Vs +0.6 < Eta < +0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_P09  = fs->make<TH1F>("Picky_ResPt_Eta_P09",  "Picky - Resolution Vs +0.9 < Eta < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_P12  = fs->make<TH1F>("Picky_ResPt_Eta_P12",  "Picky - Resolution Vs +1.2 < Eta < +1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_P15  = fs->make<TH1F>("Picky_ResPt_Eta_P15",  "Picky - Resolution Vs +1.5 < Eta < +1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_P18  = fs->make<TH1F>("Picky_ResPt_Eta_P18",  "Picky - Resolution Vs +1.8 < Eta < +2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_Picky_P21  = fs->make<TH1F>("Picky_ResPt_Eta_P21",  "Picky - Resolution Vs +2.1 < Eta < +2.4",   2000,  -10.005,  +10.005);

  ResPt_Eta_GLB_M24    = fs->make<TH1F>("GLB_ResPt_Eta_M24",    "GLB - Resolution Vs -2.4 < Eta < -2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_M21    = fs->make<TH1F>("GLB_ResPt_Eta_M21",    "GLB - Resolution Vs -2.1 < Eta < -1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_M18    = fs->make<TH1F>("GLB_ResPt_Eta_M18",    "GLB - Resolution Vs -1.8 < Eta < -1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_M15    = fs->make<TH1F>("GLB_ResPt_Eta_M15",    "GLB - Resolution Vs -1.5 < Eta < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_M12    = fs->make<TH1F>("GLB_ResPt_Eta_M12",    "GLB - Resolution Vs -1.2 < Eta < -0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_M09    = fs->make<TH1F>("GLB_ResPt_Eta_M09",    "GLB - Resolution Vs -0.9 < Eta < -0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_M06    = fs->make<TH1F>("GLB_ResPt_Eta_M06",    "GLB - Resolution Vs -0.6 < Eta < -0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_M03    = fs->make<TH1F>("GLB_ResPt_Eta_M03",    "GLB - Resolution Vs -0.3 < Eta <  0",     2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_M0     = fs->make<TH1F>("GLB_ResPt_Eta_M0",     "GLB - Resolution Vs    0 < Eta < +0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_P03    = fs->make<TH1F>("GLB_ResPt_Eta_P03",    "GLB - Resolution Vs +0.3 < Eta < +0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_P06    = fs->make<TH1F>("GLB_ResPt_Eta_P06",    "GLB - Resolution Vs +0.6 < Eta < +0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_P09    = fs->make<TH1F>("GLB_ResPt_Eta_P09",    "GLB - Resolution Vs +0.9 < Eta < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_P12    = fs->make<TH1F>("GLB_ResPt_Eta_P12",    "GLB - Resolution Vs +1.2 < Eta < +1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_P15    = fs->make<TH1F>("GLB_ResPt_Eta_P15",    "GLB - Resolution Vs +1.5 < Eta < +1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_P18    = fs->make<TH1F>("GLB_ResPt_Eta_P18",    "GLB - Resolution Vs +1.8 < Eta < +2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_GLB_P21    = fs->make<TH1F>("GLB_ResPt_Eta_P21",    "GLB - Resolution Vs +2.1 < Eta < +2.4",   2000,  -10.005,  +10.005);

  ResPt_Eta_StdA_M24    = fs->make<TH1F>("StdA_ResPt_Eta_M24",  "StdA - Resolution Vs -2.4 < Eta < -2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_M21    = fs->make<TH1F>("StdA_ResPt_Eta_M21",  "StdA - Resolution Vs -2.1 < Eta < -1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_M18    = fs->make<TH1F>("StdA_ResPt_Eta_M18",  "StdA - Resolution Vs -1.8 < Eta < -1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_M15    = fs->make<TH1F>("StdA_ResPt_Eta_M15",  "StdA - Resolution Vs -1.5 < Eta < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_M12    = fs->make<TH1F>("StdA_ResPt_Eta_M12",  "StdA - Resolution Vs -1.2 < Eta < -0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_M09    = fs->make<TH1F>("StdA_ResPt_Eta_M09",  "StdA - Resolution Vs -0.9 < Eta < -0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_M06    = fs->make<TH1F>("StdA_ResPt_Eta_M06",  "StdA - Resolution Vs -0.6 < Eta < -0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_M03    = fs->make<TH1F>("StdA_ResPt_Eta_M03",  "StdA - Resolution Vs -0.3 < Eta <  0",     2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_M0     = fs->make<TH1F>("StdA_ResPt_Eta_M0",   "StdA - Resolution Vs    0 < Eta < +0.3",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_P03    = fs->make<TH1F>("StdA_ResPt_Eta_P03",  "StdA - Resolution Vs +0.3 < Eta < +0.6",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_P06    = fs->make<TH1F>("StdA_ResPt_Eta_P06",  "StdA - Resolution Vs +0.6 < Eta < +0.9",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_P09    = fs->make<TH1F>("StdA_ResPt_Eta_P09",  "StdA - Resolution Vs +0.9 < Eta < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_P12    = fs->make<TH1F>("StdA_ResPt_Eta_P12",  "StdA - Resolution Vs +1.2 < Eta < +1.5",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_P15    = fs->make<TH1F>("StdA_ResPt_Eta_P15",  "StdA - Resolution Vs +1.5 < Eta < +1.8",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_P18    = fs->make<TH1F>("StdA_ResPt_Eta_P18",  "StdA - Resolution Vs +1.8 < Eta < +2.1",   2000,  -10.005,  +10.005);
  ResPt_Eta_StdA_P21    = fs->make<TH1F>("StdA_ResPt_Eta_P21",  "StdA - Resolution Vs +2.1 < Eta < +2.4",   2000,  -10.005,  +10.005);

  //Resolution Pt Vs Phi
  ResPt_Phi_DYT_M36       = fs->make<TH1F>("DYT_ResPt_Phi_M36",  "DYT - Resolution Vs  -3.6 < Phi < -3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M32       = fs->make<TH1F>("DYT_ResPt_Phi_M32",  "DYT - Resolution Vs  -3.2 < Phi < -2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M28       = fs->make<TH1F>("DYT_ResPt_Phi_M28",  "DYT - Resolution Vs  -2.8 < Phi < -2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M24       = fs->make<TH1F>("DYT_ResPt_Phi_M24",  "DYT - Resolution Vs  -2.4 < Phi < -2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M20       = fs->make<TH1F>("DYT_ResPt_Phi_M20",  "DYT - Resolution Vs  -2.0 < Phi < -1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M16       = fs->make<TH1F>("DYT_ResPt_Phi_M16",  "DYT - Resolution Vs  -1.6 < Phi < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M12       = fs->make<TH1F>("DYT_ResPt_Phi_M12",  "DYT - Resolution Vs  -1.2 < Phi < -0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M08       = fs->make<TH1F>("DYT_ResPt_Phi_M08",  "DYT - Resolution Vs  -0.8 < Phi < -0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M04       = fs->make<TH1F>("DYT_ResPt_Phi_M04",  "DYT - Resolution Vs  -0.4 < Phi < -0",     2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_M0        = fs->make<TH1F>("DYT_ResPt_Phi_M0",   "DYT - Resolution Vs     0 < Phi < +0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_P04       = fs->make<TH1F>("DYT_ResPt_Phi_P04",  "DYT - Resolution Vs  +0.4 < Phi < +0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_P08       = fs->make<TH1F>("DYT_ResPt_Phi_P08",  "DYT - Resolution Vs  +0.8 < Phi < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_P12       = fs->make<TH1F>("DYT_ResPt_Phi_P12",  "DYT - Resolution Vs  +1.2 < Phi < +1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_P16       = fs->make<TH1F>("DYT_ResPt_Phi_P16",  "DYT - Resolution Vs  +1.6 < Phi < +2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_P20       = fs->make<TH1F>("DYT_ResPt_Phi_P20",  "DYT - Resolution Vs  +2.0 < Phi < +2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_P24       = fs->make<TH1F>("DYT_ResPt_Phi_P24",  "DYT - Resolution Vs  +2.4 < Phi < +2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_P28       = fs->make<TH1F>("DYT_ResPt_Phi_P28",  "DYT - Resolution Vs  +2.8 < Phi < +3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_DYT_P32       = fs->make<TH1F>("DYT_ResPt_Phi_P32",  "DYT - Resolution Vs  +3.2 < Phi < +3.6",   2000,  -10.005,  +10.005);

  ResPt_Phi_TuneP_M36     = fs->make<TH1F>("TuneP_ResPt_Phi_M36", "TuneP - Resolution Vs  -3.6 < Phi < -3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M32     = fs->make<TH1F>("TuneP_ResPt_Phi_M32", "TuneP - Resolution Vs  -3.2 < Phi < -2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M28     = fs->make<TH1F>("TuneP_ResPt_Phi_M28", "TuneP - Resolution Vs  -2.8 < Phi < -2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M24     = fs->make<TH1F>("TuneP_ResPt_Phi_M24", "TuneP - Resolution Vs  -2.4 < Phi < -2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M20     = fs->make<TH1F>("TuneP_ResPt_Phi_M20", "TuneP - Resolution Vs  -2.0 < Phi < -1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M16     = fs->make<TH1F>("TuneP_ResPt_Phi_M16", "TuneP - Resolution Vs  -1.6 < Phi < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M12     = fs->make<TH1F>("TuneP_ResPt_Phi_M12", "TuneP - Resolution Vs  -1.2 < Phi < -0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M08     = fs->make<TH1F>("TuneP_ResPt_Phi_M08", "TuneP - Resolution Vs  -0.8 < Phi < -0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M04     = fs->make<TH1F>("TuneP_ResPt_Phi_M04", "TuneP - Resolution Vs  -0.4 < Phi < -0",     2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_M0      = fs->make<TH1F>("TuneP_ResPt_Phi_M0",  "TuneP - Resolution Vs     0 < Phi < +0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_P04     = fs->make<TH1F>("TuneP_ResPt_Phi_P04", "TuneP - Resolution Vs  +0.4 < Phi < +0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_P08     = fs->make<TH1F>("TuneP_ResPt_Phi_P08", "TuneP - Resolution Vs  +0.8 < Phi < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_P12     = fs->make<TH1F>("TuneP_ResPt_Phi_P12", "TuneP - Resolution Vs  +1.2 < Phi < +1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_P16     = fs->make<TH1F>("TuneP_ResPt_Phi_P16", "TuneP - Resolution Vs  +1.6 < Phi < +2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_P20     = fs->make<TH1F>("TuneP_ResPt_Phi_P20", "TuneP - Resolution Vs  +2.0 < Phi < +2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_P24     = fs->make<TH1F>("TuneP_ResPt_Phi_P24", "TuneP - Resolution Vs  +2.4 < Phi < +2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_P28     = fs->make<TH1F>("TuneP_ResPt_Phi_P28", "TuneP - Resolution Vs  +2.8 < Phi < +3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_TuneP_P32     = fs->make<TH1F>("TuneP_ResPt_Phi_P32", "TuneP - Resolution Vs  +3.2 < Phi < +3.6",   2000,  -10.005,  +10.005);

  ResPt_Phi_Picky_M36     = fs->make<TH1F>("Picky_ResPt_Phi_M36",  "Picky - Resolution Vs  -3.6 < Phi < -3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M32     = fs->make<TH1F>("Picky_ResPt_Phi_M32",  "Picky - Resolution Vs  -3.2 < Phi < -2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M28     = fs->make<TH1F>("Picky_ResPt_Phi_M28",  "Picky - Resolution Vs  -2.8 < Phi < -2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M24     = fs->make<TH1F>("Picky_ResPt_Phi_M24",  "Picky - Resolution Vs  -2.4 < Phi < -2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M20     = fs->make<TH1F>("Picky_ResPt_Phi_M20",  "Picky - Resolution Vs  -2.0 < Phi < -1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M16     = fs->make<TH1F>("Picky_ResPt_Phi_M16",  "Picky - Resolution Vs  -1.6 < Phi < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M12     = fs->make<TH1F>("Picky_ResPt_Phi_M12",  "Picky - Resolution Vs  -1.2 < Phi < -0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M08     = fs->make<TH1F>("Picky_ResPt_Phi_M08",  "Picky - Resolution Vs  -0.8 < Phi < -0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M04     = fs->make<TH1F>("Picky_ResPt_Phi_M04",  "Picky - Resolution Vs  -0.4 < Phi < -0",     2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_M0      = fs->make<TH1F>("Picky_ResPt_Phi_M0",   "Picky - Resolution Vs     0 < Phi < +0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_P04     = fs->make<TH1F>("Picky_ResPt_Phi_P04",  "Picky - Resolution Vs  +0.4 < Phi < +0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_P08     = fs->make<TH1F>("Picky_ResPt_Phi_P08",  "Picky - Resolution Vs  +0.8 < Phi < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_P12     = fs->make<TH1F>("Picky_ResPt_Phi_P12",  "Picky - Resolution Vs  +1.2 < Phi < +1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_P16     = fs->make<TH1F>("Picky_ResPt_Phi_P16",  "Picky - Resolution Vs  +1.6 < Phi < +2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_P20     = fs->make<TH1F>("Picky_ResPt_Phi_P20",  "Picky - Resolution Vs  +2.0 < Phi < +2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_P24     = fs->make<TH1F>("Picky_ResPt_Phi_P24",  "Picky - Resolution Vs  +2.4 < Phi < +2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_P28     = fs->make<TH1F>("Picky_ResPt_Phi_P28",  "Picky - Resolution Vs  +2.8 < Phi < +3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_Picky_P32     = fs->make<TH1F>("Picky_ResPt_Phi_P32",  "Picky - Resolution Vs  +3.2 < Phi < +3.6",   2000,  -10.005,  +10.005);

  ResPt_Phi_GLB_M36       = fs->make<TH1F>("GLB_ResPt_Phi_M36",  "GLB - Resolution Vs  -3.6 < Phi < -3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M32       = fs->make<TH1F>("GLB_ResPt_Phi_M32",  "GLB - Resolution Vs  -3.2 < Phi < -2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M28       = fs->make<TH1F>("GLB_ResPt_Phi_M28",  "GLB - Resolution Vs  -2.8 < Phi < -2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M24       = fs->make<TH1F>("GLB_ResPt_Phi_M24",  "GLB - Resolution Vs  -2.4 < Phi < -2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M20       = fs->make<TH1F>("GLB_ResPt_Phi_M20",  "GLB - Resolution Vs  -2.0 < Phi < -1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M16       = fs->make<TH1F>("GLB_ResPt_Phi_M16",  "GLB - Resolution Vs  -1.6 < Phi < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M12       = fs->make<TH1F>("GLB_ResPt_Phi_M12",  "GLB - Resolution Vs  -1.2 < Phi < -0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M08       = fs->make<TH1F>("GLB_ResPt_Phi_M08",  "GLB - Resolution Vs  -0.8 < Phi < -0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M04       = fs->make<TH1F>("GLB_ResPt_Phi_M04",  "GLB - Resolution Vs  -0.4 < Phi < -0",     2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_M0        = fs->make<TH1F>("GLB_ResPt_Phi_M0",   "GLB - Resolution Vs     0 < Phi < +0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_P04       = fs->make<TH1F>("GLB_ResPt_Phi_P04",  "GLB - Resolution Vs  +0.4 < Phi < +0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_P08       = fs->make<TH1F>("GLB_ResPt_Phi_P08",  "GLB - Resolution Vs  +0.8 < Phi < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_P12       = fs->make<TH1F>("GLB_ResPt_Phi_P12",  "GLB - Resolution Vs  +1.2 < Phi < +1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_P16       = fs->make<TH1F>("GLB_ResPt_Phi_P16",  "GLB - Resolution Vs  +1.6 < Phi < +2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_P20       = fs->make<TH1F>("GLB_ResPt_Phi_P20",  "GLB - Resolution Vs  +2.0 < Phi < +2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_P24       = fs->make<TH1F>("GLB_ResPt_Phi_P24",  "GLB - Resolution Vs  +2.4 < Phi < +2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_P28       = fs->make<TH1F>("GLB_ResPt_Phi_P28",  "GLB - Resolution Vs  +2.8 < Phi < +3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_GLB_P32       = fs->make<TH1F>("GLB_ResPt_Phi_P32",  "GLB - Resolution Vs  +3.2 < Phi < +3.6",   2000,  -10.005,  +10.005);

  ResPt_Phi_StdA_M36      = fs->make<TH1F>("StdA_ResPt_Phi_M36",  "StdA - Resolution Vs  -3.6 < Phi < -3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M32      = fs->make<TH1F>("StdA_ResPt_Phi_M32",  "StdA - Resolution Vs  -3.2 < Phi < -2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M28      = fs->make<TH1F>("StdA_ResPt_Phi_M28",  "StdA - Resolution Vs  -2.8 < Phi < -2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M24      = fs->make<TH1F>("StdA_ResPt_Phi_M24",  "StdA - Resolution Vs  -2.4 < Phi < -2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M20      = fs->make<TH1F>("StdA_ResPt_Phi_M20",  "StdA - Resolution Vs  -2.0 < Phi < -1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M16      = fs->make<TH1F>("StdA_ResPt_Phi_M16",  "StdA - Resolution Vs  -1.6 < Phi < -1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M12      = fs->make<TH1F>("StdA_ResPt_Phi_M12",  "StdA - Resolution Vs  -1.2 < Phi < -0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M08      = fs->make<TH1F>("StdA_ResPt_Phi_M08",  "StdA - Resolution Vs  -0.8 < Phi < -0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M04      = fs->make<TH1F>("StdA_ResPt_Phi_M04",  "StdA - Resolution Vs  -0.4 < Phi < -0",     2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_M0       = fs->make<TH1F>("StdA_ResPt_Phi_M0",   "StdA - Resolution Vs     0 < Phi < +0.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_P04      = fs->make<TH1F>("StdA_ResPt_Phi_P04",  "StdA - Resolution Vs  +0.4 < Phi < +0.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_P08      = fs->make<TH1F>("StdA_ResPt_Phi_P08",  "StdA - Resolution Vs  +0.8 < Phi < +1.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_P12      = fs->make<TH1F>("StdA_ResPt_Phi_P12",  "StdA - Resolution Vs  +1.2 < Phi < +1.6",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_P16      = fs->make<TH1F>("StdA_ResPt_Phi_P16",  "StdA - Resolution Vs  +1.6 < Phi < +2.0",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_P20      = fs->make<TH1F>("StdA_ResPt_Phi_P20",  "StdA - Resolution Vs  +2.0 < Phi < +2.4",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_P24      = fs->make<TH1F>("StdA_ResPt_Phi_P24",  "StdA - Resolution Vs  +2.4 < Phi < +2.8",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_P28      = fs->make<TH1F>("StdA_ResPt_Phi_P28",  "StdA - Resolution Vs  +2.8 < Phi < +3.2",   2000,  -10.005,  +10.005);
  ResPt_Phi_StdA_P32      = fs->make<TH1F>("StdA_ResPt_Phi_P32",  "StdA - Resolution Vs  +3.2 < Phi < +3.6",   2000,  -10.005,  +10.005);

  //Resolution Inv P
  DYT_Res_Invp       = fs->make<TH1F>("DYT_Res_InvP"   , "DYT - Res_P"     , 1200,  -0.6,  0.6);
  DYT_Res_InvpB      = fs->make<TH1F>("DYT_Res_InvPB"  , "DYT - Res_P"     , 1200,  -0.6,  0.6);
  DYT_Res_InvpE      = fs->make<TH1F>("DYT_Res_InvPE"  , "DYT - Res_P"     , 1200,  -0.6,  0.6);

  TuneP_Res_Invp     = fs->make<TH1F>("TuneP_Res_InvP" , "TuneP - Res_P"   , 1200,  -0.6,  0.6);
  TuneP_Res_InvpB    = fs->make<TH1F>("TuneP_Res_InvPB", "TuneP - Res_P"   , 1200,  -0.6,  0.6);
  TuneP_Res_InvpE    = fs->make<TH1F>("TuneP_Res_InvPE", "TuneP - Res_P"   , 1200,  -0.6,  0.6);

  Picky_Res_Invp     = fs->make<TH1F>("Picky_Res_InvP" , "Picky - Res_P"   , 1200,  -0.6,  0.6);
  Picky_Res_InvpB    = fs->make<TH1F>("Picky_Res_InvPB", "Picky - Res_P"   , 1200,  -0.6,  0.6);
  Picky_Res_InvpE    = fs->make<TH1F>("Picky_Res_InvPE", "Picky - Res_P"   , 1200,  -0.6,  0.6);

  GLB_Res_Invp       = fs->make<TH1F>("GLB_Res_InvP"   , "GLB - Res_P"     , 1200,  -0.6,  0.6);
  GLB_Res_InvpB      = fs->make<TH1F>("GLB_Res_InvPB"  , "GLB - Res_P"     , 1200,  -0.6,  0.6);
  GLB_Res_InvpE      = fs->make<TH1F>("GLB_Res_InvPE"  , "GLB - Res_P"     , 1200,  -0.6,  0.6);

  StdA_Res_Invp      = fs->make<TH1F>("StdA_Res_InvP"  , "StdA - Res_P"    , 1200,  -0.6,  0.6);
  StdA_Res_InvpB     = fs->make<TH1F>("StdA_Res_InvPB" , "StdA - Res_P"    , 1200,  -0.6,  0.6);
  StdA_Res_InvpE     = fs->make<TH1F>("StdA_Res_InvPE" , "StdA - Res_P"    , 1200,  -0.6,  0.6);

  //Pull q/p
  DYT_Pull_Invp       = fs->make<TH1F>("DYT_Pull_InvP"   , "DYT - Pull_p"     , 1000,  -10,  10);
  DYT_Pull_InvpB      = fs->make<TH1F>("DYT_Pull_InvPB"  , "DYT - Pull_p"     , 1000,  -10,  10);
  DYT_Pull_InvpE      = fs->make<TH1F>("DYT_Pull_InvPE"  , "DYT - Pull_p"     , 1000,  -10,  10);

  TuneP_Pull_Invp     = fs->make<TH1F>("TuneP_Pull_InvP",  "TuneP - Pull_p"   , 1000,  -10,  10);
  TuneP_Pull_InvpB    = fs->make<TH1F>("TuneP_Pull_InvPB", "TuneP - Pull_p"   , 1000,  -10,  10);
  TuneP_Pull_InvpE    = fs->make<TH1F>("TuneP_Pull_InvPE", "TuneP - Pull_p"   , 1000,  -10,  10);

  Picky_Pull_Invp     = fs->make<TH1F>("Picky_Pull_InvP" , "Picky - Pull_P"   , 1000,  -10,  10);
  Picky_Pull_InvpB    = fs->make<TH1F>("Picky_Pull_InvPB", "Picky - Pull_P"   , 1000,  -10,  10);
  Picky_Pull_InvpE    = fs->make<TH1F>("Picky_Pull_InvPE", "Picky - Pull_P"   , 1000,  -10,  10);

  GLB_Pull_Invp       = fs->make<TH1F>("GLB_Pull_InvPP"   , "GLB - Pull_P"     , 1000,  -10,  10);
  GLB_Pull_InvpB      = fs->make<TH1F>("GLB_Pull_InvPtB"  , "GLB - Pull_P"     , 1000,  -10,  10);
  GLB_Pull_InvpE      = fs->make<TH1F>("GLB_Pull_InvPtE"  , "GLB - Pull_P"     , 1000,  -10,  10);

  StdA_Pull_Invp      = fs->make<TH1F>("StdA_Pull_InvP"  , "StdA - Pull_P"    , 1000,  -10,  10);
  StdA_Pull_InvpB     = fs->make<TH1F>("StdA_Pull_InvPB" , "StdA - Pull_P"    , 1000,  -10,  10);
  StdA_Pull_InvpE     = fs->make<TH1F>("StdA_Pull_InvPE" , "StdA - Pull_P"    , 1000,  -10,  10);

  //Sigma(q/pt)
  DYT_SqP     = fs->make<TH1F>("DYT_SqP",  "DYT - #sigma(q/P)" ,  1000, 0, 0.0005);
  DYT_SqPB    = fs->make<TH1F>("DYT_SqPB", "DYT - #sigma(q/P)" ,  1000, 0, 0.0005);
  DYT_SqPE    = fs->make<TH1F>("DYT_SqPE", "DYT - #sigma(q/P)" ,  1000, 0, 0.0005);

  TuneP_SqP   = fs->make<TH1F>("TuneP_SqP",  "TuneP - #sigma(q/P)",  1000, 0, 0.0005);
  TuneP_SqPB  = fs->make<TH1F>("TuneP_SqPB", "TuneP - #sigma(q/P)",  1000, 0, 0.0005);
  TuneP_SqPE  = fs->make<TH1F>("TuneP_SqPE", "TuneP - #sigma(q/P)",  1000, 0, 0.0005);

  Picky_SqP   = fs->make<TH1F>("Picky_SqP",   "Picky - #sigma(q/P)",  1000, 0, 0.0005);
  Picky_SqPB  = fs->make<TH1F>("Picky_SqPB",  "Picky - #sigma(q/P)",  1000, 0, 0.0005);
  Picky_SqPE  = fs->make<TH1F>("Picky_SqPE",  "Picky - #sigma(q/P)",  1000, 0, 0.0005);

  GLB_SqP     = fs->make<TH1F>("GLB_SqP",   "GLB - #sigma(q/P)",   1000, 0, 0.0005);
  GLB_SqPB    = fs->make<TH1F>("GLB_SqPB",  "GLB - #sigma(q/P)",   1000, 0, 0.0005);
  GLB_SqPE    = fs->make<TH1F>("GLB_SqPE",  "GLB - #sigma(q/P)",   1000, 0, 0.0005);

  StdA_SqP    = fs->make<TH1F>("StdA_SqP",   "StdA - #sigma(q/P)",  1000, 0, 0.0005);
  StdA_SqPB   = fs->make<TH1F>("StdA_SqPB",  "StdA - #sigma(q/P)",  1000, 0, 0.0005);
  StdA_SqPE   = fs->make<TH1F>("StdA_SqPE",  "StdA - #sigma(q/P)",  1000, 0, 0.0005);

  //Sigma(q/pt)
  DYT_SqInvPt     = fs->make<TH1F>("DYT_SqInvPt",  "DYT - #sigma(q/Pt)" ,  1000, 0, 0.5);
  DYT_SqInvPtB    = fs->make<TH1F>("DYT_SqInvPtB", "DYT - #sigma(q/Pt)" ,  1000, 0, 0.5);
  DYT_SqInvPtE    = fs->make<TH1F>("DYT_SqInvPtE", "DYT - #sigma(q/Pt)" ,  1000, 0, 0.5);

  TuneP_SqInvPt   = fs->make<TH1F>("TuneP_SqInvPt",  "TuneP - #sigma(q/Pt)",  1000, 0, 0.5);
  TuneP_SqInvPtB  = fs->make<TH1F>("TuneP_SqInvPtB", "TuneP - #sigma(q/Pt)",  1000, 0, 0.5);
  TuneP_SqInvPtE  = fs->make<TH1F>("TuneP_SqInvPtE", "TuneP - #sigma(q/Pt)",  1000, 0, 0.5);

  Picky_SqInvPt   = fs->make<TH1F>("Picky_SqInvPt",   "Picky - #sigma(q/Pt)",  1000, 0, 0.5);
  Picky_SqInvPtB  = fs->make<TH1F>("Picky_SqInvPtB",  "Picky - #sigma(q/Pt)",  1000, 0, 0.5);
  Picky_SqInvPtE  = fs->make<TH1F>("Picky_SqInvPtE",  "Picky - #sigma(q/Pt)",  1000, 0, 0.5);

  GLB_SqInvPt     = fs->make<TH1F>("GLB_SqInvPt",   "GLB - #sigma(q/Pt)",   1000, 0, 0.5);
  GLB_SqInvPtB    = fs->make<TH1F>("GLB_SqInvPtB",  "GLB - #sigma(q/Pt)",   1000, 0, 0.5);
  GLB_SqInvPtE    = fs->make<TH1F>("GLB_SqInvPtE",  "GLB - #sigma(q/Pt)",   1000, 0, 0.5);

  StdA_SqInvPt    = fs->make<TH1F>("StdA_SqInvPt",   "StdA - #sigma(q/Pt)",  1000, 0, 0.5);
  StdA_SqInvPtB   = fs->make<TH1F>("StdA_SqInvPtB",  "StdA - #sigma(q/Pt)",  1000, 0, 0.5);
  StdA_SqInvPtE   = fs->make<TH1F>("StdA_SqInvPtE",  "StdA - #sigma(q/Pt)",  1000, 0, 0.5);

  //Sigma(pt)/pt
  DYT_SPtOverPt   = fs->make<TH1F>("DYT_SPtOverPt",   "DYT - #sigma(Pt)/Pt", 1000, 0,  0.5);
  DYT_SPtOverPtB  = fs->make<TH1F>("DYT_SPtOverPtB",  "DYT - #sigma(Pt)/Pt", 1000, 0,  0.5);
  DYT_SPtOverPtE  = fs->make<TH1F>("DYT_SPtOverPtE",  "DYT - #sigma(Pt)/Pt", 1000, 0,  0.5);

  TuneP_SPtOverPt  = fs->make<TH1F>("TuneP_SPtOverPt",  "TuneP - #sigma(Pt)/Pt",  1000, 0, 0.5);
  TuneP_SPtOverPtB = fs->make<TH1F>("TuneP_SPtOverPtB", "TuneP - #sigma(Pt)/Pt",  1000, 0, 0.5);
  TuneP_SPtOverPtE = fs->make<TH1F>("TuneP_SPtOverPtE", "TuneP - #sigma(Pt)/Pt",  1000, 0, 0.5);

  Picky_SPtOverPt   = fs->make<TH1F>("Picky_SPtOverPt",   "Picky - #sigma(Pt)/Pt",  1000, 0, 0.5);
  Picky_SPtOverPtB  = fs->make<TH1F>("Picky_SPtOverPtB",  "Picky - #sigma(Pt)/Pt",  1000, 0, 0.5);
  Picky_SPtOverPtE  = fs->make<TH1F>("Picky_SPtOverPtE",  "Picky - #sigma(Pt)/Pt",  1000, 0, 0.5);

  GLB_SPtOverPt   = fs->make<TH1F>("GLB_SPtOverPt",   "GLB - #sigma(Pt)/Pt",  1000, 0, 0.5);
  GLB_SPtOverPtB  = fs->make<TH1F>("GLB_SPtOverPtB",  "GLB - #sigma(Pt)/Pt",  1000, 0, 0.5);
  GLB_SPtOverPtE  = fs->make<TH1F>("GLB_SPtOverPtE",  "GLB - #sigma(Pt)/Pt",  1000, 0, 0.5);

  StdA_SPtOverPt   = fs->make<TH1F>("StdA_SPtOverPt",  "StdA - #sigma(Pt)/Pt",  1000, 0, 0.5);
  StdA_SPtOverPtB  = fs->make<TH1F>("StdA_SPtOverPtB", "StdA - #sigma(Pt)/Pt",  1000, 0, 0.5);
  StdA_SPtOverPtE  = fs->make<TH1F>("StdA_SPtOverPtE", "StdA - #sigma(Pt)/Pt",  1000, 0, 0.5);

  //Sigma(Q/Pt)/|Q/Pt|
  DYT_SInvPOverP   = fs->make<TH1F>("DYT_SInvPOverP",   "DYT - #sigma(q/P)/q/P", 1000, 0,  0.5);
  DYT_SInvPOverPB  = fs->make<TH1F>("DYT_SInvPOverPB",  "DYT - #sigma(q/P)/q/P", 1000, 0,  0.5);
  DYT_SInvPOverPE  = fs->make<TH1F>("DYT_SInvPOverPE",  "DYT - #sigma(q/P)/q/P", 1000, 0,  0.5);

  TuneP_SInvPOverP  = fs->make<TH1F>("TuneP_SInvPOverP",  "TuneP - #sigma(q/P)/q/P",  1000, 0, 0.5);
  TuneP_SInvPOverPB = fs->make<TH1F>("TuneP_SInvPOverPB", "TuneP - #sigma(q/P)/q/P",  1000, 0, 0.5);
  TuneP_SInvPOverPE = fs->make<TH1F>("TuneP_SInvPOverPE", "TuneP - #sigma(q/P)/q/P",  1000, 0, 0.5);

  Picky_SInvPOverP   = fs->make<TH1F>("Picky_SInvPOverP",   "Picky - #sigma(q/P)/q/P",  1000, 0, 0.5);
  Picky_SInvPOverPB  = fs->make<TH1F>("Picky_SInvPOverPB",  "Picky - #sigma(q/P)/q/P",  1000, 0, 0.5);
  Picky_SInvPOverPE  = fs->make<TH1F>("Picky_SInvPOverPE",  "Picky - #sigma(q/P)/q/P",  1000, 0, 0.5);

  GLB_SInvPOverP   = fs->make<TH1F>("GLB_SInvPOverP",   "GLB - #sigma(q/P)/q/P",  1000, 0, 0.5);
  GLB_SInvPOverPB  = fs->make<TH1F>("GLB_SInvPOverPB",  "GLB - #sigma(q/P)/q/P",  1000, 0, 0.5);
  GLB_SInvPOverPE  = fs->make<TH1F>("GLB_SInvPOverPE",  "GLB - #sigma(q/P)/q/P",  1000, 0, 0.5);

  StdA_SInvPOverP   = fs->make<TH1F>("StdA_SInvPOverP",  "StdA - #sigma(q/P)/q/P",  1000, 0, 0.5);
  StdA_SInvPOverPB  = fs->make<TH1F>("StdA_SInvPOverPB", "StdA - #sigma(q/P)/q/P",  1000, 0, 0.5);
  StdA_SInvPOverPE  = fs->make<TH1F>("StdA_SInvPOverPE", "StdA - #sigma(q/P)/q/P",  1000, 0, 0.5);

}


void DYTAnalyzer::endJob()
{

}


void DYTAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{}


void DYTAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{}


void DYTAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{}


void DYTAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{}

void DYTAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
DEFINE_FWK_MODULE(DYTAnalyzer);
