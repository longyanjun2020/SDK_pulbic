
/**
 * @file
 * u\@MMS transmission Service Layer
 *
 * Service API exposed by the u\@MMS transmission module
 *
 * <!-- #interface list begin -->
 * \section nccmms_trans Interface
 * - NCCMms_trans_init()
 * - NCCMms_trans_quit()
 * - NCCMms_trans_destroy()
 * - NCCMms_trans_commitReq()
 * - NCCMms_trans_run()
 * - NCCMms_trans_makeReqByType()
 * - NCCMms_trans_cleanReqByType()
 * <!-- #interface list end -->
 */

#ifndef __NCCMMS_TRANS_H__
#define __NCCMMS_TRANS_H__

#include <ncc_types.h>
#include <nccport_file.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
   * ======= CONSTANTS AND MACROS =======
   */

/**
   *    \name Return Values for fnTrans_*** functions.
   */

/**define the correct return value of function*/
#define TRANS_SUCCESS                                        0
/**define the error return value of function*/
#define TRANS_FAILED                                         -1

/**define single thread  macro of transmission*/
#define SThread

/**
   *    \name   Constants for request type are used by function NCCMms_trans_commitReq
   */

/*@{*/

/**define the request type of new item addition when to commit request*/
#define MMS_Trans_Add                                        0x1
/**define the request type of deleting the pointed item when to commit request*/
#define MMS_Trans_Del                                        0x2
/**define the request type of getting all request state struct when to commit request*/
#define MMS_Trans_GetAllState                                0x3
/**define the request type of getting the pointed item state struct when to commit request*/
#define MMS_Trans_GetOneState                                0x4
/**define the request type of getting configure when to commit request*/
#define MMS_Trans_GetConfig                                  0x5
/**define the request type of setting configure when to commit request*/
#define MMS_Trans_SetConfig                                  0x6
/**define the request type of being in need of generate the new one after reveiving Push SMS when to commit request*/
#define MMS_Trans_PUSH                                       0x7

/*@}*/

/**
   *    \name   constants for extention operation type when to commit request
   */

/*@{*/

/**define the extention operation type of offering configure buffer when to make the new request*/
#define MMS_Trans_Ex_OfferConfig                             0x10

/*@}*/

/**
   *    \name task state for Manager
   */

/*@{*/

/**define the task state when the task not running*/
#define Task_New                                             0
/**define the task state when the task is running*/
#define Task_Loaded                                          1

/*@}*/

/**
   *    \name current task status
   */

/*@{*/

/**define the status of task idle when to need write report into *.sta file*/
#define Status_Idle                                          0
/**define the status of task processing when to need write report into *.sta file*/
#define Status_Doing                                         1
/**define the status of task processing complete when to need write report into *.sta file*/
#define Status_Done                                          2
/**define the status of task processing complete but failed */
#define Status_Failed                                        3

/*@}*/

/**
   *    \name Return Values for Mng_GetCurrentTaskInfo function.
   */

/*@{*/

/**define the state of having no task when Transmission module processing*/
#define State_NoTask                                         0
/**define the state of the current task excuting when Transmission module processing*/
#define State_Process                                        1
/**define the state of the current task suspending or finishing in need of finding next one when Transmission module processing*/
#define State_Restart                                        2
/**define the state of the current task being lock when Transmission module processing, maybe unused*/
#define State_Lock                                           3
/**define the state of the current running task being del when Transmission module processing*/
#define State_Del                                            4

/*@}*/

/**
   *    \name   macros for adding request type when to commit request using MMS_Trans_Add
   */

/*@{*/

/**define the request value mask*/
#define Req_Mask                                             0xa0

/**define the request type of sending notify response*/
#define Req_NotifyResp                                       0xa1
/**define the request type of sending mms body*/
#define Req_Send                                             0xa2
/**define the request type of auto downloading mms immediately through mmsc*/
#define Req_Get_Immediately                                  0xa3
/**define the request type of deferred downloading mms through mmsc by user*/
#define Req_Get_Defered                                      0xa4
/**define the request type of sending acknowledge report after deferred downloading mms*/
#define Req_Acknowledge                                      0xa5
/**define the request type of sending reject report after deleting mms*/
#define Req_Reject                                           0xa6
/**define the request type of forwarding mms notify sms*/
#define Req_Forward                                          0xa7
/**define the request type of sending read report after reading downloading mms at the first time*/
#define Req_ReadReport                                       0xa8

