/*
*********************************************************************************************************
*                         AIT Multimedia Network Streaming Server
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: Aggregation of debugging Facilities at lower system / driver layer, to be included at
*              different places.
*              Including from different C source, will see only its corresponding parts being defined.
*
*/



//=======================================================================================================
// Debugging facilities for MMP-3GP
//=======================================================================================================

// It will inject special pattern and sequence number into H264 Video Frames, at MMP-3GP layer
//-------------------------------------------------------------------------------------------------------
#ifdef __AMN_SYSDBG__MMP_3GP__VFRAME_POLLUTION__
#define __AMN_SYSDBG__VFRAME_SEQ_INJECTION__
#define AMN_SYSDBG__VFRAME_POLLUTE_MAGIC  0xAA117722
#endif



//=======================================================================================================
// Debugging facilities for AHC-V4L
//=======================================================================================================

// It will inject special pattern and sequence number into H264 Video Frames, at AHC-V4L layer
//-------------------------------------------------------------------------------------------------------
#ifdef __AMN_SYSDBG__AHC_V4L__VFRAME_POLLUTION__
#define __AMN_SYSDBG__VFRAME_SEQ_INJECTION__
#define AMN_SYSDBG__VFRAME_POLLUTE_MAGIC  0xAA115588
#endif


// Trace the PUSH/POP operation on AHC_V4L's Video RingBuffer at particular events: __vbuf_trace_trigger()
// for some amounts of debugging outputs: __AMN_SYSDBG__AHC_V4L__VBUF_TRACE_TRIGGER
//-------------------------------------------------------------------------------------------------------
#if defined(__AMN_SYSDBG__AHC_V4L__VBUF_TRACE_TRIGGER) && (__AMN_SYSDBG__AHC_V4L__VBUF_TRACE_TRIGGER > 0)
UINT32 amndbg__vbuf_trace__i = 0;
#define __vbuf_trace_trigger()        amndbg__vbuf_trace__i = 0
#define __vbuf_trace_DbgOutput(A)   do { \
	if (++amndbg__vbuf_trace__i < __AMN_SYSDBG__AHC_V4L__VBUF_TRACE_TRIGGER) \
		printc("V4L:: VideoBuf BXU-" A ": " __verbose2_fmt, __verbose2_arg); \
} while (0)
#else
#define __vbuf_trace_trigger()
#define __vbuf_trace_DbgOutput(A)
#endif


// Use a standalone ARRAY to store some key metadata for Video Frames, and trace the consistency of
// PUSH/POP operation
//-------------------------------------------------------------------------------------------------------
#ifdef __AMN_SYSDBG__AHC_V4L__VFRAME_TRACE_ARRAY__
#define VFRAME_TRACE_ARRAY_SIZE  VIDEO_MAX_FRAME
static UINT32 VFrame_Trace_wptr;
static UINT32 VFrame_Trace_rptr;

struct VFrame_Trace_meta_t {
	struct v4l_videobuf_meta_t v;
	UINT32 WritePtr;
	UINT32 ReadPtr;
};

struct VFrame_Trace_meta_t VFrame_Trace_Array[VFRAME_TRACE_ARRAY_SIZE];

#define __trace_V4L_VFrame_Push()  do { \
	VFrame_Trace_Array[VFrame_Trace_wptr].v.framesize = framesize; \
	VFrame_Trace_Array[VFrame_Trace_wptr].v.push_cnt  = aque->ulVideoBuf_PushCnt; \
	VFrame_Trace_Array[VFrame_Trace_wptr].v.diff_cnt  = aque->ulVideoBuf_PushCnt - aque->ulVideoBuf_PopCnt; \
	VFrame_Trace_Array[VFrame_Trace_wptr].WritePtr    = aque->ulVideoBuf_WritePtr; \
	VFrame_Trace_Array[VFrame_Trace_wptr].ReadPtr     = aque->ulVideoBuf_ReadPtr; \
	VFrame_Trace_wptr = (VFrame_Trace_wptr + 1) % VFRAME_TRACE_ARRAY_SIZE; \
	__vbuf_trace_DbgOutput("PUSH"); \
} while (0)

