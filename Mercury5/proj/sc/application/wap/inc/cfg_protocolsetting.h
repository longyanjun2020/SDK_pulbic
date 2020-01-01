
/**
 * @file
 * Protocol setting config interfaces.
 */


#ifndef __CVS_CFG_PROTOCOLSETTING_H__
#define __CVS_CFG_PROTOCOLSETTING_H__

#include <cfg_internal.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Get total net setting items number from browser running config.
 * \param   pBrowserConfig Pointer to Browser running config structure.
 * \return  total number of favorte items.
 */
int32_t cfg_getNetSettingCount(T_BROWSERCONFIG *pBrowserConfig);

int32_t cfg_getCurNetSetting(T_BROWSERCONFIG *pBrowserConfig);

int32_t cfg_setCurNetSetting(T_BROWSERCONFIG *pBrowserConfig, int32_t index);

/**
 * Get one net setting according to the index given from browser running config
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   index           Index of net setting array
 * \param   pConnectMode    Pointer to connect mode
 * \param   ppProxyServer   Pointer to pointer to the string which describes proxy server.
 * \param   pPort           Pointer to port number.
 * \param   ppHomepage      Pointer to pointer to homepage of the net setting.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 *
 * \attention   Here ppProxyServer and ppHomepage is used to point to the address, don't give address of an array.
 */
int32_t cfg_getNetSetting(T_BROWSERCONFIG *pBrowserConfig,
                              int32_t index,
                              int8_t **ppProfileName,
                              E_CONN_MODE *pConnectMode,
                              int8_t **ppProxyServer,
                              int32_t *pPort,
                              int8_t **ppHomepage,
                              int8_t **ppApn,
                          	  int8_t **ppUserName,
                          	  int8_t **ppPass);

/**
 * Add one net setting into browser running config
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   connectMode     connect mode
 * \param   pProxyServer    Pointer to the string which describes proxy server.
 * \param   iPort           port number.
 * \param   pHomepage       Pointer to homepage of the net setting.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_addNetSetting(T_BROWSERCONFIG *pBrowserConfig,
                          int8_t *pProfileName,
                          E_CONN_MODE connectMode,
                          int8_t *pProxyServer,
                          int32_t iPort,
                          int8_t *pHomepage,
                          int8_t *pApn,
                          int8_t *pUserName,
                          int8_t *pPass);

/**
 * Change one net setting in browser running config
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   index           Index of net setting array
 * \param   connectMode     connect mode
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_changeNetSetting(T_BROWSERCONFIG *pBrowserConfig,
                             int32_t index,
                             int8_t *pProfileName,
                             E_CONN_MODE connectMode,
                             int8_t *pProxyServer,
                             int32_t iPort,
                             int8_t *pHomepage,
                             int8_t *pApn,
                             int8_t *pUserName,
                          	 int8_t *pPass);


int32_t cfg_changeHomepage(T_BROWSERCONFIG *pBrowserConfig, int32_t index, int8_t *pHomepage);

 /**
 * Delete one net setting into browser running config
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   index           Index of net setting array
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_deleteNetSetting(T_BROWSERCONFIG *pBrowserConfig,
                              int32_t index);

 /**
 * Get current proxy and port
 * \param   connectMode     connect mode
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   ppProxy         Pointer to pointer to proxy server
 * \param   iPort           Pointer to port number.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_getNetSettingProxyPort(E_CONN_MODE connectMode,
                                       T_BROWSERCONFIG *pBrowserConfig,
                                       int8_t **ppProxy,
                                       int32_t *pPort);

/**
 * Get current proxy and port
 * \param   connectMode     connect mode
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   ppProxy         Pointer to proxy server
 * \param   iPort           Port number.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_setNetSettingProxyPort(E_CONN_MODE connectMode,
                                       T_BROWSERCONFIG *pBrowserConfig,
                                       int8_t *ppProxy,
                                       int32_t iPort);

/**
 * Set certain protocol name-value headers and
 * change a long sring seperate with "\r\n" into name and value string alone
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   type            Protocol type
 * \param   flag            Flag to check the current header
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_setProtocolHeaderString(T_BROWSERCONFIG *pBrowserConfig,
                                    E_CONN_MODE type,
                                    int8_t *pHeader,
                                    int32_t flag);
/**
 * Get certain protocol name-value headers and.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   type            Enumerable type for protocol type, eg. HTTP.
 * \param   ppHeader        Address of input protocol headers buffer.
 * \param   maxlen          Address of Input buffer size.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_getProtocolHeaderstring(T_BROWSERCONFIG *pBrowserConfig,
                                    E_CONN_MODE type,
                                    int8_t **ppHeader,
                                    int32_t *maxlen);

/**
 * Get current net mode.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 */
E_CONN_MODE cfg_getNetMode(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Get current homepage.
 */
int8_t *cfg_getCurHomepage();

/**
 * Get certain protocol header name-value pairs total number.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   type            Protocol type
 * \return  name-value pairs total number
 */
int32_t cfg_getProtocolHeadersCount(T_BROWSERCONFIG *pBrowserConfig, E_CONN_MODE type);

/**
 * Get one name-value of certain protocol headers .
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   type            Protocol type.
 * \param   index           Index of protocol header array.
 * \param   ppName          Pointer to pointer to the name of a name-value pair.
 * \param   ppValue         Pointer to pointer to the value of a name-value pair.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 * \attention   Index is for a name-value pair, not just for name or value.
 */
int32_t cfg_getProtocolHeaderNameValue(T_BROWSERCONFIG *pBrowserConfig,
                                           E_CONN_MODE type,
                                           int32_t index,
                                           int8_t **ppName,
                                           int8_t **ppValue
                                           );

/**
 * Change one name-value of certain protocol headers.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   type            Protocol type
 * \param   index           Index of protocol header array.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_changeProtocolHeaderNameValue(T_BROWSERCONFIG *pBrowserConfig,
                                              E_CONN_MODE type,
                                              int32_t index,
                                              int8_t *value);
/**
 * Add one name-value of certain protocol headers.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   type            Protocol type
 * \param   pValue          Input string as value of a name-value pair.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_addProtocolHeaderNameValue(T_BROWSERCONFIG *pBrowserConfig,
                                           E_CONN_MODE type,
                                           int8_t* pName,
                                           int8_t *pValue);

/**
 * Delete one name-value pair of certain protocol headers.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   type            Protocol type
 * \param   index           Index of protocol header array.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 * \attention   Index is for a name-value pair, not just for name or value.
 */
int32_t cfg_deleteProtocolHeaderNameValue(T_BROWSERCONFIG *pBrowserConfig,
                                              E_CONN_MODE type,
                                              int32_t index);

/**
 * Free all protocol setting items including net setting in browser running config.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 */
void cfg_freeProtocolSetting(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Free all net setting items in browser running config.
 *
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 */
void cfg_freeNetSetting(T_BROWSERCONFIG *pBrowserConfig);

#ifdef __cplusplus
}
#endif

#endif
