/*	
	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/* #ident	"@(#) gp/libgp/rpc/xdr.h	$Revision: 1.4 $" */
/*      @(#)xdr.h 1.26 88/12/17 SMI      */

/*
 * xdr.h, External Data Representation Serialization Routines.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

#ifndef _RPC_XDR_H
#define _RPC_XDR_H

#ifndef TMENV_H
#include <tmenv.h>
#endif

#ifndef NOWHAT
static char	h_rpc_xdr[] = "@(#) gp/libgp/rpc/xdr.h	$Revision: 1.4 $";
#endif

#include <stdio.h>
#ifdef _TMOVMS
#include <socket.h>
#endif
#include <rpc/types.h>
#include <rpc/netcvt.h>	    /* For all ntoh* and hton*() kind of macros */
#include <Uunix.h>
#if !(defined(MSDOS) || defined(__MSDOS__))
#ifndef _huge
#define _huge
#endif
#ifndef _far
#define _far
#endif
#endif

/*
 * XDR provides a conventional way for converting between C data
 * types and an external bit-string representation.  Library supplied
 * routines provide for the conversion on built-in C data types.  These
 * routines and utility routines defined here are used to help implement
 * a type encode/decode routine for each user-defined type.
 *
 * Each data type provides a single procedure which takes two arguments:
 *
 *	bool_t
 *	xdrproc(xdrs, argresp)
 *		XDR *xdrs;
 *		<type> *argresp;
 *
 * xdrs is an instance of a XDR handle, to which or from which the data
 * type is to be converted.  argresp is a pointer to the structure to be
 * converted.  The XDR handle contains an operation field which indicates
 * which of the operations (ENCODE, DECODE * or FREE) is to be performed.
 *
 * XDR_DECODE may allocate space if the pointer argresp is null.  This
 * data can be freed with the XDR_FREE operation.
 *
 * We write only one procedure per data type to make it easy
 * to keep the encode and decode procedures for a data type consistent.
 * In many cases the same code performs all operations on a user defined type,
 * because all the hard work is done in the component type routines.
 * decode as a series of calls on the nested data types.
 */

/*
 * Xdr operations.  XDR_ENCODE causes the type to be encoded into the
 * stream.  XDR_DECODE causes the type to be extracted from the stream.
 * XDR_FREE can be used to release the space allocated by an XDR_DECODE
 * request.
 */
enum xdr_op {
	XDR_ENCODE=0,
	XDR_DECODE=1,
	XDR_FREE=2
};

/*
 * This is the number of bytes per unit of external data.
 */
#define BYTES_PER_XDR_UNIT	(4)
#define RNDUP(x)  ((((x) + BYTES_PER_XDR_UNIT - 1) / BYTES_PER_XDR_UNIT) \
		    * BYTES_PER_XDR_UNIT)

#undef _
#ifdef _TMPROTOTYPES
#define _(a) a
#else
#define _(a) ()
#endif

/*
 * The XDR handle.
 * Contains operation which is being applied to the stream,
 * an operations vector for the paticular implementation (e.g. see xdr_mem.c),
 * and two private fields for the use of the particular impelementation.
 */
#ifdef _TMPROTOTYPES
struct _xdr;
#endif


#if defined(__cplusplus)
extern "C" {
#endif

struct xdr_ops {
	bool_t	(_TM_FAR *x_getlong) _((struct _xdr _TM_FAR *, long _TM_FAR *));	/* get a long from underlying stream */
	bool_t	(_TM_FAR *x_putlong) _((struct _xdr _TM_FAR *, long _TM_FAR *));	/* put a long to " */
	bool_t	(_TM_FAR *x_getbytes) _((struct _xdr _TM_FAR *, caddr_t, u_int));/* get some bytes from " */
	bool_t	(_TM_FAR *x_putbytes) _((struct _xdr _TM_FAR *, caddr_t, u_int));/* put some bytes to " */
	_TMXDRUINT	(_TM_FAR *x_getpostn) _((struct _xdr _TM_FAR *));/* returns bytes off from beginning */
	bool_t  (_TM_FAR *x_setpostn) _((struct _xdr _TM_FAR *, _TMXDRUINT));/* lets you reposition the stream */
	long _TM_FAR *	(_TM_FAR *x_inline) _((struct _xdr _TM_FAR *, u_int));	/* buf quick ptr to buffered data */
	void	(_TM_FAR *x_destroy) _((struct _xdr _TM_FAR *));	/* free privates of this xdr_stream */
};

#if defined(__cplusplus)
}
#endif