#define __trace_V4L_VFrame_Pop()  do { \
	VFrame_Trace_rptr = (VFrame_Trace_rptr + 1) % VFRAME_TRACE_ARRAY_SIZE; \
	__vbuf_trace_DbgOutput("POP "); \
} while (0)

#else
#define __trace_V4L_VFrame_Push()
#define __trace_V4L_VFrame_Pop()
#endif


// UART-CMD for dummping the metadata for Video RingBuffer, at AHC-V4L layer
//-------------------------------------------------------------------------------------------------------
#ifdef __AMN_SYSDBG__AHC_V4L__UARTCMD_VBUF_DUMPING__

#define DUMP_FLAGS_PER_LINE   20
void UartCmd_debug_V4L(struct ait_queue_t *aque)
{
	UINT32 i, j, k, currpos, framesize;
	char aQue_buf[DUMP_FLAGS_PER_LINE+1];
	char QQ='Q', DD='D', PP='P';

	j = 0;
	currpos = aque->ulVideoBuf_ReadPtr;
	framesize = v4lpiggy(currpos)->framesize;
	printc("\r\nVideoBuf dumping:: " __verbose2_fmt, __verbose2_arg);
	while (currpos != aque->ulVideoBuf_WritePtr && j++ < 100) {
		printc("BF.%-3d:%x ", j, currpos);
		printc("nt=%p sz=%-7dct=%-7ddf=%-3dmg=%x\r\n",
				v4lpiggy(currpos)->nextframe, v4lpiggy(currpos)->framesize, v4lpiggy(currpos)->push_cnt,
				v4lpiggy(currpos)->diff_cnt,  v4lpiggy(currpos)->magic);

		currpos += ALIGN32(v4lpiggy(currpos)->framesize) + V4LVBUF_META_SIZE;
		if (currpos >= aque->ulVideoBuf_EndAddr2)
			currpos = aque->ulVideoBuf_BaseAddr;
	}

	printc("\r\naitQueue Dumping:: num (Q.%d D.%d P.%d)  idx (Q.%d D.%d P.%d) \r\n",
			aque->num_QUEUED, aque->num_DONE, aque->num_PROC, aque->idx_QUEUED, aque->idx_DONE, aque->idx_PROC);
	for (i=0; i<aque->num_buffers; i+=DUMP_FLAGS_PER_LINE) {
			for (j=0, k=i; j<DUMP_FLAGS_PER_LINE; j++, k++) {
				if (aque->bufs[k].flags & V4L2_BUF_FLAG_QUEUED)   { aQue_buf[j] = QQ; QQ='q'; DD='D'; PP='P'; }
				if (aque->bufs[k].flags & V4L2_BUF_FLAG_DONE)     { aQue_buf[j] = DD; DD='d'; QQ='Q'; PP='P'; }
				if (aque->bufs[k].flags & V4L2_BUF_FLAG_PROC)     { aQue_buf[j] = PP; PP='p'; QQ='Q'; DD='D'; }
			}
			aQue_buf[j] = 0;
			printc("\tbuf.%-5d:: %s\r\n", i, aQue_buf);
	}

	for (i=0; i<aque->num_buffers; i++) {
		char *str = "";
		if (aque->bufs[i].flags & V4L2_BUF_FLAG_DONE)  str = "DONE";
		if (aque->bufs[i].flags & V4L2_BUF_FLAG_PROC)  str = "PROC";
		if (*str)
			printc("\tbuf.%-5d:: %s  buf=%p len=%-7d \r\n", i, str,
				aque->bufs[i].m.offset + aque->ulVideoBuf_BaseAddr, aque->bufs[i].bytesused);
	}

#ifdef __AMN_SYSDBG__AHC_V4L__VFRAME_TRACE_ARRAY__
	printc("\r\nVFrame_Trace_Array[%d ~ %d] \r\n", VFrame_Trace_rptr, VFrame_Trace_wptr);
	i = VFrame_Trace_rptr;
	j = 0;
	while (i != VFrame_Trace_wptr && j++ < 100) {
		printc("%d:: [%d].framesize = %d  ", i, j, VFrame_Trace_Array[i].v.framesize);
		printc(".push_cnt = %d  ",   VFrame_Trace_Array[i].v.push_cnt );
		printc(".diff_cnt = %d  ",   VFrame_Trace_Array[i].v.diff_cnt  );
		printc(".WritePtr = %x  ",   VFrame_Trace_Array[i].WritePtr   );
		printc(".ReadPtr  = %x\r\n", VFrame_Trace_Array[i].ReadPtr    );
		i = (i + 1) % VFRAME_TRACE_ARRAY_SIZE;
	}
	printc("\r\n");
#endif
}

