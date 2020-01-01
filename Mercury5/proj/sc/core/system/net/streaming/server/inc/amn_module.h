/*
 * amn_module.h
 */
#define	NETSERV_TYPE	1
#define	NETNODE_TYPE	2
//
#define	NM_HEADER_ID	(0xfeedfeed)
#define	NC_HEADER_ID	(0xfccdfccd)
//
extern unsigned int Image$$NETNODE_INIT$$Base;
extern unsigned int Image$$NETNODE_INIT$$Limit;
extern unsigned int Image$$NETCGI_INIT$$Base;
extern unsigned int Image$$NETCGI_INIT$$Limit;
#define	SECTION_START(_s_)	((void*)(&Image$$##_s_##$$Base))
#define	SECTION_END(_s_)	((void*)(&Image$$##_s_##$$Limit))
//loader request
typedef struct {
	int		nmtype; //net module type
	int		lorder; //load order, may be used in amn_load_module() later
	int		nmid;   //net module ID
} loreq_t;

typedef int (*netnode_init_t)(loreq_t *loreq);
typedef int (*netcgi_init_t)(loreq_t *loreq);

typedef struct {
#if !defined(__RTK_OS__)
	unsigned int	netmID;
#endif
	netnode_init_t	module[1];
} netmo_t;//net module

loreq_t* amn_setup_loreq(loreq_t* plq, int nmoid, int nmotype, int order);
int amn_load_module(loreq_t *plq, netmo_t *pmo, void* image_end);
