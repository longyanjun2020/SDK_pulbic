// sqlite3_7_5.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "sqlite_porting.h"
#include "sqlite3_priv.h"
#include "sqlite_UT.h"
#include <assert.h>
#include <iostream>
#include "sqlite_UT_multithread.h"

using namespace std;

//#define __TEST_MULTITHREAD__

#ifdef __STANDALONE__
extern "C" {
extern IOStatus_t g_tIOStatus;
extern MemoryStatus_t g_tMemoryStatus;
}
#endif

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef __USE_SQLITE_UT__
    SysSqlite_RunUT();
#endif

    cout<<"IO Status:\n"<<
        "Open:"<<g_tIOStatus.nOpenCounter<<endl<<
        "Close:"<<g_tIOStatus.nCloseCounter<<endl<<
        "Read:"<<g_tIOStatus.nReadCounter<<endl<<
        "Write:"<<g_tIOStatus.nWriteCounter<<endl<<endl;

    cout<<"Memory Status:\n"<<
        "Peak:"<<g_tMemoryStatus.nPeak<<endl<<
        "CurrentUsed:"<<g_tMemoryStatus.nCurrentUsed<<endl<<
        "UnFreedMemCounter:"<<g_tMemoryStatus.nMemCounter<<endl<<endl;
    ASSERT(g_tMemoryStatus.nMemCounter==0); // Check memory leak


#ifdef __TEST_MULTITHREAD__
    MakeDB(); //make the database the first time
    CreateThread(NULL, 0, &ThreadA, 0, 0, NULL);
    ThreadB(NULL);
#endif

	return 0;
}
