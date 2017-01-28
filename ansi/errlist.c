/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/errlist.c,v 1.2 2005/07/27 11:53:05 philip Exp $ */

#include  <errno.h>

int errno = 0;

static const char const unknown[] = "Unknown error";

char const * const _sys_errlist[] = {
        "Error 0",                                                            /* EGENERIC */
        unknown,                      // "Not owner",                         /* EPERM */
        "No such file or directory",                                          /* ENOENT */
        unknown,                      // "No such process",                   /* ESRCH */
        unknown,                      // "Interrupted system call",           /* EINTR */
        "I/O error or not ready",                                             /* EIO */
        "Bad port number",            // "No such device or address",         /* ENXIO */
        unknown,                      // "Arg list too long",                 /* E2BIG */
        unknown,                      // "Exec format error",                 /* ENOEXEC */
        "Bad file number",                                                    /* EBADF */
        unknown,                      // "No children",                       /* ECHILD */
        unknown,                      // "Resource temporarily unavailable",  /* EAGAIN */
        unknown,                      // "Not enough core",                   /* ENOMEM */
        "Permission denied",                                                  /* EACCES */
        "Bad index, size or address", // "Bad address",                       /* EFAULT */
        unknown,                      // "Block device required",             /* ENOTBLK */
        "Resource busy",                                                      /* EBUSY */
        "File exists",                                                        /* EEXIST */
        unknown,                      // "Cross-device link",                 /* EXDEV */
        unknown,                      // "No such device",                    /* ENODEV */
        unknown,                      // "Not a directory",                   /* ENOTDIR */
        unknown,                      // "Is a directory",                    /* EISDIR */
        "Invalid argument",                                                   /* EINVAL */
        "File table overflow",                                                /* ENFILE */
        unknown,                      // "Too many open files",               /* EMFILE */
        unknown,                      // "Not a typewriter",                  /* ENOTTY */
        unknown,                      // "Text file busy",                    /* ETXTBSY */
        unknown,                      // "File too large",                    /* EFBIG */
        "No space left on device",                                            /* ENOSPC */
        "Illegal seek",                                                       /* ESPIPE */
        unknown,                      // "Read-only file system",             /* EROFS */
        unknown,                      // "Too many links",                    /* EMLINK */
        unknown,                      // "Broken pipe",                       /* EPIPE */
        unknown,                      // "Math argument",                     /* EDOM */
        unknown,                      // "Result too large",                  /* ERANGE */
        unknown,                      // "Resource deadlock avoided",         /* EDEADLK */
        "File name too long",                                                 /* ENAMETOOLONG */
//      unknown,                      // "No locks available",                /* ENOLCK */
//      unknown,                      // "Function not implemented",          /* ENOSYS */
//      unknown,                      // "Directory not empty",               /* ENOTEMPTY */
//      unknown,                                                              /* 40 */
//      unknown,                                                              /* 41 */
//      unknown,                                                              /* 42 */
//      unknown,                                                              /* 43 */
//      unknown,                                                              /* 44 */
//      unknown,                                                              /* 45 */
//      unknown,                                                              /* 46 */
//      unknown,                                                              /* 47 */
//      unknown,                                                              /* 48 */
//      unknown,                                                              /* 49 */
//      unknown,                      // "Invalid packet size",               /* EPACKSIZE */
//      unknown,                      // "Not enough buffers left",           /* EOUTOFBUFS */
//      unknown,                      // "Illegal ioctl for device",          /* EBADIOCTL */
//      unknown,                      // "Bad mode for ioctl",                /* EBADMODE */
//      unknown,                      // "Would block",                       /* EWOULDBLOCK */
//      unknown,                      // "Bad destination address",           /* EBADDEST */
//      unknown,                      // "Destination not reachable",         /* EDSTNOTRCH */
//      unknown,                      // "Already connected",                 /* EISCONN */
//      unknown,                      // "Address in use",                    /* EADDRINUSE */
//      unknown,                      // "Connection refused",                /* ECONNREFUSED */
//      unknown,                      // "Connection reset",                  /* ECONNRESET */
//      unknown,                      // "Connection timed out",              /* ETIMEDOUT */
//      unknown,                      // "Urgent data present",               /* EURG */
//      unknown,                      // "No urgent data present",            /* ENOURG */
//      unknown,                      // "No connection",                     /* ENOTCONN */
//      unknown,                      // "Already shutdown",                  /* ESHUTDOWN */
//      unknown,                      // "No such connection",                /* ENOCONN */
//      unknown,                      // "Address family not supported",      /* EAFNOSUPPORT */
//      unknown,                      // "Protocol not supported by AF",      /* EPROTONOSUPPORT */
//      unknown,                      // "Protocol wrong type for socket",    /* EPROTOTYPE */
//      unknown,                      // "Operation in progress",             /* EINPROGRESS */
//      unknown,                      // "Address not available",             /* EADDRNOTAVAIL */
//      unknown,                      // "Connection already in progress",    /* EALREADY */
};

const int _sys_nerr = sizeof(_sys_errlist) / sizeof(_sys_errlist[0]);
