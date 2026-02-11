#include "HEPHero.h"


//---------------------------------------------------------------------------------------------
// Tau ID
//---------------------------------------------------------------------------------------------
// https://cds.cern.ch/record/2904699/files/DP2024_063.pdf -> DeepTau v2.5 is the recommended tools for Run3
// Info of varibles nanoAOD12 https://cms-nanoaod-integration.web.cern.ch/autoDoc/

bool HEPHero::TauVSEletronID( int iobj, int WP ){

    bool obj_selected = false;
//    std::cout<<"Testando WP:"<<WP<<endl;
//    std::cout<<"Tau_idDeepTau2018v2p5VSe: "<<(Tau_idDeepTau2018v2p5VSe[iobj] & WP) <<endl;
// byDeepTau2018v2p5VSe ID working points (deepTau2018v2p5): 1 = VVVLoose, 2 = VVLoose, 3 = VLoose, 4 = Loose, 5 = Medium, 6 = Tight, 7 = VTight, 8 = VVTight
    if(      WP == 0 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 0);    //No Identification
    else if( WP == 1 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 1);    //VVVLoose
    else if( WP == 2 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 2);    //VVLoose
    else if( WP == 3 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 3);    //VLoose
    else if( WP == 4 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 4);    //Loose
    else if( WP == 5 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 5);    //Medium
    else if( WP == 6 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 6);    //Tight
    else if( WP == 7 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 7);    //VTight
    else if( WP == 8 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSe[iobj] >= 8);    //VVTight


    return obj_selected;
}

bool HEPHero::TauVSJetID( int iobj, int WP ){

    bool obj_selected = false;
 //   std::cout<<"Testando WP:"<<WP<<endl;
 //   std::cout<<"Tau_idDeepTau2018v2p5VSjet: "<<(Tau_idDeepTau2018v2p5VSjet[iobj] & WP) <<endl;
// yDeepTau2018v2p5VSjet ID working points (deepTau2018v2p5): 1 = VVVLoose, 2 = VVLoose, 3 = VLoose, 4 = Loose, 5 = Medium, 6 = Tight, 7 = VTight, 8 = VVTight
    if(      WP == 0 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 0);    //No Identification
    else if( WP == 1 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 1);    //VVVLoose
    else if( WP == 2 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 2);    //VVLoose
    else if( WP == 3 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 3);    //VLoose
    else if( WP == 4 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 4);    //Loose
    else if( WP == 5 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 5);    //Medium
    else if( WP == 6 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 6);    //Tight
    else if( WP == 7 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 7);    //VTight
    else if( WP == 8 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSjet[iobj] >= 8);    //VVTight

    return obj_selected;
}

bool HEPHero::TauVSMuonID( int iobj, int WP ){

    bool obj_selected = false;
 //   std::cout<<"Testando WP:"<<WP<<endl;
 //   std::cout<<"Tau_idDeepTau2018v2p5VSmu: "<<(Tau_idDeepTau2018v2p5VSmu[iobj] & WP) <<endl;
// byDeepTau2018v2p5VSmu ID working points (deepTau2018v2p5): 1 = VLoose, 2 = Loose, 3 = Medium, 4 = Tight
    if(      WP == 0 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSmu[iobj] >= 0);    //No Identification
    else if( WP == 1 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSmu[iobj] >= 1);    //VVLoose
    else if( WP == 2 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSmu[iobj] >= 2);    //VLoose
    else if( WP == 3 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSmu[iobj] >= 3);    //Medium
    else if( WP == 4 ) obj_selected = ((int)Tau_idDeepTau2018v2p5VSmu[iobj] >= 4);    //Tight

    return obj_selected;
}


//---------------------------------------------------------------------------------------------
// Muon ID
//---------------------------------------------------------------------------------------------
bool HEPHero::MuonID( int iobj, int WP ){

    bool obj_selected = false;

    if(      WP == 0 ) obj_selected = Muon_looseId[iobj];
    else if( WP == 1 ) obj_selected = Muon_mediumId[iobj];
    else if( WP == 2 ) obj_selected = Muon_mediumPromptId[iobj];
    else if( WP == 3 ) obj_selected = Muon_tightId[iobj];
    else if( WP == 4 ) obj_selected = Muon_softId[iobj];
    else if( WP == 5 ) obj_selected = (Muon_highPtId[iobj] >= 1);             //Recommended to muon with pt > 200

    return obj_selected;
}


//---------------------------------------------------------------------------------------------
// Muon ISO
//---------------------------------------------------------------------------------------------
bool HEPHero::MuonISO( int iobj, int WP ){

    bool obj_selected = false;

    if(      WP == 0 ) obj_selected = true;                         // No need Isolation
    else if( WP == 1 ) obj_selected = (Muon_pfIsoId[iobj] >= 1);    // PFIsoVeryLoose,
    else if( WP == 2 ) obj_selected = (Muon_pfIsoId[iobj] >= 2);    // PFIsoLoose
    else if( WP == 3 ) obj_selected = (Muon_pfIsoId[iobj] >= 3);    // PFIsoMedium
    else if( WP == 4 ) obj_selected = (Muon_pfIsoId[iobj] >= 4);    // PFIsoTight
    else if( WP == 5 ) obj_selected = (Muon_pfIsoId[iobj] >= 5);    // PFIsoVeryTight
    else if( WP == 6 ) obj_selected = (Muon_pfIsoId[iobj] >= 6);    // PFIsoVeryVeryTight

    return obj_selected;
}



