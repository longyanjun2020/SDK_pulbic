/**
 * @file mmi_mae_class.h
 *
 * This file defines all the class ids and interface ids in MAE platform.
 *
 * This file collects all the class and interface ids used in MAE platform.
 * Names of the classes and their constructors are actually defined in another
 * header file "mmi_mae_clstbl.h". But users need only this file to use class and
 * interface ids.
 *
 * @version $Id: mmi_mae_class.h 1798 2009-09-21 02:37:54Z kenny.wu $
 */

#ifndef __MMI_MAE_CLASS_H__
#define __MMI_MAE_CLASS_H__

//
// enums of interface ids
//
enum
{
    IID_BASE = 0,
    IID_SHELL,
    IID_HANDLER,
    IID_FONT,
    IID_BITMAP,
    IID_DISPLAY,
    IID_IMAGE,
    IID_IMAGEMAKER,
    IID_STREAM,
    IID_MEMSTREAM,
    IID_FSTREAM,
    IID_FILEMGR,
    IID_CLOCK,
    IID_IBATTERY,
    IID_RESCTRL,
    IID_MEDIA,
    IID_CAMERA,
    IID_SYSSTAT,
    IID_CONTENT,
    IIT_CATEGORY,
    IID_CONTENTMGR,
    IID_CONTENTBROWSER,
    IID_TASKDB,
    IID_TASKDBMGR,
    IID_EVENTDB,
    IID_LOGDB,
    IID_LOGDBMGR,
    IID_CONFIG,
    IID_SOCKET,
    IID_TOUCHSRV,
    IID_SENSORMGR,
    IID_MOTIONDETECTOR,
    IID_APPLET,
    IID_TEXTTABLE,
    IID_TEXT,
    IID_FILELIST,

#ifdef __RFID__
	IID_RFIDREADER,
#endif	//__RFID__

	    /* Model */
    IID_MODEL,
    IID_LISTMODEL,
    IID_ARRAYMODEL,
    IID_VECTORMODEL,
    IID_DATAMODEL,
    IID_INTERFACEMODEL,
    IID_IMAGEMODEL,

//    IID_THEMEMGR,

    IID_GPS,
    IID_3D,
    IID_MAE_PREDEFINED_END
};

#endif //__MAE_CLASS_H__
// end of file
