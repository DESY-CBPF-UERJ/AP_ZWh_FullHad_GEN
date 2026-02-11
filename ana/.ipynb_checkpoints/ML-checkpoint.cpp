#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace ML{

    float FatJet_pt;
    float FatJet_msoftdrop;
    int FatJet_nConstituents;
    float FatJet_WM_HbbvsQCD;
    float FatJet_WM_HccvsQCD;
    float FatJet_WM_QCD;
    float FatJet_WM_TvsQCD;
    float FatJet_WM_WvsQCD;
    float FatJet_WM_ZvsQCD;
    float FatJet_XbbVsQCD;
    float FatJet_XccVsQCD;
    float FatJet_XggVsQCD;
    float FatJet_XqqVsQCD;
    float FatJet_XttVsQCD;
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupML() {

    //======SETUP CUTFLOW==========================================================================

    _cutFlow.insert(pair<string,double>("00_Leptons_equal_0", 0) );
    _cutFlow.insert(pair<string,double>("01_NbJets_more_0", 0) );
    _cutFlow.insert(pair<string,double>("02_MET_PT_more_200_and_MHT_more_200", 0) );
    _cutFlow.insert(pair<string,double>("03_NfatJets_more_0", 0) );
    _cutFlow.insert(pair<string,double>("04_LeadingFatPt_more_200", 0) );
    _cutFlow.insert(pair<string,double>("05_Omega_more_0p3", 0) );

    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &ML::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    HDF_insert( "Nbjets", &Nbjets );
    HDF_insert( "HT", &HT );
    HDF_insert( "OmegaMin", &OmegaMin );
    HDF_insert( "FMax", &FMax );
    HDF_insert( "MHT", &MHT );
    HDF_insert( "MET_pt", &MET_pt );
    HDF_insert( "MDT", &MDT );
    HDF_insert( "MET_FatJet_deltaPhi", &MET_FatJet_deltaPhi );
    HDF_insert( "MET_FatJet_Mt", &MET_FatJet_Mt );
    HDF_insert( "RT_1", &RT_1 );
    HDF_insert( "RT_3", &RT_3 );
    HDF_insert( "tauT", &tauT );

    HDF_insert( "FatJet_pt", &ML::FatJet_pt );
    HDF_insert( "FatJet_msoftdrop", &ML::FatJet_msoftdrop );
    HDF_insert( "FatJet_nConstituents", &ML::FatJet_nConstituents );
    HDF_insert( "FatJet_WM_HbbvsQCD", &ML::FatJet_WM_HbbvsQCD );
    HDF_insert( "FatJet_WM_HccvsQCD", &ML::FatJet_WM_HccvsQCD );
    HDF_insert( "FatJet_WM_QCD", &ML::FatJet_WM_QCD );
    HDF_insert( "FatJet_WM_TvsQCD", &ML::FatJet_WM_TvsQCD );
    HDF_insert( "FatJet_WM_WvsQCD", &ML::FatJet_WM_WvsQCD );
    HDF_insert( "FatJet_WM_ZvsQCD", &ML::FatJet_WM_ZvsQCD );
    HDF_insert( "FatJet_XbbVsQCD", &ML::FatJet_XbbVsQCD );
    HDF_insert( "FatJet_XccVsQCD", &ML::FatJet_XccVsQCD );
    HDF_insert( "FatJet_XggVsQCD", &ML::FatJet_XggVsQCD );
    HDF_insert( "FatJet_XqqVsQCD", &ML::FatJet_XqqVsQCD );
    HDF_insert( "FatJet_XttVsQCD", &ML::FatJet_XttVsQCD );


    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::MLRegion() {

    LeptonSelection();

    if (!(Nleptons==0) ) return false;
    _cutFlow.at("00_Leptons_equal_0") += evtWeight;

    JetSelection();

    if ( !(Nbjets>0) ) return false;
    _cutFlow.at("01_NbJets_more_0") += evtWeight;

    if (!(MET_pt > 200 && MHT > 200) ) return false;
    _cutFlow.at("02_MET_PT_more_200_and_MHT_more_200") += evtWeight;

    FatjetSelection();

    if ( !(NfatJets>0) ) return false;
    _cutFlow.at("03_NfatJets_more_0") += evtWeight;

    if ( !(LeadingFatJet_pt>200) ) return false;
    _cutFlow.at("04_LeadingFatPt_more_200") += evtWeight;

    Get_Jet_Angular_Variables();

    if ( !(OmegaMin>OMEGA_CUT) ) return false;
    _cutFlow.at("05_Omega_more_0p3") += evtWeight;

    Get_Jet_Shape_Variables();
    Weight_corrections();


    ML::FatJet_pt = FatJet_pt[selectedFatJet.at(0)];
    ML::FatJet_msoftdrop = FatJet_msoftdrop[selectedFatJet.at(0)];
    ML::FatJet_nConstituents = FatJet_nConstituents[selectedFatJet.at(0)];
    ML::FatJet_WM_HbbvsQCD = FatJet_particleNetWithMass_HbbvsQCD[selectedFatJet.at(0)];
    ML::FatJet_WM_HccvsQCD = FatJet_particleNetWithMass_HccvsQCD[selectedFatJet.at(0)];
    ML::FatJet_WM_QCD = FatJet_particleNetWithMass_QCD[selectedFatJet.at(0)];
    ML::FatJet_WM_TvsQCD = FatJet_particleNetWithMass_TvsQCD[selectedFatJet.at(0)];
    ML::FatJet_WM_WvsQCD = FatJet_particleNetWithMass_WvsQCD[selectedFatJet.at(0)];
    ML::FatJet_WM_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[selectedFatJet.at(0)];
    ML::FatJet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[selectedFatJet.at(0)];
    ML::FatJet_XccVsQCD = FatJet_particleNet_XccVsQCD[selectedFatJet.at(0)];
    ML::FatJet_XggVsQCD = FatJet_particleNet_XggVsQCD[selectedFatJet.at(0)];
    ML::FatJet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[selectedFatJet.at(0)];
    ML::FatJet_XttVsQCD = FatJet_particleNet_XttVsQCD[selectedFatJet.at(0)];



    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPHero::MLSelection() {






    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //ML::variable1Name = 100;      [Example]

    //======FILL THE HISTOGRAMS====================================================================
    //_histograms1D.at("histogram1DName").Fill( var, evtWeight );               [Example]
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]

    //======FILL THE OUTPUT TREE===================================================================
    //_outputTree->Fill();

    //======FILL THE OUTPUT HDF5 INFO===============================================================
    HDF_fill();

    return;
}


//-------------------------------------------------------------------------------------------------
// Produce systematic histograms
//-------------------------------------------------------------------------------------------------
void HEPHero::MLSystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishML() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
