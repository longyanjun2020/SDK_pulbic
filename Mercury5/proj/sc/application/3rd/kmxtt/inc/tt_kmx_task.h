/* tt_kmx_task.h */

#ifdef __MMI_KMX_TT__


#include "ven_graphics.h"  /* graphics */
#include "ven_codec.h"


#include "kapi.h"

//#define		E_VEN_KMX_TT  E_VEN_DEFAULT

#define __SUBSCRIBE_KEYPAD__  0 /* Enable this to subscribe keypad event */
#define __SUBSCRIBE_TOUCH__   0 /* Enable this to subscribe touch event */

enum
{
	KMXTT_SUCCESS,
	KMXTT_ERROR
};

typedef struct  
{
    s32 hCodec;                                //ImgCodec handle
    ven_GraphicsBitmap* pBmp;                  //Bitmap handle
    ven_codec_imgInfo_t imgInfo;               // Image info
    ven_GraphicBitmapInfo_t bmpInfo;           // Bitmap info
    ven_codec_decode_param_t decParam;         // Decode parameter
    s32 xPos;                                  // x position to bitblt decoded image
    s32 yPos;                                  // y position to bitblt decoded image

}ImgCodec_t;

//Text Input 
enum{
    AP_TT_EDITOR,
};

typedef struct
{
    u8 APType;
    u32 title_data;
    u32 init_data;
}kmx_tt_cb_data_t;

/*   api   mode*/
typedef enum
{
    KMX_TT_API_START = 0,
    KMX_TT_API_SEND_PICTURE,
    KMX_TT_API_SEND_PHOTO,
    KMX_TT_API_END
}KMX_TT_API_ENUM;


/* Function prototyes */





#endif //__MMI_KMX_TT__ 

