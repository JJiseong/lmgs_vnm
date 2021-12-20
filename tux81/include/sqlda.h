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
	publication of such source code.
*/
#ifndef QLSQLDA
/* #ident	"@(#) sql/libsql/sqlda.h	$Revision: 1.3 $" */
#ifndef TMENV_H
#include <tmenv.h>
#endif
#ifndef NOWHAT
static	char	h_sqlda[] = "@(#) sql/libsql/sqlda.h	$Revision: 1.3 $";
#endif

/*
 *      DEFINITIONS NEEDED BY USER APPLICATION PROGRAMS.
 *
 *      Warning: This header file should not be changed in any
 *      way; doing so will destroy the compatibility with TUXEDO programs
 *      and libraries.
 */

/* The following structure declarations are for structures passed
 * by the embedded interface to libsql.a. Their tags are declared here
 * but are fully elaborated in internal TUXEDO header files
*/
struct CURSOR;
struct STATEID;
struct SQL_TLIST;

struct SQLDA {
	short SQLD;		/* number of slots in use of SQLVAR */
	short SQLN;		/* number of slots allocted for SQLVAR */
	struct SQLVAR *SQLVAR;	/* an array of variable descriptors */
	};
#define SQL_SHORT 5
#define SQL_LONG 4
#define SQL_FLOAT 7
#define SQL_DOUBLE 8
#define SQL_CHAR -1
#define SQL_STRING 1
#define SQL_CARRAY 0


struct SQLVAR {
	char *SQLDATA;		/* pointer to host variable */
	long *SQLIND;		/* pointer to host indicator variable */
	short SQLTYPE;		/* data type */
	short SQLNULL;		/* if 1 then indicator present */
	short SQLLEN;		/* length of character data */
	short SQLSCALE;		/* unused */
	struct {
		short SQLNAMEL;	/* length of column name */
		char SQLNAMEC[19];	/* column mane or display label */
	} SQLNAME;
};

_TMISQL extern long SQLCODE;


#if defined(__cplusplus)
extern "C" {
#endif

/* EMBEDDED SQL INTERFACE FUNCTIONS */
extern void ql_emsg _((char *));
extern void qlusrlog _((char *));
extern int QLclose_db _((void));
extern int QLopendb _((char *));
extern int QLprepexec _((char **, struct SQLDA *, int, int));
extern int QLclose_cursor _((struct CURSOR *, int));
extern int QL_commit _((void));
extern int QLprepare _((char **, struct STATEID **, int));
extern int QLdelete_p _((struct CURSOR *, char *));
extern int QLexecute _((struct STATEID *, struct SQLDA *, int));
extern int QLdescribe _((struct SQLDA *, struct STATEID *));
extern int QLfetch_it _((struct CURSOR *, struct SQLDA *, int));
extern int QLopen _((struct STATEID *, struct SQLDA *, struct CURSOR **, char *));
extern int QLprepopen _((char **, struct SQLDA *, struct CURSOR **));
extern int QL_abort _((void));
extern int QLset_tran _((int, int, int));
extern int QLerror1 _((char *, char *, int));
extern int QLselect _((char **, struct SQLDA *, int, int, int));
extern int QLupdate_p _((struct SQLDA *, char **, struct CURSOR *, struct SQL_TLIST **));
extern int QLlkdb _((int));
extern int QLlktable _((char *, int));
extern int QLunlkdb _((void));
extern int QLdrop_database _((char *));

#if defined(__cplusplus)
}
#endif


#define QLSQLDA 1
#endif
