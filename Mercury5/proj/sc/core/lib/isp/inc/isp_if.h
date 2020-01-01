/*************************************************************************************************
 * ISP Library Interface
 * AIT AT Team
 * Ver. 0.0.0.1
 *************************************************************************************************/

#ifndef _ISP_IF_H_
#define _ISP_IF_H_


/*************************************************************************************************/
/* ISP I/F Type Definitions                                                                      */
/*************************************************************************************************/
typedef unsigned char					ISP_UINT8;
typedef unsigned short					ISP_UINT16;
typedef unsigned long					ISP_UINT32;
typedef signed char						ISP_INT8;
typedef signed short					ISP_INT16;
typedef signed long						ISP_INT32;

#define ISP_MIN(a, b)					( ((a) < (b)) ? (a) : (b) )
#define ISP_MAX(a, b)					( ((a) > (b)) ? (a) : (b) )
#define ISP_ARRSIZE(a)					( sizeof((a)) / sizeof((a[0])) )
#define ISP_DIFF(a, b)					( ((a) < (b)) ? (b)-(a) : (a)-(b) )
#define ISP_ABS(a)						( ((a) < 0) ? (-(a)) : (a) )


typedef enum {
	ISP_CMD_CLASS_LIB				= 0,
	ISP_CMD_CLASS_AE				= 1,
	ISP_CMD_CLASS_AWB				= 2,
	ISP_CMD_CLASS_AF				= 3
} ISP_CMD_CLASS;

typedef enum {
	ISP_CMD_STATUS_SUCCESS			= 0,
	ISP_CMD_STATUS_FAIL				= 1,
	ISP_CMD_STATUS_INVALID_CLASS	= 2,
	ISP_CMD_STATUS_INVALID_METHOD	= 3,
	ISP_CMD_STATUS_INVALID_CMD		= 4,
	ISP_CMD_STATUS_INCORRECT_COUNT	= 5
} ISP_CMD_STATUS;

typedef enum {
	ISP_SHADING_DISABLE				= 0,
	ISP_SHADING_ENABLE				= 1
} ISP_SHADING_CTL;

typedef enum {
	ISP_IMAGE_EFFECT_NORMAL			= 0,
	ISP_IMAGE_EFFECT_GREY			= 1,
	ISP_IMAGE_EFFECT_SEPIA			= 2,
	ISP_IMAGE_EFFECT_NEGATIVE		= 3,
	ISP_IMAGE_EFFECT_ANTIQUE		= 4,
	ISP_IMAGE_EFFECT_WATERCOLOR		= 5,
	ISP_IMAGE_EFFECT_RED			= 11,
	ISP_IMAGE_EFFECT_GREEN			= 12,
	ISP_IMAGE_EFFECT_BLUE			= 13,
	ISP_IMAGE_EFFECT_BEAUTY			= 14,
	ISP_IMAGE_EFFECT_YELLOW			= 15,
	ISP_IMAGE_EFFECT_CARTOON		= 16,
	ISP_IMAGE_EFFECT_EMBOSS			= 17,
	ISP_IMAGE_EFFECT_OIL			= 18,
	ISP_IMAGE_EFFECT_BW				= 19,
	ISP_IMAGE_EFFECT_SKETCH			= 20,
	ISP_IMAGE_EFFECT_CRAYONE		= 21,
	ISP_IMAGE_EFFECT_WHITEBOARD		= 22,
	ISP_IMAGE_EFFECT_BLACKBOARD		= 23,
	ISP_IMAGE_EFFECT_NUM
} ISP_IMAGE_EFFECT;

typedef enum {
	ISP_COLOR_EFFECT_NORMAL			= 0,
	ISP_COLOR_EFFECT_ACCENT			= 1,
	ISP_COLOR_EFFECT_WEAKEN			= 2,
	ISP_COLOR_EFFECT_SWAP			= 3,
	ISP_COLOR_EFFECT_GRADIENT		= 4,
	ISP_COLOR_EFFECT_SOLARIZE		= 5,
	ISP_COLOR_EFFECT_VINTAGE		= 6,
	ISP_COLOR_EFFECT_CONTRAST		= 7,
	ISP_COLOR_EFFECT_LOMO			= 8,
	ISP_COLOR_EFFECT_NUM
} ISP_COLOR_EFFECT;

typedef enum {
	ISP_3A_ALGO_AE					= 0,
	ISP_3A_ALGO_AWB					= 1,
	ISP_3A_ALGO_AF					= 2
} ISP_3A_ALGO;

typedef enum {
	ISP_AF_STOP						= 0,
	ISP_AF_START					= 1
} ISP_AF_CTL;

typedef enum {
	ISP_AF_MODE_AUTO				= 0,
	ISP_AF_MODE_MANUAL				= 1,
	ISP_AF_MODE_MACRO				= 2,
	ISP_AF_MODE_FULL				= 3,
	ISP_AF_MODE_PAN					= 4,
	ISP_AF_MODE_NULL				= 5
} ISP_AF_MODE;

typedef enum {
	ISP_AF_TYPE_ONE_SHOT			= 0,
	ISP_AF_TYPE_CONTINUOUS			= 1
} ISP_AF_TYPE;

typedef enum {
	ISP_AF_RESULT_MOVING			= 0,
	ISP_AF_RESULT_FOCUSED			= 2,
	ISP_AF_RESULT_MISSED			= 3
} ISP_AF_RESULT;

typedef enum {
	ISP_CUSTOM_WIN_MODE_OFF			= 0,
	ISP_CUSTOM_WIN_MODE_ON			= 1
} ISP_CUSTOM_WIN_MODE;

typedef enum {
	ISP_AE_STATUS_UNSTABLE			= 0,
	ISP_AE_STATUS_STABLE			= 1
} ISP_AE_STATUS;

typedef enum {
	ISP_AE_METERING_AVERAGE			= 0,
	ISP_AE_METERING_CENTER			= 1,
	ISP_AE_METERING_SPOT			= 2,
	ISP_AE_METERING_MATRIX			= 3,
	ISP_AE_METERING_LAND			= 4,
	ISP_AE_METERING_NUM
} ISP_AE_METERING;

typedef enum {
	ISP_AE_MODE_P					= 0, // program
	ISP_AE_MODE_A					= 1, // aperture priority
	ISP_AE_MODE_S					= 2, // shutter priority
	ISP_AE_MODE_M					= 3, // manual
	ISP_AE_MODE_NUM
} ISP_AE_MODE;

typedef enum {
	ISP_AE_FLICKER_OFF				= 0,
	ISP_AE_FLICKER_AUTO				= 1,
	ISP_AE_FLICKER_60HZ				= 2,
	ISP_AE_FLICKER_50HZ				= 3
} ISP_AE_FLICKER;

typedef enum {
	ISP_AWB_MODE_BYPASS				= 0,
	ISP_AWB_MODE_AUTO				= 1,
	ISP_AWB_MODE_MANUAL				= 2,
	ISP_AWB_MODE_NUM
} ISP_AWB_MODE;

typedef enum {
	ISP_AL_DISABLE					= 0,
	ISP_AL_ENABLE					= 1,
	ISP_AL_LOCK						= 3,
	ISP_AL_UNLOCK					= 5,
	ISP_AL_SET						= 0xFF
} ISP_AL_CTL;

