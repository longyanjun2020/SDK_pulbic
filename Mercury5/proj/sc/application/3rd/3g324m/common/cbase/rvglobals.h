#ifndef _rv_globals_h_
#define _rv_globals_h_


#include "rvglobalindexes.h"

#if defined(__cplusplus)
extern "C" {
#endif



/********************************************************************************************
 * RvStartGlobalDataServices
 * 
 * Initializes global data services
 *
 * INPUT   : None
 * OUTPUT  : started - tells whether service was initialized currently or in a 
 *                     previous call to the function;
 * RETURN  : the data pointer of NULL if fails
 */
RvStatus RvStartGlobalDataServices(OUT RvBool* started);

/********************************************************************************************
 * RvStartGlobalDataServices
 * 
 * Stops global data services
 *
 * INPUT   : None
 * OUTPUT  : None
 * RETURN  : None
 */
void RvStopGlobalDataServices(void);

/********************************************************************************************
 * RvGetGlobalDataPtr
 * 
 * Fetches the pointer to the global data structure
 *
 * INPUT   :  
 *           indx - the index of the global data structure
 * OUTPUT  : None.
 * RETURN  : the data pointer of NULL if fails
 */
RVCOREAPI void* RvGetGlobalDataPtr(IN int indx);


/********************************************************************************************
 * RvGlobalDataCreateFunc
 * Function to be supplied by the module wishing to create the global data structure.
 * This function will be called by global data server upon request
 * INPUT   : 
 *              index - index within thread vars array for the newly created structure
 *              usrData - pointer to arbitrary data that may be needed when creating 
 *                        global data structure
 * OUTPUT  : None.
 * RETURN  : Pointer to the newly created global data structure or NULL if the function fails
 */
typedef void* (*RvGlobalDataCreateFunc)(IN int index, IN void* usrData);

/********************************************************************************************
 * RvGlobalDataDestroyFunc
 * Function to be supplied by the module wishing to create the global data structure.
 * This function will be called by global data server upon request
 * INPUT   : 
 *              index - index within thread vars array where global data structure was held
 *              glDataPtr - pointer to global data structure to be destroyed 
 * OUTPUT  : None.
 * RETURN  : None
 */
typedef void (*RvGlobalDataDestroyFunc)(IN int index, IN void* glDataPtr);


/********************************************************************************************
 * RvCreateGlobalData
 * Instructs global data server to create the global data structure for specific index
 * INPUT   : 
 *              index - index within thread vars array for the newly created structure
 *              crtF - function that creates and initializes the global data structure
 *              usrData - pointer to arbitrary data (will be passed to crtF)
 *              dstrF - function that destroys the global data structure
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI RvStatus RvCreateGlobalData(IN int index, IN RvGlobalDataCreateFunc crtF, IN void *usrData, 
                            IN RvGlobalDataDestroyFunc dstrF);

/********************************************************************************************
 * RvDestroyGlobalData
 * Instructs global data server to destroy the global data structure for specific index
 * INPUT   : 
 *              index - index within thread vars array for the destroyed structure
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI RvStatus RvDestroyGlobalData(IN int index);

#if defined(__cplusplus)
}
#endif

typedef struct 
{
    int                         iIndex;
    int                         iRefCount;
    RvGlobalDataDestroyFunc     iDestroyFunc;
    void*                       iGlobalData;
} RvGlDataStruct;


#endif
