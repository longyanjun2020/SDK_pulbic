
#ifndef __WMLCONV_TQH_H__
#define __WMLCONV_TQH_H__

#include <ncc_types.h>

#ifdef WIDE_CHARS
typedef unsigned short wchar;
#else
typedef uint8_t wchar;
#endif

struct ROKXML_binding {
    struct ROKXML_binding *next;
    wchar                 *name;
    wchar                 *value;
    uint8_t         flag ;
    uint8_t         unUsed1;
    uint16_t        unUsed2;
};
struct ROKXML_handlers {
    void (*begin  )(wchar const *, struct ROKXML_binding *);
    void (*end    )(wchar const *);
    void (*empty  )(wchar const *, struct ROKXML_binding *);
    void (*text   )(wchar const *);
    void (*cdata  )(wchar const *);
    void (*entity )(wchar const *);
    void (*comment)(wchar const *);
    void (*pi     )(wchar const *, wchar const *);
    void (*start  )(wchar const *, wchar const *);  /* root|0, pubid|0 */
    void (*finish )(void);                          /* end document */
};
extern void   quit(int8_t const *);

#endif /* __WMLCONV_TQH_H__ */