struct _xdr {
	enum xdr_op	x_op;		/* operation; fast additional param */
	struct xdr_ops _TM_FAR *x_ops;
	char _huge * 	x_public;	/* users' data */
	char _huge *	x_private;	/* pointer to private data */
	char _huge * 	x_base;		/* private used for position info */
	_TMXDRINT	x_handy;	/* extra private word */
};
typedef struct _xdr XDR;

/*
 * A xdrproc_t exists for each data type which is to be encoded or decoded.
 *
 * The second argument to the xdrproc_t is a pointer to an opaque pointer.
 * The opaque pointer generally points to a structure of the data type
 * to be decoded.  If this pointer is 0, then the type routines should
 * allocate dynamic storage of the appropriate size and return it.
 */

#if defined(__cplusplus)
extern "C" {
#endif

typedef	bool_t (_TM_FAR *xdrproc_t) _((XDR _TM_FAR *, caddr_t, u_int));

#if defined(__cplusplus)
}
#endif


/*
 * Operations defined on a XDR handle
 *
 * XDR		*xdrs;
 * long		*longp;
 * caddr_t	 addr;
 * u_int	 len;
 * u_int	 pos;
 */
#define XDR_GETLONG(xdrs, longp)			\
	(*(xdrs)->x_ops->x_getlong)(xdrs, longp)
#define xdr_getlong(xdrs, longp)			\
	(*(xdrs)->x_ops->x_getlong)(xdrs, longp)

#define XDR_PUTLONG(xdrs, longp)			\
	(*(xdrs)->x_ops->x_putlong)(xdrs, longp)
#define xdr_putlong(xdrs, longp)			\
	(*(xdrs)->x_ops->x_putlong)(xdrs, longp)

#define XDR_GETBYTES(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_getbytes)(xdrs, addr, len)
#define xdr_getbytes(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_getbytes)(xdrs, addr, len)

#define XDR_PUTBYTES(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_putbytes)(xdrs, addr, len)
#define xdr_putbytes(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_putbytes)(xdrs, addr, len)

#define XDR_GETPOS(xdrs)				\
	(*(xdrs)->x_ops->x_getpostn)(xdrs)
#define xdr_getpos(xdrs)				\
	(*(xdrs)->x_ops->x_getpostn)(xdrs)

#define XDR_SETPOS(xdrs, pos)				\
	(*(xdrs)->x_ops->x_setpostn)(xdrs, pos)
#define xdr_setpos(xdrs, pos)				\
	(*(xdrs)->x_ops->x_setpostn)(xdrs, pos)

#define	XDR_INLINE(xdrs, len)				\
	(*(xdrs)->x_ops->x_inline)(xdrs, len)
#define	xdr_inline(xdrs, len)				\
	(*(xdrs)->x_ops->x_inline)(xdrs, len)

#define	XDR_DESTROY(xdrs)				\
	(*(xdrs)->x_ops->x_destroy)(xdrs)
#define	xdr_destroy(xdrs) XDR_DESTROY(xdrs)

/*
 * Support struct for discriminated unions.
 * You create an array of xdrdiscrim structures, terminated with
 * a entry with a null procedure pointer.  The xdr_union routine gets
 * the discriminant value and then searches the array of structures
 * for a matching value.  If a match is found the associated xdr routine
 * is called to handle that part of the union.  If there is
 * no match, then a default routine may be called.
 * If there is no match and no default routine it is an error.
 */
#define NULL_xdrproc_t ((xdrproc_t)0)
struct xdr_discrim {
	int	value;
	xdrproc_t proc;
};

/*
 * In-line routines for fast encode/decode of primitve data types.
 * Caveat emptor: these use single memory cycles to get the
 * data from the underlying buffer, and will fail to operate
 * properly if the data is not aligned.  The standard way to use these
 * is to say:
 *	if ((buf = XDR_INLINE(xdrs, count)) == NULL)
 *		return (FALSE);
 *	<<< macro calls >>>
 * where ``count'' is the number of bytes of data occupied
 * by the primitive data types.
 *
 * N.B. and frozen for all time: each data type here uses 4 bytes
 * of external representation.
 */
#define IXDR_GET_LONG(buf)		((long)ntohl((u_long)*(buf)++))
#define IXDR_PUT_LONG(buf, v)		(*(buf)++ = (long)htonl((u_long)v))

