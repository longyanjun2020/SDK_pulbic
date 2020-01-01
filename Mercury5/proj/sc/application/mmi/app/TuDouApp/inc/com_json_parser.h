
#ifndef __SP_JSON_PARSER_H__
#define __SP_JSON_PARSER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define JSON_KAY_LEN_MAX 32
#define JSON_VALUE_LEN_MAX  80//16

typedef enum
{
	JSON_TYPE_NONE,

	JSON_TYPE_EMPTY,

	JSON_TYPE_STRING,
	JSON_TYPE_OBJECT,
	JSON_TYPE_ARRAY,

	JSON_TYPE_MAX
}JSON_TYPE_ENUM;


typedef struct _common_json_item
{
	char key[JSON_KAY_LEN_MAX];
	char value[JSON_VALUE_LEN_MAX];
	char *value_ex;
	struct _common_json_item *next;
}common_json_item;


struct _com_json_parser_cntx;

typedef struct _common_json_data
{
	struct _com_json_parser_cntx *parser_cntx;
	char type;
	char name[JSON_KAY_LEN_MAX];
	char *data;

	struct _common_json_data *parent;
	struct _common_json_data *next;
}common_json_data;


#define JSON_PARSER_STATIC_MEM

#ifdef JSON_PARSER_STATIC_MEM
#define JSON_DATA_MAX 500
#define JSON_ITEM_DATA_MAX 400
#endif

typedef struct _com_json_parser_cntx
{
	common_json_data *curr_data;
	char curr_key[JSON_KAY_LEN_MAX];

#ifdef JSON_PARSER_STATIC_MEM
	common_json_data json_data[JSON_DATA_MAX];
	common_json_item json_item_data[JSON_ITEM_DATA_MAX];
	int json_data_index;
	int json_item_data_index;
#endif
}com_json_parser_cntx;

extern void* com_json_parser(char *file_path, int length);
extern void com_json_destroy(void *handle);

extern char* com_json_get_string_object_value(common_json_data *src_object);
extern common_json_data* com_json_get_subobject(common_json_data *src_project, char* subobject_name);
extern common_json_data* com_json_get_array_object(common_json_data *src_array, int index);
extern int com_json_get_array_object_count(common_json_data *array_data);

#ifdef __cplusplus
}
#endif

#endif

