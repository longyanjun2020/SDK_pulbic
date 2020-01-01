/**
 *
 * @file    gss_prim.hc
 *
 * @brief   This module definies the message/primitive index of GSS task
 *
 * @author  Jack Hsieh
 *
 */
#ifndef __GSS_PRIM_HC__
#define __GSS_PRIM_HC__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_msgof.hc"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __GSS_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "gss_message_define__.hi"
};

#define G3D_TRACE                  (_CUS2|LEVEL_18)

/**
 *  @brief Primitive/Message ID Base Definition
 *         Please notice there are only 64 unit of ID for each function
 */
#define   GSS_DEV_BASE      (u16)(VM_CUS69_BASE)  /**< DEV task GSS Base ID*/ 

/**
 *  @brief MMP GSS System Primitive/Message ID
 */
#define   GSS_G3D_FRAME_END_IND         (GSS_DEV_BASE+0x01)  /**< G3D IRQ request */ 

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __GSS_PRIM_HC__ */


