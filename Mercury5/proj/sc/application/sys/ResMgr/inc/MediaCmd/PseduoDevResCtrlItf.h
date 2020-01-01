/**
* @file PseduoDevResCtrlItf.h
*
* This header file defines the interfaces of pseduo device resources
* 
*/

#ifndef __PSEDUODEVRESCTRLITF_H__
#define __PSEDUODEVRESCTRLITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResCtrlHandle_t PseduoDevResCtrl_Init(void);
void PseduoDevResCtrl_Uninit(ResCtrlHandle_t pResCtrlHdl);
#endif //__PSEDUODEVRESCTRLITF_H__