/*@}*/

/**
   *    \name   some default values for maximum in request category
   */

/*@{*/

/**define max request type num*/
#define Max_RequestType                                      8
/**define max index num*/
#define Max_Index                                            20
/**define max lenth of directory name*/
#define DIR_NAME_MAX                                         MAX_FILENAME_LEN
/**define max request num*/
#define Max_ReqNum                                           Max_Index

/*@}*/

/**
   *    \name   some default values for maximum in configure category
   */

/*@{*/

/**define max APN length*/
#define MMS_APN_Max_Num                                      40
/**define max MMSC addr length*/
#define MMS_MMSC_ADDR_LEN                                    100
/**define max gateway length*/
#define MMS_GATEWAY_LEN                                      100
/**define max proxy gateway addr length*/
#define MMS_PROXY_LEN                                        40

/*@}*/

/**
   *    \name Values for Parsing pdu type.
   */

/*@{*/

/**define a callback buffer type: notification*/
#define MMS_NOTIFICATIONIND                                  0x1
/**define a callback buffer type: PDU-type readreport*/
#define MMS_READREPORTPDU                                    0x2
/**define a callback buffer type: delivery pdu*/
#define MMS_DELIVERYREPORT                                   0x3
/**define a callback buffer type: MMS-type readreport*/
#define MMS_READREPORTMMS                                    0x5
/**define a callback buffer type: downloaded MM*/
#define MMS_DOWNLOADEDMM                                     0x6
/*define a callback buffer type: The operation of immediately download MM is unsuccessful,then convert it into deferred download.*/
#define MMS_IMMEDIATELYDOWNLOADMM_FAIL                       0x7
/*define a callback buffer type:M-Send.conf pdu*/
#define MMS_SEND_CONF_PDU                                    0x8
/*define a callback buffer type:M-Forward.conf pdu*/
#define MMS_FORWARD_CONF_PDU                                 0x9

/*@}*/

/**
   *    \name current running status
   */

/*@{*/

/**define a status type: try again*/
#define RUN_STATUS_TRYAGAIN                                  0x1
/**define a status type: no task*/
#define RUN_STATUS_NOTASK                                    0x2
/**define a status type: net send success*/
#define RUN_STATUS_NETSEND_SUCCESS                           0x3
/**define a status type: net send failed, wap failed*/
#define RUN_STATUS_NETSEND_FAILED                            0x4
/**define a status type: MMS protocol failed*/
#define RUN_STATUS_MMS_FAILED                                0x5
/**define a status type: WAP uri not found*/
#define RUN_STATUS_URINOTFOUND                               0x6
/**define a status type: Other error*/
#define RUN_STATUS_OTHER_ERR                                 0x7

/*@}*/

/**
   *    \name Values for no state file when to query state by ID matching
   */

/*@{*/

/**define a macro for no state file when to query state by ID matching*/
#define MMS_VAL_NoState                                      0xa1

/*@}*/

/**
   *    \name Return Values for fnTrans_xxx functions.
   */

/*@{*/

