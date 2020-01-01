
#ifndef  __IFLAYER_DLBDPARSER_H__
#define  __IFLAYER_DLBDPARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************Structure*********************************/
/**
 * Download descriptor structure
 * NOT Change following data
 */
typedef struct T_DL_DDfile{
    int8_t  *dd_objectURI;
    int8_t  *dd_size;
    int8_t  *dd_type;
    int8_t  *dd_name;
    int8_t  *dd_DDVersion;
    int8_t  *dd_vendor;
    int8_t  *dd_description;
    int8_t  *dd_installNotifyURI;
    int8_t  *dd_nextURL;
    int8_t  *dd_infoURL;
    int8_t  *dd_iconURI;
    int8_t  *dd_installParam;
}T_DL_DD;

/** defining report status*/

typedef enum _T_DB_DL_REPORT_STATUS
{
    DB_OMADL_SUCCESS,
    DB_OMADL_NOMEMORY,
    DB_OMADL_USERCANCEL,
    DB_OMADL_LOSTSERVICE,
    DB_OMADL_ATTRMISMATCH,
    DB_OMADL_INVALIDDD,
    DB_OMADL_INVALIDVERSION,
    DB_OMADL_DEVICEABORT,
    DB_OMADL_UNKOWNCONTENT,
    DB_OMADL_LOADERROR,
    DB_OMADL_OTHER
}T_DB_DL_REPORT_STATUS;


/**********************Function *********************************/

/**
 * fnDLOTA_Free: Free the structure of DD file
 * \param     T_DL_DD *dd
 * \return      TRUE ---  success.      FALSE --- fail.
 */
int32_t fnDB_OMADDFree(T_DL_DD *dd);

/**
 * fnDLOTA_Parse: main parser
 * \param      int8_t *dFData
 * \return      T_DL_DD * ---  success.      NULL --- fail.
 */
T_DL_DD *fnDB_OMADDParse(int8_t *pDData);

int8_t * fnDB_OMADLGetStatusInfo(T_DB_DL_REPORT_STATUS  status);

T_DL_DD * fnDB_OMADDProcess(int8_t *pDData);

void fnDB_OMADLStatus(T_DB_DL_REPORT_STATUS status,T_DL_DD ** dd);

#ifdef __cplusplus
}
#endif

#endif /*_DDPARSER_H*/
