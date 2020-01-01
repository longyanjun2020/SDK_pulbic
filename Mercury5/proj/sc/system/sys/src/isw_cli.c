#ifdef __I_SW_OS_G1__
#include "sys_MsWrapper_cus_os.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "cus_os_def.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "cus_os_event.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_MsWrapper_cus_os_mem.h"
extern u8 cyg_hal_plf_serial_getc(void* __ch_data);
#else
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "vm_types.ht"
#include "i_sw_uart.h"
#endif
#include "isw_cli.h"

#define CLIDEBUG(a) do{} while(0)
//	#define CLIDEBUG(a) cliPrintf a

#define _BZERO(dst, len) memset(dst, 0, len)
#define _BCMP(src1, src2, len) memcmp(src1, src2, len)
#define _ISUPPER(a) ((a)>='A' && (a)<='Z')
#define _ISLOWER(a) ((a)>='a' && (a)<='z')
#define _TOLOWER(a) ((a)|0x20)
#define _ISSPACE(a) ((a)==' ' || (a)=='\t')
#define _ISCNTRL(a) ((a)>=127 || ((a)<=31 && (a)!='\r' && (a)!='\n'))
#define _ISXDIGIT(a) (((a)>='0'&&(a)<='9') || ((a)>='a'&&(a)<='f') || ((a)>='A'&&(a)<='F'))
#define _ISDIGIT(a) (((a)>='0'&&(a)<='9'))

#define CLI_ROOT_PATH "/"
#define CLI_VERSION "0.0"
#define CLI_PROMPT ":>"
#define CLI_BANNER "M-Star I-SW Command Line Interface " CLI_VERSION "\n"
#define IS_PARSE_TOKEN_END(pTblx) ((pTblx)->pCmd==NULL)

static CliParseToken_t* _ptCurTokenTbl;
static CliParseToken_t* _ptRootTokenTbl;
static char _pszCurPath[CLI_MAX_PATH];
static char _szHistory[CLI_MAX_HISTORY][CLI_MAX_INBUF];
static int _nHisCount = 0;
static int _nHisIdx = 0;


static void _tokenCurPathSet (const char* path)
{
    strncpy(_pszCurPath, path, CLI_MAX_PATH);
}

static char* _tokenCurPathGet (void)
{
    return _pszCurPath;
}

static void _tokenCurTblSet (CliParseToken_t *pTbl)
{
    _ptCurTokenTbl = pTbl;
}

static CliParseToken_t * _tokenCurTblGet ()
{
    return _ptCurTokenTbl;
}

static void _tokenRootTblSet (CliParseToken_t *pTbl)
{
    _ptRootTokenTbl = pTbl;
}

static CliParseToken_t * _tokenRootTblGet ()
{
    return _ptRootTokenTbl;
}

void tokenInit(CLI_t *pCli)
{
    CLIDEBUG(("tokenInit -- pCli: %p\n", pCli));
    pCli->pToken = (char *) pCli->token;
    _BZERO((char *)pCli->token, sizeof(pCli->token));
    pCli->tokenIdx = 0;
    pCli->tokenLvl = 0;
    pCli->token_count = 0;
    pCli->parseTblIdx = 0;
    _BZERO((char *)&pCli->ParseTbl, sizeof(pCli->ParseTbl));
}

int CliTokenCount(CLI_t *pCli)
{
    int i, idx, cnt = 0;

    idx = pCli->tokenIdx;
    for (i = 0; i < CLI_MAX_TOKEN; i++)
    {
        if (pCli->token[idx])
        {
            cnt++;
        }
        idx = (idx + 1) % CLI_MAX_TOKEN;
    }
    return cnt;
}