typedef enum {
	ISP_DF_DISABLE					= 0,
	ISP_DF_ENABLE					= 1,
	ISP_DF_LOCK						= 3,
	ISP_DF_UNLOCK					= 5,
	ISP_DF_SET						= 0xFF
} ISP_DF_CTL;

typedef enum {
	ISP_3A_DISABLE					= 0,
	ISP_3A_ENABLE					= 1,
	ISP_3A_PAUSE					= 2,
	ISP_3A_RECOVER					= 3
} ISP_3A_CTL;

typedef enum {
	ISP_FLASH_STATUS_OFF			= 0,
	ISP_FLASH_STATUS_ON				= 1
} ISP_FLASH_STATUS;

typedef enum {
	ISP_IQ_HDR_MODE_STAGGER                = 0,
    ISP_IQ_HDR_MODE_SEQUENTIAL             = 1
} ISP_IQ_HDR_STATUS;

typedef enum {
	ISP_IQ_SWITCH_OFF				= 0x0000,
	ISP_IQ_SWITCH_ALL				= 0xFFFF,
	ISP_IQ_SWITCH_LS				= 0x0001,
	ISP_IQ_SWITCH_CS				= 0x0002,
	ISP_IQ_SWITCH_R0				= 0x0004,
	ISP_IQ_SWITCH_R1				= 0x0008,
	ISP_IQ_SWITCH_R2				= 0x0010,
	ISP_IQ_SWITCH_R3				= 0x0020,
	ISP_IQ_SWITCH_R4				= 0x0040,
	ISP_IQ_SWITCH_R5				= 0x0080,
	ISP_IQ_SWITCH_R6				= 0x0100,
	ISP_IQ_SWITCH_R7				= 0x0200,
	ISP_IQ_SWITCH_R8				= 0x0400,
	ISP_IQ_SWITCH_HSV				= 0x8000,
	ISP_IQ_SWITCH_OPR				= 0xFFFC,
	ISP_IQ_SWITCH_NUM
} ISP_IQ_SWITCH;

typedef enum {
	ISP_IQ_MEMOPR_MODE_OFF			= 0,
	ISP_IQ_MEMOPR_MODE_AUTO			= 1,
	ISP_IQ_MEMOPR_MODE_CPU			= 2,
	ISP_IQ_MEMOPR_MODE_DMA			= 3
} ISP_IQ_MEMOPR_MODE;

typedef enum {
	ISP_IQ_MODULE_SDC				= 0,	// static defect correction
	ISP_IQ_MODULE_BLC				= 1,	// black level compensation
	ISP_IQ_MODULE_BCG				= 2,	// awb calibration gain
	ISP_IQ_MODULE_AEG				= 3,	// ae gain
	ISP_IQ_MODULE_LS				= 4,	// luma shading
	ISP_IQ_MODULE_CS				= 5,	// chroma shading
	ISP_IQ_MODULE_DPC				= 6,	// defect pixel compensation
	ISP_IQ_MODULE_AWBG				= 7,	// awb gain
	ISP_IQ_MODULE_NR				= 8,	// noise reduction: bnr, ynr, gnr, cnr
	ISP_IQ_MODULE_EE				= 9,	// edge enhancement: yee, old_edge
	ISP_IQ_MODULE_UVM12				= 10,	// uv ccm
	ISP_IQ_MODULE_CC				= 11,	// color correction matrix
	ISP_IQ_MODULE_GC8				= 12,	// gamma correction
	ISP_IQ_MODULE_ALL				= 13,	// all modules
	ISP_IQ_MODULE_NUM
} ISP_IQ_MODULE;

typedef enum {
	ISP_IQ_DIRECTION_ORIGINAL		= 0,
	ISP_IQ_DIRECTION_90_DEGREE		= 1,
	ISP_IQ_DIRECTION_180_DEGREE		= 2,
	ISP_IQ_DIRECTION_270_DEGREE		= 3,
	ISP_IQ_DIRECTION_H_MIRROR		= 4,
	ISP_IQ_DIRECTION_V_MIRROR		= 5
} ISP_IQ_DIRECTION;

typedef enum {
	ISP_IQ_CHECK_CLASS_GAIN			= 0,
	ISP_IQ_CHECK_CLASS_ENERGY		= 1,
	ISP_IQ_CHECK_CLASS_COLORTEMP	= 2
} ISP_IQ_CHECK_CLASS;

typedef enum {
	ISP_COLOR_ID_R					= 0,
	ISP_COLOR_ID_GR					= 1,
	ISP_COLOR_ID_GB					= 2,
	ISP_COLOR_ID_B					= 3
} ISP_COLOR_ID;

typedef enum {
	ISP_CHIP_ID_838					= 0,
	ISP_CHIP_ID_848					= 1,
	ISP_CHIP_ID_868					= 2,
	ISP_CHIP_ID_988E				= 3,
	ISP_CHIP_ID_82X					= 4,
	ISP_CHIP_ID_840					= 5,
	ISP_CHIP_ID_842					= 6,
	ISP_CHIP_ID_8451				= 7,
	ISP_CHIP_ID_8453				= 8,
	ISP_CHIP_ID_988					= 9,
	ISP_CHIP_ID_8455				= 10,
	ISP_CHIP_ID_8589				= 11,
	ISP_CHIP_ID_8428				= 12,
	ISP_CHIP_ID_NUM
} ISP_CHIP_ID;

typedef enum {
	ISP_OPR_OFFSET_VIF				= 0,
	ISP_OPR_OFFSET_R0				= 1,
	ISP_OPR_OFFSET_R1				= 2,
	ISP_OPR_OFFSET_R2				= 3,
	ISP_OPR_OFFSET_R3				= 4,
	ISP_OPR_OFFSET_R4				= 5,
	ISP_OPR_OFFSET_R5				= 6,
	ISP_OPR_OFFSET_R6				= 7,
	ISP_OPR_OFFSET_R7				= 8,
	ISP_OPR_OFFSET_APICAL			= 9,
	ISP_OPR_OFFSET_LS				= 10,
	ISP_OPR_OFFSET_CS				= 11,
	ISP_OPR_OFFSET_GNR_LUMA			= 12,
	ISP_OPR_OFFSET_YNRYEE			= 13,
	ISP_OPR_OFFSET_YNRYEE_W			= 14,
	ISP_OPR_OFFSET_SDC				= 15,
	ISP_OPR_OFFSET_YMIX				= 16,
	ISP_OPR_OFFSET_HSVADJ			= 17,
	ISP_OPR_OFFSET_R8				= 18,
	ISP_OPR_OFFSET_NUM
} ISP_OPR_OFFSET;

typedef enum {
	ISP_HW_LIMIT_AE_WIN_NUM			= 0,
	ISP_HW_LIMIT_AWB_WIN_NUM		= 1,
	ISP_HW_LIMIT_AF_WIN_NUM			= 2,
	ISP_HW_LIMIT_AF_FILTER_NUM		= 3,
	ISP_HW_LIMIT_AF_FD_IDX			= 4,
	ISP_HW_LIMIT_HIST_BIN_NUM		= 5,
	ISP_HW_LIMIT_NUM
} ISP_HW_LIMIT;

