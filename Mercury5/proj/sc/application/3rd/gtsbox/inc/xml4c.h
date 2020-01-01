#ifndef __XML4C_H__
#define __XML4C_H__

#include "xlite_type.h"
#include "xlite_E_type.h"

/************************************************************************/
/*                                                                      */
/*  struct and enum def                                                 */
/*                                                                      */
/************************************************************************/

// Tag数组最大值
#define TAG_MAX 2048

typedef xl_int32 Token;

// 状态机器状态
typedef enum
{
	// 开始
	MACHINE_STATE_START = 0x0,
	// 标记开始
	MACHINE_STATE_TAG_START,
	// 标记结束
	MACHINE_STATE_TAG_END,
	// 标记结束,表示要过滤的数据
	MACHINE_STATE_TAG_FILTER_END,
	//xml内容
	MACHINE_STATE_DATA,
	// 结束了
	MACHINE_STATE_END,
	//属性数据
	MACHINE_ATTRIBUTE_DATA
}state_machine_state;

// 解析出来的token类型
typedef enum
{
	// 读取到文件长度超过了
	TOKEN_TYPE_END = 0x0,
	// 开始标记
	TOKEN_TYPE_TAG,
	//数据
	TOKEN_TYPE_DATA,
	// 结束标记
	TOKEN_TYPE_END_TAG,
	//过滤的TOKEN，如<? xxx ?>,<! xxx>
	TOKEN_TYPE_FLITER_TAG,
	// 读取到'\0'结束
	TOKEN_TYPE_OVER
}token_type;

typedef enum
{
	// 开始
	ATTRIBUTE_START = 0x0,
	//属性名
	ATTRIBUTE_NAME,
	//属性值
	ATTRIBUTE_VALUE,
	//结束
	ATTRIBUTE_END
}attribute_enum;

typedef enum
{
	TOKEN_POZ_HEAD,//token为头<a>
	TOKEN_POZ_TAIL//token为尾</a>
}token_position;//token 的位置

typedef enum
{
	//默认的token格式：<a xxx="xxx">xxx</a>
	TOKEN_FOMAT_STANDARD,
	//token格式：<a xxx="xxx" />
	TOKEN_FOMAT_FOR_SHORT,
	//token类型数量
	token_label_total
}token_fomat;

typedef enum
{
	TOKEN_ATTRIBUTE_FOMAT_NULL,		//KONG
	TOKEN_ATTRIBUTE_FOMAT_A,		//<a xx="xxxx">默认为双引号,里面可以有单引号
	TOKEN_ATTRIBUTE_FOMAT_B			//<a xx='xxx'>单引号
}token_attribute_fomat;

// 节点结构
typedef struct _xml_node
{
	//父节点(为了加入数据方便使用，无需再建立标记堆栈)
	struct _xml_node* father;

	//子节点集(类型为xml_node)
	xlite_list children;

	// 属性集合
	xlite_list att_list;

	// 结点名称
	xl_char*			node_name;
	
	// 结点数据，即节点的内容
	xl_char*			data;

	// 其他内容
	xl_char*			other;
}xml_node;

typedef struct
{
	// 属性名称
	xl_char*			name;	

	// 属性数据
	xl_char*			data;

}attribute;

typedef struct 
{
	//开始位置
	xl_int32 curr_xml_start;

	//结束位置
	xl_int32 curr_xml_end;

	//数据内容
	xl_char curr_tag[TAG_MAX];
	
	//当前节点
	xml_node *current_node;

	//前一个节点
	xml_node *pre_node;

	//token的格式
	xl_int8 fomat;

	//token位置
	xl_int8	token_poz;

	//属性格式类型
	xl_int8	crt_att_fomat;
}_xml;

/************************************************************************/
/*                                                                      */
/*                                                                      */
/*  Function Interfaces                                                 */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/************************************************************************/

/*!
* @brief 当前字符是否为制定字符
* @param c1 检测字符
* @param c2 检测字符
* @return 如果相同返回TRUE,否则返回FALSE
*/
#define isChar(c1,c2) (c1 == c2)

//////////////////////////////////////////////////////////////////////////
// Global Functions


/*!
* @brief 解析xml链表到buffer里面后长度
* @param root_node 传入xml根节点
* @return 返回添加的总长度
* @note 递归
*/
xl_uint32 xml4c_get_xml_list_to_string_length(xml_node* root_node);

/*!
* @brief 解析XML
* @param buffer XML缓冲
*/
xl_void xml4c_string_to_xml_list(const xl_char *cBuffer,xlite_list *xml_list);

/*!
* @brief 解析xml链表到buffer里面
* @param buffer 输出buffer
* @param root_node 传入xml根节点
* @return 返回添加的总长度
* @note 递归
*/
xl_int32 xml4c_xml_list_to_string(xl_char* buffer, xml_node* root_node);

