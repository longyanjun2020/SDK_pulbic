#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "sqlite3_priv.h"

DWORD WINAPI ThreadA(LPVOID);
DWORD ThreadB(LPVOID);
void MakeDB();
