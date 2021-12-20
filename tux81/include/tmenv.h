/*
 *	Copyright (c) 1997 BEA Systems, Inc.
 *	All rights reserved
 *
 *	THIS IS UNPUBLISHED PROPRIETARY
 *	SOURCE CODE OF BEA Systems, Inc.
 *	The copyright notice above does not
 *	evidence any actual or intended
 *	publication of such source code.
 */
#ifndef TMENV_H
#define TMENV_H 1

/* #ident	"@(#) gp/libgp/mach/winnt_ev.h	$Revision: 1.5 $" */

#ifndef WIN32
#define WIN32 1
#endif

#define _TMPROTOTYPES 1

#if defined(_TMPROTOTYPES)
#if !defined(_TMCONST)
#define _TMCONST	const
#endif
#else
#define _TMCONST
#endif


#define _TMDOWN 1	/* DOS, OS/2, Windows, NT */

#define NOWHAT 1


#define _(a) a

#define	_TM_FAR
#define _TM_NEAR
#define	_TMDLLENTRY	__stdcall
#define _TM_CDECL
#define _TM_THREADVAR

#define _TMDLLEXPORT	__declspec(dllexport)
#define _TMDLLIMPORT	__declspec(dllimport)

#if defined(__cplusplus)
#define __cplus21 1
#define __cpp_stdc 1
extern "C" {
#endif

#if (defined(WIN32) && defined(_TMWS)) && !defined(_TMDLL)
extern int _TM_FAR * _TMDLLENTRY _Uget_Uunixerr_addr(void);
extern int _TMDLLENTRY          getUunixerr(void);
#endif

extern int getopt(int, char * const *, const char *);

#if defined(__cplusplus)
}
#endif

#include <stddef.h>
#include <sys/types.h>
#include "process.h"
#define ioctl ____ioctl
#include "io.h"
#undef ioctl

#if !defined(__TURBOC__)
typedef long uid_t;
typedef long gid_t;
typedef int mode_t;
#endif

typedef long pid_t;
typedef char *caddr_t;

#if defined(__TURBOC__)
typedef long off_t;
#endif
#if defined(__STRICT_ANSI)
#define off_t _off_t
#endif

typedef size_t		isize_t;
typedef uid_t           iuid_t;
typedef gid_t           igid_t;

#define _TMNOCRYPTHDR 1
#define _TMNOCRYPT 1
#define _TML_ENDIAN 1

#define _TMPAGESIZE 	512L

typedef	int		_TMXDRINT;
typedef	unsigned int	_TMXDRUINT;
typedef	long		TM32I;
typedef	unsigned long	TM32U;

typedef int (_TMDLLENTRY * _TM_FARPROC)(void);

#define _TMDEF_UINT 1

#define _TM_WINSOCKAPI 1	

#define _GPTHREADS

#ifndef LIBBUFT_INTERNAL
#define _TMIBUFT	_TMDLLIMPORT
#else
#define _TMIBUFT
#endif

#ifndef LIBDNW_INTERNAL
#define _TMIDNW		_TMDLLIMPORT
#else
#define _TMIDNW
#endif

#ifndef LIBFML_INTERNAL
#define _TMIFML		_TMDLLIMPORT
#else
#define _TMIFML
#endif

#ifndef LIBFML32_INTERNAL
#define _TMIFML32	_TMDLLIMPORT
#else
#define _TMIFML32
#endif

#ifndef LIBFS_INTERNAL
#define _TMIFS		_TMDLLIMPORT
#else
#define _TMIFS
#endif

#ifndef LIBGP_INTERNAL
#define _TMIGP		_TMDLLIMPORT
#else
#define _TMIGP
#endif

#ifndef LIBNWI_INTERNAL
#define _TMINWI		_TMDLLIMPORT
#else
#define _TMINWI
#endif

#ifndef LIBNWS_INTERNAL
#define _TMINWS		_TMDLLIMPORT
#else
#define _TMINWS
#endif

#ifndef LIBQM_INTERNAL
#define _TMIQM		_TMDLLIMPORT
#else
#define _TMIQM
#endif

#ifndef LIBRMS_INTERNAL
#define _TMIRMS		_TMDLLIMPORT
#else
#define _TMIRMS
#endif

#ifndef LIBSQL_INTERNAL
#define _TMISQL		_TMDLLIMPORT
#else
#define _TMISQL
#endif

#ifndef LIBTMIB_INTERNAL
#define _TMITMIB	_TMDLLIMPORT
#else
#define _TMITMIB
#endif

#ifndef LIBTUX_INTERNAL
#define _TMITUX		_TMDLLIMPORT
#else
#define _TMITUX
#endif

#ifndef LIBTUX2_INTERNAL
#define _TMITUX2	_TMDLLIMPORT
#else
#define _TMITUX2
#endif

#if !defined(LIBWSC_INTERNAL) && !defined(LIBTUX2_INTERNAL)
#define _TMITUX2WSC	_TMDLLIMPORT
#else
#define _TMITUX2WSC
#endif

#if !defined(LIBWSC_INTERNAL) && !defined(LIBTUX_INTERNAL)
#define _TMITUXWSC	_TMDLLIMPORT
#else
#define _TMITUXWSC
#endif

#ifndef LIBUSORT_INTERNAL
#define _TMIUSORT	_TMDLLIMPORT
#else
#define _TMIUSORT
#endif

#ifndef LIBWSC_INTERNAL
#define _TMIWSC		_TMDLLIMPORT
#else
#define _TMIWSC
#endif

#ifndef LIBGW_INTERNAL
#define _TMIGW	_TMDLLIMPORT
#else
#define _TMIGW
#endif

#ifndef LIBGWT_INTERNAL
#define _TMIGWT	_TMDLLIMPORT
#else
#define _TMIGWT
#endif

#ifndef LIBTRPC_INTERNAL
#define _TMITRPC	_TMDLLIMPORT
#else
#define _TMITRPC
#endif

#ifndef LIBSERVER_INTERNAL
#define _TMISERVER  _TMDLLIMPORT
#else
#define _TMISERVER  _TMDLLEXPORT
#endif

#endif