typedef enum {
	ISP_BANK_ADDR_IQ				= 0,
	ISP_BANK_ADDR_LS				= 1,
	ISP_BANK_ADDR_CS				= 2,
	ISP_BANK_ADDR_NUM
} ISP_BANK_ADDR;

typedef enum {
	ISP_BUFFER_CLASS_IQ_BIN_SRC		= 0,
	ISP_BUFFER_CLASS_IQ_BIN_DST		= 1,
	ISP_BUFFER_CLASS_IQ_BIN_TMP		= 2,
	ISP_BUFFER_CLASS_MEMOPR_IQ		= 3,
	ISP_BUFFER_CLASS_MEMOPR_LS		= 4,
	ISP_BUFFER_CLASS_MEMOPR_CS		= 5,
	ISP_BUFFER_CLASS_AE_HW			= 6,
	ISP_BUFFER_CLASS_AE_SW			= 7,
	ISP_BUFFER_CLASS_AF_HW			= 8,
	ISP_BUFFER_CLASS_AF_SW			= 9,
	ISP_BUFFER_CLASS_AWB_HW			= 10,
	ISP_BUFFER_CLASS_AWB_SW			= 11,
	ISP_BUFFER_CLASS_FLICKER_HW		= 12,
	ISP_BUFFER_CLASS_FLICKER_SW		= 13,
	ISP_BUFFER_CLASS_HIST_HW		= 14,
	ISP_BUFFER_CLASS_HIST_SW		= 15,
	ISP_BUFFER_CLASS_IQ_BIN_EZ		= 16,
	ISP_BUFFER_CLASS_NUM
} ISP_BUFFER_CLASS;

typedef enum {
	ISP_BUFFER_TYPE_ARBITRARY		= 0,
	ISP_BUFFER_TYPE_CACHEABLE		= 1,
	ISP_BUFFER_TYPE_NONCACHEABLE	= 2
} ISP_BUFFER_TYPE;


typedef enum {
	//BLC
	ISP_TUNING_TYPE_BLC					= 0x000,
	//DPC
	ISP_TUNING_TYPE_DPC					= 0x010,
	//luma shading
	ISP_TUNING_TYPE_LSHD_R_TBL			= 0x020,
	ISP_TUNING_TYPE_LSHD_G_TBL			= 0x021,
	ISP_TUNING_TYPE_LSHD_B_TBL			= 0x022,
	//chroma shading
	ISP_TUNING_TYPE_CSHD_R_TBL			= 0x030,
	ISP_TUNING_TYPE_CSHD_G_TBL			= 0x031,
	ISP_TUNING_TYPE_CSHD_B_TBL			= 0x032,
	//demoasaic
	ISP_TUNING_TYPE_DEMOSAIC			= 0x040,
	//YNR
	ISP_TUNING_TYPE_YNR_CI				= 0x050,
	ISP_TUNING_TYPE_YNR_GNR				= 0x051,
	//CNR
	ISP_TUNING_TYPE_CNR					= 0x060,
	//EE
	ISP_TUNING_TYPE_EE					= 0x070,
	//CCM
	ISP_TUNING_TYPE_CCM					= 0x080,
	//HSV
	ISP_TUNING_TYPE_HSV					= 0x090,
	//Gamma
	ISP_TUNING_TYPE_GAMMA_R				= 0x0A0,
	ISP_TUNING_TYPE_GAMMA_G				= 0x0A1,
	ISP_TUNING_TYPE_GAMMA_B				= 0x0A2,
	//AE
	ISP_TUNING_TYPE_AE_CURVE			= 0x0B0,
	ISP_TUNING_TYPE_AE_CALIRATE			= 0x0B1,
	ISP_TUNING_TYPE_AE_EV_TARGET		= 0x0B2,
	ISP_TUNING_TYPE_AE_EV_ARRAY			= 0x0B3,
	ISP_TUNING_TYPE_AE_CUS_WIN_WEIGHT	= 0x0B4,
	ISP_TUNING_TYPE_AE_CONVERGE_SPEED	= 0x0B5,	
	//AWB
	ISP_TUNING_TYPE_AWB_OPD				= 0x0C0,	
	ISP_TUNING_TYPE_AWB_OPD_WEIGHT		= 0x0C1,	
	ISP_TUNING_TYPE_AWBADJ_BY_RBGAIN	= 0x0C2,		
	ISP_TUNING_TYPE_AWBADJ_BY_LUX		= 0x0C3,			
	ISP_TUNING_TYPE_AWB_MWB				= 0x0C4,			
					
	ISP_TUNING_TYPE_NUM
} ISP_TUNING_TYPE;

#define EZ_IQ_SYS_NUM  3
#define EZ_IQ_ITEM_NUM  8
#define EZ_IQ_TABLE_COL	100
#define EZ_IQ_MAX_ITEM  35//8*3+11
#define EZ_IQ_DATA_MAX_SIZE  (256+28)
#define EZ_IQ_HEADER_SIZE  28//header size in EZ_MODE_IQ_DATA_BUF


typedef enum {
	EZ_IQ_YNR_CI		= 0,
	EZ_IQ_EE			= 1,
	EZ_IQ_CNR			= 2,
	EZ_IQ_YNR_GNR		= 3,
	EZ_IQ_DPC			= 4,
	EZ_IQ_UVM10			= 5,
	EZ_IQ_UVM8			= 6,
	EZ_IQ_INIT			= 7,
	EZ_IQ_NUM_CNT
} EZ_MODE_IQ_TYPE;

typedef struct
{
	char info[16];
	unsigned int sysmode;
	unsigned int page;
	unsigned int type;
	unsigned int index;
	unsigned int size;
	unsigned int tbl_width;
	unsigned int tbl_height;
	unsigned int tbl_type;
	void *buf_ptr;
} EZ_MODE_IQ_ITEM_SETTING;

typedef struct
{
	char info[128];
	unsigned int sys_num;
	unsigned int item_num;
	unsigned int otheriq_num;
	unsigned int offset[EZ_IQ_MAX_ITEM];
	EZ_MODE_IQ_ITEM_SETTING	 item[EZ_IQ_MAX_ITEM];
	unsigned int fsize;
} EZ_MODE_IQ_STRUCT;

typedef struct __packed
{
	unsigned int cmd_type;
	unsigned int data_length;
	unsigned int sysmode;
	unsigned int page;
	unsigned int type;
	unsigned int index;
	unsigned int buf_ptr_size;
	void* buf_ptr;
} EZ_MODE_IQ_DATA_BUF;

typedef struct {
	ISP_CHIP_ID			ID;
	ISP_UINT16*			OprOfst;
	ISP_UINT32*			HwLimit;
	ISP_UINT32			BankAddr[ISP_BANK_ADDR_NUM];
	ISP_UINT32			BufAddr[ISP_BUFFER_CLASS_NUM];
	ISP_UINT32			BufSize[ISP_BUFFER_CLASS_NUM];
} ISP_CHIP;

extern ISP_CHIP gIspChip;

extern ISP_UINT16 gOprMap[256];

typedef	struct {
	ISP_UINT8			ID[16];
	ISP_UINT8			MajorVer;
	ISP_UINT8			MinorVer;
	ISP_UINT8			InnerVer0;
	ISP_UINT8			InnerVer1;
	ISP_UINT16			Year;
	ISP_UINT8			Month;
	ISP_UINT8			Day;
	
	//EZ IQ
	ISP_UINT8			DateTime[32];
	ISP_UINT8			GUID[64];
} ISP_IF_VERSION;

