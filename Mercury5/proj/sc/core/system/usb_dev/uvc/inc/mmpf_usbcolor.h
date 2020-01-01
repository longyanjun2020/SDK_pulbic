#ifndef COLOR_H
#define COLOR_H

// PU Range : 
#define SAT_MIN (  0)//(0x0000)
#define SAT_MAX (255)//(0x007F)
#define SAT_DEF (128)//(0x0040)

#define CON_MIN (  0)//(0x0000)
#define CON_MAX (255)//(0x007F)//(0x7F)
#define CON_DEF (128)//(0x0040)

#define BRI_MIN (  0)//(0x0000)//(0xFFF6)//(0xFF81)
#define BRI_MAX (255)//(0x0013)//(0x007F)
#define BRI_DEF (128)//(0x000A)

#define HUE_MIN (  0)//(0xFF4C)
#define HUE_MAX (255)//(0x00B4)
#define HUE_DEF (128)//(0x0000)

#define GAM_MIN (  1)//(0x0001) // 0->1 , UVC test pass
#define GAM_MAX (255)//(0x00C8)
#define GAM_DEF (128)//(0x0064)

#define BLC_MIN (  0)
#define BLC_MAX (  1)
#define BLC_DEF (  0)

#define SHA_MIN (  0)//(0x0000)
#define SHA_MAX (255)//(0x0008)
#define SHA_DEF (128)//(0x0004)

#define EPV_MIN (0x0026)
#define EPV_MAX (0x00D6)
#define EPV_DEF (0x005A)

#define WBT_MIN (0x0AF0)//(0x0000)// 
#define WBT_MAX (0x1964)//(0x000A)//
#define WBT_DEF (0x16A8)//(0x0000)//

#define GAIN_DEF (0)
#define GAIN_MIN (0  )
#define GAIN_MAX (255)


// Set Logical zoom range from 0 ~ 10
#define ZOM_MIN (0x0000) 
#define ZOM_MAX (0x000A)
#define ZOM_DEF (0x0000)

#define PANTILT_RES (3600)

#define PAN_MIN (-10 * PANTILT_RES)
#define PAN_MAX ( 10 * PANTILT_RES)
#define PAN_DEF ( 0  )

#define TILT_MIN (-10 * PANTILT_RES)
#define TILT_MAX ( 10 * PANTILT_RES)
#define TILT_DEF (  0 * PANTILT_RES)


#define AAF_MIN (0x0000) //absolute focus
#define AAF_MAX (0x00FF)//(0x0064) //(0x00FF)
#define AAF_DEF (0x0000) //(0x0080)

#define AUTOAF_MIN (0x0000) //auto focus
#define AUTOAF_MAX (0x0001)
#define AUTOAF_DEF (0x0001)

#define AWB_DEF (0x01)
#define AWB_MIN (0x00)
#define AWB_MAX (0x01)

#define BAND_DEF BAND_60HZ

void Set_Saturation(MMP_UBYTE value);
void Set_Contrast(MMP_UBYTE value);
void Set_Brightness(MMP_SHORT value);
void Set_Hue(MMP_SHORT value);
void Set_Gamma(MMP_SHORT value);
void Set_Backlight(MMP_UBYTE value);
void Set_Sharpness(MMP_BYTE value);
void Set_PowerLineFreq(MMP_UBYTE value);
void Set_AWBTemp(MMP_USHORT value);
void Set_LensPosition(MMP_USHORT pos);
void Set_AutoFocusControl(MMP_BOOL Enable);
#endif