#ifndef NCCPort_I18N_INTERTAL_H
#define NCCPort_I18N_INTERTAL_H

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Lookup entry for unicode to DBCS conversion
 */
typedef struct {
    uint16_t unicodeStart;      /** Starting unicode value */
    uint16_t dbcsValueOffset;   /** Correspoding offset in the DBCS value table */
    uint32_t indexBitmap;       /** Bitmap for up to 32 following characters */
} DbcsLookupEntry;

/**
 * Modified binary search for a DbcsLookupEntry table.
 *
 * @param table DbcsLookupEntry table
 * @param tableSize Size of the table
 * @param value The value to be searched for.
 * @return The index of the value if it is found in the table; otherwise return -1
 */
int32_t dbcsBinSearch(const DbcsLookupEntry *table, int32_t tableSize, uint16_t value);

#ifdef __cplusplus
}
#endif

#endif

