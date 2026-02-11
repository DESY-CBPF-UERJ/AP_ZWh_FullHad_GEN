#include "HEPHero.h"

void HEPHero::Jet_lep_overlap( float deltaR_cut ){

    Jet_LepOverlap.clear();
    for( unsigned int ijet = 0; ijet < nJet; ++ijet ) {
        Jet_LepOverlap.push_back(false);
    }

    //for( unsigned int iele = 0; iele < nElectron; ++iele ) {
    for( unsigned int iselEle = 0; iselEle < selectedEle.size(); ++iselEle ) {
        int iele = selectedEle.at(iselEle);
        float drMin = 99999.;
        int JetID = -1;
        for( unsigned int ijet = 0; ijet < nJet; ++ijet ) {
            double deta = fabs(Electron_eta[iele] - Jet_eta[ijet]);
            double dphi = fabs(Electron_phi[iele] - Jet_phi[ijet]);
            if( dphi > M_PI ) dphi = 2*M_PI - dphi;
            double dr = sqrt( deta*deta + dphi*dphi );
            if( dr < drMin ){
                drMin = dr;
                JetID = ijet;
            }
        }
        if( (drMin < deltaR_cut) && (JetID >= 0) ){
            //cout << "deltaR " << drMin << " " << endl;
            //cout << "JetID " << JetID << " " << endl;
            Jet_LepOverlap[JetID] = true;
        }
    }

    //for( unsigned int imu = 0; imu < nMuon; ++imu ) {
    for( unsigned int iselMu = 0; iselMu < selectedMu.size(); ++iselMu ) {
        int imu = selectedMu.at(iselMu);
        float drMin = 99999.;
        int JetID = -1;
        for( unsigned int ijet = 0; ijet < nJet; ++ijet ) {
            double deta = fabs(Muon_eta[imu] - Jet_eta[ijet]);
            double dphi = fabs(Muon_phi[imu] - Jet_phi[ijet]);
            if( dphi > M_PI ) dphi = 2*M_PI - dphi;
            double dr = sqrt( deta*deta + dphi*dphi );
            if( dr < drMin ){
                drMin = dr;
                JetID = ijet;
            }
        }
        if( (drMin < deltaR_cut) && (JetID >= 0) ){
            //cout << "deltaR " << drMin << " " << endl;
            //cout << "JetID " << JetID << " " << endl;
            Jet_LepOverlap[JetID] = true;
        }
    }

}

//---------------------------------------------------------------------------------------------
// Lepton selection
//---------------------------------------------------------------------------------------------
void HEPHero::LeptonSelection(){

    selectedEle.clear();
    selectedMu.clear();
    selectedTau.clear();

    //LOOP ELETRON
    for( unsigned int iele = 0; iele < nElectron; ++iele ) {
        
        if( abs(Electron_eta[iele]) >= ELECTRON_ETA_CUT ) continue;
        if( !ElectronID( iele, ELECTRON_ID_WP ) ) continue;
        if( (abs(Electron_eta[iele] + Electron_deltaEtaSC[iele]) > ELECTRON_GAP_LOWER_CUT) &&
            (abs(Electron_eta[iele] + Electron_deltaEtaSC[iele]) < ELECTRON_GAP_UPPER_CUT) ) continue;
        if( Electron_pt[iele] <= ELECTRON_PT_CUT ) continue;

        selectedEle.push_back(iele);
    }

    //LOOP MUON
    for( unsigned int imu = 0; imu < nMuon; ++imu ) {
        //std::cout<<"MUON_ID_WP"<<MUON_ID_WP<<endl;
        if( abs(Muon_eta[imu]) >= MUON_ETA_CUT ) continue;
        if( !MuonID( imu, MUON_ID_WP ) ) continue;
        if( !MuonISO( imu, MUON_ISO_WP ) ) continue;

        if( Muon_pt[imu] <= MUON_PT_CUT ) continue;

        selectedMu.push_back(imu);
  
    }

    //LOOP TAU
    for( unsigned int itau = 0; itau < nTau; ++itau ) {

        if( Tau_pt[itau] <= TAU_PT_CUT ) continue;
        if( abs(Tau_eta[itau]) >= TAU_ETA_CUT ) continue;

        if( !TauVSMuonID( itau, TAU_VS_MU_ISO_WP ) ) continue;
        if( !TauVSEletronID( itau, TAU_VS_ELE_ISO_WP ) ) continue;
        if( !TauVSJetID( itau, TAU_VS_JET_ISO_WP ) ) continue;

        selectedTau.push_back(itau);
    }


    Nelectrons = selectedEle.size();
    Nmuons = selectedMu.size();
    Ntaus = selectedTau.size();
    Nleptons = Nelectrons + Nmuons + Ntaus;

    
}


