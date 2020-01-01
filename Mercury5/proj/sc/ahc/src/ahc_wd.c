//==============================================================================
//
//  File        : AHC_WD.c
//  Description : AHC watch dog function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_wd.h"
#include "Customer_config.h"

/*===========================================================================
 * Main body
 *===========================================================================*/ 
#if 0
void ____WatchDog_Function_____(){ruturn;} //dummy
#endif

#if (AIT_HW_WATCHDOG_ENABLE)
//------------------------------------------------------------------------------
//  Function    : AHC_WD_Enable
//  Description :
//------------------------------------------------------------------------------
void AHC_WD_Enable(AHC_BOOL bEnable)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    if (bEnable) {
    
        MMP_ULONG clk_div, CLK_DIV[] = {1024, 128, 32 , 8};
        MMP_ULONG ms;
        MMP_ULONG g0_slow, rst_c, c;

        ms = 4000;
        
        MMPF_PLL_GetGroupFreq(CLK_GRP_GBL, &g0_slow);
        g0_slow = g0_slow / 2;
        
        c = 0;

        printc("ms : %d, G0 slow:%d\r\n",ms, g0_slow);        

        do {
            clk_div = CLK_DIV[c];
            rst_c = (g0_slow * ms) / (clk_div * 16384);
            printc("rst_c : %d,DIV:%d\r\n",rst_c, clk_div);
            c++;
            
            if (c >= 3) {
                printc("%s,%d parameters error!\r\n", __FUNCTION__, __LINE__);
                break ;
            }
        }
        while ((rst_c > 31) || (!rst_c));
                       
        sRet = MMPF_WD_SetTimeOut(rst_c, clk_div);
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return;}    

        sRet = MMPF_WD_EnableWD(MMP_TRUE, MMP_TRUE, MMP_FALSE, NULL, MMP_TRUE); 
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return;}    

        sRet = MMPF_WD_SW_EnableWD(MMP_TRUE, AIT_HW_WATCHDOG_TIMEOUT);
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return;}    
    }
    else {
        sRet = MMPF_WD_EnableWD(MMP_FALSE, MMP_FALSE, MMP_FALSE, NULL, MMP_FALSE);         
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return;}    

        sRet = MMPF_WD_SW_EnableWD(MMP_FALSE, 0);
        if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return;}    
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_WD_Kick
//  Description :
//------------------------------------------------------------------------------
void AHC_WD_Kick(void)
{
    MMPF_WD_SW_Kick();
}
#endif
