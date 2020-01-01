#ifndef _MMPF_IRDA_H_
#define _MMPF_IRDA_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_SUPPORT_CMD_SET     (2)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMPF_IRDA_CMD {

    MMP_UBYTE   ubNumOfStartBit;
    MMP_UBYTE   ubNumOfDataBit;
    MMP_UBYTE   ubBitModeSel[8];    // 7 Start Bit + 1 Data Bit
    MMP_USHORT  usMode1StartBitLen; // Unit:us
    MMP_USHORT  usMode1Log1LevelLen;// Unit:us
    MMP_USHORT  usMode1CompRange;
    MMP_USHORT  usMode1DiffLevel;   // High or Low
    MMP_USHORT  usMode0DataPeriod;  // Unit:us
    MMP_USHORT  usMode0LatchFac;    // Unit:us
    
    void*       pCBFunc;            // Callback function for parsing data

} MMPF_IRDA_CMD;

typedef struct _MMPF_IRDA_ATTR {
    MMP_BOOL    bInDataInvEn;
    MMP_BOOL    bStartBitH2L;
    MMP_BOOL    bInDataMsbFirst;
    MMP_BOOL    bData2FIFOInvEn;
    MMP_ULONG   ulIrdaClk;          // Unit:Hz
    
    MMPF_IRDA_CMD* pCmdAttr[2];
} MMPF_IRDA_ATTR;

typedef void IrdaCallBackFunc(MMP_ULONG, MMP_ULONG);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void MMPF_IRDA_ISR(void);
MMP_ERR MMPF_IRDA_Initialize(void);
void MMPF_IRDA_PADSetting(void);
MMP_ERR MMPF_IRDA_SetCmdAttribute(MMPF_IRDA_ATTR* pAttr);
MMP_ERR MMPF_IRDA_GetCmdAttribute(MMPF_IRDA_ATTR* pAttr);
MMP_ERR MMPF_IRDA_EnableRx(MMP_BOOL bEnable);

#endif //_MMPF_IRDA_H_