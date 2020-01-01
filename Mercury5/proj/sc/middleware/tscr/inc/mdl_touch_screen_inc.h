


/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MAX_PRESS_COUNT ((600 + _gnPollingTime - 1)/_gnPollingTime)
#define TS_IDLE                  0



/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef union
{
    vm_osTimerMsgBody_t    TimerMsg;
    MdlTouchScreenData_t   tsData;
    MdlTouchScreenInfo_t   tsInfo;
    MdlTouchScreenFwUpdate_t tsfwupdate;
    DrvAbbAdcResults_t     adcResults;
    MdlTscrPowerSwitch_e tsPowerSwitch;
}vm_msgBody_t;

#include "vm_msgt.ht"


typedef struct
{
	u16    x;
	u16    y;
} MTPoint_t;



/*=============================================================*/
// Variable definition
/*=============================================================*/
extern u32 _gnXResistance;
extern u32 _gYResistance;

extern u32 _gnXtemp1, _gnYtemp1;
extern u32 _gnXtemp2, _gnYtemp2;

extern u32 _gnZ1Location;
extern u32 _gnZ2Location;


extern u8  _gncurrentAdcJob;

extern u32 _gbTSState;

extern u32 _gnPollingTime;

extern u16 TOUCH_TRACE_FLAG;


extern void MdlTouchScreenStatusReport(MdlTouchScreenInfo_t TscrInfo);
extern void MdlMultiTouchGetCurve(void);
extern MdlTsRetCode_e MdlMultiTouchRecognize(vm_msg_t *ptMsg);
extern void MdlMultiTouchSetPollingTime(u32 _gnPollingTime);




