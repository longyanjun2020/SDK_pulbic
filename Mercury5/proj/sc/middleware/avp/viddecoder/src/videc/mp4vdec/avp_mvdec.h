#ifndef MVDEC_H
#define MVDEC_H
/********************************************************************
	created:	2002/06/06
	created:	6:6:2002   10:49
	filename: 	.\src\mvdec.h
	file base:	mvdec
	file ext:	h

	purpose:	Motion vector decoding.
*********************************************************************/

void ATTR_INST16 fitMvInRange(mvpair* mv, mvinfo* info);
void ATTR_INST16 mp4v_find_pmv(M4V_HANDLE *hp, int x, int y, int block, mvpair *pmv);


err_type decodeVopNULL(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
err_type decodeVopMVIntra(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
err_type decodeVopDoNothing(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);

err_type ATTR_INST16 decodePVopFrameMV(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
err_type decodePVopFieldMV(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
err_type decodePVop4MV(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
err_type decodeBVopFrameMV(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
err_type decodeBVopFieldMV(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
err_type decodeDirectFrameMV(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
err_type decodeDirectFieldMV(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);

extern err_type (* const decodePVopMV[16])(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);
extern err_type (* const decodeBVopMV[4])(M4V_HANDLE *hp, int mb_xpos, int mb_ypos);

#endif
