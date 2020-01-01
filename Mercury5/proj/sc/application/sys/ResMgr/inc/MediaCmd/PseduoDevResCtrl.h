/**
* @file PseduoDevResCtrl.h
*
* This header file defines the interfaces of pseduo device resources
* 
*/

#ifndef __PSEDUODEVRESCTRL_H__
#define __PSEDUODEVRESCTRL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PseduoDevResCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum PseduoDevRes_e_
{
    PSEDUO_DEV_RES__GPS = 0,
    PSEDUO_DEV_RES__AUD,
    PSEDUO_DEV_RES__VDO,
    PSEDUO_DEV_RES__CAM,
    PSEDUO_DEV_RES__FMR,
    PSEDUO_DEV_RES__USB,
    PSEDUO_DEV_RES__CODEC,
    PSEDUO_DEV_RES__NUM,
    PSEDUO_DEV_RES__INVALID
} PseduoDevRes_e;

typedef struct PseduoDevResInfo_t_
{
    u16 uResNum;
    PseduoDevRes_e *pDevResInfo;
} PseduoDevResInfo_t;

typedef struct PseduoDevResCtrl_TravData_t_
{
    u16 uNewReqResID;
    ResCtrlHandle_t pConflictResCtrlHdl;
    bool bConflict;
} PseduoDevResCtrl_TravData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__PSEDUODEVRESCTRL_H__

