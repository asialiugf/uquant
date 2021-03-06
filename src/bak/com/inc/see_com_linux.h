
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _SEE_COM_LINUX_H_INCLUDED_
#define _SEE_COM_LINUX_H_INCLUDED_


#ifndef _GNU_SOURCE
#define _GNU_SOURCE             /* pread(), pwrite(), gethostname() */
#endif

#define _FILE_OFFSET_BITS  64

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>             /* offsetof() */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <glob.h>
#include <sys/vfs.h>            /* statfs() */

#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sched.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>        /* TCP_NODELAY, TCP_CORK */
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>

#include <time.h>               /* tzset() */
#include <malloc.h>             /* memalign() */
#include <limits.h>             /* IOV_MAX */
#include <sys/ioctl.h>
#include <crypt.h>
#include <sys/utsname.h>        /* uname() */

#include <dlfcn.h>




#if (SEE_HAVE_POSIX_SEM)
#include <semaphore.h>
#endif


#if (SEE_HAVE_SYS_PRCTL_H)
#include <sys/prctl.h>
#endif


#if (SEE_HAVE_SENDFILE64)
#include <sys/sendfile.h>
#else
extern ssize_t sendfile(int s, int fd, int32_t *offset, size_t size);
#define SEE_SENDFILE_LIMIT  0x80000000
#endif


#if (SEE_HAVE_POLL)
#include <poll.h>
#endif


#if (SEE_HAVE_EPOLL)
#include <sys/epoll.h>
#endif


#if (SEE_HAVE_SYS_EVENTFD_H)
#include <sys/eventfd.h>
#endif
#include <sys/syscall.h>
#if (SEE_HAVE_FILE_AIO)
#include <linux/aio_abi.h>
typedef struct iocb  see_aiocb_t;
#endif


#ifndef SEE_HAVE_SO_SNDLOWAT
/* setsockopt(SO_SNDLOWAT) returns ENOPROTOOPT */
#define SEE_HAVE_SO_SNDLOWAT         0
#endif


#ifndef SEE_HAVE_INHERITED_NONBLOCK
#define SEE_HAVE_INHERITED_NONBLOCK  0
#endif

#define SEE_HAVE_OS_SPECIFIC_INIT    1
#define see_debug_init()

extern char **environ;


#endif /* _SEE_LINUX_CONFIG_H_INCLUDED_ */