char* CliTokenPop(CLI_t *pCli)
{
    int i, idx;

    idx = pCli->tokenIdx;
    for (i = 0; i < CLI_MAX_TOKEN; i++)
    {
        if (pCli->token[idx])
        {
            char *p;
            p = pCli->token[idx];
            pCli->token[idx] = 0;
            CLIDEBUG(("CliTokenPop %p -- %s, len: %d, cnt: %d\n", pCli, p, strlen(p), CliTokenCount(pCli)));
            return p;
        }
        idx = (idx + 1) % CLI_MAX_TOKEN;
    }
    return NULL;
}

char* CliTokenPopWoCase(CLI_t *pCli)
{
    int i, idx;

    idx = pCli->tokenIdx;
    for (i = 0; i < CLI_MAX_TOKEN; i++)
    {
        if (pCli->token[idx])
        {
            char *pBuf = (char *) pCli->ibuf;
            char *p = pCli->token[idx];
            char ch;

            pCli->token[idx] = 0;
            while (*p)
            {
                ch = *pBuf = *p;
                if (_ISUPPER(ch))
                { /* Convert upper to lower case */
                    *pBuf = ch - 'A' + 'a';
                }
                p++;
                pBuf++;
            }
            *pBuf = 0;
            pBuf = (char *) pCli->ibuf;
            CLIDEBUG(("CliTokenPopWoCase -- %s, len: %d, cnt: %d\n",
                                            pBuf, strlen(pBuf), CliTokenCount(pCli)));
            return pBuf;
        }
        idx = (idx + 1) % CLI_MAX_TOKEN;
    }
    return NULL;
}

void CliTokenPush(CLI_t *pCli, char *p)
{
    pCli->token[pCli->tokenIdx] = p;
    if (pCli->tokenIdx == 0)
    {
        pCli->pToken0 = p;
    }
    pCli->tokenIdx = (pCli->tokenIdx + 1) % CLI_MAX_TOKEN;
    CLIDEBUG(("CliTokenPush %p -- %s, len: %d, cnt: %d\n", pCli, p, strlen(p),
                                    CliTokenCount(pCli)));
}

int CliTokenCmp(char *p1, char *p2, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        if (_TOLOWER(p1[i]) != _TOLOWER(p2[i]))
        {
            return 1;
        }
    }
    return 0;
}

int cdCmdScan(CliParseToken_t *pTbl, const char* path)
{
    CliParseToken_t *pTblx;
    int bmatch;
    char* p;
    int len;

    if ('\0' == path[0])
    {
        return eCLI_PARSE_ERROR;
    }
    if ('/' == path[0])
    {
        if ('\0' != path[1])
            return cdCmdScan(_tokenRootTblGet(), path+1);
        else
        {
            _tokenCurTblSet(_tokenRootTblGet());
            _tokenCurPathSet(CLI_ROOT_PATH);
            return eCLI_PARSE_OK;
        }
    }

    p=strchr(path, '/');

    if (p!=NULL)
        len = p-path;
    else
        len = strlen(path);

    bmatch = 0;
    for (pTblx = pTbl; pTblx->pCmd; pTblx++)
    {
         if( (len==strlen(pTblx->pCmd)) && (0==_BCMP(pTblx->pCmd, path, len)))
         {
             if (pTblx->pNxtParseTbl != NULL)
             {
                 bmatch = 1;
                 break;
             }
         }
    }

    if (bmatch==0)
        return eCLI_PARSE_ERROR;

    if (p!=NULL)
        return cdCmdScan(pTblx->pNxtParseTbl, p+1);
    else
    {
        _tokenCurTblSet(pTblx->pNxtParseTbl);
        _tokenCurPathSet(pTblx->pCmd);
        return eCLI_PARSE_OK;
    }
}

int CliCdCmdScan(const char* path)
{
    return cdCmdScan(_tokenCurTblGet(), path);
}

