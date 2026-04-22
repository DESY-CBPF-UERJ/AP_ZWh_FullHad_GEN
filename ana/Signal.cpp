#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace Signal{

    int tag_drellyan;

    float boson_pt;
    float boson_m;
    float boson_pol_phi;

    float drellyan_boson_uncorr_pt;
    float drellyan_boson_uncorr_m;
    float drellyan_boson_pol_phi;


    int N_particles;
    int N_jets;
    int N_jets30;
    float LeadingJet_pt;

    float MET_pt;

    int N_fatjets;
    float LeadingFatJet_pt;
    float N_fatjets200;

}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupSignal() {
    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("good_events", 0) );
   //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    HDF_insert("event_number", &event_number );
    HDF_insert("evtWeight", &evtWeight );
    
    HDF_insert("boson_uncorr_pt", &Signal::boson_pt );
    HDF_insert("boson_uncorr_m", &Signal::boson_m );
    HDF_insert("boson_pol_phi", &Signal::boson_pol_phi );

    HDF_insert("N_particles", &Signal::N_particles );
    HDF_insert("N_jets", &Signal::N_jets );
    HDF_insert("N_jets30", &Signal::N_jets30 );
    HDF_insert("LeadingJet_pt", &Signal::LeadingJet_pt );

    HDF_insert("tag_drellyan",&Signal::tag_drellyan);
    HDF_insert("drellyan_boson_uncorr_pt",&Signal::drellyan_boson_uncorr_pt);
    HDF_insert("drellyan_boson_uncorr_m",&Signal::drellyan_boson_uncorr_m);
    HDF_insert("drellyan_boson_pol_phi",&Signal::drellyan_boson_pol_phi);
    
    HDF_insert("MET_pt",&Signal::MET_pt);
    
    HDF_insert("N_fatjets",&Signal::N_fatjets);
    HDF_insert("LeadingFatJet_pt",&Signal::LeadingFatJet_pt);
    HDF_insert("N_fatjets200",&Signal::N_fatjets200);
    
    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::SignalRegion() {

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
void HEPHero::SignalSelection() {



 plot_events({1, 5});
    
    // https://dayabay.bnl.gov/dox/HepMC/html/classHepMC_1_1GenParticle.html
    Signal::tag_drellyan = 0;
    Signal::boson_pt = -1;
    Signal::boson_m = -1;
    Signal::boson_pol_phi = -999;
    bool is_good = false;
    for (auto p: _evt.particles()) {
        if( (*p).end_vertex() && ((abs((*p).pdg_id()) == 22) || (abs((*p).pdg_id()) == 23)) ){
            for (auto daughter : (*p).end_vertex()->particles_out() ) { 
                if( (abs((*daughter).pdg_id()) == 11) || (abs((*daughter).pdg_id()) == 13) || (abs((*daughter).pdg_id()) == 15) ){
                    _cutFlow.at("good_events") += 1; 
                    Signal::tag_drellyan = 1;
                    is_good = true;
                    Signal::drellyan_boson_uncorr_pt = (*p).momentum().perp();
                    Signal::drellyan_boson_uncorr_m = (*p).momentum().m();
                    Signal::drellyan_boson_pol_phi = (*p).momentum().phi();
                    break;
                }
            }
            if( is_good ) break;
        }
    }



    // AQUI TEMOS O LOOP DOS JATOS/PARTICULAS
    vector<fastjet::PseudoJet> particles;          
    TLorentzVector all_particle, one_particle;
    all_particle.SetPxPyPzE(0,0,0,0);
    Signal::N_particles = 0;
    for (auto p: _evt.particles()) {
        if( (*p).end_vertex() ){
            one_particle.SetPxPyPzE(
            (*p).momentum().px(),
            (*p).momentum().py(),
            (*p).momentum().pz(),
            (*p).momentum().e()
        );
          
            particles.push_back( fastjet::PseudoJet((*p).momentum().px(), (*p).momentum().py(), (*p).momentum().pz(), (*p).momentum().e()) );
            Signal::N_particles += 1;
            
            all_particle += one_particle;
        
        }
    }
    Signal::MET_pt = all_particle.Pt();


        
     // =======================
    // AK4 jets (R = 0.4)
    // =======================
    double R = 0.4;
    fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);
    
    fastjet::ClusterSequence cs(particles, jet_def);
    vector<fastjet::PseudoJet> jets = fastjet::sorted_by_pt(cs.inclusive_jets());
    
    
    // =======================
    // FatJets (AK8, R = 0.8)
    // =======================
    double Rfat = 0.8;
    fastjet::JetDefinition jet_def_fat(fastjet::antikt_algorithm, Rfat);
    
    fastjet::ClusterSequence cs_fat(particles, jet_def_fat);
    vector<fastjet::PseudoJet> fatjets = fastjet::sorted_by_pt(cs_fat.inclusive_jets());
    
    
    // =======================
    // Overlap removal (APENAS fatjets com pt > 200)
    // =======================
    vector<fastjet::PseudoJet> clean_jets;
    
    for (unsigned ijet = 0; ijet < jets.size(); ijet++) {
        bool keep = true;
    
        for (unsigned ifat = 0; ifat < fatjets.size(); ifat++) {
    
            // Só considera fatjets "duros"
            if (fatjets[ifat].pt() <= 200) continue;
    
            if (jets[ijet].delta_R(fatjets[ifat]) < 1.2) {
                keep = false;
                break;
            }
        }
    
        if (keep) clean_jets.push_back(jets[ijet]);
    }
    
    
    // =======================
    // Variáveis AK4 (limpos)
    // =======================
    Signal::N_jets = clean_jets.size();
    
    Signal::LeadingJet_pt = 0;
    if (clean_jets.size() > 0)
        Signal::LeadingJet_pt = clean_jets[0].pt();
    
    Signal::N_jets30 = 0;
    for (unsigned ijet = 0; ijet < clean_jets.size(); ijet++) {
        if (clean_jets[ijet].pt() > 30)
            Signal::N_jets30 += 1;
    }
    
    
    // =======================
    // Variáveis FatJets
    // =======================
    Signal::N_fatjets = fatjets.size();
    
    Signal::LeadingFatJet_pt = 0;
    if (fatjets.size() > 0)
        Signal::LeadingFatJet_pt = fatjets[0].pt();
    
    Signal::N_fatjets200 = 0;
    for (unsigned ifat = 0; ifat < fatjets.size(); ifat++) {
        if (fatjets[ifat].pt() > 200)
            Signal::N_fatjets200 += 1;
    }
    
    
    // =======================
    evtWeight = weights_value.at(0);

    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //Signal::variable1Name = 100;      [Example]

    //======FILL THE HISTOGRAMS====================================================================
    //_histograms1D.at("histogram1DName").Fill( var, evtWeight );               [Example]
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]

    //======FILL THE OUTPUT TREE===================================================================
    //_outputTree->Fill();

    //======FILL THE OUTPUT HDF5 INFO===============================================================
    HDF_fill();










    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //Signal::variable1Name = 100;      [Example]

    //======FILL THE HISTOGRAMS====================================================================
    //_histograms1D.at("histogram1DName").Fill( var, evtWeight );               [Example]
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]

    //======FILL THE OUTPUT TREE===================================================================
    //_outputTree->Fill();

    //======FILL THE OUTPUT HDF5 INFO===============================================================
    //HDF_fill();

    return;
}


//-------------------------------------------------------------------------------------------------
// Produce systematic histograms
//-------------------------------------------------------------------------------------------------
void HEPHero::SignalSystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishSignal() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}

