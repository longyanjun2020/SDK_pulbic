#ifdef __B3_UPLOAD_NEW__
//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "dwl_medium.h"

//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------
bool    dwl_nandTrcOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
bool    dwl_nandTrcRead(dwl_handle_t phandle, void *pdata, u32 u32len);
bool    dwl_nandTrcClose(dwl_handle_t phandle);

#endif
