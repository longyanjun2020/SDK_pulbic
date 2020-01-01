
/* External API definitions */
#ifndef __expat_external_h__
#define __expat_external_h__

#ifndef XML_STATIC
#define XML_STATIC
#endif

#if defined(_MSC_EXTENSIONS) && !defined(__BEOS__) && !defined(__CYGWIN__)
#define XML_USE_MSC_EXTENSIONS 0
#endif

/* Expat tries very hard to make the API boundary very specifically
   defined.  There are two macros defined to control this boundary;
   each of these can be defined before including this header to
   achieve some different behavior, but doing so it not recommended or
   tested frequently.

   XMLCALL    - The calling convention to use for all calls across the
                "library boundary."  This will default to cdecl, and
                try really hard to tell the compiler that's what we
                want.

   XMLIMPORT  - Whatever magic is needed to note that a function is
                to be imported from a dynamically loaded library
                (.dll, .so, or .sl, depending on your platform).

   The XMLCALL macro was added in Expat 1.95.7.  The only one which is
   expected to be directly useful in client code is XMLCALL.

   Note that on at least some Unix versions, the Expat library must be
   compiled with the cdecl calling convention as the default since
   system headers may assume the cdecl convention.
*/

#define XMLIMPORT
#define XMLCALL
#define XMLPARSEAPI(type) type

#ifdef __cplusplus
extern "C" {
#endif

#ifdef XML_UNICODE_WCHAR_T
#define XML_UNICODE
#endif

#ifdef XML_UNICODE     /* Information is UTF-16 encoded. */
#ifdef XML_UNICODE_WCHAR_T
typedef wchar_t XML_Char;
typedef wchar_t XML_LChar;
#else
typedef unsigned short XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE_WCHAR_T */
#else                  /* Information is UTF-8 encoded. */
typedef char XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE */

#endif /* __expat_external_h__ */