typedef enum {
	ISP_VERSION_STATUS_MATCH			= 0,
	ISP_VERSION_STATUS_NONMATCH			= 1
} ISP_VERSION_STATUS;

typedef enum {
	ISP_CUSTOM_WEIGHT_MODE_OFF			= 0,
	ISP_CUSTOM_WEIGHT_MODE_ON			= 1
} ISP_CUSTOM_WEIGHT_MODE;

/*************************************************************************************************/
/* ISP I/F Library Control Related Routines                                                      */
/*************************************************************************************************/
ISP_IF_VERSION ISP_IF_LIB_GetLibVer(void);
ISP_IF_VERSION ISP_IF_LIB_GetIQFormatVer(void);
ISP_IF_VERSION ISP_IF_LIB_GetIQDataVer(void);
ISP_IF_VERSION ISP_IF_LIB_GetUserName(void);
ISP_IF_VERSION ISP_IF_LIB_GetProjectName(void);
ISP_IF_VERSION ISP_IF_LIB_GetSensorName(void);
ISP_IF_VERSION ISP_IF_LIB_GetEzIqVer(void);
ISP_VERSION_STATUS ISP_IF_LIB_CompareIQVer(void);
ISP_CHIP_ID ISP_IF_LIB_GetChipID(void);
void ISP_IF_LIB_Init(void);//lunch IQ file, initial Library

ISP_UINT32 ISP_IF_LIB_GetTableStartAddr(void);
ISP_UINT32 ISP_IF_LIB_GetTableTotalSize(void);
ISP_UINT32 ISP_IF_LIB_GetTableAddr(ISP_UINT8 index);

ISP_UINT32 ISP_IF_LIB_Compress(ISP_UINT32 src_addr, ISP_UINT32 dst_addr, ISP_UINT32 size, ISP_UINT32 tmp_addr);
ISP_UINT32 ISP_IF_LIB_Decompress(ISP_UINT32 src_addr, ISP_UINT32 dst_addr, ISP_UINT32 tmp_addr);

ISP_UINT32 ISP_IF_LIB_GetDbgData(ISP_UINT8 idx);
ISP_UINT16 ISP_IF_LIB_DumpOprData(ISP_UINT8* dbg_addr, ISP_UINT32 max_size);

ISP_UINT32 ISP_IF_LIB_BigRatio(ISP_UINT32 x, ISP_UINT32 n, ISP_UINT32 m); // x*n/m

/*************************************************************************************************/
/* ISP I/F Color Related Routines                                                                */
/*************************************************************************************************/
void ISP_IF_IQ_ControlMemOpr(ISP_IQ_MEMOPR_MODE mode);
void ISP_IF_IQ_SetAll(void);						//set IQ from excel, it will set all ON
void ISP_IF_IQ_CheckBypass(void);					//check which item to turn off

void ISP_IF_IQ_SetSysMode(ISP_UINT32 sys_mode);
ISP_UINT32 ISP_IF_IQ_GetSysMode(void);

void ISP_IF_IQ_SetOpr(ISP_UINT16 addr, ISP_UINT8 byte_count, ISP_UINT32 val);	//set value to opr buffer(DMA mode)
ISP_UINT32 ISP_IF_IQ_GetOpr(ISP_UINT16 addr, ISP_UINT8 byte_count);
void ISP_IF_IQ_SetHwOpr(ISP_UINT16 addr, ISP_UINT8 byte_count, ISP_UINT32 val);	//set value to HW opr
ISP_UINT32 ISP_IF_IQ_GetHwOpr(ISP_UINT16 addr, ISP_UINT8 byte_count);

void ISP_IF_IQ_SetRunMode(ISP_UINT32 run_mode);		//mode predefine for usage[CAMERA/SCENE/CALI_AWB/CALI_LS/CALI_CS/CALI_SNR]

void ISP_IF_IQ_ControlLS(ISP_SHADING_CTL status);	// LS HW enable on/off
void ISP_IF_IQ_ControlCS(ISP_SHADING_CTL status);	// CS HW enable on/off

ISP_INT32 ISP_IF_IQ_GetID(ISP_IQ_CHECK_CLASS check_class);						//Get current status ID( GID,EID,TID)
void ISP_IF_IQ_SetIDOffset(ISP_IQ_CHECK_CLASS check_class, ISP_INT32 offset);	//increase/decreae index for XID
ISP_INT32 ISP_IF_IQ_GetIDOffset(ISP_IQ_CHECK_CLASS check_class);

void ISP_IF_IQ_SetSwitch(ISP_IQ_MODULE module, ISP_UINT8 enable);				//turn ON/OFF for isp item, !not to turn OFF "ISP_IQ_MODULE_ALL"!
ISP_IQ_MODULE ISP_IF_IQ_GetSwitch(ISP_IQ_MODULE module);

void ISP_IF_IQ_SetIQIndex(ISP_UINT16 module_num,ISP_UINT16 cond_id, ISP_UINT16 index);	//replace index if not 0xFF
ISP_UINT16 ISP_IF_IQ_GetIQIndex(ISP_UINT16 module_num,ISP_UINT16 cond_id);

void ISP_IF_IQ_SetDirection(ISP_IQ_DIRECTION direction);						//set VIF-ISP direct

void ISP_IF_IQ_UpdateInputSize(void);				//trigger for Acc window recalculate

void ISP_IF_IQ_SetCCM(ISP_INT16* ccm);				//translate ccm matrix to HW opr			

void ISP_IF_IQ_ControlHSV(ISP_UINT8 enable);		//HSV on/off 988/8589
void ISP_IF_IQ_SetHSV_HueAdj(ISP_INT16* hueadj);	//HSV table	988/8589
void ISP_IF_IQ_SetHSV_SatAdj(ISP_UINT16* satadj);
void ISP_IF_IQ_SetHSV_ValAdj(ISP_UINT16* valadj);

ISP_UINT32* ISP_IF_IQ_GetEdgeAccPtr(void);
ISP_UINT32* ISP_IF_IQ_GetFlickerAccPtr(void);
ISP_UINT32* ISP_IF_IQ_GetHistAccPtr(void);

void ISP_IF_IQ_SetAWBGains(ISP_UINT32 gain_r, ISP_UINT32 gain_g, ISP_UINT32 gain_b, ISP_UINT32 gain_base);	//AWB gain to HW
void ISP_IF_IQ_SetAEGain(ISP_UINT32 gain, ISP_UINT32 gain_base);				//AE Digital gain to HW
void ISP_IF_IQ_SetAEGainF1(ISP_UINT32 gain, ISP_UINT32 gain_base);				//AE Digital gain to HW (HDR short exposure)

void ISP_IF_IQ_SetColorID(ISP_UINT8 color_id);
ISP_UINT8 ISP_IF_IQ_GetColorID(void);

void ISP_IF_IQ_SetISPInputLength(ISP_UINT32 length_x, ISP_UINT32 length_y);		//update VIF->ISP size, need to call "ISP_IF_IQ_UpdateInputSize" to set for HW
void ISP_IF_IQ_GetISPInputLength(ISP_UINT32 *length_x, ISP_UINT32 *length_y);

