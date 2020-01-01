#ifndef _zm_app_config_h_
#define _zm_app_config_h_

#include "zm_typedef.h"

typedef struct
{
	const unsigned char*	m_app;
	int						m_length;
}zm_fixedapp;

/**
 * 获取固化应用个数
 */
zm_extern zm_int zm_get_fixedapp_count(zm_void);

/**
 * 获取固化应用
 */
zm_extern const zm_fixedapp* zm_get_fixedapp(zm_int idx);

#endif//_zm_app_config_h_
