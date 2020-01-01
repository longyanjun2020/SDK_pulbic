
#ifndef CODEC_DOT_H
#define CODEC_DOT_H

typedef struct
{
  int     frequency;              /* 48000, 44100 and 32000 allowed. */
  int     mode;                   /* 0 = Stereo, 2 = Dual Channel, 3 = Mono */
  int     bitrate;                /* */
  int     emphasis;               /* 0 = None, 1 = 50/15 microsec, 3 = CCITT J.17 */
  int     fPrivate;
  int     fCRC;
  int     fCopyright;
  int     fOriginal;

} CodecInitIn;


typedef struct
{
    int         nSamples;
    int         bufferSize;
} CodecInitOut;


/*************************************************************************
*
*  Function:   MP3Enc_codecInit
*  Purpose:    MP3 encoder initialization
*
***************************************************************************/
extern  CodecInitOut * MP3Enc_codecInit( CodecInitIn * psInitData );

/*************************************************************************
*
*  Function:   MP3Enc_codecEncodeChunk
*  Purpose:    encode one frame
*
***************************************************************************/
extern  unsigned int MP3Enc_codecEncodeChunk( int nSamples, short * pSamples, char * pOutput );

/*************************************************************************
*
*  Function:   MP3Enc_codecExit
*  Purpose:    exit MP3 encoder
*
***************************************************************************/
extern  unsigned int  MP3Enc_codecExit( char * pOutput );

/*************************************************************************
*
*  Function:   MP3Enc_initSwStack
*  Purpose:    initialize working buffer.
*
***************************************************************************/
extern	void MP3Enc_initSwStack(void );


/*************************************************************************
*
*  Function:   MP3Enc_SetWorkingBuf
*  Purpose:    set mp3 encode working buffer.
*
***************************************************************************/
extern	int	MP3Enc_SetWorkingBuf(int *buf);

#endif