void HEPHero::JetSelection(){
    // ------------------------
    // Recommendations for Run3 here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetMET#Run3_recommendations
    // ------------------------

    selectedJet.clear();
    //jetMomenta.clear();

    // // TODO: TO BE IMPLEMENTED
    // JESvariation();
    // JERvariation();

    Jet_lep_overlap(JET_LEP_DR_ISO_CUT);

    Nbjets = 0;
    Nbjets30 = 0;
    Nbjets_LepIso04 = 0;
    Nbjets30_LepIso04 = 0;
    Njets = 0;
    Njets30 = 0;
    Njets40 = 0;
    Njets_LepIso04 = 0;
    Njets30_LepIso04 = 0;
    Njets40_LepIso04 = 0;
    Njets_forward = 0;
    Njets_tight = 0;
    Njets_ISR = 0;
    NPUjets = 0;
    Jet_abseta_max = 0;
    HT = 0;
    HT30 = 0;
    HT40 = 0;
    float HPx = 0;
    float HPy = 0;
    float HPx30 = 0;
    float HPy30 = 0;
    float HPx40 = 0;
    float HPy40 = 0;
    float HPx_trig = 0;
    float HPy_trig = 0;

    // Main loop to process each jet
    for( unsigned int ijet = 0; ijet < nJet; ++ijet ) {
        
        if( Jet_pt[ijet] <= JET_PT_CUT ) continue;
        if( Jet_jetId[ijet] >= 2 ){
            TLorentzVector Jet_trig;
            Jet_trig.SetPtEtaPhiE(Jet_pt[ijet], Jet_eta[ijet], Jet_phi[ijet], 0);
            HPx_trig += Jet_trig.Px();
            HPy_trig += Jet_trig.Py();
        }
        //if( (abs(Jet_eta[ijet]) < JET_ETA_CUT) and (Jet_jetId[ijet] >= 2) ) Njets_tight += 1;
        if( Jet_jetId[ijet] < JET_ID_WP ) continue;
        
        //if( Jet_lep_overlap( ijet, JET_LEP_DR_ISO_CUT ) ) continue;
        if( Jet_LepOverlap[ijet] ) continue;
        
        // TODO: Verify values for that implementation. This line was implemented for Run2, but we do not know if is the same for Run3. Try to check in https://twiki.cern.ch/twiki/bin/view/CMS/EgammaRunIIIRecommendations
        //if( (Jet_pt[ijet] < 50) && (Jet_puId[ijet] < JET_PUID_WP) ) continue;

        if ( (Jet_pt[ijet] < 50) && ( 2.5 < abs(Jet_eta[ijet]) && 3 > abs(Jet_eta[ijet]) ) ) continue;   // due to eta spikes (since we apply a cut in jet with more than 2.5 eta, this cut is not necessary, but I will leave this here for the future)


        if( abs(Jet_eta[ijet]) >= 5.0 ) continue;
        //if( abs(Jet_eta[ijet]) > 1.4 ) Njets_forward += 1;
        //if( abs(Jet_eta[ijet]) > Jet_abseta_max ) Jet_abseta_max = abs(Jet_eta[ijet]);
        if( abs(Jet_eta[ijet]) >= JET_ETA_CUT ) continue;
        selectedJet.push_back(ijet);
        TLorentzVector Jet;
        Jet.SetPtEtaPhiE(Jet_pt[ijet], Jet_eta[ijet], Jet_phi[ijet], 0);
        Njets += 1;
        //if( !Jet_lep_overlap(ijet, 0.4) ) Njets_LepIso04 += 1;
        if( PileupJet( ijet ) ) NPUjets += 1;
        HT += Jet_pt[ijet];
        HPx += Jet.Px();
        HPy += Jet.Py();
        if( Jet_pt[ijet] > 30 ){
            Njets30 += 1;
            //if( !Jet_lep_overlap(ijet, 0.4) ) Njets30_LepIso04 += 1;
            HT30 += Jet_pt[ijet];
            HPx30 += Jet.Px();
            HPy30 += Jet.Py();
        }
        if( Jet_pt[ijet] > 40 ){
            Njets40 += 1;
            //if( !Jet_lep_overlap(ijet, 0.4) ) Njets40_LepIso04 += 1;
            HT40 += Jet_pt[ijet];
            HPx40 += Jet.Px();
            HPy40 += Jet.Py();
        }
        if( JetBTAG( ijet, JET_BTAG_WP ) ){
            Nbjets += 1;
            if( Jet_pt[ijet] > 30 ) Nbjets30 += 1;
            //if( !Jet_lep_overlap(ijet, 0.4) ){
            //    Nbjets_LepIso04 += 1;
            //    if( Jet_pt[ijet] > 30 ) Nbjets30_LepIso04 += 1;
            //}
        }
        if( Jet_pt[ijet] > 26 ) Njets_ISR += 1;
        
    }
    MHT = sqrt(HPx*HPx + HPy*HPy);
    MHT30 = sqrt(HPx30*HPx30 + HPy30*HPy30);
    MHT40 = sqrt(HPx40*HPx40 + HPy40*HPy40);
    MHT_trig = sqrt(HPx_trig*HPx_trig + HPy_trig*HPy_trig);

    MDT = abs(MHT_trig - MET_pt);
    
    LeadingJet_pt = 0;
    SubLeadingJet_pt = 0;
    ThirdLeadingJet_pt = 0;
    FourthLeadingJet_pt = 0;

    LeadingJet_jetId = 0;
    SubLeadingJet_jetId = 0;
    ThirdLeadingJet_jetId = 0;
    FourthLeadingJet_jetId = 0;

    LeadingJet_mass = 0;
    SubLeadingJet_mass = 0;
    ThirdLeadingJet_mass = 0;
    FourthLeadingJet_mass = 0;


    if( Njets >= 1 ) { 
        LeadingJet_pt = Jet_pt[selectedJet.at(0)];
        LeadingJet_jetId = Jet_jetId[selectedJet.at(0)];
        LeadingJet_mass = Jet_mass[selectedJet.at(0)];
    }
    if( Njets >= 2 ) { 
        SubLeadingJet_pt = Jet_pt[selectedJet.at(1)];
        SubLeadingJet_jetId = Jet_jetId[selectedJet.at(1)];
        SubLeadingJet_mass = Jet_mass[selectedJet.at(1)];
    }
    if( Njets >= 3 ) { 
        ThirdLeadingJet_pt = Jet_pt[selectedJet.at(2)];
        ThirdLeadingJet_jetId = Jet_jetId[selectedJet.at(2)];
        ThirdLeadingJet_mass = Jet_mass[selectedJet.at(2)];
    }
    if( Njets >= 4 ) {
        FourthLeadingJet_pt = Jet_pt[selectedJet.at(3)];
        FourthLeadingJet_jetId = Jet_jetId[selectedJet.at(3)];
        FourthLeadingJet_mass = Jet_mass[selectedJet.at(3)];
    }


}


