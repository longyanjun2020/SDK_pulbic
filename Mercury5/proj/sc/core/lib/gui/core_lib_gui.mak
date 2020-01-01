#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

# c file list
SRC_C_LIST = \
	GUIConf.c\
	LCDConf.c\
	SIMConf.c\
	GUICC_111.c\
	GUICC_222.c\
	GUICC_233.c\
	GUICC_323.c\
	GUICC_332.c\
	GUICC_444_12.c\
	GUICC_444_12_1.c\
	GUICC_444_16.c\
	GUICC_555.c\
	GUICC_556.c\
	GUICC_565.c\
	GUICC_655.c\
	GUICC_666.c\
	GUICC_822216.c\
	GUICC_84444.c\
	GUICC_8666.c\
	GUICC_8666_1.c\
	GUICC_888.c\
	GUICC_8888.c\
	GUICC_M233.c\
	GUICC_M323.c\
	GUICC_M332.c\
	GUICC_M3454.c\
	GUICC_M444_12.c\
	GUICC_M444_16.c\
	GUICC_M555.c\
	GUICC_M556.c\
	GUICC_M565.c\
	GUICC_M655.c\
	GUICC_M666.c\
	GUICC_M8565.c\
	GUICC_M888.c\
	GUICC_M8888.c\
	GUICC_2.c\
	GUICC_4.c\
	GUICC_5.c\
	GUICC_0.c\
	GUICC_1.c\
	GUICC_555_Index2Color.c\
	GUICC_565_Index2Color.c\
	GUICC_8888_Index2Color.c\
	GUICC_888_Index2Color.c\
	GUICC_M3454_Index2Color.c\
	GUICC_M555_Index2Color.c\
	GUICC_M565_Index2Color.c\
	GUICC_M888_Index2Color.c\
	GUI_2DLib.c\
	GUI_AddBin.c\
	GUI_AddDec.c\
	GUI_AddDecMin.c\
	GUI_AddDecShift.c\
	GUI_AddHex.c\
	GUI_Alloc.c\
	GUI_ALLOC_AllocInit.c\
	GUI_ALLOC_AllocZero.c\
	GUI_Arc.c\
	GUI_BMP.c\
	GUI_BMP_DrawScaled.c\
	GUI_BMP_Serialize.c\
	GUI_CalcColorDist.c\
	GUI_Char.c\
	GUI_CharLine.c\
	GUI_CharM.c\
	GUI_CharP.c\
	GUI_CharPExt.c\
	GUI_CharPFrm.c\
	GUI_Circ.c\
	GUI_ClearRectEx.c\
	GUI_Color2Index.c\
	GUI_Color2VisColor.c\
	GUI_Core.c\
	GUI_Curs1.c\
	GUI_CursorArrowL.c\
	GUI_CursorArrowLI.c\
	GUI_CursorArrowLPx.c\
	GUI_CursorArrowM.c\
	GUI_CursorArrowMI.c\
	GUI_CursorArrowMPx.c\
	GUI_CursorArrowS.c\
	GUI_CursorArrowSI.c\
	GUI_CursorArrowSPx.c\
	GUI_CursorCrossL.c\
	GUI_CursorCrossLI.c\
	GUI_CursorCrossLPx.c\
	GUI_CursorCrossM.c\
	GUI_CursorCrossMI.c\
	GUI_CursorCrossMPx.c\
	GUI_CursorCrossS.c\
	GUI_CursorCrossSI.c\
	GUI_CursorCrossSPx.c\
	GUI_CursorHeaderM.c\
	GUI_CursorHeaderMI.c\
	GUI_CursorHeaderMPx.c\
	GUI_CursorPal.c\
	GUI_CursorPalI.c\
	GUI_Device.c\
	GUI_DispBin.c\
	GUI_DispCEOL.c\
	GUI_DispChar.c\
	GUI_DispChars.c\
	GUI_DispHex.c\
	GUI_DispString.c\
	GUI_DispStringAt.c\
	GUI_DispStringAtCEOL.c\
	GUI_DispStringHCenter.c\
	GUI_DispStringInRect.c\
	GUI_DispStringInRectEx.c\
	GUI_DispStringInRectWrap.c\
	GUI_DispStringLen.c\
	GUI_DrawBitmap.c\
	GUI_DrawBitmapEx.c\
	GUI_DrawBitmapExp.c\
	GUI_DrawBitmapHWAlpha.c\
	GUI_DrawBitmapMag.c\
	GUI_DrawBitmap_24.c\
	GUI_DrawBitmap_555.c\
	GUI_DrawBitmap_565.c\
	GUI_DrawBitmap_888.c\
	GUI_DrawBitmap_8888.c\
	GUI_DrawFocusRect.c\
	GUI_DrawGradient.c\
	GUI_DrawGraph.c\
	GUI_DrawGraphEx.c\
	GUI_DrawHLine.c\
	GUI_DrawLine.c\
	GUI_DrawPie.c\
	GUI_DrawPixel.c\
	GUI_DrawPoint.c\
	GUI_DrawPolygon.c\
	GUI_DrawPolyline.c\
	GUI_DrawRectEx.c\
	GUI_DrawRoundedRect.c\
	GUI_DrawVLine.c\
	GUI_EnableAlpha.c\
	GUI_EncExt.c\
	GUI_EncJS.c\
	GUI_ErrorOut.c\
	GUI_Exec.c\
	GUI_FillPolygon.c\
	GUI_FillRect.c\
	GUI_FillRectEx.c\
	GUI_FillRoundedRect.c\
	GUI_GetBitmapPixelColor.c\
	GUI_GetBitmapPixelIndex.c\
	GUI_GetClientRect.c\
	GUI_GetColor.c\
	GUI_GetDispPos.c\
	GUI_GetDrawMode.c\
	GUI_GetFont.c\
	GUI_GetFontInfo.c\
	GUI_GetFontSizeY.c\
	GUI_GetLineStyle.c\
	GUI_GetOrg.c\
	GUI_GetStringDistX.c\
	GUI_GetTextAlign.c\
	GUI_GetTextExtend.c\
	GUI_GetTextMode.c\
	GUI_GetVersionString.c\
	GUI_GetYSizeOfFont.c\
	GUI_GIF.c\
	GUI_GIF_DrawScaled.c\
	GUI_Goto.c\
	GUI_Index2Color.c\
	GUI_InitLUT.c\
	GUI_InvertRect.c\
	GUI_IsInFont.c\
	GUI_JOYSTICK.c\
	GUI_JPEG.c\
	GUI_JPEG_DrawScaled.c\
	GUI_Log.c\
	GUI_MergeRect.c\
	GUI_MOUSE.c\
	GUI_MOUSE_DriverPS2.c\
	GUI_MoveRect.c\
	GUI_OnKey.c\
	GUI_Pen.c\
	GUI_PID.c\
	GUI_PolyEnlarge.c\
	GUI_PolyMagnify.c\
	GUI_PolyRotate.c\
	GUI_Realloc.c\
	GUI_RectsIntersect.c\
	GUI_SaveContext.c\
	GUI_ScreenSize.c\
	GUI_SelectLayer.c\
	GUI_SelectLCD.c\
	GUI_SetAlpha.c\
	GUI_SetClipRect.c\
	GUI_SetColor.c\
	GUI_SetColorIndex.c\
	GUI_SetDecChar.c\
	GUI_SetDefault.c\
	GUI_SetDrawMode.c\
	GUI_SetFont.c\
	GUI_SetLBorder.c\
	GUI_SetLineStyle.c\
	GUI_SetOrg.c\
	GUI_SetPixelIndex.c\
	GUI_SetTextAlign.c\
	GUI_SetTextMode.c\
	GUI_SetTextStyle.c\
	GUI_SIF.c\
	GUI_SIF_Prop.c\
	GUI_SIF_PropExt.c\
	GUI_SIF_PropExtFrmInfo.c\
	GUI_SIF_PropFrm.c\
	GUI_SPRITE.c\
	GUI_Stream.c\
	GUI_StreamCreate.c\
	GUI_Task.c\
	GUI_Time.c\
	GUI_Timer.c\
	GUI_TOUCH.c\
	GUI_TOUCH_DriverAnalog.c\
	GUI_TOUCH_StoreState.c\
	GUI_TOUCH_StoreUnstable.c\
	GUI_UC.c\
	GUI_UC0.c\
	GUI_UC_ConvertUC2UTF8.c\
	GUI_UC_ConvertUTF82UC.c\
	GUI_UC_DispString.c\
	GUI_UC_EncodeNone.c\
	GUI_UC_EncodeUTF8.c\
	GUI_Val.c\
	GUI_Valf.c\
	GUI_WaitEvent.c\
	GUI_WaitKey.c\
	GUI_Warn.c\
	GUI_X.c\
	GUI_XBF.c\
	GUI_XBF_Prop.c\
	GUI_XBF_PropExt.c\
	GUI_XBF_PropFrm.c\
	GUI__AddSpaceHex.c\
	GUI__Arabic.c\
	GUI__BiDi.c\
	GUI__CalcTextRect.c\
	GUI__CompactPixelIndices.c\
	GUI__DivideRound.c\
	GUI__DivideRound32.c\
	GUI__DrawBitmap16bpp.c\
	GUI__ExpandPixelIndices.c\
	GUI__GetCursorPos.c\
	GUI__GetFontSizeY.c\
	GUI__GetNumChars.c\
	GUI__HandleEOLine.c\
	GUI__IntersectRect.c\
	GUI__IntersectRects.c\
	GUI__memcpy.c\
	GUI__memset.c\
	GUI__memset16.c\
	GUI__Read.c\
	GUI__ReduceRect.c\
	GUI__SetPixelAlpha.c\
	GUI__SetText.c\
	GUI__SinHQ.c\
	GUI__strcmp.c\
	GUI__strlen.c\
	GUI__Wrap.c\
	LCD.c\
	LCD_AA.c\
	LCD_Color.c\
	LCD_ControlCache.c\
	LCD_GetColorIndex.c\
	LCD_GetEx.c\
	LCD_GetNumDisplays.c\
	LCD_GetP.c\
	LCD_GetPixelColor.c\
	LCD_Index2ColorEx.c\
	LCD_Info.c\
	LCD_Mirror.c\
	LCD_MixColors256.c\
	LCD_NextPixelAPI.c\
	LCD_ReadRect.c\
	LCD_RLE16.c\
	LCD_RLE4.c\
	LCD_RLE8.c\
	LCD_Rotate180.c\
	LCD_RotateCCW.c\
	LCD_RotateCW.c\
	LCD_SelectLCD.c\
	LCD_Set.c\
	LCD_SetClipRectEx.c\
	LCD_UpdateColorIndices.c\
	GUIDRV_Lin_16.c\
	GUIDRV_Lin_16CCW.c\
	GUIDRV_Lin_24.c\
	GUIDRV_Lin_8.c\
	GUIDRV_Lin_ARGB32.c\
	GUIDRV_Lin_ARGB32CCW.c\
	F08_1.c\
	F08_ASCII.c\
	F10S_1.c\
	F10S_ASCII.c\
	F10_1.c\
	F10_ASCII.c\
	F13B_1.c\
	F13B_ASCII.c\
	F13HB_1.c\
	F13HB_ASCII.c\
	F13H_1.c\
	F13H_ASCII.c\
	F13_1.c\
	F13_ASCII.c\
	F16B_1.c\
	F16B_ASCII.c\
	F16_1.c\
	F16_1HK.c\
	F16_ASCII.c\
	F16_HK.c\
	F20B_1.c\
	F20B_ASCII.c\
	F20F_ASCII.c\
	F20_1.c\
	F20_ASCII.c\
	F24B_1.c\
	F24B_ASCII.c\
	F24_1.c\
	F24_ASCII.c\
	F32B_1.c\
	F32B_ASCII.c\
	F32_1.c\
	F32_ASCII.c\
	F4x6.c\
	F6x8.c\
	F6x8_1.c\
	F6x8_ASCII.c\
	F8x10_ASCII.c\
	F8x12_ASCII.c\
	F8x13_1.c\
	F8x13_ASCII.c\
	F8x15B_1.c\
	F8x15B_ASCII.c\
	F8x16.c\
	F8x16_1.c\
	F8x16_ASCII.c\
	F8x8.c\
	F8x8_1.c\
	F8x8_ASCII.c\
	FComic18B_1.c\
	FComic18B_ASCII.c\
	FComic24B_1.c\
	FComic24B_ASCII.c\
	FD24x32.c\
	FD32.c\
	FD36x48.c\
	FD48.c\
	FD48x64.c\
	FD60x80.c\
	FD64.c\
	FD80.c\
	
