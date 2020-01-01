/*----------------------------------------------+
 |												|
 |	ivESRParam.h - ESR 2 Parameter 	Defination	|
 |												|
 |		Copyright (c) 1999-2008, iFLYTEK Ltd.	|
 |		All rights reserved.					|
 |												|
 +----------------------------------------------*/

#ifndef IFLYTEK_VOICE__ESRPARAM__H
#define IFLYTEK_VOICE__ESRPARAM__H

#define ES_PARAM_SENSITIVITY			(1)
#define SENSITIVITY_SENSITIVE		    ((ivCPointer)0)
#define SENSITIVITY_ACTIVE				((ivCPointer)1)
#define SENSITIVITY_NORMAL			    ((ivCPointer)2)
#define SENSITIVITY_PRECISE		    	((ivCPointer)3)
#define SENSITIVITY_STRICT  		    ((ivCPointer)4)
	
	/* Default sensitivity */
	#define ES_DEFAULT_SENSITIVITY		SENSITIVITY_ACTIVE

#define ES_PARAM_RESPONSETIMEOUT		(2)
	#define ES_DEFAULT_RESPONSETIMEOUT	((ivCPointer)0)		/* No response timeout */

#define ES_PARAM_SPEECHTIMEOUT			(3)
	#define ES_DEFAULT_SPEECHETIMEOUT	((ivCPointer)0)		/* No speech timeout */

#define ES_PARAM_SPEECHSTARTNOTIFY		(4)
	#define ES_SPEECHSTARTNOTIFY_ON		((ivCPointer)ivTrue)	
	#define ES_SPEECHSTARTNOTIFY_OFF	((ivCPointer)ivFalse)	
	#define ES_DEFAULT_SPEECHSTARTNOTIFY	ES_SPEECHSTARTNOTIFY_OFF	/* No speech start notify */

#define ES_PARAM_ENHANCEVAD				(5)
	#define ES_ENHANCEVAD_ON			((ivCPointer)ivTrue)
	#define ES_ENHANCEVAD_OFF			((ivCPointer)ivFalse)
	#define ES_DEFAULT_ENHANCEVAD		ES_ENHANCEVAD_ON

#define ES_PARAM_RECORDSKIP				(6)
#define ES_DEFAULT_RECORDSKIP			((ivCPointer)0)		/* No skip */

#endif /* !IFLYTEK_VOICE__ESRPARAM__H*/