/**define the return value mask*/
#define MMS_ERR_VAL_MASK                                     0xffffff00
/**define the return value of null pointer using*/
#define MMS_ERR_VAL_NULL_POINTER                             -2
/**define the return value of unknown operation type when make new request*/
#define MMS_ERR_VAL_UKNOWN_OPTYPE                            -3
/**define the return value when malloc failed*/
#define MMS_ERR_VAL_MALLOC                                   -4
/**define the return value of no length given when malloc*/
#define MMS_ERR_VAL_ZERO_LENGTH                              -5
/**define the return value of failing to open one file*/
#define MMS_ERR_VAL_FILEOPEN                                 -6
/**define the return value of invalid ID inputting*/
#define MMS_ERR_VAL_Invalid_ID                               -7
/**define the return value of too many folder existing when to init Transmission module*/
#define MMS_ERR_VAL_Overmany_Folder                          -8
/**define the return value of too many files existing when to add more request files*/
#define MMS_ERR_VAL_Overmany_File                            -9
/**define the return value of no file existing when to load more task data files*/
#define MMS_ERR_VAL_NoFile                                   -10
/**define the return value of invalid argument of function calling*/
#define MMS_ERR_VAL_INVALID_ARGS                             -11
/**define the return value of MM or PDU parse error */
#define MMS_ERR_VAL_PARSE                                    -12
/**define the return value of dail failure*/
#define MMS_ERR_VAL_DIAL                                     -13
/**define the return value of porting layer netSend error */
#define MMS_ERR_VAL_NETSEND                                  -14
/**define the return value of NCCMms_trans_run: if this happen, report.text is fullfilled*/
#define MMS_ERR_VAL_RESPONSE_PARSE                           -15
/**define the return value of identical ID when adding new request*/
#define MMS_ERR_VAL_IDENTICAL_ID                             -16

/**define the return value of unknown error*/
#define MMS_ERR_VAL_Other                                    -30

/*@}*/

/**
   *=======Data Structures are used by Transmission Module=======
   */

/**
   *    \name Structure Types that are used by Transmission Module
   */

/*@{*/

/**
 * Structure that defines dial information for mms configure,it is used by Transmission Module
 */
typedef struct {
    int8_t APN[MMS_APN_Max_Num];        /**< string buf used for saving APN name*/
    int8_t user[MMS_APN_Max_Num];       /**< string buf used for saving APN user name*/
    int8_t passwd[MMS_APN_Max_Num];     /**< string buf used for saving APN user passward*/
} T_MMS_Dial_Cfg;

/**
 * Structure that defines connect information for mms configure,it is used by Transmission Module
 */
typedef struct {
    int32_t protocol_mask;                  /**< used to select the suitable stack which is wap or http*/
    int8_t mmsc_addr[MMS_MMSC_ADDR_LEN];    /**< used to save the address of mms center*/
    int8_t gateway[MMS_GATEWAY_LEN];        /**< used to save the address of gateway*/
    int32_t gateway_port;                   /**< used to save the port number of gateway*/
    int8_t proxy[MMS_PROXY_LEN];            /**< used to save the address of HTTP proxy when using http stack*/
    int32_t proxy_port;                     /**< used to save the port number of gateway when using http stack*/
    int32_t up_limit;                       /**< used to save the max transport bitrate*/
    int32_t low_limit;                      /**< used to save the min transport bitrate*/
} T_MMS_Conn_Cfg;

/**
 * Structure that defines control information for mms configure,it is used by Transmission Module
 */
typedef struct {
    int32_t defer_download;     /**< select the proper downloading mode which is immediately or deferred*/
    int32_t send_deliveryreport;    /**< select the proper sending delivery report mode which is or not*/
    int32_t recv_readreport;    /**< select the proper recveive read report mode which is or not*/
} T_MMS_Cfg;

/**
 *  Structure that defines folder info for mms transmission
 */
typedef struct {
    int8_t *Default_TaskList_Dir; /**< define the default directory path of task file list , Path should be a string Macro */
    int8_t *Default_TaskData_Dir; /**< define the default directory path of task data file, Path should be a string Macro */
    int8_t *Default_TaskState_Dir; /**< define the default directory path of task state file,Path should be a string Macro */
} T_MMS_Folder_cfg;

/**
 * Structure that defines all sub_struct for mms configure,it is used by Transmission Module
 */
typedef struct {
    T_MMS_Dial_Cfg dial_param;  /**< used to save dial configure info*/
    T_MMS_Conn_Cfg conn_param;  /**< used to save connect configure info*/
    T_MMS_Cfg mms_cfg;          /**< used to save control configure info*/
    T_MMS_Folder_cfg folder_cfg; /**< used to save folder configure info for transmission  */
} T_MMS_Trans_Cfg;

