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
#define	INITMSK	((FLDID)40961)	/* number: 1	 type: string */
#define	CURSID	((FLDID)8194)	/* number: 2	 type: long */
#define	CURSOC	((FLDID)8195)	/* number: 3	 type: long */
#define	LEVKEY	((FLDID)40964)	/* number: 4	 type: string */
#define	STATLIN	((FLDID)40965)	/* number: 5	 type: string */
#define	FORMNAM	((FLDID)40966)	/* number: 6	 type: string */
#define	UPDTMOD	((FLDID)7)	/* number: 7	 type: short */
#define	SRVCNM	((FLDID)40968)	/* number: 8	 type: string */
#define	NEWFORM	((FLDID)40969)	/* number: 9	 type: string */
#define	CHGATTS	((FLDID)49162)	/* number: 10	 type: carray */
#define	USYS1FLD	((FLDID)40971)	/* number: 11	 type: string */
#define	USYS2FLD	((FLDID)40972)	/* number: 12	 type: string */
#define	USYS3FLD	((FLDID)40973)	/* number: 13	 type: string */
#define	USYS4FLD	((FLDID)49166)	/* number: 14	 type: carray */
#define	USYS5FLD	((FLDID)49167)	/* number: 15	 type: carray */
#define	USYS6FLD	((FLDID)49168)	/* number: 16	 type: carray */
#define	DESTSRVC	((FLDID)40977)	/* number: 17	 type: string */
#define	MODS	((FLDID)49170)	/* number: 18	 type: carray */
#define	VALONENTRY	((FLDID)40979)	/* number: 19	 type: string */
#define	BQCMD	((FLDID)41041)	/* number: 81	 type: string */
