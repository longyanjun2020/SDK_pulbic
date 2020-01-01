#ifndef _AF_H_
#define _AF_H_


#include "isp_if.h"


/*****************************************************************************/
/* AF Definitions                                                            */
/*****************************************************************************/
typedef struct {
	// Version Control
	ISP_IF_VERSION*			Version;							// AF version

	// General Settings
	ISP_AF_TYPE				Type;								// one shot or continuous (AI servo)
	ISP_AF_MODE				Mode;								// auto, manual, macro, full, pan, etc.
	ISP_UINT8				FastFlag;							// AF fast mode
	ISP_UINT32				SysMode;							// AF system mode (normal, video, ...)

	// Acc Related
	ISP_UINT32				*AFAcc;								// AF ACC buffer (store all acc)	// Read only - don't modify it in your AF algorithm

	// Motor Related
	ISP_UINT16				Pos;								// motor - target position
	ISP_UINT16				NormalMin;							// motor - normal mode min position
	ISP_UINT16				NormalMax;							// motor - normal mode max position
	ISP_UINT16				MacroMin;							// motor - macro mode min position
	ISP_UINT16				MacroMax;							// motor - macro mode max position
	ISP_UINT8				PosBitwidth;						// motor - target position bitwidth

	// Custom Parameters
	ISP_CUSTOM_WIN_MODE		CustomWinMode;						// AF custom mode (on, off)
	ISP_UINT32				CustomWin[4];						// AF custom mode window (x_start, x_end, y_start, y_end)
	ISP_UINT32				CustomWinBase;						// AF custom mode window base
	ISP_UINT32				CustomWinACCDiv;					// AF custom mode window ACCDiv

	// Debug Data
	ISP_UINT8				DbgData[32];						// debug data - used to store debug data (will be shown in JPEG)

	// get AF result
	ISP_AF_RESULT			(*GetResult)(void);					// get AF status

	// get CAF result
	ISP_AF_RESULT			(*GetCAFResult)(void);					// get CAF status

	// set AF mode
	ISP_UINT8				(*SetMode)(ISP_AF_MODE mode);		// set AF mode (ex. normal, macro, full, pan, etc.)

	// send command to algorithm
	ISP_CMD_STATUS			(*SendCommand)(ISP_UINT32 cmd, void *buf_ptr, ISP_UINT32 size, ISP_UINT32 count);

} VENUS_AF_CONFIG;

extern VENUS_AF_CONFIG gAFConfig;


#endif // _AF_H_