# cpp file list
#SRC_CPP_LIST = \
#	C4.cpp\
#	C5.cpp\
#	C6.cpp

# asm file list
#SRC_ASM_LIST =\
#	A1.asm\
#	A2.asm

# header file folder for this library 
PATH_H +=\
	$(PATH_core_lib_gui)/inc/Config\
	$(PATH_core_lib_gui)/inc/Core\
	$(PATH_core_lib_gui)/inc/DisplayDriver\
 
#	$(PATH_ex20)/ex21/ex22\
#	$(PATH_ex23)/ex24/ex25/ex26/ex27\
#	$(PATH_ex28)/ex29/ex30/ex31

# c/cpp source code for this library 
PATH_C =\
	$(PATH_core_lib_gui)/src/Config\
	$(PATH_core_lib_gui)/src/ConvertColor\
	$(PATH_core_lib_gui)/src/ConvertMono\
	$(PATH_core_lib_gui)/src/Core\
	$(PATH_core_lib_gui)/src/DisplayDriver\
	$(PATH_core_lib_gui)/src/Font\

# $(PATH_ex1)/ex2/ex3\
# $(PATH_ex4)/ex5/ex6/ex7/ex8\
# $(PATH_ex9)/ex10/ex11/ex12

# assembler source code for this library 
#PATH_ASM =\
# $(PATH_ex31)/ex32/ex33\
# $(PATH_ex34)/ex35/ex36/ex37/ex38\
# $(PATH_ex39)/ex40/ex41/ex42

# mark C_OPTIONS if there is no cpp files would be compiled
#C_OPTIONS += \
#	--cpp

