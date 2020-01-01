/*
 **************************************************
	 Modifications
 **************************************************

 $Log$



*/


#ifndef __DMA_SOURCES_HC__
#define __DMA_SOURCES_HC__

#include "stdcomp.h"
#include "cpu_mem_map.hc"

/*####################################################################*/
/*################## REGISTERS DEFINITIONS ###########################*/
/*####################################################################*/

/*####################################################################*/
/*##################### DMA sources and destination DEFINITIONS #############################*/
/*####################################################################*/

#define AUDIO_RX_DMA_POS 11

#define AUDIO_TX_DMA_POS 10

#define UART2_RX_DMA_POS 9

#define UART2_TX_DMA_POS 8

#define I2C_RX_DMA_POS 7

#define I2C_TX_DMA_POS 6

#define UART1_RX_DMA_POS 5

#define UART1_TX_DMA_POS 4

#define SPI2_RX_DMA_POS 3

#define SPI2_TX_DMA_POS 2

#define SPI1_RX_DMA_POS 1

#define SPI1_TX_DMA_POS 0

#if 0

/*####################################################################*/
/*##################### IRQ sources DEFINITIONS #############################*/
/*####################################################################*/
#define WATCHDOG_IT_POS	35

#define SIM1_IT_POS 32

#define EX_ICE_IT_POS 31

#define DMAC_IT_POS 30

#define CMU_IT_POS 27

#define SHIFACE_IT_POS 26

#define DSMA_IT_POS 25

#define AUDIO_IT_POS 24

#define RFDL_COL_IT_POS 23

#define TBU_SINTA_IT_POS 22

#define TBU_FINT_IT_POS 21

#define TBU_SINT3_IT_POS 20

#define TBU_SINT2_IT_POS 19

#define TBU_SINT1_IT_POS 18

#define TBU_SINT0_IT_POS 17

#define TIMEOUT_IT_POS 15

#define OSTICK_IT_POS 14

#define TIMSOFT_IT_POS 13

#define KEYBOARD_IT_POS 12

#define UART2_IT_POS 11

#define UART1_IT_POS 10

#define I2C_TRANSFER_IT_POS 9

#define SPI2_IT_POS 6

#define SPI1_IT_POS 5

#define I2C_STATUS_IT_POS 4

#define EXT3_IT_POS 3

#define EXT2_IT_POS 2

#define EXT1_IT_POS 1

#define RTC_IT_POS 0

#endif

#endif // __DMA_SOURCES_HC__

