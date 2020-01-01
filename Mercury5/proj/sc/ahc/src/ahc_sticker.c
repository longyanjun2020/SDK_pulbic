/**
 @file ahc_sticker.c
 @brief ahc sticker control Function
 @author 
 @version 1.0
*/
/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_sticker.h"
#include "ahc_capture.h"
#include "ahc_utility.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

/*===========================================================================
 * Extern function
 *===========================================================================*/ 

/*===========================================================================
 * Main body
 *===========================================================================*/ 

#if 0
void _____Sticker_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_STICKER_TransDateToString
//  Description : Transfer pstRtcTime(int) to pbyDate(string)
//------------------------------------------------------------------------------
AHC_BOOL AHC_STICKER_TransDateToString(AHC_RTC_TIME* pstRtcTime, INT8* pbyDate, UINT8 byDateConfig, UINT8 byFormatConfig)
{
    AHC_TIME_STRING sTimeString;

    AHC_Utility_Int2Str(pstRtcTime->uwYear,     sTimeString.byYear);
    AHC_Utility_Int2Str(pstRtcTime->uwMonth,    sTimeString.byMonth);
    AHC_Utility_Int2Str(pstRtcTime->uwDay,      sTimeString.byDay);
    AHC_Utility_Int2Str(pstRtcTime->uwHour,     sTimeString.byHour);
    AHC_Utility_Int2Str(pstRtcTime->uwMinute,   sTimeString.byMinute);
    AHC_Utility_Int2Str(pstRtcTime->uwSecond,   sTimeString.bySecond);

    if (AHC_ACC_TIMESTAMP_TIME_ONLY != byDateConfig) {

        if (byFormatConfig == AHC_ACC_TIMESTAMP_FORMAT_1) {

            STRCPY(pbyDate, sTimeString.byYear);
            STRCAT(pbyDate, " ");

            if (pstRtcTime->uwMonth < 10)
                STRCAT(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byMonth);
            STRCAT(pbyDate, " ");

            if (pstRtcTime->uwDay < 10)
                STRCAT(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byDay);
        }
        else if (byFormatConfig == AHC_ACC_TIMESTAMP_FORMAT_2) {
            
            STRCPY(pbyDate, sTimeString.byYear);
            STRCAT(pbyDate, "/");

            if (pstRtcTime->uwMonth < 10)
                STRCAT(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byMonth);
            STRCAT(pbyDate, "/");

            if (pstRtcTime->uwDay < 10)
                STRCAT(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byDay);
        }
        else if (byFormatConfig == AHC_ACC_TIMESTAMP_FORMAT_3) {

            if (pstRtcTime->uwDay < 10)
                STRCPY(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byDay);
            STRCAT(pbyDate, "/");

            if (pstRtcTime->uwMonth < 10)
                STRCAT(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byMonth);
            STRCAT(pbyDate, "/");
            STRCAT(pbyDate, sTimeString.byYear);
        }
        else if (byFormatConfig == AHC_ACC_TIMESTAMP_FORMAT_4) {

            if (pstRtcTime->uwMonth < 10)
                STRCPY(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byMonth);
            STRCAT(pbyDate, "/");

            if (pstRtcTime->uwDay < 10)
                STRCAT(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byDay);
            STRCAT(pbyDate, "/");
            STRCAT(pbyDate, sTimeString.byYear);
        }

        if (AHC_ACC_TIMESTAMP_DATE_AND_TIME == (byDateConfig & AHC_ACC_TIMESTAMP_DATE_MASK)) {

            STRCAT(pbyDate, " ");

            if (pstRtcTime->uwHour < 10)
                STRCAT(pbyDate, "0");

            STRCAT(pbyDate, sTimeString.byHour);
            STRCAT(pbyDate, ":");

            if (pstRtcTime->uwMinute < 10)
                STRCAT(pbyDate,"0");

            STRCAT(pbyDate, sTimeString.byMinute);
            STRCAT(pbyDate, ":");

            if (pstRtcTime->uwSecond < 10)
                STRCAT(pbyDate,"0");

            STRCAT(pbyDate, sTimeString.bySecond);
        }
    }
    else {
        if (pstRtcTime->uwHour < 10) {
            STRCPY(pbyDate, "0");
            STRCAT(pbyDate, sTimeString.byHour);
        }
        else {
            STRCPY(pbyDate, sTimeString.byHour);
        }

        STRCAT(pbyDate, ":");

        if (pstRtcTime->uwMinute < 10)
            STRCAT(pbyDate, "0");

        STRCAT(pbyDate, sTimeString.byMinute);
        STRCAT(pbyDate, ":");

        if (pstRtcTime->uwSecond < 10)
            STRCAT(pbyDate, "0");

        STRCAT(pbyDate, sTimeString.bySecond);
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_STICKER_DrawTextEdge
//  Description :
//------------------------------------------------------------------------------
void AHC_STICKER_DrawTextEdge(UINT32 uiSrcAddr, UINT16 uwSrcW, UINT16 uwSrcH, UBYTE TextColor, UBYTE BGColor, UBYTE EdgeColor)
{
#if (STICKER_DRAW_EDGE)

    UINT16 x,y;
    MMP_UBYTE *Addr = (MMP_UBYTE *)uiSrcAddr;

    for (y = 1; y < uwSrcH-1; y++) {
        for (x = 1; x < uwSrcW-1; x++) {

            if (Addr[y*uwSrcW+x] == BGColor) {
                if ((Addr[(y-1)*uwSrcW+(x-1)] == TextColor) || 
                    (Addr[(y-1)*uwSrcW+x] == TextColor) || 
                    (Addr[(y-1)*uwSrcW+(x+1)] == TextColor) || \
                    (Addr[y*uwSrcW+(x-1)] == TextColor) || 
                    (Addr[y*uwSrcW+(x+1)] == TextColor) || \
                    (Addr[(y+1)*uwSrcW+(x-1)] == TextColor) || 
                    (Addr[(y+1)*uwSrcW+x] == TextColor) || 
                    (Addr[(y+1)*uwSrcW+(x+1)] == TextColor))
                   
                   Addr[y*uwSrcW+x] = EdgeColor;
            }
        }
    }
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_STICKER_TransRGB565toIndex8
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_STICKER_TransRGB565toIndex8(UINT32 uiSrcAddr,
                                         UINT32 uiSrcW,
                                         UINT32 uiSrcH,
                                         UINT32 uiDestAddr,
                                         UINT32 uiDestW,
                                         UINT32 uiDestH,
                                         UINT8  byForegroundColor,
                                         UINT8  byBackgroundColor)
{
    UINT16  *puwSrcBuf;
    UINT8   *pbyDestBuf;
    UINT32  uiY;
    UINT32  uiX;

    puwSrcBuf   = (UINT16 *)uiSrcAddr;
    pbyDestBuf  = (UINT8 *)uiDestAddr;

    for (uiY = 0; uiY < uiDestH; ++uiY) {

        for (uiX = 0; uiX < uiDestW; ++uiX) {

            *(pbyDestBuf + (uiY * uiDestW) + uiX) =
                (*(puwSrcBuf + (uiY * uiSrcW) + (uiX + (uiSrcW - uiDestW))) != 0) ? byForegroundColor : byBackgroundColor;
        }
    }

    return AHC_TRUE;
}

