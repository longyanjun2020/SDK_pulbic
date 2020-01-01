/**
 * @file 
 */

/**
 * @addtogroup Module_PIM_Data_Types
 *
 * @{
 */

#ifndef ___JK_PIM_COMMON_H
#define ___JK_PIM_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif


#include "JkTypes.h"



/** 
 *  @name Minimum Identifier Value
 *  The smallest number for an identifier defined in the PIM optional package specification.
 */
/*@{*/ 

/**
 *  Minimum extended field identifier value
 * 
 *  The smallest number for an extended field identifier.
 *  The native system can use a value of this or larger for the custom identifiers of extended fields.
 * 
 */
#define JK_PIM_EXTENDED_FIELD_MIN_VALUE		0x01000000

/**
 *  Minimum extended attribute identifier value
 * 
 *  The smallest number for an extended attribute identifier.
 *  The native system can use a value of this or larger for the custom identifiers of extended attributes.
 *  Note that an attribute identifier must be defined by a bit value.
 */
#define JK_PIM_EXTENDED_ATTRIBUTE_MIN_VALUE	0x01000000

/*@}*/


/*	---------- ---------- ----------
	 @: List type
	---------- ---------- ---------- */
/**
 *  List type
 *  
 *  Holds information indicating the kind of list.
 *  A list is a set of data corresponding to a table in an ordinary database. 
 * 
 *  The following values can be set as the list type.
 *  <ul>
 *   <li> #JK_PIM_CONTACT
 *   <li> #JK_PIM_EVENT
 *   <li> #JK_PIM_TODO
 *  </ul>
 */
typedef JKSint32	JKPIMListType;

/** 
 *  @name List Type
 *  Constants representing kinds of lists.
 *  JBlend also uses this in a parameter passed to #JkPIMGetListNames(), #JkPIMOpenConnection().
 */
/*@{*/ 

/**
 *  List type: Contact list
 *  
 *  Corresponds to <code>javax.microedition.pim.CONTACT_LIST</code>.
 */
#define JK_PIM_CONTACT		1

/**
 *  List type: Event list
 *  
 *  Corresponds to <code>javax.microedition.pim.EVENT_LIST</code>.
 */
#define JK_PIM_EVENT		2

/**
 *  List type: ToDo list
 *  
 *  Corresponds to <code>javax.microedition.pim.TODO_LIST</code>.
 */
#define JK_PIM_TODO			3

/*@}*/ 


/*	---------- ---------- ----------
	 @: Access mode type
	---------- ---------- ---------- */
/**
 *  Access mode.
 *  
 *  Holds information indicating the access mode for the list.
 *  
 *  The following values can be set as the access mode.
 *  <ul>
 *   <li> #JK_PIM_READ_ONLY
 *   <li> #JK_PIM_WRITE_ONLY
 *   <li> #JK_PIM_READ_WRITE
 *  </ul>
 */
typedef JKSint32	JKPIMAccessMode;

/** 
 *  @name Access Mode
 *  Constants representing the access mode for the list.
 *  JBlend also uses this in a <i>mode</i> passed to #JkPIMOpenConnection().
 */
/*@{*/ 

/**
 *  Access mode: Read only
 *  
 *  Corresponds to <code>javax.microedition.pim.READ_ONLY</code>.
 */
#define JK_PIM_READ_ONLY	1

/**
 *  Access mode: Write only
 *  
 *  Corresponds to <code>javax.microedition.pim.WRITE_ONLY</code>.
 */
#define JK_PIM_WRITE_ONLY	2

/**
 *  Access mode: Read/write accessible
 *  
 *  Corresponds to <code>javax.microedition.pim.READ_WRITE</code>.
 */
#define JK_PIM_READ_WRITE	3

/*@}*/


/*	---------- ---------- ----------
	 @: Data type
	---------- ---------- ---------- */
/**
 *  Field data type
 *  
 *  Holds information indicating the kind of field data.
 *  
 *  The following values can be set as the field data type.
 *  <ul>
 *   <li> #JK_PIM_BINARY
 *   <li> #JK_PIM_BOOLEAN
 *   <li> #JK_PIM_DATE
 *   <li> #JK_PIM_CALENDAR
 *   <li> #JK_PIM_INT
 *   <li> #JK_PIM_STRING
 *   <li> #JK_PIM_STRING_ARRAY
 *  </ul>
 */
typedef JKSint32	JKPIMDataType;