/**
 * Structure that saves interactive data between manager and transaction module when transmission is running,it is used by Transmission Module
 */
typedef struct {
    int32_t task_id;                    /**< used to save task id*/
    int8_t task_name[DIR_NAME_MAX + 5]; /**< used to save task name*/
} T_Trans_TaskKey;

/**
 * Structure that saves the status report data when submitting the report to transmission,it is used by Transmission Module
 */
typedef struct {
    int32_t status;     /**< used to mark the task status which is Task_New or Task_Loaded*/
    int32_t stage;      /**< used to express the percent of task running progress*/

    int32_t text_len;   /**< used to express the length of the status text from gateway*/
    int8_t *text;       /**< used to saved the status text buffer from gateway*/
} T_MMS_Status_Report;

/**
 * Structure that saves the state report chained list for proper tasks when querying the report by task ID,it is used by Transmission Module
 */
typedef struct T_MMS_State {
    int32_t task_id;            /**< the task ID which the user need to query the state report by*/
    int32_t TaskStatus;         /**< express the task current task status to the task ID*/
    int32_t TaskState;          /**< express the task state for running state which is Task_New or Task_Loaded*/

    T_MMS_Status_Report Report; /**< express the status report from gateway*/

#ifdef SThread
    struct T_MMS_State *Next;   /**< next pointer in chained list*/
#endif
} T_MMS_State;

/**
 * Structure that saves the new task data when submitting the new one task,it is used by Transmission Module
 */
typedef struct {
    int8_t *op_buf;         /**< buffer saved pdu data or URL into*/
    int32_t op_buf_len;     /**< pdu data or URL buffer length*/

    int32_t req_type;       /**< request type for the new task*/
} T_MMS_Trans_Data;

/**
 * Structure that saves the new request data when submitting the new one request,it is used by Transmission Module
 */
typedef struct {
    int32_t Req_ID;             /**< the request ID generated by user*/
    int32_t Op_Type;            /**< operation type such as add,del,query, etc.*/

    T_MMS_Trans_Cfg *pConfig;   /**< used to save mms configure info which may be supported by user or be feed back info when to get configure info*/
    T_MMS_Trans_Data Data;      /**< used to save the new task data when submitting the new one task*/
    T_MMS_State *pState;        /**< used to save the state report when to query*/
} T_MMS_Request;

/**
 * Structure that indicate current NCCMms_trans_run() status
 */
typedef struct {
    int32_t run_status;             /**< used to indicate current running status */
    int32_t task_id;                /**< used to indicate which task is running*/
    int32_t task_status;            /**< used to indicate current task status */
    int32_t task_stage;             /**< used to indicate current task netSend stage (1 ~ 100) */
#ifdef TRANS_DEBUG
    int32_t protocol_status;        /**< used while debug netSend porting layer module */
#endif
} T_MMS_FeedbackInfo;

/*@}*/

/**
   *=======define API functions of transmission module=======
   */

/**
   *    \name   API functions of transmission module.
   */

/*@{*/

/**
 * Fucntion type define for transmission callback, After user regitered this callback,
 * transmissio will call this callback at following cases:\n
 * 1. get a PDU-type readreport\n
 * 2. get a delivery report\n
 * 3. get a notification.ind if current config is defer download\n
 * 4. get a MM (both of normal MM and MMS-type readreport)\n
 *
 * \param  type            buffer type
 * \param  *buf            buffer address
 * \param  len             buffer len
 *
 * example code:<pre>
 * void test_Notifier (uint32_t type, uint8_t* buf, uint32_t len)
   {
   switch (type)
   {
   case MMS_READREPORTPDU:
       save_as_prefix (buf, len, "C:\\mms\\Notifier_save\\readReport_pduType");
       break;
   case MMS_DELIVERYREPORT:
       save_as_prefix (buf, len, "C:\\mms\\Notifier_save\\delivery_pdu");
       break;
   case MMS_NOTIFICATIONIND:
       save_as_prefix (buf, len, "C:\\mms\\Notifier_save\\notification_pdu");
       break;
   case MMS_DOWNLOADEDMM:
       save_as_prefix (buf, len, "C:\\mms\\Notifier_save\\downloadedMM");
       break;
   defult:
       break;
   }
   }</pre>
 *
 */
