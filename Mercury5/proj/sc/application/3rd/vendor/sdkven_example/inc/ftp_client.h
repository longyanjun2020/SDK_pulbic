/**
 *
 * @file    ftp_client.h
 * @brief   This file is the common define file for the ftp
 *
 * @author  Allen.Lai
 * @version $Id:$
 *
 */
 
#ifndef __FTP_CLIENT_H__
#define __FTP_CLIENT_H__

#include "ven_sdk.h"
#include "ven_dbg.h"


#define _FTP             VEN_DBG_GROUP_0

#define _FTP_GENERAL   _FTP | VEN_DBG_LEVEL_30

#define SDKVEN_FTP_APID   E_VEN_DEFAULT

enum 
{ 
    FTP_DOWNLOAD_1MB = 0, 
    FTP_DOWNLOAD_2MB = 1, 
    FTP_UPLOAD_200KB = 2, 
    FTP_UPLOAD_500KB = 3 
};

#endif /* __FTP_CLIENT_H__ */
