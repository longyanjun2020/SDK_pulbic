#if ! defined( common_list_h )
#define common_list_h
/*****************************************************************************/
/* common_list_h                                                             */
/* list.h                                                                    */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

#define OFFSET( type, field )           ( (int) &( ( (type *)0 )->field ) )
#define RECORD( address, type, field )  (   \
            (type *)(                                                       \
                (char *)(address) - (unsigned int)( &( (type *)0 )->field ) \
            )                                                               \
        )

/*****************************************************************************/

typedef struct _DLIST {
    struct _DLIST * volatile F;
    struct _DLIST * volatile B;
} DLIST, *PDLIST;

/*---------------------------------------------------------------------------*/

#define InitDList( h )              ( (h)->F = (h)->B = (h) )
#define RemoveHead( h )             (h)->F; { RemoveEntry( (h)->F ) }
#define RemoveEntry( e ) {          \
            PDLIST  _b, _f;         \
            _f = (e)->F;            \
            _b = (e)->B;            \
            _b->F = _f;             \
            _f->B = _b;             \
        }
#define InsertTail( h, e ) {        \
            PDLIST _h, _b;          \
            _h = (h);               \
            _b = _h->B;             \
            (e)->F = _h;            \
            (e)->B = _b;            \
            _b->F = (e);            \
            _h->B = (e);            \
        }
#define InsertEntry( p, e )         InsertTail( p, e )

/*****************************************************************************/
#endif  /* ! defined ( common_list_h ) */