extern void UartCmd_debug_ASS_encH264(void);
extern void UartCmd_debug_ASS_encMJPEG(void);

void UartCmd_debug11(void)
{
	struct ait_queue_t *aque;
	void (*UartCmd_debug_ASS_SrcNode)(void) = NULL;

	AHC_STREAMING_MODE uiStreamingMode = AHC_GetStreamingMode();

	if (uiStreamingMode == AHC_STREAM_H264) {
		aque = &m_aitQueue[MMP_STREAM_H264];
		UartCmd_debug_ASS_SrcNode = UartCmd_debug_ASS_encH264;
	}
	if (uiStreamingMode == AHC_STREAM_MJPEG) {
		aque = &m_aitQueue[MMP_STREAM_JPEG];
		UartCmd_debug_ASS_SrcNode = UartCmd_debug_ASS_encMJPEG;
	}

	printc("\r\n\r\n===================================================================\r\n");
	MMPF_OS_AcquireSem( aque->ulVideoBuf_lock, 0 );
	UartCmd_debug_V4L(aque);
	if (UartCmd_debug_ASS_SrcNode)  UartCmd_debug_ASS_SrcNode();
	MMPF_OS_ReleaseSem( aque->ulVideoBuf_lock );
	printc("===================================================================\r\n\r\n");
}

void UartCmd_debug22(void)
{
}
#endif


// Automatically output the snapshot provided by UartCmd_debug11(), upon congestion
// Note that we must not do this on PUSH, since it's too high priority to do debugging print!!
//-------------------------------------------------------------------------------------------------------
#ifdef __AMN_SYSDBG__AHC_V4L__UARTCMD_VBUF_SNAPSHOT_ON_CONG__
#define __snapshot_V4L_VFrame()  do { \
	if ((aque->ulVideoBuf_PushCnt - aque->ulVideoBuf_PopCnt) >= (aque->cong_ctl - 4)) { \
		static unsigned __sysdbg_v4l_i__ = 0; \
		if ((__sysdbg_v4l_i__++ % 64) == 0) { \
			UartCmd_debug11(); \
		} \
	} \
} while (0)
#else
#define __snapshot_V4L_VFrame()
#endif



//=======================================================================================================
// Debugging facilities for AMN-ASS (AIT Streaming Server)
//=======================================================================================================

// UART-CMD for dummping the metadata for Video RingBuffer, at AMN-ASS layer
//-------------------------------------------------------------------------------------------------------
#if defined(__AMN_SYSDBG__ASS_H264__UARTCMD_DUMPING__) || defined(__AMN_SYSDBG__ASS_MJPEG__UARTCMD_DUMPING__)

