/**
 * @file 
 */

/**
 * @addtogroup Module_PIM_Data_Types
 *
 * @{
 */

#ifndef ___JK_PIM_TODO_H
#define ___JK_PIM_TODO_H

#ifdef __cplusplus
extern "C" {
#endif



/** 
 *  @name Field ID of a ToDo List.
 *  Field identifiers defined in the PIM optional package specification for fields
 *  in lists of type #JK_PIM_TODO.
 *  See <code>javax.microedition.pim.ToDo</code> specification.
 *  
 *  This is used as a value for the <i>fieldId</i> member of JKPIMFieldDef structure. 
 */
/*@{*/ 
 
/**
 *  Field ID of a ToDo List: CLASS
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.CLASS</code>.
 *  The data type for this field is #JK_PIM_INT.
 */
#define JK_PIM_TODO_CLASS				100

/**
 *  Field ID of a ToDo List: COMPLETED
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.COMPLETED</code>.
 *  The data type for this field is #JK_PIM_BOOLEAN.
 */
#define JK_PIM_TODO_COMPLETED			101

/**
 *  Field ID of a ToDo List: COMPLETION_DATE
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.COMPLETION_DATE</code>.
 *  The data type for this field is #JK_PIM_CALENDAR.
 */
#define JK_PIM_TODO_COMPLETION_DATE		102

/**
 *  Field ID of a ToDo List: DUE
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.DUE</code>.
 *  The data type for this field is #JK_PIM_CALENDAR.
 */
#define JK_PIM_TODO_DUE					103

/**
 *  Field ID of a ToDo List: NOTE
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.NOTE</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_TODO_NOTE				104

/**
 *  Field ID of a ToDo List: PRIORITY
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.PRIORITY</code>.
 *  The data type for this field is #JK_PIM_INT.
 */
#define JK_PIM_TODO_PRIORITY			105

/**
 *  Field ID of a ToDo List: REVISION
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.PRIORITY</code>.
 *  The data type for this field is #JK_PIM_DATE.
 */
#define JK_PIM_TODO_REVISION			106

/**
 *  Field ID of a ToDo List: SUMMARY
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.SUMMARY</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_TODO_SUMMARY				107

/**
 *  Field ID of a ToDo List: UID
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.UID</code>.
 *  The data type for this field is #JK_PIM_STRING.
 */
#define JK_PIM_TODO_UID					108

/*@}*/ 


/**
 *  @name Values for the JK_PIM_TODO_CLASS field
 *  Values that can be set in a field whose field ID is JK_PIM_TODO_CLASS.
 *  See <code>javax.microedition.pim.ToDo</code> specification.
 */
/*@{*/ 

/**
 *  A value for the JK_PIM_TODO_CLASS field: CONFIDENTIAL
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.CLASS_CONFIDENTIAL</code>.
 */
#define JK_PIM_TODO_CLASS_CONFIDENTIAL	200

/**
 *  A value for the JK_PIM_TODO_CLASS field: PRIVATE
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.CLASS_PRIVATE</code>.
 */
#define JK_PIM_TODO_CLASS_PRIVATE		201

/**
 *  A value for the JK_PIM_TODO_CLASS field: PUBLIC
 *  
 *  Corresponds to <code>javax.microedition.pim.ToDo.CLASS_PUBLIC</code>.
 */
#define JK_PIM_TODO_CLASS_PUBLIC		202
/*@}*/ 



#ifdef __cplusplus
}
#endif

#endif /* ___JK_PIM_TODO_H */

/** @} end of group */
