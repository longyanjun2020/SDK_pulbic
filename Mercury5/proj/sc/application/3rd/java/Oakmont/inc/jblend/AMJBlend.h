/*
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMJBlend.h
 *   JBlend Initialization JBI
 */
/**
 * @addtogroup JBlend_Initialization_JBI
 * @{
 */

#ifndef ___AM_JBLEND_H
#define ___AM_JBLEND_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Initializes JBlend.
 *  @param jkf
 *   Designate NULL (Reserved for future. Not used currently.)
 *  @param flags
 *   Designate 0 (Reserved for future. Not used currently.)
 *  @return
 *   0: succeeded<br>
 *   negative value: failed
 *
 *  This function needs to be called only once, when the native system is 
 *  initialized, before calling any service functions.
 * 
 *  When this function is called, JBlend calls JkSectionGetInfoR2() as part of 
 *  the processing in this function. 
 *  If JkSectionGetInfoR2() returns illegal section information, this function 
 *  fails, returning a negative value. If, for example, the value returned by 
 *  JkSectionGetInfoR2() is #JK_NULL, this may mean a value of less than 1 was 
 *  set in the <i>number</i> parameter passed to JkSectionGetInfoR2().
 */
int AmJBlendInitialize(const void* jkf, long flags);

#ifdef __cplusplus
}
#endif

#endif

/** @} end of group */
