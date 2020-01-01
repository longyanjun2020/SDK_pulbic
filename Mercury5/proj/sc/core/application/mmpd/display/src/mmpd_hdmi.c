
#ifdef BUILD_CE
#undef BUILD_FW
#endif

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_display.h"
#include "mmpf_display.h"

/** @addtogroup MMPD_Display
 *  @{
 */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void ____HDMI_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_Display_SetHDMIOutput
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR MMPD_Display_SetHDMIOutput(	MMP_DISPLAY_CONTROLLER 	controller, 
									MMP_HDMI_ATTR 	*hdmiAttr, 
									MMP_DISPLAY_RGB_IF 		rgbIf)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_HDMI_DisableHDMI
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_HDMI_DisableHDMI(MMP_DISPLAY_RGB_IF ubRgbIf)
{
    return MMP_ERR_NONE;
}

#if defined(ALL_FW)
//------------------------------------------------------------------------------
//  Function    : MMPD_HDMI_InitAnalog
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_HDMI_InitAnalog(MMP_HDMI_ATTR *hdmiattribute)
{
    return MMP_ERR_NONE;
}

const MMP_HDMI_OUTPUT_MODE HDMIVideoTable[128] =
{
    0,
    MMP_HDMI_OUTPUT_640X480P,
    MMP_HDMI_OUTPUT_720X480P,
    MMP_HDMI_OUTPUT_720X480P,
    MMP_HDMI_OUTPUT_1280X720P,
    MMP_HDMI_OUTPUT_1920X1080I,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    //10
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,//MMP_HDMI_OUTPUT_1920X1080P, // 16
    MMP_HDMI_OUTPUT_720X576P,
    MMP_HDMI_OUTPUT_720X576P,
    MMP_HDMI_OUTPUT_1280X720P_50FPS, // 19
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_UNSUPPORT,
    MMP_HDMI_OUTPUT_1920X1080P_30FPS,
    0
};

//------------------------------------------------------------------------------
//  Function    : MMPD_HDMI_ParseEDID
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_HDMI_ParseEDID(MMP_UBYTE *pEDID, MMP_ULONG *pSpportFormat, MMP_ULONG *pEDIDType)
{
    MMP_USHORT i = 0, d = 0, Len = 0, j = 0;
    MMP_UBYTE revnum;
    
    *pEDIDType = pEDID[0];
    
    switch(pEDID[0]) {
    case 0x00:
        break;
    case 0x02: // Extend timing block
        revnum = pEDID[1];
        d = pEDID[2];
        i = 4;
        while(1) {
            if(i >= d)
                break;
            if((pEDID[i] & 0xE0) == 0x40) {
                Len = pEDID[i] & 0x1F;
                for(j = 1; j <= Len; j++) {
                    //VAR_L(0, pEDID[i+j]);
                    *pSpportFormat |= HDMIVideoTable[pEDID[i+j] & 0x7F];
                }
                break;
            } else {
                i += (pEDID[i] & 0x1F) + 1;
            }
        }
        break;
    default:
        break;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_HDMI_InitDigital
//  Description :
// AVI info frame
/*
AVI info frame field
===============================
         bit7                    bit0
BYTE 1   F17=0|Y1|Y0|A0|B1|B0|S1|S0              
===============================
Y1  Y0          RGB or YCbCr
0   0           RGB
0   1           YCbCr 4:2:2
1   0           YCbCr 4:4:4
1   1           Future

A0              Active Format Info Present
0               no data
===============================
         bit7                 bit0
BYTE 2   C1|C0|M1|M0|R3|R2|R1|R0       
===============================
C1  C0          Colorimetry
0   0           no data
0   1           SMPTE 170M  ITU601
1   0           ITU709
1   1           Extended Colorimetry

M1  M0          Picture Aspect Ratio
0   0           no data
0   1           4:3
1   0           16:9
1   1           Future

R3  R2  R1  R0  Active Format Aspect Ratio
1   0   0   0   same as picture aspect ratio
1   0   0   1   4:3(center)
1   0   1   0   16:9(center)
1   0   1   1   14:9(center)
===============================
         bit7                      bit0
BYTE 3   ITC|EC2|EC1|EC0|Q1|Q0|SC1|SC0
===============================
ITC             IT Content
0               no data
1               IT content

EC2 EC1 EC0     Extended Colorimetry
0   0   0       xvYCC601
0   0   1       xvYCC709

Q1  Q0          RGB Quantization Range
0   0           Default(depends on video format)
0   1           Limited Range
1   0           Full Range
1   1           Reserved        
*/
//------------------------------------------------------------------------------
MMP_ERR MMPD_HDMI_InitDigital(MMP_HDMI_ATTR *hdmiattribute)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_HDMI_Initialize
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_HDMI_Initialize(MMP_HDMI_ATTR *hdmiattribute, MMP_DISPLAY_RGB_IF rgbIf)
{
    return MMP_ERR_NONE;
}
#endif//(ALL_FW)

/// @}

#ifdef BUILD_CE
#define BUILD_FW
#endif
