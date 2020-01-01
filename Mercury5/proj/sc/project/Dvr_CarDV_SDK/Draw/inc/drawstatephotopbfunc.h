
//==============================================================================
//
//  File        : drawstatephotopbfunc.h
//  Description : INCLUDE File for the DrawStatePhotoPBFunc function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#ifndef _DRAWSTATEPHOTOPBFUNC_H_
#define _DRAWSTATEPHOTOPBFUNC_H_

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void DrawStatePhotoPb_handler_Lcd( UINT32 ubEvent);
void DrawStatePhotoPb_handler_Hdmi(UINT32 ulEvent);
void DrawStatePhotoPb_handler_Tv(UINT32 ulEvent);

void DrawStateJpgPbMode_Update(void);
void DrawStateJpgPbPageSwitch(UINT8 ubPage);
void DrawStatePhotoPbInit_Lcd(void);
void DrawStatePhotoPbInit_Hdmi(UINT8 bID0, UINT8 bID1);
void DrawStatePhotoPbInit_Tv(UINT8 bID0, UINT8 bID1);
void DrawJpgPb_FileIndex(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawJpgPb_FileInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawJpgPb_DateInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawJpgPb_LockCurFile(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor,INT32 Para1);
#endif   // _DRAWSTATEPHOTOPBFUNC_H_ 

