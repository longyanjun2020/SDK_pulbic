#ifndef NCCPort_I18N_H
#define NCCPort_I18N_H

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * Ncc Porting Layer: Encoding support.
 *
 * This interface provides additional charset support for the Ncc VM.
 */

#define IS_GB2312_HIGH_BYTE(c)  ((c) >= 0xA1 && (c) <= 0xF7)
#define IS_GB2312_LOW_BYTE(c)   ((c) >= 0xA1 && (c) <= 0xFE)
#define IS_GBK_HIGH_BYTE(c)     ((c) >= 0x81 && (c) <= 0xFE)
#define IS_GBK_LOW_BYTE(c)      ((c) >= 0x40 && (c) <= 0xFE && (c) != 0x7F)
#define IS_BIG5_HIGH_BYTE(c)    ((c) >= 0xA1 && (c) <= 0xF9)
#define IS_BIG5_LOW_BYTE(c)     (((c) >= 0x40 && (c) <= 0x7E) \
                                 || ((c) >= 0xA1 && (c) <= 0xFE))
#define IS_ASCII(c)             ((c) <= 127)

#define INVALID_UNICODE         0xFFFD
/**
 * @name Charset value defines
 * @ingroup i18n
 *
 * Charset value defines
 * see http://msdn.microsoft.com/library/default.asp?url=/library/en-us/intl/unicode_81rn.asp
 */
typedef enum {
    NCC_CHARSET_GBK        = 936,      /** Simplified Chinese GBK (CP936) */
    NCC_CHARSET_GB2312     = 20936,    /** Simplified Chinese GB2312 (CP936) */
    NCC_CHARSET_BIG5       = 950,      /** BIG5 (CP950) */
    NCC_CHARSET_LATIN1     = 28591,    /** ISO 8859-1, Latin 1 */
    NCC_CHARSET_UTF8       = 65001,    /** UTF-8 */
    NCC_CHARSET_UTF16LE    = 1200,     /** UTF-16 LE */
    NCC_CHARSET_UTF16BE    = 1201,     /** UTF-16 BE */
    NCC_CHARSET_UNSUPPORTED = -1
} NCCPort_NccCharset_t;

/**
 * Convert multibyte string of specified charset to unicode string.
 * Note NO terminating '\0' will be appended to the output unicode string.
 *
 * Since the default implementation of NCCPort_i18n_mbsToWcs performs necessary
 * checks on multibyte sequences and ensure *bytesConsumed (see below) has
 * the correct value, it is strongly recommended not to re-implement
 * NCCPort_i18n_mbsToWcs (as well as NCCPort_i18n_wcsToMbs) in a port unless you know
 * clearly what you're doing.
 *
 * If a port needs to utilize native charset conversion routines available
 * (e.g. MultiByteToWideChar/WideCharToMultiByte on win32 platforms), it
 * should instead implement certain NCCPort_i18n_CHARSET_mbToWc and
 * NCCPort_i18n_CHARSET_wcTomb in an overrided nccport_i18n_CHARSET.c. It's safe
 * to have single character based (mbToWc/wcToMb) porting layer than
 * the multi-character based ones (mbsToWcs/wcsToMbs) for most major
 * multibyte charsets because they have no corresponding code points in
 * the supplementary characters (U+10000 to U+10FFFF). For those that have
 * supplementray characters, we can still define multi-character based
 * porting layer for them.
 *
 * For example, for a win32 port which needs GB2312 charset support, you
 * should leave base/src/i18n/nccport_i18n.c untouched and provide your
 * implementations of NCCPort_i18n_gb2312_gbToWc and NCCPort_i18n_gb2312_wcToMb
 * in your own nccport_i18n_gb2312.c. The implementations could be as simple as:
 * <code>
 * uint16_t NCCPort_i18n_gb2312_gbToWc(uint8_t high, uint8_t low)
 * {
 *     char[2] gbs = {high, low};
 *     unsigned short wc = 0xFFFD;
 *     MultiByteToWideChar(936, 0, gbs, 2, &wc, 1);
 *     return wc;
 * }
 * </code>
 *
 *
 * Obviously, it's also much easier and less error prone to implement single
 * unicode character based and charset specific xxx_mbToWc and xxx_wcToMb
 * than the all-in-one version NCCPort_i18n_mbsToWcs/NCCPort_i18n_wcsToMbs.
 *
 * @see NCCPort_i18n_gb2312_gbToWc
 * @see NCCPort_i18n_gb2312_wcToGb
 *
 * @param charset Charset of the multibyte string.
 * @param mbs Multibyte string to be converted.
 * @param mbsLen Number of the bytes (in mbs) to be converted.
 * @param wcsBuf Buffer for the converted unicode characters.
 *               If wcsBuf is NULL, the function returns the number of unicode
 *               characters required for the buffer.
 * @param bufSizeInWideChar The size (in wide char) of wcsBuf
 * @param bytesConsumed The number of bytes in mbs that have been successfully
 *                      converted. The value of *bytesConsumed is undefined
 *                      if wcsBuf is NULL.
 *
 * @return Number of the successfully converted unicode characters if wcsBuf
 *         is not NULL. If wcsBuf is NULL, returns required unicode buffer
 *         size. -1 for unrecoverable errors.
 */