/** 
 *  @name Field Data Type
 *  Constants representing kinds of field data types.
 *  This is used as a value for the <i>dataType</i> member of JKPIMField structure. 
 */
/*@{*/ 

/**
 *  Data type: Binary data
 */
#define JK_PIM_BINARY		0

/**
 *  Data type: Boolean data
 */
#define JK_PIM_BOOLEAN		1

/**
 *  Data type: Date/time
 *  
 *  The elapsed time from 00:00:00.000, January 1, 1970 of Greenwich mean time (GMT)) in millisecond as a numeric value. 
 * 
 */
#define JK_PIM_DATE			2

/**
 *  Data type: Integer
 */
#define JK_PIM_INT			3

/**
 *  Data type: String
 */
#define JK_PIM_STRING		4

/**
 *  Data type: String array
 */
#define JK_PIM_STRING_ARRAY	5

/**
 *	Data Type: Date/Time
 *	Date and time are time zone independent.
 *	For example, one's birthday and time are always the same anywhere in the world.
 *	An alarm clock set to ring at 7 am should ring at 7 am. 
 *	This data type has not beed defined in the JSR75 specification; however, it is considered necessary 
 *	according to examing the use case, especially, examing Palm's performance.
 *	Date data handled in JSR75 - PIM, except the updated date data(Contact.REVISION,Event.REVISION,ToDo.REVISION)
 *	is expressed as the data type described above.
 * 
 */
#define JK_PIM_CALENDAR		6

/*@}*/ 


/*	---------- ---------- ----------
	 @: Error code
	---------- ---------- ---------- */
/**
 *  Error code
 *  
 *  Holds information indicating the JSI functions and JBI functions results.
 *  The meanings of error codes returned by a function are defined separately for each function. 
 *  The following values can be set as the error code.
 *  <ul>
 *   <li> #JK_PIM_SUCCESS
 *   <li> #JK_PIM_ASYNC_FUNCTION
 *   <li> #JK_PIM_MEMORY_ERR
 *   <li> #JK_PIM_END_OF_RESULTSET_ERR
 *   <li> #JK_PIM_INVALID_PARAM_ERR
 *   <li> #JK_PIM_SECURITY_ERR
 *   <li> #JK_PIM_FEATURE_NOT_SUPPORTED
 *   <li> #JK_PIM_GENERAL_ERR
 *   <li> #JK_PIM_LIST_CLOSED
 *   <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *   <li> #JK_PIM_MAX_CATEGORIES_EXCEEDED
 *   <li> #JK_PIM_UNSUPPORTED_VERSION
 *   <li> #JK_PIM_UPDATE_ERR
 *   <li> #JK_PIM_INDEX_ERR
 *   <li> #JK_PIM_UNSUPPORTED_FIELD_ERR
 *   <li> #JK_PIM_EXISTING_CATEGORY_SPECIFIED
 *   <li> #JK_PIM_NOT_EXISTING_CATEGORY_SPECIFIED
 *   <li> #JK_PIM_DO_NOTHING
 *   <li> #JK_PIM_FIELD_EMPTY
 *  </ul>
 */
typedef JKSint32	JKPIMErrCode;

/** 
 *  @name Error Code
 *  Constants representing error codes.
 *  This is used as a return value for the PIM JSI or PIM JBI. 
 */
/*@{*/ 

/**
 *  Error code: The function succeeded.
 */
#define JK_PIM_SUCCESS							  0

/**
 *  Error code: The function performs its processing asynchronously.
 */
#define JK_PIM_ASYNC_FUNCTION					 -1

/**
 *  Error code: The function failed because insufficient memory error. 
 *  
 *  JBlend throws OutOfMemoryError in case a JSI function returns this error code.
 */
#define JK_PIM_MEMORY_ERR						 -2

/**
 *  Error code: The function failed because no more result sets are available.
 */
#define JK_PIM_END_OF_RESULTSET_ERR				 -3

/**
 *  Error code: The function failed because an invalid parameter was designated.
 */
#define JK_PIM_INVALID_PARAM_ERR				 -4

/**
 *  Error code: The function failed because of a security error.
 */
#define JK_PIM_SECURITY_ERR						 -5

/**
 *  Error code: The function failed because the platform does not support the requested functionality.
 */
#define JK_PIM_FEATURE_NOT_SUPPORTED			 -6

/**
 *  Error code: The function failed because of a general database processing error.
 */
