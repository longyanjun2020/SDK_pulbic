/**
 * @file mmi_javafactoryapp_custom.h
 *
 * JavaFactoryApp Customization Data
 *
 * @version $Id: mmi_javafactoryapp_custom.h 40354 2009-09-15 16:57:00Z code.lin $
 */

#ifndef __MMI_JAVAFACTORYAPP_CUSTOM_H__
#define __MMI_JAVAFACTORYAPP_CUSTOM_H__

// define the source folder path of the Java MIDlets
#define JAVA_MIDLET_SOURCE_PATH L"fs:/CARD/JAVA_GAMES/"

// define the destination storage to install Java MIDlets
#ifdef __JAVA_OAKMONT__
#define JAVA_MIDLET_DEST_STORAGE JAVASRV_STORAGE_PREINSTALL
#else
// JAVASRV_STORAGE_NAND or JAVASRV_STORAGE_MEMCARD
#define JAVA_MIDLET_DEST_STORAGE JAVASRV_STORAGE_MEMCARD
#endif


#endif // __MMI_JAVAFACTORYAPP_CUSTOM_H__