int32_t NCCPort_i18n_mbsToWcs(NCCPort_NccCharset_t charset,
        const uint8_t *mbs, int32_t mbsLen,
        uint16_t *wcsBuf, int32_t bufSizeInWideChar,
        int32_t *bytesConsumed);

/**
 * Convert unicode string to multibyte string with specified charset.
 * Note NO terminating '\0' will be appended to the output multibyte string.
 *
 * @see NCCPort_i18n_mbsToWcs
 *
 * @param charset Charset of the multibyte string to be converted to.
 * @param wcs     Unicode string to be converted.
 * @param wcsLen  Number of the unicode characters (in wcs) to be converted.
 * @param mbsBuf  Buffer for converted multibyte characters.
 *                If mbsBuf is NULL, the function returns the number of bytes
 *                required for the buffer.
 * @param bufSizeInByte The size (in byte) of mbsBuf.
 *
 * @return Number of the successfully converted bytes.
 */
int32_t NCCPort_i18n_wcsToMbs_ext(NCCPort_NccCharset_t charset,
                                  const uint16_t       *wcs,
                                  int32_t              wcsLen,
                                  uint8_t              *mbsBuf,
                                  int32_t              bufSizeInByte,
                                  int32_t              *unicodeConsumed);

int32_t NCCPort_i18n_wcsToMbs(NCCPort_NccCharset_t charset,
        const uint16_t *wcs, int32_t wcsLen,
        uint8_t *mbsBuf, int32_t bufSizeInByte);

/**
 * Convert 2 GB2312 bytes to one unicode character.
 * It's safe to return just one 16-bit unicode because GB2312 has no
 * correspoding code points in U+10000 to U+10FFFF.
 *
 * @see NCCPort_i18n_mbsToWcs
 *
 * @param high High byte of one GB2312 character. Caller (typically the
 *             default NCCPort_i18n_mbsToWcs implementation) guarantees that
 *             0xA1 <= high <= 0xF7.
 * @param low  Low byte of one GB2312 character. Caller (typically the
 *             default NCCPort_i18n_mbsToWcs implementation) guarantees that
 *             0xA1 <= low <= 0xFE.
 *
 * @return Converted unicode character on success. Returns 0xFFFD on error.
 */
uint16_t NCCPort_i18n_gb2312_gbToWc(uint8_t high, uint8_t low);