#define JK_PIM_GENERAL_ERR						 -7

/**
 *  Error code: The function failed because the list is already closed.
 */
#define JK_PIM_LIST_CLOSED						 -8

/**
 *  Error code: The function failed because the list cannot be accessed.
 */
#define JK_PIM_LIST_NOT_ACCESSIBLE				 -9

/**
 *  Error code: The function failed because no more categories can be supported.
 */
#define JK_PIM_MAX_CATEGORIES_EXCEEDED			-10

/**
 * 
 */
#define JK_PIM_UNSUPPORTED_VERSION				-11

/**
 * 
 */
#define JK_PIM_UPDATE_ERR						-12

/**
 *  Error code: The function failed because of an invalid index for an array.
 */
#define JK_PIM_INDEX_ERR						-13

/**
 *  Error code: The function failed because the designated field is not supported.
 */
#define JK_PIM_UNSUPPORTED_FIELD_ERR			-14

/**
 *  Error code: The function failed because the designated category already exists.
 */
#define JK_PIM_EXISTING_CATEGORY_SPECIFIED		-15

/**
 *  Error code: The function failed because the designated category does not exist.
 */
#define JK_PIM_NOT_EXISTING_CATEGORY_SPECIFIED	-16

/**
 *  Error code: The function performed no operation.
 */
#define JK_PIM_DO_NOTHING						-17

/**
 *  Error code: The function failed because the field is empty.
 */
#define JK_PIM_FIELD_EMPTY						-18

/** 
 *  Error code: The function failed because of insufficient data.
 */
#define JK_PIM_NEED_MORE_DATA					-19

/** 
 *  Error code: The function reached end of the data.
 */
#define JK_PIM_DATA_FINISHED					-20

/** 
 *  Error code: The function failed because of incomplete data.
 */
#define JK_PIM_DATA_BROKEN						-21

/** 
 *  Error code: The function failed because the character encoding is not supported.
 */
#define JK_PIM_UNSUPPORTED_CHAR_ENCODING_ERR	-22

/** 
 *  Error code: The function failed because the data format is not supported.
 */
#define JK_PIM_UNSUPPORTED_DATA_FORMAT_ERR		-23

/*@}*/ 


/*	---------- ---------- ----------
	 @: Integer type
	---------- ---------- ---------- */

/**
 *  A structure consists of a signed 32-bit integer array.
 *  
 *  The data in this structure can be manipulated using @ref Module_PIM_ACCESS_JBI_variable_2.
 */
typedef struct {
    /**
     *   The element count of the array pointed to by <i>data</i>.
     */
	JKSint32	size;
	
    /**
     *   A pointer to an array of pointers to JKPIMLong structures containing long integers data.
     */
	JKSint32*	data;
} JKPIMIntArray;


/**
 *  The data structure type representing a long value.
 *  
 *  This structure contains 64-bit data corresponding to the Java <code>long</code> type.
 */
typedef struct {
    /**
     *   High-order 32 bits.
     */
	JKUint32	high;

    /**
     *   Low-order 32 bits.
     */
	JKUint32	low;
} JKPIMLong;


/**
 *  The data structure type representing a variable-length array of long integers.
 *  
 *  The data in this structure can be manipulated using @ref Module_PIM_ACCESS_JBI_variable_3.
 */
typedef struct {
    /**
     *   The element count of the pointer (JKPIMLong*) array pointed to by <i>data</i>.
     */
	JKSint32	size;
	
    /**
     *   A pointer to an array of pointers to JKPIMLong structures containing long integers data.
     */
	JKPIMLong**	data;
} JKPIMLongArray;


/*	---------- ---------- ----------
	 @: String type
	---------- ---------- ---------- */
/**
 *  The data structure type representing a Unicode string.
 *  
 *  It is encoded in UNICODE and not terminated by '\0'.
 *  Setting JK_NULL for <i>text</i> and 0 for <i>length</i> represents the string '\0'.
 *  Setting JK_NULL for <i>text</i> and a negative value for <i>length</i> represents a NULL string.
 */
typedef struct {
    /**
     *   A pointer to the Unicode string.
     */
	JKWChar*	text;
	
    /**
     *   The length (number of characters) of the Unicode string.
     */
	JKSint32	length;
} JKPIMString;


/**
 *  The data structure type representing a variable-length string array.
 *  
 *  The data in this structure can be manipulated using @ref Module_PIM_ACCESS_JBI_variable_1.
 */
