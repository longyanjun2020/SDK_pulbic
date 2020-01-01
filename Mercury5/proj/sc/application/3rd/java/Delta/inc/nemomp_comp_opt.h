#ifndef __NEMOMP_COMPILE_OPTION_H__
#define __NEMOMP_COMPILE_OPTION_H__

#define __JAVA_CLDC__
#define __JAVA_MIDP__

#ifdef __JAVA_DELTA_JSR75__
#define __JAVA_JSR75_FC__
#endif

#ifdef __JAVA_DELTA_JSR184__
#define __JAVA_JSR184__
#endif

#ifdef __JAVA_DELTA_JTWI__
#define __JAVA_JSR211_CHAPI__
#define __JAVA_JTWI__
#endif

#endif /* __NEMOMP_COMPILE_OPTION_H__ */
