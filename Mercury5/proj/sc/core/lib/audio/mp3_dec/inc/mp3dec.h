
/**************************************************************************************
 *
 * mp3dec.h - public C API for MP3 decoder
 **************************************************************************************/

#ifndef _MP3DEC_H
#define _MP3DEC_H

#ifdef __cplusplus
extern "C" {
#endif


/* debug symbol defined here */
#define	DEBUG_LOSS_FRAME	0
#define DEBUG_PRINTF		0

/* optimaize defined here */
#define SW_HW_PIPELINE_PINGPONG 0 //use ping-pong buffer to avoid CPU copy
#define SW_IMDCT_SUBBAND_DIS    0 //remove SW IMDCT & Subband to save code size

/* determining MAINBUF_SIZE:
 *   max mainDataBegin = (2^9 - 1) bytes (since 9-bit offset) = 511
 *   max nSlots (concatenated with mainDataBegin bytes from before) = 1440 - 9 - 4 + 1 = 1428
 *   511 + 1428 = 1939, round up to 1940 (4-byte align)
 */
#define MAINBUF_SIZE		2048

#define ARMULATE_MUL_FACT	1

#ifdef __cplusplus
}
#endif
#endif	/* _MP3DEC_H */