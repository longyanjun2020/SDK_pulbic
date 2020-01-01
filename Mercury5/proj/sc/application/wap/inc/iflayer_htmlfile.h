
#ifndef __IFLAYER_HTMLFILE_H__
#define __IFLAYER_HTMLFILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <wap_service.h>

    /*The size of first buffer*/
#define FIRST_BLOCK_MEM 10240
    /*The increased MEM size for each time*/
#define EVERY_BLOCK_MEM 10240

#define HTML_SAVE_NAME_LEN 512

#define WML_ENCODE_IDENTIFICATION "<wml"
#define WML_ENCODE_IDENTIFICATION_L L"<wml"

    /** struct of saved html resource */
typedef struct _HtmlResourcelist
{
    uint8_t *data;
    int32_t length;
    uint8_t name[HTML_SAVE_NAME_LEN];
    struct _HtmlResourcelist *pResourceNext;
}HtmlResourceList;
/** struct for save html */
typedef struct _HtmlVars
{
    int32_t manyText;
    int32_t manyANode;
    int32_t lastNodeisP;
    int32_t lastNodeisBR;
    int32_t fontText;
    int32_t fontA;
}HtmlVars;
/** struct for mem */
typedef struct _HtmlMems
{
    int32_t totalMem;
    int32_t curMem;
}HtmlMems;


    /**
    * Convert the number the string, and return the number of bits
    * \param  the number be converted
    * \param  string to be converted
    * \return  the converted string
    */
    int8_t *changeFromCommonWord(int32_t t, int32_t *s);

    /**
    * Link the string
    * \param destination string
    * \param the string will be linked to buf
    * \param htmlMem the structure to save buf info
    * \return value: void
    */
    void StringCat(int8_t ** buf, const int8_t *str, HtmlMems * htmlMem);

   /**
   * Append context of  label in head to the buffer
   * \param link the previous and next BUFFER
   * \param htmlMem the structure to save buf info
   * \return value: void
   */
    void SaveHeadToBuffer(int8_t**buf, T_DB_ParseCtxtPtr ParseCtxt, HtmlMems * htmlMem);

     /**
     * Append the normal text the the buffer
     * \param link the previous and next BUFFER
     * \param current node
     * \param htmlMem the structure to save buf info
     * \param htmlVar the structure to save html info
     * \return value: void
     */
    void SaveTextToBuffer(int8_t **buf, T_DB_NodeInterfacePtr pNode, T_DB_ParseCtxtPtr ParseCtxt,
        HtmlMems * htmlMem,HtmlVars * htmlVar);

    /**
    * link the context in the label A to buffer
    * \param link the previous and next BUFFER;
    * \param current node
    * \param htmlMem the structure to save buf info
    * \param pResListFirst the point of first structure list to save buf info
    * \param htmlVar the structure to save html info
    * \return value: void
    */
    void SaveAToBuffer(int8_t **buf, T_DB_NodeInterfacePtr pNode, T_DB_ParseCtxtPtr ParseCtxt,
        HtmlMems * htmlMem, HtmlResourceList ** pResListFirst, HtmlVars * htmlVar);
    /**
    * link the context about IMG label to BUFFER
    * \param link the previous and next BUFFER:
    * \param current node
    * \param saveName the name of save path
    * \param htmlMem the structure to save buf info
    * \param pResListFirst the point of first structure list to save buf info
    * \return value: void
    */
    void SaveImgToBuffer(int8_t **buf, T_DB_NodeInterfacePtr pNode, int8_t * saveName,
        HtmlMems * htmlMem, HtmlResourceList ** pResListFirst);
    /**
    * link the context about INPUT label to the BUFFER
    * \param link the previous and next BUFFER
    * \param current node
    * \param htmlMem the structure to save buf info
    * \return value: void
    */
    void SaveFieldToBuffer(int8_t **buf, T_DB_NodeInterfacePtr pNode, HtmlMems * htmlMem);

    /**
    * link the context about TABLE to BUFFER
    * \param link the previous and next BUFFER
    * \param current node
    * \param saveName the name of save path
    * \param htmlMem the structure to save buf info
    * \param pResListFirst the point of first structure list to save buf info
    * \param htmlVar the structure to save html info
    * \return value: void
   */
    void SaveTableToBuffer(int8_t **buf, T_DB_NodeInterfacePtr pNode, T_DB_ParseCtxtPtr ParseCtxt,
                        int8_t * saveName, HtmlMems * htmlMem, HtmlResourceList ** pResouceFirst,
                        HtmlVars * htmlVar);

    /**
    * validate file name with invalid characters
    * \param  file name
    */
    void ValidateInvalidFilename(uint8_t * filename);
	
    /**
    * save the picture, return the local path of saved picture
    * \param  URL path
    * \param  image type
    * \param  the data pointer of image structure
    * \param  the size of image data
    * \param savePath the name of save path
    * \param pResListFirst the point of first structure list to save buf info
    * \return value  local path
    */
    uint8_t * GetSaveSrc(uint8_t * src, int32_t state, uint8_t *  data, int32_t size,
                      int8_t * savePath, HtmlResourceList ** pResListFirst);
                      
    int32_t checkSavedPageDocType(int8_t * saveName);

#ifdef __cplusplus
}
#endif

#endif  // _DB_HTMLFILE_H
