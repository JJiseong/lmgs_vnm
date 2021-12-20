/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1986 AT&T; 1991 USL
	All rights reserved
*/
/* #ident	"@(#) sql/libsql/sqlca.h	$Revision: 1.3 $" */
#ifndef QLSQLCA
/* not already included */

#ifndef TMENV_H
#include <tmenv.h>
#endif
#ifndef NOWHAT
static	char	h_sqlca[] = "@(#) sql/libsql/sqlca.h	$Revision: 1.3 $";
#endif

/*
 *      DEFINITIONS NEEDED BY USER APPLICATION PROGRAMS.
 *
 *      Warning: This header file should not be changed in any
 *      way; doing so will destroy the compatibility with TUXEDO programs
 *      and libraries.
 */
#define QLOPER_LEN	256
#define QLTOK_LEN	80
#define QLSOURCELEN 128

struct sqlca_s {
	long sqlcode;
	long sqlerrd[9];
	/* 0 - reserved	       */
	/* 1 - RM error	code */
	/* 2 - number of rows processed	*/
	/* 3 - unused */
	/* 4 - FS error	code */
	/* 5 - FML error code */
	/* 6 - unix error code */
	/* 7 - unix system call	that returned error */
        char sqlwarn[8];
	/* 0 - any of sqlwarn[1-5] are set to W */
	/* 1 - truncation to fit into a character host variable */
	/* 2 - an aggregate function encountered a null value */
	/* 3 - into clause on fetch less than select list for declare */
	/* 4 - no where cluase on update or delete statement */
	/* 5 - transaction restarted */
	char operation[QLOPER_LEN];	/* operation where error occurred */
	char token[QLTOK_LEN];		/* token at which error	occurred */
	char source[QLSOURCELEN]; /* user program err/warn loc location*/ 
};
#define QLNOTFOUND 100
#define	SQLNOTFOUND 100

/* following used for sqlwarn */
#define QLWARN 0
#define QLTRUNC 1
#define QLAGNULL 2
#define QLINTO 3
#define QLNOWHERE 4
#define QLRESTART 5

/* following used for sqlerrd */
#define QLRMERROR 1
#define QLROWCOUNT 2
#define QLFSERROR 4
#define QLFMLERROR 5
#define QLUNIXERROR 6
#define QLUNIXCALL 7


#define SQLWARN0 0
#define SQLWARN1 1
#define SQLWARN2 2
#define SQLWARN3 3
#define sqlca SQLCA

_TMISQL extern struct sqlca_s SQLCA;
#define QLSQLCA 1
#endif
