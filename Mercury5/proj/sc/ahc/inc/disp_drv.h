/*
 * disp_drv.h
 */
#include "lcd_common.h"

#define	DISP_NONE		0
#define	DISP_LCD		1
#define	DISP_LCDV		2
#define	DISP_NTSC		3
#define	DISP_PAL		4
#define	DISP_HDMI		5

typedef struct {
	unsigned short disp_w;
	unsigned short disp_h;
	unsigned short disp_clrs; // In ALL_FW, it would be the default off screen buffers to be created.
	                          // It should be 24/32 or 16. 24 is now treated as 32.
	unsigned short disp_type; // Currently this is for power-on image only.
} DISP_PROP;

DISP_PROP* RTNA_GetDisplayProp(void);
MMPF_PANEL_ATTR* RTNA_LCD_GetAttr(void);