// Main loop to process each fat jet
void HEPHero::FatjetSelection(){

    //TODO: Check if there is a recommendation about the Fat JET (AK8) ID. We could not find any information in the twiki. 

    selectedFatJet.clear();

    NfatJets = 0;

    for( unsigned int ijet = 0; ijet < nFatJet; ++ijet ) {

        // std::cout << "FAT_JET_PT_CUT: " << FAT_JET_PT_CUT << "| FAT_JET_ETA_CUT: " << FAT_JET_ETA_CUT << std::endl;
        // std::cout << "FatJet_pt: " << FatJet_pt[ijet] << " | FatJet_eta: " << FatJet_eta[ijet] << " | FatJet_mass: " << FatJet_mass[ijet] << std::endl;

        if( FatJet_pt[ijet] <= FAT_JET_PT_CUT ) continue;
        if( abs(FatJet_eta[ijet]) >= FAT_JET_ETA_CUT ) continue;
        if( FatJet_jetId[ijet] < FAT_JET_ID_WP ) continue;

        selectedFatJet.push_back(ijet);        
        NfatJets += 1;


        //TLorentzVector FatJet;
        //FatJet.SetPtEtaPhiE(FatJet_pt[ijet], FatJet_eta[ijet], FatJet_phi[ijet], LeadingFatJet_mass[ijet]);
//      float M_PI = 3.14159265358979323846264338327950288;
        MET_FatJet_deltaPhi = abs( FatJet_phi[0] - MET_phi );
        if( MET_FatJet_deltaPhi > M_PI ) MET_FatJet_deltaPhi = 2*M_PI - MET_FatJet_deltaPhi;
        MET_FatJet_Mt = sqrt( 2 * FatJet_pt[0] * MET_pt * ( 1 - cos( MET_FatJet_deltaPhi ) ) ) ;

    }
   
    LeadingFatJet_jetId = 0;
    SubLeadingFatJet_jetId = 0;
    ThirdLeadingFatJet_jetId = 0;
    FourthLeadingFatJet_jetId = 0;
    LeadingFatJet_pt = 0;
    SubLeadingFatJet_pt = 0;
    ThirdLeadingFatJet_pt = 0;
    FourthLeadingFatJet_pt = 0;
    LeadingFatJet_mass = 0;
    SubLeadingFatJet_mass = 0;
    ThirdLeadingFatJet_mass = 0;
    FourthLeadingFatJet_mass = 0;
    LeadingFatJet_XbbVsQCD = 0;
    SubLeadingFatJet_XbbVsQCD = 0;
    ThirdLeadingFatJet_XbbVsQCD = 0;
    FourthLeadingFatJet_XbbVsQCD = 0;
    LeadingFatJet_XccVsQCD = 0;
    SubLeadingFatJet_XccVsQCD = 0;
    ThirdLeadingFatJet_XccVsQCD = 0;
    FourthLeadingFatJet_XccVsQCD = 0;
    LeadingFatJet_XggVsQCD = 0;
    SubLeadingFatJet_XggVsQCD = 0;
    ThirdLeadingFatJet_XggVsQCD = 0;
    FourthLeadingFatJet_XggVsQCD = 0;
    LeadingFatJet_XqqVsQCD = 0;
    SubLeadingFatJet_XqqVsQCD = 0;
    ThirdLeadingFatJet_XqqVsQCD = 0;
    FourthLeadingFatJet_XqqVsQCD = 0;
    LeadingFatJet_msoftdrop = 0;
    SubLeadingFatJet_msoftdrop = 0;
    ThirdLeadingFatJet_msoftdrop = 0;
    FourthLeadingFatJet_msoftdrop = 0;
    LeadingFatJet_massCorr = 0;
    SubLeadingFatJet_massCorr = 0;
    ThirdLeadingFatJet_massCorr = 0;
    FourthLeadingFatJet_massCorr = 0;
    LeadingFatJet_ZvsQCD = 0;
    SubLeadingFatJet_ZvsQCD = 0;
    ThirdLeadingFatJet_ZvsQCD = 0;
    FourthLeadingFatJet_ZvsQCD = 0;

    FatJet_b_max_deltaEta = 0;


    if( NfatJets >= 1 ) {
        LeadingFatJet_jetId = FatJet_jetId[selectedFatJet.at(0)];
        LeadingFatJet_pt = FatJet_pt[selectedFatJet.at(0)];
        LeadingFatJet_mass = FatJet_mass[selectedFatJet.at(0)];
        LeadingFatJet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[selectedFatJet.at(0)];
        LeadingFatJet_XccVsQCD = FatJet_particleNet_XccVsQCD[selectedFatJet.at(0)];
        LeadingFatJet_XggVsQCD = FatJet_particleNet_XggVsQCD[selectedFatJet.at(0)];
        LeadingFatJet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[selectedFatJet.at(0)];
        LeadingFatJet_massCorr = FatJet_particleNet_massCorr[selectedFatJet.at(0)];
        LeadingFatJet_msoftdrop = FatJet_msoftdrop[selectedFatJet.at(0)];
        LeadingFatJet_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[selectedFatJet.at(0)];


        for( unsigned int iseljet = 0; iseljet < selectedJet.size(); ++iseljet ) {
        int ijet = selectedJet[iseljet];
        if( JetBTAG( ijet, JET_BTAG_WP ) ){
            float FatJet_b_deltaEta = abs( FatJet_eta[selectedFatJet.at(0)] - Jet_eta[ijet]);
            if( FatJet_b_deltaEta > FatJet_b_max_deltaEta ) FatJet_b_max_deltaEta = FatJet_b_deltaEta;
        }
    }
        
    }
    if( NfatJets >= 2 ) {
        SubLeadingFatJet_jetId = FatJet_jetId[selectedFatJet.at(1)];
        SubLeadingFatJet_pt = FatJet_pt[selectedFatJet.at(1)];
        SubLeadingFatJet_mass = FatJet_mass[selectedFatJet.at(1)];
        SubLeadingFatJet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[selectedFatJet.at(1)];
        SubLeadingFatJet_XccVsQCD = FatJet_particleNet_XccVsQCD[selectedFatJet.at(1)];
        SubLeadingFatJet_XggVsQCD = FatJet_particleNet_XggVsQCD[selectedFatJet.at(1)];
        SubLeadingFatJet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[selectedFatJet.at(1)];
        SubLeadingFatJet_massCorr = FatJet_particleNet_massCorr[selectedFatJet.at(1)];
        SubLeadingFatJet_msoftdrop = FatJet_msoftdrop[selectedFatJet.at(1)];
        SubLeadingFatJet_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[selectedFatJet.at(1)];
        
    }
    if( NfatJets >= 3 ) {
        ThirdLeadingFatJet_jetId = FatJet_jetId[selectedFatJet.at(2)];
        ThirdLeadingFatJet_pt = FatJet_pt[selectedFatJet.at(2)];
        ThirdLeadingFatJet_mass = FatJet_mass[selectedFatJet.at(2)];
        ThirdLeadingFatJet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[selectedFatJet.at(2)];
        ThirdLeadingFatJet_XccVsQCD = FatJet_particleNet_XccVsQCD[selectedFatJet.at(2)];
        ThirdLeadingFatJet_XggVsQCD = FatJet_particleNet_XggVsQCD[selectedFatJet.at(2)];
        ThirdLeadingFatJet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[selectedFatJet.at(2)];
        ThirdLeadingFatJet_massCorr = FatJet_particleNet_massCorr[selectedFatJet.at(2)];
        ThirdLeadingFatJet_msoftdrop = FatJet_msoftdrop[selectedFatJet.at(2)];
        ThirdLeadingFatJet_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[selectedFatJet.at(2)];
        
    }
    if( NfatJets >= 4 ) {
        FourthLeadingFatJet_jetId = FatJet_jetId[selectedFatJet.at(3)];
        FourthLeadingFatJet_pt = FatJet_pt[selectedFatJet.at(3)];
        FourthLeadingFatJet_mass = FatJet_mass[selectedFatJet.at(3)];
        FourthLeadingFatJet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[selectedFatJet.at(3)];
        FourthLeadingFatJet_XccVsQCD = FatJet_particleNet_XccVsQCD[selectedFatJet.at(3)];
        FourthLeadingFatJet_XggVsQCD = FatJet_particleNet_XggVsQCD[selectedFatJet.at(3)];
        FourthLeadingFatJet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[selectedFatJet.at(3)];
        FourthLeadingFatJet_massCorr = FatJet_particleNet_massCorr[selectedFatJet.at(3)];
        FourthLeadingFatJet_msoftdrop = FatJet_msoftdrop[selectedFatJet.at(3)];
        FourthLeadingFatJet_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[selectedFatJet.at(3)];
    }

    // if( NfatJets >= 1 ) LeadingFatJet_pt = FatJet_pt[selectedFatJet.at(0)];
    // if( NfatJets >= 2 ) SubLeadingFatJet_pt = FatJet_pt[selectedFatJet.at(1)];
    // if( NfatJets >= 3 ) ThirdLeadingFatJet_pt = FatJet_pt[selectedFatJet.at(2)];
    // if( NfatJets >= 4 ) FourthLeadingFatJet_pt = FatJet_pt[selectedFatJet.at(3)];

    // FatJet_b_max_deltaEta = 0;
    // for( unsigned int iseljet = 0; iseljet < selectedJet.size(); ++iseljet ) {
    //     int ijet = selectedJet[iseljet];
    //     if( JetBTAG( ijet, JET_BTAG_WP ) ){
    //         float FatJet_b_deltaEta = abs(FatJet_eta - Jet_eta[ijet]);
    //         if( FatJet_b_deltaEta > FatJet_b_max_deltaEta ) FatJet_b_max_deltaEta = FatJet_b_deltaEta;
    //     }
    // }

    // Hadronic Channel - 1 (Z-channel), 2(h-channel)
    hadronic_channel = 0;
    if( NfatJets >= 1 ) {
        int fatjet_idx = selectedFatJet.at(0);
        
        vector<float> input_vec;
        input_vec.push_back(FatJet_particleNet_XbbVsQCD[fatjet_idx]);
        input_vec.push_back(FatJet_particleNet_XccVsQCD[fatjet_idx]);
        input_vec.push_back(FatJet_particleNet_XggVsQCD[fatjet_idx]);
        input_vec.push_back(FatJet_particleNet_XqqVsQCD[fatjet_idx]);
        input_vec.push_back(FatJet_particleNet_XteVsQCD[fatjet_idx]);
        input_vec.push_back(FatJet_particleNet_XtmVsQCD[fatjet_idx]);
        input_vec.push_back(FatJet_particleNet_XttVsQCD[fatjet_idx]);
        input_vec.push_back(FatJet_particleNet_QCD[fatjet_idx]);
        vector<float> fatjet_type_prob = SoftmaxHEP(input_vec);
        
        int type_id = max_element(fatjet_type_prob.begin(), fatjet_type_prob.end()) - fatjet_type_prob.begin();
        if( type_id == 2 ){
            hadronic_channel = 2;
        }else if( type_id == 3 ){
            hadronic_channel = 1;
        }else{
            vector<float> input_vec_2;
            input_vec_2.push_back(FatJet_particleNetWithMass_HbbvsQCD[fatjet_idx]);
            input_vec_2.push_back(FatJet_particleNetWithMass_HccvsQCD[fatjet_idx]);
            input_vec_2.push_back(FatJet_particleNetWithMass_ZvsQCD[fatjet_idx]);
            vector<float> fatjet_Zh_prob = SoftmaxHEP(input_vec_2);
            float Hbb_prob = fatjet_Zh_prob[0];
            float Hcc_prob = fatjet_Zh_prob[1];
            float Z_prob = fatjet_Zh_prob[2];
    
            if( Z_prob > Hbb_prob && Z_prob > Hcc_prob ){
                hadronic_channel = 1;
            }else{
                hadronic_channel = 2;
            }
        }
    }
    
}


