/*
 * Copyright 2006-2007 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMFiberSyncedObjectPool.h
 * Fiber Synced Object Pool JBI
 */

#ifndef __AM_FIBERSYNCEDOBJECTPOOL_H
#define __AM_FIBERSYNCEDOBJECTPOOL_H

#include "JkTypesFiber.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup Fiber_Synced_Object_Pool_JBI Fiber Synced Object Pool JBI
 *
 * @{
 *  An interface for operating a Synchronized Object Pool.
 *
 *  The functions in this interface can be used to create and destroy a 
 *  Synchronized Object Pool. A Synchronized Object Pool is used to 
 *  create, release and manage a collection of Synchronized Objects.
 *
 *  A Synchronized Object can be thought of as a base class from which 
 *  useful synchronization objects may be derived. These derived objects 
 *  can be help manage Fiber synchronization through Event signaling and 
 *  Synchronized Section access.
 * 
 *  The memory used in the Synchronized Object Pool is provided through 
 *  the #AmFiberSyncedObjectPoolCreate() function. It is used to manage 
 *  all objects within the Synchronized Object Pool. 
 * 
 *  It is important to remember that the objects managed by the 
 *  Synchronized Object Pool must all be released <i>before</i> the pool 
 *  is destroyed. This means that all @ref Fiber_JBI "Fibers" using 
 *  Synchronized Objects must have released their locks on them.
 * 
 *  @par Warning: 
 *  The Fiber Synced Object Pool JBI is <b>not</b> thread-safe.
 *
 */

/**
 * @name Fiber Synchronization Object Capacity
 * @{
 */

/**
 *  The minimum number of Synchronized Objects hosted by a Synchronized Object Pool.
 */
#define JK_FIBER_SOP_OBJECTS_MIN        (1)     /*    1 object  */

/**
 *  The maximum number of Synchronized Objects hosted by a Synchronized 
 *  Object Pool.
 */
#define JK_FIBER_SOP_OBJECTS_MAX        (65535) /* 65535 objects */

/**
 * @}
 */

/**
 * @name Fiber Synchronization Object Specifications
 * @{
 */

/**
 *  A flag used to indicate that support for Synchronized Event objects is
 *  required in a Synchronized Object Pool.
 */
#define JK_FIBER_SO_SPECIFICATION_EVENT     (0x00000001)

/**
 *  A flag used to indicate that support for Synchronized Section objects 
 *  is required in a Synchronized Object Pool.
 */
#define JK_FIBER_SO_SPECIFICATION_SECTION   (0x00000002)

/**
 *  A flag used to indicate that support for Synchronized Semaphore objects 
 *  is required in a Synchronized Object Pool.
 */
#define JK_FIBER_SO_SPECIFICATION_SEMAPHORE (0x00000003)

/**
 * @}
 */

/**
 *  Creates a Synchronized Object Pool necessary to host and manage 
 *  Synchronized Objects.
 *
 *  @param ulSpecifications
 *   A bit-field listing indicating the types of Synchronized Objects 
 *   supported by the pool being created.
 *  @param uiObjectLimit
 *   The maximum number of Synchronized Objects supported by the pool. 
 *  @param pvObjectHeap
 *   A void pointer to the heap used for all Synchronized Object Pool 
 *   related activities. If JK_NULL is set, the recommended heap size 
 *   is returned in <i>pulObjectHeapSize</i>.
 *  @param pulObjectHeapSize
 *   An pointer to the size of the data pointed to by <i>pvObjectHeap</i>. If 
 *   <i>pvObjectHeap</i> is JK_NULL, then the memory referenced by this pointer 
 *   will receive the recommended heap size. If set to JK_NULL, the function 
 *   will return #JK_RESULT_FIBER_BAD_PARAM.
 *  @param phFiberSyncedObjectPool
 *   Upon function success, a valid #JKFiberSyncedObjectPoolHandle is 
 *   returned.<br>
 *   Upon function failure, the contents of this parameter remain unchanged.<br>
 *   This parameter must not be JK_NULL if <i>pvFiberHeap</i> points to a 
 *   valid heap segment (is not JK_NULL).
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  This function creates a @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Object Pool" object based 
 *  on the parameters and amount of contiguous heap memory provided. If 
 *  the <i>pvObjectHeap</i> parameter is set to JK_NULL, the function 
 *  will return a recommended heap size in the memory referenced by 
 *  <i>pulObjectHeapSize</i>. The heap size calculation uses the 
 *  <i>ulSpecifications</i> and <i>cshObjectCapacity</i> parameters to 
 *  determine the maximum @ref 
 *  Fiber_Synced_Object_JBI "Synchronized Object" capacity of the 
 *  Synchronized Object Pool.
 * 
 *  The <i>ulSpecifications</i> parameter is a bit-wise OR'ing of the 
 *  #JK_FIBER_SO_SPECIFICATION_EVENT and #JK_FIBER_SO_SPECIFICATION_SECTION 
 *  flags.
 * 
 *  Valid values for the <i>fibers</i> component of the 
 *  <i>cshObjectCapacity</i> parameter are between 
 *  #JK_FIBERPOOL_FIBERS_MIN and #JK_FIBERPOOL_FIBERS_MAX inclusive.

 *  Valid values for the <i>objects</i> component of the 
 *  <i>cshObjectCapacity</i> parameter are between 
 *  #JK_FIBER_SOP_OBJECTS_MIN and #JK_FIBER_SOP_OBJECTS_MAX inclusive.
 * 
 *  If the <i>pvObjectHeap</i> parameter points to a segment of memory, the 
 *  function will validate that the requested memory size (as specified by 
 *  the value referenced in <i>pulObjectHeapSize</i>) does indeed 
 *  support the memory requirements of the Synchronized Object Pool being 
 *  created.
 * 
 *  The value returned in <i>phFiberSyncedObjectPool</i> may be used with 
 *  the other Synchronized Object Pool class APIs listed below.
 * 
 *  Synchronized Object Pool contents can be shared across more than one 
 *  @ref Fiber_Pool_JBI "Fiber Pool".
 *
 *  @par Optimization:
 *  Heap memory requirements are related directly to the value of 
 *  <i>ulSpecifications</i>. Memory usage can be optimized slightly be 
 *  hosting each Synchronized Object type its own separate Synchronized 
 *  Object Pool.
 *  @par
 *  The total number of Synchronized Objects in the Synchronized Object 
 *  Pool greatly affects memory requirements. Only slightly less 
 *  important, when considering memory usage, is the number of Fibers
 *  using the Synchronized Objects in the Synchronized Object Pool. Review 
 *  the planned usage of these objects to verify if there are 1:1 (Fiber 
 *  to Object) relationships. If not, perhaps memory can be saved by using 
 *  a different allocation ratio like 2:5 or 3:12.
 * 
 *  @par Note:
 *  The memory provided via <i>pvObjectHeap</i> must remain valid until the 
 *  Synchronized Object Pool object is destroyed via the 
 *  #AmFiberSyncedObjectPoolDestroy() function.
 *  @par
 *  This function is thread-safe.
 *
 *  @par Invocation:
 *  This function may be called from a @ref Fiber_JBI "Fiber", thread or 
 *  process context. See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 * 
 *  @see
 *  AmFiberSyncedObjectPoolDestroy
 * 
 */

long AmFiberSyncedObjectPoolCreate( unsigned long ulSpecifications, unsigned int uiObjectLimit, void *pvObjectHeap, unsigned long *pulObjectHeapSize, JKFiberSyncedObjectPoolHandle *phFiberSyncedObjectPool );

/**
 *  Destroys a Synchronized Object Pool object.
 * 
 *  @param hFiberSyncedObjectPool
 *   A valid Synchronized Object Pool object handle.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BUSY<br>
 *     when the Synchronized Object Pool contains Synchronized Objects 
 *     which are still in use.
 *
 *  <p>
 *  This function will verify that the @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Object Pool"
 *  specified by the <i>hFiberSyncedObjectPool</i> parameter is no 
 *  longer in use. After a successful return, the memory associated with 
 *  the Synchronized Object Pool may be released.
 * 
 *  All associated @ref 
 *  JKFiberSyncedObjectHandle "JKFiberSyncedObjectHandles" obtained from 
 *  the Synchronized Object Pool should be considered invalid at the 
 *  moment the function begins processing and should no longer be used 
 *  upon successful return.
 *
 *  @par Important
 *  The objects managed by the Synchronized Object Pool must all be 
 *  released before the pool is destroyed. This means that all @ref 
 *  Fiber_JBI "Fibers" using Synchronized Objects must have released their 
 *  locks on them. 
 *
 *  @par Invocation:
 *  This function may be called from a @ref Fiber_JBI "Fiber", thread or 
 *  process context. See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberSyncedObjectPoolDestroy( JKFiberSyncedObjectPoolHandle hFiberSyncedObjectPool );

/**
 *  Retrieves the number of Synchronized Objects in the Synchronized Object Pool.
 * 
 *  @param hFiberSyncedObjectPool
 *   A valid Fiber Pool object handle.
 *  @param puiSyncedObjectCount
 *   Upon function success, the number of allocated Synchronized Objects is
 *   returned in the memory referenced by this pointer.<br>
 *   Upon function failure, the contents of the memory referenced by this 
 *   pointer remain unchanged.<br>
 *   If set to JK_NULL, the function will return 
 *   #JK_RESULT_FIBER_BAD_PARAM.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  This function will return, in memory referenced by 
 *  <i>puiSyncedObjectCount</i>, the number of @ref 
 *  Fiber_Synced_Object_JBI "Synchronized Objects" that the @ref
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Object Pool" has allocated. 
 *  
 *  This value is <b>not</b> the same as <i>object</i> from the 
 *  <i>cshObjectCapacity</i> which was passed into the 
 *  #AmFiberSyncedObjectPoolCreate() function during the creation of the 
 *  Synchronized Object Pool. Instead, it represents the number of 
 *  Synchronized Objects that have been successfully allocated via the 
 *  #AmFiberSyncedObjectCreate() function.
 *
 *  @par Invocation:
 *  This function may be called from a @ref Fiber_JBI "Fiber", thread or 
 *  process context. See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberSyncedObjectPoolCreate
 * 
 */

long AmFiberSyncedObjectPoolGetCount( JKFiberSyncedObjectPoolHandle hFiberSyncedObjectPool, unsigned int *puiSyncedObjectCount );

/**
 * @name Fiber Synchronization Event Signal Types
 * @{
 */

/**
 *  Defines a Synchronized Event object which can maintain a signaled 
 *  state for an indefinite period of time after the initial signalling 
 *  process occurs.
 */
#define JK_FIBER_SE_TYPE_TOGGLE             (0x00000000)

/**
 *  Defines a Synchronized Event object which can not maintain a signaled 
 *  state after the initial signalling process occurs.
 */
#define JK_FIBER_SE_TYPE_PULSE              (0x00000001)

/**
 *  The bit-field mask used to access the Synchronized Event's 
 *  signal state behaviour configuration flags.
 */
#define JK_FIBER_SE_TYPE_MASK               (JK_FIBER_SE_TYPE_TOGGLE | JK_FIBER_SE_TYPE_PULSE)

/**
 *  The bit-field position (zero-based offset) of the Synchronized Event's 
 *  signal state configuration flags.
 */
#define JK_FIBER_SE_TYPE_POS                (0x00)

/**
 * @}
 */

/**
 * @name Fiber Synchronization Event Signal State Control
 * @{
 */

/**
 *  This flag may be used with @ref 
 *  JK_FIBER_SE_TYPE_TOGGLE "toggle type" Synchronized Event 
 *  objects to initialize them as non-signaled upon creation.
 */
#define JK_FIBER_SE_STATE_RESET             (0x00000000)

/**
 *  This flag may be used with @ref 
 *  JK_FIBER_SE_TYPE_TOGGLE "toggle type" Synchronized Event 
 *  objects to initialize them as signaled upon creation.
 */
#define JK_FIBER_SE_STATE_SIGNALED          (0x00000002)

/**
 *  The bit-field mask used to access the Synchronized Event's 
 *  initial state configuration flags.
 */
#define JK_FIBER_SE_STATE_MASK              (JK_FIBER_SE_STATE_RESET | JK_FIBER_SE_STATE_SIGNALED)

/**
 *  The bit-field position (zero-based offset) of the Synchronized Event's 
 *  initial state configuration flags.
 */
#define JK_FIBER_SE_STATE_POS               (0x01)

/**
 * @}
 */

/**
 * @name Fiber Synchronization Event Signal Reset Control
 * @{
 */

/**
 *  This flag may be used with a @ref 
 *  JK_FIBER_SE_TYPE_TOGGLE "toggle type" Synchronized Event 
 *  object to require @ref AmFiberEventReset "manual reset" after it is 
 *  signaled.
 */
#define JK_FIBER_SE_RESET_MANUAL            (0x00000000)

/**
 *  This flag may be used with a @ref 
 *  JK_FIBER_SE_TYPE_TOGGLE "toggle type" Synchronized Event 
 *  object to force an automatic reset after signalling with at least 
 *  one Fiber @ref AmFiberEventWait "blocking" on the object.
 */
#define JK_FIBER_SE_RESET_AUTO              (0x00000004)

/**
 *  The bit-field mask used to access the Synchronized Event's
 *  reset behaviour configuration flags.
 */
#define JK_FIBER_SE_RESET_MASK              (JK_FIBER_SE_RESET_MANUAL | JK_FIBER_SE_RESET_AUTO)

/**
 *  The bit-field position (zero-based offset) of the Synchronized Event's
 *  reset behaviour configuration flags.
 */
#define JK_FIBER_SE_RESET_POS               (0x02)

/**
 * @}
 */

/**
 * @name Fiber Synchronization Semaphore Lock Control
 * @{
 */

/**
 *  Defines the maximum lock value the Syncronized Semaphore can attain.
 */
#define JK_FIBER_SS_LOCK_LIMIT              (65535)

/**
 *  The bit-field mask used to access the Synchronized Semaphore's
 *  initial lock setting.
 */
#define JK_FIBER_SS_LOCK_BASIS_MASK         (0x0000FFFF)

/**
 *  The bit-field position (zero-based offset) of the Synchronized Semaphore's
 *  initial lock setting.
 */
#define JK_FIBER_SS_LOCK_BASIS_POS          (0x00)

/**
 *  The bit-field mask used to access the Synchronized Semaphore's
 *  lock limit.
 */
#define JK_FIBER_SS_LOCK_LIMIT_MASK         (0xFFFF0000)

/**
 *  The bit-field position (zero-based offset) of the Synchronized Semaphore's
 *  lock limit.
 */
#define JK_FIBER_SS_LOCK_LIMIT_POS          (0x08)

/**
 * @}
 */

/**
 *  Creates a Synchronized Object for use with Fibers.
 * 
 *  @param hFiberSyncedObjectPool
 *   A valid Synchronized Object Pool object handle.
 *  @param ulSpecification
 *   A value indicating what type of Synchronized Object to create.
 *  @param ulOptions
 *   A bit-field specifying various flags for Synchronized Object creation.
 *  @param phFiberSyncedObject
 *   Upon function success, a valid #JKFiberSyncedObjectHandle is 
 *   returned.<br>
 *   Upon function failure, the contents of this parameter remain 
 *   unchanged.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_NO_MEMORY<br>
 *     when there is not enough memory available to complete the operation.
 * 
 *  <p>
 *  This function allocates a @ref 
 *  Fiber_Synced_Object_JBI "Synchronized Object" from the @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Object Pool" specified by 
 *  <i>hFiberSyncedObjectPool</i> and returns the handle to it in the 
 *  memory referenced by <i>phFiberSyncedObject</i>.
 *
 *  The <i>ulSpecification</i> parameter is used to specify what type of 
 *  Synchronized Object will be created. Valid values are 
 *  #JK_FIBER_SO_SPECIFICATION_EVENT, #JK_FIBER_SO_SPECIFICATION_SECTION and
 *  #JK_FIBER_SO_SPECIFICATION_SEMAPHORE. The <i>ulSpecification</i> parameter
 *  is used as an ordinal value instead of a bit-field (as seen in the 
 *  #AmFiberSyncedObjectPoolCreate() function).
 * 
 *  When #JK_FIBER_SO_SPECIFICATION_EVENT is specified in the 
 *  <i>ulSpecification</i> parameter, a Synchronized Event object will be 
 *  created with a formal type of #JKFiberSyncedEventHandle. A Synchronized 
 *  Section object with a formal type of #JKFiberSyncedSectionHandle will be 
 *  created when #JK_FIBER_SO_SPECIFICATION_SECTION is used. Lastly, a
 *  Synchronized Semaphore object will be created with a formal type of
 *  #JKFiberSyncedSemaphoreHandle when #JK_FIBER_SO_SPECIFICATION_SEMAPHORE
 *  is used. All three objects are subclasses of the ubiquitous Synchronized 
 *  Object. As such, the handle used to manage these objects can be cast to 
 *  the #JKFiberSyncedObjectHandle type when needed.
 * 
 *  Usage of the <i>ulOptions</i> parameter varies based on the value 
 *  supplied in the <i>ulSpecification</i> parameter. 
 * 
 *  The @ref JK_FIBER_SO_SPECIFICATION_EVENT "Synchronized Event" 
 *  specification enables the use of the @ref
 *  JK_FIBER_SE_TYPE_TOGGLE "JK_FIBER_SE_TYPE_XXX"
 *  and conditionally the @ref
 *  JK_FIBER_SE_STATE_RESET "JK_FIBER_SE_STATE_XXX" 
 *  and @ref JK_FIBER_SE_RESET_MANUAL "JK_FIBER_SE_RESET_XXX" 
 *  flags with the <i>ulOptions</i> parameter. In consideration of the 
 *  object @ref JK_FIBER_SE_TYPE_TOGGLE "type", these flags may be 
 *  bit-wise OR'ed together to control the initial signal state and signal 
 *  reset behaviour of the Synchronized Event object being created.
 * 
 *  The @ref 
 *  JK_FIBER_SO_SPECIFICATION_SECTION "Synchronized Section"
 *  does not make use of any flags in the <i>ulOptions</i> parameter. In 
 *  this case, the value of the <i>ulOptions</i> parameter should be 
 *  <code>0x00000000</code>.
 * 
 *  The @ref 
 *  JK_FIBER_SO_SPECIFICATION_SEMAPHORE "Synchronized Semaphore"
 *  uses the <i>ulOptions</i> parameter to specify initial and maximum lock
 *  settings. The @ref JK_FIBER_SS_LOCK_BASIS_MASK "lock control masks" 
 *  should be used with the <i>ulOptions</i> parameter to ensure proper 
 *  configuration. The @ref JK_FIBER_SS_LOCK_BASIS_MASK "initial count" 
 *  must be greater than or equal to zero. The 
 *  @ref JK_FIBER_SS_LOCK_LIMIT_MASK "lock limit" will be set to 
 *  #JK_FIBER_SS_LOCK_LIMIT when specified as zero (0) in the 
 *  <i>ulOptions</i> parameter. Both values must be less than or equal to
 *  #JK_FIBER_SS_LOCK_LIMIT.
 *
 *  The Synchronized Event and Synchronized Section handles 
 *  indirectly returned by this function, via memory referenced by the
 *  <i>phFiberSyncedObject</i> parameter, may be used by the @ref 
 *  Fiber_JBI to manage Fiber state relationships. See 
 *  #AmFiberEventWait(), #AmFiberSectionEnter() and #AmFiberSemaphoreWait()
 *  for more details.
 * 
 *  Fibers can use this function to create new Synchronization Objects.
 * 
 *  @par Note:
 *  The value returned in the buffer referenced 
 *  by <i>phFiberSyncedObject</i> must be released 
 *  via #AmFiberSyncedObjectRelease() before the Synchronized Object Pool 
 *  can be @ref AmFiberSyncedObjectPoolDestroy() "destroyed".
 *
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 * 
 *  @see
 *  AmFiberEventWait, AmFiberSectionEnter, AmFiberSemaphoreWait,
 *  AmFiberSyncedObjectRelease, AmFiberSyncedObjectPoolDestroy
 *
 */

long AmFiberSyncedObjectCreate( JKFiberSyncedObjectPoolHandle hFiberSyncedObjectPool, unsigned long ulSpecification, unsigned long ulOptions, JKFiberSyncedObjectHandle *phFiberSyncedObject );

/**
 *  Releases a Synchronized Object from use.
 * 
 *  @param hFiberSyncedObjectPool
 *   A valid Synchronized Object Pool object handle.
 *  @param hFiberSyncedObject
 *   A valid Synchronized Object handle.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Synchronized Object is still in use.
 *   - #JK_RESULT_FIBER_ITEM_NOT_FOUND<br>
 *     when the <i>hFiberSyncedObject</i> is not found in the Synchronized 
 *     Object Pool specified by <i>hFiberSyncedObjectPool</i>.
 * 
 *  <p>
 *  This function releases a @ref 
 *  Fiber_Synced_Object_JBI "Synchronized Object" (as specified by 
 *  <i>hFiberSyncedObject</i>) from use and allows the resources it 
 *  consumes to be re-used by the @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Object Pool".
 *
 *  The #AmFiberSyncedObjectCreate() function is used to create 
 *  Synchronized Objects of various @ref 
 *  JK_FIBER_SO_SUBCLASS_EVENT "types". These objects must no longer 
 *  be in use by when calling this function. This means that Synchronized 
 *  Objects cannot be released until all references on it are removed. 
 *  Once a Synchronized Object is released, its handle should no longer be 
 *  used.
 *
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberSyncedObjectCreate
 *
 */

long AmFiberSyncedObjectRelease( JKFiberSyncedObjectPoolHandle hFiberSyncedObjectPool, JKFiberSyncedObjectHandle hFiberSyncedObject );

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AM_FIBERSYNCEDOBJECTPOOL_H */
