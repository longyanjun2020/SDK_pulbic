//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
#ifndef _DRVLIST_H
#define _DRVLIST_H

#include <MsTypes.h> // for TRUE, FALSE

/* list structure definition */
struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

#define DECLARE_LIST(mylist)  \
	struct list_head mylist = { &(mylist), &(mylist) }

/**
     * @brief		Initial list structure data member
     *
     * @param		pInitList   pointer of the list to be initialized.
     *
     * @return		None
     */
static __inline__ void ms_list_init (struct list_head *pInitList)
{
	pInitList->next = pInitList;
	pInitList->prev = pInitList;
}

/**
     * @brief		Insert list after the specified list
     *
     * @param		pNew                New list to be added.
     *
     * @param		pInsert_after_it  Insert list after this list.
     *
     * @return		None
     */
static __inline__ void ms_insert_list_after( struct list_head *pNew, struct list_head *pInsert_after_it )
{
	struct list_head *next;
	next = pInsert_after_it->next;
	pInsert_after_it->next = pNew;
	pNew->next = next;
	pNew->prev = pInsert_after_it;
	next->prev = pNew;
}

/**
     * @brief		check if  is empty list
     *
     * @param		pList    list to be checked.
     *
     * @return		boolean
     */
static __inline__ int ms_is_empty_list(const struct list_head *pList )
{
	if (pList == pList->next)
		return TRUE;
	else
		return FALSE;
}

/**
     * @brief		Insert list before the specified list
     *
     * @param		pNew                   New list to be added.
     *
     * @param		pInsert_before_it   Insert list before this list.
     *
     * @return		None
     */
static __inline__ void ms_insert_list_before( struct list_head *pNew, struct list_head *pInsert_before_it )
{
	struct list_head *prev;
	prev = pInsert_before_it->prev;
	pNew->prev = prev;
	pNew->next = pInsert_before_it;
	pInsert_before_it->prev = pNew;
	prev->next = pNew;
}

/**
     * @brief		Remove current entry from list
     *
     * @param		pNew             Current entry to be removed.
     *
     * @return		None
     */
static __inline__ void ms_list_remove( struct list_head *pList )
{
	pList->prev->next = pList->next;
	pList->next->prev = pList->prev;
}

/**
     * @brief		Remove current entry from list and initial the entry
     *
     * @param		pEntry            Current entry to be removed.
     *
     * @return		None
     */
static __inline__ void ms_list_remove_and_init(struct list_head *pEntry)
{
	ms_list_remove(pEntry);
	ms_list_init(pEntry);
}

/**
     * @brief		Join lists.
     *
     * @param		pList             The list to be added.
     *
     * @param		pHead           The place
     *
     * @return		None
     */
static __inline__ void ms_list_join(const struct list_head *pList, struct list_head *pHead)
{
	struct list_head *pFirst = pList->next;
	struct list_head *pLast = pList->prev;
	struct list_head *pNext = pHead->next;

	pFirst->prev = pHead;
	pHead->next = pFirst;

	pLast->next = pNext;
	pNext->prev = pLast;
}

/**
 * list_splice - join two lists, this is designed for stacks
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void list_splice(
	const struct list_head *list,
	struct list_head *head
)
{
	if (!ms_is_empty_list(list))
		ms_list_join(list, head);
}

/**
 * list_is_singular - tests whether a list has just one entry.
 * @head: the list to test.
 */
static inline int list_is_singular(const struct list_head *head)
{
	return !ms_is_empty_list(head) && (head->next == head->prev);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void list_move_tail(struct list_head *list,
				  struct list_head *head)
{
	ms_list_remove(list);
	ms_insert_list_before(list, head);
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void list_move(struct list_head *list, struct list_head *head)
{
	ms_list_remove(list);
	ms_insert_list_after(list, head);
}

/**
 * list_splice_tail_init - join two lists and reinitialise the emptied list
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * Each of the lists is a queue.
 * The list at @list is reinitialised
 */
// FIXME: 3.10.40 only
static inline void list_splice_tail_init(struct list_head *list,
					 struct list_head *head)
{
	if (!ms_is_empty_list(list)) {
		ms_insert_list_before(list, head);
		ms_list_init(list);
	}
}

/**
     * @brief		cast a member item to the container structure.
     *
     * @param		_item_          member item pointer.
     *
     * @param		_struct_        The type definition of the container structure
     *
     * @param		_member_     The name of the _item_ in the structure _struct_
     *
     * @return		the container structure pointer
     */
#define entry_to_container( _item_, _struct_, _member_ ) \
    ((_struct_ *)((char *)(_item_)-(char *)(offsetof(_struct_,_member_))))

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
	entry_to_container((ptr)->next, type, member)

#define list_for_loop( _item_, _list_ )   \
	for ( (_item_)=(_list_)->next; (_item_)!=(_list_); (_item_)=(_item_)->next )

#define list_for_each_entry(_list_, _head_, _item_)                     \
for ((_list_) = entry_to_container((_head_)->next, typeof(*_list_), _item_); \
	&((_list_)->_item_) != (_head_);                                 \
	(_list_) = entry_to_container((_list_)->_item_.next, typeof(*_list_), _item_))

#define list_for_loop_ex(_item_, _temp_, _list_) \
	for (_item_=(_list_)->next, _temp_=_item_->next; _item_!=(_list_); _item_=_temp_, _temp_=_item_->next)

#if 0
#define list_for_each_prev(_item_, _list_) \
	or (_item_ = (_list_)->prev; _item_ != (_list_); _item_ = _item_->prev)
#endif

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

#define INIT_LIST_HEAD( _list_ )   ms_list_init( _list_)
#define list_add( _newlist_, _list_add_after_ )  ms_insert_list_after( _newlist_, _list_add_after_ )
#define list_empty( _list_ )  ms_is_empty_list( _list_)
#define list_add_tail( _newlist_, _list_add_before_ )  ms_insert_list_before( _newlist_, _list_add_before_ )
#define list_del( _list_ )   ms_list_remove( _list_)
#define list_del_init( _list_ )   ms_list_remove_and_init( _list_)
#define __list_splice( _list_, _head_ )   ms_list_join( _list_, _head_ )
#define list_entry( _list_, _struct_, _member_ ) entry_to_container( _list_, _struct_, _member_ )
#define list_for_each_safe(_item_, _temp_, _list_)  list_for_loop_ex(_item_, _temp_, _list_)
#define list_for_each( _item_, _list_ )   list_for_loop( _item_, _list_ )

#endif
