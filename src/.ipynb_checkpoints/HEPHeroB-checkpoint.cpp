#include "HEPHero.h"


//-------------------------------------------------------------------------------------------------
// FILL CONTROL VARIABLES WITH INPUT FILE LINES
//-------------------------------------------------------------------------------------------------
void HEPHero::FillControlVariables( string key, string value){

    //----CORRECTIONS------------------------------------------------------------------------------
    // if( key == "PILEUP_WGT"                 )   apply_pileup_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "ELECTRON_ID_WGT"            )   apply_electron_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "MUON_ID_WGT"                )   apply_muon_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "JET_PUID_WGT"               )   apply_jet_puid_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "BTAG_WGT"                   )   apply_btag_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "TRIGGER_WGT"                )   apply_trigger_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "PREFIRING_WGT"              )   apply_prefiring_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "JER_CORR"                   )   apply_jer_corr = ( atoi(value.c_str()) == 1 );
    // if( key == "MET_XY_CORR"                )   apply_met_xy_corr = ( atoi(value.c_str()) == 1 );
    // if( key == "MET_RECOIL_CORR"            )   apply_met_recoil_corr = ( atoi(value.c_str()) == 1 );
    // if( key == "TOP_PT_WGT"                 )   apply_top_pt_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "W_PT_WGT"                   )   apply_w_pt_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "VJETS_HT_WGT"               )   apply_vjets_HT_wgt = ( atoi(value.c_str()) == 1 );
    // if( key == "MUON_ROC_CORR"              )   apply_muon_roc_corr = ( atoi(value.c_str()) == 1 );

    //----METADATA FILES---------------------------------------------------------------------------
    // if( key == "lumi_certificate"           )   certificate_file = value;
    // if( key == "pdf_type"                   )   PDF_file = value;
    // if( key == "pileup"                     )   pileup_file = value;
    // if( key == "electron"                   )   electron_file = value;
    // if( key == "muon"                       )   muon_file = value;
    // if( key == "JES_MC"                     )   JES_MC_file = value;
    // if( key == "jet_puID"                   )   jet_puid_file = value;
    // if( key == "btag_SF"                    )   btag_SF_file = value;
    // if( key == "btag_eff"                   )   btag_eff_file = value;
    // if( key == "trigger"                    )   trigger_SF_file = value;
    // //if( key == "JER_MC"                     )   JER_file = value;
    // //if( key == "JER_SF_MC"                  )   JER_SF_file = value;
    // if( key == "JERC"                       )   jet_jerc_file = value;
    // if( key == "mu_RoccoR"                  )   muon_roc_file = value;
    // if( key == "Z_recoil"                   )   Z_recoil_file = value;
    // if( key == "NN_prep_keras"              )   preprocessing_keras_file = value;
    // if( key == "NN_model_keras"             )   model_keras_file = value;
    if( key == "NN_model"                      )   NN_model_file = value;

    //----SELECTION--------------------------------------------------------------------------------
    if( key == "JET_ETA_CUT"                )   JET_ETA_CUT = atof(value.c_str());
    if( key == "JET_PT_CUT"                 )   JET_PT_CUT = atof(value.c_str());
    if( key == "JET_ID_WP"                  )   JET_ID_WP = atoi(value.c_str());
    if( key == "JET_PUID_WP"                )   JET_PUID_WP = atoi(value.c_str());
    if( key == "JET_BTAG_WP"                )   JET_BTAG_WP = atoi(value.c_str());
    if( key == "JET_LEP_DR_ISO_CUT"         )   JET_LEP_DR_ISO_CUT = atof(value.c_str());

    if( key == "FAT_JET_PT_CUT"             )   FAT_JET_PT_CUT = atof(value.c_str());
    if( key == "FAT_JET_ETA_CUT"            )   FAT_JET_ETA_CUT = atof(value.c_str());
    if( key == "FAT_JET_ID_WP"              )   FAT_JET_ID_WP = atoi(value.c_str());

    if( key == "ELECTRON_GAP_LOWER_CUT"     )   ELECTRON_GAP_LOWER_CUT = atof(value.c_str());
    if( key == "ELECTRON_GAP_UPPER_CUT"     )   ELECTRON_GAP_UPPER_CUT = atof(value.c_str());
    if( key == "ELECTRON_ETA_CUT"           )   ELECTRON_ETA_CUT = atof(value.c_str());
    if( key == "ELECTRON_PT_CUT"            )   ELECTRON_PT_CUT = atof(value.c_str());
    if( key == "ELECTRON_LOW_PT_CUT"        )   ELECTRON_LOW_PT_CUT = atof(value.c_str());
    if( key == "ELECTRON_ID_WP"             )   ELECTRON_ID_WP = atoi(value.c_str());

    if( key == "MUON_ETA_CUT"               )   MUON_ETA_CUT = atof(value.c_str());
    if( key == "MUON_PT_CUT"                )   MUON_PT_CUT = atof(value.c_str());
    if( key == "MUON_LOW_PT_CUT"            )   MUON_LOW_PT_CUT = atof(value.c_str());
    if( key == "MUON_ID_WP"                 )   MUON_ID_WP = atoi(value.c_str());
    if( key == "MUON_ISO_WP"                )   MUON_ISO_WP = atoi(value.c_str());

    if( key == "TAU_VS_ELE_ISO_WP"          )   TAU_VS_ELE_ISO_WP = atoi(value.c_str());
    if( key == "TAU_VS_JET_ISO_WP"          )   TAU_VS_JET_ISO_WP = atoi(value.c_str());
    if( key == "TAU_VS_MU_ISO_WP"           )   TAU_VS_MU_ISO_WP = atoi(value.c_str());
    if( key == "TAU_PT_CUT"                 )   TAU_PT_CUT = atoi(value.c_str());
    if( key == "TAU_ETA_CUT"                )   TAU_ETA_CUT = atoi(value.c_str());

    if( key == "OMEGA_CUT"                  )   OMEGA_CUT = atof(value.c_str());

}


//-------------------------------------------------------------------------------------------------
// Init
//-------------------------------------------------------------------------------------------------
bool HEPHero::Init() {
    
    //======SET HISTOGRAMS STYLE===================================================================
    setStyle(1.0,true,0.15);

    return true;
}


//-------------------------------------------------------------------------------------------------
// ANAFILES' ROUTINES
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupAna(){
    if( false );
    else if( _SELECTION == "Test" ) SetupTest();
    // SETUP YOUR SELECTION HERE
    else {
      cout << "Unknown selection requested. Exiting. " << endl;
      return;
    }
}

bool HEPHero::AnaRegion(){
    bool Selected = true;
    if( _SELECTION == "Test" && !TestRegion() ) Selected = false;
    // SET THE REGION OF YOUR SELECTION HERE

    return Selected;
}

void HEPHero::AnaSelection(){
    if( _SELECTION == "Test" ) TestSelection();
    // CALL YOUR SELECTION HERE
}

void HEPHero::AnaSystematic(){
    if( _SELECTION == "Test" ) TestSystematic();
    // PRODUCE THE SYSTEMATIC OF YOUR SELECTION HERE
}

void HEPHero::FinishAna(){
    if( _SELECTION == "Test" ) FinishTest();
    // FINISH YOUR SELECTION HERE
}
   
