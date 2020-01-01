/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for the GUI Toolkit as a whole.
 */

#ifndef ___GUI_USER_TOOLKIT_H
#define ___GUI_USER_TOOLKIT_H

#include <JkTypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Initialize
 * @{
 */

/**
 * The GUI Toolkit initialization function.
 * 
 * @param argc
 *        reserved
 * @param argv
 *        reserved
 *
 * @return
 *         Return 0 if initialization succeeds, or a negative value if it fails.
 *
 *     Perform initialization processing necessary for using the GUI Toolkit.
 *
 */
JKSint32 JgurInit(int argc, const char *argv[]);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_USER_TOOLKIT_H */

