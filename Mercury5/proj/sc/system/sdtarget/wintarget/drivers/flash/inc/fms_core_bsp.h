/****************************************************************************/
/*  $Workfile::   fms_core_bsp.h                                          $ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Flash Memory Services - Common core routines                 */
/*                                     Board support package                */
/****************************************************************************/



#ifndef _d8215c5c978428f9394aed469d0921e2_INCLUDED_FMS_CORE_BSP_H
#define _d8215c5c978428f9394aed469d0921e2_INCLUDED_FMS_CORE_BSP_H

/****************************************************************************/
/* EXPORTED DEFINITIONS                                                     */
/****************************************************************************/

#ifdef __TARGET__
#define SAVE_CPUFLAGS(_X_,_Y_) _X_ = fms_CoreEnterCritical(_Y_)
#define RESTORE_CPUFLAGS(_Y_) fms_CoreLeaveCritical(_Y_)
#else
#define SAVE_CPUFLAGS(_X_,_Y_)
#define RESTORE_CPUFLAGS(_Y_)
#endif

/****************************************************************************/
/* EXPORTED FUNCTIONS                                                       */
/****************************************************************************/

/****************************************************************************/
/*  Function: fms_CoreEnterCritical                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Enters in a critical execution region.                        */
/*            Prevents the preemption during low-level flash operations.    */
/*            Sets the CPU in an acceptable state.                          */
/*  Return    : (u32) flags (see above)                                     */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Needed     | X |   |   |  TRUE if the interrupts have to be      */
/*                    |   |   |   |  masked                                 */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
u32 fms_CoreEnterCritical(u32 i__u32_Needed);

/****************************************************************************/
/*  Function: fms_CoreLeaveCritical                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Exits the critical region.                                    */
/*            Restores to the state before the call to fms_CoreEnterCritical*/
/*                                                                          */
/*  Return    : void                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Flags      | X |   |   |  Flags returned by fms_CoreEnterCritical*/
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void fms_CoreLeaveCritical(u32 i__u32_Flags);
	


#endif /* ! _d8215c5c978428f9394aed469d0921e2_INCLUDED_FMS_CORE_BSP_H   */
