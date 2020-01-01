/**
* @file Simu_Vfs.h
*
* This header file defines the interface of lower layer device simulation for VFS
*
*/
#ifndef __SIMU_VFS_H__
#define __SIMU_VFS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"
#include "ABL_Vfs.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct Simu_VfsCbRemap_t_
{
    u16 uTimerId;
    ABL_VfsCb VfsCb;
} Simu_VfsCbRemap_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_VfsOpenSessionCb(void *pUserData);
void Simu_VfsCloseSessionCb(void *pUserData);
#endif //__SIMU_VFS_H__