//---------------------------------------------------------------------------------------------
// Electron ID
//---------------------------------------------------------------------------------------------
bool HEPHero::ElectronID( int iobj, int WP ){

    bool obj_selected = false;

    if(      WP == 0 ) obj_selected = (Electron_cutBased[iobj] >= 0);
    else if( WP == 1 ) obj_selected = (Electron_cutBased[iobj] >= 1);
    else if( WP == 2 ) obj_selected = (Electron_cutBased[iobj] >= 2);
    else if( WP == 3 ) obj_selected = (Electron_cutBased[iobj] >= 3);
    else if( WP == 4 ) obj_selected = Electron_mvaIso_WP80[iobj];
    else if( WP == 5 ) obj_selected = Electron_mvaIso_WP90[iobj];

    return obj_selected;
}


//-------------------------------------------------------------------------
// Return boolean informing if the reco jet is a pileup jet or not
//-------------------------------------------------------------------------
bool HEPHero::PileupJet( int iJet ){
    bool isPileup = true;
    bool isSignal = false;

    for( unsigned int igenJet = 0; igenJet < nGenJet; ++igenJet ) {
        float DEta = fabs( GenJet_eta[igenJet] - Jet_eta[iJet] );
        float DPhi = fabs( GenJet_phi[igenJet] - Jet_phi[iJet] );
        if( DPhi > M_PI ) DPhi = 2*M_PI - DPhi;
        float DR = sqrt( DEta*DEta + DPhi*DPhi );
        if( DR < 0.4 ) isSignal = true;
    }
    if( isSignal ) isPileup = false;

    return isPileup;
}

//---------------------------------------------------------------------------------------------
// Jet BTAG
//---------------------------------------------------------------------------------------------
bool HEPHero::JetBTAG( int iobj, int WP ){
    // Source: https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer22/#general-remarks
    bool obj_selected = false;
    float BTAG_CUT;

    // DeepJet
    if( dataset_year == "22"){
        if( dataset_dti == 0 ){     //SUMMER2022
            if(      WP == 0 ) BTAG_CUT = 0.0583;   // loose
            else if( WP == 1 ) BTAG_CUT = 0.3086;   // medium
            else if( WP == 2 ) BTAG_CUT = 0.7183;   // tight
            else if( WP == 3 ) BTAG_CUT = 0.8111;   // very tight
            else if( WP == 4 ) BTAG_CUT = 0.9512;   // very very tight
        }else{                      //SUMMMER2022EE
            if(      WP == 0 ) BTAG_CUT = 0.0614;   // loose
            else if( WP == 1 ) BTAG_CUT = 0.3196;   // medium
            else if( WP == 2 ) BTAG_CUT = 0.73;   // tight
            else if( WP == 3 ) BTAG_CUT = 0.8184;   // very tight
            else if( WP == 4 ) BTAG_CUT = 0.9542;   // very very tight
        }
    }

    // particleNET
    if( dataset_year == "22"){
        if( dataset_dti == 0 ){     //SUMMER2022
            if(      WP == 5 ) BTAG_CUT = 0.047;   // loose
            else if( WP == 6 ) BTAG_CUT = 0.245;   // medium
            else if( WP == 7 ) BTAG_CUT = 0.6734;   // tight
            else if( WP == 8 ) BTAG_CUT = 0.7862;   // very tight
            else if( WP == 9 ) BTAG_CUT = 0.961;   // very very tight
        }else{                      //SUMMMER2022EE
            if(      WP == 5 ) BTAG_CUT = 0.0499;   // loose
            else if( WP == 6 ) BTAG_CUT = 0.2605;   // medium
            else if( WP == 7 ) BTAG_CUT = 0.6915;   // tight
            else if( WP == 8 ) BTAG_CUT = 0.8033;   // very tight
            else if( WP == 9 ) BTAG_CUT = 0.9664;   // very very tight
        }
    }

    // robustParticleTransformer
    if( dataset_year == "22"){
        if( dataset_dti == 0 ){     //SUMMER2022
            if(      WP == 10 ) BTAG_CUT = 0.0849;   // loose
            else if( WP == 11 ) BTAG_CUT = 0.4319;   // medium
            else if( WP == 12 ) BTAG_CUT = 0.8482;   // tight
            else if( WP == 13 ) BTAG_CUT = 0.9151;   // very tight
            else if( WP == 14 ) BTAG_CUT = 0.9874;   // very very tight
        }else{                      //SUMMMER2022EE
            if(      WP == 10 ) BTAG_CUT = 0.0897;   // loose
            else if( WP == 11 ) BTAG_CUT = 0.451;   // medium
            else if( WP == 12 ) BTAG_CUT = 0.8604;   // tight
            else if( WP == 13 ) BTAG_CUT = 0.9234;   // very tight
            else if( WP == 14 ) BTAG_CUT = 0.9893;   // very very tight
        }
    }

    if(      WP >= 0 and WP <=4 ) obj_selected = (Jet_btagDeepFlavB[iobj] > BTAG_CUT);    // DeepJet
    else if( WP >= 5 and WP <=9 ) obj_selected = (Jet_btagPNetB[iobj] > BTAG_CUT);        // particleNET
    else if( WP >= 10 and WP <=14 ) obj_selected = (Jet_btagRobustParTAK4B[iobj] > BTAG_CUT);        // robustParticleTransformer




    return obj_selected;
}





