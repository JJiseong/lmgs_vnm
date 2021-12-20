/*	Copyright (c) 1984 AT&T
	All rights reserved

       /units2/units/src/tuxedo/include/s.Usysflds
       Usysflds     40.1 
*/

#ifndef NOWHAT
static	char h_Usysflds[] = "@(#) tuxedo/include/Usysflds	$Revision: 1.3 $";
#endif

/* #ident	"@(#) tuxedo/include/Usysflds	$Revision: 1.3 $" */

/*	DEFINITIONS NEEDED BY USER APPLICATION PROGRAMS.

	Warning: This file should not be changed in any
	way, doing so will destroy the compatibility with TUXEDO programs
	and libraries.
*/
/*	SYSTEM RESERVED FIELD ENTRIES	*/
/*	fname	fldid            */
/*	-----	-----            */
#define	INITMSK	((FLDID32)167772161)	/* number: 1	 type: string */
#define	CURSID	((FLDID32)33554434)	/* number: 2	 type: long */
#define	CURSOC	((FLDID32)33554435)	/* number: 3	 type: long */
#define	LEVKEY	((FLDID32)167772164)	/* number: 4	 type: string */
#define	STATLIN	((FLDID32)167772165)	/* number: 5	 type: string */
#define	FORMNAM	((FLDID32)167772166)	/* number: 6	 type: string */
#define	UPDTMOD	((FLDID32)7)	/* number: 7	 type: short */
#define	SRVCNM	((FLDID32)167772168)	/* number: 8	 type: string */
#define	NEWFORM	((FLDID32)167772169)	/* number: 9	 type: string */
#define	CHGATTS	((FLDID32)201326602)	/* number: 10	 type: carray */
#define	USYS1FLD	((FLDID32)167772171)	/* number: 11	 type: string */
#define	USYS2FLD	((FLDID32)167772172)	/* number: 12	 type: string */
#define	USYS3FLD	((FLDID32)167772173)	/* number: 13	 type: string */
#define	USYS4FLD	((FLDID32)201326606)	/* number: 14	 type: carray */
#define	USYS5FLD	((FLDID32)201326607)	/* number: 15	 type: carray */
#define	USYS6FLD	((FLDID32)201326608)	/* number: 16	 type: carray */
#define	DESTSRVC	((FLDID32)167772177)	/* number: 17	 type: string */
#define	MODS	((FLDID32)201326610)	/* number: 18	 type: carray */
#define	VALONENTRY	((FLDID32)167772179)	/* number: 19	 type: string */
#define	BQCMD	((FLDID32)167772241)	/* number: 81	 type: string */
