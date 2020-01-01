#if ! defined( DRIVER_DRIVER_h )
#define DRIVER_DRIVER_h
/*****************************************************************************/
/* DRIVER_DRIVER_h                                                           */
/* DRIVER.h                                                                  */
/* 2000/09                                                                   */
/* Copyright 2000 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

typedef struct _DRIVER_CONTEXT {

    void *          synthDrvContext;
    void *          waveDrvContext;
    void *          textDrvContext;
    void *          pictDrvContext;
    void *          ledDrvContext;
    void *          vibDrvContext;

} DRIVER_CONTEXT, *PDRIVER_CONTEXT;

/*****************************************************************************/

extern
PDRIVER_CONTEXT
DriverCreate(
    void *  deviceContext
);

extern
void
DriverDestroy(
    PDRIVER_CONTEXT C
);

/*****************************************************************************/
#endif  /* ! defined( DRIVER_DRIVER_h ) */