int helpCmdScan(CliParseToken_t *pTbl, char *pTxt, char *pFilter, int verbose)
{
    CliParseToken_t *pTblx;
    char buf[132];
    int bmatch;
    bool found = FALSE;

    if (pTbl == NULL || pTxt == NULL)
    {
        return eCLI_PARSE_HELP_NOT_FOUND;
    }

    for (pTblx = pTbl; pTblx->pCmd; pTblx++)
    {
        if (verbose && pTblx->pNxtParseTbl)
        {
            sprintf(buf, "%s %s", pTxt, pTblx->pCmd);
            if (verbose > 0)
            {
                if (pFilter)
                {
                    bmatch = _BCMP(pTblx->pCmd, pFilter, strlen(pFilter));
                    if (bmatch == 0)
                    {
                        helpCmdScan(pTblx->pNxtParseTbl, buf, NULL, verbose-1);
                        found = TRUE;
                    }
                }
                else
                {
                    helpCmdScan(pTblx->pNxtParseTbl, buf, NULL, verbose-1);
                    found = TRUE;
                }
            }
        }
        else
        {
            if (pTblx->pHelpText)
            {
                if (pTblx->pNxtParseTbl && 0==verbose) // This is a sub-menu, and only show it.
                    sprintf(buf, " [%s]", pTblx->pCmd);
                else
                    sprintf(buf, "%s %s", pTxt, pTblx->pCmd);

                if (pFilter)
                {
                    bmatch = _BCMP(pTblx->pCmd, pFilter, strlen(pFilter));
                    if (bmatch == 0)
                    {
                        cliPrintf("%-35s -- %s\n", buf, pTblx->pHelpText ? pTblx->pHelpText : "");
                        if (pTblx->pUsageText)
                            cliPrintf("%s\n", pTblx->pUsageText);
                        found = TRUE;
                    }
                }
                else
                {
                    cliPrintf("%-35s -- %s\n", buf, pTblx->pHelpText ? pTblx->pHelpText : "");
                    found = TRUE;
                }
            }
        }
    }
    if (found == TRUE)
        return eCLI_PARSE_OK;
    else
        return eCLI_PARSE_HELP_NOT_FOUND;
}

int ClihelpCmdScan(char *pTxt, char *pFilter, int verbose)
{
    return helpCmdScan(_tokenCurTblGet(), pTxt, pFilter, verbose);
}


CliParseToken_t* _tokenFindMatch(CliParseToken_t *pTbl, char* cmd)
{
    CliParseToken_t *pTblx;
    int len = strlen(cmd);
    int match;

    CLIDEBUG(("cmd: %s, len: %d\n", cmd, strlen(cmd)));
    match = 0;
    for (pTblx = pTbl; pTblx->pCmd != NULL; pTblx++)
    {
        if (len == strlen(pTblx->pCmd) && CliTokenCmp(cmd, pTblx->pCmd, len) == 0)
        {
            CLIDEBUG(("Exact match found\n"));
            match = 1; /* exact match */
            break;
        }
    }

    if (match==1)
        return pTblx;
    else
        return NULL;
}

