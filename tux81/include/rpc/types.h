/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T; 1991 USL	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF USL	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/* #ident	"@(#) gp/libgp/rpc/types.h	$Revision: 1.3 $" */
/*      @(#)types.h 1.23 88/10/25 SMI      */

/*
 * Rpc additions to <sys/types.h>
 */
#ifndef _RPC_TYPES_H
#define _RPC_TYPES_H

#ifndef TMENV_H
#include <tmenv.h>
#endif

#ifndef NOWHAT
static char	h_rpc_types[] = "@(#) gp/libgp/rpc/types.h	$Revision: 1.3 $";
#endif

#define	bool_t	int
#define	enum_t	int
#define __dontcare__	-1

#ifndef FALSE
#	define	FALSE	(0)
#endif

#ifndef TRUE
#	define	TRUE	(1)
#endif

#ifndef NULL
#	define NULL 0
#endif

#ifndef KERNEL
#ifdef _TMPROTOTYPES
#include <stdlib.h>
#include <string.h>
#else
#include <memory.h>
/* malloc.h stuff included in Uunix.h */
#endif
#define mem_alloc(bsize)	(char *)malloc(bsize)
#define mem_free(ptr, bsize)	free(ptr)
#else
extern char *kmem_alloc();
#define mem_alloc(bsize)	kmem_alloc((u_int)bsize)
#define mem_free(ptr, bsize)	kmem_free((caddr_t)(ptr), (u_int)(bsize))
#endif

#include <sys/types.h>
/* #include <sys/time.h> */

#ifdef _TMDEF_UINT
typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned long u_long;
#endif

#endif /* ! _RPC_TYPES_H */
