
/**
 * @file
 * Browser Layout Dump functions
 *
 * Service API exposed by the Dump Functions
 *
 * <!-- #interface list begin -->
 * \section layout_dump Functions
 * -    NCCBrw_layout_dumpSetLogName()
 * -    NCCBrw_layout_dumpLayout()
 * <!-- #interface list end -->
 */

#ifndef __LAYOUT_DUMP_H_
#define __LAYOUT_DUMP_H_

#ifdef __cplusplus
extern  "C" {
#endif

/**
 * Set the dump log file name
 *
 * \param layout_log_name: the name for dump log,it should be a ASCII string terminated with '\0'
 * \return int32_t: 1 as set success, 0 as set failed
 */
int32_t NCCBrw_layout_dumpSetLogName(const char* layout_log_name);

/**
 * Dump the layout result (since the parser and the layout engine use the same data structure,
 * we can use this function to dump the parser's result as well), the log will be stored as
 * plain ASCII text file
 */
void  NCCBrw_layout_dumpLayout(void);

#ifdef __cplusplus
}
#endif

#endif /* __LAYOUT_DUMP_H_ */
