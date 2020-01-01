/**
 * @file 
 */

/**
 * @addtogroup Module_PIM_Data_Types
 *
 * @{
 */

#ifndef ___JK_PIM_CONTACT_H
#define ___JK_PIM_CONTACT_H

#ifdef __cplusplus
extern "C" {
#endif



/** 
 *  @name Field ID of Contact Interface.
 *  Field identifiers defined in the PIM optional package specification for fields
 *  in lists of type #JK_PIM_CONTACT.
 *  See <code>javax.microedition.pim.Contact</code> specification.
 *  
 *  This is used as a value for the <i>fieldId</i> member of JKPIMFieldDef structure. 
 */
/*@{*/ 

/**
 *  Field ID of <code>Contact</code>: ADDR
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ADDR</code>.
 *  The data type for this field is #JK_PIM_STRING_ARRAY.
 */
#define JK_PIM_CONTACT_ADDR					100

/**
 *  Field ID of <code>Contact</code>: BIRTHDAY
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.BIRTHDAY</code>.
 *  The data type for this field is #JK_PIM_CALENDAR.
 */
#define JK_PIM_CONTACT_BIRTHDAY				101

/**
 *  Field ID of <code>Contact</code>: CLASS
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.CLASS</code>.
 *  The data type for this field is #JK_PIM_INT.
 */
#define JK_PIM_CONTACT_CLASS				102

/**
 *  Field ID of <code>Contact</code>: EMAIL
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.EMAIL</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_EMAIL				103

/**
 *  Field ID of <code>Contact</code>: FORMATTED_ADDR
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.FORMATTED_ADDR</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_FORMATTED_ADDR		104

/**
 *  Field ID of <code>Contact</code>: FORMATTED_NAME
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.FORMATTED_NAME</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_FORMATTED_NAME		105

/**
 *  Field ID of <code>Contact</code>: NAME
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.NAME</code>.
 *  The data type for this field is #JK_PIM_STRING_ARRAY.
 */
#define JK_PIM_CONTACT_NAME					106

/**
 *  Field ID of <code>Contact</code>: NICKNAME
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.NICKNAME</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_NICKNAME				107

/**
 *  Field ID of <code>Contact</code>: NOTE
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.NOTE</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_NOTE					108

/**
 *  Field ID of <code>Contact</code>: ORG
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ORG</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_ORG					109

/**
 *  Field ID of <code>Contact</code>: PHOTO
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.PHOTO</code>.
 *  The data type for this field is #JK_PIM_BINARY.
 */
#define JK_PIM_CONTACT_PHOTO				110

/**
 *  Field ID of <code>Contact</code>: PHOTO_URL
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.PHOTO_URL</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_PHOTO_URL			111

/**
 *  Field ID of <code>Contact</code>: PUBLIC_KEY
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.PUBLIC_KEY</code>.
 *  The data type for this field is #JK_PIM_BINARY.
 */
#define JK_PIM_CONTACT_PUBLIC_KEY			112

/**
 *  Field ID of <code>Contact</code>: PUBLIC_KEY_STRING
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.PUBLIC_KEY_STRING</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_PUBLIC_KEY_STRING	113

/**
 *  Field ID of <code>Contact</code>: REVISION
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.REVISION</code>.
 *  The data type for this field is #JK_PIM_DATE.
 */
#define JK_PIM_CONTACT_REVISION				114

/**
 *  Field ID of <code>Contact</code>: TEL
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.TEL</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_TEL					115

/**
 *  Field ID of <code>Contact</code>: TITLE
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.TITLE</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_TITLE				116

/**
 *  Field ID of <code>Contact</code>: UID
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.UID</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_UID					117

/**
 *  Field ID of <code>Contact</code>: URL
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.URL</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_CONTACT_URL					118

/*@}*/ 


/** 
 *  @name Element ID of JK_PIM_CONTACT_ADDR field.
 *  This is an identifier defined in the PIM optional package specification, for 
 *  identifying elements in the fields whose field ID is #JK_PIM_CONTACT_ADDR.
 *  See <code>javax.microedition.pim.Contact</code> specification.
 *  
 *  This is used as a value for the <i>elementIds</i> member of JKPIMExFieldDef structure.
 */
/*@{*/ 

/**
 *  Element ID of JK_PIM_CONTACT_ADDR field: POBOX
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ADDR_POBOX</code>.
 */
#define JK_PIM_CONTACT_ADDR_POBOX		0

/**
 *  Element ID of JK_PIM_CONTACT_ADDR field: EXTRA
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ADDR_EXTRA</code>.
 */
#define JK_PIM_CONTACT_ADDR_EXTRA		1

/**
 *  Element ID of JK_PIM_CONTACT_ADDR field: STREET
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ADDR_STREET</code>.
 */
#define JK_PIM_CONTACT_ADDR_STREET		2

/**
 *  Element ID of JK_PIM_CONTACT_ADDR field: LOCALITY
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ADDR_LOCALITY</code>.
 */
#define JK_PIM_CONTACT_ADDR_LOCALITY	3

/**
 *  Element ID of JK_PIM_CONTACT_ADDR field: REGION
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ADDR_REGION</code>.
 */
#define JK_PIM_CONTACT_ADDR_REGION		4

/**
 *  Element ID of JK_PIM_CONTACT_ADDR field: POSTALCODE
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ADDR_POSTALCODE</code>.
 */
#define JK_PIM_CONTACT_ADDR_POSTALCODE	5

/**
 *  Element ID of JK_PIM_CONTACT_ADDR field: COUNTRY
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ADDR_COUNTRY</code>.
 */
#define JK_PIM_CONTACT_ADDR_COUNTRY		6

/**
 *  Element ID of JK_PIM_CONTACT_ADDR field: ADDRSIZE
 *  
 *  The number of the elements of the <code>javax.microedition.pim.Contact.ADDR</code> field
 *  specified by the PIM optional package.
 */
#define JK_PIM_CONTACT_ADDR_ADDRSIZE	7

/*@}*/ 


/** 
 *  @name Element ID of JK_PIM_CONTACT_NAME field.
 *  This is an identifier defined in the PIM optional package specification, for 
 *  identifying elements in the fields whose field ID is #JK_PIM_CONTACT_NAME.
 *  See <code>javax.microedition.pim.Contact</code> specification.
 *  
 *  This is used as a value for the <i>elementIds</i> member of JKPIMExFieldDef structure.
 */
/*@{*/ 

/**
 *  Element ID of JK_PIM_CONTACT_NAME field: FAMILY
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.NAME_FAMILY</code>.
 */
#define JK_PIM_CONTACT_NAME_FAMILY		0

/**
 *  Element ID of JK_PIM_CONTACT_NAME field: GIVEN
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.NAME_GIVEN</code>.
 */
#define JK_PIM_CONTACT_NAME_GIVEN		1

/**
 *  Element ID of JK_PIM_CONTACT_NAME field: OTHER
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.NAME_OTHER</code>.
 */
#define JK_PIM_CONTACT_NAME_OTHER		2

/**
 *  Element ID of JK_PIM_CONTACT_NAME field: PREFIX
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.NAME_PREFIX</code>.
 */
#define JK_PIM_CONTACT_NAME_PREFIX		3

/**
 *  Element ID of JK_PIM_CONTACT_NAME field: SUFFIX
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.NAME_SUFFIX</code>.
 */
#define JK_PIM_CONTACT_NAME_SUFFIX		4

/**
 *  Element ID of JK_PIM_CONTACT_NAME field: NAMESIZE
 *  
 *  The number of the elements of the <code>javax.microedition.pim.Contact.NAME</code> field
 *  specified by the PIM optional package.
 */
#define JK_PIM_CONTACT_NAME_NAMESIZE	5

/*@}*/ 

 
/** 
 *  @name Attribute ID.
 *  Identifiers defined in the PIM optional package specification.
 *  These are used in bit-wise OR operator combinations. 
 *  See <code>javax.microedition.pim.Contact</code> specification.
 */
/*@{*/ 
 
/**
 *  Attribute ID: ASST
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_ASST</code>.
 */
#define JK_PIM_CONTACT_ATTR_ASST		0x01

/**
 *  Attribute ID: AUTO
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_AUTO</code>.
 */
#define JK_PIM_CONTACT_ATTR_AUTO		0x02

/**
 *  Attribute ID: FAX
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_FAX</code>.
 */
#define JK_PIM_CONTACT_ATTR_FAX			0x04

/**
 *  Attribute ID: HOME
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_HOME</code>.
 */
#define JK_PIM_CONTACT_ATTR_HOME		0x08

/**
 *  Attribute ID: MOBILE
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_MOBILE</code>.
 */
#define JK_PIM_CONTACT_ATTR_MOBILE		0x10

/**
 *  Attribute ID: OTHER
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_OTHER</code>.
 */
#define JK_PIM_CONTACT_ATTR_OTHER		0x20

/**
 *  Attribute ID: PAGER
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_PAGER</code>.
 */
#define JK_PIM_CONTACT_ATTR_PAGER		0x40

/**
 *  Attribute ID: PREFERRED
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_PREFERRED</code>.
 */
#define JK_PIM_CONTACT_ATTR_PREFERRED	0x80

/**
 *  Attribute ID: SMS
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_SMS</code>.
 */
#define JK_PIM_CONTACT_ATTR_SMS			0x0100

/**
 *  Attribute ID: WORK
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.ATTR_WORK</code>.
 */
#define JK_PIM_CONTACT_ATTR_WORK		0x0200

/*@}*/ 


/** 
 *  @name Values for the JK_PIM_CONTACT_CLASS field.
 *  Values that can be set in a field whose field ID is JK_PIM_CONTACT_CLASS.
 *  See <code>javax.microedition.pim.Contact</code> specification.
 */
/*@{*/ 

/**
 *  A value for the JK_PIM_CONTACT_CLASS field: CONFIDENTIAL
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.CLASS_CONFIDENTIAL</code>.
 */
#define JK_PIM_CONTACT_CLASS_CONFIDENTIAL	200

/**
 *  A value for the JK_PIM_CONTACT_CLASS field: PRIVATE
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.CLASS_PRIVATE</code>.
 */
#define JK_PIM_CONTACT_CLASS_PRIVATE		201

/**
 *  A value for the JK_PIM_CONTACT_CLASS field: PUBLIC
 *  
 *  Corresponds to <code>javax.microedition.pim.Contact.CLASS_PUBLIC</code>.
 */
#define JK_PIM_CONTACT_CLASS_PUBLIC			202

/*@}*/ 



#ifdef __cplusplus
}
#endif

#endif /* ___JK_PIM_CONTACT_H */

/** @} end of group */
