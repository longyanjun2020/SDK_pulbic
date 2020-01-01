/**
 *
 * @file    ven_util.h
 * @brief   This file defines utility funtions
 *
 * @author Ming.Chen
 * @version $Id$
 *
 */
#ifndef __VEN_UTIL_H__
#define __VEN_UTIL_H__


#include "ven_sdk.h"
#ifdef __3G_RIL_MMI__
#include "ven_comdef_priv.h"
#endif //#ifdef __3G_RIL_MMI__
#include "mdl_vm_rai_id.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

#define VEN_IMSI_SIZE   16
#define VEN_IMEI_SIZE   16
#define VEN_NBMAX_NEAR  6

#define VEN_FS_RAI_BASE_ID 	VEN_FS_RAI_START_ID
#define VEN_UTIL_RAI_SIZE_MAX ( 30 * 1024 ) //30k bytes is the max size of each RAI object.
//raiCategory is one of ven_util_rai_id_category_e
#define VEN_UTIL_RAI_START_ID( raiCategory ) raiCategory##_START = ( VEN_FS_RAI_BASE_ID + ((raiCategory & 0x000000FF) << 16) )
#define VEN_UTIL_RAI_END_ID( raiCategory )   raiCategory##_END

typedef u32 ven_util_raiId_t;

typedef struct
{
	u16 size;
}ven_util_raiInfo_t;

typedef enum
{
	//add your RAI ID category, then add	VEN_UTIL_RAI_START_ID(your RAI ID category) in front of your RAI ID enum.
	//please reference VEN_UTIL_RAI_START_ID(VEN_UTIL_RAI_SDKTEST) in sdkven_example.c
	VEN_UTIL_RAI_SDKTEST = 0,
#ifdef __COOL_BAR__
	VEN_UTIL_RAI_COOLBAR,
#endif
}ven_util_rai_id_category_e;

typedef u8  ven_Imsi_t [VEN_IMSI_SIZE];
typedef u8  ven_Imei_t [VEN_IMEI_SIZE];

enum
{
    VEN_UTIL_RET_SUCCESS            = 0, ///< operation completed successfully
    VEN_UTIL_RET_BAD_PARAM          = 1, ///< invalid input parameters
    VEN_UTIL_RET_FAILED             = 2, ///< WHAT? every code here is failed
    VEN_UTIL_RET_OUT_MOMORY         = 3,
    VEN_UTIL_RET_BUSY               = 4,
    VEN_UTIL_RET_OUT_OF_SIZE,
};
typedef s32 ven_util_ret_t;


#ifdef __3G_RIL_MMI__
typedef enum
{
    VEN_UTIL_CELL_ONE_SHOT = 0
   ,VEN_UTIL_CELL_AUTO_SHOT
   ,VEN_UTIL_CELL_STOP_AUTO

} ven_util_CellMode_e;

typedef enum
{
    VEN_UTIL_CELL_DUMP_MAIN_CELL_ONLY = 1
,     //Main Cell only
    VEN_UTIL_CELL_DUMP_NEI_ALL = 2
,                //Neighbours 1 to 6
    VEN_UTIL_CELL_DUMP_MAIN_NEI_ALL = 3
,           //Main Cell then Neighbours 1 to 6
    VEN_UTIL_CELL_DUMP_TA = 4
,                 //Main Cell Timing Advance
    VEN_UTIL_CELL_DUMP_MAIN_TA = 5
,                //Main Cell, then Timing Advance
    VEN_UTIL_CELL_DUMP_6 = 6
,                  //Neighbours 1 to 6, then Timing Advance
    VEN_UTIL_CELL_DUMP_7 = 7
,                  //Main Cell, then Neighbours 1 to 6, then Timing Advance
    VEN_UTIL_CELL_DUMP_RSSI = 8
,                   //Main Cell RSSI indications(RxLev), in a range from 0 to 31
    VEN_UTIL_CELL_DUMP_RSSI_MAIN = 9
,          //CSQ+Main Cell only
    VEN_UTIL_CELL_DUMP_10 = 10
,                    //CSQ+Neighbors 1 to 6
    VEN_UTIL_CELL_DUMP_11 = 11
,                    //CSQ+Main Cell, then Neighbours 1 to 6
    VEN_UTIL_CELL_DUMP_12 = 12
,                    //CSQ+Timing Advance only
    VEN_UTIL_CELL_DUMP_13 = 13
,                    //CSQ+Main Cell, then Timing Advance
    VEN_UTIL_CELL_DUMP_14 = 14
,                    //CSQ+Neighbours 1 to 6, then Timing Advance
    VEN_UTIL_CELL_DUMP_15 = 15
,                    //CSQ+Main Cell, then Neighbours 1 to 6, then Timing Advance
    VEN_UTIL_CELL_DUMP_16 = 16
,                    //<requested dump> 1 + <requested dump> 2 + <requested dump> 4 +Neighbour1 to Neighbour6 Timing Advance
} ven_util_CellReqDump_e;

