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
* Filename      : GUI_ConfDefaults.h
* Version       : 5.04a
* Purpose       : Defaults for GUI config switches.
*********************************************************************************************************
* Note(s)       : (1) Do not modify this file ! If you do, you will not be able do update to a later 
*                     GUI version !
*********************************************************************************************************
*/


#ifndef  GUI_CONFDEFAULTS_H
#define  GUI_CONFDEFAULTS_H

#include "GUIConf.h"

#ifndef   LCD_MAX_LOG_COLORS
  #define LCD_MAX_LOG_COLORS 256
#else
  #if (LCD_MAX_LOG_COLORS > 256)
    #error The value of LCD_MAX_LOG_COLORS must be <= 256!
  #endif
#endif

#ifndef GUI_BYTESPERPIXEL
  #define GUI_BYTESPERPIXEL 4
#endif

#if   (GUI_BYTESPERPIXEL != 4)
  #error This uC/GUI version only supports an internal length of 4 bytes per pixel!
#endif

#if   (GUI_BYTESPERPIXEL == 1)
  #define LCD_PIXELINDEX U8
#elif (GUI_BYTESPERPIXEL == 2)
  #define LCD_PIXELINDEX U16
#elif (GUI_BYTESPERPIXEL == 4)
  #define LCD_PIXELINDEX U32
#else
  #error The value of GUI_BYTESPERPIXEL needs to be 1, 2 or 4!
#endif

#ifndef LCD_YMAG
  #define LCD_YMAG 1
#endif
#ifndef LCD_XMAG
  #define LCD_XMAG 1
#endif

/**********************************************************************
*
*       Defaults for config switches
*
***********************************************************************
*/

/* Define "universal pointer". Normally, this is not needed (define will expand to nothing)
   However, on some systems (AVR - IAR compiler) it can be necessary ( -> __generic),
   since a default pointer can access RAM only, not the built-in Flash
*/
#ifndef GUI_UNI_PTR
  #define GUI_UNI_PTR
  #define GUI_UNI_PTR_USED 0
#else
  #define GUI_UNI_PTR_USED 1
#endif

/* Define const storage. Normally, this is not needed (define will expand to const)
   However, on some systems (AVR - IAR compiler) it can be necessary ( -> __flash const),
   since otherwise constants are copied into RAM
*/
#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

#ifndef GUI_USE_MEMDEV_1BPP_FOR_SCREEN
  #define GUI_USE_MEMDEV_1BPP_FOR_SCREEN 1
#endif

#ifndef GUI_BIDI_MAX_CHARS_PER_LINE
  #define GUI_BIDI_MAX_CHARS_PER_LINE 80
#endif

#ifndef GUI_SUPPORT_BIDI
  #define GUI_SUPPORT_BIDI 0
#endif

#ifndef GUI_ALLOC_SIZE
  #define GUI_ALLOC_SIZE      0
#endif

#ifndef GUI_MAXBLOCKS
  #define GUI_MAXBLOCKS (2 + GUI_ALLOC_SIZE / 32)
#endif

#ifndef GUI_SUPPORT_TOUCH
  #define GUI_SUPPORT_TOUCH   0
#endif

#ifndef GUI_SUPPORT_MOUSE
  #define GUI_SUPPORT_MOUSE   0
#endif

#ifndef GUI_SUPPORT_MEMDEV
  #define GUI_SUPPORT_MEMDEV  0
#endif

#ifndef GUI_OS
  #define GUI_OS              0
#endif

#ifndef GUI_SUPPORT_LARGE_BITMAPS
  #if GUI_ALLOC_SIZE > 65535
    #define GUI_SUPPORT_LARGE_BITMAPS 1
  #else
    #define GUI_SUPPORT_LARGE_BITMAPS 0
  #endif
#endif

#ifndef GUI_COMPATIBLE_MODE
  #define GUI_COMPATIBLE_MODE 1
#endif

#ifndef GUI_NUM_LAYERS
  #define GUI_NUM_LAYERS      1
#endif

#ifndef GUI_SUPPORT_CURSOR
  #define GUI_SUPPORT_CURSOR  (GUI_SUPPORT_MOUSE | GUI_SUPPORT_TOUCH)
#endif

#ifndef   GUI_SUPPORT_SPRITE
  #define GUI_SUPPORT_SPRITE 1
#endif

#ifndef   GUI_CURSOR_LAYER
  #define GUI_CURSOR_LAYER 0
#endif

#ifndef GUI_SELECT_JPEG
  #define GUI_SELECT_JPEG 0
#endif

#ifndef GUI_MEMCPY
  #define GUI_MEMCPY(pDest, pSrc, NumBytes) memcpy(pDest, pSrc, NumBytes)
#endif

#ifndef GUI_SUPPORT_ROTATION
  #define GUI_SUPPORT_ROTATION 1
#endif

/* In order to avoid warnings for undefined parameters */
#ifndef GUI_USE_PARA
  #if defined (__BORLANDC__) || defined(NC30) || defined(NC308)
    #define GUI_USE_PARA(para)
  #else
    #define GUI_USE_PARA(para) para=para;
  #endif
#endif

/* Default for types */
#ifndef GUI_TIMER_TIME
  #define GUI_TIMER_TIME int  /* default is to use 16 bits for 16 bit CPUs,
	                           32 bits on 32 bit CPUs for timing */
#endif

/* Types used for memory allocation */
#if (GUI_ALLOC_SIZE >= 32767) || (GUI_ALLOC_SIZE == 0)
  #define GUI_ALLOC_DATATYPE   I32
  #define GUI_ALLOC_DATATYPE_U U32
#else
  #define GUI_ALLOC_DATATYPE   I16
  #define GUI_ALLOC_DATATYPE_U U16
#endif

#ifndef   GUI_MAX_XBF_BYTES
  #define GUI_MAX_XBF_BYTES 200
#endif

#ifndef   GUI_MEMSET
  #define GUI_MEMSET GUI__memset
#endif


#endif   /* ifdef GUI_CONFDEFAULTS_H */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 	 	 		  	 		 	      		    	 		  	    		      	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 					 	   	 	 	 	 	  		 		   		    	 		  			 		 				 		   		 		 				 		 			  		 	  				 					 	 	 		  	  	  		      		  	   		      		  	 		 	      		  	  			  		  		  	   		   		   	 					 	  	  		      		  	   		      		  	 		 	      		  	  			  	 		 	   	  		    	 		  
