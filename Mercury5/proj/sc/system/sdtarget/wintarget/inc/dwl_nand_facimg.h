#ifndef __DWL_NAND_FACIMG_H__
#define __DWL_NAND_FACIMG_H__

#if defined(__NAND__)
s32 dwl_NandFacImgUpld(u8 u8type, void *parg);

bool dwl_NandFacImgOpen(dwl_handle_t *, void *, u32 *);
bool dwl_NandFacImgRead(dwl_handle_t, void *, u32);
bool dwl_NandFacImgClose(dwl_handle_t);

bool dwl_NandFacImgTblOpen(dwl_handle_t *, void *, u32 *);
bool dwl_NandFacImgTblRead(dwl_handle_t, void *, u32);
bool dwl_NandFacImgTblClose(dwl_handle_t);

#endif

#endif