typedef struct
{
    ven_util_CellMode_e mode;
    ven_util_CellReqDump_e reqDump;
} ven_util_CellInfoReq_t;
#endif // __3G_RIL_MMI__

typedef struct
{
    ven_common_sim_id_t nSimID;
} ven_util_get_cell_info_t;

typedef struct
{
    u8    Mcc[2];              /* Main Cell Mcc */
    u8    Mnc;                 /* Main Cell Mnc */
    u8    Lac[2];              /* Main Cell LAC */
    u8    cellavailable;       /* cellidavailable*/
    u8    CellId[2];           /* Main Cell CI */
    u8    RxLev;               /* Main Cell RxLev */
} ven_util_CellInfo_t;

typedef struct
{
    ven_util_CellInfo_t Serving; /* Serving Cell inforamtion                     */
    u32                 nNeighbor;  /* Number of nearby cells in Neighbor table  */
    ven_util_CellInfo_t Neighbor[VEN_NBMAX_NEAR]; /* Neighbor Cell information   */
} ven_util_CellInfoRsp_t;

#ifdef __3G_RIL_MMI__
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_common_sim_id_t nSimID;
    u16 *Mcc;
    u16 *Mnc;
    u32 *pRetCode; //for sync
}  iVen_query_NetworkStatus_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_common_sim_id_t nSimID;
    u8 *pIMSI;
    u32 *pRetCode; //for sync
}  iVen_Get_IMSI_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_common_sim_id_t nSimID;
    ven_util_CellInfoReq_t Req;
    ven_util_CellInfoRsp_t *pCellInfo;
    u32 *pRetCode; //for sync
}  iVen_Get_CellInfo_req_t;


typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_util_ret_t retCode;
} iVen_Get_CellInfo_rsp_t;
#endif // __3G_RIL_MMI__


/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 * @brief Copy the SIM IMSI into a buffer.
 * @param [out] pImsi  Pointer on the buffer given in parameter
 *
 * @param [In]  SimID  The designate SIM card.
 *                     Only E_VEN_MASTER_SIM, and E_VEN_SLAVE_SIM are valid input
 *
 * @return None
 */
ven_util_ret_t ven_util_getImsi(ven_Imsi_t *pImsi, ven_common_sim_id_t SimID);

/**
 * @brief Copy the SIM IMEI into a buffer.
 *
 * @param [out] pImei  Pointer on the buffer given in parameter
 *
 * @return None
 */
ven_util_ret_t ven_util_getImei(ven_Imei_t *pImei);

/**
 * @brief Get the MCC/MNC of the current network
 *
 * @param [In]  SimID  The designate SIM card.
 *                     Only E_VEN_MASTER_SIM, and E_VEN_SLAVE_SIM are valid input
 *
 * @param [out] Mcc  MCC of the current network
 * @param [out] Mnc  MNC of the current network
 *
 * @return None
 */
ven_util_ret_t ven_util_getMccMnc(ven_common_sim_id_t SimID, u16 *Mcc, u16 *Mnc);

/**
 * @brief Get the cell info
 *
 * @param [in]  pCellInfo    Pointer to the cell info request
 * @param [out] pCellInfoRsp Pointer to the cell info result
 * @param [in]  ptVenReq     The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                           It is up to the user to free the memory allocated for the vendor request data.
 * @return None
 * @note Synchronous function
 */
ven_util_ret_t ven_util_GetCellInfo(ven_util_get_cell_info_t *pCellInfo, ven_util_CellInfoRsp_t *pCellInfoRsp, ven_req_data_t *ptVenReq);

/**
 * @brief Get the software version string
 *
 * @param [out]  pOutSwVerStr  Pointer to the pointer of software version string
 * @param [out]  pCharLen      Length in unicode character
 *
 * @return None
 */
void ven_util_getSwVerString(u16 **ppOutSwVerStr, u32 *pCharLen);


/**
  * \fn		s32 ven_util_raiWrite(ven_util_raiId_t ident, ven_util_raiSize_t size, const void * data);
  * \brief	Create or modify a random access item
  * \param	[in] ident id of the created / modified object
  * \param	[in] size total size of the object
  * \param	[in] data object contents
  * \return	VEN_UTIL_RET_SUCCESS on success,
  *			VEN_UTIL_RET_OUT_OF_SIZE if the requested size exceeds the VEN_UTIL_RAI_SIZE_MAX limit when creating new object
  *			VEN_UTIL_RET_BAD_PARAM	 if the size is not equal with original size when modifying existed object
  *           	VEN_UTIL_RET_FAILED if there is not enough free space left or other reasons
  *
  */
