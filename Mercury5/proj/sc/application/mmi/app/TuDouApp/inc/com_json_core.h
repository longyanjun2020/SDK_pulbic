/* See JSON_parser.c for copyright information and licensing. */

#ifndef __SP_JSON_CORE_H__
#define __SP_JSON_CORE_H__


#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Windows DLL stuff */

#define IMP_Assert  /\
/

#define JSON_PARSER_DLL_API

/* Determine the integer type use to parse non-floating point numbers */
typedef long JSON_int_t;
#define JSON_PARSER_INTEGER_SSCANF_TOKEN "%ld"
#define JSON_PARSER_INTEGER_SPRINTF_TOKEN "%ld"


typedef enum
{
    JSON_E_NONE = 0,
    JSON_E_INVALID_CHAR,
    JSON_E_INVALID_KEYWORD,
    JSON_E_INVALID_ESCAPE_SEQUENCE,
    JSON_E_INVALID_UNICODE_SEQUENCE,
    JSON_E_INVALID_NUMBER,
    JSON_E_NESTING_DEPTH_REACHED,
    JSON_E_UNBALANCED_COLLECTION,
    JSON_E_EXPECTED_KEY,
    JSON_E_EXPECTED_COLON,
    JSON_E_OUT_OF_MEMORY
} JSON_error;

typedef enum
{
    JSON_T_NONE = 0,
    JSON_T_ARRAY_BEGIN,
    JSON_T_ARRAY_END,
    JSON_T_OBJECT_BEGIN,
    JSON_T_OBJECT_END,
    JSON_T_INTEGER,
    JSON_T_FLOAT,
    JSON_T_NULL,
    JSON_T_TRUE,
    JSON_T_FALSE,
    JSON_T_STRING,
    JSON_T_KEY,
    JSON_T_MAX
} JSON_type;

typedef struct JSON_value_struct {
    union {
        JSON_int_t integer_value;

        double float_value;

        struct {
            const char* value;
            size_t length;
        } str;
    } vu;
} JSON_value;

/*! \brief JSON parser callback

    \param ctx The pointer passed to new_JSON_parser.
    \param type An element of JSON_type but not JSON_T_NONE.
    \param value A representation of the parsed value. This parameter is NULL for
        JSON_T_ARRAY_BEGIN, JSON_T_ARRAY_END, JSON_T_OBJECT_BEGIN, JSON_T_OBJECT_END,
        JSON_T_NULL, JSON_T_TRUE, and SON_T_FALSE. String values are always returned
        as zero-terminated C strings.

    \return Non-zero if parsing should continue, else zero.
*/
typedef int (*JSON_parser_callback)(void* ctx, int type, const struct JSON_value_struct* value);


#ifndef JSON_PARSER_STACK_SIZE
#define JSON_PARSER_STACK_SIZE 128
#endif

#ifndef JSON_PARSER_PARSE_BUFFER_SIZE
#define JSON_PARSER_PARSE_BUFFER_SIZE 3500
#endif

//#define JSON_parser_free(p) 		do{if((NULL != (p))) free((p)); (p) = NULL; }while(0)

#define JSON_parser_free(p)       FREEIF(p)

typedef unsigned short UTF16;

typedef struct __JSON_parser_struct {
    JSON_parser_callback callback;
    void* ctx;
    signed char state, before_comment_state, type, escaped, comment, allow_comments, handle_floats_manually, error;
    char decimal_point;
    UTF16 utf16_high_surrogate;
    int current_char;
    int depth;
    int top;
    int stack_capacity;
    signed char* stack;
    char* parse_buffer;
    size_t parse_buffer_capacity;
    size_t parse_buffer_count;
    signed char static_stack[JSON_PARSER_STACK_SIZE];
    char static_parse_buffer[JSON_PARSER_PARSE_BUFFER_SIZE];
}JSON_parser_struct;

typedef JSON_parser_struct* JSON_parser;

/*! \brief The structure used to configure a JSON parser object

    \param depth If negative, the parser can parse arbitrary levels of JSON, otherwise
        the depth is the limit
    \param Pointer to a callback. This parameter may be NULL. In this case the input is merely checked for validity.
    \param Callback context. This parameter may be NULL.
    \param depth. Specifies the levels of nested JSON to allow. Negative numbers yield unlimited nesting.
    \param allowComments. To allow C style comments in JSON, set to non-zero.
    \param handleFloatsManually. To decode floating point numbers manually set this parameter to non-zero.

    \return The parser object.
*/
typedef struct {
    JSON_parser_callback     callback;
    void*                    callback_ctx;
    int                      depth;
    int                      allow_comments;
    int                      handle_floats_manually;
} JSON_config;


/*! \brief Initializes the JSON parser configuration structure to default values.

    The default configuration is
    - 127 levels of nested JSON (depends on JSON_PARSER_STACK_SIZE, see json_parser.c)
    - no parsing, just checking for JSON syntax
    - no comments

    \param config. Used to configure the parser.
*/
JSON_PARSER_DLL_API void init_JSON_config(JSON_config* config);

/*! \brief Create a JSON parser object

    \param config. Used to configure the parser. Set to NULL to use the default configuration.
        See init_JSON_config

    \return The parser object.
*/
JSON_PARSER_DLL_API extern JSON_parser new_JSON_parser(JSON_config* config);

/*! \brief Destroy a previously created JSON parser object. */
JSON_PARSER_DLL_API extern void delete_JSON_parser(JSON_parser jc);

/*! \brief Parse a character.

    \return Non-zero, if all characters passed to this function are part of are valid JSON.
*/
JSON_PARSER_DLL_API extern int JSON_parser_char(JSON_parser jc, int next_char);

/*! \brief Finalize parsing.

    Call this method once after all input characters have been consumed.

    \return Non-zero, if all parsed characters are valid JSON, zero otherwise.
*/
JSON_PARSER_DLL_API extern int JSON_parser_done(JSON_parser jc);

/*! \brief Determine if a given string is valid JSON white space

    \return Non-zero if the string is valid, zero otherwise.
*/
JSON_PARSER_DLL_API extern int JSON_parser_is_legal_white_space_string(const char* s);

/*! \brief Gets the last error that occurred during the use of JSON_parser.

    \return A value from the JSON_error enum.
*/
JSON_PARSER_DLL_API extern int JSON_parser_get_last_error(JSON_parser jc);

extern int json_parser(char *data,void *result_data_cntx, JSON_parser_callback callback);

void* JSON_parser_malloc1(int size);
void* JSON_parser_malloc2(int size);
void* JSON_parser_malloc3(int size);
void* JSON_parser_malloc4(int size);
void* JSON_parser_malloc5(int size);
void* JSON_parser_malloc6(int size);
void* JSON_parser_malloc7(int size);
void* JSON_parser_malloc8(int size);
void* JSON_parser_malloc9(int size);
void* JSON_parser_malloc10(int size);
void* JSON_parser_malloc11(int size);
void* JSON_parser_malloc12(int size);

#ifdef __cplusplus
}
#endif


#endif /* JSON_PARSER_H */

