



/** \mainpage OS SCOPE AND OVERVIEW
 *
 *  \section OSS Operating system scope
 *  The operating system (OS) has been designed for real time embedded software, with the below scope.
 *  \section TM Task management
 *  The OS contains a multi-task, preemptive, priority-based scheduler that is responsible for the correct scheduling of tasks. The scheduling algorithm can be summarized as follows:
 *
 * Each task is assigned a priority. A task is susceptible to be run when it has been initialized, started and is not waiting for a semaphore or mailbox event. A task is activated when it has the highest priority out of all those tasks that are susceptible to run.
 *
 * Every time a task becomes ready, the scheduler is activated to verify the tasks relative priorities. If the new ready task has a higher priority than the running task, the running task will be immediately put in the suspended state and the new task will be activated. The execution of the running task has been preempted by the new task. Thus, a running task can be stopped anytime by the scheduler. The suspended task is resumed when the new task is finished or is waiting for a semaphore or a mailbox.
 *
 *  \section CSM Critical section management
 * The OS provides critical section management. Critical sections are used to stop the scheduling process for a short period of time. These sections are needed when a task must not be interrupted (for example when a time critical operation is in progress).
 *
 *  \section SMFM Semaphore, mutex and flag management
 * The OS provides three types of thread as well as share resource access synchronization mechanisms, including semaphore/mutex/flag services.
 *
 * A mutex (mutual exclusion object) allows multiple threads to share a resource serially and could be considered as a binary semaphore. Besides, the mutex is with the owner concept and prority inherence protocol to deal with potential priority inversion issue.
 *
 * On the other hand, flags are synchronization mechanisms represented by a 32-bit word. Each bit in the flag represents a condition, which allows a thread to wait for either a single condition or a combination of conditions. The waiting thread specifies if all conditions or a combination of conditions are to be met before it wakes up. The signaling thread can then set or reset bits according to specific conditions so the appropriate thread can be executed.
 *
 *  \section MTM Mailbox and timer management
 * The OS provides mailbox management. Mailboxes are used for inter-task communication and synchronization. Tasks can send messages to a mailbox or wait for messages to arrive in a mailbox. Two tasks can be synchronized by having one of them send messages to a certain mailbox and having the other wait for messages to arrive in the same mailbox. A mailbox can also be used to allow a task to wait for the expiration of a delay (timer management).
 *
 *  \section MM Memory management
 * The OS provides dynamic memory management. Dynamic Memory Management is provided in order to optimize the overall RAM requirements. Both pool (fixed size) and heap (variable size) are supported.
 *
 *  \section QM Queue management
 * The OS provides queue management. Queues are used to create and manage linked lists of various objects. Primitives are provided to add, remove and search for objects in a queue. Queues are used internally by the Real Time Kernel to manage tasks, semaphores, mailboxes and memory pools.
 *
 *  \section IEM Interrupt and exception management
 * The OS provides interrupt management. The parameters of each primitive are checked for consistency. When an error is found, a user-provided exception handler is called to handle the error. The exception handler does not return meaning that it is fatal and terminates program execution.
 *
 * The exception handler is not included in the operating system and must be defined by the programmer.
 * The exception handler's C prototype is given below
 *
 * - void RtkExceptionRoutine(u8, u32);
 *
 * In Mstar mobile platform, this exception handler is called "backtrace". The purposes of this handler are to:
 *
 * - Deal with different type of exception reasons.
 * - Dump the corresponding and necessary information from OS kernel or HW dependent layer, through the pre-defined "arbiter".
 * - Store into the user-defined flash area.
 * - Auto reset then reboots up the target.
 * - Store the raw data into SD card upon next reboot.
 *
 * Then the PC side development tool (combined in TMT) will parse the raw content according to the workspace and generate the user readable text exception log for crash issue resolving.
 */

/**
 * @defgroup TaskMan1 Task Management
 *
 **/

/**
 * @defgroup CRITAREA Critical Area Management
 *
 **/

/**
 * @defgroup UTIL Utilities
 *
 **/

/**
 * @defgroup FlagMan Flag Management
 *
 **/

/**
 * @defgroup IntMan Interrupt Management
 *
 **/

/**
 * @defgroup MailMan Mailbox Management
 *
 **/

/**
 * @defgroup SenMan Semaphore Management
 *
 **/

/**
 * @defgroup  TimerMan Timer Management
 *
 **/

/**
 * @defgroup  MemMan Memory  Management
 *
 **/