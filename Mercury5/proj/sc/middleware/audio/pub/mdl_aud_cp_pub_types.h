#ifndef __MDL_AUD_CP_PUB_TYPES_H__
#define __MDL_AUD_CP_PUB_TYPES_H__

#include "mdl_aud_forward.h"
#include "mdl_aud_cp_pub_api.h"

// mdl_aud_cp_pub_api.h
/**
 *  @brief Callback informatoin structure supported for middleware
 */
struct Mdl_AudNotifyCb_t_{
	u8               bufferID;   /**< Buffer ID */
	MdlAudCPCbFn_t    pfnCpCb;    /**< Call back function that called by Media task after receiving the notification. */
};

/**
 *  @brief The structure defines the register Cut point callback command
 */
struct MdlAudCpRegCallback_t_
{
    MdlAudCPCbFn_t  tCpCbFn;
};

struct MdlAudCpBufferId_t_
{
    u8              bufferId;
};


struct MdlAudCpData_t_{
  u32 nDataAddr;
  u32 nDataSize;
};


struct MdlAudCpInDataInfo_t_{
  MdlAudCpData_t     tCpDlRawDataInfo;       /**< Downlink raw data */
  MdlAudCpData_t     tCpUlRawDataInfo;       /**< Uplink raw data */
  MdlAudCpData_t     tCpAmrRecordDataInfo;   /**< Amr recording data */
  MdlAudCpData_t     tCpAmrEncodeDataInfo;   /**< Amr encode data */
};


struct MdlAudCpOutDataInfo_t_{
  MdlAudCpData_t     tCpDlOutDataInfo;       /**< Downlink output data */
  MdlAudCpData_t     tCpAmrDecodeDataInfo;   /**< Amr decode data */
};


struct MdlAudCPDataInfo_t_{
  MdlAudCpData_t       tCpInputData;
  MdlAudCpData_t      tCpOutputData;
};
// end mdl_aud_cp_pub_api.h


#endif // __MDL_AUD_CP_PUB_TYPES_H__

