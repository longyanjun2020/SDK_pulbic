#ifndef __SQLITE_UT_H__
#define __SQLITE_UT_H__

//#define __USE_SQLITE_UT__  //Enable UT

#ifdef __USE_SQLITE_UT__

void SysSqlite_RunUT(void);

//For thread testing
#ifndef __STANDALONE__
void SysSqlite_CreateThread(void);
void SysSqlite_StartThread(void);
void SysSqlite_DestoryThread(void);
#endif //__STANDALONE__

#endif //__USE_SQLITE_UT__

#endif //__SQLITE_UT_H__
