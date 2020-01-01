#ifndef __MMI_COMMON_ON_H__
#define __MMI_COMMON_ON_H__

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
	PowerOnType_Unknow = 0, /* unknow readon. */
	PowerOnType_Normal,  /* Power on by long press END key */
	PowerOnType_Auto,        /* Power on by auto power on alarm expired */
	PowerOnType_Alarm,       /* Power on by an normal alarm expired */
	PowerOnType_Charging,    /* Power on by plugging charger and battery is enough to show animation */
	PowerOnType_Charging_NoAnim,    /* Power on by plugging charger and battery is too low to show animation. Wait battery level is enough to show animation */
	PowerOnType_Powercut,    /* Power on by power cut */
	PowerOnType_ATCommand,    /* Power on by AT command */
	PowerOnType_STKRefresh,	/* Power on by STK refresh */
	PowerOnType_Reset,	/* Power on by Watch dog reset */
	PowerOnType_TimeEvt,	/* Power on by Minute event power on */
	PowerOnType_SWReset,	/* Power on by  Power cut power on */
	PowerOnType_Normal_Key_Release,	/* Power on by KEYON power on but not long press */
	PowerOnType_Others	/* Power on by others */
} PowerOnType_e;

typedef struct
{
	PowerOnType_e eStartType;	//start reason for launching on ap.
	u32 nAlarmEventCode;	//alarm event code for PowerOnType_Auto and PowerOnType_Alarm cases.
} OnAppStart_t;

#endif //__MMI_COMMON_ON_H__
