#ifndef _AMRENCLIB_H
#define _AMRENCLIB_H

#include "amr_mode_enc.h"
#include "amr_typedef.h"

struct amrencoder
{
	unsigned short *speech_buf;
	int frames;
	int *enstate; /* pointer to encoder state structure */
	void *heapaddr;
};

/*
 * Declare structure types
 */
/* Declaration transmitted frame types */
enum TXFrameType { TX_SPEECH_GOOD = 0,
                   TX_SID_FIRST,
                   TX_SID_UPDATE,
                   TX_NO_DATA,
                   TX_SPEECH_DEGRADED,
                   TX_SPEECH_BAD,
                   TX_SID_BAD,
                   TX_ONSET,
                   TX_N_FRAMETYPES     /* number of frame types */
};

/* Declaration of interface structure */
typedef struct
{
   short  sid_update_counter;   /* Number of frames since last SID */
   short  sid_handover_debt;    /* Number of extra SID_UPD frames to schedule */
   int    dtx;
   enum   TXFrameType prev_ft;  /* Type of the previous frame */
   void   *encoderState;        /* Points encoder state structure */
} enc_interface_State;

extern s32 amrnb_encoder_open(void *pInst,
                            s32 s32dtx_enable,
                            u32 *samplebuffer,
                            u32 *u32bits_per_sample,
                            u32 *u32sample_rate,
                            u32 *u32frame_length,
                            u32 *u32channels,
                            u32 *u32para);

extern s32 amrnb_encoder_enc_data(void *pInst,
                          s32 *out_size,
                          u32 *u32rectotaltime,
                          u32 *u32rectotalsize,
                          s32 s32first_frame);

extern s32 amrnb_encoder_get_timestamp(void *pInst, u32 *pu32Pos);

extern void amrnb_encoder_engine_clock(void *pInst, u8 onoff);

extern s32 amrnb_encoder_close(void *pInst);

extern s32 amrnb_encoder_write_close(void *pinst ,s32 *seek_offt, s32 *wsize, u8** wsrcptr);


/*
extern int fnAMREnc_Init(void **pInst, void *amrheapaddr);
extern int fnAMREnc_Open(void *pInst, int dtx);
extern int fnAMREnc_Dec(void *pInst, char *prawpcm, int size, unsigned char *poutstream, int *outbufsize, int *pactualoutsize, int first_frame);
*/

#endif