vector<float> HEPHero::SoftmaxHEP( vector<float> input_vec ){

    vector<float> output_vec;
    float denominator = 0;
    for( unsigned int i = 0; i < input_vec.size(); ++i ) {
        denominator += exp(input_vec.at(i));
        output_vec.push_back(exp(input_vec.at(i)));
    }

    for( unsigned int i = 0; i < input_vec.size(); ++i ) {
        output_vec.at(i) = output_vec.at(i)/denominator;
    }
    
    return output_vec;
}


bool HEPHero::Trigger(){
    bool triggered = false;
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgHLTRunIISummary (electron triggers recommendation)

    //=====TRIGGERS FOR 2022=====================================================================
    if( dataset_year == "22" ){

        triggered = true; 

    }

    //=====TRIGGERS FOR 2023=====================================================================
    if( dataset_year == "23" ){

    }

    //=====TRIGGERS FOR 2024=====================================================================
    if( dataset_year == "24" ){

    }


    return triggered;
}




//-------------------------------------------------------------------------------------------------
// Get angular variables
//-------------------------------------------------------------------------------------------------
void HEPHero::Get_Jet_Angular_Variables( int pt_cut ){

    if( (pt_cut != 20) && (pt_cut != 30) && (pt_cut != 40) ){
        cout << "Sorry, for angular variables the only cuts acceptable are 20, 30, or 40. Let's consider your cut equal to 20 GeV!" << endl;
        pt_cut = 20;
    }

    double HPx = 0;
    double HPy = 0;
    for( unsigned int iselJet = 0; iselJet < selectedJet.size(); ++iselJet ) {
        int iJet = selectedJet.at(iselJet);
        if( Jet_pt[iJet] < pt_cut ) continue;
        TLorentzVector Jet;
        Jet.SetPtEtaPhiE(Jet_pt[iJet], Jet_eta[iJet], Jet_phi[iJet], 0);
        HPx += Jet.Px();
        HPy += Jet.Py();
    }
    double MHT_i = sqrt(HPx*HPx + HPy*HPy);

    float omegaMin = 999999;
    float chiMin = 999999;
    float fMax = 0;
    for( unsigned int iselJet = 0; iselJet < selectedJet.size(); ++iselJet ) {
        int iJet = selectedJet.at(iselJet);
        if( Jet_pt[iJet] < pt_cut ) continue;

        double dPhi_i = abs( Jet_phi[iJet] - atan2(-HPy,-HPx) );
        if( dPhi_i > M_PI ) dPhi_i  = 2*M_PI-dPhi_i ;

        double f_i = Jet_pt[iJet]/MHT_i;
        if( f_i > fMax ) fMax = f_i;

        double M1 = dPhi_i;
        if( dPhi_i > M_PI/2 ) M1  = M_PI/2 ;

        double M2 = f_i;
        if( f_i > -cos(dPhi_i) ) M2 = -cos(dPhi_i);

        double MAX = f_i + cos(dPhi_i);
        if( MAX < 0 ) MAX = 0;

        double M3 = f_i;
        if( M3 > MAX ) M3 = MAX;

        double omega_i = atan2(sin(M1),f_i);
        if( omega_i < omegaMin ) omegaMin = omega_i;

        double chi_i = atan2(sqrt(1+M2*M2+2*M2*cos(dPhi_i)),M3);
        if( chi_i < chiMin ) chiMin = chi_i;

    }
    if( omegaMin == 999999 ) omegaMin = -1;
    if( chiMin == 999999 ) chiMin = -1;

    if( pt_cut == 20 ){
        OmegaMin = omegaMin;
        ChiMin = chiMin;
        FMax = fMax;
    }else if( pt_cut == 30 ){
        OmegaMin30 = omegaMin;
        ChiMin30 = chiMin;
        FMax30 = fMax;
    }else if( pt_cut == 40 ){
        OmegaMin40 = omegaMin;
        ChiMin40 = chiMin;
        FMax40 = fMax;
    }

}


