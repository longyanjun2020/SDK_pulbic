
typedef enum FileType
{
    WAV,
    AIFF,
    RAW
} FileType;

typedef enum    SampleType
{
    STEREO,
    INVERSE_STEREO,
    DOWNMIX_MONO,
    LEFT_CHANNEL_MONO,
    RIGHT_CHANNEL_MONO
} SampleType;

typedef struct SplInDef
{
    /* These may be set from the outside after openInput */

    SampleType      outputType;
    int             outputFreq;

    /* These may NOT be set from the outside */

    unsigned int    length;                         /* Length in samples */
    int             errcode;
//  FILE            * fp;
    unsigned int    samplesLeft;

    /* Input format. Output is always 16-bit signed. */

    int             freq;                           /* Hz */
    int             fReadStereo;                    /* TRUE = Read sample is in stereo */
    int             bits;                           /* Bits/sample (8 or 16). */
    int             fSign;                          /* Signed/unsigned */
    int             byteorder;                      /* LITTLE_ENDIAN or BIG_ENDIAN */
    FileType        filetype;                       /* WAV or AIFF */

    /* The following is only used by some formats */

    char            preReadBuffer[256];
    int             nPreReadBytes;

} SplIn;



int openInput( SplIn * psInfo, char * pFileName );
int readSamples( SplIn * psInfo, unsigned int nSamples, short * wpSamples );
int closeInput( SplIn * psInfo );

