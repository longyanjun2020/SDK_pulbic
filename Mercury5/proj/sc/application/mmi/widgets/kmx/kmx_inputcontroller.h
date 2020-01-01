
#ifndef KMX_INPUTCONTROLLER_H
#define KMX_INPUTCONTROLLER_H

#ifdef __cplusplus
extern "C"{
#endif

void InputController_InitInputModeList(InputController_t *pThis);
void InputController_KMX_SwitchInputMode(InputController_t *pThis, u32 inputMode);
void InputController_KMX_ImChanged_Notify(InputController_t *pThis, int im_mode, int case_info);

#ifdef __cplusplus
}
#endif

#endif /* KMX_INPUTCONTROLLER_H */
