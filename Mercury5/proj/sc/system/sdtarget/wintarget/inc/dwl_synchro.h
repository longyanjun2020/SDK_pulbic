/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Synchronisation with the remote host                         */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef _30748c514e58c294279669651b915644_included_dwl_synchro_h
#define _30748c514e58c294279669651b915644_included_dwl_synchro_h

/****************************************************************************/
/*  Function: dwl_ConnectWithPC                                             */
/*--------------------------------------------------------------------------*/
/*  Scope   : Handshakes with PC                                            */
/*                                                                          */
/*                                                                          */
/*  Return    :  n/a                                                        */
/*                                                                          */
/*  Interface :  n/a                                                        */
/****************************************************************************/
void dwl_ConnectWithPC(void);

/****************************************************************************/
/*  Function: dwl_ResyncWaitComplete                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : Resync with PC and wait complete.txt generate                 */
/*                                                                          */
/*                                                                          */
/*  Return    : bool TRUE ( SUCCESSFUL ) / FALSE ( FAIL )                   */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
bool dwl_ResyncWaitComplete(void);

#endif /* ! _30748c514e58c294279669651b915644_included_dwl_synchro_h   */
