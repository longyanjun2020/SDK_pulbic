/**
 *
 * @file    cus_ps.h
 *
 * @brief   This file defines the Protocol Stack related interface for
 *          customer layer where the implementation might different between
 *          platforms.
 *          ** Note ** 
 *          The file is new created, new add related functions should be 
 *          added here!!
 *
 * @author  Alex Lin
 * @version $Id: cus_ps.h 15678 2008-10-29 06:59:18Z alex.lin $
 *
 */

#ifndef __CUS_PS_H__
#define __CUS_PS_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/

#include "remote.ho"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
#if defined(__QUAD_SIM_DUAL_STANDBY__)
typedef struct
{
    u8 MaxSimNum;               /* maximun number of SIM card supported */
    u8 MaxActiveSimNum;     /* maximun number of active SIM card supported */
    bool Sim1MuxCtrl;
    bool Sim2MuxCtrl;
} cus_psSimInfo_t;
#endif


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/

 
/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION PROTOTYPE                                                */
/*--------------------------------------------------------------------------*/
bool    cus_psEnhanceSimPadDrive( void );
bool    cus_psIsDualImeiEnabled( void );
bool    cus_psIsFacDelayRrInit(void);
bool    CusIsGSMStatusUpdate(void);


#if defined(__QUAD_SIM_DUAL_STANDBY__)
void cus_PsGetSimInfo(cus_psSimInfo_t *pSimInfo);
#endif
 
#ifdef __TEST_SIM_AUTOATTACH__
bool cus_PsGetGPRSAtuoAttachDisable(void);
#endif /* __TEST_SIM_AUTOATTACH__ */


#endif



