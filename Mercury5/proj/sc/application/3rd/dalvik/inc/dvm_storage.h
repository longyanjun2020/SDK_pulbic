#ifndef STORAGE_HEADER__
#define STORAGE_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

/* the handle for dvm_storageXXX operations. */
typedef void *FileHandle;

/*
 * An equivalent of fopen in ANSI C.
 *
 * @param filename the path to the file to be opened.
 * @param mode the mode to open the file. It's usage is compatible with that
 *        of fopen in ANSI C.
 * @return a handle for succeeding operations. NULL if failed.
 */
extern FileHandle dvm_storageOpen(const char *filename, const char *mode);

/*
 * close previously opened file handle.
 * @return 0    success
 *         -1   if something wrong.
 */
extern int dvm_storageClose(FileHandle fh);

/*
 * read a byte into specified buffer
 * @return 0    success
 *         -1   if something wrong.
 */
extern int dvm_storageReadByte(FileHandle fh, unsigned char *val);


/*
 * read a short value into buffer. (The contents in file were stored in
 * big-endian.)
 * @return 0    success
 *         -1   if something wrong.
 */
extern int dvm_storageReadShort(FileHandle fh, unsigned short *val);

/*
 * read a short value into buffer. (The contents in file were stored in
 * big-endian.)
 * @return 0    success
 *         -1   if something wrong.
 */
extern int dvm_storageReadInt(FileHandle fh, unsigned int *val);

/* 
 * read as many bytes as specified by len. until reached eof or something wrong
 * @return bytes read. if something wrong or eof reached, the returned value
 *         is less than the param len.
 */
extern int dvm_storageRead(FileHandle fh, char *buf, int len);

/*
 * write a byte into file.
 * @return 0    success
 *         -1   if something wrong.
 */
extern int dvm_storageWriteByte(FileHandle fh, unsigned char val);

/*
 * write a short value into file. (in big-endian)
 * @return 0    success
 *         -1   if something wrong.
 */
extern int dvm_storageWriteShort(FileHandle fh, unsigned short val);

/*
 * write an integer (32-bit) into file. (in big-endian)
 * @return 0    success
 *         -1   if something wrong.
 */
extern int dvm_storageWriteInt(FileHandle fh, unsigned int val);

/*
 * write len-bytes of contents start at buf into file.
 * @return number of bytes written. if something wrong the return valuemay
 * less than param len.
 */
extern int dvm_storageWrite(FileHandle fh, const char *buf, int len);

/*
 * move the read/write position to specified position from start of file.
 * @return the position of read/write pointer after successful seek operation,
 *         -1 indicate something wrong in operation
 */
extern long dvm_storageSeek(FileHandle fh, long offset);

/*
 * return non-zero if EOF reached. otherwise return zero
 */
extern int dvm_storageEOF(FileHandle fh);
#ifdef __cplusplus
}
#endif

#endif // STORAGE_HEADER__
/* vim:set tw=78 ts=4 sw=4 et: */
