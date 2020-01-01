/**
 * \file    mmi_mae_config_types.h
 * \brief   
 *
 * @version
 */

#ifndef __MMI_MAE_CONFIG_TYPES_H__
#define __MMI_MAE_CONFIG_TYPES_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_clstbl.h"
#include "mmi_mae_forward.h"

/* enum for MAECfgCategory_t */
enum MAECfgCategory_t_
{
    MAECFGCAT_SYSTEM = 0,
    //Paul
    //	MAECFGCAT_INPUT,
    //#ifdef __TOUCH_SCREEN_MMI__
    //#ifdef __HANDWRITING_MMI__
    //	MAECFGCAT_HANDWRITING,
    //#endif
    //#endif
    MAECFGCAT_SUM
};

/* enum for MAECfgItemId_t of MAECFGCAT_SYSTEM */
enum MAECfgItemId_t_
{
    MAECFGSYS_ID_LANGUAGE = (CLSID_CONFIG << 16 | 0),	///< MAE_LANG_CODE_e(u8), see mmi_mae_langcode.h for reference

    MAECFGSYS_ID_DBGINFO_MEMSTATUS,						///< boolean, TRUE/FALSE : on/off
    MAECFGSYS_ID_DBGINFO_UPDATEINDICATION,       		///< boolean, TRUE/FALSE : on/off
    MAECFGSYS_ID_DBGINFO_UPDATETIME,						///< boolean, TRUE/FALSE : on/off

    MAECFGSYS_ID_OSDSTAT_MAINDISP,                   	///< boolean, TRUE/FALSE : on/off
    MAECFGSYS_ID_OSDSTAT_SUBDISP,                    	///< boolean, TRUE/FALSE : on/off

    MAECFGSYS_ID_MOTION_DETECTOR_STAT,			///< boolean, TRUE/FALSE : on/off

    //========== Add ID before this line ===========//
    MAECFGSYS_ID_SUM
};

enum
{
    SYS_DBGINFOID_MEMSTATUS,
    SYS_DBGINFOID_UPDATEINDICATION,
    SYS_DBGINFOID_SUM
};

struct ConfigListener_t_
{
	PfnCfgListener   pCfgListener;	///< a call back function with PFNCFGLISTENER prototype
	void             *pUsrData;			///< a context data pointer to pass into callback function
	u32               nMask;				///< the mask of the interested items
	ICONFIG          *pConfig;          ///< a IConfig pointer to indicate which IConfig this listener belongs to
	ConfigListener_t *pNext;			///< next listener structure
};


#endif /* __MMI_MAE_CONFIG_TYPES_H__ */

