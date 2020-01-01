
#ifndef  __IFLAYER_DLIMG_H__
#define  __IFLAYER_DLIMG_H__

#include <ncc_types.h>

/** defining relayout frequency*/
#define DB_RELAYOUT_AFTER_IMAGES 10

/*IMG params*/
#define DB_MAX_AIMAGESIZE   (250 * 1024)//(600*1024)   /* max size support */
#define DB_MIN_AIMAGESIZE   0           /* min size support */
#define DB_MAXIMAGEWIDTH    1024        /* max width support */
#define DB_MAXIMAGEHEIGHT   768         /* max height support */
#define DB_MAXIMGINPAGE     80          /* max sum of images in one page */

/**
 * query to download image
 *   \return
 */
void fnDB_DLCheckImg(void);

/**
*  if the image is valid
*   \param  imagetype       type of image
*   \param  imgbuf          buffer of image
*   \param  imagesize       size of image
*   \return success or fail
*/
int32_t fnDB_DLCheckImageValid(int32_t imagetype,uint8_t * p,int32_t imagesize);

/**
*  get width and height of image
*   \param  buf     buffer of image
*   \param  type    type og image
*   \param  width   width pointer of image
*   \param  height  height pointer of image
*   \return success or fail
*/
int32_t fnDB_DLGetImageSize(int8_t * buf, int32_t type, int16_t * width,int16_t * height);

/**
* get image type from buffer
*   \param  buf     buffer pointer of image
*   \return type of image
*/
int32_t fnDB_DLGetImgType(uint8_t * buf);

#endif
