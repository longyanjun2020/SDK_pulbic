#ifndef _MDL_VT_STATE_HANDLER_H_
#define _MDL_VT_STATE_HANDLER_H_


#include "mdl_vt_state.h"


vt_state_err_et pre_handler_Open_From_Close(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_WaitingToPlay(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_Stop(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Stop_From_WaitingToPlay(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_Close(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubRemotePictureDisabled(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubRemotePictureEnabled(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubBlankPreviewDisabled(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubBlankPreviewEnabled(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubLocalVideoSrcPicture(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubLocalVideoSrcCamera(vt_state_t *state, vt_event_t e, void *data);

vt_state_err_et pre_handler_PlaySubRecordStarting(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubRecording(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubRecordStopping(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubRecordFileSaving(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et pre_handler_PlaySubRecordStopped_SaveFileOk(vt_state_t *state, vt_event_t e, void *data);

vt_state_err_et post_handler_Stop_From_Play(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Stop_From_Play_ReadyToStop1(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitingToPlay_From_Stop(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitingToPlay_From_WaitingToPlay(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitingToStop_From_WaitingToStop(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_ErrorHandling(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitingToStop(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Stop(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Stop_From_Stop(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitingToOpen(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitingToClose(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Stop_From_Close(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Close(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_LocalVideoSrc(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_ScreenMode(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_RemotePic(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_SensorBrightness(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_SensorContrast(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_DigitalZoom(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_AvpVdr(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_Record(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_Play_From_Play_BlankPreview(vt_state_t *state, vt_event_t e, void *data);


vt_state_err_et post_handler_PlaySubLocalLarge(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubLocalSmall(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRemoteOnly(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubLocalOnly(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubVdrStopDone_From_PlaySubOk(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubAvpStopDone_From_PlaySubOk(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubAllStopDone(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordStarting(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecording(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordSaving(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordSaving_DiskFull(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordSaving_RuntimeError(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordFileDiscarding(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordSaving(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordSaving_From_PlaySubRecordSaving_RecordStop(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordSaveFileFail_From_PlaySubRecordSaving_SaveFileFail(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordStopped_RecordStartFail(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordStopped_From_PlaySubRecordSarting_DiskFull(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordStopped_SaveFileOk(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordStopped_From_PlaySubRecordFileDiscarding_DiscardFileOk(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordStopped_SaveFileAborting(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordStopped_AbortSavingFileOk(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_PlaySubRecordStopped_From_PlaySubRecordSaveFileFail_DiscardFileOk(vt_state_t *state, vt_event_t e, void *data);



vt_state_err_et post_handler_WaitPlaySubStartVdrDone_From_WaitPlaySubInit(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitPlaySubStartAvpDone_From_WaitPlaySubInit(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitPlaySubStartAvpFail_From_WaitPlaySubInit(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitPlaySubStartVdrDone_From_WaitPlaySubStartVdrDone(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitPlaySubStartVdrFail_From_WaitPlaySubInit(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitPlaySubStartAvpDone_From_WaitPlaySubStartAvpDone(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitPlaySubInit(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitPlaySubStartAllDone(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitStopSubStopVdrDone_From_WaitStopSubInit(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitStopSubStopAvpDone_From_WaitStopSubInit(vt_state_t *state, vt_event_t e, void *data);
vt_state_err_et post_handler_WaitStopSubStopAllDone(vt_state_t *state, vt_event_t e, void *data);




#endif
