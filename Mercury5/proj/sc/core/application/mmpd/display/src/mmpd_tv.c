
#ifdef BUILD_CE
#undef BUILD_FW
#endif

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_display.h"
#include "mmpf_display.h"

/** @addtogroup MMPD_Display
 *  @{
 */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void ____TV_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_Display_SetTVOutput
//  Description : 
//------------------------------------------------------------------------------
/** 
@brief The function set the needed parameter for TV 
@param[in] controller  the display controller
@param[in] tvattribute struct with TV related information
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Display_SetTVOutput(MMP_DISPLAY_CONTROLLER 	controller, 
								 MMP_TV_ATTR				*tvAttr,
								 MMP_DISPLAY_RGB_IF 		rgbIf)
{
	return MMP_ERR_NONE;  
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_Initialize
//  Description : Enable TV interface
//------------------------------------------------------------------------------
/**
@brief The function call Firmware to init TV encoder
@param[in] bInit 1 for enable TC, 0 for disable TV.
*/
MMP_ERR MMPD_TV_Initialize(MMP_BOOL bInit, MMP_TV_TYPE output_panel)
{
    return MMP_ERR_NONE;    
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_EnableDisplay
//  Description : Enable TV interface
//------------------------------------------------------------------------------
/** 
@brief The function enable TV_IF. After enable TV_IF, the real signal send to TV

@param[in] enable  1 to enable TV IF,  0 to disable TV IF
*/
MMP_ERR MMPD_TV_EnableDisplay(MMP_UBYTE enable)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_SetInterface
//  Description : Initialize TV interface
//------------------------------------------------------------------------------
/** @brief The function set all attribute for TV

The function set TV attributes such as type(NTSC/PAL), start X, Y, Width, Height and background color.
@param[in] tvattribute Attributes for type(NTSC/PAL), start X, Y, Width, Height and background color.
*/
MMP_ERR MMPD_TV_SetInterface(MMP_TV_ATTR *tvattribute)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_EncRegSet
//  Description : General function for setting TV encoder register
//------------------------------------------------------------------------------
/** @brief General function for setting TV encoder register
@param[in] addr Register address.
@param[in] data Register value.
@retval MMP_ERR_NONE Success.
@retval MMP_DISPLAY_ERR_NOT_SUPPORT Fail.
*/
MMP_ERR MMPD_TV_EncRegSet(MMP_ULONG addr, MMP_ULONG data)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_EncRegGet
//  Description : General function for getting TV encoder register
//------------------------------------------------------------------------------
/** @brief General function for getting TV encoder register
@param[in] addr Register address.
@param[out] data Register value.
@retval MMP_ERR_NONE Success.
@retval MMP_DISPLAY_ERR_NOT_SUPPORT Fail.
*/
MMP_ERR MMPD_TV_EncRegGet(MMP_ULONG addr, MMP_ULONG *data)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_SetBrightLevel
//  Description : Function for setting TV Bright Level
//------------------------------------------------------------------------------
/** @brief Function for setting TV Bright Level
@param[in] ubLevel Bright level
@retval MMP_ERR_NONE Success.
@retval MMP_DISPLAY_ERR_NOT_SUPPORT Fail.
*/
MMP_ERR MMPD_TV_SetBrightLevel(MMP_UBYTE ubLevel)
{
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_GetBrightLevel
//  Description : Function for getting TV Bright Level
//------------------------------------------------------------------------------
/** @brief Function for getting TV Bright Level
@param[in] *pubLevel Bright level
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_TV_GetBrightLevel(MMP_UBYTE *pubLevel)
{
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_SetGamma
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_TV_GetGamma(MMP_DISPLAY_TV_GAMMA *DspyGamma)
{
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_SetContrast
//  Description :
//------------------------------------------------------------------------------
/**
@brief Luma scale of contrast in main channel.
@param[in] usLevel Contrast level.
@retval MMP_ERR_NONE Success.
@retval MMP_DISPLAY_ERR_NOT_SUPPORT Fail.
*/
MMP_ERR MMPD_TV_SetContrast(MMP_USHORT usLevel)
{
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_GetContrast
//  Description :
//------------------------------------------------------------------------------
/**
@brief Luma scale of contrast in main channel.
@param[in] *pusLevel Contrast level.
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_TV_GetContrast(MMP_USHORT *pusLevel)
{
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_SetSaturation
//  Description :
//------------------------------------------------------------------------------
/**
@brief Chroma scale of saturation in main and second channels.
@param[in] ubUlevel Saturation U scale level.
@param[in] ubVlevel Saturation V scale level.
@retval MMP_ERR_NONE Success.
@retval MMP_DISPLAY_ERR_NOT_SUPPORT Fail.
*/
MMP_ERR MMPD_TV_SetSaturation(MMP_UBYTE ubUlevel, MMP_UBYTE ubVlevel)
{	
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_GetSaturation
//  Description :
//------------------------------------------------------------------------------
/**
@brief Chroma scale of saturation in main and second channels.
@param[in] *pubUlevel Saturation U scale level.
@param[in] *pubVlevel Saturation V scale level.
@retval MMP_ERR_NONE Success.
@retval MMP_DISPLAY_ERR_NOT_SUPPORT Fail.
*/
MMP_ERR MMPD_TV_GetSaturation(MMP_UBYTE *pubUlevel, MMP_UBYTE *pubVlevel)
{
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_TV_SetInterlaceMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_TV_SetInterlaceMode(MMP_BOOL bEnable)
{
    return MMPF_TV_SetInterlaceMode(bEnable);
}

/// @}

#ifdef BUILD_CE
#define BUILD_FW
#endif
