/**
* @file MediatorItf.h
*
* This header file defines the interfaces of mediator
*
*/

#ifndef __MEDIATORITF_H__
#define __MEDIATORITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "DataStructItf.h"
#include "DataStructFactoryItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void (*MedChangeStaus) (void *pCurData, void *pChangedData);
typedef void (*MedOnChange) (u16 uMedId, void *pChangedData, u32 uParams, void *pCusData);

typedef void* MediatorHandle_t;

typedef struct MediatorClient_t_
{
    MedOnChange OnChange;
    u32 uParams;
} MediatorClient_t;

typedef struct Mediator_t_
{
    u16 uMedId;
    u16 uDataSize;
    void *pData;
    void *pCusData;
    DataStruct_t *pClients;
    MedChangeStaus ChangeStatus;
} Mediator_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
MediatorHandle_t Mediator_Init(u16 uMedId, u16 uDataSize, MedChangeStaus ChangeStatus, void *pInitVal, void *pCusData);
void Mediator_Uninit(MediatorHandle_t pMedHdl);

void Mediator_RegClient(MediatorHandle_t pMedHdl, MediatorClient_t *pMedClientItf);
void Mediator_DeregClient(MediatorHandle_t pMedHdl, MediatorClient_t *pMedClientItf);

void Mediator_ChangeStatus(MediatorHandle_t pMedHdl, void *pChangedData);
void Mediator_GetStatus(MediatorHandle_t pMedHdl, void *pData);
void Mediator_OnChanged(MediatorHandle_t pMedHdl, void *pChangedData);

#endif //__MEDIATORITF_H__
