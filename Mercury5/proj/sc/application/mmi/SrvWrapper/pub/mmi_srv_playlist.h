/**
* @file     mmi_srv_playlist.h
* @brief    This service is to provide the interface to manipulate playlist, included of creating, loading, moving, deleting and listing.
*           Every element inside the playlist is indicated the place of the media file. Currently, this service only supports music file,
*           so the playlist file is formed as .m3u. In addition, the playlist file can only be created via the service. It's not allowed
*           to import from existed or any outside playlist file. All of operation will be consistent with the playlist file. Hence, it's
*           not necessary to restore the playlist content to its corresponding file.
*/

#ifndef __MMI_SRV_PLAYLIST_H__
#define __MMI_SRV_PLAYLIST_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_playlistsrv.h"

/** SrvPlaylistListPlaylists
* @brief         Request to list all file names of the playlists (.m3u or .v3u) in the specified folder.
*                [Note] The ppIVectorClass will be created in service so it's necessary to call VectorRelease to release it by AP self.
*
* @param[in]     pWStrDirPath              The path of the M3U folder. For example, L"fs:/CARD/My Playlist/".
* @param[out]    ppIVectorClass            The pointer to the memory which is used to fill with the pointer of the vector class being kept the M3U filenames in the specific folder.
* @param[in]     eRetrievedPlaylistType    The playlist type we want to list.
*                                          MUSIC_PLAYLIST_TYPE    The music type (.m3u).
*                                          VIDEO_PLAYLIST_TYPE    The video type (.v3u).
*                                          ALL_PLAYLIST_TYPE      The music or video types (.m3u or .v3u).
* @param[in]     pOwner                    The pointer of the applet.
*
* @retval        MAE_RET_SUCCESS           If it succeeds to request to get the playlist.
* @retval        MAE_RET_FAILED            If it fails to do file manipulation.
*                                          [Note] For file manipulation, except for MAE_RET_FAILED to represent the common failure,
*                                                 there still exists some error codes for the exact causes.
* @retval        MAE_RET_BAD_PARAM         If the service data is NULL or the input parameters are invalid.
* @retval        MAE_RET_OUT_OF_MEMORY     If there's no enough memory to do allocation for service instance or the data pool.
*/ 
MAE_Ret SrvPlaylistListPlaylists(const MAE_WChar *pWStrDirPath,
                                 VectorClass_t **ppIVectorClass,
                                 PLAYLISTSRV_PlaylistType_e eRetrievedPlaylistType,
                                 IBase *pOwner);

/** SrvPlaylistCreatePlaylist
* @brief        Request to create a playlist for music(.m3u).
*               [Note] Currently, this API only supports .m3u.
* 
* @param[in]    pWStrFilePath            The M3U file path to be created. For example, L"fs:/CARD/My Playlist/My music.m3u".
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to get the playlist.
* @retval       MAE_RET_FAILED           If it fails to do file manipulation.
*                                        [Note] For file manipulation, except for MAE_RET_FAILED to represent the common failure,
*                                               there still exists some error codes for the exact causes.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the input file path is NULL.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance or the data pool.
* @retval       MAE_RET_FILE_EXISTS      If the input file has existed.
* @retval       MMI_RET_OVERCAPACITY     If the number of playlist files at the specific directory exceeds PLAYLISTSRV_MAX_PALYLISTS_NUM(=100).
*/
MAE_Ret SrvPlaylistCreatePlaylist(const MAE_WChar *pWStrFilePath);

/** SrvPlaylistDeletePlaylist
* @brief        Request to delete the specified playlist.
*
* @param[in]    pWStrFilePath            The file path of the playlist which will be deleted. For example, L"fs:/CARD/My Playlist/My music.m3u".
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to delete the playlist.
* @retval       MAE_RET_FAILED           If it fails to do file manipulation.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the input file path is NULL.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvPlaylistDeletePlaylist(MAE_WChar *pWStrFilePath);

/** SrvPlaylistRenamePlaylist
* @brief        Request to rename the playlist file.
*
* @param[in]    pWStrSrcFilePath         The source playlist file path. For example, L"fs:/CARD/My Playlist/My music.m3u".
* @param[in]    pWStrDestFileName        The destnation playlist filename. For example, L"My music2.m3u".
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to rename the playlist file.
* @retval       MAE_RET_FAILED           If it fails to rename the file.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the input file name/path is NULL.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_FOUND        If the source file doesn't exist.
*/
MAE_Ret SrvPlaylistRenamePlaylist(const MAE_WChar *pWStrSrcFilePath, const MAE_WChar *pWStrDestFileName);

