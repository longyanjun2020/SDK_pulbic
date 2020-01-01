//==============================================================================
//
//  File        : AHC_VersionEx.c
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "isp_if.h"
#include "ahc_version.h"
#include "ahc_parameter.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define AIT_CHIP_VERSION     	    0x80008CEC 
#define AIT_CHIP_MODEL_VERSION	    0x80008CF0
#define AIT_CHIP_ECO_VERSION	    0x80008CFD

#define CHIP_MODEL_STRING_LENGTH    (12)

/*===========================================================================
 * Main body
 *===========================================================================*/ 

//------------------------------------------------------------------------------
//  Function    : AHC_GetHwVersion
//  Description : 
//------------------------------------------------------------------------------
void AHC_GetHwVersion(BYTE* pbyChipVersion, BYTE* pbyEcoVersion, BYTE* pbyModel)
{	
    int i;
	BYTE* pChipVersionId = (BYTE*)AIT_CHIP_VERSION;
	BYTE* pChipEcoId     = (BYTE*)AIT_CHIP_ECO_VERSION;
	BYTE* pModelId       = (BYTE*)AIT_CHIP_MODEL_VERSION;

	*pbyChipVersion  =  *pChipVersionId;
	*pbyEcoVersion   =  *pChipEcoId;

	for (i = 0; i < CHIP_MODEL_STRING_LENGTH; i++) {
		*pbyModel++  = *pModelId++;
	}
}

//------------------------------------------------------------------------------
//  Function    : AHC_PrintIspLibVersion
//  Description : 
//------------------------------------------------------------------------------
void AHC_PrintIspLibVersion( void )
{
	printc("ISP version: %x.%x ", 	ISP_IF_LIB_GetLibVer().MajorVer,
					   				ISP_IF_LIB_GetLibVer().MinorVer);

	printc("(%x.%x) ", 	ISP_IF_LIB_GetLibVer().InnerVer0,
					    ISP_IF_LIB_GetLibVer().InnerVer1);

	printc(" - %d/%d/%d \n", 	ISP_IF_LIB_GetLibVer().Year,
					        	ISP_IF_LIB_GetLibVer().Month, 
					        	ISP_IF_LIB_GetLibVer().Day);
}

//------------------------------------------------------------------------------
//  Function    : AHC_PrintFwVersion
//  Description : 
//------------------------------------------------------------------------------
void AHC_PrintFwVersion(void)
{
    UINT16 ulMajorVersion;
    UINT16 ulMediumVersion;
    UINT16 ulMinorVersion;
    UINT16 ulBranchVersion;
    UINT16 ulTestVersion;
    char*  szReleaseName = 0;
	UINT32 uiBoardtype;
	BYTE   byChipVer;
	BYTE   byEcoVer;
    BYTE   byModelId[CHIP_MODEL_STRING_LENGTH+1] = {0};

	printc("------------------------------------------\n");

    //AHC_GetHwVersion(&byChipVer, &byEcoVer, byModelId);
    //printc("Model:%s  - HW version: %02X ECO %02X\n", byModelId, byChipVer, byEcoVer);
    
    AHC_GetFwVersion(&ulMajorVersion, &ulMediumVersion, &ulMinorVersion, &ulBranchVersion, &ulTestVersion, &szReleaseName);
    printc("FW version : %04X.%04X.%04X\n - BRANCH : %04X  TEST : %04X\n", ulMajorVersion, ulMediumVersion, ulMinorVersion, ulBranchVersion, ulTestVersion);

	AHC_PrintIspLibVersion();
    printc("Release: %s\n", szReleaseName);

	//AHC_GetParam(PARAM_ID_MAINBOARD_TYPE, &uiBoardtype);
	//printc("Board Type: %d\n", uiBoardtype);

	printc("------------------------------------------\n");
}

//------------------------------------------------------------------------------
//  Function    : AHC_PrintBuildTime
//  Description : 
//------------------------------------------------------------------------------
void AHC_PrintBuildTime(void)
{
	printc("\n");
	printc("------------------------------------------\n");
    printc("Build Time - %s  %s  \n", __DATE__,__TIME__); 
}
