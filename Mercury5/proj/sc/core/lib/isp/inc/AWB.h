#ifndef _AWB_H_
#define _AWB_H_


#include "isp_if.h"


/*****************************************************************************/
/* AWB Definitions                                                           */
/*****************************************************************************/
typedef struct {
	// Version Control
	ISP_IF_VERSION*			Version;					// WB version

	// General Settings
	ISP_AWB_MODE			Mode;						// WB mode
	ISP_UINT32				ColorTemp;					// color temperature
	ISP_INT32				ColorTempAdjust;			// color temperature adjustment (warmer or colder)
	ISP_UINT32				SysMode;					// AWB system mode (normal, video, ...)
	ISP_UINT32				FastFlag;					// fast AWB mode flag (1->fast AWB is turned on)

	// Acc Related
	ISP_UINT32*				AWBAcc;						// AWB Acc - the pointer to acc buffer
	ISP_UINT32				AWBAccDiv;					// AWB Acc normalization divider
	ISP_UINT32				AWBOpdAcc[32];				// AWB OPD Acc
	ISP_UINT32				InputRatio;					// zoom ratio (view angle of zoomed preview)

	// AWB Parameters
	ISP_UINT32				GainR;						// R Gain | 1X: GainBase
	ISP_UINT32				GainG;						// G Gain | 1X: GainBase
	ISP_UINT32				GainB;						// B Gain | 1X: GainBase
	ISP_UINT32				GainBase;

	// Custom Parameters
	ISP_CUSTOM_WIN_MODE		CustomWinMode;				// AWB custom mode (on, off)
	ISP_UINT32				CustomWin[4];				// AWB custom mode window (x_start, x_end, y_start, y_end)
	ISP_UINT32				CustomWinBase;				// AWB custom mode window base

	// Debug Data
	ISP_UINT32				DbgData[32];				// debug data - used to store debug data (will be shown in JPEG)

	// get current color temperature
	ISP_UINT32				(*GetColorTemp)(void);

	// update AWB before preview
	void					(*UpdateBeforePreview)(void);

	// update AWB before capture
	void					(*UpdateBeforeCapture)(void);

	// send command to algorithm
	ISP_CMD_STATUS			(*SendCommand)(ISP_UINT32 cmd, void *buf_ptr, ISP_UINT32 size, ISP_UINT32 count);

} VENUS_AWB_CONFIG;

extern VENUS_AWB_CONFIG gAWBConfig;


#endif // _AWB_H_