//-------------------------------------------------------------------------------------------------
// Get shape variables [https://arxiv.org/abs/1102.4785]
//-------------------------------------------------------------------------------------------------
void HEPHero::Get_Jet_Shape_Variables(){

    float HT_1 = 0;
    float HT_2 = 0;
    float HT_3 = 0;
    float HT_4 = 0;
    int phi_values = 32; // 2*M_PI/0.4 = 15.7
    vector<float> prod_sum(phi_values, 0.0);
    for( unsigned int iseljet = 0; iseljet < selectedJet.size(); ++iseljet ){
        int ijet = selectedJet.at(iseljet);
        if(iseljet < 1) HT_1 += Jet_pt[ijet];
        if(iseljet < 2) HT_2 += Jet_pt[ijet];
        if(iseljet < 3) HT_3 += Jet_pt[ijet];
        if(iseljet < 4) HT_4 += Jet_pt[ijet];

        TLorentzVector Jet;
        Jet.SetPtEtaPhiE(Jet_pt[ijet], Jet_eta[ijet], Jet_phi[ijet], 0);
        for( unsigned int iphi = 0; iphi < phi_values; ++iphi ) {
            float phi = 2*M_PI*(iphi/phi_values);
            float n_x = cos(phi);
            float n_y = sin(phi);
            prod_sum.at(iphi) += abs(Jet.Px()*n_x + Jet.Py()*n_y);
        }
    }

    if( HT > 0 ){
        RT_1 = HT_1/HT;
        RT_2 = HT_2/HT;
        RT_3 = HT_3/HT;
        RT_4 = HT_4/HT;
        int id_max = max_element(prod_sum.begin(), prod_sum.end()) - prod_sum.begin();
        float TT = prod_sum.at(id_max)/HT; //transverse thrust
        tauT = 1 - TT;
    }else{
        RT_1 = 0;
        RT_2 = 0;
        RT_3 = 0;
        RT_4 = 0;
        tauT = 0;
    }

}


