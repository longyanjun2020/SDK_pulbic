#ifndef STEREO_IMAGE_MAIN_H
#define STEREO_IMAGE_MAIN_H

#include "mdl_imgcodec_main.h"
image_Errmsg convert_stereo_image(unsigned short* bufAddr, int width, int height, int stride, Image_RotationAngle rotate_angle);

#endif //STEREO_IMAGE_MAIN_H