int _tokenParser(CLI_t *pCli, CliParseToken_t *pTbl, CliParseToken_t *pTblAux)
{
    char *p;
    char *pFilter;
    int rc;

    CLIDEBUG(("_tokenParser\n"));
    pCli->tokenLvl++;
    pCli->ParseTbl[pCli->parseTblIdx++] = pTbl;
    p = CliTokenPopWoCase(pCli);
    if (p)
    {
        CliParseToken_t *pTblx = _tokenFindMatch(pTbl, p);

        if (pTblx == NULL && pTblAux!=NULL)
            pTblx = _tokenFindMatch(pTblAux, p);

        if (pTblx != NULL)
        {
            pFilter = p;
            if (pTblx->fHandler)
            {
                rc = (*pTblx->fHandler)(pCli, p);
                if (rc != eCLI_PARSE_OK && pTblx->pUsageText)
                    cliPrintf("%s\n", pTblx->pUsageText);
            }
            else if (pTblx->pNxtParseTbl)
                rc = _tokenParser(pCli, pTblx->pNxtParseTbl, NULL);
            else
                rc = eCLI_PARSE_UNKNOWN;
            if (rc == eCLI_PARSE_NO_VALUE || rc == eCLI_PARSE_UNKNOWN || rc == eCLI_PARSE_INVALID_PARAMETER)
            {
                if (rc == eCLI_PARSE_INVALID_PARAMETER)
                {
                    helpCmdScan(pCli->ParseTbl[pCli->parseTblIdx - 1], "", NULL, 1);
                }
                else
                {
                    if (rc == eCLI_PARSE_UNKNOWN)
                    {
                        helpCmdScan(pCli->ParseTbl[pCli->parseTblIdx - 1], pTblx->pCmd, pFilter, 1);
                    }
                    else
                    {
                        helpCmdScan(pTblx->pNxtParseTbl, pTblx->pCmd, NULL, 1);
                    }
                }
                rc = (rc == eCLI_PARSE_NO_VALUE) ? eCLI_PARSE_TOO_FEW : eCLI_PARSE_ERROR;
            }
            return rc;
        }

        if (pCli->tokenLvl > 1)
        {
            cliPrintf("Invalid parameter: %s", p);
        }
        else
        {
            cliPrintf("Unknown command: %s", p);
        }

        while ((p = CliTokenPop(pCli)) != NULL)
        {
            cliPrintf(" %s", p);
        }
        cliPrintf("\n");

        CLIDEBUG(("parseTblIdx: %d\n", pCli->parseTblIdx));
        return pCli->tokenLvl <= 2 ? eCLI_PARSE_UNKNOWN : eCLI_PARSE_INVALID_PARAMETER;
    }
    return eCLI_PARSE_NO_VALUE;
}

int CliTokenPopNum(CLI_t *pCli, u32 *pV, int base)
{
    char *p;
    char *pEnd;

    pCli->tokenLvl++;
    p = CliTokenPop(pCli);
    if (p)
    {
        CLIDEBUG(("p: %s, len: %d\n", p, strlen(p)));
        //*pV = _strtoul(p, &pEnd, base);
        *pV = strtoul(p, &pEnd, base);
        CLIDEBUG(("*pEnd = %d\n", *pEnd));
        if (p == pEnd || *pEnd)
        {
            cliPrintf("Invalid input\n");
            return eCLI_PARSE_ERROR;
        }
        return eCLI_PARSE_OK;
    }

    cliPrintf("Error -- No value specified\n");
    return eCLI_PARSE_ERROR;
}

void CliReassembleToken(void *pCli, char * dst)
{
	int i;
	CLI_t * pCliTemp = pCli;
	char *p = dst;

	for (i = 0; i < pCliTemp->tokenIdx; i++)
	{
		if (pCliTemp->token[i])
		{
			int tokenlen;

			tokenlen = strlen(pCliTemp->token[i]);
			memcpy(p,pCliTemp->token[i],tokenlen);
			*(p + tokenlen) = ' ';//Add space
			p += (tokenlen + 1);
			CliTokenPop(pCliTemp);
		}
	}

	if(dst == p) {
		*p = 0;
	}
	else {
		*(p - 1) = 0;
	}
}

int CliGetChar(void)
{
#ifdef __I_SW_OS_G1__
    return cyg_hal_plf_serial_getc(NULL);
#else
    return get_char();
#endif
}