typedef void (*FUNC_Notifier) (int32_t type, uint8_t * buf, int32_t len);

/**
 * Used to init transmission module, init mms configure info and register push handle callback function
 * \param  *pConfig            the pointer of mms configure
 * \param  *pTOP_Handle          transmission handle address,output param
 * \param  callback            callback function address
 *
 * \return <ul>
 *             <li> #TRANS_SUCCESS          if success
 *             <li> #MMS_ERR_VAL_NULL_POINTER       if parameter NULL
 *             <li> #MMS_ERR_VAL_Overmany_Folder        if too many folders
 *             <li> #MMS_ERR_VAL_UKNOWN_OPTYPE      if op_type unknown
 *             <li> #MMS_ERR_VAL_INVALID_ARGS       if parameter invalid
 *         </ul>
 *
 * example code:<pre>
  int32_t TOP_Hanle;
  int32_t transmission_init_example (void)
  {
   T_MMS_Trans_Cfg cur_config;
   int32_t ret;
   get_your_config (&cur_config);
   ret = NCCMms_trans_init (&cur_config, &TOP_Handle, test_Notifier);
   assert (TRANS_SUCCESS == ret);
  }
   </pre>
 *
 */
int32_t NCCMms_trans_init(T_MMS_Trans_Cfg * pConfig, int32_t * pTOP_Handle,
                          FUNC_Notifier callback);

/**
 * Clean transmission module(free memory and clean all state files, request files and task files).
 * \param  TOP_Handle            transmission handle address
 * \return <ul>
 *             <li> #TRANS_SUCCESS          if success
 *             <li> #MMS_ERR_VAL_NULL_POINTER       if parameter NULL
 *             <li> #MMS_ERR_VAL_INVALID_ARGS       if parameter invalid
 *         </ul>
 */
int32_t NCCMms_trans_quit(int32_t TOP_Handle);

/**
 *Only free the memory for MMS transmission module.It is different from NCCMms_trans_quit() API.
 *This APIs only free memory,not clean all files(state files, request files and task files)
 *that are related to MMS transmission.
 *  \param  T_Handle    transmission handle address.
 *  \return
 *  <ul>
 *      <li>#TRANS_SUCCESS,if successed.
 *  </ul>
 */
int32_t NCCMms_trans_destroy(int32_t T_Handle);

/**
 * Commit one new request
 * \param  TOP_Handle
 * \param  pInput
 * \return <ul>
 *             <li> #TRANS_SUCCESS          if success
 *             <li> #MMS_ERR_VAL_NULL_POINTER       if parameter NULL
 *             <li> #MMS_ERR_VAL_INVALID_ARGS       if parameter invalid
 *             <li> #MMS_ERR_VAL_NULL_POINTER       if parameter NULL
 *         </ul>
 */
int32_t NCCMms_trans_commitReq(int32_t TOP_Handle, T_MMS_Request * pInput);

