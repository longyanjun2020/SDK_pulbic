/****************************************************************************/
/*  File    : util_ucs2.h                                                   */
/*--------------------------------------------------------------------------*/
/* Description: Standard Unicode related utility functions.                 */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef __SYS_UTIL_UCS2_H__
#define __SYS_UTIL_UCS2_H__

#define UCS2_TERMINATOR     (0)
#define U8_TERMINATOR       (0)

#define CTRL_PERCENT   '%'

#define OP_a        'a' // Ascii char
#define OP_A        'A' // Ascii string
#define OP_DASH     '-'
#define OP_PLUS     '+'
#define OP_SPACE    ' '
#define OP_NUMS     '#'
#define OP_STAR     '*'
#define OP_DOT      '.'
#define OP_0        '0'

#define OP_f        'f'
#define OP_e        'e'
#define OP_E        'E'
#define OP_g        'g'
#define OP_G        'G'
#define OP_i        'i'
#define OP_u        'u'
#define OP_o        'o'
#define OP_x        'x'
#define OP_X        'X'
#define OP_c        'c'
#define OP_h        'h'
#define OP_n        'n'
#define OP_d        'd'
#define OP_l        'l'
#define OP_L        'L'
#define OP_s        's' // UCS2 string
#define OP_p        'p'

#define Chr_0       '0'
#define Chr_SPACE   ' '
#define Chr_SA      '<'
#define Chr_LA      '>'

#define __LJUSTIFY       0x00000001
#define __SIGNED         0x00000002
#define __BLANKER        0x00000004
#define __VARIANT        0x00000010
#define __PRECGIVEN      0x00000020
#define __LONGSPECIFIER  0x00000040
#define __SHORTSPEC      0x00000100
#define __PADZERO        0x00000200
#define __FPCONV         0x00000400

#define _IS_DIGI_(_C_) (_C_ >= '0' && _C_ <= '9')
#define _INTOFDIGIT_(X) ((X) - '0')

#endif // #ifndef __SYS_UTIL_UCS2_H__
