/*
*********************************************************************************************************
*                                               uC/GUI
*                        Universal graphic software for embedded applications
*
*                     (c) Copyright 2002-2010, Micrium Inc., Weston, FL
*                     (c) Copyright 2002-2010, SEGGER Microcontroller Systeme GmbH
*
*               All rights reserved. Protected by international copyright laws.
*
*               uC/GUI is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
* Filename      : LCD_Protected.h
* Version       : 5.04a
* Purpose       : LCD level - To be used only internally by the GUI.
*********************************************************************************************************
*/

#ifndef LCD_PROTECTED_H
#define LCD_PROTECTED_H

#include "LCD.h"

/*********************************************************************
*
*       Data types
*/
typedef struct {
  LCD_COLOR * paColor;
  I16         NumEntries;
} LCD_LUT_INFO;

typedef struct {
  tLCDDEV_DrawPixel  * pfDrawPixel;
  tLCDDEV_DrawHLine  * pfDrawHLine;
  tLCDDEV_DrawVLine  * pfDrawVLine;
  tLCDDEV_FillRect   * pfFillRect;
  tLCDDEV_DrawBitmap * pfDrawBitmap;
} LCD_API_LIST;

/*********************************************************************
*
*       External data
*/
extern GUI_CONST_STORAGE U8 LCD_aMirror[256];
extern LCD_PIXELINDEX LCD__aConvTable[LCD_MAX_LOG_COLORS];

/*********************************************************************
*
*       Misc functions
*/
void LCD_UpdateColorIndices   (void);
int  LCD_PassingBitmapsAllowed(void);
void LCD_EnableCursor         (int OnOff);
void LCD_SelectLCD            (void);

void LCD_DrawBitmap(int x0, int y0,
                    int xsize, int ysize,
                    int xMul, int yMul,
                    int BitsPerPixel,
                    int BytesPerLine,
                    const U8 GUI_UNI_PTR * pPixel,
                    const LCD_PIXELINDEX * pTrans);

/*********************************************************************
*
*       Internal used color conversion routines
*/
tLCDDEV_Index2Color LCD_Index2Color_555;
tLCDDEV_Index2Color LCD_Index2Color_565;
tLCDDEV_Index2Color LCD_Index2Color_8666;
tLCDDEV_Index2Color LCD_Index2Color_888;
tLCDDEV_Index2Color LCD_Index2Color_8888;
tLCDDEV_Index2Color LCD_Index2Color_M555;
tLCDDEV_Index2Color LCD_Index2Color_M565;
tLCDDEV_Index2Color LCD_Index2Color_M888;
tLCDDEV_Color2Index LCD_Color2Index_8666;

tLCDDEV_Index2Color LCD_Index2Color_M3454;

#endif /* LCD_PROTECTED_H */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 	 	 		  	 		 	      		    	 		  	    		      	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 					 	   	 	 	 	 	  		 		   		    	 		  			 		 				 		   		 		 				 		 			  		 	  				 					 	 	 		  	  	  		      		  	   		      		  	 		 	      		  	  			  		  		  	   		   		   	 					 	  	  		      		  	   		      		  	 		 	      		  	  			  	 		 	   	  		    	 		  
