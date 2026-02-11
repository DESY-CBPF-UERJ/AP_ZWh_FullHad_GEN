#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace Test{
    
    float boson_pt;
    float boson_m;
    float boson_pol_phi;

    int N_particles;
    int N_jets;
    int N_jets30;
    float LeadingJet_pt;
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupTest() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("good_events", 0) );

    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &Test::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    HDF_insert("event_number", &event_number );
    HDF_insert("evtWeight", &evtWeight );
    
    HDF_insert("boson_uncorr_pt", &Test::boson_pt );
    HDF_insert("boson_uncorr_m", &Test::boson_m );
    HDF_insert("boson_pol_phi", &Test::boson_pol_phi );

    HDF_insert("N_particles", &Test::N_particles );
    HDF_insert("N_jets", &Test::N_jets );
    HDF_insert("N_jets30", &Test::N_jets30 );
    HDF_insert("LeadingJet_pt", &Test::LeadingJet_pt );

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::TestRegion() {

    //-------------------------------------------------------------------------
    // Cut description
    //-------------------------------------------------------------------------
    //if( !(CutCondition) ) return false;           [Example]
    //_cutFlow.at("CutName") += evtWeight;          [Example]

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPHero::TestSelection() {
    
    plot_events({1, 5});

    /*
    vertices:
    • weights – vector of floating point numbers which correspond to the weights assigned to this vertex.
    particles:
    • flows – vector of integer numbers which correspond to the QCD color flow information. No encoding scheme of the colour flows is imposed by the library, but it is expected to comply with the rules in Ref. [2].
    • theta – an attribute holding the floating point value of the θ angle for polarisation.
    */
    
    // https://dayabay.bnl.gov/dox/HepMC/html/classHepMC_1_1GenParticle.html
    
    
    Test::boson_pt = -1;
    Test::boson_m = -1;
    Test::boson_pol_phi = -1;
    bool is_good = false;
    for (auto p: _evt.particles()) {
        if( (*p).end_vertex() && ((abs((*p).pdg_id()) == 22) || (abs((*p).pdg_id()) == 23)) ){
            for (auto daughter : (*p).end_vertex()->particles_out() ) { 
                if( (abs((*daughter).pdg_id()) == 11) || (abs((*daughter).pdg_id()) == 13) || (abs((*daughter).pdg_id()) == 15) ){
                    _cutFlow.at("good_events") += 1; 
                    is_good = true;
                    Test::boson_pt = (*p).momentum().perp();
                    Test::boson_m = (*p).momentum().m();
                    break;
                }
            }
            if( is_good ) break;
        }
    }


    vector<fastjet::PseudoJet> particles;

    Test::N_particles = 0;
    for (auto p: _evt.particles()) {
        if( (*p).end_vertex() ){
            particles.push_back( fastjet::PseudoJet((*p).momentum().px(), (*p).momentum().py(), (*p).momentum().pz(), (*p).momentum().e()) );
            Test::N_particles += 1;
        }
    }
    
    // choose a jet definition
    double R = 0.4;
    fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);
    
    // run the clustering, extract the jets
    fastjet::ClusterSequence cs(particles, jet_def);
    vector<fastjet::PseudoJet> jets = fastjet::sorted_by_pt(cs.inclusive_jets());

    Test::N_jets = jets.size();
    Test::LeadingJet_pt = 0;
    if( jets.size() > 0 ) Test::LeadingJet_pt = jets[0].pt();

    Test::N_jets30 = 0;
    for (unsigned ijet = 0; ijet < jets.size(); ijet++) {
        if( jets[ijet].pt() > 30 ) Test::N_jets30 += 1;
    }

    evtWeight = weights_value.at(0);

    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //Test::variable1Name = 100;      [Example]

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
void HEPHero::TestSystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishTest() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