typedef struct {
    /**
     *   The element count of the array pointed to by <i>data</i>.
     */
	JKSint32		size;
	
    /**
     *   A pointer to an array of pointers to JKPIMString structures containing Unicode string.
     */
	JKPIMString**	data;
} JKPIMStringArray;


/*	---------- ---------- ----------
	 @: Date type
	---------- ---------- ---------- */
/**
 *  The data structure type representing a calendar value.
 * 
 * This structure may be used to handle date/time data whose interpretation
 * does not differ on a time zone.
 * 
 * 
 */
typedef struct {
    /**
     *   year
     *   
     *   The valid range is between -2^31 and 2^31. 
     */
	JKSint32	year;

    /**
     *   month
     *   
     *   The valid range is between 0 and 11. 
     */
	JKUint8		month;

    /**
     *   day
     *   
     *   The valid range is between 1 and 31. 
     */
	JKUint8		day;

    /**
     *   hour
     *   
     *   The valid range is between 0 and 23. 
     */
	JKUint8		hour;

    /**
     *   minute
     *   
     *   The valid range is between 0 and 59. 
     */
	JKUint8		minute;
	
    /**
     *   second
     *   
     *   The valid range is between 0 and 59. 
     */
	JKUint8		second;

    /**
     *   millisecond
     *   
     *   The valid range is between 0 and 999. 
     */
	JKUint16	millis;
} JKPIMCalendar;


/**
 *  The data structure type representing a variable-length array of calendar data.
 *  
 *  The data in this structure can be manipulated using @ref Module_PIM_ACCESS_JBI_variable_4.
 */
typedef struct {
    /**
     *   The element count of the array pointed to by <i>data</i>.
     */
	JKSint32		size;

    /**
     *   A pointer to an array of pointers to JKPIMString structures containing Unicode string.
     */
	JKPIMCalendar**	data;
} JKPIMCalendarArray;


/**
 *  The data structure type representing a date value.
 * 
 * It can hold the elapsed time in milliseconds starting at 1970/1/1 00:00:00.
 * The data of this type is used with the timezone offset value set in the native system.
 *
 */
typedef JKPIMLong		JKPIMDate;


/**
 *  The data structure type representing a variable-length array of date data.
 * 
 */
typedef JKPIMLongArray	JKPIMDateArray;


/*	---------- ---------- ----------
	 @: Dield definition type
	---------- ---------- ---------- */
/**
 *  The data structure type representing a field definition.
 */
typedef struct {
    /**
     *   Field ID.
     *   
     *   This value can be one defined in the PIM optional package specification or 
     *   an extended value defined in the native system.
     */
	JKSint32		fieldId;
	
    /**
     *   The label of the field.
     */
	JKPIMString		label;
	
    /**
     *   The data type of the field.
     */
	JKPIMDataType	dataType;
	
    /**
     *   The maximum number of data items the field can hold.
     */
	JKSint32		maxSize;
	
    /**
     *   The bitwise OR of one or more of the constants defined as attribute identifiers.
     */
	JKSint32		attributes;
} JKPIMFieldDef;


/**
 *  The data structure type representing an extended field definition.
 * 
 * This is a type extending the JKPIMFieldDef structure, for holding an 
 * extended field attribute of data type #JK_PIM_STRING_ARRAY.
 */
typedef struct {
    /**
     *   A JKPIMFieldDef structure holding field definition.
     */
	JKPIMFieldDef		def;
	
    /**
     *   The count of the field elements.
     *
     *  This is the sum of the number of the elements defined by the
     *  PIM optional package and the number of the elements defined originally in 
     *  the native system.
     *  This is identical with the value returned by the 
     *  <code>javax.microedition.pim.PIMList</code> class 
     *  <code>stringArraySize</code> method.
     *  
     *  If, for example, the field ID is #JK_PIM_CONTACT_ADDR, the element count should be 
     *  as follows.
     *  
     *  #JK_PIM_CONTACT_ADDR_ADDRSIZE + [The count of the element defined in the native system]
     */
	JKSint32			size;
	
    /**
     *   A pointer to an array of element IDs.
     *   
     *  The value to be set to an element is a constant defined in the PIM optional package 
     *  specification.
     */
	JKSint32*			elementIds;
	
    /**
     *   A JKPIMStringArray structure holding label of the elements.
     */
	JKPIMStringArray	labels;
} JKPIMExFieldDef;