void UartCmd_debug_ASS(void *n)
{
	uint_t i, j, k;

	printc("encNode.%s: FBuf RING:%d(%d,%d,%d) \r\n",
		cast_Node(n)->name, cast_MyNode(n)->frames_head,
		cast_MyNode(n)->frames_head % MAX_QBUF,
		cast_MyNode(n)->frames_proc % MAX_QBUF,
		cast_MyNode(n)->frames_tail % MAX_QBUF);

	k = cast_MyNode(n)->frames_tail;
	for (j=1; (k != cast_MyNode(n)->frames_head && j < 100); j++, k++) {
		i = k % MAX_QBUF;
		printc("\t%-3d:: %-4d [%3d].len=%7d  .idx=%-3d  .buf=%x  .ts=%d \r\n", j, k, i,
				cast_MyNode(n)->fb_len[i],
				cast_MyNode(n)->fb_idx[i],
                cast_MyNode(n)->bufaddr[cast_MyNode(n)->fb_idx[i]] + cast_MyNode(n)->fb_off[i],
                cast_MyNode(n)->fb_ts[i]);
	}

	if (cast_Node(n)->pl) {
		struct ammo_pipeline *pl = cast_Node(n)->pl;
		printc("encNode.%s: Pipeline %d %d \r\n", cast_Node(n)->name, pl->slot_head, pl->slot_tail);
		for (j=pl->slot_head; j!= pl->slot_tail;) {
			struct ammo_frame *f = pl->slots[pl->slot_head];
			printc( "\t%d:: frame=%p .len=%d .buf=%p (%s) \r\n", j, f, f->length, f->d, f->owner->name );
			j = (j + 1) % MAX_PIPELINE_SLOTS;
		}
	}
}

#ifdef __AMN_SYSDBG__ASS_H264__UARTCMD_DUMPING__
void UartCmd_debug_ASS_encH264(void)
{
	struct ammo_node* node = NULL;
	node = node_find_name( AMMO_TYPE__NODE_SOURCE, "H264.0", -1 );
	UartCmd_debug_ASS(node);
}
#endif

#ifdef __AMN_SYSDBG__ASS_MJPEG__UARTCMD_DUMPING__
void UartCmd_debug_ASS_encMJPEG(void)
{
	struct ammo_node* node = NULL;
	node = node_find_name( AMMO_TYPE__NODE_SOURCE, "MJPEG.0", -1 );
	UartCmd_debug_ASS(node);
}
#endif

#endif



//=======================================================================================================
// Common debugging facilities -- Injection of special meta data (seq.no) at the header of each H264 frame
//
// The special video player - openRTSP, can store the streaming video into file: video-H264-1 
//     openRTSP -b 500000 -B 500000 rtsp://192.168.11.8/liveRTSP/v1
//=======================================================================================================
#ifdef __AMN_SYSDBG__VFRAME_SEQ_INJECTION__
#define __pollute_vframes(frame_addr, frame_time, frame_type) do { \
		/* neglect PPS/SPS frames AND boundary frames */ \
		MMP_BYTE nalu_type = *(MMP_BYTE*)((frame_addr) + 4) & 0x1f; \
		static MMP_ULONG amndbg__polluting__i; \
		\
		if (nalu_type == 0x07 /* SPS */ || nalu_type == 0x08 /* PPS */) \
			amndbg__polluting__i = 0; \
		else { \
			*(MMP_ULONG*)((frame_addr) + 8)  = AMN_SYSDBG__VFRAME_POLLUTE_MAGIC; \
			*(MMP_ULONG*)((frame_addr) + 12) = amndbg__polluting__i++; \
			*(MMP_ULONG*)((frame_addr) + 16) = frame_time; \
		/*	*(MMP_ULONG*)((frame_addr) + 20) = frame_type; */ \
		} \
} while (0)
#else
#define __pollute_vframes(frame_addr, frame_time, frame_type)
#endif



//=======================================================================================================
// Common debugging facilities -- ???
//=======================================================================================================
typedef int in_case_no_debug_is_defined;
