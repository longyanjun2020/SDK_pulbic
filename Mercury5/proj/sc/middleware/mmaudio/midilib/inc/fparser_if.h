/*
 * Copyright(c) Faith,Inc.  All Rights Reserved.
 *
 * $Revision: 1.2 $
 */
 
/** @file
 *  @brief This header file contains the interface definition for a FParser module
 *
 */

#ifndef CORE_FPARSER_IF_H__
#define CORE_FPARSER_IF_H__


#include "fsystem_types.h"

typedef struct {
	

	const u_8*            data_buf;

	fsize_t               data_size;


	u_32				  option;


} fparser_init_param_t;



#define	FPARSER_OPTION_DEFAULT               (0)



#define FPARSER_OPTION_DISABLE_MFI4          (1<<0)

#define FPARSER_OPTION_ENABLE_SMFFORIMODE    (1<<1)

#define FPARSER_OPTION_ENABLE_EXTRA_DATA	 (1<<2)


#define FPARSER_OPTION_ENABLE_LINEAR_VOLUME	 (1<<3)

#define FPARSER_OPTION_ENABLE_XMF1          (1<<4)


#define FPARSER_RESULT_SUCCESS                      (0)


#define FPARSER_RESULT_ERROR_ILLEGAL_PARAMETER      (-(0x0100))

#define FPARSER_RESULT_ERROR_MELODY_BUFFER          (-(0x0200))


#define FPARSER_RESULT_ERROR_ILLEGAL_FORMAT         (-(0x0300))


#define FPARSER_RESULT_ERROR_PARSE_END              (-(0x0400))

#define FPARSER_RESULT_ERROR_CANNOT_FIND_FORMAT     (-(0x0500))


typedef int fparser_result_t;


typedef struct  {

	fparser_result_t     (*open) (fhandle_t work_memory, const fparser_init_param_t* init_param);

	fparser_result_t     (*close) (fhandle_t work_memory);

	fparser_result_t     (*proc) (fhandle_t work_memory);

	fparser_result_t     (*reset) (fhandle_t work_memory, int is_repeat_flag);

	fparser_result_t     (*get_next_time) (fhandle_t work_memory);

	fparser_result_t     (*find_format) (const u_8 *data, fsize_t size);


}fparserif_t;


#define FPARSER_DEFAULT_TEMPO                     (60000000)

typedef enum{
	FPARSER_CBIF_RESULT_ERROR       = -1,
	FPARSER_CBIF_RESULT_BREAK       = 0,
	FPARSER_CBIF_RESULT_CONTINUE    = 1
} fparser_cbif_result_t;


#endif /* CORE_FPARSER_IF_H__ */