/** SrvPlaylistGetM3UElementInfo
* @brief         Request to load the M3U element from the input playlist content.
* 
* @param[in]     pWStrFilePath            The file path of the playlist. For example, L"fs:/CARD/My Playlist/My music.m3u".
*                                         [Note] Currently, this parameter is useless. The loaded element must be from the loaded content not the specific file.
* @param[in]     pIDataModel              Pointer to the memory to fill with the pointer to the array model (the content of the play list).
* @param[in]     nContentIdx              The index of the playlist element.
* @param[out]    pM3UElement              The pool which is used to store the M3U element information.
*                                         [Note] The spaces for pTitle and pPath are both allocated inside the service, so it's necessary to release them by the caller.
*
* @retval        MAE_RET_SUCCESS          If it succeeds to request to load the M3U element.
* @retval        MAE_RET_FAILED           If it fails to load the specific element from the implied file retrieved from the input data model.
* @retval        MAE_RET_BAD_PARAM        If the service data is NULL or pIDataModel/pM3UElement is NULL. Also, if the input index exceeds the number of elements.
* @retval        MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance or the data pool.
*/
MAE_Ret SrvPlaylistGetM3UElementInfo(const MAE_WChar *pWStrFilePath,
                                     IDataModel *pIDataModel,
                                     u32 nContentIdx,
                                     PLAYLISTSRV_M3UElement_t *pM3UElement);

/** SrvPlaylistGetPlaylistSize
* @brief         Request to get the number of elements in the input playlist content.
*
* @param[in]     pIDataModel              Pointer to the memory to fill with the pointer to the array model (the content of the play list).
* @param[out]    pPlaylistSize            Point to the number of elements in the playlist.
*
* @retval        MAE_RET_SUCCESS          If it succeeds to request to get the number of the elements.
* @retval        MAE_RET_FAILED           If it fails to retrieve the data from the input data model.
* @retval        MAE_RET_BAD_PARAM        If the service data is NULL or pIDataModel/pPlaylistSize is NULL.
* @retval        MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance or the data pool.
*/
MAE_Ret SrvPlaylistGetPlaylistSize(IDataModel *pIDataModel, u32 *pPlaylistSize);

/** SrvPlaylistDeletePlaylistContent
* @brief        Request to delete the specific element from the input playlist content.
*
* @param[in]    pIDataModel                           Pointer to the memory to fill with the pointer to the array model (the content of the play list).
* @param[in]    nContentIdx                           The index of the playlist element.
* @param[in]    pOwner                                The pointer of the applet.
* @param[in]    pfnCb                                 The callback function which will be called to notify the success(PLAYLISTSRV_REQUEST_SUCCESS) or 
*                                                     failure to delete the specific element.
*
* @retval       MAE_RET_SUCCESS                       If it succeeds to request to delete the specific element.
* @retval       MAE_RET_BUSY                          If the service is at idle state which can't provide the manipulation for playlist.
* @retval       MAE_RET_FAILED                        If it fails to retrieve the data from the input data model.
* @retval       MAE_RET_BAD_PARAM                     If the service data is NULL or pIDataModel/pOwner is NULL.
* @retval       MAE_RET_OUT_OF_MEMORY                 If there's no enough memory to do allocation for service instance or the data pool.
* @retval       MAE_RET_ERROR_GET_FILE_INFORMATION    If it fails to get the information the implied file retrieved from the input data model.
*/
MAE_Ret SrvPlaylistDeletePlaylistContent(IDataModel *pIDataModel,
                                         u32 nContentIdx,
                                         IBase *pOwner,
                                         PlaylistSrvCmnCB pfnCb);

