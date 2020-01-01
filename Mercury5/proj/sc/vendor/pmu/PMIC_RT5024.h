#include "lib_retina.h"

#define		CH1_4V			(0x40)
#define		CH1_5V			(0xA0)
#define		CH1_MASK		(0x0F)

#define		NO_BATTERY_FLAG					(0x10)
#define		TEMPATURE_0_DEGREE				(0xC0)
#define		TEMPATURE_0_2_10_DEGREE			(0x80)
#define		TEMPATURE_10_2_45_DEGREE		(0x00)
#define		TEMPATURE_45_2_60_DEGREE		(0x20)
#define		TEMPATURE_60__DEGREE			(0x60)
#define		TEMPATURE_OVERHEAT__DEGREE		(0x40)

MMP_ERR		RT5024_ReadReg(MMP_UBYTE ubReg, MMP_USHORT* ubValue);
MMP_ERR		RT5024_WriteReg(MMP_UBYTE ubReg, MMP_USHORT ubValue);
MMP_ERR		RT5024_Initialize(void);
MMP_ERR		RT5024_EnterSuspendMode(void);
MMP_ERR		RT5024_ExitSuspendMode(void);
MMP_ERR		RT5024_DisableCharger(void);
MMP_ERR		RT5024_EnableCharger(void);
MMP_BOOL 	RT5024_ClearINTStatus(void);
MMP_BOOL	RT5024_CheckBatteryStatus(void);
MMP_BOOL	RT5024_CheckBatteryTempatureError(void);
MMP_BOOL	RT5024_CheckBatteryTempatureWarning(void);
MMP_ERR 	RT5024_SetChargerTimer(MMP_UBYTE ubHour);
MMP_UBYTE 	RT5024_GetChargerTimer(void);
MMP_ERR 	RT5024_ChangeCH1(MMP_UBYTE ubCH1Val);