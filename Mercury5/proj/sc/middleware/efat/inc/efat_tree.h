#ifndef	_LINUX_RBTREE_H
#define	_LINUX_RBTREE_H
///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   efat_tree.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////


struct ms_efat_node {
	struct ms_efat_node *ms_efat_left;	/* left element */
	struct ms_efat_node *ms_efat_right;	/* right element */
	struct ms_efat_node *ms_efat_parent;	/* parent element */
	int ms_efat_color;			/* node color */
};

struct ms_efat_root {
	struct ms_efat_node *ms_efat_node; /* root of the tree */
};
#define pNULL ((void *)0)
#define MS_EFAT_ROOT ((struct ms_efat_root){NULL})
#define ms_efat_entry(p, container, field)		\
	((container *) ((char *)p - ((char *)&(((container *)0)->field))))

#define MS_EFAT_BLACK	0
#define MS_EFAT_RED		1


extern void ms_efat_insert_color(struct ms_efat_node *, struct ms_efat_root *);
extern void ms_efat_erase(struct ms_efat_node *, struct ms_efat_root *);

/* Find logical next and previous nodes in a tree */
extern struct ms_efat_node *ms_efat_next(struct ms_efat_node *);
extern struct ms_efat_node *ms_efat_prev(struct ms_efat_node *);
extern struct ms_efat_node *ms_efat_first(struct ms_efat_root *);

/* Fast replacement of a single node without remove/rebalance/add/rebalance */
extern void ms_efat_replace_node(struct ms_efat_node *victim, struct ms_efat_node *new,
			    struct ms_efat_root *root);

static __inline void ms_efat_link_node(struct ms_efat_node * node, struct ms_efat_node * parent,
				struct ms_efat_node ** ms_efat_link)
{
	node->ms_efat_parent = parent;
	node->ms_efat_color = MS_EFAT_RED;
	node->ms_efat_left = node->ms_efat_right = pNULL;

	*ms_efat_link = node;
}

#endif	/* _LINUX_RBTREE_H */
