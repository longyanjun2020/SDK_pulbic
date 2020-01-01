#ifndef _AIT_INIT_H_
#define _AIT_INIT_H_

typedef int (*ait_initcall_t)(void);

/* Reference from Linux init.h */
/*
#define pure_initcall_level				0
#define core_initcall_level				1
#define core_initcall_sync_level		1s
#define postcore_initcall_level			2
#define postcore_initcall_sync_level	2s
#define arch_initcall_level				3
#define arch_initcall_sync_level		3s
#define subsys_initcall_level			4
#define subsys_initcall_sync_level		4s
#define fs_initcall_level				5
#define fs_initcall_sync_level			5s
#define rootfs_initcall_level			rootfs
#define device_initcall_level			6
#define device_initcall_sync_level		6s
#define late_initcall_level				7
#define late_initcall_sync_level		7s
*/

#if 0

#define ait_init_local
//#define ait_init_local static //original porting but make compilation warnings

#define __ait_define_initcall(fn, id)	\
	ait_init_local ait_initcall_t __ait_initcall_##fn##id = &fn


#define ait_device_initcall(fn)		__ait_define_initcall(fn,6)
#define __ait_initcall(fn) ait_device_initcall(fn)
#define ait_module_init(x)	__ait_initcall(x)

#define ait_core_initcall(fn)		__ait_define_initcall(fn,1)
#define ait_core_init(x)	ait_core_initcall(x)

#else

#define __ait_define_initcall0(fn, id) \
	const ait_initcall_t __ait_initcall_##fn##id __attribute__((used)) = &fn

#define __ait_define_initcall1(fn, id) \
	const ait_initcall_t __ait_initcall_##fn##id __attribute__((used)) = &fn

#define __ait_define_initcall2(fn, id) \
	const ait_initcall_t __ait_initcall_##fn##id __attribute__((used)) = &fn

#define __ait_define_initcall3(fn, id) \
	const ait_initcall_t __ait_initcall_##fn##id __attribute__((used)) = &fn

#define __ait_define_initcall4(fn, id) \
	const ait_initcall_t __ait_initcall_##fn##id __attribute__((used)) = &fn

#define __ait_define_initcall5(fn, id) \
	const ait_initcall_t __ait_initcall_##fn##id __attribute__((used)) = &fn
	
#define __ait_define_initcall6(fn, id)	\
    const ait_initcall_t __ait_initcall_##fn##id __attribute__((used)) = &fn
    
#define __ait_define_initcall7(fn, id) \
	const ait_initcall_t __ait_initcall_##fn##id = &fn

#define ait_device_initcall(fn)		__ait_define_initcall6(fn,6)
#define __ait_initcall(fn) ait_device_initcall(fn)
#define ait_module_init(x)	__ait_initcall(x)

#define ait_core_initcall(fn)		__ait_define_initcall1(fn,1)
#define ait_core_init(x)	ait_core_initcall(x)

#endif

#endif /* _AIT_INIT_H_ */