void ISP_IF_IQ_SetCaliRatio(ISP_UINT32 x_scale_n, ISP_UINT32 x_scale_m, ISP_INT32 x_offset, ISP_UINT32 y_scale_n, ISP_UINT32 y_scale_m, ISP_INT32 y_offset);	//set calibration table zoom/shift
void ISP_IF_IQ_GetCaliBase(ISP_UINT32 *base_x, ISP_UINT32 *base_y);				//get default calibration image size.

void ISP_IF_IQ_SetHDRStatus(ISP_IQ_HDR_STATUS mode, ISP_UINT8 enable);			//HDR on/off
ISP_UINT8 ISP_IF_IQ_GetHDRStatus(void);
ISP_UINT32 ISP_IF_IQ_GetHDR_ShortShutter(void);
ISP_UINT32 ISP_IF_IQ_GetHDR_ShortGain(void);
void ISP_IF_IQ_HDR_SetGain(ISP_UINT16 gain);		//Long-short ration

void ISP_IF_IQ_UpdateOprtoHW(ISP_IQ_SWITCH iq_switch, ISP_UINT8 force_update);	//update DRAM data to HW opr

/*************************************************************************************************/
/* ISP I/F Feature Related Routines                                                              */
/*************************************************************************************************/
void ISP_IF_F_SetImageEffect(ISP_IMAGE_EFFECT image_effect);
void ISP_IF_F_SetColorEffect(ISP_COLOR_EFFECT color_effect, ISP_UINT8 r0, ISP_UINT8 g0, ISP_UINT8 b0, ISP_UINT8 r1, ISP_UINT8 g1, ISP_UINT8 b1, ISP_INT16 level);
void ISP_IF_F_SetContrast(ISP_INT16 level);
void ISP_IF_F_SetNoiseReduction(ISP_INT16 level);
void ISP_IF_F_SetSharpness(ISP_INT16 level);
void ISP_IF_F_SetSaturation(ISP_INT16 level);
void ISP_IF_F_SetGamma(ISP_INT16 level);
void ISP_IF_F_SetHue(ISP_INT16 level);
void ISP_IF_F_SetBrightness(ISP_INT16 level);
void ISP_IF_F_SetBeautyShotLevel(ISP_INT16 level);
void ISP_IF_F_SetPosterization(ISP_UINT16 level);
void ISP_IF_F_AdjustColorTemp(ISP_INT16 level);

void ISP_IF_F_SetZoomRatio(ISP_UINT16 zoom_ratio);

void ISP_IF_F_SetIS(ISP_UINT16 param);			//change shutter for ISC mode
void ISP_IF_F_SetDefogLevelScale(ISP_UINT16 level);
ISP_UINT16 ISP_IF_F_GetDefogLevelScale(void);
void ISP_IF_F_SetDefogEn(ISP_UINT16 enable);	//defog with WDR curve
ISP_UINT16 ISP_IF_F_GetDefogEn(void);
void ISP_IF_F_SetDefog(ISP_UINT16 level);		//set value for isolate function
ISP_UINT16 ISP_IF_F_GetDefog(void);

void ISP_IF_F_SetWDREn(ISP_UINT16 enable);		//WDR HW on/off
ISP_UINT16 ISP_IF_F_GetWDREn(void);
void ISP_IF_F_SetWDR(ISP_UINT16 level);			//WDR level, currently is AUTO controled by AE
ISP_UINT16 ISP_IF_F_GetWDR(void);

void ISP_IF_F_SetWDRGgain(ISP_UINT16* ggain);	//manual set WDR gain
void ISP_IF_F_SetWDRLgain(ISP_UINT16* lgain_min, ISP_UINT16* lgain_max, ISP_UINT16 lgain_hi, ISP_UINT16 lgain_lw);
void ISP_IF_F_SetWDRVgain(ISP_UINT16 vgain_up, ISP_UINT16 vgain_dn);			//vertical WDR gain
void ISP_IF_F_WDRFastCnt(ISP_UINT16 cnt);

void ISP_IF_F_SetDark(ISP_UINT16 level);		//change gamma by lux

//TBD
void ISP_IF_F_SetTiltShift(ISP_UINT8 enable, ISP_UINT16 center_x, ISP_UINT16 center_y, ISP_UINT16 width, ISP_UINT16 strength);
ISP_UINT8 ISP_IF_F_GetTiltShift(void);
void ISP_IF_F_SetBeautyShot(ISP_UINT8 enable, ISP_UINT16 center_x, ISP_UINT16 center_y, ISP_UINT16 width, ISP_UINT16 strength);
ISP_UINT8 ISP_IF_F_GetBeautyShot(void);
void ISP_IF_F_SetDOFEffect(ISP_UINT8 enable, ISP_UINT16 center_x, ISP_UINT16 center_y, ISP_UINT16 width, ISP_UINT16 strength);
ISP_UINT8 ISP_IF_F_GetDOFEffect(void);
//TBD

void ISP_IF_F_SetAL(ISP_AL_CTL ctl, ISP_UINT8 x_low, ISP_UINT8 x_high, ISP_UINT8 bp_max, ISP_UINT8 wp_min, ISP_UINT8 p_low_percent, ISP_UINT8 p_high_percent, ISP_UINT8 cycles, ISP_UINT8 update_th);
void ISP_IF_F_SetAL_Th(ISP_UINT8 x_low, ISP_UINT8 x_high);

//defog with gain-offset
void ISP_IF_F_SetALDF(ISP_DF_CTL ctl, ISP_UINT8 x_low, ISP_UINT8 x_high, ISP_UINT8 bp_max, ISP_UINT8 wp_min, ISP_UINT8 p_low_percent, ISP_UINT8 p_high_percent);
void ISP_IF_F_SetALDF_Th(ISP_UINT8 x_low, ISP_UINT8 x_high);
ISP_UINT8 ISP_IF_F_GetALDF(void);
void ISP_IF_F_SetALDFLevel(ISP_UINT16 level);
ISP_UINT16 ISP_IF_F_GetALDFLevel(void);
ISP_UINT32 ISP_IF_F_Table_GetAddrByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_F_Table_GetValueByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_F_Table_GetRowsByName(ISP_UINT32 name);
ISP_UINT32 ISP_IF_F_Table_GetColsByName(ISP_UINT32 name);
ISP_UINT32 ISP_IF_F_Table_GetTypeByName(ISP_UINT32 name);

//histrogram customer windows setting
void ISP_IF_HIST_SetCustomWin(ISP_UINT16 x_start, ISP_UINT16 x_end, ISP_UINT16 y_start, ISP_UINT16 y_end, ISP_UINT16 base);
ISP_UINT8 ISP_IF_HIST_GetCustomMode(void);

/*************************************************************************************************/
/* ISP I/F 3A Related Routines                                                                   */
/*************************************************************************************************/
void ISP_IF_3A_Init(void);						//3A function registered and parameter initial
void ISP_IF_3A_Control(ISP_3A_CTL status);		//3A status control
void ISP_IF_3A_SetSwitch(ISP_3A_ALGO algo, ISP_UINT8 enable);					//3A algorism control
ISP_UINT8 ISP_IF_3A_GetSwitch(ISP_3A_ALGO algo);

