#ifndef __NEMOMP_STORAGE_H__
#define __NEMOMP_STORAGE_H__

// 20081103: Added for rms.c using jam flag
#define USE_JAM_STORAGE		1

/* DRM defines for instalation */
#define DRM_INVALID_FORMAT                     (-2)
#define DRM_PROCESS_ERROR                      (-1)

extern nm_char *running_suite_storage_name;
extern nm_uint32 java_total_used_space;
extern nm_uint32 max_java_use_space;

extern nm_int32 nemomp_jam_check_and_create_folder(nm_wchar *folder);
extern nm_uint32 nemomp_jam_get_free_space(nm_char* workDirPath); // 20090818: Changed; 20081203: Changed

extern nm_int32 nemomp_jam_drm_decode_file(nm_wchar *p_jar_path);

extern nm_int32 nemomp_jam_encrypt_jar(nm_wchar* p_jar_path, nm_int32* return_size); // 20081125: Added

#endif /* __NEMOMP_STORAGE_H__ */