#define IXDR_GET_BOOL(buf)		((bool_t)IXDR_GET_LONG(buf))
#define IXDR_GET_ENUM(buf, t)		((t)IXDR_GET_LONG(buf))
#define IXDR_GET_U_LONG(buf)		((u_long)IXDR_GET_LONG(buf))
#define IXDR_GET_SHORT(buf)		((short)IXDR_GET_LONG(buf))
#define IXDR_GET_U_SHORT(buf)		((u_short)IXDR_GET_LONG(buf))

#define IXDR_PUT_BOOL(buf, v)		IXDR_PUT_LONG((buf), ((long)(v)))
#define IXDR_PUT_ENUM(buf, v)		IXDR_PUT_LONG((buf), ((long)(v)))
#define IXDR_PUT_U_LONG(buf, v)		IXDR_PUT_LONG((buf), ((long)(v)))
#define IXDR_PUT_SHORT(buf, v)		IXDR_PUT_LONG((buf), ((long)(v)))
#define IXDR_PUT_U_SHORT(buf, v)	IXDR_PUT_LONG((buf), ((long)(v)))

#ifdef _TMPROTOTYPES
#ifdef lint
#undef RNDUP
u_int
RNDUP(u_int);
#undef XDR_GETLONG
bool_t
XDR_GETLONG(XDR *, long *);
#undef xdr_getlong
bool_t
xdr_getlong(XDR *, long *);
#undef XDR_PUTLONG
bool_t
XDR_PUTLONG(XDR *, long *);
#undef xdr_putlong
bool_t
xdr_putlong(XDR *, long *);
#undef XDR_GETBYTES
bool_t
XDR_GETBYTES(XDR *, caddr_t, register u_int);
#undef xdr_getbytes
bool_t
xdr_getbytes(XDR *, caddr_t, register u_int);
#undef XDR_PUTBYTES
bool_t
XDR_PUTBYTES(XDR *, caddr_t, register u_int);
#undef xdr_putbytes
bool_t
xdr_putbytes(XDR *, caddr_t, register u_int);
#undef XDR_GETPOS
_TMXDRUINT
XDR_GETPOS(XDR *);
#undef xdr_getpos
_TMXDRUINT
xdr_getpos(XDR *);
#undef XDR_SETPOS
bool_t
XDR_SETPOS(XDR *, _TMXDRUINT);
#undef xdr_setpos
bool_t
xdr_setpos(XDR *, _TMXDRUINT);
#undef XDR_INLINE
long
XDR_INLINE(XDR *, int);
#undef xdr_inline
long
xdr_inline(XDR *, int);
#undef XDR_DESTROY
void
XDR_DESTROY(XDR *);
#undef xdr_destroy
void
xdr_destroy(XDR *);
#undef IXDR_GET_LONG
long
IXDR_GET_LONG(long *);
#undef IXDR_PUT_LONG
bool_t
IXDR_PUT_LONG(char _huge *, long);
#undef IXDR_GET_BOOL
bool_t
IXDR_GET_BOOL(bool_t *);
#undef IXDR_GET_ENUM
long
IXDR_GET_ENUM(long *);
#undef IXDR_GET_U_LONG
u_long
IXDR_GET_U_LONG(u_long *);
#undef IXDR_GET_SHORT
short
IXDR_GET_SHORT(short *);
#undef IXDR_GET_U_SHORT
u_short
IXDR_GET_U_SHORT(u_short *);
#undef IXDR_PUT_BOOL
bool_t
IXDR_PUT_BOOL(char _huge *, bool_t);
#undef IXDR_PUT_ENUM
bool_t
IXDR_PUT_ENUM(char _huge *, long);
#undef IXDR_PUT_U_LONG
bool_t
IXDR_PUT_U_LONG(char _huge *, u_long);
#undef IXDR_PUT_SHORT
bool_t
IXDR_PUT_short(char _huge *, short);
#undef IXDR_PUT_U_SHORT
bool_t
IXDR_PUT_U_SHORT(char _huge *, u_short);
#endif
#endif

#undef _
#ifdef _TMPROTOTYPES
#define _(a) a
#else
#define _(a) ()
#endif
/*
 * These are the "generic" xdr routines.
 */