int _to_getstr(char* buf, int max_len,  int echo)
{
    int i, len;
    static char ch = '\0';
    u8 arrow_key_found=FALSE;

    len = 0;
    while (1)
    {
        buf[len] = (char) CliGetChar();

        if (27 == buf[len]) // to check key up/down
        {
            arrow_key_found = 1;
            continue;
        }
        if (1==arrow_key_found && 91==buf[len])
        {
            arrow_key_found = 2;
            continue;
        }
        if (2==arrow_key_found)
        {
            if (65==buf[len] || 66==buf[len])
            {
                for (i=0; i<len; i++)
                    cliPrintf("\b");
                for (i=0; i<len; i++)
                    cliPrintf(" ");
                for (i=0; i<len; i++)
                    cliPrintf("\b");
                _nHisIdx += (65==buf[len]) ? (-1) : 1;
                _nHisIdx = (_nHisIdx==-1) ? CLI_MAX_HISTORY-1 : _nHisIdx;
                _nHisIdx %= CLI_MAX_HISTORY;
                strcpy(buf, _szHistory[_nHisIdx]);
                len = strlen(_szHistory[_nHisIdx]);
                cliPrintf(buf);
            }
            arrow_key_found = 0;
            continue;
        }
        arrow_key_found = 0;

        // To ignore one for (\r,\n) or (\n, \r) pair
        if ((buf[len]=='\n'&&ch=='\r') || (buf[len]=='\r'&&ch=='\n'))
        {
            ch = '\0';
            continue;
        }
        ch = buf[len];
        if (ch=='\n' || ch=='\r')
        {
            if (echo)
                cliPrintf("\n");
            break;
        }
        if (len < (CLI_MAX_INBUF - 1))
        {
            if (ch == '\b') /* Backspace? */
            {
                if (len <= 0)
                    cliPrintf("\007");
                else
                {
                    cliPrintf("\b \b");
                    len --;
                }
                continue;
            }
            len++;
        }
        if (echo)
            cliPrintf("%c", ch);
    }
    buf[len] = '\0';
    return len;
}

int _parser(CLI_t *pCli, CliParseToken_t *pTbl, int echo)
{
    char buf[CLI_MAX_INBUF];
    char *pToken;
    int i, len;

    tokenInit(pCli);

    _to_getstr(buf, CLI_MAX_INBUF, echo);

    // to copy to history buffer
    len=strlen(buf);
    strcpy(_szHistory[_nHisCount], buf);
    for (i = 0; i < len; i++)
    {
        if (_ISSPACE(buf[i]))
            buf[i] = '\0';
        else if (_ISCNTRL(buf[i]))
            return eCLI_PARSE_INPUT_ERROR;
    }

    if (buf[0]=='\0') // to do nothing
        return eCLI_PARSE_OK;

    // A valid string => increase history
    _nHisCount = (_nHisCount+1)%CLI_MAX_HISTORY;
    _nHisIdx = _nHisCount;

    // To push the token into token stack
    pToken = NULL;
    for (i=0; i<len+1; i++) // take into account the last string end
    {
        if (buf[i] != '\0')
        {
            if (pToken == NULL)
                pToken = &buf[i];
        }
        else
        {
            if (pToken != NULL)
                CliTokenPush(pCli, pToken);
            pToken = NULL;
        }
    }

    return _tokenParser(pCli, pTbl, _tokenRootTblGet());
}

char welcome[] =
    "*********************************************************************************\n"
    " Welcome to CLI @@ (Command Line Interface).\n"
    "*********************************************************************************\n";

void cli(CLI_t *pCli, CliParseToken_t *rootTbl)
{
    int status;
    u8 i;

    cliPrintf(welcome);
    cliPrintf("\n\n");
    cliPrintf(CLI_BANNER);
    _tokenRootTblSet(rootTbl);
    _tokenCurTblSet(rootTbl);
    _tokenCurPathSet(CLI_ROOT_PATH);
    for (i=0; i<CLI_MAX_HISTORY; i++)
        _szHistory[i][0] = '\0';
    for (;;)
    {
        cliPrintf("\r\n%s%s", _tokenCurPathGet(), CLI_PROMPT);
        status = _parser(pCli, _tokenCurTblGet(), 1);
        if (status == eCLI_PARSE_QUIT)
        {
            break;
        }
        if (CliTokenCount(pCli) || status == eCLI_PARSE_TOO_MANY)
        {
            cliPrintf("Too many parameters!\n");
        }
        else if (status == eCLI_PARSE_TOO_FEW)
        {
            cliPrintf("Not enough parameters!\n");
        }
        else if (status == eCLI_PARSE_INVALID_PARAMETER)
        {
            cliPrintf("Invalid parameter!\n");
        }
        else if (status == eCLI_PARSE_INPUT_ERROR)
        {
            cliPrintf("Invalid input characters!\n");
        }
        else if (status == eCLI_PARSE_NO_VALUE)
        {
            cliPrintf("No parameter specified!\n");
        }
    }
}

