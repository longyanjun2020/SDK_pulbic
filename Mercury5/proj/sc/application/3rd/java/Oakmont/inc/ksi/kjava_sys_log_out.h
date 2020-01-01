/**
 * @file kjava_sys_log_out.h
 */


#ifndef KJAVA_SYS_LOG_OUT_HEADER
#define KJAVA_SYS_LOG_OUT_HEADER

#ifdef __cplusplus
extern "C"{
#endif

/**
 *  @addtogroup Trace_Output_KSI
 *
 * @par Include file 
 * \#include kjava_sys_log_out.h
 *  @{
 */

/** 
 *        Outputs a logging message. 
 * @param message
 *        A pointer to a NUL-terminated message string.
 */
void kjava_sys_log_printOut(char *message);

/** @} */

#ifdef __cplusplus
}
#endif


#endif /* KJAVA_SYS_LOG_OUT_HEADER */