/**
 * Convert a unicode character to GB2312 encoded bytes
 * It's safe to convert one 16-bit character at one time because GB2312 has
 * no correspoding code points in U+10000 to U+10FFFF, therefore it can
 * simply return '?' for surrogate pair values (0xD800 - 0xDFFF).
 *
 * @param wc      Unicode char to converted.
 * @param gbsBuf  Buffer for converted GB2312 bytes.
 * @param bufSize Size (in byte) of gbsBuf.
 *
 * @return Number of converted GB byte(s). If the buffer is NULL or not big
 *         enough for converted bytes, no actual conversion will be done but
 *         the function will still return the number of GB byte(s) that can
 *         be converted to.
 */
int32_t NCCPort_i18n_gb2312_wcToGb(uint16_t wc, uint8_t * gbsBuf, int32_t bufSize);

/**
 * Convert 2 GBK bytes to one unicode character.
 * It's safe to return just one 16-bit unicode because GBK has no
 * correspoding code points in U+10000 to U+10FFFF.
 *
 * @see NCCPort_i18n_mbsToWcs
 *
 * @param high High byte of one GBK character. Caller (typically the
 *             default NCCPort_i18n_mbsToWcs implementation) guarantees that
 *             0x81 <= high <= 0xFE.
 * @param low  Low byte of one GBK character. Caller (typically the
 *             default NCCPort_i18n_mbsToWcs implementation) guarantees that
 *             0x40 <= low <= 0xFE.
 *
 * @return Converted unicode character on success. Returns 0xFFFD on error.
 */
uint16_t NCCPort_i18n_gbk_gbToWc(uint8_t high, uint8_t low);

/**
 * Convert a unicode character to GBK encoded bytes
 * It's safe to convert one 16-bit character at one time because GBK has
 * no correspoding code points in U+10000 to U+10FFFF, therefore it can
 * simply return '?' for surrogate pair values (0xD800 - 0xDFFF).
 *
 * @param wc      Unicode char to converted.
 * @param gbsBuf  Buffer for converted GBK bytes.
 * @param bufSize Size (in byte) of gbsBuf.
 *
 * @return Number of converted GBK byte(s). If the buffer is NULL or not big
 *         enough for converted bytes, no actual conversion will be done but
 *         the function will still return the number of GBK byte(s) that can
 *         be converted to.
 */
int32_t NCCPort_i18n_gbk_wcToGb(uint16_t wc, uint8_t * gbsBuf, int32_t bufSize);

/**
 * Convert 2 BIG5 bytes to one unicode character.
 * It's safe to return just one 16-bit unicode because BIG5 has no
 * correspoding code points in U+10000 to U+10FFFF.
 *
 * @see NCCPort_i18n_mbsToWcs
 *
 * @param high High byte of one BIG5 character. Caller (typically the
 *             default NCCPort_i18n_mbsToWcs implementation) guarantees that
 *             0xA1 <= high <= 0xF9.
 * @param low  Low byte of one BIG5 character. Caller (typically the
 *             default NCCPort_i18n_mbsToWcs implementation) guarantees that
 *             0x40 <= low <= 0x7E or 0xA1 <= low <= 0xFE.
 *
 * @return Converted unicode character on success. Returns 0xFFFD on error.
 */
uint16_t NCCPort_i18n_big5_big5ToWc(uint8_t high, uint8_t low);

/**
 * Convert a unicode character to BIG5 encoded bytes
 * It's safe to convert one 16-bit character at one time because GBK has
 * no correspoding code points in U+10000 to U+10FFFF, therefore it can
 * simply return '?' for surrogate pair values (0xD800 - 0xDFFF).
 *
 * @param wc      Unicode char to converted.
 * @param big5Buf Buffer for converted BIG5 bytes.
 * @param bufSize Size (in byte) of big5Buf.
 *
 * @return Number of converted BIG5 byte(s). If the buffer is NULL or not big
 *         enough for converted bytes, no actual conversion will be done but
 *         the function will still return the number of BIG5 byte(s) that can
 *         be converted to.
 */
int32_t NCCPort_i18n_big5_wcToBig5(uint16_t wc, uint8_t * big5Buf, int32_t bufSize);

#ifdef __cplusplus
}
#endif

#endif