#if defined(__cplusplus)
extern "C" {
#endif

extern bool_t	_TM_FAR xdr_void _((void));
extern bool_t	_TM_FAR xdr_int _((XDR _TM_FAR *, int _TM_FAR *));
extern bool_t	_TM_FAR xdr_u_int _((XDR _TM_FAR *, u_int _TM_FAR *));
extern bool_t	_TM_FAR xdr_long _((register XDR _TM_FAR *, long _TM_FAR *));
extern bool_t	_TM_FAR xdr_u_long _((register XDR _TM_FAR *, u_long _TM_FAR *));
extern bool_t	_TM_FAR xdr_short _((register XDR _TM_FAR *, short _TM_FAR *));
extern bool_t	_TM_FAR xdr_u_short _((register XDR _TM_FAR *, u_short _TM_FAR *));
extern bool_t	_TM_FAR xdr_bool _((register XDR _TM_FAR *, bool_t _TM_FAR *));
extern bool_t	_TM_FAR xdr_enum _((XDR _TM_FAR *, enum_t _TM_FAR *));
extern bool_t	_TM_FAR xdr_array _((register XDR _TM_FAR *, caddr_t _TM_FAR *, u_int _TM_FAR *, u_int, u_int, xdrproc_t));
extern bool_t	_TM_FAR xdr_bytes _((register XDR _TM_FAR *, char _TM_FAR *_TM_FAR *, register u_int _TM_FAR *, u_int));
extern bool_t	_TM_FAR xdr_opaque _((register XDR _TM_FAR *, caddr_t, register u_int));
extern bool_t	_TM_FAR xdr_string _((register XDR _TM_FAR *, char _TM_FAR *_TM_FAR *, u_int));
extern bool_t	_TM_FAR xdr_union _((register XDR _TM_FAR *, enum_t _TM_FAR *, char _TM_FAR *, struct xdr_discrim _TM_FAR *, xdrproc_t));
#ifndef KERNEL
extern bool_t	_TM_FAR xdr_char _((XDR *, char *));
extern bool_t	_TM_FAR xdr_u_char _((XDR *, unsigned char *));
extern bool_t	_TM_FAR xdr_vector _((register XDR *, register char *, register u_int, register u_int, register xdrproc_t));
extern bool_t	_TM_FAR xdr_float _((register XDR *, register float *));
extern bool_t	_TM_FAR xdr_double _((register XDR *, double *));
extern bool_t	_TM_FAR xdr_reference _((register XDR *, caddr_t *, u_int, xdrproc_t));
extern bool_t	_TM_FAR xdr_pointer _((register XDR *, char **, u_int, xdrproc_t));
extern bool_t	_TM_FAR xdr_wrapstring _((XDR *, char **));
#endif /* !KERNEL */

#if defined(__cplusplus)
}
#endif


/*
 * Common opaque bytes objects used by many rpc protocols;
 * declared here due to commonality.
 */
#define MAX_NETOBJ_SZ 1024 
struct netobj {
	u_int	n_len;
	char	_TM_FAR *n_bytes;
};
typedef struct netobj netobj;

#if defined(__cplusplus)
extern "C" {
#endif

extern bool_t   _TM_FAR xdr_netobj _((XDR _TM_FAR *, struct netobj _TM_FAR *));

/*
 * These are the public routines for the various implementations of
 * xdr streams.
 */

/* Free a data structure using XDR */
extern void _TM_FAR xdr_free _((xdrproc_t, char _TM_FAR *));
/* XDR using memory buffers */
extern void   _TM_FAR xdrmem_create _((register XDR _TM_FAR *, caddr_t, _TMXDRUINT, enum xdr_op));
#ifndef KERNEL
/* XDR using stdio library */
extern void   _TM_FAR xdrstdio_create _((register XDR _TM_FAR *, FILE _TM_FAR *, enum xdr_op));
/* XDR pseudo records for tcp */
extern void   _TM_FAR xdrrec_create _((register XDR _TM_FAR *, register u_int, register u_int, caddr_t, int (_TM_FAR *)(caddr_t, caddr_t, int), int (_TM_FAR *)(caddr_t, caddr_t, int)));
/* make end of xdr record */
extern bool_t _TM_FAR xdrrec_endofrecord _((XDR _TM_FAR *, bool_t));
/* move to beginning of next record */
extern bool_t _TM_FAR xdrrec_skiprecord _((XDR _TM_FAR *));
/* true if no more input */
extern bool_t _TM_FAR xdrrec_eof _((XDR _TM_FAR *));
#else
extern void xdrmbuf_init();		/* XDR using kernel mbufs */
#endif /* !KERNEL */

#if defined(__cplusplus)
}
#endif


#endif /* !_RPC_XDR_H */
