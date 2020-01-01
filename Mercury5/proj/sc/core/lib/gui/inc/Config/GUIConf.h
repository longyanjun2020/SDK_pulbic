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
* Filename      : GUIConf.h
* Version       : 5.04a
* Purpose       : Configuration of available features and default values.
*********************************************************************************************************
*/

#ifndef GUICONF_H
#define GUICONF_H

/*********************************************************************
*
*       Multi layer/display support
*/
#define GUI_NUM_LAYERS      64//34//16   // Maximum number of available layers

/*********************************************************************
*
*       Multi tasking support
*/
#define GUI_OS              (0)  // Compile with multitasking support

/*********************************************************************
*
*       Configuration of available packages
*/
#define GUI_SUPPORT_TOUCH   (0)  // Support a touch screen (req. win-manager)
#define GUI_SUPPORT_MOUSE   (0)  // Support a mouse
#define GUI_SUPPORT_UNICODE (0)  // Support mixed ASCII/UNICODE strings
#define GUI_WINSUPPORT      (0)  // Window manager package available
#define GUI_SUPPORT_MEMDEV  (0)  // Memory devices available
#define GUI_SUPPORT_AA      (0)  // Anti aliasing available

/*********************************************************************
*
*       Default font
*/
#define GUI_DEFAULT_FONT          &GUI_Font6x8

#endif  /* Avoid multiple inclusion */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 	 	 		  	 		 	      		    	 		  	    		      	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 					 	   	 	 	 	 	  		 		   		    	 		  			 		 				 		   		 		 				 		 			  		 	  				 					 	 	 		  	  	  		      		  	   		      		  	 		 	      		  	  			  		  		  	   		   		   	 					 	  	  		      		  	   		      		  	 		 	      		  	  			  	 		 	   	  		    	 		  
