/*
 * iq_utility.h
 *
 *  Created on: 2016/1/6
 *      Author: Cue.hu
 */

#ifndef __iq_utility__
#define __iq_utility__

#define MAX_STS_WIDTH_IQ           (16)    //AE statistic size after down scale from ACC
#define MAX_STS_HEIGHT_IQ          (16)

void pAE_CalLumY_AfterGamma(IqInput_t *IqInput, IQ_GAMA_C2A_SC_CFG* strIQGamma, IQ_DLC_CFG* strIQDLC, MS_U16* u4LumY_OUT, MS_U16 u4NumX, MS_U16 u4NumY);
void pCal_FourBinHist(MS_U16* u4LumY_In, MS_U16* Histogram_Out, MS_U16 u4NumX, MS_U16 u4NumY);
void pCal_shade_target(MS_U16* u4LumY_In, MS_U16* Histogram_In, MS_U16 Curve[4][5], MS_U16* wdr_shade_tar_Out, MS_U16* tmp_max_wdr_shade_gain_Out, MS_U16 u4NumX, MS_U16 u4NumY);
void ExtendData(MS_U16* Table_In, MS_U16* Table_Out, MS_U16 OriNumX, MS_U16 OriNumY);
void GenWDRLocalTargetAndGainTbl(IqInput_t *IqInput, IQ_GAMA_C2A_SC_CFG* strIQGamma, IQ_DLC_CFG* strIQDLC, IQ_WDR_LOC_CFG* strIQWdrLoc);
//void LOC_WDR_CopyGainAndTargetTblToHWFormat(MS_U16* tbl_WDR, MS_U16* wdr_shade_tar_In, MS_U16* wdr_shade_gain_In);
void LOC_WDR_CopyGainAndTargetTblToHWFormat(MS_U16* tbl_WDR_1, MS_U16* tbl_WDR_2, MS_U16* wdr_shade_tar_In, MS_U16* wdr_shade_gain_In);


#endif /* __iq_utility__ */
