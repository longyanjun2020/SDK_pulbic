/**
 * @file mmi_CBS_custom.h
 *
 * 
 * Class Id: CLSID_CBS
 *
 * @version $Id:  $
 */
#ifndef __MMI_CBS_CUSTOM_H__
#define __MMI_CBS_CUSTOM_H__

/*  define the max number of latest CB message that temporary keep in memory. 
 *  If user press Close(RSK) in Idle to ignore the current CB messages, 
 *  the max number of CB messages that will show in Miss event AP..
 */
#define CBS_Queue_SIZE_MAX   5

#endif /* __MMI_CBS_CUSTOM_H__ */