//-------------------------------------------------------------------------------------------------
// Get Signal Taggers
//-------------------------------------------------------------------------------------------------
void HEPHero::Get_Signal_Taggers(){
    float floatC = 1.;

    float fatjet_pt = FatJet_pt[selectedFatJet.at(0)];
    float fatjet_msoftdrop = FatJet_msoftdrop[selectedFatJet.at(0)];
    float fatjet_nConstituents = FatJet_nConstituents[selectedFatJet.at(0)];
    float fatjet_WM_HbbvsQCD = FatJet_particleNetWithMass_HbbvsQCD[selectedFatJet.at(0)];
    float fatjet_WM_HccvsQCD = FatJet_particleNetWithMass_HccvsQCD[selectedFatJet.at(0)];
    float fatjet_WM_QCD = FatJet_particleNetWithMass_QCD[selectedFatJet.at(0)];
    float fatjet_WM_TvsQCD = FatJet_particleNetWithMass_TvsQCD[selectedFatJet.at(0)];
    float fatjet_WM_WvsQCD = FatJet_particleNetWithMass_WvsQCD[selectedFatJet.at(0)];
    float fatjet_WM_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[selectedFatJet.at(0)];
    float fatjet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[selectedFatJet.at(0)];
    float fatjet_XccVsQCD = FatJet_particleNet_XccVsQCD[selectedFatJet.at(0)];
    float fatjet_XggVsQCD = FatJet_particleNet_XggVsQCD[selectedFatJet.at(0)];
    float fatjet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[selectedFatJet.at(0)];
    float fatjet_XttVsQCD = FatJet_particleNet_XttVsQCD[selectedFatJet.at(0)];

    vector<vector<float>> inputTensorValues = {{OmegaMin, Nbjets*floatC, HT, FMax, MHT, MET_pt, MDT, MET_FatJet_deltaPhi, MET_FatJet_Mt, RT_1, RT_3, tauT, fatjet_pt, fatjet_msoftdrop, fatjet_nConstituents*floatC, fatjet_WM_HbbvsQCD, fatjet_WM_HccvsQCD, fatjet_WM_QCD, fatjet_WM_TvsQCD, fatjet_WM_WvsQCD, fatjet_WM_ZvsQCD, fatjet_XbbVsQCD, fatjet_XccVsQCD, fatjet_XggVsQCD, fatjet_XqqVsQCD, fatjet_XttVsQCD}};
    vector<vector<int64_t>> inputTensorDims = {{1, 26}};
    const char* inputNames[] = {"features"};

    vector<vector<float>> outputTensorValues = {{999., 999.}};
    vector<vector<int64_t>> outputTensorDims = {{1, 2}};
    const char* outputNames[] = {"output"};

    vector<float> signal_tag_vec = signal_tagger.predict(inputNames, inputTensorValues, inputTensorDims, outputNames, outputTensorValues, outputTensorDims);
    signal_tag = signal_tag_vec.at(0);

}