/** SrvPlaylistMovePlayListContent
* @brief        Request to move the specific element to the target position from the input playlist content.
*
* @param[in]    pIDataModel                           Pointer to the memory to fill with the pointer to the array model (the content of the play list).
* @param[in]    nFromContentIdx                       The index of the source playlist element.
* @param[in]    nToContentIdx                         The index of the target position to store the source playlist element.
* @param[in]    pOwner                                The pointer of the applet.
* @param[in]    pfnCb                                 The callback function which will be called to notify the success(PLAYLISTSRV_REQUEST_SUCCESS) or 
*                                                     failure to move the specific element.
*
* @retval       MAE_RET_SUCCESS                       If it succeeds to request to move the specific element.
* @retval       MAE_RET_BUSY                          If the service is at idle state which can't provide the manipulation for playlist.
* @retval       MAE_RET_FAILED                        If it fails to retrieve the data from the input data model.
* @retval       MAE_RET_BAD_PARAM                     If the service data is NULL or pIDataModel/pOwner is NULL.
* @retval       MAE_RET_NOT_SUPPORTED                 If nFromContentIdx equals nToContentIdx.
* @retval       MAE_RET_OUT_OF_MEMORY                 If there's no enough memory to do allocation for service instance or the data pool.
* @retval       MAE_RET_ERROR_GET_FILE_INFORMATION    If it fails to get the information the implied file retrieved from the input data model.
*/
MAE_Ret SrvPlaylistMovePlayListContent(IDataModel *pIDataModel,
                                       u32 nFromContentIdx,
                                       u32 nToContentIdx,
                                       IBase *pOwner,
                                       PlaylistSrvCmnCB pfnCb);

/** SrvPlaylistAppendContentToPlayList
* @brief        Request to append the selected files (eg. mp3 files) to the playlist content.
*
* @param[in]    pIDataModel              Pointer to the memory to fill with the pointer to the array model (the content of the play list).
* @param[in]    nFileMgrHdlId            The handle to keep the information of the marked files which will be added into playlist.
* @param[in]    uFileNum                 The number of marked files.
* @param[in]    nListType                The type of the playlist content.
*                                        PLAYLISTSRV_LIST_TYPE__DEFAULT         The number of elements inside the playlist is limited as 1000.
*                                        PLAYLISTSRV_LIST_TYPE__USER_CREATED    The number of elements inside the playlist is limited as 300.
* @param[in]    pOwner                   The pointer of the applet.
* @param[in]    pfnCb                    The callback function which will be called to notify the success(PLAYLISTSRV_REQUEST_SUCCESS) or 
*                                        failure to append the specific selected files to the playlist. Also, the updated data model will be carried together.
*                                        [Note] The carried data model will be created in service so it's necessary to call RELEASEIF to release it by AP self.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to append the selected files to the playlist.
* @retval       MAE_RET_BUSY             If the service is at idle state which can't provide the manipulation for playlist.
* @retval       MAE_RET_FAILED           If it fails to retrieve the data from the input data model.
*                                        [Note] For file manipulation, except for MAE_RET_FAILED to represent the common failure,
*                                               there still exists some error codes for the exact causes.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or one of the input parameters is invalid.
* @retval       MAE_RET_NOT_SUPPORTED    If the encoding type inside the playlist content is not UCS2. Also, if the list type is user-created and the number of
*                                        updated elements exceeds 300.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance or the data pool.
* @retval       MAE_RET_VOLUME_FULL      If the card space is full.
*/
MAE_Ret SrvPlaylistAppendContentToPlayList(IDataModel *pIDataModel,
                                           u32 nFileMgrHdlId,
                                           u32 uFileNum,
                                           PLAYLISTSRV_ListType_e nListType,
                                           IBase *pOwner,
                                           PlaylistSrvLoadPlaylistDataCB pfnCb);

/** SrvPlaylistLoadPlaylistContent
* @brief        Request to load the content of the specific playlist.
*
* @param[in]    pWStrFilePath            The file path of the playlist which will be loaded. For example, L"fs:/CARD/My Playlist/My music.m3u".
* @param[in]    nListType                The type of the playlist content.
*                                        PLAYLISTSRV_LIST_TYPE__DEFAULT         The number of elements inside the playlist is limited as 1000.
*                                        PLAYLISTSRV_LIST_TYPE__USER_CREATED    The number of elements inside the playlist is limited as 300.
* @param[in]    pOwner                   The pointer of the applet.
* @param[in]    pfnCb                    The callback function which will be called to notify the success(PLAYLISTSRV_REQUEST_SUCCESS) or 
*                                        failure to load content form the playlist. Also, the data model will be carried together.
*                                        [Note] The carried data model will be created in service so it's necessary to call RELEASEIF to release it by AP self.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to load the content.
* @retval       MAE_RET_BUSY             If the service is at idle state which can't provide the manipulation for playlist.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or one of the input parameters is invalid.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance or the data pool.
*/
MAE_Ret SrvPlaylistLoadPlaylistContent(const MAE_WChar *pWStrFilePath,
                                       PLAYLISTSRV_ListType_e nListType,
                                       IBase *pOwner,
                                       PlaylistSrvLoadPlaylistDataCB pfnCb);