/**
 *  A data structure representing a variable-length array of field definitions.
 *  
 *  The data in this structure can be manipulated using @ref Module_PIM_ACCESS_JBI_variable_5.
 */
typedef struct {
    /**
     *   The element count of the array pointed to by <i>data</i>.
     */
	JKSint32		size;
	
    /**
     *   A pointer to an array of pointers to JKPIMFieldDef structures holding field definitions.
     */
	JKPIMFieldDef**	data;
} JKPIMFieldDefArray;


/*	---------- ---------- ----------
	 @: Attribute definition type
	---------- ---------- ---------- */
/**
 *  The data structure type representing an attribute definition.
 */
typedef struct {
    /**
     *   Attribute ID.
     *
     *   This value can be one defined in the PIM optional package specification or 
     *   an extended value defined in the native system.
     */
	JKSint32		attributeId;
	
    /**
     *   The label of the attribute.
     */
	JKPIMString		label;
} JKPIMAttributeDef;


/**
 *  A data structure representing a variable-length array of attribute definitions.
 *  
 *  The data in this structure can be manipulated using @ref Module_PIM_ACCESS_JBI_variable_7.
 */
typedef struct {
    /**
     *   The element count of the array pointed to by <i>data</i>.
     */
	JKSint32			size;
	
    /**
     *   A pointer to an array of pointers to a JKPIMAttributeDef structure holding attribute definitions.
     */
	JKPIMAttributeDef**	data;
} JKPIMAttributeDefArray;


/*	---------- ---------- ----------
	 @: Data type
	---------- ---------- ---------- */
/**
 *  The data structure type representing a field data of binary data type.
 *  
 *  This structure contains data for a field of the data type #JK_PIM_BINARY.
 */
typedef struct {
    /**
     *   The bitwise OR of one or more of the constants defined as attribute identifiers.
     */
	JKSint32	attributes;
	
    /**
     *   The binary data size in bytes. 
     */
	JKSint32	size;
	
    /**
     *   A pointer to the memory area holding the binary data. 
     */
	JKSint8*	data;
} JKPIMBinaryValue;


/**
 *  The data structure type representing a field data of boolean type.
 *  
 *  This structure contains data for a field of the data type #JK_PIM_BOOLEAN.
 */
typedef struct {
    /**
     *   The bitwise OR of one or more of the constants defined as attribute identifiers.
     */
	JKSint32	attributes;
	
    /**
     *   Boolean data.
     */
	JKBool		data;
} JKPIMBooleanValue;


/**
 *  The data structure type representing a field data of date type.
 *  
 *  This structure contains data for a field of the data type #JK_PIM_DATE.
 */
typedef struct {
    /**
     *   The bitwise OR of one or more of the constants defined as attribute identifiers.
     */
	JKSint32	attributes;
	
    /**
     *   Date/time data.
     *   
     *   The elapsed time from 00:00:00.000, January 1, 1970 of Greenwich mean time (GMT)) 
     *   in millisecond as a numeric value. 
	 * 	
     */
	JKPIMDate	data;
} JKPIMDateValue;


/**
 *  The data structure type representing a field data of date type.
 *  
 *  This structure contains data for a field of the data type #JK_PIM_DATE.
 */
typedef struct {
    /**
     *   The bitwise OR of one or more of the constants defined as attribute identifiers.
     */
	JKSint32		attributes;

    /**
     *   Calendar data.
     */
	JKPIMCalendar	data;
} JKPIMCalendarValue;


/**
 *  The data structure type representing a field data of integer type.
 *  
 *  This structure contains data for a field of the data type #JK_PIM_INT.
 */
typedef struct {
    /**
     *   The bitwise OR of one or more of the constants defined as attribute identifiers.
     */
	JKSint32	attributes;
	
    /**
     *   Integer data.
     */
	JKSint32	data;
} JKPIMIntValue;


/**
 *  The data structure type representing a field data of string type.
 *  
 *  This structure contains data for a field of the data type #JK_PIM_STRING.
 */
typedef struct {
    /**
     *   The bitwise OR of one or more of the constants defined as attribute identifiers.
     */
	JKSint32	attributes;
	
    /**
     *   JKPIMString data.
     */
	JKPIMString	data;
} JKPIMStringValue;


/**
 *  The data structure type representing a field data of string array type.
 *  
 *  This structure contains data for a field of the data type #JK_PIM_STRING_ARRAY.
 */
