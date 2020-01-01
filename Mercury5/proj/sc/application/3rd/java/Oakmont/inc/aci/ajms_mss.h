/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */
/** 
 * @file ajms_mss.h
 * Application Security Setting ACI
 */

#ifndef AJMS_MSS_HEADER
#define AJMS_MSS_HEADER

#ifdef __cplusplus
extern "C"{
#endif

#include "aj_type.h"
#include "ajms_pcs.h"
#include "ajms_common.h"


/*
 *  Interfaces listed in the group are used for application security setting, 
 *  including these functionalities:
 *       - Get midlet suite's protection domain.
 *       - Get midlet suite's security setting.
 *       - Set midlet suite's security setting.
 *       .
 */

/** 
 * @addtogroup ams_security_setting_error_code
 *
 * @par Include file 
 * \#include ajms_mss.h
 *  @{ 
 */
/**  
 * No error. 
 */
#define AJMS_MSS_ERR_NONE                (0)
/**  
 * An alert level conflict occurred.
 */
#define AJMS_MSS_ERR_CONFLICT_ALERT     (-1)
/**  
 * An exclusive level conflict occurred.
 */
#define AJMS_MSS_ERR_CONFLICT_EXCLUSIVE (-2)
/**  
 * Invalid parameter. 
 */
#define AJMS_MSS_ERR_INVALID_PARAM      (-3)
/**  
 * Function failed because the function group is for private use. 
 */
#define AJMS_MSS_ERR_GROUP_IS_PRIVATE   (-4)
/**  
 * Function failed because the permission level set to the function group is Allowed.
 */
#define AJMS_MSS_ERR_GROUP_IS_ALLOWED   (-5)
/**  
 * An I/O operation failed. 
 */
#define AJMS_MSS_ERR_IO                 (-6)
/**  
 * Failed for any other reason.
 */
#define AJMS_MSS_ERR_INTERNAL           (-7)
/** @} */

/** 
 * @addtogroup Protection_Domain_Retrieval_ACI
 *
 * @par Include file 
 * \#include ajms_mss.h
 * @{ 
 */

/**
 *        Gets the protection domain of an installed MIDlet suite.
 * @param suiteId 
 *        The identifier of the MIDlet suite.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @retval "A protection domain identifier"
 *         The identifier of the protection domain to which the designated MIDlet suite belongs. 
 *         One of the following values:
 *          - #AJMS_PCS_DOMAIN_UNSPECIFIED
 *          - #AJMS_PCS_DOMAIN_MANUFACTURER
 *          - #AJMS_PCS_DOMAIN_OPERATOR
 *          - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *          .
 * @retval #AJMS_MSS_ERR_INVALID_PARAM
 *         if the <i>suiteId</i> parameter is invalid.
 * @retval #AJMS_MSS_ERR_IO
 *         if a file I/O error occurs.
 * @retval #AJMS_MSS_ERR_INTERNAL
 *         if the function fails for any other reason.
 */
AJ_S32 ajms_mss_getDomainId( const AJ_S32 suiteId );
/** @} */

/** @addtogroup Function_Group_ACI
 *
 * @par Include file 
 * \#include ajms_mss.h<br>
 * \#include ajms_pcs.h
 *  @{ 
 */

/**
 *         Gets the current user interaction mode set for a function group.
 * @param  suiteId
 *         The identifier of the application.
 * @param  groupId
 *         The function group index. 
 *         The value should be between 0 and the return value of ajms_pcs_getGroupCount() minus 1.
 *         All the properties of a function group is available via ajms_pcs_getGroup().
 * @param  mode
 *         A pointer to the buffer for receiving the current user interaction mode.
 *         This function sets one of the following mode values in the buffer when it returns #AJMS_MSS_ERR_NONE.
 *         - #AJMS_PCS_MODE_NO
 *         - #AJMS_PCS_MODE_ONESHOT 
 *         - #AJMS_PCS_MODE_SESSION 
 *         - #AJMS_PCS_MODE_BLANKET 
 *         - #AJMS_PCS_MODE_BLANKET_GRANTED
 *         .
 * @retval #AJMS_MSS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_MSS_ERR_INVALID_PARAM
 *         if <i>suiteId</i> or <i>groupId</i> is invalid.
 * @retval #AJMS_MSS_ERR_GROUP_IS_ALLOWED
 *         if the permission level is {@link #AJMS_PCS_STATE_ALLOWED Allowed}, not {@link #AJMS_PCS_STATE_USER User}.
 * @retval #AJMS_MSS_ERR_IO
 *         if an I/O error occurs.
 * @retval #AJMS_MSS_ERR_INTERNAL
 *         if the function fails for any other reason.
 */
AJ_S32 ajms_mss_getGroupMode( const AJ_S32  suiteId, 
                              const AJ_S32  groupId,
                                    AJ_S32 *mode );

/**
 *        Sets the user interaction mode of a function group.
 * @param suiteId
 *        The identifier of the application.
 * @param groupId
 *        The function group index. 
 *        The value should be between 0 and the return value of ajms_pcs_getGroupCount() minus 1.
 * @param mode
 *        The new user interaction mode setting. 
 *        Pass one of the following values:
 *         - #AJMS_PCS_MODE_NO
 *         - #AJMS_PCS_MODE_ONESHOT
 *         - #AJMS_PCS_MODE_SESSION
 *         - #AJMS_PCS_MODE_BLANKET
 *         - #AJMS_PCS_MODE_BLANKET_GRANTED 
 * @param info
 *        A pointer to an #AJMS_DomainRestriction structure for receiving the restriction information when this function returns
 *        #AJMS_MSS_ERR_CONFLICT_ALERT or #AJMS_MSS_ERR_CONFLICT_EXCLUSIVE.
 *        The pointer type members in the structure remain valid until the next time an ACI function is called. 
 *
 * @retval #AJMS_MSS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_MSS_ERR_INVALID_PARAM
 *          if the function fails for one of the following reasons.
 *          - The <i>suiteId</i> parameter is invalid.
 *          - The <i>groupId</i> parameter is invalid.
 *          - The <i>mode</i> parameter is not one of the following values:
 *               - #AJMS_PCS_MODE_NO
 *               - #AJMS_PCS_MODE_ONESHOT
 *               - #AJMS_PCS_MODE_SESSION
 *               - #AJMS_PCS_MODE_BLANKET
 *               - #AJMS_PCS_MODE_BLANKET_GRANTED
 *               .
 *          .
 * @retval #AJMS_MSS_ERR_CONFLICT_ALERT
 *         if the function call triggers an alert level conflict.  
 *         When this value is returned, the caller should show an alert information passed via <i>info</i> to alert user.
 *         Note that the permission setting has been changed even when an alert level conflict happens.
 * @retval #AJMS_MSS_ERR_CONFLICT_EXCLUSIVE
 *         if the function call triggers an exclusive level conflict.
 *         Note that the permission setting has not been changed when an exclusive level conflict happens.
 * @retval #AJMS_MSS_ERR_GROUP_IS_PRIVATE
 *         if the function fails because a private permission function group cannot be changed.
 * @retval #AJMS_MSS_ERR_GROUP_IS_ALLOWED
 *         if the function fails because an Allowed permission level setting cannot be changed.
 * @retval #AJMS_MSS_ERR_IO
 *         if the function fails due to an I/O error.
 * @retval #AJMS_MSS_ERR_INTERNAL
 *         if the function fails for any other reason.
 */
AJ_S32 ajms_mss_setGroupMode( const AJ_S32 suiteId, 
                              const AJ_S32 groupId, 
                              const AJ_S32 mode,
                              AJMS_DomainRestriction *info );

/** @} */ 

#ifdef __cplusplus
}
#endif 

#endif /* AJMS_MSS_HEADER */
