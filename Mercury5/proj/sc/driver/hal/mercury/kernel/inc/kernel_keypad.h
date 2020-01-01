/***************************************************************************
 *  kernel_keypad.h
 *--------------------------------------------------------------------------
 *  Scope: Keypad related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_KEYPAD_H__
#define __KERNEL_KEYPAD_H__

/* B2 registers definition */

#include "vm_types.ht"
#include "cpu_mem_map.hc"

/************************************************/
/* KEYPAD registers definition                  */
/************************************************/

typedef struct OKeyPad_s
{
    u16 nConfig; 		// 0x00
    u16 nIoConfig;
    u16 nData; 			// 0x04
    u16 nColRowMode;
    u16 nInterruptStatus; // 0x08
    u16 nSpare1;
    u16 nInterruptClear; // 0x0C
    u16 nSpare2;
    u16 nSpare3;			// 0x10
    u16 nSpare4;
    u16 nStatus;			// 0x14
} OKeyPad_t;

/*** Config register ***/
#define KEYPAD_DEBOUNCE_MSK     (0x003F<<0)
#define KEYPAD_DEBOUNCE_POS     0

/* IO mode configuration register */
#define KEYPAD_DIR_ROW_POS      0  // 1=IN    0=OUT
#define KEYPAD_DIR_ROW_MSK      (0x00FF<<KEYPAD_DIR_ROW_POS) 
#define KEYPAD_DIR_COL_POS      8
#define KEYPAD_DIR_COL_MSK      (0x00FF<<KEYPAD_DIR_COL_POS)

/*** Data register ***/
#define KEYPAD_DATA_ROW_POS      0
#define KEYPAD_DATA_ROW_MSK     (0x00FF<<KEYPAD_DATA_ROW_POS)
#define KEYPAD_DATA_COL_POS     8
#define KEYPAD_DATA_COL_MSK     (0x00FF<<KEYPAD_DATA_COL_POS)


/*** Col Row Mode ***/
#define KEYPAD_MODE_ROW_POS 0  // 0=keyboard 1 =IO pads
#define KEYPAD_MODE_ROW_MSK (0x00FF << KEYPAD_MODE_ROW_POS)
#define KEYPAD_MODE_COL_POS 8
#define KEYPAD_MODE_COL_MSK (0x00FF << KEYPAD_MODE_COL_POS)


/*** Status register ***/
#define KEYPAD_ROW_PRESSED_POS  0  // 0=pressed    1=released
#define KEYPAD_ROW_PRESSED_MSK  (0x00FF<<KEYPAD_ROW_PRESSED_POS) 
#define KEYPAD_COL_PRESSED_POS  8
#define KEYPAD_COL_PRESSED_MSK  (0x00FF<<KEYPAD_COL_PRESSED_POS)

extern volatile OKeyPad_t*  const g_ptOKeyPad;

#endif //__KERNEL_KEYPAD_H__
