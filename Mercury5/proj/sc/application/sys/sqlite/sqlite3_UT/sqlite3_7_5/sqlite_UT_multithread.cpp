#include "../sqlite3_UT/sqlite3_7_5/stdafx.h"

#include "sqlite_UT_multithread.h"

#define ALONGTIME   (1000)

void _SimulateBusyCase(void);
void _ExecuteSelectCmd(void);
void _ExecuteOpenDB(void);
void _TouchDB(void);

void _SimulateBusyCase()
{
    volatile int nStupid = 0;
    while(nStupid < 10000)
    {
        nStupid++;
    }
}

void _ExecuteSelectCmd(sqlite3 *pDb)
{
    //use an open connection and select
    wchar_t StrSQL[] = L"SELECT * FROM B";
    sqlite3_stmt *pStmt = NULL;
    const void *pMsg = 0;
    int nRc = 0;

    printf("B");
    nRc = sqlite3_prepare16(pDb, StrSQL, -1, &pStmt, &pMsg);
    ASSERT(SQLITE_OK == nRc || SQLITE_BUSY == nRc);
    if(SQLITE_OK == nRc)
    {
        nRc = sqlite3_step(pStmt);
        ASSERT(SQLITE_DONE == nRc || SQLITE_ROW == nRc || SQLITE_BUSY == nRc);
        if(SQLITE_BUSY != nRc)
        {
            sqlite3_finalize(pStmt);
        }
        else if(SQLITE_BUSY == nRc)
        {
            //ASSERT(0);
            printf("_ExecuteSelectCmd function happen busy case");
        }
    }
    else if(SQLITE_BUSY == nRc)
    {
        //ASSERT(0);
         printf("_ExecuteSelectCmd function happen busy case");
    }
}

void _ExecuteOpenDB()
{
    //open a new connection and select
    sqlite3 *pDb = NULL;
    int nRc = 0;
    ASSERT(SQLITE_OK == (nRc = sqlite3_open16(L"testdb", &pDb)));
    sqlite3_busy_timeout(pDb, ALONGTIME);
    _ExecuteSelectCmd(pDb);
    sqlite3_close(pDb);
}

//open a connection and select
DWORD WINAPI ThreadA(LPVOID)
{
    while(1)
    {
        Sleep(7);
        sqlite3 *pDb = 0;
        char StrSQL[] = "SELECT * FROM A";
        sqlite3_stmt *pStmt = NULL;
        const void *pMsg = 0;
        int nRc = 0;

        printf("A");
        ASSERT(SQLITE_OK == (nRc = sqlite3_open16(L"testdb", &pDb)));
        sqlite3_busy_timeout(pDb, ALONGTIME);
        nRc = sqlite3_prepare16(pDb, StrSQL, -1, &pStmt, &pMsg);
        if(SQLITE_OK == nRc)
        {
            nRc = sqlite3_step(pStmt);
            ASSERT(SQLITE_DONE == nRc || SQLITE_ROW == nRc);
            _SimulateBusyCase();

            _ExecuteOpenDB(); //call a function that may query the db

            _SimulateBusyCase();
            sqlite3_finalize(pStmt);
        }
        else if(SQLITE_BUSY == nRc)
        {
            //ASSERT(0);
            printf("ThreadA function happen busy case");
        }

        sqlite3_close(pDb);
    }
}

void _TouchDB()
{
    static int nCounter = 0;
    sqlite3 *pDb = 0;
    char *StrSQL = NULL;
    char *pMsg = 0;
    int nRc = 0;

    assert(SQLITE_OK == (nRc = sqlite3_open16(L"testdb", &pDb)));
    sqlite3_busy_timeout(pDb, ALONGTIME);
    printf("C(%d)", nCounter);
    StrSQL = sqlite3_mprintf("INSERT INTO C VALUES(%d);", nCounter++);
    nRc = sqlite3_exec(pDb, StrSQL, 0, 0, &pMsg);
    if(SQLITE_OK == nRc)
    {

    }
    else if(SQLITE_BUSY == nRc )
    {
        //ASSERT(0);
        printf("_TouchDB function happen busy case");
    }
    sqlite3_close(pDb);
}

DWORD ThreadB(LPVOID)
{
    while(!kbhit())
    {
        Sleep(3);
        _TouchDB(); //touch the db
    }
    return 0;
}

void MakeDB()
{
    sqlite3 *pDb = 0;
    char StrSQL[] = "DROP TABLE IF EXISTS A;"
        "DROP TABLE IF EXISTS B;"
        "DROP TABLE IF EXISTS C;"
        "CREATE TABLE A(ID INTEGER PRIMARY KEY);"
        "CREATE TABLE B(ID INTEGER PRIMARY KEY);"
        "CREATE TABLE C(ID INTEGER PRIMARY KEY);"
        "INSERT INTO A VALUES(1);"
        "INSERT INTO B VALUES(2);";
    char *pMsg = 0;
    int nRc = 0;

    if (SQLITE_OK == (nRc = sqlite3_open16(L"testdb", &pDb)))
    {
        sqlite3_busy_timeout(pDb, ALONGTIME);
        nRc = sqlite3_exec(pDb, StrSQL, 0, 0, &pMsg);
        nRc = sqlite3_close(pDb);
    }
}