/*!
* @brief 创建根节点
* @param root_list 链表名
* @param root_name 节点名字
* @param root_data 节点数据
*/
xl_void xml4c_create_root(xlite_list *root_list,xl_char *root_name,xl_char *root_data);

/*!
* @brief 创建节点
* @param node_name 节点名字
* @param node_data 节点数据
*/
xml_node* xml4c_create_node(xl_char *node_name,xl_char *node_data);

/*!
* @brief 连接节点
* @param fnode 节点名字
* @param node 节点名字
*/
xl_void xml4c_connect_node(xml_node* fnode,xml_node *node);

/*!
* @brief 创建节点属性
* @param attrName 属性名称
* @param attrValue 属性值
*/
attribute* xml4c_create_attribute(xl_char* attrName,xl_char* attrValue);

/*!
* @brief 添加节点的属性
* @param node 节点
* @param attr 节点属性
*/
xl_void xml4c_add_attribute(xml_node* node,attribute *attr);

/*!
* @brief 获取节点的孩子链表
* @param xnode 节点名字
*/
xlite_list* xml4c_get_node_children_list(xml_node *xnode);

/*!
* @brief 获取跟节点
* @param rlist 链表名字
*/
xml_node* xml4c_get_root_node(xlite_list *rlist);

/*!
* @brief 释放节点内存
* @root_node 输入节点
*/
xl_void xml4c_xml4c_release(xml_node *root_node);

/*!
* @brief	释放节点内存
* @name		节点名字
* @l  		链表
* @note 	会递归下面所有节点都删除
*/
xl_void xml4c_list_delete_node_by_name(xlite_list *l,xl_char *name);

//add and remove by dk 2011-1-4  
/*!
* @brief 检查xml的有效性
* cBuffer 输入节点
*/
xl_bool xml4c_check_xml_validity(const xl_char *cBuffer);

/************************************************************************/
/*                                                                      */
/*                                                                      */
/*    static func defs                                                  */
/*                                                                      */
/*                                                                      */
/************************************************************************/
/*!
* @brief	是否为英语字母
* cChar 	当前字符
*/
static xl_bool isCharEnglish(const xl_char cChar);

/*!
* @brief	是否为数字
* cChar 	当前字符
*/
static xl_bool isCharNumber(const xl_char cChar);

/*!
* @brief	移动buffer指针到下一个位置
*/
static xl_char getNextChar(const char* buffer);

/*!
* @brief	查看前一个字符
* cChar 	当前字符
*/
static xl_char view_PreChar_only(const char* buffer);

/*!
* @brief	查看字符
* @n 		要查看的位置，0为当前位置
*/
static xl_char view_NextChar_only(const char* buffer,xl_int8 n);

/*!
* @brief	获取token类型为：TOKEN_FOMAT_FOR_SHORT的token的长度
*/
static xl_int32 get_token_head_len_for_type_short(const char *buffer);

/*!
* @brief	去除字符串末尾的空格回车等格式
*/
static xl_void xml4c_modify_string(xl_char* chararr);

/*!
* @brief	获取下一个TOKEN
*/
static Token xml4c_getNextToKen(const xl_char* buffer);

/*!
* @brief	释放xml，并将节点清零
* @root_node	节点名
*/
static xl_void xml4c_xml4c_release_ex(xml_node **root_node);

/*!
* @brief	解析token的属性
* @att_list	属性链表
* buffer	
*/
static xl_void	xml4c_parse_token_tag_attribute(xlite_list *att_list,xl_char *buffer);

/*!
* @brief	节点属性数据表转为字符串
* @root_node	节点数据
*/
static xl_void xml4c_list_child_attribute_to_string(xml_node *root_node,xl_char** curr);

/*!
* @brief	节点属性数据表转为字符串
* @root_node	节点数据
*/
static xl_void xml4c_list_child_other_to_string(xml_node *root_node,xl_char** curr);

/*!
* @brief	节点是否有数据
* @node		节点
*/
//static xl_char* xml4c_is_node_has_data(xml_node *node);

/*!
* @brief	移动BUFFER指针
* @poz		buffer的位置
*/
static xl_char get_next_char(const char* buffer,xl_int32 *poz);

/*!
* @brief	当前字符是否是些特殊格式
* @cChar		当前字符
*/
static xl_bool isCharTabs(const xl_char cChar);

/*!
* @brief	转换XML的一些常用字符
* @pBuffer		
*/
static xl_char trans_special_symbol(const xl_char *pBuffer);

/*!
* @brief	获取node长度递归
* @pBuffer		
*/
static xl_uint32 get_xml_list_to_string_length(xml_node* root_node);
static xl_uint32 get_list_child_other_to_string_length(xml_node *root_node);
static xl_uint32 get_list_child_attribute_to_string_lenght(xml_node *root_node);

#endif
