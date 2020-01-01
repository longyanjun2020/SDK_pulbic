

#ifndef _DRV_HUVC_MEDIA_ENTITY_H_
#define _DRV_HUVC_MEDIA_ENTITY_H_

struct media_pipeline {
};

struct media_link {
	struct media_pad *source;	/* Source pad */
	struct media_pad *sink;		/* Sink pad  */
	struct media_link *reverse;	/* Link in the reverse direction */
	unsigned long flags;		/* Link flags (MEDIA_LNK_FL_*) */
};

struct media_pad {
	struct media_entity *entity;	/* Entity this pad belongs to */
	u16 index;			/* Pad index in the entity pads array */
	unsigned long flags;		/* Pad flags (MEDIA_PAD_FL_*) */
};

struct media_entity_operations {
	int (*link_setup)(struct media_entity *entity,
			  const struct media_pad *local,
			  const struct media_pad *remote, u32 flags);
};

struct media_entity {
	struct list_head list;
	struct media_device *parent;	/* Media device this entity belongs to*/
	u32 id;				/* Entity ID, unique in the parent media
					 * device context */
	const char *name;		/* Entity name */
	u32 type;			/* Entity type (MEDIA_ENT_T_*) */
	u32 revision;			/* Entity revision, driver specific */
	unsigned long flags;		/* Entity flags (MEDIA_ENT_FL_*) */
	u32 group_id;			/* Entity group ID */

	u16 num_pads;			/* Number of sink and source pads */
	u16 num_links;			/* Number of existing links, both
					 * enabled and disabled */
	u16 num_backlinks;		/* Number of backlinks */
	u16 max_links;			/* Maximum number of links */

	struct media_pad *pads;		/* Pads array (num_pads elements) */
	struct media_link *links;	/* Links array (max_links elements)*/

	const struct media_entity_operations *ops;	/* Entity operations */

	/* Reference counts must never be negative, but are signed integers on
	 * purpose: a simple WARN_ON(<0) check can be used to detect reference
	 * count bugs that would make them negative.
	 */
	int stream_count;		/* Stream count for the entity. */
	int use_count;			/* Use count for the entity. */

	struct media_pipeline *pipe;	/* Pipeline this entity belongs to. */

	union {
		/* Node specifications */
		struct {
			u32 major;
			u32 minor;
		} v4l;
		struct {
			u32 major;
			u32 minor;
		} fb;
		struct {
			u32 card;
			u32 device;
			u32 subdevice;
		} alsa;
		int dvb;

		/* Sub-device specifications */
		/* Nothing needed yet */
	};
};


#endif /* _DRV_HUVC_MEDIA_ENTITY_H_ */
