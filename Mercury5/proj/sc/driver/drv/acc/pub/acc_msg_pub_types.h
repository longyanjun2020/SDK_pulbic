#ifndef __ACC_MSG_PUB_TYPES_H__
#define __ACC_MSG_PUB_TYPES_H__

#include "vm_types.ht"
#include "acc_msg_pub_forward.h"
#include "dev_acc_pub_types.h"		/* For DEV_ACC_LAST_EXT_MSG */

/**
 * \brief Definition of components which are handled by ACC
 * \Note! The order must be the same as the definition of CompPattern[] in acc_task.c
 */
enum
{
	ACC_VIB,
	ACC_KPD_LED,
	ACC_MAIN_DISP_BL,
	ACC_COMP_NUM        /* Shall not be larger than 255 (u8) */
};

/**
 * \brief ACC messages types
 */
opaque_enum(MSG_TYPE_ACC_)
{
 	DEV_ACC_PLUG_DETECTED = DEV_ACC_LAST_EXT_MSG,  
	DEV_ACC_COMP_SWITCH,
	DEV_ACC_COMP_REPEAT,
    DEV_FM_TUNER_REQ,
    DEV_FM_TUNER_CNF,
    DEV_ACC_LAST_INT_MSG,
    DEV_EM_MENU_REQ,
    DEV_FACTORY_DEFAULT_REQ,
    DEV_CLEAR_PASSWORD_REQ
};

struct dev_sw_toolInfo_S_
{
	u8 * toolHeader;
	u8 * toolVersion;
};


/**
 * \brief Structure used in \ref DEV_ACC_COMP_SWITCH message
 * 
 */
 #if 0
typedef struct
{
	u8  component;
	u8  pad[3];
	//Douglas
	dev_accBacklightLevel_t  level;
	//Douglas
} dev_accComponentSwitch_t;  
#endif

/**
 * \brief Structure used in \ref DEV_ACC_COMP_REPEAT message
 * 
 */
 #if 0
typedef struct
{
	u8  component;
	u32 on_time;
	u32 off_time;
	u32 total_time;
	//Douglas
	dev_accBacklightLevel_t  on_level;
  dev_accBacklightLevel_t  off_level;
	dev_accBacklightLevel_t  org_level;
	//Douglas
} dev_accComponentRepeat_t;
#endif

#if 0
/**
 * \brief Union of all messages received or sent by ACC
*/
typedef union
{
    vm_osTimerMsgBody_t        	vm_osTimerMsgBody;       
    dev_accPlugInd_t		        dev_accPlugInd;
    //dev_accComponentSwitch_t    dev_accCompSwitch;
    //dev_accComponentRepeat_t	  dev_accCompRepeat;
    //dev_accPlugDetect_t					dev_accPlugDetect;
#ifndef __SDK_SIMULATION__
    api_atCmdPreParser_t        AT_CmdPreParserInd;
#endif
} Body_t;
#include "stdmsg.ht"  /* For MSG header and body definition. It must be put after def of Body_t */
#endif

#endif /* __ACC_MSG_PUB_TYPES_H__ */
