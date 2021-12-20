/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1984 AT&T; 1991 USL
	All rights reserved
*/
#ifndef RESTARTH
#define RESTARTH 1

/* #ident	"@(#) dux/libfs/restart.h	$Revision: 1.3 $" */
#ifndef TMENV_H
#include <tmenv.h>
#endif
#ifndef NOWHAT
static	char	h_restart[] = "@(#) dux/libfs/restart.h	$Revision: 1.3 $";
#endif

/*
 *	FS RESTART DEFINITIONS NEEDED BY USER APPLICATION PROGRAMS.
 *
 *
 *	Warning: This TUXEDO header file should not be changed in any
 *	way, doing so will destroy the compatibility with TUXEDO programs
 *	and libraries.
 */

/*
 *	This TUXEDO header file depends on the following header files 
 *	which should be included prior to this file:
 *
 *	#include <setjmp.h>
 *	#include "fs.h"
 */
#include <fs.h>


#if defined(__cplusplus)
extern "C" {
#endif

extern	int	dorestart _((int *, int *, TRANID *));
extern	int	setrestart _((int, TRANID *));
extern	int	trsrp _((void));

#if defined(__cplusplus)
}
#endif


/* special limit for restartable transactions */
#define MAXRSTR		1	/* restartable transactions per process */

struct trsenv {
	jmp_buf	trenv;	/* stack -- restart point */
	TRANID	trid;	/* transaction id */
	short	ttx;	/* index to the transaction table */
};

extern struct trsenv TRrestp[MAXRSTR];

/* The macro TRP permits the definition of restart points. All parameters
   are output parameters: rp contains the restart point
			  rest is the result of the macro
				-1	there is an error
				 0	normal return
				 1	a transaction is restarting
			  TRANID contains the transaction id of the tran
			       which is restarting or -1 otherwise

   This macro should be called from the "root" where all DB calls are realized.
   This is because of the setjmp operation: contexts saved by this operation
   are lost when the function which set it returns.

   A restart point is associated with a transaction when the last one is
   started  (i.e. trstart(degree,options, rp))

   When a restartable transaction associated with a rp restart point
   is killed by a deadlock problem, the control will be tranfered
   (i.e. longjmp) to this rp restart point.

   TRrestp is a table on the process space containing the association between
   transactions and the stack context saved by setjmp. (In general, the restart
   property will only apply to PSWAIT (wait with process suspension) and
   CLWAIT (wait with client process suspension) transactions).
   
*/

#define TRP(rp,rest,TRANID) \
	if((rp = trsrp()) < 0) { \
		rest = -1; \
		TRANID = -1; \
	} else { \
		rest = 0; \
		while((rp = setjmp(TRrestp[rp].trenv)) > 0) { \
			(void)dorestart(&rp, &rest, &TRANID); \
		} \
		if(!rest) { \
			(void)setrestart(rp, &TRANID); \
		} \
	} 

#endif