/*************************************************************************************************/
/* ISP I/F AF Related Routines                                                                   */
/*************************************************************************************************/
void ISP_IF_AF_Control(ISP_AF_CTL status);
ISP_AF_RESULT ISP_IF_AF_GetResult(void);
ISP_UINT8 ISP_IF_AF_SetMode(ISP_AF_MODE mode);	//search perfer
ISP_AF_MODE ISP_IF_AF_GetMode(void);
void ISP_IF_AF_SetType(ISP_AF_TYPE type);		//continue / one-shot
ISP_AF_TYPE ISP_IF_AF_GetType(void);
void ISP_IF_AF_Execute(void);
void ISP_IF_AF_SetCustomWinMode(ISP_CUSTOM_WIN_MODE mode);						//use customer window to do AF
void ISP_IF_AF_SetCustomWin(ISP_UINT16 x_start, ISP_UINT16 x_end, ISP_UINT16 y_start, ISP_UINT16 y_end, ISP_UINT16 base);
void ISP_IF_AF_SetWin(ISP_UINT8 win_idx, ISP_UINT16 *win);						//Acc window position
void ISP_IF_AF_SetWins(ISP_UINT16 *win);
void ISP_IF_AF_GetWin(ISP_UINT8 win_idx, ISP_UINT16 *win);
void ISP_IF_AF_GetWins(ISP_UINT16 *wins);

ISP_UINT16 ISP_IF_AF_GetPos(ISP_UINT8 pos_bitwidth);
void ISP_IF_AF_SetPos(ISP_UINT16 pos, ISP_UINT8 pos_bitwidth);

void ISP_IF_AF_SetSearchRange(ISP_UINT16 normal_min, ISP_UINT16 normal_max, ISP_UINT16 macro_min, ISP_UINT16 macro_max, ISP_UINT8 pos_bitwidth);
void ISP_IF_AF_GetSearchRange(ISP_UINT16* normal_min, ISP_UINT16* normal_max, ISP_UINT16* macro_min, ISP_UINT16* macro_max, ISP_UINT8 pos_bitwidth);

ISP_UINT8 ISP_IF_AF_GetPosBitwidth(void);

void ISP_IF_AF_SetFastMode(ISP_UINT8 enable);
void ISP_IF_AF_SetSysMode(ISP_UINT32 sys_mode);
ISP_UINT32 ISP_IF_AF_GetSysMode(void);
ISP_IF_VERSION ISP_IF_AF_GetVer(void);

//IIR filter parameter setting
void ISP_IF_AF_SetAccFilter_IIR0(ISP_UINT16 b1, ISP_UINT16 b2, ISP_UINT16 a0, ISP_UINT16 a1, ISP_UINT16 a2, ISP_UINT16 in_lc, ISP_UINT16 in_hc, ISP_UINT16 out_lc, ISP_UINT16 out_hc);
void ISP_IF_AF_SetAccFilter_IIR1(ISP_UINT16 b1, ISP_UINT16 b2, ISP_UINT16 a0, ISP_UINT16 a1, ISP_UINT16 a2, ISP_UINT16 in_lc, ISP_UINT16 in_hc, ISP_UINT16 out_lc, ISP_UINT16 out_hc);

ISP_UINT32* ISP_IF_AF_GetAccPtr(void);
ISP_UINT32 ISP_IF_AF_GetAccWinNum(void);
ISP_UINT32 ISP_IF_AF_GetAccFilterNum(void);

void ISP_IF_AF_GetHWAcc(ISP_UINT8 buf_index);
void ISP_IF_AF_SetHWAccBuf(ISP_UINT8 buf_index);								//register ACC buffer addr 

ISP_UINT8* ISP_IF_AF_GetDbgDataPtr(void);
ISP_UINT8 ISP_IF_AF_GetDbgData(ISP_UINT8 idx);

ISP_UINT32 ISP_IF_AF_Table_GetAddrByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_AF_Table_GetValueByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_AF_Table_GetRowsByName(ISP_UINT32 name);
ISP_UINT32 ISP_IF_AF_Table_GetColsByName(ISP_UINT32 name);
ISP_UINT32 ISP_IF_AF_Table_GetTypeByName(ISP_UINT32 name);

/*************************************************************************************************/
/* ISP I/F AE Related Routines                                                                   */
/*************************************************************************************************/
//PASM mode  (now ONLY S mode)
void ISP_IF_AE_SetMode(ISP_AE_MODE mode, ISP_UINT32 shutter, ISP_UINT32 shutter_base, ISP_UINT32 fnum, ISP_UINT32 fnum_base);

ISP_AE_STATUS ISP_IF_AE_GetStatus(void);		//AE stable flag

void ISP_IF_AE_SetMetering(ISP_AE_METERING metering_mode);
ISP_AE_METERING ISP_IF_AE_GetMetering(void);
void ISP_IF_AE_SetISO(ISP_UINT32 iso);			//ISO mode setting, 50 = 1x gain
void ISP_IF_AE_SetFlicker(ISP_AE_FLICKER flicker);								//flicker mode setting
ISP_AE_FLICKER ISP_IF_AE_GetFlicker(void);
ISP_AE_FLICKER ISP_IF_AE_GetAutoFlicker(void);
void ISP_IF_AE_SetEV(ISP_INT32 ev);				//EV +250~-250, default EV:0
ISP_INT32 ISP_IF_AE_GetEV(void);
void ISP_IF_AE_SetEVBias(ISP_INT32 ev_bias, ISP_UINT32 ev_bias_base);			// 1 ev_bias_base = 100 EV
void ISP_IF_AE_GetEVBias(ISP_INT32* ev_bias, ISP_UINT32* ev_bias_base);
void ISP_IF_AE_SetSysMode(ISP_UINT32 sys_mode);
ISP_UINT32 ISP_IF_AE_GetSysMode(void);
void ISP_IF_AE_SetFPS(ISP_UINT32 fps);			//0 for Auto
ISP_UINT32 ISP_IF_AE_GetFPS(void);
void ISP_IF_AE_SetFPSx10(ISP_UINT32 fps);
ISP_UINT32 ISP_IF_AE_GetFPSx10(void);

void ISP_IF_AE_SetFastMode(ISP_UINT8 enable);

void ISP_IF_AE_SetCustomWinMode(ISP_CUSTOM_WIN_MODE mode);						//Do AE with customer window
void ISP_IF_AE_SetCustomWin(ISP_UINT16 x_start, ISP_UINT16 x_end, ISP_UINT16 y_start, ISP_UINT16 y_end, ISP_UINT16 base);
void ISP_IF_AE_SetCustomWinTarget(ISP_UINT32 current, ISP_UINT32 target);
ISP_UINT32 ISP_IF_AE_GetCustomWinAvgLum(void);	//return AvgLum within custom window
ISP_UINT32 ISP_IF_AE_GetAvgLum(void);			//return AvgLum within AE window

ISP_UINT8 ISP_IF_AE_GetFastFlag(void);

ISP_UINT32 ISP_IF_AE_GetRealFPS(void);			//return current estimate sensor FPS
ISP_UINT32 ISP_IF_AE_GetRealFPSx10(void);

