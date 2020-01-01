/**
 * @file	mmi_view_id_range.h
 * @version	$Id: mmi_view_id_range.h 40727 2009-09-17 16:30:23Z lih.wang $
 * @brief	This file defines the range of different kind of view id.
 */
#ifndef __MMI_VIEW_ID_RANGE_H__
#define __MMI_VIEW_ID_RANGE_H__


/* Reserved View Id range 0x0000~0x000F */
#define MMI_VIEW_ID_RESERVED_BEGIN	0x0000
#define MMI_VIEW_ID_RESERVED_END	0x000F

/* Common Dialog View Id range 0x0010~0x0FFF */
#define MMI_VIEW_ID_COMMON_BEGIN	0x0010
#define MMI_VIEW_ID_COMMON_END		0x01FF

/* Common Option View Id range 0x0010~0x0FFF */
#define MMI_VIEW_ID_OPTION_BEGIN	0x0200
#define MMI_VIEW_ID_OPTION_END		0x02FF

/* Common Popup View Id range 0x0010~0x0FFF */
#define MMI_VIEW_ID_POPUP_BEGIN	    0x0300
#define MMI_VIEW_ID_POPUP_END		0x03FF

/* AP View Id range 0x1000~0xFFFF */
#define MMI_VIEW_ID_AP_BEGIN		0x1000
#define MMI_VIEW_ID_AP_END			0xFFFF

#endif /* __MMI_VIEW_ID_RANGE_H__ */
