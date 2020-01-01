#ifndef __SYS_SYS_ISW_CLI_H__
#define __SYS_SYS_ISW_CLI_H__

#ifdef __I_SW_OS_G1__
#define cliPrintf diag_printf
#else
#ifdef __I_SW__
#define cliPrintf UartSendTrace
#else
#define cliPrintf
#endif
#endif
#define CLI_MAX_TOKEN 16
#define CLI_MAX_INBUF 80
#define CLI_MAX_PATH 80
#define CLI_MAX_HISTORY 8
#define ISW_CLI_TEST_ENABLE (1) //Disable all test function in formal release.

#if ISW_CLI_TEST_ENABLE
#define  JPE_UT_EN (1)
#define  MFE_UT_EN (1)
#define  DEMO_JPEG_TEST (1)
#else
#define  JPE_UT_EN (0)
#define  MFE_UT_EN (0)
#define  DEMO_JPEG_TEST (0)
#endif

enum
{
    eCLI_PARSE_ERROR = -1,
    eCLI_PARSE_OK = 0,
    eCLI_PARSE_NO_TBL = 1,
    eCLI_PARSE_NO_VALUE = 2,
    eCLI_PARSE_TOO_FEW = 3,
    eCLI_PARSE_TOO_MANY = 4,
    eCLI_PARSE_UNKNOWN = 5,
    eCLI_PARSE_INPUT_ERROR = 6,
    eCLI_PARSE_INVALID_PARAMETER = 7,
    eCLI_PARSE_HELP_NOT_FOUND = 8,
    eCLI_PARSE_QUIT = 99,
};

#define PARSE_TOKEN_DELIMITER { NULL, NULL, NULL, NULL, NULL}

typedef struct cli_s
{
    struct cli_parse_token_s *ParseTbl[CLI_MAX_TOKEN];
    int parseTblIdx;
    char *token[CLI_MAX_TOKEN];
    char *pToken;
    char *pToken0;
    int tokenIdx;
    int tokenLvl;
    int token_count;
    char ibuf[CLI_MAX_INBUF];
} CLI_t;

typedef struct cli_parse_token_s
{
    char *pCmd;
    char *pHelpText;
    char *pUsageText;
    int (*fHandler)(struct cli_s *, char *);
    struct cli_parse_token_s *pNxtParseTbl;
} CliParseToken_t;


int CliTokenCount(CLI_t *pCli);
char *CliTokenPop(CLI_t *pCli);
char *CliTokenPopWoCase(CLI_t *pCli);
void CliTokenPush(CLI_t *pCli, char *p);
int CliTokenCmp(char *p1, char *p2, int len);
int CliTokenPopNum(CLI_t *pCli, u32 *pV, int base);
void cli(CLI_t *pCli, CliParseToken_t *rootTbl);
int ClihelpCmdScan(char *pTxt, char *pFilter, int verbose);
int CliCdCmdScan(const char* path);
int CliGetChar(void);
void CliReassembleToken(void *pCli, char * dst);

#endif // __SYS_SYS_ISW_CLI_H__

