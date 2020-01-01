/******************************************************************************/
/*  File    :   sys_ext_int.h                                                 */
/*----------------------------------------------------------------------------*/
/*  Scope   :   External IRQ handler                                          */
/*                                                                            */
/*  Contents:                                                                 */
/*                                                                            */
/******************************************************************************/

#ifndef __SYS_EXT_INT_H__
#define __SYS_EXT_INT_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/**
 * Number of extern interruption lines
 */
#define SYS_EXT_INT_NUMBER   6


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef enum {
	EXT_INT_0 = 0,
	EXT_INT_1,
	EXT_INT_2,
	EXT_INT_3,
	EXT_INT_4,
	EXT_INT_5,
 	EXT_INT_6,
	EXT_INT_7,
	EXT_INT_8,
	EXT_INT_9,
 	EXT_INT_10,
	EXT_INT_11,
	EXT_INT_12,
	EXT_INT_13,
	EXT_INT_14,
	EXT_INT_15
} sys_ExtIntNumber_t;

/**
 * Interrupt Service Routine type
 */
typedef void (*sys_ExtIntISR)( void );

/**
 * The interrupt line can be mapped on IRQ or FIQ
 */
typedef enum
{
	MAP_TO_EXT_INT_1=0,
	MAP_TO_EXT_INT_2,
	MAP_TO_EXT_INT_3
} sys_ExtIntMap;

/**
 * Polarity of the interrupt line
 */
typedef enum
{
	EXT_INT_NORMAL_POLARITY=0, /// 0: normal polarity (rising edge/high level)
	EXT_INT_REVERSE_POLARITY /// 1: reverse polarity (falling edge/low level)
} sys_ExtIntPolarity_t;

/**
 * Mode type
 */
typedef enum
{
	EXT_INT_BYPASS_MODE=0, ///bypass mode
	EXT_INT_SHORT_PULSE_MODE, ///short pulse mode
	EXT_INT_DEBOUNCE_MODE, ///debounce mode
	EXT_INT_DEBOUNCE_BOTH_EDGE_MODE ///debounce + both edge detector mode
} sys_ExtIntMode_t;

typedef struct 
{
	sys_ExtIntPolarity_t      polarity;       ///
	sys_ExtIntMode_t      	mode;       ///
	u8 			debounce; // number of debounce cycle
	u8             	priority;       ///
	sys_ExtIntISR  isr;
} sys_ExtIntParam;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
void sys_ext_int_Handler_1(void);
void sys_ext_int_Handler_2(void);
void sys_ext_int_Handler_3(void);
void sys_ext_int_Mask(const sys_ExtIntNumber_t interruptNumber);
void sys_ext_int_Unmask(const sys_ExtIntNumber_t interruptNumber);
s32 sys_ext_int_Initialize(const sys_ExtIntParam *it_param,
                           const sys_ExtIntNumber_t interruptNumber);

#endif /* __SYS_EXT_INT_H__ */
