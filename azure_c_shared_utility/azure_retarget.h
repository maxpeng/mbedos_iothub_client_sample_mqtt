#ifndef __AZURE_RETARGET_H__
#define __AZURE_RETARGET_H__

// refer https://github.com/ARMmbed/mbed-os/blob/master/platform/mbed_retarget.h
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
/* The intent of this section is to unify the errno error values to match
 * the POSIX definitions for the GCC_ARM, ARMCC and IAR compilers. This is
 * necessary because the ARMCC/IAR errno.h, or sys/stat.h are missing some
 * symbol definitions used by the POSIX filesystem API to return errno codes.
 * Note also that ARMCC errno.h defines some symbol values differently from
 * the GCC_ARM/IAR/standard POSIX definitions. The definitions guard against
 * this and future changes by changing the symbol definition as shown below. */

extern int errno;

#undef ENOENT
#define ENOENT      2       /* No such file or directory. */

#undef EIO
#define EIO         5       /* I/O error */

#undef ENXIO
#define ENXIO       6       /* No such device or address */

#undef ENOEXEC
#define ENOEXEC     8       /* Exec format error */

#undef EBADF
#define EBADF       9       /* Bad file number */

#undef EAGAIN
#define EAGAIN      11      /* Resource unavailable, try again */

#undef EWOULDBLOCK
#define EWOULDBLOCK EAGAIN  /* Operation would block */

#undef ENOMEM
#define ENOMEM      12      /* Not enough space */

#undef EACCES
#define EACCES      13      /* Permission denied */

#undef EFAULT
#define EFAULT      14      /* Bad address */

#undef EEXIST
#define EEXIST      17      /* File exists */

#undef EXDEV
#define EXDEV       18      /* Cross-device link */

#undef EINVAL
#define EINVAL      22      /* Invalid argument */

#undef ENFILE
#define ENFILE      23      /* Too many open files in system */

#undef EMFILE
#define EMFILE      24      /* File descriptor value too large */

#undef ESPIPE
#define ESPIPE      29      /* Invalid seek */

#undef ENOSYS
#define ENOSYS      38      /* Function not implemented */

#undef EOVERFLOW
#define EOVERFLOW 75 /* Value too large to be stored in data type */
#endif

#endif