/**
 * User call this function to drive the real task processing. Everytime, MMI
 * call this, MMI should check the return value to get what happen at current stage
 * \param  TOP_Handle            transmission handle address
 * \param  *feedback_info      feedback_info about current running
 * \return <ul>
 *             <li>when successful,return#TRANS_SUCCESS, then check feedbak_info.run_status
 *                 <ul>
 *         <li>#RUN_STATUS_TRYAGAIN
 *         <li>#RUN_STATUS_NOTASK
 *         <li>#RUN_STATUS_NETSEND_FAILED
 *         <li>#RUN_STATUS_NETSEND_SUCCESS
 *         <li>#RUN_STATUS_MMS_FAILED
 *                 </ul>
 *             <li>when failed,return
 *                 <ul>
 *                     <li>#MMS_ERR_VAL_NULL_POINTER
 *                     <li>#MMS_ERR_VAL_INVALID_ARGS
 *                     <li>#MMS_ERR_VAL_NETSEND
 *                     <li>#MMS_ERR_VAL_DIAL
 *                 </ul>
 *         </ul>
 *
 * example code: <pre>
   #define DIAL_COUNT_MAX      5
   #define NETSEND_WAP_ERR_MAX 5
   do {
       ret = NCCMms_trans_run(Handle, &feedback_info);\n
       // if dial failed, try again
       if (MMS_ERR_VAL_DIAL == ret)
       {
           dial_count++;
           if (dial_count >= DIAL_COUNT_MAX)
           {
               // continous error !
               // give up, or try it later
           }
           continue;
       }
       dial_count = 0;\n
       if ((TRANS_SUCCESS == ret) && (RUN_STATUS_NETSEND_FAILED == feedback_info.run_status))
       {
           // netSend : RUN_STATUS_NETSEND_FAILED (wap problem)
           netSend_wap_err++;
           if (netSend_wap_err >= NETSEND_WAP_ERR_MAX)
           {
               // continous error !
               // give up, or try it later
               // check your MMS config right or wrong
           }
           break;
       }
       netSend_wap_err = 0;
       if (TRANS_SUCCESS == ret)
       {
           switch (feedback_info.run_status)
           {
           case RUN_STATUS_TRYAGAIN:
               break;
           case RUN_STATUS_NOTASK:
               break;
           case RUN_STATUS_NETSEND_SUCCESS:
               {
                   T_MMS_Request repState;
                   // query status
                   CRTL_memset(&repState,0,sizeof(T_MMS_Request));
                   repState.Op_Type = MMS_Trans_GetAllState;
                   NCCMms_trans_makeReqByType(&repState);
                   ret = NCCMms_trans_commitReq(Handle, &repState);
                   NCCMms_trans_cleanReqByType(&repState);
               }
               break;
           case RUN_STATUS_MMS_FAILED:
               {
                   T_MMS_Request repState;
                   // query status
                   CRTL_memset(&repState,0,sizeof(T_MMS_Request));
                   repState.Op_Type = MMS_Trans_GetAllState;
                   NCCMms_trans_makeReqByType(&repState);
                   ret = NCCMms_trans_commitReq(Handle, &repState);
                   NCCMms_trans_cleanReqByType(&repState);
               }
               break;
           default:
               break;
           }
       }
       if (TRANS_SUCCESS != ret)
       {
           // TODO: your jobs here
           break;
       }
   } while (0);
  </pre>
 */
int32_t NCCMms_trans_run(int32_t TOP_Handle,
                         T_MMS_FeedbackInfo * feedback_info);

/**
 * Make request struct according to the operation type
 * malloc space according to:\n
 * pInput->Op_Type     :the type of the option. can use those macro named "Constants for request type",
 *                      if Mask MMS_Trans_Ex_OfferConfig is set by a option 'and', malloc config space,
 *                          such as Req_Send&MMS_Trans_Ex_OfferConfig \n
 * pInput->Data.op_buf_len : if not zero, malloc op_buf_len size space and memset it\n
 * \param  *pInput         the new request data struct
 * \return <ul>
 *             <li> #TRANS_SUCCESS          if success
 *             <li> #MMS_ERR_VAL_NULL_POINTER       if parameter NULL
 *             <li> #MMS_ERR_VAL_MALLOC         if no memory
 *             <li> #MMS_ERR_VAL_ZERO_LENGTH        if pInput->Data.op_buf_len is zero
 *             <li> #MMS_ERR_VAL_UKNOWN_OPTYPE      if op_type unknow
 *         </ul>
 */
int32_t NCCMms_trans_makeReqByType(T_MMS_Request * pInput);

/**
 * Clean request struct according to the operation type
 * \param  *pInput         the point request data struct
 * \return <ul>
 *             <li> #TRANS_SUCCESS          if success
 *             <li> #MMS_ERR_VAL_NULL_POINTER       if parameter invalid
 *             <li> #MMS_ERR_VAL_UKNOWN_OPTYPE      if op_type unknow
 *         </ul>
 */
int32_t NCCMms_trans_cleanReqByType(T_MMS_Request * pInput);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* __NCCMMS_TRANS_H__ */