#ifdef __TEST_LOAD__
#include "sys_sys.h"
#include "zlib.h"
#include "sys_MsWrapper_cus_os_int_pub.h"
#define CLI_BANNER_TESTLOAD "M-Star B5 Test Load " CLI_VERSION "\n"



void cli_test_load(CLI_t *pCli, CliParseToken_t *rootTbl)
{
	  u32 keypadmap = 0x00000000;
	  u32 resultmap = 0x00000000;
      MsIntMask_e ItMask;
	  //SYS_UDELAY(1000*1000);
	  cliPrintf(welcome);
    cliPrintf("\n\n");
    cliPrintf(CLI_BANNER_TESTLOAD);
    UartSendTrace("\n\r");
		UartSendTrace("--------------------------------------------------\n\r");
		UartSendTrace("Software Datecode :%s : %s\n\r",__DATE__,__TIME__);
		UartSendTrace("--------------------------------------------------\n\r");
		UartSendTrace("Function to test : \n\r");

#ifdef __FLASH_STRESS_LOOP__
	test_flash_loop();
#endif

	if(1)//((u32)sys_GetChipRevisionId()==(u32)CHIP_ID(B5, U01))
	{
    cliPrintf("\n 0. Boot ROM Test...\n");
	if ( 0x9bb5031b != zlib_crc32(0, 0x04000000, 102*1024) )
    {
        cliPrintf("\n Boot ROM Test Failed...\n");
        resultmap |=0x100;
    }
	}



    cliPrintf("\n 1. Memory(IMI BIST) Test...\n");
    if ( 1 == Imi_Test_Total() )
    {
        cliPrintf("\n IMI Test Failed...\n");
        resultmap |=0x01;
    }


    cliPrintf("\n 3. SDIO Test...\n");
    if (1 == CheckChipSdioStatus() )
    {
    	  cliPrintf("\n SDIO Test Failed...\n");
        resultmap |=0x10;
    }
    //MDrvStorageInitial(E_MODE_INTERPT);

    cliPrintf("\n 4. Keypad Test...\n");
    keypadmap = hIswKeypadAutoRunTest();
    if (0x0 != keypadmap)
    {
        cliPrintf("Keypad Test Failed: 0x%x\n", keypadmap);
        resultmap |=0x20;

    }


    cliPrintf("\n Bach Audio Test...\n");
    g_AudioTest2();


    cliPrintf("\n Display Test...\n");
    HalGpdWLedToggle(63);
    _DispEnPatgen(pCli, rootTbl);

    cliPrintf("\n 2. Memory(EMI BIST) Test...\n");
    if ( 1 == Emi_Test_Total() )
    {
        cliPrintf("\n EMI Test Failed...\n");
        resultmap |=0x02;
    }


    if ( 0x0 != resultmap )
    {
    	 cliPrintf("\n Test FAILED:%x...\n", resultmap);

    }
    else
    {
        cliPrintf("\n Test PASSED...\n");
    }

        // sotp ARM & WDT
	*(volatile u16*)0x74007c44=0xBABE     ;
	*(volatile u16*)0x74007c48=0x03       ;
	*(volatile u16*)0x34002c0c=0xDFF      ;
	*(volatile u16*)0x34002c10=0xDFF      ;


    while(1) ;
}
#endif //__TEST_LOAD__