ISP_UINT32 ISP_IF_AE_GetSensorVsyncByFPS(void);	//get Vsync limitation

ISP_UINT32 ISP_IF_AE_GetLightCond(void);		//estimate Lux with pre-setting average reflection
ISP_UINT32 ISP_IF_AE_GetLightCondx16(void);

void ISP_IF_AE_SetShutter(ISP_UINT32 shutter, ISP_UINT32 shutter_base);			//overwrite shutter variable
void ISP_IF_AE_SetGain(ISP_UINT32 gain, ISP_UINT32 gain_base);

ISP_UINT32 ISP_IF_AE_GetFnum(void);
ISP_UINT32 ISP_IF_AE_GetFnumBase(void);
ISP_UINT32 ISP_IF_AE_GetShutter(void);
ISP_UINT32 ISP_IF_AE_GetShutterBase(void);
void ISP_IF_AE_SetShutterBase(ISP_UINT32 shutterbase);							//change shutter unit for 1 second
ISP_UINT32 ISP_IF_AE_GetVsync(void);
ISP_UINT32 ISP_IF_AE_GetVsyncBase(void);
ISP_UINT32 ISP_IF_AE_GetGain(void);
ISP_UINT32 ISP_IF_AE_GetGainBase(void);

ISP_UINT32 ISP_IF_AE_GetAccDiv(void);			//divider = each acc block pixel count

ISP_UINT32 ISP_IF_AE_GetDbgData(ISP_UINT8 idx);

void ISP_IF_AE_SetViewAngle(ISP_UINT16 view_angle);
void ISP_IF_AE_PTZ_SetWin(ISP_UINT32 x_str, ISP_UINT32 y_str, ISP_UINT32 width, ISP_UINT32 height, ISP_UINT8 type);
void ISP_IF_AE_PTZ_AccOn(ISP_UINT8 enable);

ISP_UINT8 ISP_IF_AE_GetAdditionMode(void);
void ISP_IF_AE_SetAdditionMode(ISP_UINT8 flag);
void ISP_IF_AE_UpdateHistAETbl(ISP_UINT8 index);
void ISP_IF_AE_SetBinningMode(ISP_UINT8 N,ISP_UINT8 M);

ISP_IF_VERSION ISP_IF_AE_GetVer(void);

void ISP_IF_AE_Execute(void);
void ISP_IF_DF_Execute(void);

void ISP_IF_AE_SetMaxSensorFPS(ISP_UINT32 target_fps);							//to set minimum Vsync for sensor
void ISP_IF_AE_SetMaxSensorFPSx10(ISP_UINT32 target_fps);

ISP_UINT32* ISP_IF_AE_GetAccPtr(void);
ISP_UINT32 ISP_IF_AE_GetAccWinNum(void);
ISP_UINT32 ISP_IF_AE_GetHistBinNum(void);

void ISP_IF_AE_GetHWAcc(ISP_UINT8 buf_index);
void ISP_IF_AE_SetHWAccBuf(ISP_UINT8 buf_index);

void ISP_IF_AE_SetMinFPS(ISP_UINT32 min_fps);	//control max-shutter when checking curve point
void ISP_IF_AE_SetMinFPSx10(ISP_UINT32 min_fps);

void ISP_IF_AE_SetMaxFPS(ISP_UINT32 max_fps);	//to set maximum FPS when AE calculate			
void ISP_IF_AE_SetMaxFPSx10(ISP_UINT32 max_fps);

void ISP_IF_AE_UpdateBeforePreview(void);
void ISP_IF_AE_UpdateBeforeCapture(void);

void ISP_IF_AE_SetFlashStatus(ISP_FLASH_STATUS status);
ISP_FLASH_STATUS ISP_IF_AE_GetFlashStatus(void);

ISP_UINT32 ISP_IF_AE_Table_GetAddrByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_AE_Table_GetValueByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_AE_Table_GetRowsByName(ISP_UINT32 name);
ISP_UINT32 ISP_IF_AE_Table_GetColsByName(ISP_UINT32 name);
ISP_UINT32 ISP_IF_AE_Table_GetTypeByName(ISP_UINT32 name);

void ISP_IF_NaturalAE_Enable(ISP_UINT8 enable);
void ISP_IF_AE_SetEVTargetOffset(ISP_UINT32 offset); 							//set manual NaturalAE offset.
ISP_UINT8 ISP_IF_AE_AEConvergeCheck(void);	//check AE stable or reach max gain/shutter

ISP_UINT32 ISP_IF_AE_GetEVTargetOffset(void);

void ISP_IF_AF_SetCustomWeightMode(ISP_CUSTOM_WEIGHT_MODE mode);
void ISP_IF_AE_SetCustomWeightTable(ISP_UINT8 *addr);

void ISP_IF_AE_SetCustomMaxGain(ISP_UINT32 maxgain);//Customer Max Gain & Max Shutter
void ISP_IF_AE_SetCustomMinExposureFPS(ISP_UINT32 minexposurefps);
ISP_UINT32 ISP_IF_AE_GetCustomMaxGain(void);
ISP_UINT32 ISP_IF_AE_GetCustomMinExposureFPS(void);

void ISP_IF_AE_SetHWAccAddr(ISP_UINT8 index);
void ISP_IF_Flicker_SetHWAccAddr(ISP_UINT8 index);
void ISP_IF_Hist_SetHWAccAddr(ISP_UINT8 index);
/*************************************************************************************************/
/* ISP I/F AWB Related Routines                                                                  */
/*************************************************************************************************/
void ISP_IF_AWB_SetMode(ISP_AWB_MODE mode);	//set AWB mode
ISP_AWB_MODE ISP_IF_AWB_GetMode(void);

//101~200 for special mode. other for temperature used for "ISP_AWB_MODE_MANUAL"
void ISP_IF_AWB_SetColorTemp(ISP_UINT32 color_temp);
ISP_UINT32 ISP_IF_AWB_GetColorTemp(void);
void ISP_IF_AWB_AdjustColorTemp(ISP_INT32 color_temp_adjust);
void ISP_IF_AWB_SetSysMode(ISP_UINT32 sys_mode);
ISP_UINT32 ISP_IF_AWB_GetSysMode(void);
void ISP_IF_AWB_GetRefGain(ISP_UINT32 *buf_ptr_in,ISP_UINT32 *buf_ptr_out);		//do AWB calibration flow in ISP

ISP_UINT32 ISP_IF_AWB_GetGainR(void);
ISP_UINT32 ISP_IF_AWB_GetGainG(void);
ISP_UINT32 ISP_IF_AWB_GetGainB(void);
ISP_UINT32 ISP_IF_AWB_GetGainBase(void);
void ISP_IF_AWB_SetGains(ISP_UINT32 gain_r, ISP_UINT32 gain_g, ISP_UINT32 gain_b);

void ISP_IF_AWB_SetViewAngle(ISP_UINT16 view_angle);

ISP_UINT32 ISP_IF_AWB_GetDbgData(ISP_UINT8 idx);

void ISP_IF_AWB_SetFastMode(ISP_UINT8 enable);

void ISP_IF_AWB_SetCustomWinMode(ISP_CUSTOM_WIN_MODE mode);
void ISP_IF_AWB_SetCustomWin(ISP_UINT16 x_start, ISP_UINT16 x_end, ISP_UINT16 y_start, ISP_UINT16 y_end, ISP_UINT16 base);