typedef struct {
    /**
     *   The bitwise OR of one or more of the constants defined as attribute identifiers.
     */
	JKSint32			attributes;
	
    /**
     *   JKPIMStringArray data.
     */
	JKPIMStringArray	data;
} JKPIMStringArrayValue;


/*	---------- ---------- ----------
	 @: Field data type
	---------- ---------- ---------- */
/**
 *  The data structure type representing a field data.
 *  
 *  This structure holds data of fields making up an item.
 *  Each field is represented as a variable-length array holding an indefinite amount of data. 
 *  
 *  A field corresponds to a "column" in an ordinary database.
 */
typedef struct {
    /**
     *   Field ID.
     */
	JKSint32		fieldId;
	
    /**
     *   The data type of the field.
     */
	JKPIMDataType	dataType;
	
    /**
     *   A pointer to the JKPIMFieldDef structure holding field definitions. 
     */
	JKPIMFieldDef*	def;
	
    /**
     *   The number of data units the field holds.
     */
	JKSint32		size;
	
    /**
     *   A pointer to an array of pointers to a data which the field holds.
     */
	union {
        /**
         *   A pointer to an array of pointers to JKPIMBinaryValue structures holding binary data.
         *   
         *   This member is used when the <i>dataType</i> member is #JK_PIM_BINARY.
         */
		JKPIMBinaryValue**		binaries;
        /**
         *   A pointer to an array of pointers to JKPIMBooleanValue structures holding boolean data.
         *   
         *   This member is used when the <i>dataType</i> member is #JK_PIM_BOOLEAN.
         */
		JKPIMBooleanValue**		booleans;
        /**
         *   A pointer to an array of pointers to JKPIMDateValue structures holding date data.
         *   
         *   This member is used when the <i>dataType</i> member is #JK_PIM_DATE.
         */
		JKPIMDateValue**		dates;
		/**
		 *	An array of pointers to JKPIMCalendar structures holding date/time data. 
		 *	Date/time data handled here would be interpreted independently regardless of a time zone.
		 *	This is only in case that a member dataType is #JK_PIM_CALENDAR.
		 * 
		 */
		JKPIMCalendarValue**	calendars;
        /**
         *   A pointer to an array of pointers to JKPIMIntValue structures holding integer data.
         *   
         *   This member is used when the <i>dataType</i> member is #JK_PIM_INT.
         */
		JKPIMIntValue**			ints;
        /**
         *   A pointer to an array of pointers to JKPIMStringValue structures holding string data.
         *   
         *   This member is used when the <i>dataType</i> member is #JK_PIM_STRING.
         */
		JKPIMStringValue**		strings;
        /**
         *   A pointer to an array of pointers to JKPIMStringArrayValue structures holding string array data.
         *   
         *   This member is used when the <i>dataType</i> member is #JK_PIM_STRING_ARRAY.
         */
		JKPIMStringArrayValue**	stringArrays;
	}				data;
} JKPIMField;


/*	---------- ---------- ----------
	 @: Item data type
	---------- ---------- ---------- */
/**
 *  The data structure type representing an item data.
 *  
 *  An item consists of one or more fields.
 *  
 *  An item corresponds to a "record" in an ordinary database.
 */
typedef struct {
    /**
     *   The list type.
     */
	JKPIMListType		listType;
	
    /**
     *   The number of fields making up an item.
     */
	JKSint32			size;
	
    /**
     *   A pointer to an array of pointers to a JKPIMField structure containing fields making 
     *   up an item.
     */
	JKPIMField**		fields;
	
    /**
     *   The string array containing the names of categories that are assigned to an item.
     */
	JKPIMStringArray	categories;
} JKPIMItem;


/**
 * Item array type
 *
 * A variable-length array type for containing an indefinite 
 * amount of pointers to JKPIMItem structure.
 *  
 *  The data in this structure can be manipulated using @ref Module_PIM_ACCESS_JBI_variable_8.
 */
typedef struct {
    /**
     *  The element count of the array pointed to by the <i>item</i> member.
     */
	JKSint32	size;
	
    /**
     *  A pointer to the array of pointers to JKPIMItem.
     */
	JKPIMItem**	items;
} JKPIMItemArray;



#ifdef __cplusplus
}
#endif

#endif /* ___JK_PIM_COMMON_H */

/** @} end of group */




