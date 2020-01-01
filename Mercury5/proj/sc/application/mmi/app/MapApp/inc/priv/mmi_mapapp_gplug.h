#ifndef _MMI_MAPAPP_GPLUG_H_
#define _MMI_MAPAPP_GPLUG_H_

/* extern */
#ifdef __cplusplus
extern "C" {
#endif    /* end of #ifdef __cplusplus */

/*
 * 1, wg_flag: 初始化變數標誌
 *             系統在首次調用轉換模組時，wg_flag設置為0，此後設定為1。
 * 2, wg_lng:  GPS信號接收到的WGS84經度。單位是1/1024秒。
 * 3, wg_ lat: GPS信號接收到的WGS84緯度。單位是1/1024秒。
 * 4, wg_heit: 當前位置的高度。單位是公尺。
 * 5, wg_week: 自1980年1月6日零時算起，至當前時間累計的週數，也即GPS週（七天為一週）
 * 6, wg_time: 以GPS週為準，從一週起始時間累積至當前時間的秒數，該值每週清零。單位是1/1000秒。
 *
 * Return:
 * 1, china_lng: 轉換後座標經度，單位是1/1024秒。
 * 2, china_lat: 轉換後座標緯度，單位是1/1024秒。
 *
 * 函數使用說明:
 * 1, 轉換模組接收到異常值，如經度為0，模組將返回錯誤標誌(0xFFFF95FF)，且設置返回的經緯度為0；
 * 2, 若在進行過程中，無法獲得GPS信號，將上一次獲得的GPS真實值傳入轉換模組。
 * 3, 正常結束: 0x00000000。
 */
#if (!defined(__MAP_MMI_GPS_PLUGIN_LIB__))||defined(__PC_SIMULATOR__)
/* if the library doesn't exist, gplug_add() has to be implemented here to do decoding of GPS position. */
unsigned int gplug_add(int wg_flag,unsigned int wg_lng,unsigned int wg_lat,int wg_heit,int wg_week,
                       unsigned int wg_time,unsigned int *china_lng,unsigned int *china_lat)
{
    LOG_TRACE(MMI_LEVEL_MAPVIEW,"[GPLUG - gplug_add] flag=%d, height=%d, week=%d, time=%d, long=d, lat=%d",
                                 wg_flag,wg_heit,wg_week,wg_time,wg_lng,wg_lat);
    (*china_lng)=wg_lng;
    (*china_lat)=wg_lat;
    return 0x00000000;    /* succeed; 0xFFFF95FF -> fail */
}
#else
unsigned int gplug_add(int wg_flag,unsigned int wg_lng,unsigned int wg_lat,int wg_heit,int wg_week,
                       unsigned int wg_time,unsigned int *china_lng,unsigned int *china_lat);
#endif

#ifdef __cplusplus
}
#endif    /* end of #ifdef __cplusplus */

#endif    /* end of #ifndef _MMI_MAPAPP_GPLUG_H_ */
