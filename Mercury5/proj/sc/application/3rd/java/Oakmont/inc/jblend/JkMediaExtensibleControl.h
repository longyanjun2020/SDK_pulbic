/***************************************************************************/
/*                                                                         */
/*        Copyright 2004 Aplix Corporation. All rights reserved.           */
/*                                                                         */
/***************************************************************************/
/**
 * @file JkMediaExtensibleControl.h
 * 
 *  Addition of Extended Control 
 */

/**
 * @addtogroup MediaControl_JSI_Extensible
 *
 * @{
 */

#ifndef __JKMEDIAEXTENSIBLECONTROL_H__
#define __JKMEDIAEXTENSIBLECONTROL_H__

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  A structure defining extended control header.
 */
typedef struct JKT_MediaExt_ControlHeader {
	/**
     *  The extended control ID
	 */
    JKUint32 funcID;
    /**
     *  A pointer to the function structure defining an extended control.
	 */
    void const* pFuncTable;
} JKT_MediaExt_ControlHeader;

/**
 *  A structure defining extended control.
 */
typedef struct JKT_MediaExt_ControlRoot {
	/**
     *  The element count of the JKT_MediaExt_FuncHeader array indicated by 
     *  <i>pExtFuncHeader</i>
	 */
    const JKUint32 count;
    /**
     * A pointer to an array of extended control header.
	 */
    JKT_MediaExt_ControlHeader const* pExtFuncHeadres;
} JKT_MediaExt_ControlRoot;

#define JKTMEDIA_CTRID_TERMINATOR 0xffffffff

/*
 * Above structures are used like this.
 *
  JKT_MediaExtension
	+-------------+
	|             |      JKT_MediaExt_ControlRoot
	|  pExtFuncs ------> +-----------------+
	+-------------+      |                 |
	                     |  count          |        JKT_MediaExt_ControlHeader
	                     |  funcHeaders*  --------> +- T_FuncHeaderA -+
	                     +-----------------+        |  funcID_A       |      Each Control
	                                                |  funcTableA* --------> +- FunctableA -+
	                                                +-----------------+      |              |
	                                                +- T_FuncHeaderB -+      |              |
	                                                |  funcID_B       |      +--------------+
	                                                |  funcTableB* --------> +- FunctableB -+
	                                                +-----------------+      |              |
	                                                                         |              |
	                                                                         +--------------+
 */


#ifdef __cplusplus
}
#endif

#endif /* !__JKMEDIAEXTENSIBLECONTROL_H__ */

/** @} end of group */
