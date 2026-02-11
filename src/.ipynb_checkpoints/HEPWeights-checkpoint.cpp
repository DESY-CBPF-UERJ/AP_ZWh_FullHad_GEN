#include "HEPHero.h"


//-------------------------------------------------------------------------------------------------
// Weight corrections
//-------------------------------------------------------------------------------------------------
void HEPHero::Weight_corrections(){

    //pileup_wgt = 1.;

    if(dataset_group != "Data"){

        /*
        if( apply_pileup_wgt ){
            pileup_wgt = GetPileupWeight(Pileup_nTrueInt, "nominal");
            evtWeight *= pileup_wgt;
        }
        */
    }

}


//-------------------------------------------------------------------------------------------------
// Pileup Correction
// Return weight associated to the pileup effect
//-------------------------------------------------------------------------------------------------
//float HEPHero::GetPileupWeight( float Pileup_nTrueInt, string sysType ){
//
//    double pileup_weight = 1.;
//    pileup_weight = pileup_corr->evaluate({Pileup_nTrueInt, sysType});
//
//    return pileup_weight;
//}
