////////////////////////////////////////////////////////////////////////////////
///@file efat_list.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef ONCE_FS_JFFS2_LIST_H
#define ONCE_FS_JFFS2_LIST_H

#include <stddef.h>
#include <infra_type.h>

// TYPES 

struct efat_list_head {
    struct efat_list_head *next;
    struct efat_list_head *prev;
};

// MACROS 

#define EFAT_LIST_HEAD_INIT(name) { &(name), &(name) }

#define EFAT_LIST_HEAD(name) struct efat_list_head name = EFAT_LIST_HEAD_INIT(name)

#define EFAT_INIT_LIST_HEAD( _list_ ) EFAT_MACRO_START (_list_)->next = (_list_)->prev = (_list_); EFAT_MACRO_END

// FUNCTIONS 

// Insert an entry before the specified entry 
static __inline__ void
efat_list_add_tail( struct efat_list_head *newent, struct efat_list_head *lastent )
{
    struct efat_list_head *prev = lastent->prev;
    newent->prev = prev;
    newent->next = lastent;
    lastent->prev = newent;
    prev->next = newent;
}

// Is list empty? 
static __inline__ int
efat_list_empty( struct efat_list_head *list )
{
    return ( list->next == list );
} 

#define efat_list_entry( _list_, _type_, _member_ ) ((_type_ *)((char *)(_list_)-(char *)(offsetof(_type_,_member_))))

#define efat_list_for_each( _ent_, _list_ )   \
    for ( (_ent_) = (_list_)->next;      \
    (_ent_) != (_list_);                 \
    (_ent_) = (_ent_)->next )

#define efat_list_for_each_entry(_list_, _head_, _item_)                     \
for ((_list_) = efat_list_entry((_head_)->next, typeof(*_list_), _item_); \
     &((_list_)->_item_) != (_head_);                                 \
     (_list_) = efat_list_entry((_list_)->_item_.next, typeof(*_list_), _item_))


// Insert an entry after the specified entry 
static __inline__ void
efat_list_add( struct efat_list_head *newent, struct efat_list_head *lastent )
{
    struct efat_list_head *next = lastent->next;
    newent->next = next;
    newent->prev = lastent;
    lastent->next = newent;
    next->prev = newent;
} 

// Delete the specified entry 
static __inline__ void
efat_list_del( struct efat_list_head *ent )
{
    ent->prev->next = ent->next;
    ent->next->prev = ent->prev;
} 

// -----------------------------------------------------------------------
#endif // #ifndef ONCE_FS_JFFS2_LIST_H 
// EOF list.h 
