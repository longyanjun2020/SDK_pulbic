#ifndef __NEMOMP_JAM_INFO_H__
#define __NEMOMP_JAM_INFO_H__

typedef enum
{
    NM_JAM_LIST_PARSE_FULL_MODE,   /* Full info mode */
    NM_JAM_LIST_PARSE_SMALL_MODE   /* Small info mode */
} nm_jam_list_parse_mode_enum;

typedef struct nm_suite_icon_info_t
{
    nm_int32 icon_size;
    nm_int32 icon_width;
    nm_int32 icon_height;
    nm_uint8 *icon_data; /* ARGB8888 */
} nm_suite_icon_info;

typedef struct nm_midlet_info_t
{
    struct nm_midlet_info_t *mid_next; /* pointer to next node */

    nm_wchar *mid_name;			/* MIDlet-Name-X */
    nm_suite_icon_info mid_icon;	/* MIDlet Icon */
} nm_midlet_info;

typedef struct nm_suite_info_t
{
    nm_int32 mid_count;			 /* How many MIDlets in this MIDletSuite */
    nm_int32 mid_info_size;		/* MIDlet-Data-Size */
    nm_midlet_info *mid_list;
} nm_suite_info;

typedef struct nm_suite_detail_t
{
    struct nm_suite_detail_t *suite_detail_next;   /* pointer to next node */

    nm_int32 mids_info_size; /* internal use, size of mids_info_rawdata */
    nm_uint8 *mids_info_rawdata;   /* pointer to mids info raw data to speed up release */
    nm_wchar *mids_name;		/* MIDletSuite Name */
    nm_wchar *mids_root;
    nm_wchar *jad_url;
    nm_wchar *jar_url;			 /*MIDlet-JAR-URL */
    nm_wchar *website;
    nm_suite_icon_info mids_icon;	/* MIDletSuite Icon */
    nm_suite_info mid_info;		/* Other Information */
    nm_int32 mids_size;			/* MIDlet-JAR-Size */
    nm_wchar *mids_version;		/* MIDlet-Version */
    nm_wchar *mids_vendor;		/* MIDlet-Vendor */
    nm_wchar *mids_description;		/* MIDlet-Description */
    nm_bool mids_authorized;
    nm_wchar *mids_authorized_by;
    nm_wchar *mids_auto_start;		/* MIDlet-Push-X */
} nm_suite_detail;

typedef struct nm_suites_list_t
{
    nm_int32 mids_count;                   /* Total mids count */
    nm_int32 mids_avail_indx;              /* Available mids on list start index */
    nm_int32 mids_avail_count;             /* Available mids on list count */
    nm_suite_detail *mids_info_list;  /* Available mids on list */
} nm_suites_list;

#endif /* __NEMOMP_JAM_INFO_H__ */
