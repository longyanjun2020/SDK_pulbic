/**
 * @file mmi_mae_sm_version.h
 *
 * This file defines the current version number of state machine engine
 * The version number is used to make sure that the application's data is right for current state machine engine
 * Compilation will fail if the version is mismatch with the application source code.
 *
 * MAE_SM_CG_VERSION Format: ABXX
 * A: Major Version
 * B: Minor Version
 * XX: patch
 *
 * @version $Id: mmi_mae_sm_version.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
#ifndef __MMI_MAE_SM_VERSION_H__
#define __MMI_MAE_SM_VERSION_H__
//#define MAE_SM_CG_VERSION   1000    /* 20070523 */
//#define MAE_SM_CG_VERSION   1100    /* 20070625, add internql queue to the parameter of GenericModeMethod */
#define MAE_SM_CG_VERSION	1200	/* 20070928, change _New parameter sequence */

#endif /* __MAE_SM_VERSION_H__ */