ISP_IF_VERSION ISP_IF_AWB_GetVer(void);

void ISP_IF_AWB_Execute(void);

ISP_UINT32* ISP_IF_AWB_GetAccPtr(void);
ISP_UINT32* ISP_IF_AWB_GetOPDAccPtr(void);
ISP_UINT32 ISP_IF_AWB_GetAccWinNum(void);

void ISP_IF_AWB_GetHWAcc(ISP_UINT8 buf_index);
void ISP_IF_AWB_SetHWAccBuf(ISP_UINT8 buf_index);

void ISP_IF_AWB_SetAccRange(ISP_UINT16 percentage_L, ISP_UINT16 percentage_R, ISP_UINT16 percentage_U, ISP_UINT16 percentage_D);
void ISP_IF_AWB_Set8OPDWin(ISP_UINT8 opd_idx, ISP_UINT8* opd_win);
void ISP_IF_AWB_Set8OPDGain(ISP_UINT8* opd_gain);

void ISP_IF_AWB_UpdateBeforePreview(void);
void ISP_IF_AWB_UpdateBeforeCapture(void);

ISP_UINT32 ISP_IF_AWB_Table_GetAddrByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_AWB_Table_GetValueByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_AWB_Table_GetRowsByName(ISP_UINT32 name);
ISP_UINT32 ISP_IF_AWB_Table_GetColsByName(ISP_UINT32 name);
ISP_UINT32 ISP_IF_AWB_Table_GetTypeByName(ISP_UINT32 name);

/*************************************************************************************************/
/* ISP I/F Calibration Related Routines                                                          */
/*************************************************************************************************/
void ISP_IF_CALI_Execute(void);

void ISP_IF_CALI_SetAWB(ISP_UINT8 index,
						ISP_UINT16 gain_r, ISP_UINT16 gain_gr, ISP_UINT16 gain_gb, ISP_UINT16 gain_b,
						ISP_UINT16 color_temp, ISP_UINT16 lux);

void ISP_IF_CALI_SetAWB_Bin(ISP_UINT8 index, ISP_UINT16 color_temp, ISP_UINT16 lux, ISP_UINT16* bin);

void ISP_IF_CALI_SetLS(	ISP_UINT8 index,
						ISP_UINT16 base_x, ISP_UINT16 base_y,
						ISP_UINT16 center_x, ISP_UINT16 center_y,
						ISP_UINT16 offset_x, ISP_UINT16 offset_y,
						ISP_UINT16 rate_x, ISP_UINT16 rate_y,
						ISP_UINT16* table_r, ISP_UINT16* table_g, ISP_UINT16* table_b,
						ISP_UINT16 color_temp, ISP_UINT16 lux);

void ISP_IF_CALI_SetLS_Bin(ISP_UINT8 index, ISP_UINT16 color_temp, ISP_UINT16 lux, ISP_UINT16* bin);

void ISP_IF_CALI_SetLS_Center(ISP_UINT8 index, ISP_UINT16 center_x, ISP_UINT16 center_y);
void ISP_IF_CALI_SetLS_Offset(ISP_UINT8 index, ISP_UINT16 offset_x, ISP_UINT16 offset_y);

void ISP_IF_CALI_SetCS(	ISP_UINT8 index,
						ISP_UINT16 base_x, ISP_UINT16 base_y,
						ISP_UINT16 center_x, ISP_UINT16 center_y,
						ISP_UINT16 offset_x, ISP_UINT16 offset_y,
						ISP_UINT16 scale,
						ISP_UINT16* pos_x, ISP_UINT16* pos_y,
						ISP_UINT16* table_r, ISP_UINT16* table_g, ISP_UINT16* table_b,
						ISP_UINT16 color_temp, ISP_UINT16 lux);

void ISP_IF_CALI_SetCS_Bin(ISP_UINT8 index, ISP_UINT16 color_temp, ISP_UINT16 lux, ISP_UINT16* bin);

void ISP_IF_CALI_SetCS_Center(ISP_UINT8 index, ISP_UINT16 center_x, ISP_UINT16 center_y);
void ISP_IF_CALI_SetCS_Offset(ISP_UINT8 index, ISP_UINT16 offset_x, ISP_UINT16 offset_y);

ISP_UINT16 ISP_IF_CALI_GetAWBGainR(void);
ISP_UINT16 ISP_IF_CALI_GetAWBGainG(void);
ISP_UINT16 ISP_IF_CALI_GetAWBGainB(void);

void ISP_IF_CALI_SetAWBColorTemp(ISP_UINT32 color_temp);
void ISP_IF_CALI_SetLSColorTemp(ISP_UINT32 color_temp);
void ISP_IF_CALI_SetCSColorTemp(ISP_UINT32 color_temp);

/*************************************************************************************************/
/* ISP I/F Command Related Routines                                                              */
/*************************************************************************************************/
ISP_CMD_STATUS ISP_IF_CMD_SendCommand(ISP_CMD_CLASS cmd_class, ISP_UINT32 cmd, void *buf_ptr, ISP_UINT32 size, ISP_UINT32 count);
ISP_CMD_STATUS ISP_IF_CMD_SendCommandtoLib(ISP_UINT32 cmd, void *buf_ptr, ISP_UINT32 size, ISP_UINT32 count);
ISP_CMD_STATUS ISP_IF_CMD_SendCommandtoAE(ISP_UINT32 cmd, void *buf_ptr, ISP_UINT32 size, ISP_UINT32 count);
ISP_CMD_STATUS ISP_IF_CMD_SendCommandtoAWB(ISP_UINT32 cmd, void *buf_ptr, ISP_UINT32 size, ISP_UINT32 count);
ISP_CMD_STATUS ISP_IF_CMD_SendCommandtoAF(ISP_UINT32 cmd, void *buf_ptr, ISP_UINT32 size, ISP_UINT32 count);


/*************************************************************************************************/
/* ISP I/F Tuning Related Routines                                                          */
/*************************************************************************************************/
//ISP_CMD_STATUS ISP_IF_APTUNING_SetPara(ISP_TUNING_TYPE type, void *buf_ptr);
//ISP_CMD_STATUS ISP_IF_APTUNING_GetPara(ISP_TUNING_TYPE type, void *buf_ptr);
ISP_UINT32 ISP_IF_INIT_Table_GetAddrByName(ISP_UINT32 name, ISP_UINT32 index);
ISP_UINT32 ISP_IF_IQ_Table_GetAddrByName(ISP_UINT32 name, ISP_UINT32 index);
void ISP_IF_IQ_SetEZIQSize(ISP_UINT32 size);
ISP_CMD_STATUS ISP_IF_APTUNING_SetPara(ISP_UINT16 mode, ISP_UINT16 page, ISP_UINT16 type, ISP_UINT16 index, void *buf_ptr);
ISP_CMD_STATUS ISP_IF_APTUNING_GetPara(ISP_UINT16 mode, ISP_UINT16 page, ISP_UINT16 type, ISP_UINT16 index, void *buf_ptr);
ISP_CMD_STATUS ISP_IF_APTUNING_Para(EZ_MODE_IQ_DATA_BUF *iq);

#endif // _ISP_IF_H_

