/*
 * Copyright(c) Faith,Inc.  All Rights Reserved.
 *
 * $Revision: 1.2 $
 */



#ifndef CORE_PRIVATE_FPARSER_IMELODY_H__
#define CORE_PRIVATE_FPARSER_IMELODY_H__

#include "fparser_if.h"
#include "fsystem_source.h"



#define IM_STREAMWINDOWSIZE		1024	
#define IM_NOTE_C0				12		
#define IM_DEFAULT_TONE			0
#define IM_DEFAULT_LED_CTRL		1
#define IM_DEFAULT_VIB_CTRL		1
#define IM_DEFAULT_BACK_CTRL	1

#define IM_MAXVOLUME	15
#define IM_TIMEBASE		504		

#define IM_MAXTOKENLEN	8		
#define IM_N_TOKENS		10		

#define IM_MAXMARKRP	1
#define IM_MAXMARKSTACK	4
#define IM_MELODYBEGIN	(IM_MAXMARKRP)
#define IM_MELODYEND	(IM_MAXMARKRP+1)
#define IM_MELODYSTACK	(IM_MAXMARKRP+2)

#define IMELODY_CH	0
#define IMELODY_DEF_OCTAVE	4
#define IMELODY_DEF_VOLUME	7
#define	IMELODY_DEF_STYLE		0
#define IMELODY_DEF_BEAT		120
#define IMELODY_MIN_BEAT		25
#define IMELODY_MAX_BEAT		900

#define IMELODY_MAXLINE_SIZE	77 

typedef struct {
	struct _fsrc_base_		base_work;
	fsrc_t					fsrc;
	fsrc_base_t				base;

	ftime_t		delta_time;
	ftime_t		rest_time;

	foff_t		melody_offset;

	s_32		loop_count;
	foff_t		loop_offset;

	s_16	status;

	s_16	beat;

	u_8		octave:4;
	u_8		volume:4;

	u_8		style:2;
	u_8		is_loop:1;
	u_8		is_noteoff:1;
	u_8		is_tail:1;
	u_8		linear_vol_flag:1;
	u_8		reserved:2;

	u_8		midi_note;

	u_8			str[ IMELODY_MAXLINE_SIZE + 1 ];

#if 0
	u_8			title[ IMELODY_MAXLINE_SIZE + 1 ];
	u_8			title_len;

	u_8			author[ IMELODY_MAXLINE_SIZE + 1 ];
	u_8			author_len;
#endif

} fparser_imelody_work_t;

BEGIN_C_DECLS


extern const fparserif_t fparser_if_imelody_entry;

END_C_DECLS

#endif /* CORE_PRIVATE_FPARSER_IMELODY_H__ */


