/*
 *
 *	V 4 L 2   D R I V E R   H E L P E R   A P I
 *
 * Moved from videodev2.h
 *
 *	Some commonly needed functions for drivers (v4l2-common.o module)
 */
#ifndef _V4L2_IOCTL_H
#define _V4L2_IOCTL_H

#include "AIT4Linux.h"
#include "videodev2.h"



struct v4l2_ioctl_ops {
	/* ioctl callbacks */

	/* VIDIOC_QUERYCAP handler */
	int (*vidioc_querycap)(struct file *file, void *fh, struct v4l2_capability *cap);///< VIDIOC_QUERYCAP

		/* Input handling */
	int (*vidioc_enum_input)(struct file *file, void *fh, struct v4l2_input *inp);///< VIDIOC_ENUMINPUT
	int (*vidioc_g_input)   (struct file *file, void *fh, int *i);///< VIDIOC_S_INPUT
	int (*vidioc_s_input)   (struct file *file, void *fh, int *i);

    /*  Standard handling
	    ENUMSTD is handled by videodev.c
     */
	int (*vidioc_querystd) (struct file *file, void *fh, v4l2_std_id *a);
	int (*vidioc_g_std) (struct file *file, void *fh, v4l2_std_id *norm);
	int (*vidioc_s_std) (struct file *file, void *fh, v4l2_std_id *norm);///< VIDIOC_S_STD


	/* Crop ioctls */
	int (*vidioc_cropcap) (struct file *file, void *fh, struct v4l2_cropcap *a);//< VIDIOC_CROPCAP
	int (*vidioc_g_crop)  (struct file *file, void *fh, struct v4l2_crop *a);
	int (*vidioc_s_crop)  (struct file *file, void *fh, struct v4l2_crop *a);///< VIDIOC_S_CROP

	
	/* VIDIOC_ENUM_FMT handlers */
	int (*vidioc_enum_fmt_vid_cap)     (struct file *file, void *fh, struct v4l2_fmtdesc *f);
	int (*vidioc_enum_fmt_vid_cap_mplane)(struct file *file, void *fh, struct v4l2_fmtdesc *f);


	/* VIDIOC_G_FMT handlers */
	int (*vidioc_g_fmt_vid_cap)    (struct file *file, void *fh, struct v4l2_format *f);
	int (*vidioc_g_fmt_vid_cap_mplane)(struct file *file, void *fh, struct v4l2_format *f);


	/* VIDIOC_S_FMT handlers */
	int (*vidioc_s_fmt_vid_cap)  (struct file *file, void *fh, struct v4l2_format *f);
	int (*vidioc_s_fmt_vid_cap_mplane)(struct file *file, void *fh, struct v4l2_format *f);
	
    /* VIDIOC_TRY_FMT handlers */
	int (*vidioc_try_fmt_vid_cap)    (struct file *file, void *fh, struct v4l2_format *f);
	int (*vidioc_try_fmt_vid_cap_mplane)(struct file *file, void *fh, struct v4l2_format *f);

	/* Buffer handlers */
	int (*vidioc_reqbufs) (struct file *file, void *fh, struct v4l2_requestbuffers *b);
	int (*vidioc_querybuf)(struct file *file, void *fh, struct v4l2_buffer *b);
	int (*vidioc_qbuf)    (struct file *file, void *fh, int idx);
	int (*vidioc_dqbuf)   (struct file *file, void *fh, struct v4l2_buffer **b);

	int (*vidioc_create_bufs)(struct file *file, void *fh, struct v4l2_create_buffers *b);
	int (*vidioc_prepare_buf)(struct file *file, void *fh, struct v4l2_buffer *b);

	/* Stream on/off */
	int (*vidioc_streamon) (struct file *file, void *fh, enum v4l2_buf_type* i);
	int (*vidioc_streamoff)(struct file *file, void *fh, enum v4l2_buf_type* i);
	/* AIT extension */
	int (*vidioc_bufdone_callback)(struct file *file, void *fh, struct ait_buffer_callback* callback);
	int (*vidioc_s_flowctl)(struct file *file, void *fh, int *i);
//	int (*vidioc_sensor_mode)(struct file *file, void *fh, enum v4l2_buf_type* i);
};

/* Standard handlers for V4L ioctl's */
int video_ioctl2(struct file *file, unsigned int cmd, void* arg);

#endif /* _V4L2_IOCTL_H */
