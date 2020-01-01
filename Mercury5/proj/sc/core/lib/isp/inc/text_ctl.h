#ifndef _TEXT_CTL_H
#define _TEXT_CTL_H

#include "isp_if.h"

#ifndef ON
#define ON  1
#endif
#ifndef OFF
#define OFF  0
#endif


// enable draw text feature
#define DRAW_TEXT_FEATURE_EN		OFF//ON



#if DRAW_TEXT_FEATURE_EN==ON


#define DRAW_TEXT_BUF_LEN			256

extern ISP_UINT8 gDrawTextEn;
extern char gDrawTextBuf[DRAW_TEXT_BUF_LEN];


// print string interface
void VR_PrintString(	ISP_INT8* txt_buf,			// text buffer
						ISP_UINT16 txt_v_offset,	// vertical offset
						ISP_UINT16 txt_h_offset,	// horizontal offset
						ISP_UINT16 txt_front_color,	// txt front color		// in RGB565
						ISP_UINT16 txt_back_color);	// txt background color	// in RGB565


void PrintString1BytePixel(	ISP_UINT8 *dest_buf,	//image buffer
							ISP_UINT32 line_width,	//pixel per line
							ISP_UINT32 offset,		//string offset in text line
							ISP_UINT8 front_color,
							ISP_UINT8 back_color,
							ISP_UINT8 txt_interval,	//interval between text in pixel
							ISP_INT8* text	);

void PrintString2BytePixel(	ISP_UINT16 *dest_buf,	//image buffer
							ISP_UINT32 line_width,	//pixel per line
							ISP_UINT32 offset,		//string offset in text line
							ISP_UINT16 front_color,
							ISP_UINT16 back_color,
							ISP_UINT8 txt_interval,	//interval between text in pixel
							ISP_INT8* text	);

void PrintString4BytePixel(	ISP_UINT32 *dest_buf,	//image buffer
							ISP_UINT32 line_width,	//pixel per line
							ISP_UINT32 offset,		//string offset in text line
							ISP_UINT32 front_color,
							ISP_UINT32 back_color,
							ISP_UINT8 txt_interval,	//interval between text in pixel
							ISP_INT8* text	);

void PrintStringYuv422(		ISP_UINT16 *dest_buf,	//image buffer
							ISP_UINT32 line_width,	//pixel per line
							ISP_UINT32 offset,		//string offset in text line
							ISP_UINT16 front_color,
							ISP_UINT16 back_color,
							ISP_UINT8 txt_interval,	//interval between text in pixel
							ISP_INT8* text	);

ISP_INT8* _strcpy(ISP_INT8* dest, ISP_INT8* src);
ISP_INT32 _strlen(ISP_INT8* str);
ISP_INT8* _strcat(ISP_INT8* dest, ISP_INT8* src);
ISP_INT8* itohs(ISP_UINT32 val, ISP_INT8* buf);
ISP_INT8* ui_to_ds(ISP_UINT32 val, ISP_INT8* buf);
ISP_INT8* i_to_ds(ISP_INT32 val, ISP_INT8* buf);
ISP_INT32 _sprintf(ISP_INT8* buf, ISP_INT8* fmt,...);

#endif // DRAW_TEXT_FEATURE_EN

#endif // _TEXT_CTL_H
