#ifndef __UNFD_DEVICE_H__
#define __UNFD_DEVICE_H__

#include "drvNAND.h"
#if IF_IP_VERIFY
#if defined(H9LA25G25HAMBR) && H9LA25G25HAMBR
	#define NAND_DEVICE_ID               "\xAD\x35"
	#define NAND_DEVICE_ID_LEN           2
	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x20

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C3TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(H8ACU0CE0DAR) && H8ACU0CE0DAR
	#define NAND_DEVICE_ID               "\xAD\x76"
	#define NAND_DEVICE_ID_LEN           2
	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x20

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(TY9A0A111443KA) && TY9A0A111443KA
    #define NAND_DEVICE_ID			 "\x98\xA1\x00\x15\x72\x14\x02"
    #define NAND_DEVICE_ID_LEN			 7
    #define NAND_BLK_CNT				 0x400
    #define NAND_BLK_PAGE_CNT			 0x40

    #define NAND_RW_ADR_CYCLE_CNT		 ADR_C4TFS0
    #define NAND_E_ADR_CYCLE_CNT		 ADR_C2TRS0
    #define NAND_ECC_TYPE				 ECC_TYPE_RS

    #define NAND_PAGE_BYTE_CNT			 0x800
    #define NAND_SPARE_BYTE_CNT 		 0x40
    #define NAND_SECTOR_BYTE_CNT		 0x200


#elif defined(TY8A0A111178KC4) && TY8A0A111178KC4
	#define NAND_DEVICE_ID               "\x98\xC1\x90\x55\x76\x14"
	#define NAND_DEVICE_ID_LEN           6
	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(TY890A111229KC40) && TY890A111229KC40
	#define NAND_DEVICE_ID               "\x98\xD0\x00\x15\x72\x14"
	#define NAND_DEVICE_ID_LEN           6
	#define NAND_BLK_CNT                 0x200
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(TY8A0A111162KC40) && TY8A0A111162KC40 
	#define NAND_DEVICE_ID               "\x98\xA1\x90\x15\x76\x14"
	#define NAND_DEVICE_ID_LEN           6
	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(K9F4G08X0A) && K9F4G08X0A /* K9F4G08U0A, K9F4G08U0A */
	#define NAND_DEVICE_ID               "\xEC\xDC\x14\x25\x54"
	#define NAND_DEVICE_ID_LEN           5
	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x80
	
	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS
	
	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200


#elif defined(K9F1G08X0B) && K9F1G08X0B /* K9F1G08U0B, K9F1G08B0B */
	#define NAND_DEVICE_ID               "\xEC\xE1\x00\x85\x40"
	#define NAND_DEVICE_ID_LEN           5
	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40
	
	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS
	
	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

	
#elif defined(K9F1G08X0C) && K9F1G08X0C /* K9F1G08U0C, K9F1G08B0C */
	#define NAND_DEVICE_ID               "\xEC\xF1\x00\x95\x40"
	#define NAND_DEVICE_ID_LEN           5
	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(K522H1GACE) && K522H1GACE /* K522H1GACE, K522H1GACE */
	#define NAND_DEVICE_ID               "\xEC\xBA\x00\x55\x44"
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(H27UAG8T2M) && H27UAG8T2M
	#define NAND_DEVICE_ID               "\xAD\xD5\x14\xB6\x44"
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x80

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x1000
	#define NAND_SPARE_BYTE_CNT          0x80
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(H27UAG8T2M_FAKE2K) && H27UAG8T2M_FAKE2K
	#define NAND_DEVICE_ID               "\xAD\xD5\x14\xB6\x44"
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x80

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_24BIT1KB

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x80
	#define NAND_SECTOR_BYTE_CNT         0x400

#elif defined(H27UAS08561) && H27UAS08561
	#define NAND_DEVICE_ID               "\xAD\x75"
	#define NAND_DEVICE_ID_LEN           2
	
	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x20
	
	#define NAND_RW_ADR_CYCLE_CNT        ADR_C3TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS
	
	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10
	#define NAND_SECTOR_BYTE_CNT         0x200


#elif defined(NAND256W3A) && NAND256W3A
	#define NAND_DEVICE_ID               "\x20\x75"
	#define NAND_DEVICE_ID_LEN           2

	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x20

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C3TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(NAND512W3A2C) && NAND512W3A2C
	#define NAND_DEVICE_ID               "\x20\x76"
	#define NAND_DEVICE_ID_LEN           2

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x20

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(H27UF081G2A) && H27UF081G2A
	#define NAND_DEVICE_ID               "\xAD\xF1\x80\x1D"
	#define NAND_DEVICE_ID_LEN           4

	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(H27U1G8F2B) && H27U1G8F2B
	#define NAND_DEVICE_ID               "\xAD\xF1\x00\x15"
	#define NAND_DEVICE_ID_LEN           4

	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(HY27UF084G2B) && HY27UF084G2B
	#define NAND_DEVICE_ID               "\xAD\xDC\x10\x95\x54"
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(K9HAG08U1M) && K9HAG08U1M
	#define NAND_DEVICE_ID               "\xEC\xD3\x55\x25\x58"
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x80

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200

#elif defined(K511F12ACA) && K511F12ACA
	#define NAND_DEVICE_ID               "\xEC\xA1\x00\x15\x40"
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40
	#define NAND_SECTOR_BYTE_CNT         0x200
	
#elif defined(PIUXGA30AT) && PIUXGA30AT
	#define NAND_DEVICE_ID               "\xC8\xD5\x14\x29\x34\x01\x7F\x7F\x7F\x7F\x7F"
	#define NAND_DEVICE_ID_LEN           11
	
	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x80
	
	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS
	
	#define NAND_PAGE_BYTE_CNT           0x1000
	#define NAND_SPARE_BYTE_CNT          0x80
	#define NAND_SECTOR_BYTE_CNT         0x200

#else
	#error "No NAND device specified\n"
#endif
#endif // IF_IP_VERIFY
#endif /* __UNFD_DEVICE_H__ */
