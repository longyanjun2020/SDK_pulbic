
#ifndef __SA_LOG_H__
#define __SA_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Dump the infomation of a T_DB_TagStylePtr
 * \param attrHandle pointer of a T_DB_TagStylePtr
 * \return void
 */
void sa_log_DumpAttr(T_DB_TagStylePtr attrHandle);

/**
 * Log the infomation collocted
 * \param fmt format control
 * \param ... optional arguments
 * \return void
 */
void sa_log_Write(const uint8_t* fmt, ...);

/**
 * Dump string
 * \param string the pointer of the string to be dumped
 * \param name the specific name
 * \return void
 */
void sa_log_DumpString(int8_t* string, int8_t* name);

/**
 * Translate tag name macro to string
 * \param index the index of defined macro of tag
 * \return the string accordingly
 */
int8_t* sa_log_TransTagIndexToString(uint32_t index);

/**
 * Translate property name macro to string
 * \param index the index of the defined macro of property
 * \return the string accordingly
 */
int8_t* sa_log_TransPropertyIndexToString(uint32_t index);

#ifdef __cplusplus
}
#endif

#endif /* __SA_LOG_H__ */
