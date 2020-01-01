/**
 * @file mmi_offapp_custom.h
 *
 * @version $Id:
 */
#ifndef __MMI_OFFAPP_CUSTOM_H__
#define __MMI_OFFAPP_CUSTOM_H__
#include "mmi_layout.h"

//<<Customize data begin>>
#ifdef _MSIM_	//for PC simulator
#define OFFAPP_POWEROFF_ANIM_TIMER 3200
#else
#define OFFAPP_POWEROFF_ANIM_TIMER 7000
#endif

#define OFFAPP_FACTORY_POWER_ON_ALARM_TIMER 5  // Set an alarm to trigger the handset to power on when master restore is executed in factory mode.(MSZ requirement)

//
// Group: OffApp Layout Definitions
//

#if defined (__MMI_LAYOUT_QVGA_H__)
#define		OFFAPP_BOTTOMBGWIDGET_HEIGHT	(70)
#define		OFFAPP_BOTTOMBGWIDGET_POS_X		(0)
#define		OFFAPP_BOTTOMBGWIDGET_POS_Y		(250)
#define		OFFAPP_BUTTONWIDGET_WIDTH		(198)
#define		OFFAPP_BUTTONWIDGET_HEIGHT		(34)
#define		OFFAPP_BUTTONWIDGET_POS_X		(21)
#define		OFFAPP_BUTTONWIDGET_POS_Y		(268)
#define		OFFAPP_SLIDEWIDGET_HEIGHT		(60)

#elif defined (__MMI_LAYOUT_QCIF_PLUS_H__)
#define		OFFAPP_BOTTOMBGWIDGET_HEIGHT	(48)
#define		OFFAPP_BOTTOMBGWIDGET_POS_X		(0)
#define		OFFAPP_BOTTOMBGWIDGET_POS_Y		(172)
#define		OFFAPP_BUTTONWIDGET_WIDTH		(140)
#define		OFFAPP_BUTTONWIDGET_HEIGHT		(24)
#define		OFFAPP_BUTTONWIDGET_POS_X		(18)
#define		OFFAPP_BUTTONWIDGET_POS_Y		(184)
#define		OFFAPP_SLIDEWIDGET_HEIGHT		(40)

#elif defined (__MMI_LAYOUT_HVGA_320_480_H__)
#define		OFFAPP_BOTTOMBGWIDGET_HEIGHT	(105)
#define		OFFAPP_BOTTOMBGWIDGET_POS_X		(0)
#define		OFFAPP_BOTTOMBGWIDGET_POS_Y		(375)
#define		OFFAPP_BUTTONWIDGET_WIDTH		(264)
#define		OFFAPP_BUTTONWIDGET_HEIGHT		(50)
#define		OFFAPP_BUTTONWIDGET_POS_X		(28)
#define		OFFAPP_BUTTONWIDGET_POS_Y		(402)
#define		OFFAPP_SLIDEWIDGET_HEIGHT		(90)

#elif defined (__MMI_LAYOUT_WQVGA_240_400_H__)
#define		OFFAPP_BOTTOMBGWIDGET_HEIGHT	(70)
#define		OFFAPP_BOTTOMBGWIDGET_POS_X		(0)
#define		OFFAPP_BOTTOMBGWIDGET_POS_Y		(330)
#define		OFFAPP_BUTTONWIDGET_WIDTH		(198)
#define		OFFAPP_BUTTONWIDGET_HEIGHT		(34)
#define		OFFAPP_BUTTONWIDGET_POS_X		(21)
#define		OFFAPP_BUTTONWIDGET_POS_Y		(348)
#define		OFFAPP_SLIDEWIDGET_HEIGHT		(60)

#endif
//<<Customize data end>>

#endif /* __MMI_OFFAPP_PRIV_H__ */
