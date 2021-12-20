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
/* #ident	"@(#) sql/libsql/sqlcode.h	$Revision: 1.3 $" */
#ifndef SQLCODE_H
#define SQLCODE_H

#ifndef TMENV_H
#include <tmenv.h>
#endif
#ifndef NOWHAT
static	char	h_sqlcode[] = "@(#) sql/libsql/sqlcode.h	$Revision: 1.3 $";
#endif
 
/*
 *      DEFINITIONS NEEDED BY USER APPLICATION PROGRAMS.
 *
 *      Warning: This header file should not be changed in any
 *      way; doing so will destroy the compatibility with TUXEDO programs
 *      and libraries.
 */

/* return codes	*/

#define	QLMAXCODE	2
#define	QLMINCODE	-53

#define	SQL_OK		0	/* ok */

#define	QLSYNTERR	-1	/* syntax error	*/
#define	QLMEMERR	-2	/* out of memory */
#define	QLINVSTAR	-3	/* invalid use of '*' in set function */
#define	QLINVNUM	-4	/* invalid number token	*/
#define	QLINVSTR	-5	/* no ending quote for string */
#define	QLINVNAME	-6	/* invalid name	token */
#define	QLINVAVG	-7	/* invalid 'avg' */
#define	QLINVMAX	-8	/* invalid 'max' */
#define	QLINVMIN	-9	/* invalid 'min' */
#define	QLINVSUM	-10	/* invalid 'sum' */
#define	QLINVCNT	-11	/* invalid 'count' */
#define	QLINVFROM	-12	/* invalid from	clause */
#define	QLINVSC		-13	/* invalid search condition */
#define	QLINVEXP	-14	/* invalid arithmetic expression */
#define	QLCOLMATCH	-15	/* column count/data type mismatch */
#define	QLINVNEST	-16	/* invalid inner query of a nested query */
#define	QLCARDEXCEPT	-17	/* cardinality violation */
#define	QLCOLNF		-18	/* column not found */
#define	QLTBLNF		-19	/* table not found */
#define	QLDISTERR	-20	/* unused */
#define	QLEXTAGG	-21	/* invalid external reference in agg */
#define	QLBAD_TRE	-22	/* Bad structure found with parsed tree	*/
#define	QLBAD_TYP	-23	/* Unknown data	type found */
#define	QLCONSTEXCEPT	-24	/* constraint violation	*/
#define	QLCUR_NTF	-25	/* Cursor not found */
#define	QLDATAEXCEPT	-26	/* data	exception */
#define	QLDATA_MATCH	-27	/* Mismatch  of	field types */
#define	QLDUP_CUR	-28	/* Duplicate Cursor name found */
#define	QLMIXCA		-29	/* expression mixes columns and	aggregates */
#define	QLUNQHOM	-30	/* unqualified homonym */
#define	QLUNSUPP	-31	/* unsupported case */
#define	QLWRG_TYP	-32	/* Mismatch of data type */
#define	QLCUREXCEPT	-33	/* invalid cursor state	*/
#define	QLFMLERR	-34	/* fml error */
#define	QLNOTUP		-35	/* not updateable */
#define	QLRMERR		-36	/* RM error */
#define	QLSORTERR	-37	/* sort	error */
#define QLLINKERR	-38	/* invalid link reference */
#define QLUNIXERR	-39	/* unix error */
#define QLINTOERR	-40	/* degree of into clause too big */
#define QLPRECIS	-41	/* loss of precision */
#define QLUPKEY		-42	/* invalid attempt to update key */
#define QLDEADLOCK	-43	/* killed because of timeout or deadlock */
#define QLFSERR		-44	/* error came from FS function */
#define QLDDLERR	-45	/* error in processing of DDL stmt */
#define QLABORTED	-46	/* transaction aborted */
#define QLBADNO		-47	/* number of param specs and using args unequal */
#define QLNOPREP	-48	/* statement has not been prepared */
#define QLNOQUEST	-49	/* parameter specification is illegal */
#define QLINVEX		-50	/* invalid statement for prepare */
#define QLUPMAXREC	-51	/* increase the MAXRECLEN */
#define QLTEMPNAME	-52	/* error in call to tmpnam */
#define QLVARERR	-53	/* SQLN too small or SQLVAR == 0 in a describe */

#endif
