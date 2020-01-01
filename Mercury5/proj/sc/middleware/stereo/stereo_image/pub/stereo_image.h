#ifndef STEREO_IMAGE_H
#define STEREO_IMAGE_H

#define HORIZONTAL_STEP 32
#define VERTICAL_STEP 32

extern unsigned char *rgbBuf;
extern unsigned char *rgbBufL;
extern unsigned char *rgbBufR;
extern unsigned char *rgbBufAll;

extern unsigned char *rgbMaxBuf;
extern unsigned char *rgbMinBuf;

extern unsigned char *depthBlkMap;
extern unsigned char *depthBlkMap_p;

extern unsigned char *depthBlkMapSmooth;
extern unsigned char *depthBlkMapSmooth_p;

extern short *biasMap;
extern short *MCDiWMap;

//int BufInit(const int width, const int height);
//void BufFree(void);

void StatusDetection(const int frameIdx, const int width, const int height);
void DepthDetection(const int width, const int height);
void DepthGeneration(const int width, const int height);
void RenderLR(const int width, const int height);
void OverlayLR(const int width, const int height, unsigned char *BufL, unsigned char *BufR, unsigned char *BufAll);
void OverlayLR_Dubois_Anaglyph(const int width, const int height, unsigned char *BufL, unsigned char *BufR, unsigned char *BufAll);
void OverlayLR_Dubois_Anaglyph_reduced(const int width, const int height, unsigned char *BufL, unsigned char *BufR, unsigned char *BufAll);
void Render_Overlay_Dubois_Anaglyph_reduced_angle_0(const int buf_width, const int width, const int height, const int stride_u16, unsigned short *BufRGB565);
void Render_Overlay_Dubois_Anaglyph_reduced_angle_90(const int buf_width, const int width, const int height, const int stride_u16, unsigned short *BufRGB565);
void Render_Overlay_Dubois_Anaglyph_reduced_angle_180(const int buf_width, const int width, const int height, const int stride_u16, unsigned short *BufRGB565);
void Render_Overlay_Dubois_Anaglyph_reduced_angle_270(const int buf_width, const int width, const int height, const int stride_u16, unsigned short *BufRGB565);
#endif //STEREO_IMAGE_H

