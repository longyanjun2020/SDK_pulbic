/**********************************************************************
                        DNSe_VH_ver102a.h
***********************************************************************/

// Initialization
extern void DNSe_VH_Init( int Fs, int mode, int lfe );
// Setting parameters
extern void DNSe_VH_SetPar( int m3deff, int m3drvrb, int m3diadel, int belev, int befc, int db );
// Processing deinterleaved stream
extern void DNSe_VH( short* left, short* right, short **in, int n );
// Processing interleaved stream
extern void DNSe_VH_interleaved( short* out, short* in, int n );

