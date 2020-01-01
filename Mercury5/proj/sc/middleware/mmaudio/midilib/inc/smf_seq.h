#ifndef	_smf_seq_h_
#define	_smf_seq_h_

/*	max. SMF track	*/
#define	MAX_SMF_TRK	40
/*	Sys. Exclusive Buffer length.	*/
#define	SYS_EXC_MAX_LEN	16
/*	Max. number of Audio stream Chunk    */
//#define	MAX_AUD_CHUNK	16

#define	FSP_DEFAULT_TEMPO	0x10000

/********************* SMF ********************/
/*	STATUS */
#define	SMF_META	0xff
#define	SMF_EXC		0xf0
#define	SMF_RAW		0xf7
/* Meta Number */
#define	SMF_META_EOT	0x2f
#define	SMF_META_TEMPO	0x51
#define	SMF_META_TEXT	0x03
/********************* MIDI *******************/
#define	MIDI_NOTEOFF	0x80
#define	MIDI_NOTEON		0x90
#define	MIDI_POLYPRESS	0xa0
#define	MIDI_CTRLCHG	0xb0
#define	MIDI_PRG_CHG	0xc0
#define	MIDI_CHPRESS	0xd0
#define	MIDI_PITCHBEND	0xe0
#define	MIDI_EXC	0xf0
#define	MIDI_MAX_CH		16
#define	MIDI_MAX_KEY	128
#define	MIDI_CC_HOLD	0x40
#define	MIDI_CC_ASOFF	120
#define	MIDI_CC_RSTCTRL	121
#define	MIDI_CC_ANOFF	123
#define MIDI_META_AUD_START		0x10
#define MIDI_META_AUD_STOP		0x11
#define MIDI_META_AUD_VOLUME	0x12
#define MIDI_META_AUD_REVERB	0x13

typedef enum {
	fspEr_NoError=0,			/*	成功 */
	fspEr_Bussy=400,			/*	プ?イ?がこのＡＰＩを実行できない状態 */
	fspEr_Format=401,			/*	SMF フォーマットエ?ー */
	fspEr_NotSuport=402,	/*	サポートされていない SMF フォーマット */
	fspEr_OverRun=403,		/*	SMF?に記述されているサイズに対し実データ長が短い */
	fspEr_DataEnd=404,		/*	現在位置がデータの終端 */
	fspEr_ConvOpenErr=405
} fspErrorCode;

typedef enum {
	fspStat_Wait=0,		/*	?期化直後の SMF が登録されていない状態  */
	fspStat_Ready=1,	/*	SMF が登録され?奏可能で?るが停止?の状態  */
	fspStat_Run=2,		/*	?奏?  */
	fspStat_Seek=3,		/*	位置移動?  */
	fspStat_End=4,
	fspStat_Error=-1	/*	エ?ーが発生し、??続行不可能な状態  */
/*	fspSetSmf() により fspStat_Ready へ移行する?で
  	エ?ー状態は解?される   */
} fspStat;

enum _FAITH_FILEKIND {
	FILEKIND_SMF = 0,
	FILEKIND_IMELODY,
	FILEKIND_INVALID
};


#ifdef __cplusplus
extern "C"{
#endif

fspErrorCode fspInitSeq(void *_hSynth, void (*_ledCallback)(void*,int), void (*_vibCallback)(void*,int), void (*_lcdCallback)(void*,int), void *_paramCallback );
void fspExitSeq(void);
fspErrorCode fspSetSmf(void *smf, unsigned int length, unsigned long *pTimebase, int *pFilekind );
//void fspUnsetSmf(void);
fspErrorCode fspSetSmf_game(void *smf, unsigned int length, unsigned long *pTimebase, int *pFilekind );

fspStat fspGetStat(void);
fspStat fspSeqProc(unsigned int elTime, long *pTick);
fspStat fspSeqProc_game(unsigned int elTime, long *pTick);


/*
	?奏開始
	状態が fspStat_Ready の?にのみ実効可能
	エ?ーコードとしてfspEr_DataEndが返ってきた場?は
	現在位置がデータの終端で?ることを示す
*/
fspErrorCode fspPlay(void);

/*
	?奏の停止
*/
fspErrorCode fspStop(void);

/*
	現在位置の取得
	状態が fspStat_Wait, fspStat_Seek, fspStat_Error の場?には
	返り値は保証されない
	位置は曲の先頭からの絶対位置を単位ミ?秒で返す
	誤差は SMF の 1delta (1 tick) 以内で常に多きなる方向に誤差を?つ
*/
unsigned long fspGetCurPosition(void);

/*
	移調量の指定
	半音単位で元調からの移調量を指定する
*/
//fspErrorCode fspSetTransPose(int transpose);

/*
	テ?ポの変更
	元テ?ポに対する変化率を指定する
	FSP_DEFAULT_TEMPO で 元テ?ポ
	元テ?ポ　の 90% にしたい場?は

	(FSP_DEFAULT_TEMPO*90)/100 を引?に与える
*/
//void fspSetTempo(unsigned int tempoModyfy);

/*
	?奏位置の移動（曲の先頭からの絶対位置）（単位ミ?秒）
	状態が fspStat_Ready の?にのみ実効可能
*/
fspErrorCode fspSeek(unsigned long ms_time);
/*
	?奏位置の移動（曲の先頭からの絶対位置）（単位ステップ／ティック）
	状態が fspStat_Ready の?にのみ実効可能
*/
fspErrorCode fspSeekByTick(unsigned long tick_time);

/*
	現在位置の取得
	状態が fspStat_Wait, fspStat_Seek, fspStat_Error の場?には
	返り値は保証されない
	位置は曲の先頭からの絶対位置を単位ステップ／ティックで返す
*/
unsigned long fspGetCurTick(void);

//char* fspGetTitle( int *pLength );

void fspSeqProcRestart(void);
void fspUnsetSmf(void);

#ifdef __cplusplus
}
#endif
#endif
