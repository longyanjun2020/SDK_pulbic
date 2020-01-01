/*
 *
 *	V 4 L 2   D R I V E R   H E L P E R   A P I
 *
 * Moved from videodev2.h
 *
 *	Some commonly needed functions for drivers (v4l2-common.o module)
 */
#ifndef _V4L2_DEV_H
#define _V4L2_DEV_H

#include "AIT4Linux.h"
#include "videodev2.h"

/*
 * Newer version of video_device, handled by videodev2.c
 * 	This version moves redundant code from video device code to
 *	the common handler
 */

struct video_device
{
	/* device ops */
	const struct v4l2_file_operations *fops;
	/* callbacks */ 
	void (*release)(struct video_device *vdev);

	/* ioctl callbacks */
	const struct v4l2_ioctl_ops *ioctl_ops;

	/* 'minor' is set to -1 if the registration failed */
	int minor;
	u16 num;

	/* use bitops to set/clear/test flags */
	unsigned long flags;
	/* attribute to differentiate multiple indices on one physical device */
	int index;

	/* Video standard vars */
	v4l2_std_id tvnorms;		/* Supported tv norms */
	v4l2_std_id current_norm;	/* Current tvnorm */

};
#endif /* _V4L2_DEV_H */
