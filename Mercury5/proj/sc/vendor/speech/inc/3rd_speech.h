
#ifndef _3RD_SPEECH_H_
#define _3RD_SPEECH_H_

#include "mmp_err.h"
#include "lock_queue.h"
#include "aitu_ringbuf.h"
#include "api_wakeup.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/
typedef void (*MMP_SpeechRecogCbFunc) (MMP_ULONG);

#ifdef _3RD_SPEECH_C_
#define	SPEECH_EXTERN
#else
#define	SPEECH_EXTERN	extern
#endif

#ifndef MIN
#define MIN(x, y)           (((x) < (y))?(x):(y))
#endif


/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum
{
	SPEECH_RECOG_ID1,
	SPEECH_RECOG_ID2,
	SPEECH_RECOG_ID3,
}SPEECH_RECOG_ID;

SPEECH_EXTERN void			Speech_TaskHandler(void *p_arg);
SPEECH_EXTERN voice_msg_t*	Speech_GetBuffer(void);
SPEECH_EXTERN MMP_ERR		Speech_SetVoiceData(void *buf);
SPEECH_EXTERN MMP_ERR		Speech_SetCB(MMP_SpeechRecogCbFunc  CB);
SPEECH_EXTERN MMP_ULONG		Speech_PCMTransferCB(AUTL_RINGBUF *pPCMOutRing, MMP_ULONG ulUnReadSampleCnt);
SPEECH_EXTERN MMP_ERR		Speech_Init(void);
SPEECH_EXTERN int			_handler(void *obj, wakeup_status_t status, char *json, int bytes);
SPEECH_EXTERN MMP_BOOL      Speech_AuthPass(void);
#endif //#ifndef _3RD_SPEECH_H_


