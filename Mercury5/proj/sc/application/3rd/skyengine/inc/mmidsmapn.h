#ifndef __DSM_APN_H__
#define __DSM_APN_H__
typedef struct
{
//	char* NetId;
	unsigned short mcc;
	unsigned short mnc; 
	char *apn;
	char *userName;
	char *passWord;
	unsigned char dns[4];
	unsigned char authentication_type;
}T_DSM_APN;

T_DSM_APN* mr_getAPN(unsigned short imcc,unsigned short imnc);
#endif

/*#end#*/
