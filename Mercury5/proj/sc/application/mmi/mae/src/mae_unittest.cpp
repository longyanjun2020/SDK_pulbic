#define __SFILE__ "mae_unittest.cpp"

#include "mmi_mae_platform_def.h"
#include "mmi_mae_unittest_data.h"

#if defined (__SDK_SIMULATION__)

#include <windows.h>

#define MAX_HOOK_REC	100
DWORD HookFunctions[MAX_HOOK_REC] = {0}; 

void HotPatch(void *oldProc, void *newProc)
{
    DWORD	oldProtect = 0;

    WORD* pJumpBack = (WORD*)oldProc;
    BYTE* pLongJump = ((BYTE*)oldProc-5);
    DWORD* pLongJumpAdr = ((DWORD*)oldProc-1);

    VirtualProtect(pLongJump, 20, PAGE_EXECUTE_WRITECOPY, &oldProtect);

    if ((0xff8b == *pJumpBack) && 
        (0xcc == *pLongJump) &&
        (0xcccccccc == *pLongJumpAdr))
    {
		int i = 0;
		for (i=0;i<MAX_HOOK_REC;i++)
		{
			if (0 == HookFunctions[i])
			{
				HookFunctions[i] = (DWORD)oldProc;
				break;
			}
		}
        *pLongJump = 0xE9;	// long jmp
        *pLongJumpAdr = ((DWORD)newProc)-((DWORD)oldProc);
        *pJumpBack = 0xF9EB; //JMP EB     jump back 5 bytes
    }
    VirtualProtect(pLongJump, 20, oldProtect, &oldProtect);
}

void HotUnpatch(void*oldProc)
{
    DWORD	oldProtect = 0;

    WORD* pJumpBack = (WORD*)oldProc;
    BYTE* pLongJump = ((BYTE*)oldProc-5);
    DWORD* pLongJumpAdr = ((DWORD*)oldProc-1);

    VirtualProtect(pJumpBack, 2, PAGE_EXECUTE_WRITECOPY, &oldProtect);

    if (0xF9EB == *pJumpBack)
    {
		int i = 0;
		for (i=0;i<MAX_HOOK_REC;i++)
		{
			if (HookFunctions[i] == (DWORD)oldProc)
			{
				HookFunctions[i] = 0;
				break;
			}
		}
        *pJumpBack = 0xff8b;		// mov edi, edi = nop
		*pLongJump = 0xcc;
		*pLongJumpAdr = 0xcccccccc;
    }

    VirtualProtect(pJumpBack, 2, oldProtect, &oldProtect);
}

void HotUnpatch_all(void)
{
	int i = 0;
	for (i=0;i<MAX_HOOK_REC;i++)
	{
		if (HookFunctions[i])
		{
			HotUnpatch((void*)HookFunctions[i]);
			HookFunctions[i] = 0;
		}
	}
}


void Query_HookFunc_Data(HOOKFUNC_DATA *FuncData)
{
    HOOKFUNC_DATA_QUERY_RST ret = HOOKFUNC_DATA_QUERY_FAIL;

    if ( (!FuncData->fp) || (!FuncData->QueryDataName) || (!FuncData->result)) 
    {
        if (FuncData->result)
            *(FuncData->result) = HOOKFUNC_DATA_QUERY_FAIL;
        return;
    }
    if (HOOKFUNC_DATA_INT == FuncData->nFuncDataType)
    {
        if (!FuncData->IntData)
        {
            *(FuncData->result) = HOOKFUNC_DATA_QUERY_FAIL;
            return;
        }
    }
    if (HOOKFUNC_DATA_STR == FuncData->nFuncDataType)
    {
        if (!FuncData->StrData || FuncData->StrBufSize <= 0 || !FuncData->StrLen)
        {
            *(FuncData->result) = HOOKFUNC_DATA_QUERY_FAIL;
            return;
        }
    }
    MKernel_SendQueryHookFuncData((void *)FuncData, sizeof(HOOKFUNC_DATA));
    return;

}

#endif
