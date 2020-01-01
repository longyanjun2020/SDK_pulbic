/*----------------------------------------------+
|												|
|	ivESRErrorCode.h - Basic Definitions		|
|												|
|		Copyright (c) 1999-2007, iFLYTEK Ltd.	|
|		All rights reserved.					|
|												|
+----------------------------------------------*/

#ifndef IFLYTEK_VOICE__ESRERRORCODE__H
#define IFLYTEK_VOICE__ESRERRORCODE__H

#include "ivDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef	ivCStr		EsErrID;
typedef ivInt32		ivESRStatus;

#define	EsErrID_OK	 ivNull
#define EsErr_InvCal	((EsErrID)1)
#define EsErr_InvArg	((EsErrID)2)
#define EsErr_TellSize	((EsErrID)3)
#define EsErr_OutOfMemory	((EsErrID)4)
#define EsErr_InvProperty	((EsErrID)5)
#define EsErr_CmdObj	((EsErrID)6)
#define EsErr_BufferFull	((EsErrID)7)
#define EsErr_ASREnded	((EsErrID)8)
#define EsErr_Result	((EsErrID)9)
#define EsErr_ForceResult	((EsErrID)10)
#define EsErr_BufferEmpty	((EsErrID)11)
#define EsErr_ResultNone	((EsErrID)12)
#define EsErr_SetFailed	((EsErrID)13)
#define EsErr_ParamNotSupport	((EsErrID)14)
#define EsErr_ReEnter	((EsErrID)15)
#define EsErr_InvRes	((EsErrID)16)
#define EsErr_CmdCountExceeded	((EsErrID)17)
#define EsErr_SpeechStart		((EsErrID)18)
#define EsErr_ResponseTimeOut	((EsErrID)19)
#define EsErr_CmdTooLong		((EsErrID)20)
#define EsErr_Limited			((EsErrID)21)
#define EsErr_InsufficientWorkBuffer		((EsErrID)22)
#define EsErr_InsufficientResidentBuffer	((EsErrID)23)
#define EsErr_InvSyntax			((EsErrID)24)
#define EsErr_RecStartFail		((EsErrID)27)
#define EsErr_RecStopFail		((EsErrID)28)
#define EsErr_InvHeader			((EsErrID)29)
#define EsErr_InvName			((EsErrID)30)
#define EsErr_LexNotFound		((EsErrID)31)
#define EsErr_SceneNotFound		((EsErrID)32)
#define EsErr_BeginProcess		((EsErrID)33)
/*
*	ivESR Status return
*/

/* General */
#define ivESR_OK			EsErrID_OK
#define ivESR_INVCAL		((ivESRStatus)EsErr_InvCal)
#define ivESR_INVARG		((ivESRStatus)EsErr_InvArg)
#define ivESR_INVHEADER		((ivESRStatus)EsErr_InvHeader)

/* For lexicon and scene input */
#define ivESR_INVNAME		((ivESRStatus)EsErr_InvName)
#define ivESR_OUTOFMEMORY	((ivESRStatus)EsErr_OutOfMemory)
#define ivESR_INVPROPERTY	((ivESRStatus)EsErr_InvProperty)
#define ivESR_CMDTOOLONG	((ivESRStatus)EsErr_CmdTooLong)
#define ivESR_INSUFFICIENTWORKBUFFER	((ivESRStatus)EsErr_InsufficientWorkBuffer)
#define ivESR_INSUFFICIENTRESIDENTBUFFER	((ivESRStatus)EsErr_InsufficientResidentBuffer)
#define ivESR_SYNTAXERROR	((ivESRStatus)EsErr_InvSyntax)
#define ivESR_LEXNOTFOUNT	((ivESRStatus)EsErr_LexNotFound)	
#define ivESR_SCENENOTFOUND	((ivESRStatus)EsErr_SceneNotFound)

/* For create ESR object */
#define ivESR_SIZECACULATED	((ivESRStatus)EsErr_TellSize)
#define ivESR_CMDOBJ		((ivESRStatus)EsErr_CmdObj)

/* For append PCM data */
#define ivESR_BUFFERFULL	((ivESRStatus)EsErr_BufferFull)
#define ivESR_ASR_ENDED		((ivESRStatus)EsErr_ASREnded)

/* For run Step  */
#define ivESR_RESULT		((ivESRStatus)EsErr_Result)
#define ivESR_FORCERESULT	((ivESRStatus)EsErr_ForceResult)
#define ivESR_BUFFEREMPTY	((ivESRStatus)EsErr_BufferEmpty)
#define ivESR_ASR_ENDED		((ivESRStatus)EsErr_ASREnded)

/* For get recognition result ID */
#define ivESR_NONE				((ivESRStatus)EsErr_ResultNone)
#define	ivESR_LIMITED			((ivESRStatus)EsErr_Limited)

/* For set parameters */
#define ivESR_FAILED			((ivESRStatus)EsErr_SetFailed)
#define ivESR_NOT_SUPPORT		((ivESRStatus)EsErr_ParamNotSupport)

/* For build grammar */
#define ivESR_CMDCOUNTEXCEED	((ivESRStatus)EsErr_CmdCountExceeded)
#define ivESR_INVRESOURCE		((ivESRStatus)EsErr_InvRes)

/* For time out */
#define ivESR_SPEECHSTART		((ivESRStatus)EsErr_SpeechStart)
#define ivESR_RESPONSETIMEOUT	((ivESRStatus)EsErr_ResponseTimeOut)

/* For record callback */
#define ivESR_RECSTARTFAIL		((ivESRStatus)EsErr_RecStartFail)
#define ivESR_RECSTOPFAIL		((ivESRStatus)EsErr_RecStopFail)

/* For recording skip */
#define ivESR_BEGINPROCESS		((ivESRStatus)EsErr_BeginProcess)

#ifdef __cplusplus
}
#endif


#endif /* !IFLYTEK_VOICE__ESRERRORCODE__H */
