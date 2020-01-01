/***************************************************************************/
/*                                                                         */
/*  svotval.h                                                              */
/*                                                                         */
/*    The FreeType OpenType validation service (specification).            */
/*                                                                         */
/*  Copyright 2004, 2006 by                                                */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/
/*  MStar Semiconductor, Inc. hereby chooses to receive license on the     */
/*  FreeType 2 font engine under the FreeType License, found in the file   */
/*  'FTL.TXT'                                                              */
/***************************************************************************/

#ifndef __SVOTVAL_H__
#define __SVOTVAL_H__

#include FT_OPENTYPE_VALIDATE_H
#include <ftvalid.h>

FT_BEGIN_HEADER


#define FT_SERVICE_ID_OPENTYPE_VALIDATE  "opentype-validate"


  typedef FT_Error
  (*otv_validate_func)( FT_Face volatile  face,
                        FT_UInt           ot_flags,
                        FT_Bytes         *base,
                        FT_Bytes         *gdef,
                        FT_Bytes         *gpos,
                        FT_Bytes         *gsub,
                        FT_Bytes         *jstf );


  FT_DEFINE_SERVICE( OTvalidate )
  {
    otv_validate_func  validate;
  };

  /* */


FT_END_HEADER


#endif /* __SVOTVAL_H__ */


/* END */