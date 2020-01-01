#ifndef _AE_H_
#define _AE_H_


#include "isp_if.h"


/*****************************************************************************/
/* AE Definitions                                                            */
/*****************************************************************************/
typedef struct {
	// Version Control
	ISP_IF_VERSION*			Version;					// AE version

	// General Settings
	ISP_UINT32				ISO;						// ISO value (50, 100, 200, 400, etc.; 0 is auto)
	ISP_AE_MODE				Mode;						// AE mode
	ISP_UINT32				FPS;						// frame rate control (auto/fix fps) x10
	ISP_UINT32				MinFPS;						// min frame rate (auto fps mode) x10
	ISP_UINT32				MaxFPS;						// max frame rate (auto fps mode) x10
	ISP_UINT32				MaxSensorFPS;				// max sensor frame rate (sensor hardware limitation) x10
	ISP_AE_METERING			MeteringMode;				// metering mode (average, center, spot, etc.)
	ISP_AE_FLICKER			FlickerMode;				// flicker mode (50HZ, 60HZ, auto, off)
	ISP_AE_FLICKER			FlickerModeAuto;			// auto flicker mode results (50HZ, 60HZ)
	ISP_INT32				EV;							// exposure value (-2.5, -2.25, ..., -0.25, 0, 0.25, 0.5, ... , 2.5)
	ISP_INT32				EVBias;						// EV bias
	ISP_UINT32				EVBiasBase;					// EV bias base
	ISP_UINT32				AvgLuma;					// HW ACC Luma value(8bit)
	ISP_UINT32				FastFlag;					// fast AE mode flag (1->fast AE is turned on)
	ISP_UINT32				InputRatio;					// zoom ratio (view angle of zoomed preview)
	ISP_UINT32				ROI_enable;					// ROI switch to ROI win (for PTZ function)
	ISP_UINT32				ROI_type;					// ROI type, 0: set 256 win, 1: set roi win (for PTZ function)
	ISP_UINT32				ROI_x_str;					// ROI win x start, base: VIF output size (for PTZ function)
	ISP_UINT32				ROI_y_str;					// ROI win y start (for PTZ function)
	ISP_UINT32				ROI_width;					// ROI win width   (for PTZ function)
	ISP_UINT32				ROI_height;					// ROI win height  (for PTZ function)
	ISP_UINT32				SysMode;					// AE system mode (normal, video, ...)
	ISP_FLASH_STATUS		FlashStatus;				// flash status (on, off)

	// Acc Related
	ISP_UINT32*				AEAcc;						// AE Acc - the pointer to acc buffer
	ISP_UINT32				AEAccDiv;					// single AE Acc window size (could be used to normalize Acc)

	ISP_UINT32*				FlickerAcc;					// Flicker Acc - the pointer to acc buffer
	ISP_UINT32*				HistAcc;					// Hist Acc - the pointer to acc buffer
	ISP_UINT32				HistAccSum;					// Hist Acc - sum of hist acc
	ISP_INT32				HistAccSumState;			// Hist Acc - wait for two times get acc
	ISP_INT32				HistAccSumDone;				// Hist Acc - update sum of hist acc when window changed

	ISP_UINT32				EdgeAcc[5];					// Edge Acc (0: total | 1-2: H | 3-4: V)

	// Exposure Parameters
	ISP_UINT32				RefreshFlag;				// if AE related settings are set, this flag will be triggered.

	// final shutter, gains, sensor vsync
	ISP_UINT32				Fnum;						// f-number
	ISP_UINT32				FnumBase;					// f-number base
	ISP_UINT32				Shutter;					// shutter | 1s: ShutterBase
	ISP_UINT32				ShutterBase;				// shutter base
	ISP_UINT32				Gain;						// gain | 1X: GainBase
	ISP_UINT32				GainBase;					// gain base
	ISP_UINT32				SensorVsync;				// vsync | 1s: SensorVsyncBase
	ISP_UINT32				SensorVsyncBase;			// vsync base

	ISP_UINT32				HDR_ShortShutter;			// shutter | 1s: ShutterBase
	ISP_UINT32				HDR_ShortGain;				// shutter | 1s: ShutterBase
	
	// PASM mode
	ISP_UINT32				ManualFnum;					// manual f-number      (for A, M modes)
	ISP_UINT32				ManualFnumBase;				// manual f-number base (for A, M modes)
	ISP_UINT32				ManualShutter;				// manual shutter       (for S, M modes)
	ISP_UINT32				ManualShutterBase;			// manual shutter base  (for S, M modes)

	// Custom Parameters
	ISP_CUSTOM_WIN_MODE		CustomWinMode;				// AE custom mode (on, off)
	ISP_UINT32				CustomWin[4];				// AE custom mode window (x_start, x_end, y_start, y_end)
	ISP_UINT32				CustomWinBase;				// AE custom mode window base
	ISP_UINT32				CustomWinCur;				// AE custom mode window current intensity
	ISP_UINT32				CustomWinTar;				// AE custom mode window target intensity

	// Debug Data
	ISP_UINT32				DbgData[32];				// debug data - used to store debug data (will be shown in JPEG)

	// get AE status
	ISP_AE_STATUS			(*GetStatus)(void);

	// update AE before preview
	void					(*UpdateBeforePreview)(void);

	// update AE before capture
	void					(*UpdateBeforeCapture)(void);

	// get current light condition
	ISP_UINT32				(*GetLightCond)(void);

	// get current 16x light condition
	ISP_UINT32				(*GetLightCondx16)(void);

	// get current light condition
	ISP_UINT32				(*GetBackLightCond)(void);

	// control sensor addition mode
	ISP_UINT8				(*GetAdditonMode)(void);

	// Check AE converged or not
	ISP_UINT8				(*AEConverge)(void);

	// control sensor addition mode
	void					(*SetAdditonMode)(ISP_UINT8 flag);
	
	// set binning mode or energy change rate for capture calculate.
	void					(*setBinningMode)(ISP_UINT8 N,ISP_UINT8 M);
	
	//update AE converge table from IQ file
	void					(*UpdateHistAETbl)(ISP_UINT8 index);

	// send command to algorithm
	ISP_CMD_STATUS			(*SendCommand)(ISP_UINT32 cmd, void *buf_ptr, ISP_UINT32 size, ISP_UINT32 count);
	ISP_UINT8 NaturalAE_Enable;
	
	ISP_UINT32 EVTarget_offset;
	
	//Customer Max Gain & Max Shutter	
	ISP_UINT32 CustomMinExposureFPS;
	ISP_UINT32 CustomMaxGain;	
	
	ISP_CUSTOM_WEIGHT_MODE CustomWeightMode;
	ISP_UINT8 *CustomWeight;

} VENUS_AE_CONFIG;

extern VENUS_AE_CONFIG gAEConfig;


#endif // _AE_H_
