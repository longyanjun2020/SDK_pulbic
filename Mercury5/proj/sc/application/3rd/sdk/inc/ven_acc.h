/**
 *
 * @file    ven_acc.h
 * @brief   This file defines accessory interface
 *
 * @author  William.Tseng
 * @version $Id$
 *
 */
#ifndef __VEN_ACC_H_
#define __VEN_ACC_H_



#ifdef __SDK_DEVICE_CONTROL__
extern int ven_sys_acc_startBacklightFlash(int duration);
extern int ven_sys_acc_stopBacklightFlash(void);
extern int ven_sys_acc_startVibration(int duration);
extern int ven_sys_acc_stopVibration(void);
#endif /* __SDK_DEVICE_CONTROL__ */


#endif /*__VEN_ACC_H_*/
