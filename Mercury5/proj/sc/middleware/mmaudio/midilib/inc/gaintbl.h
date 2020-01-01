#if 0
extern const short tblGain[];
extern const unsigned short tblGainPan[];


#define TBL_GAIN_G( i )     ( tblGain[ (int)(i) ] )
#define TBL_GAIN_ZERO()     ( tblGain[ 0 ] )
#define TBL_GAIN_NRM()      ( tblGain[ 127 ] )
//#define TBL_GAIN_CUR( i )   ( ( (long)( tblGain[ i ] ) ) << 16 )
#define TBL_GAIN_CUR( i )   ( tblGain[ (int)(i) ] )
#define TBL_GAIN_MUL( a, b )    \
        (short)( ( ( (long)(a) ) * ( (long)(b) ) ) >> 15 )

#define TBL_GAIN_PANL( i )  tblGainPan[ 64 - (i) ]
#define TBL_GAIN_PANR( i )  tblGainPan[ 64 + (i) ]

#else
//extern short midiGaintbl[256];
extern short *gU8MIDIGaintblPtr;

#define TBL_GAIN_G( i )     *((short *)gU8MIDIGaintblPtr+(int)(i))
#define TBL_GAIN_ZERO()     *((short *)gU8MIDIGaintblPtr)
#define TBL_GAIN_NRM()      *((short *)gU8MIDIGaintblPtr+127)
//#define TBL_GAIN_CUR( i )   ( ( (long)( tblGain[ i ] ) ) << 16 )
#define TBL_GAIN_CUR( i )   *((short *)gU8MIDIGaintblPtr+(int)(i))
#define TBL_GAIN_MUL( a, b )    \
        (short)( ( ( (long)(a) ) * ( (long)(b) ) ) >> 15 )

#define TBL_GAIN_PANL( i )  *(((unsigned short *)gU8MIDIGaintblPtr+128)+64-i)
#define TBL_GAIN_PANR( i )  *(((unsigned short *)gU8MIDIGaintblPtr+128)+64+i)
#endif
