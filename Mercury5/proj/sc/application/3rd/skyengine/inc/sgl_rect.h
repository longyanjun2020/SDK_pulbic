/*
** funs.h: the functions header file.
**
** Copyright (C) 2007-2008 SKY-MOBI AS.  All rights reserved.
**
** This file is part of the simple gui library.
** It may not be redistributed under any circumstances.
*/

#ifndef _SGL_RECT_H
#define _SGL_RECT_H

#include "sgl_gal.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * \brief check 2 rect is intersect
 *
 * \param psrc1 the first rect
 * \param psrc2 the second rect
 */
BOOL GUIAPI DoesIntersect(PRECT psrc1, PRECT psrc2);

/**
 * \brief union psrc to pdst
 *
 * \param pdst the dest rect
 * \param psrc the src rect
 */
VOID GUIAPI UnionRect(PRECT pdst, PRECT psrc);

/**
 * \brief intersect rects
 *
 * \param pdst the result rect
 * \param psrc1 the first rect
 * \param psrc2 the second rect
 */
VOID GUIAPI IntersectRect(PRECT pdst, PRECT psrc1, PRECT psrc2);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _SGL_RECT_H */

