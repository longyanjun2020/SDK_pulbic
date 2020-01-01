

#if !defined(ES_TEAM__2008_11_11__ESR__H)
#define ES_TEAM__2008_11_11__ESR__H

#include "ivPlatform.h"
#include "ivDefine.h"
#include "ivEsrErrorCode.h"
#include "ivEsrParam.h"
#include "ivESRSDKID.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define ivESR_CP_GBK					936		/* GBK (default) */
#define ivESR_CP_BIG5					950		/* Big5 */
#define ivESR_CP_UTF8					65001	/* UTF-8 */
#define ivESR_CP_GB18030				ivESR_CP_GBK

typedef ivUInt16 ivEncoding;

/* Format resident buffer */
ivESRStatus ivCall EsrResidentBufferFormat(
	ivPointer pResidentBuffer,						/* Pointer to resident buffer */
	ivSize nResidentBufferBytes						/* Size of resident buffer */
	);

#define EsrCreate(phEsrObj, pUserSys, pResPackDesc, pResPackCount) \
	EsrCreateG(phEsrObj, pUserSys, pResPackDesc, pResPackCount, AITALK22_SDK_USERID)

/* Create ESR object */
ivESRStatus ivCall EsrCreateG(
	ivHandle ivPtr	phEsrObj,						/* To hold the ESR object handle */
	ivPUserSys		pUserSys,						/* Description of the user's system environment */
	ivPResPackDesc	pResPackDesc,					/* Description of resource pack */
	ivSize			nResPackCount,					/* Number of resource pack description */
	ivCStrA			pUserID							/* SDK User ID */
	);

/* Destroy ESR object */
ivESRStatus ivCall EsrDestroy(
	ivHandle		hEsrObj							/* The ESR object handle */
	);

/* Set ANSI Codepage */
ivESRStatus ivCall EsrSetACP(
	ivHandle hEsrObj,								/* The ESR object handle */ 
	ivUInt16 nEncoding								/* ANSI Codepage: ivESR_CP_GBK ivESR_CP_BIG5 ivESR_CP_UTF8 ivESR_CP_GB18030 */
	);


/* Begin to make a lexicon(dictionary) */
ivESRStatus ivCall EsrBeginLexiconA(
	ivHandle		hEsrObj,						/* The ESR object handle */
	ivCStrA			lpName							/* Name of the lexicon (ANSI String) */
	);

/* Begin to make a lexicon(dictionary) */
ivESRStatus ivCall EsrBeginLexiconW(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivCStrW lpName									/* Name of the lexicon (UTF-16 String) */
	);

/* Add one lexicon item(word) to the lexicon */
ivESRStatus ivCall EsrAddLexiconItemA(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivCStrA lpContent,								/* Text of the word (ANSI String) */
	ivUInt32 nID									/* Word ID */
	);

/* Add one lexicon item(word) to the lexicon */
ivESRStatus ivCall EsrAddLexiconItemW(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivCStrW lpContent,								/* Text of the word (UTF-16 String) */
	ivUInt32 nID									/* Word ID(Assigned by user) */
	);

/* Finish making the lexicon */
ivESRStatus ivCall EsrEndLexicon(
	ivHandle		hEsrObj							/* The ESR object handle */
	);

/* Begin to make a scene */
ivESRStatus ivCall EsrBeginSceneA(
	ivHandle hEsrObj,								/* The ESR object handle */ 
	ivCStrA lpName									/* Name of the scene (ANSI String) */
	);

/* Begin to make a scene */
ivESRStatus ivCall EsrBeginSceneW(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivCStrW lpName									/* Name of the scene (UTF-16 String) */
	);

/* Add one scene item(syntax) to the scene */
ivESRStatus ivCall EsrAddSyntaxA(
	ivHandle		hEsrObj,						/* The ESR object handle */
	ivCStrA			pSyntaxDesc,					/* Text of the syntax description (ANSI String) */
	ivUInt32		nID								/* Syntax ID(Assigned by user) */
	);

/* Add one scene item(syntax) to the scene */
ivESRStatus ivCall EsrAddSyntaxW(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivCStrW pSyntaxDesc,							/* Text of the syntax description (UTF-16 String)*/
	ivUInt32 nID									/* Syntax ID(Assigned by user) */
	);

/* Finish making the scene */
ivESRStatus ivCall EsrEndScene(
	ivHandle hEsrObj								/* The ESR object handle */
	);

/* Start speech recognition */
ivESRStatus ivCall EsrStartA(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivCStrA lpName									/* Name of the scene made by user(ANSI String) */
	);

/* Start speech recognition */
ivESRStatus ivCall EsrStartW(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivCStrW lpName									/* Name of the scene made by user(UTF-16 String) */
	);

/* Speech recognition reset */
ivESRStatus ivCall EsrEngineReset(
	ivHandle		hEsrObj							/* The ESR object handle */
	);

/* Append audio data to ESR object */
ivESRStatus ivCall EsrAppendData(
	ivHandle		hEsrObj,						/* The ESR object handle */
	ivCPointer		pData,
	ivSize			nDataSamples
	);

/* Stop speech recognition */
ivESRStatus ivCall EsrStop(
	ivHandle		hEsrObj							/* The ESR object handle */
	);

/* Run one step of recognition */
ivESRStatus ivCall EsrRunStep(
	ivHandle		hEsrObj							/* The ESR object handle */
	);

/* Get syntax result */
ivESRStatus ivCall EsrGetResultSyntax(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivPUInt32 pnSyntaxID							/* To keep syntax ID result */
	);

/* Get lexicon result in syntax */
ivESRStatus ivCall EsrGetResultParameterA(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivPUInt32 ivPtr ppCmdID,						/* To keep result word ID list pointer */ 
	ivPUInt32 pnSame,								/* To keep number of same ID */
	ivCStrA pName									/* Name of lexicon)(ANSI String) */
	);

/* Get parameter(lexicon in syntax) result */
ivESRStatus ivCall EsrGetResultParameterW(
	ivHandle hEsrObj,								/* The ESR object handle */
	ivPUInt32 ivPtr ppCmdID,						/* To keep result word ID list pointer*/
	ivPUInt32 pnSame,								/* To keep number of same ID */
	ivCStrW pName									/* Name of lexicon(UTF-16 String) */
	);

/* Set ESR system parameter */
ivESRStatus ivCall EsrSetParam(
	ivHandle		hEsrObj,						/* The ESR object handle */
	ivUInt32		nParamID,						/* Parameter ID */
	ivCPointer		nParamValue						/* Parameter value */
	);

/* Get SDK version */
ivESRStatus ivCall EsrGetVersion(
	ivPUInt8		piMajor,						/* Main version */
	ivPUInt8		piMinor,						/* Sub version */
	ivPUInt16		piRevision						/* Build version */
	);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ES_TEAM__2008_11_11__ESR__H */
