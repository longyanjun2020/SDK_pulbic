/*

  Synthesizer and Sequencer APIs
			Copyright(c) Faith,Inc.. 2007		All Rightes Reserved.

*/
#ifndef _FAITHAPI_H
#define _FAITHAPI_H
#ifdef __cplusplus
extern "C"{
#endif

#define FAITHSYNTH_MAXVOICE			32	// number of polyphony
//#define FAITHSYNTH_MAXVOICE			64	// number of polyphony
#define FAITHSYNTH_SAMPLERATE 	32000	// [Hz]
#define FAITHSYNTH_BLOCKSIZE		2048	// [sample]  1024[sample] = 2048[byte]
#define MIDI_CONVOUT_BLOCKSIZE MIDI_CONVBUFSIZE

#define MIDI_EVENT_BYTES 4
#define READBYTES_FROM_GAME 12
#define STREAMBUFSIZE 1200 // must be multiple of READBYTES_FROM_GAME, max is (MIDI_TRACKPOOLBUFSIZE - 128)

#define MIDIGAME_IMMEDIATE_PLAY


//#define BLOCK_STREAM_ENABLE
#ifdef BLOCK_STREAM_ENABLE
#define SEGMENT_STREAM
#endif

#define SEGMENT_STREAM //ccc
#ifdef SEGMENT_STREAM
#define MIDI_CONV_THREAD //ccc
#endif

int FaithAPI_SynthInit( void (*ledCallback)(void*,int), void (*vibCallback)(void*,int), void (*lcdCallback)(void*,int), void *callbackParam );

void FaithAPI_SynthExit(void);

int FaithAPI_Proc( short *pBuf );
int FaithAPI_Proc_game( short *pBuf );

void FaithAPI_SeqSetLoop( int doLoop );


int FaithAPI_SeqGetState(void);


int FaithAPI_SeqSetFile( void* pImg, unsigned long nImgLength );
int FaithAPI_SeqSetFile_game( void* pImg, unsigned long nImgLength );



void FaithAPI_SeqUnsetFile(void);


int FaithAPI_SeqPlay(void);


int FaithAPI_SeqStop(void);


int FaithAPI_SeqSeek( unsigned long timeMSEC );


unsigned long FaithAPI_SeqGetPos(void);



#ifdef __cplusplus
}
#endif
#endif
