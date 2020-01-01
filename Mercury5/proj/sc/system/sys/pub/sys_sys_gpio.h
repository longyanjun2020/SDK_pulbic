/****************************************************************************/
/*  File    : SYS_SYS_GPIO.H                                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   : Macro and function for GPIO management                        */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/

#ifndef __SYS_SYS_GPIO_HP__
#define __SYS_SYS_GPIO_HP__

#include "stdcomp.h"

#define O_GPO     0x80

s32 HWL_s32_GPIOSetGpioSettings(const u32 i_u32_Mask, const u32 i_u32_Settings);	/* Set GPIO direction: Input or Output */
void sys_UpGpio       ( u8 NoGpio );    /* set output           */
void sys_DwnGpio      ( u8 NoGpio );    /* reset output         */
u8   sys_AcqGpio      ( u8 NoGpio );    /* acquire value        */

/* Number of define only for gpio purpose. */

#define PULSE(NoBit)                                          \
{                                                             \
}

/* Set an output GPIO to 1. */

#define FUP_GPIO(NoBit)                                       \
{                                                            \
}

#if 0 //yfa
 OGpio->Data |= (1 << NoBit);                                 \
}
#endif


#define UP_GPIO(NoBit)                                       \
{\
}
#if 0 // yfa
 OGpio->Direction  &= (~(1 << NoBit));                        \
 OGpio->Data |= (1 << NoBit);                                 \
 }
#endif 


/* Set an output GPIO to 0. */

#define FDWN_GPIO(NoBit)                                      \
{                                                            \
}

#if 0
 OGpio->Data &= (~(1 << NoBit));                              \
    }
#endif


#define DWN_GPIO(NoBit)                                      \
{\
}

#if 0 //yfa
 OGpio->Direction  &= (~(1 << NoBit));                        \
 OGpio->Data &= (~(1 << NoBit));                              \
}
#endif


/* Read the state of an input GPIO. */
#define FACQ_GPIO(NoBit) ((OGpio->Data >> NoBit) & 0x01)


/* Read the state of a GPIO. */
#define ACQ_GPIO(NoBit, State)                           \
{\
}

#if 0 
 OGpio->Direction  |= ((1 << NoBit));\
 State = ((OGpio->Data >> NoBit) & 0x01);\
    }
#endif




#endif /* __SYS_SYS_GPIO_HP__ */