ven_util_ret_t ven_util_raiWrite(ven_util_raiId_t ident, u16 size, const void * data);

/**
  * \fn		s32 ven_util_raiRead (ven_util_raiId_t ident, ven_util_raiSize_t start, ven_util_raiSize_t length, void * data);
  * \brief	Read a range of a the given RAI object content. \n
  *         Read operations past the object's end of data will be truncated.
  * \param	[in] ident id of the object to read from
  * \param	[in] start read start offset
  * \param	[in] length number of bytes to read
  * \param	[out] data object data receive buffer
  * \return	the number of bytes read, 0 if no object was found or out of size
  *
  */
s32 ven_util_raiRead (ven_util_raiId_t ident, u16 start, u16 length, void * data);

/**
  * \fn		ven_util_ret_t ven_util_raiInfo(ven_util_raiId_t ident, ven_util_raiInfo_t *info);
  * \brief	Get informations on a random access item, size is the only infomation.
  * \param	[in] ident id of the object to get info on
  * \param	[out] info returned informations
  * \return	VEN_UTIL_RET_SUCCESS on success, VEN_UTIL_RET_FAILED if the object does not exist
  *
  */
ven_util_ret_t ven_util_raiInfo(ven_util_raiId_t ident, ven_util_raiInfo_t *info);

/**
  * \fn		ven_util_ret_t ven_util_raiDelete (ven_util_raiId_t ident);
  * \brief	Delete a random access item
  * \param	[in] ident id of the object to delete
  * \return	VEN_UTIL_RET_SUCCESS on success, VEN_UTIL_RET_FAILED if the object did not exist
  *
  */
ven_util_ret_t ven_util_raiDelete (ven_util_raiId_t ident);

/**
  * \fn		ven_util_convertUCS2ToPinYin(u16 u16InputWChar, u8 *pPinYinBuffer, u8 maxBufferSize);
  * \brief	Convert unicode(UCS2) to PinYin String Buffer
  * \param	[in] u16 u16InputWChar : input unicode (UCS2)
  * \param	[out] u8 *pPinYinBuffer : output string buffer (PinYin string)
  * \param	[in] u8 maxBufferSize : the max buffer size
  * \return	The size of output string buffer, 0 if not found or input error
  *
  */
u8 ven_util_convertUCS2ToPinYin(u16 u16InputWChar,u8 *pPinYinBuffer, u8 maxBufferSize);

/**
  * \fn		ven_util_convertUCS2ToBPMF(u16 u16InputWChar, u8 *pBPMFBuffer, u8 maxBufferSize);
  * \brief	Convert unicode(UCS2) to BPMF String Buffer
  * \param	[in] u16 u16InputWChar : input unicode (UCS2)
  * \param	[out] u16 *pBPMFBuffer : output string buffer (BPMF string)
  * \param	[in] u8 maxBufferSize : the max buffer size
  * \return	The size of output string buffer, 0 if not found or input error
  *
  */
u8 ven_util_convertUCS2ToBPMF(u16 u16InputWChar,u16 *pBPMFBuffer, u8 maxBufferSize);

/**
  * \fn		ven_util_base64_decode(u8 *dest, u8 *src, u16 srcLen, u16 maxDestSize, u16 *destLen);
  * \brief	Decode base64 code
  * \param	[out] u8 *dest : output string
  * \param	[in] u8 *src : input string
  * \param	[in] u16 srcLen : the length of input string
  * \param	[in] u16maxDestSize : max output size
  * \param	[out] u16 *destLen : the length of output string
  *
  */
void ven_util_base64_decode(u8 *dest, u8 *src, u16 srcLen, u16 maxDestSize, u16 *destLen);

/**
  * \fn		ven_util_base64_encode(u8 *dest, u8 *src, u16 srcLen, u16 maxDestSize, u16 *destLen);
  * \brief	Encode base 64 code
  * \param	[out] u8 *dest : output string
  * \param	[in] u8 *src : input string
  * \param	[in] u16 srcLen : the length of input string
  * \param	[in] u16maxDestSize : max output size
  * \param	[out] u16 *destLen : the length of output string
  *
  */
void ven_util_base64_encode(u8 *dest, u8 *src, u16 srcLen, u16 maxDestSize, u16 *destLen);


#endif //__VEN_UTIL_H__
