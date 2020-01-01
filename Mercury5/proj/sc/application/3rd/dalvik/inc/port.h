#ifndef PORT_H
#define PORT_H

#ifdef __cplusplus
extern "C"{
#endif

/* declarision for syscall porting layer */
//int dvm_open(const char* pathname, int flags);
//int dvm_open(const char* pathname, int flags, mode_t mode);
int dvm_open(const char* pathname, int flags, ...);
ssize_t dvm_read(int fd, void *buf, size_t count);
ssize_t dvm_write(int fd, const void *buf, size_t count);
off_t dvm_lseek(int fd, off_t offset, int whence);
int dvm_close(int fd);
int dvm_unlink(const char* pathname);
int dvm_fsync(int fd);
int dvm_fdatasync(int fd);

int dvm_truncate(const char* path, off_t length);
int dvm_ftruncate(int fd, off_t length);

int dvm_stat(const char*path, struct stat *buf);
int dvm_fstat(int fd, struct stat* buf);

struct timeval* tv;
struct timezone* tz;
int dvm_gettimeofday(struct timeval *tv, struct timezone *tz);
char* dvm_getcwd(char *buf, size_t size);

/* for mmap */
void *dvm_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int dvm_munmap(void *addr, size_t length);
int dvm_mprotect(void *__addr, size_t __len, int __prot);
int dvm_msync(void *addr, size_t length, int flags);
int dvm_madvise(void *addr, size_t length, int advice);
int dvm_isatty(int fd);
/* for mmap */

#ifdef __cplusplus
}
#endif
#endif
