
/* -- DO NOT MODIFY ---- DO NOT MODIFY ----------- O NOT MODIFY ---------- DO NOT MODIFY DIFY -------------- */
/* -- DO NOT MODIFY ----- DO NOT MODIFY --------- O NOT MODIFY ---------- DO NOT MODIFY MODIFY ------------- */
/* -- DO NOT MODIFY ------ DO NOT MODIFY ------- O NOT MODIFY ---------- DO NOT MODIFY T MODIFY ------------ */
/* -- DO NOT MODIFY ------- DO NOT MODIFY ----- O NOT MODIFY ---------- DO NOT MODIFY NOT MODIFY ----------- */
/* -- DO NOT MODIFY -------- DO NOT MODIFY --- O NOT MODIFY ---------- DO NOT MODIFY O NOT MODIFY ---------- */
/* -- DO NOT MODIFY --------- DO NOT MODIFY - O NOT MODIFY ---------- DO NOT MODIFY - DO NOT MODIFY -------- */
/* -- DO NOT MODIFY ---------- DO NOT MODIFY O NOT MODIFY ---------- DO NOT MODIFY --- DO NOT MODIFY ------- */
/* -- DO NOT MODIFY ----------- DO NOT MODIFY NOT MODIFY ---------- DO NOT MODIFY ----- DO NOT MODIFY ------ */
/* -- DO NOT MODIFY ------------ DO NOT MODIFY T MODIFY ---------- DO NOT MODIFY --DONT- DO NOT MODIFY ----- */
/* -- DO NOT MODIFY ------------- DO NOT MODIFY MODIFY ---------- DO NOT MODIFY --------- DO NOT MODIFY ---- */
/* -- DO NOT MODIFY -------------- DO NOT MODIFY DIFY ---------- DO NOT MODIFY ----------- DO NOT MODIFY --- */
/* -- DO NOT MODIFY --------------- DO NOT MODIFY ------------- DO NOT MODIFY ------------- DO NOT MODIFY -- */

#ifndef IIMAGE_H
#define IIMAGE_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _MyPOINT
{
	short x;
	short y;
} MyPOINT;

static __inline MyPOINT point( int x, int y )
{
    MyPOINT p;

    p.x = x;
    p.y = y;

    return p;
}

typedef struct _IIMAGE
{
	int  depth;             /* Pixel depth in bytes: 1~4 byte                   */
    int  width;             /* Image width in pixels.                           */
    int  height;            /* Image height in pixels.                          */
    int  widthOrigin;       /* Image width in pixels.                           */
    int  heightOrigin;      /* Image height in pixels.                          */
    int  imageSize;         /* Image data size in bytes                         */
    int  widthStep;                  /* Size of aligned image row in bytes.     */
    unsigned char *imageData;        /* Pointer to aligned image data with ROI  */
    unsigned char *imageDataOrigin;  /* Pointer to origin image data without ROI*/
} IIMAGE;


extern IIMAGE *iCreateImage(int width, int height, int depth);
extern int iAllocateImage(IIMAGE* image, int width, int height, int depth);
extern int NewiAllocateImage(IIMAGE* image, int width, int height, int depth);
extern void iReleaseImage(IIMAGE **image);
extern void iClearImage(IIMAGE *image);
extern void iSetROI(IIMAGE *image,int x,int y,int width,int height);
extern void NewiSetROI(unsigned char *temp_rowone_image, IIMAGE *image,int x,int y,int width,int height);
extern void iResetROI(IIMAGE *image);
extern unsigned int get_IImage_BufSize(int width, int height, int depth);

#ifdef __cplusplus
}
#endif

#endif
