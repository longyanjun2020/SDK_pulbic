////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_javaamsapp.h
* @version
* @brief   javaams header file
*
*/

#ifndef __MMI_JAVAAMSAPP_H__
#define __MMI_JAVAAMSAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_launcher_javaams.h"
#include "mmi_mae_filemgr.h"
#include "mmi_srv_header.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
// Embedded start reason
enum
{
    JAVAAMSAPP_EMBEDDED_NONE = 0,
    JAVAAMSAPP_EMBEDDED_INSTALL,        // Embedded start for install JAD/JAR
    JAVAAMSAPP_EMBEDDED_LAUNCH,         // Embedded start for launch installed MIDlet
    JAVAAMSAPP_EMBEDDED_BG_EXECUTION_LAUNCH,         // when Java BackGround execution ,launch installed MIDlet     //BG_EXEC_NOT_ENTER_AMS_LIST
};

/* JAD properties*/
typedef enum
{
    JAVA_PROP_DESCRIPTION = 0,
    JAVA_PROP_INFO_URL,
    JAVA_PROP_JAR_URL,

    JAVA_PROP_NUM,
}Java_Prop_e;

// Embedded launch
typedef struct
{
    u32 nMIDletId;       // MIDlet ID to launch
} JavaAmsApp_EmbeddedLaunch_t;


//JAVA_INSTALL_WITH_TWO_PATH
typedef struct
{
    MAE_WChar pszFile[FILEMGR_MAX_FILEPATH_SIZE]; // filename in wide character format
    MAE_WChar pszFile2[FILEMGR_MAX_FILEPATH_SIZE]; //JAD path if have (WAP used only)   JAVA_INSTALL_WITH_TWO_PATH    filename in wide character format
    JavaAmsApp_EmbeddedLaunch_t tLaunchInfo;
} JavaAmsApp_tParam_t;


// Parameter for embedded applet
typedef struct
{
    u32 nEmbeddedReason; // Embedded install/launch

    JavaAmsApp_tParam_t tParam;

    //mark by JAVA_INSTALL_WITH_TWO_PATH    
	//union
    //{
    //    MAE_WChar pszFile[FILEMGR_MAX_FILEPATH_SIZE]; // filename in wide character format
    //    JavaAmsApp_EmbeddedLaunch_t tLaunchInfo;
	//} tParam;
} JavaAmsApp_EmbeddedParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** JavaamsPreNew
* @brief        Prenew function to Launch Java Install applet
*
*/
void JavaamsPreNew(void);

/** JavaAppNew
* @brief        New function to create Javaams Applet
*
* @param[in]    nClsId               Javaams class id
* @param[in]    ppObj               The pointer of pointer of Applet
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       other               Fail.
*
*/
MAE_Ret JavaAppNew(MAE_ClsId id, void **ppObj);
#ifdef __WAP_MMI_CDWAP__
/*-------------------------------------------------------------------------*/
/* Epilogue */
/* User Code Begin */

/*
*	Parse a given JAD buffer and returns the property string
*	pInJadBuf       [in] : input buffer from a given JAD file
*	eProp           [in] : User interested JAD property
*   ppOutPropString [out]: The output JAD property string. The output is allocated automatically.
*                          User need to free the property string after using.
*
*   retval MAE_RET_SUCCESS if success.
*          MAE_RET_FAILED if failed.
*/
MAE_Ret JavaAmsAppGetPropStringFromJad(u8 *pInJadBuf, Java_Prop_e eProp, MAE_WChar **ppOutPropString);
#endif

#endif /* __MMI_JAVAAMSAPP_H__ */
