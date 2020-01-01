/**
 * @file mmi_mae_logdb_types.h
 *
 * @version $Id: mmi_mae_logdb_types.h $
 */
#ifndef __MMI_MAE_LOGDB_TYPES_H__
#define __MMI_MAE_LOGDB_TYPES_H__
/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LOGDB_NLID_SIZE									(sizeof(u32))
#define LOGDB_NLOGTIME_SIZE								(sizeof(u32))
#define LOGDB_NLOGTYPE_SIZE								(sizeof(u8))
#define LOGDB_NLOGCONTENT_SIZE							(sizeof(u32))
#define LOGDB_PLOGSTRPARAM_SIZE							((sizeof(MAE_WChar))*100)

#define LOGDB_RECORD_SIZE	(LOGDB_NLID_SIZE+LOGDB_NLOGTIME_SIZE+LOGDB_NLOGTYPE_SIZE+LOGDB_NLOGCONTENT_SIZE+LOGDB_PLOGSTRPARAM_SIZE)

#define LOGDB_COLUMN_NUM								5
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------*/
#define MAE_RET_LOGDB_BASE 0x0800
enum {

    MAE_RET_LOGDB_NOMOREITEM = (MAE_RET_LOGDB_BASE + 1),
};

/*-------------------------------------------------------------------------*/
#define LOGDBATTR_BASE  3900

enum
{
    LOGDBATTR_LID = LOGDBATTR_BASE,
    LOGDBATTR_LOGDBTIME,
    LOGDBATTR_LOGDBTYPE,
    LOGDBATTR_LOGDBCONTENT,
	LOGDBATTR_LOGDBSTRPARAM,
	LOGDBATTR_MAX
};

struct MAELogdb_t_
{
	struct MAELogdb_t_ *pPre;		/**< (internal usage) Pointer to previous MAELogdb instance */
	struct MAELogdb_t_ *pNext;		/**< (internal usage) Pointer to next MAELogdb instance */

	u32 nLogTime;				/**< timestamp of this log record */
	u8 nLogType;					/**< type of log */
    u32 nLogContent;				/**< Text Label ID for this log message */
	u32 nLID;					/**< Unique ID, PRIMIARY KEY */
	MAE_WChar *pLogStrParam;		/**< String param for this text label */
};

#endif /* __MMI_MAE_LOGDB_TYPES_H__ */