/** SrvPlaylistCancelOperation
* @brief     Request to cancel the operations invoked by SrvPlaylistDeletePlaylistContent, SrvPlaylistMovePlayListContent, SrvPlaylistAppendContentToPlayList
*            or SrvPlaylistLoadPlaylistContent.
*
* @retval    MAE_RET_SUCCESS          If it succeeds to cancel the operations.
* @retval    MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvPlaylistCancelOperation(void);

/** SrvPlaylistLoadLastPlaybackContent
* @brief         Request to load the last playback content, included of the playlist file, song and its index.
*                [Note] This API is usually used when being powered on and the music player service needs to load the last playback content.
*
* @param[in]     pOwner                   The pointer of the applet.
* @param[out]    pPlaybackInfo            The playback content.
*                                         strLastPlaylistPath     The playlist path which the last playing music is stored at.
*                                         strLastPlaySongPath     The path of the Last playing song.
*                                                                 [Note] Currently, this field is useless.
*                                         nLastStoredIdx          The last playing index or last playing content ID. nLastStoredIdx will be valid if the playlist is user-defined.
*                                         bIsPredefinedList       It indicates if the playlist is predefined (L"My music").
* @param[in]     pfnCb                    The callback function which will be called to notify the success(PLAYLISTSRV_REQUEST_SUCCESS) or 
*                                         failure to load the last playback content. Also, the data model will be carried together.
*                                         [Note] The carried data model will be created in service so it's necessary to call RELEASEIF to release it by AP self.
*
* @retval        MAE_RET_SUCCESS          If it succeeds to request to load the last playback content.
* @retval        MAE_RET_FAILED           If it fails to retrieve the data by the file manipulation.
*                                         [Note] For file manipulation, except for MAE_RET_FAILED to represent the common failure,
*                                                there still exists some error codes for the exact causes.
* @retval        MAE_RET_BAD_PARAM        If the service data is NULL or one of the input parameters is invalid.
* @retval        MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance or the data pool.
*/
MAE_Ret SrvPlaylistLoadLastPlaybackContent(IBase *pOwner, PLAYLISTSRV_Playback_Info_t *pPlaybackInfo, PlaylistSrvLoadPlaylistDataCB pfnCb);

/** SrvPlaylistStoreLastPlaybackContent
* @brief        Request to store last playback content to a system file (L"_sysLastPlay.sys") in SD card
*
* @param[in]    pIDataModel              Pointer to the memory to fill with the pointer to the array model (the content of the play list).
* @param[in]    nPlayingIdx              The last playing index or last playing content ID.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to store the last playback content.
* @retval       MAE_RET_FAILED           If it fails to retrieve the data by the file manipulation.
*                                        [Note] For file manipulation, except for MAE_RET_FAILED to represent the common failure,
*                                               there still exists some error codes for the exact causes.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or one of the input parameters is invalid.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance or the data pool.
*/
MAE_Ret SrvPlaylistStoreLastPlaybackContent(IDataModel *pIDataModel, u32 nPlayingIdx);

/** SrvPlaylistClearLastPlaybackContent
* @brief     Request to clear the last playback content.
*            [Note] This API is usually used when some error of the playback occurs.
*
* @retval    MAE_RET_SUCCESS          If it succeeds to request to clear the last playback content.
* @retval    MAE_RET_FAILED           If it fails to retrieve the data by the file manipulation.
*                                     [Note] For file manipulation, except for MAE_RET_FAILED to represent the common failure,
*                                            there still exists some error codes for the exact causes.
* @retval    MAE_RET_BAD_PARAM        If the service data is NULL.
* @retval    MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance or the data pool.
* @retval    MAE_RET_FS_ERROR         If it fails to write the reset data into the system file.
*/
MAE_Ret SrvPlaylistClearLastPlaybackContent(void);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_PLAYLIST_H__
