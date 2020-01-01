/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkMediaExtension.h
 *  Media Extension Control
 */

/**
 * @addtogroup MediaControl_JSI_Advanced
 *
 * @{
 */

#ifndef __JKMEDIAEXTENSION_H__
#define __JKMEDIAEXTENSION_H__

#include "JkTypes.h"

#include "JkMediaStream.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * A structure defining extension to media optional control features.
 *
 * To implement extension, device manufacturer 
 * implements structures for the extension purpose and set 
 * their pointers to corresponding member in 
 * a JKT_MediaExtension structure, and set the 
 * pointer to the JKT_MediaExtension to the <i>pExtFuncs</i> member 
 * of the JKT_MediaControl structure. 
 * If a feature is not supported, JK_NULL can be set in the 
 * corresponding JKT_MediaExtension structure member. 
 * JBlend considers the JK_NULL member as an unsupported 
 * function and does not use the feature. 
 *
 * To implement media streaming, for example, device manufacturer
 * implements the JKT_Media_StreamControl function structure and set 
 * its pointer to the <i>pStreamFuncs</i> member of JKT_MediaExtension structure.
 * 
 * The <i>pExtFuncs</i> member of JKT_MediaExtension is reserved for future use;
 * set it to JK_NULL.
 */
typedef struct {
    /**
     * A pointer to the function structure defining streaming playback control functions.
     */
    JKT_Media_StreamControl const* pStreamFuncs;

    /**
     * Reserved.
     */
     void const* pMultiFuncs;
    /**
     * Reserved for future use.
     */
    void const* pExtFuncs;
} JKT_MediaExtension;
 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__JKMEDIAEXTENSION_H__ */

/** @} end of group */
