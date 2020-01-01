
/**
 * @file
 * Browser memory block management of uWAP
 */


#ifndef _ALYSMMANAGE_H_
#define _ALYSMMANAGE_H_

#include <wap_config.h>
#include <wap_struct.h>
#include <ncccommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NCC_BROWSER1_2

/*memory block configure*/
#define  TEXTBUF_FIRST_BLOCK_LEN    (4096)
#define  TEXTBUF_NORMAL_BLOCK_LEN   (3072)

#define  NODE_FIRST_BLOCK_LEN     50
#define  NODE_NORMAL_BLOCK_LEN    50

#define TEXT_FIRST_BLOCK_LEN      50
#define TEXT_NORMAL_BLOCK_LEN     50

#define  A_FIRST_BLOCK_LEN        50
#define  A_NORMAL_BLOCK_LEN       50

#define  AATTR_FIRST_BLOCK_LEN    50
#define  AATTR_NORMAL_BLOCK_LEN   50

#define  TABLE_FIRST_BLOCK_LEN    10
#define  TABLE_NORMAL_BLOCK_LEN   5

#define  TR_FIRST_BLOCK_LEN       50
#define  TR_NORMAL_BLOCK_LEN      10

#define  TD_FIRST_BLOCK_LEN       50
#define  TD_NORMAL_BLOCK_LEN      10

#define  IMG_FIRST_BLOCK_LEN      20
#define  IMG_NORMAL_BLOCK_LEN     20

#define  FORM_FIRST_BLOCK_LEN     10
#define  FORM_NORMAL_BLOCK_LEN    10

#define  FIELD_FIRST_BLOCK_LEN    20
#define  FIELD_NORMAL_BLOCK_LEN   20

#define OPTION_FIRST_BLOCK_LEN    20
#define OPTION_NORMAL_BLOCK_LEN   20

#define P_FIRST_BLOCK_LEN         20
#define P_NORMAL_BLOCK_LEN        20

#define YPOS_FIRST_BLOCK_LEN 50
#define YPOS_NORMAL_BLOCK_LEN 50

#define BOX_FIRST_BLOCK_LEN   50
#define BOX_NORMAL_BLOCK_LEN  20

#define OBJECT_FIRST_BLOCK_LEN 10
#define OBJECT_NORMAL_BLOCK_LEN 10

#define LINE_FIRST_BLOCK_LEN 10
#define LINE_NORMAL_BLOCK_LEN 10

#else

/*memory block configure*/
#define  TEXTBUF_FIRST_BLOCK_LEN    (2048)
#define  TEXTBUF_NORMAL_BLOCK_LEN   (2048)

#define  NODE_FIRST_BLOCK_LEN     50
#define  NODE_NORMAL_BLOCK_LEN    50

#define TEXT_FIRST_BLOCK_LEN      20
#define TEXT_NORMAL_BLOCK_LEN     20

#define  A_FIRST_BLOCK_LEN        20
#define  A_NORMAL_BLOCK_LEN       20

#define  AATTR_FIRST_BLOCK_LEN    10
#define  AATTR_NORMAL_BLOCK_LEN   10

#define  TABLE_FIRST_BLOCK_LEN    5
#define  TABLE_NORMAL_BLOCK_LEN   5

#define  TR_FIRST_BLOCK_LEN       5
#define  TR_NORMAL_BLOCK_LEN      5

#define  TD_FIRST_BLOCK_LEN       5
#define  TD_NORMAL_BLOCK_LEN      5

#define  IMG_FIRST_BLOCK_LEN      10
#define  IMG_NORMAL_BLOCK_LEN     5

#define  FORM_FIRST_BLOCK_LEN     5
#define  FORM_NORMAL_BLOCK_LEN    5

#define  FIELD_FIRST_BLOCK_LEN    5
#define  FIELD_NORMAL_BLOCK_LEN   5

#define OPTION_FIRST_BLOCK_LEN    5
#define OPTION_NORMAL_BLOCK_LEN   5

#define P_FIRST_BLOCK_LEN         5
#define P_NORMAL_BLOCK_LEN        5

#define YPOS_FIRST_BLOCK_LEN 10
#define YPOS_NORMAL_BLOCK_LEN 10

#define BOX_FIRST_BLOCK_LEN   10
#define BOX_NORMAL_BLOCK_LEN  10

#define OBJECT_FIRST_BLOCK_LEN 5
#define OBJECT_NORMAL_BLOCK_LEN 5

#define LINE_FIRST_BLOCK_LEN 5
#define LINE_NORMAL_BLOCK_LEN 5


#endif

/**  thd docSrc structure from all nodes */
struct browserMM
{
    T_Comm_MBlockPtr    mPtr[DB_MM_MAX];
    void                *attrTable;
};

typedef struct browserMM        T_DBA_BrowserMM;
typedef T_DBA_BrowserMM        *T_DBA_BrowserMMPtr;

/**  params strcut for browser block management */
struct browserMMParam
{
    int16_t firstSize;  /**< amount of first block group */
    int16_t eachSize;   /**< amount of other block group */
    int16_t itemSize;   /**< size of each block */
    int16_t alignByte;  /**< align byte*/
};

/** Append memory and copy the context of src to it
*
*   \param buf   the context we wanted to save
*   \param len   the context length
*   \param alignByte   align mode
*   \return    pointer to the src
*/
uint8_t*  fnDBA_comnBufAppendMult(
    uint8_t*        buf,
    int16_t     len,
    int16_t     alignByte
);

/** Initiate space of all nodes and their members
*
*   \return
*/
int32_t fnDBA_MMInit(void);

/**getting the browser memory manager of current page
* \return  the browser memory manager
*/
T_DBA_BrowserMMPtr fnDBA_GetbrowserMMPtr(void);

/**Setting the browser memory manager of current page
*   \param ctxt   the browser memory manager
*/
void fnDBA_SetbrowserMMPtr(T_DBA_BrowserMMPtr  ctxt);

/**Make the browser memory manager free
*   \param ctxt  the browser memory manager
*/
void fnDBA_browserMMFree(T_DBA_BrowserMMPtr  ctxt);

#ifdef __cplusplus
}
#endif

#endif /*_ALYSMMANAGE_H_*/
