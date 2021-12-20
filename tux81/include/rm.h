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
#ifndef RM_H
#define RM_H
/* #ident	"@(#) dux/librms/rm.h	$Revision: 1.3 $" */
#ifndef TMENV_H
#include <tmenv.h>
#endif
#ifndef NOWHAT
static	char	h_rm[] = "@(#) dux/librms/rm.h	$Revision: 1.3 $";
#endif

/*	RM User Header File	*/

/*
 *	Warning: This TUXEDO header file should not be changed in any way;
 *	doing so will destroy its compatibility with TUXEDO programs and
 *	libraries.
 */

/*	This header file does not depend on any other header file. */

/*
 *	System generation parameters 
 */
#include <fml.h>
#include <fs.h>


#define RMAXNAME  14	/* maximum rm name length is = to MAXFNAME (in fs) */
#define RMAXKEYL  128	/* maximum indexed key length - must be able to fit */
#define MAXPREDF  10	/* maximum number of predicate link fields to comprise key*/

/*	Starting values for file and set id's	*/
#define RMSOFNO 0	/* start of file numbers - up to 8192 files */
#define RMSOSNO 8192	/* start of set numbers */

/* maximum degree of nway link */
#define RMMXWAY		5

/* maximum number of predicate links on a member file */
#define RMMXPRF		40

/* the following are RM limitations based on the internal data structures
   and may NOT be increased
 */
#define RMLBLK	4194304	/* 2e22 logical blocks/file */
#define RMBLKL	65536	/* 2e16 bytes/logical block */
#define RMRECL	65536	/* 2e32 bytes/record */
#define	RMRECN	512	/* records/logical block/RM file (multiple RM files
			   per FS file or block) */

/* definitions for rmsetc */
#define RMINITCURS ((short)(-1))/* used instead of fid argto rmsetc() func*/

/* definitions used for B-tree functions */
/* stored flag files, used by rmcrfi, rmchfi, rmlifi */
#define RMBTBINARY	000001		/* use binary node search */
					/* no key compression */
#define RMBTLINEAR	000002		/* use linear node search */
					/* key compression */

/* read request flags for rmbtread, rmbtreadf */
#define RMBTLT		000001		/* find less than record */
#define RMBTLE		000002		/* find less than or equal record */
#define RMBTEQ		000004		/* find equal record */
#define RMBTGE		000010		/* find greater than or equal record */
#define RMBTGT		000020		/* find greater than record */
#define RMBTKEYONLY	000040		/* apply match request to key only */
#define RMBTDATA	000100		/* read data from associated file */

/* rm_ftyp definitions */

#define RMHASH	 1	/* hash file  */
#define RMHEAP	 2	/* heap file  */
#define RMBTREE  3	/* b-tree file */
#define RMINV	 4	/* inverted index */
#define RMCLUSTERED	 5	/* clustered */
#define RMFIFO	6	/* fifo file - like heap but true fifo */
#define RMPHANT 7	/* phantom file, same as hash */


/* rm_styp definitions */

#define RMOWAY	1	/* one way set */
#define	RMTWAY	2	/* two way set */
#define	RMNTO1	3	/* n to 1 set  */
#define	RMINDXD	4	/* one-way indexed set */
#define	RMINDXD2	5	/* two-way indexed set */
#define RMNW	6	/* n-to-m link */
#define RMNW2 7	/* n-to-m tway link */


/* parameters for creating rmtbls */
struct rmtprms {
	short	maxfiles;
	short	maxlinks;
	short	maxfields;
	short	maxskeys;
	short	maxnmids;
	short	maxpreds;
};

/* parameters for creating rm files */
#define	RMEXTPERFI	50	/* see fs.h ...it should be the same number */

struct rmfprms {
	short	rm_fid;		  	/* rm file id			*/
	char	rm_fnm[RMAXNAME+1];	/* rm file name			*/
	char	fs_fnm[RMAXNAME+1];	/* fs file name			*/
	unsigned short	rm_tag;		/* tag for closely held files	*/
	short	rm_ftyp;		/* file type			*/
	short	rm_icf;			/* in core flag (0,1, or 2)	*/
	long	rm_blkl;		/* fs file block length		*/
	long	rm_dblks;		/* number of data blocks	*/
	long	rm_pblks;		/* # block pool blocks		*/
	short	rm_perm;		/* permissions			*/
	unsigned short rm_uid;		/* user id of owner		*/
	unsigned short rm_gid;		/* group id of owner		*/
	short	rm_maxwtr;		/* max waiters on queue		*/
	short	rm_mapc;		/* count of map entries/map block */
	short	rm_extno;		/* 0 sys alloc extent, otherwise user */
	struct {			/* extents		*/
		short	devx;		/* device index	*/
		long	nblk;		/* number of blocks */
	} rm_ext[RMEXTPERFI];
	long rm_flag;
	long rm_info;
};
#ifndef RMSTRFILE
#define RMSTRFILE 040		/* structured file */
#endif


/* parameters for creating rm link types */
struct rmsprms {
	short	rm_sid;			/* rm set id		*/
	char	rm_snm[RMAXNAME+1];	/* rm set name		*/
	char	rm_ownr[RMAXNAME+1];	/* rm owner file name	*/
	char	rm_mbr[RMAXNAME+1];	/* rm member file name	*/
	char	rm_inv[RMAXNAME+1];	/* rm inverse link name	*/
	short	rm_chf;			/* closely held flag (0 or 1)	*/
	short	rm_styp;		/* set type 	*/
	short	rm_perm;		/* permissions		*/
	unsigned short rm_uid;		/* user id of owner	*/
	unsigned short rm_gid;		/* group id of owner	*/
};


/* parameters for creating nway link */
struct rmnprms {
	short	rm_sid;			/* rm set id		*/
	short	rm_phid;		/* id of phantom file	*/
	char	rm_snm[RMAXNAME+1];	/* rm set name		*/
	char 	rm_file[RMMXWAY][RMAXNAME+1]; /* owner files */ 
	char 	rm_role[RMMXWAY][RMAXNAME+1]; /* roles */ 
	short	rm_nway;		/* n in nway link, ie 2 in 2 way link */
	short	rm_styp;		/* set type ntom or ntom2 	      */
	short	rm_perm;		/* permissions		*/
	unsigned short rm_uid;		/* user id of owner	*/
	unsigned short rm_gid;		/* group id of owner	*/
	short  rm_rids[RMMXWAY];	/* role ids of roles */
};

#ifdef FLD_SHORT
/* parameters for adding predicate link */
struct rmpprms {
	short rm_lid;	/* the link id of the corresponding link */
	FLDID rm_fldo[MAXPREDF];/* the fldid of the owner field to be compared*/
	FLDID rm_fldm[MAXPREDF];/* the fldid of the member field to be compared*/
	short rm_fido;	/* the file id of the member of the link */ 
	short rm_strong;/* 1 for strong links, 0 for weak links*/
	short rm_fldcnt;/* number of fields to be compared*/
};


/* parameters for creating rm field table entries */
struct rmaprms {
	FLDID	rm_fldid;		/* rm field id		*/
	char	rm_file[RMAXNAME+1];	/* file name		*/

	short	rm_key;			/* key field (primary keys)?RMPKEY */
    					/* required field?RMNON_NULL */
					/* other?RMNON_PKEY */

	short	rm_perm;		/* permissions */
	unsigned short rm_uid;		/* user id of owner	*/
	unsigned short rm_gid;		/* group id of owner	*/
	unsigned short rm_len;
	long rm_offset;			/* -1 -> system computes it */
	unsigned short rm_occur;
	short rm_nnul;			/* non-null field - i.e. required*/
};

/* possibilities for rm_key field - only one may be specified */
#define RMNON_PKEY 02	/* data field - can be null */
#define RMPKEY 04	/* PRIMARY key field */
#define RMNON_NULL 010	/* data field may not be null */

/* paramaters for creating secondary key table entries */
struct rmskprms {
	short rm_lid;			/* link maintained */
	short rm_multirec;		/* 1=> one record per occurrence */
	short rm_sparse;		/* 1=> sparse index */
	short rm_fldcnt;		/* count of fields assoc with sec. key*/
	FLDID *rm_flds;			/* fields assoc. with sec. key */
	short rm_unique;			/* 1=>unique secondary key */
};

#ifndef MAXFNAM
#define MAXFNAM 30
#endif

/* parameters for creating field name/field id mapping */
struct rmniprms {
	FLDID	rm_fldid;
	long	rm_fldno;
	short	rm_ftype;
	char	rm_fldname[MAXFNAM + 1];
};
#endif

/* structure for passing user buffers to rm functions */
struct rmbfr {
	unsigned short	len;		/* length of current value in buffer */
	unsigned short	maxlen;		/* maximum length allocated to buffer */
	char   *val;			/* value buffer */
};


/*
   Format of record address. 
*/

struct rmaddr {
	long	blk;		/* logical block in file */
	unsigned short	mrk;	/* unique identifier in directory on block */
	unsigned short	tag;	/* directory number - 1 for primary file
						     >1 for closely held file */
};

#define ADDRLEN sizeof(struct rmaddr)

/*  definitions for cursors  */

#define	RMONREC		1
#define	RMOFFREC	2

#define RMFORWARD	1
#define RMREVERSE	2

/*  Format of rm cursor.  */

struct rmcurs {
	long 		magic;	/* magic number -- not validated yet */
	short		stat;	/* cursor status	*/
	short		dir;	/* forward or reverse	*/
	long		file;	/* current file id	*/
	struct rmaddr	adr;	/* current address      */
	unsigned short	kfl;
	unsigned short  flags;	/* flags to pass to routines */
#ifdef _TMLONG64
	unsigned short	fill1;
	unsigned short	fill2;
#endif
	char		kfv[RMAXKEYL];
};

typedef struct rmcurs RMCURS;
#define RMEXCLRD 01
#define RMCLRFLAG 02

/* macro to determine direction of navigation on a set */
#define RMDRCTN(curs)	((curs)->dir == RMFORWARD ? RMFORWARD : RMREVERSE)

#define RMHSHBITS	5	/* # bits for hash functions */
#define RMHSHTYPS	(1<<RMHSHBITS)	/* # hash functions allowed */

/*	rmerror values		*/

#define RMEMINVAL	0	/* bottom of error messages	*/
#define	FSERROR		1	/* File system error */
#define	RMERECLEN	2	/* Invalid record length or record too long
				   for buffer */
#define	RMEKEYLEN	3	/* Invalid key length or key too long for
				   buffer */
#define	RMEFILE		4	/* Invalid file name or file identifier */
#define	RMENFILES	5	/* Too many files */
#define	RMEFILETYP	6	/* Invalid file type */
#define	RMESET		7	/* Invalid link name or link identifier */
#define	RMENSETS	8	/* Too many links */
#define	RMESETYP	9	/* Invalid link type */
#define	RMERMNM		10	/* Invalid rm name */
#define	RMEFSNM		11	/* Invalid fs file name */
#define	RMEINCONS	12	/* Inconsistent specification */
#define	RMENOTPRES	13	/* Record not in database */
#define	RMENTBLS	14	/* RM tables not created */
#define	RMENOSPACE	15	/* No space */
#define	RMEDUPKEY	16	/* Duplicate key */
#define	RMENONSET	17	/* Record not on link instance */
#define	RMEONSET	18	/* Record on link instance */
#define	RMETAG		19	/* Invalid file tag (clustered where primary
				   file required or visa versa) */
#define	RMEOWNER	20	/* File must be an owner of link */
#define	RMEMEMBER	21	/* File must be a member of link */
#define	RMECURS		22	/* Invalid cursor */
#define	RMEOPRTN	23	/* Invalid operation on file or link */
#define	RMEINVERSE	24	/* Cannot connect/disconnect using inverse
				   n-to-1 link */
#define	RMEBLKL		25	/* Block length not multiple of physical page 
				   size as defined in fs.h */
#define	RMEINTL		26	/* RM internal error */
#define	RMECHFLG	27	/* Invalid closely held flag value */
#define	RMEKEY		28	/* Key required but not present */
#define	RMEFLD		29	/* Invalid field name or field identifier */
#define	RMENFLDS	30	/* Too many fields */
#define	RMEFLDTYP	31	/* Invalid field type */
#define	RMEBADADR	32	/* Record not found at forwarding address */
#define	RMETBLS		33	/* RM tables already created */
#define	RMEFML		34	/* Field manipulation language error */
#define	RMEFTYPE	35	/* Fielded function used where non-field
				   function needed or visa versa */
#define	RMEITYPE	36	/* Link identifier used where file identifier
				   needed or visa versa */
#define	RMENINI		37	/* RM not initialized */
#define RMEINCORE	38	/* bad incore flag */
#define RMEUNIX		39	/* unix function call error */
#define RMEUBB		40	/* Bulletin board function error */
#define RMESKEY		41	/* Invalid secondary key identifier */
#define RMENSKEY	42	/* Too many secondary keys */
#define RMEONSKEY	43	/* Field on secondary key */
#define RMENOHASH	44	/* No hash function present */
#define RMEFPERM	45	/* Insufficient file permissions */
#define RMESPERM	46	/* Insufficient set permissions */
#define RMEDPERM	47	/* Insufficient field permissions */
#define RMEPERM		48	/* Insufficient permissions */
#define RMELTYPE	49	/* nway link function used on non nway links 
				   or vice versa*/
#define RMELTINC	50	/* nway link inconsistency-internal error*/
#define RMERMIS		51	/* roles missing or partially specified or
				duplicate on nway link */
#define RMEROLE		52	/* roles supplied non-existent on nway link*/ 
#define RMEPMIS		53	/* phantom file missing */
#define RMEPHAN		54	/* invalid operation on a phantom file*/
#define RMENOKEY	55	/* no key fields allowed on this file type */
#define RMENWAY		56	/* cardinality of nway relationship too large*/
#define RMEPNE		57	/* phantom or primary file not empty */
#define	RMENPRDS	58	/* Too many predicate links */
#define RMEMXPF		59	/* too many predicate links on file */
#define RMEPSTR		60	/* missing field required in fielded buf */
#define RMERIDKEY       61      /* rid field cannot be a primary key */
#define RMEONERID       62      /* only 1 rid field per file */
#define RMERIDINX	63	/* index file can't have a rid field*/
#define RMERORRID	64	/* field can't be both rid and rrid */
#define RMERIDCRY	65	/* rid & rrid must be carray */
#define RMERIDLEN	66	/* rid & rrid len must = 8 bytes */
#define RMESKPL		67	/* sec key used by pred link */
#define RMENORID	68	/* file does not contain rid field */
#define RMENOTRID	69	/* field not a rid field for file */
#define RMEMOWP		70	/* illegal modification of owner of predicate link*/
#define RMCONVRT	71	/* running new software on unconverted db */
#define RMECIDNT	72	/* invalid C identifier entered */
#define RMENOWAY	73	/* cannot change link type from nway to nway2 
				   or vice versa */
#define RMECARDNW	74	/* cannot change cardinality of nway link */
#define RMESETNW	75	/* cannot change nway link set name */
#define RMEFILENW	76	/* cannot change participating files in nway link */
#define RMENULL		77	/* required field missing from buffer */
#define RMEBTTAGS	78	/* inconsistent tags for B-tree file */
#define RMEBTSIBS	79	/* inconsistent siblings in B-tree file */
#define RMEBTINIT	80	/* uninitialized B-tree node */
#define RMEBTKEYVAL	81	/* invalid B-tree key value entry */
#define RMEBTFLAG	82	/* invalid B-tree request flag */
#define RMEBTBADFIT	83	/* B-tree key length/node size conflict */
#define RMEBTUNIQUE	84	/* B-tree file/function call unique conflict */
#define RMEBTSPLIT	85	/* B-tree node split error */
#define RMEBTLEV	86	/* B-tree level too large */
#define	RMEFLAG		87	/* incorrect flag value supplied or cannot change 
				   flag value for B-tree file in use */
#define	RMEINFO		88	/* incorrect info value specified */
#define	RMEBTDATA	89	/* flag value must not be ORed with RMBTDATA
				   (or DATA in rmgr), if B-tree file is specified  */
#define	RMEREC		90	/* rec must not be NULL, if flag value is ORed 
				   with RMBTDATA(or DATA in rmgr) */
#define RMEFMIOF	91	/* no matching field in owner file of pred link*/
				/* abb stands for field missing in owner file */
#define RMEWPLIS	92	/* weak predicate link illegal on structured file*/
#define RMEPLAM		93	/* predicate link already maintained */
#define RMEDDLIP	94	/* DDL operation in progress */
#define RMEINTR		95	/* signal interrupted operation */
#define	RMERSPL		96	/* recursive strong predicate link not allowed*/
#define	RMEONPRED	97	/* field used by predicate link */
#define	RMECLIU		98	/* RM catalogue in use */
#define	RMEMAXVAL	99	/* maximum rmerror value	*/


/* interface functions */

#ifdef _TMPROTOTYPES
#include <stdio.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif

extern int HASHTYPE _((int));
extern int MKHASHTYPE _((int, int));
extern void rm_error _((char *));
extern int rmadd _((short, struct rmcurs *, struct rmbfr *, struct rmbfr *));
extern int rmaddf _((short, struct rmcurs *, FBFR *));
extern int rmaddfd _((struct rmaprms *));
extern int rmaddpl _((struct rmpprms *));
extern int rmaddsk _((struct rmskprms *));
extern int rmbtread _((short, struct rmcurs *, unsigned short, struct rmbfr *, struct rmbfr *));
extern int rmbtreadf _((short, struct rmcurs *, unsigned short, FBFR *));
extern int rmchconn _((short, struct rmcurs *, struct rmcurs *));
extern int rmchd _((short, struct rmcurs *, struct rmbfr *, struct rmbfr *));
extern int rmchdf _((short, struct rmcurs *, FBFR *));
extern int rmchfi _((struct rmfprms *));
extern int rmchgsk _((struct rmskprms *));
extern int rmchln _((struct rmsprms *));
extern int rmchnw _((struct rmnprms *));
extern int rmclose _((void));
extern int rmcmpc _((struct rmcurs *, struct rmcurs *));
extern int rmconn _((short, struct rmcurs *, struct rmcurs *));
extern int rmconw _((short, struct rmcurs *, short *, struct rmbfr *, struct rmcurs *));
extern int rmconwf _((short, struct rmcurs *, short *, FBFR *, struct rmcurs *));
extern int rmcrfd _((struct rmniprms *));
extern int rmcrfi _((struct rmfprms *));
extern int rmcrln _((struct rmsprms *));
extern int rmcrnw _((struct rmnprms *));
extern int rmcrtb _((struct rmtprms *));
extern int rmlitb _((struct rmtprms *));
extern int rmcurf _((short, struct rmcurs *, FBFR *));
extern int rmcurrent _((short, struct rmcurs *, struct rmbfr *, struct rmbfr *));
extern int rmdcnw _((short, struct rmcurs *, short[]));
extern int rmdisc _((short, struct rmcurs *));
extern int rmdlt _((short, struct rmcurs *, struct rmbfr *));
extern int rmdltf _((short, struct rmcurs *, FBFR *));
extern int rmdltfd _((FLDID, short));
extern int rmdltpl _((short));
extern int rmdltsk _((short));
extern int rmdsfd _((FLDID));
extern int rmdsfi _((short));
extern int rmdsln _((short));
extern int rmdsnw _((short));
extern void rmemsg _((char *));
extern void rmuserlog _((char *));
extern char *rmstrerror _((int));
extern struct rmcurs *rmflags _((struct rmcurs *, int));
extern int rmflgval _((struct rmcurs *));
extern FLDID rmfldid _((char *));
extern char *rmfname _((FLDID));
extern int rmnmid _((struct rmniprms *, int));
extern int rmnmidr _((struct rmniprms *, int, int));
extern int rmfprint _((FBFR *, short));
extern int rmffprint _((FBFR *, FILE *, short));
extern int rmfextread _((FBFR *, FILE *, short));
extern int rmfchg _((FBFR *, FLDID, int, char *, FLDLEN, short));
extern int rmfinit _((FBFR *, FLDLEN, short));
extern int rmfget _((FBFR *, FLDID, int, char *, FLDLEN *, short));
extern char *rmffind _((FBFR *, FLDID, int, FLDLEN *, short));
extern int rmfnext _((char *, FLDID *, int *, char *, FLDLEN *, short));
extern int rmfcmp _((char *, char *, short));
extern int rmgensk _((short, int));
extern short rmfid _((char *));
extern short rmlid _((char *));
extern short rmrid _((short, char *));
extern int rmindex _((FBFR *, short, int));
extern int rminfi _((short));
extern int rmlifd _((struct rmaprms *));
extern int rmlifda _((struct rmaprms *, int));
extern int rmlifdf _((short, struct rmaprms *, int));
extern int rmlifdr _((short, struct rmaprms *, int, int));
extern int rmlifds _((short, FLDID *, int));
extern int rmlifi _((struct rmfprms *));
extern int rmlifia _((struct rmfprms *, int));
extern int rmlifir _((struct rmfprms *, int, int));
extern int rmlifisk _((short, short *, int));
extern int rmliln _((struct rmsprms *));
extern int rmlilna _((struct rmsprms *, int));
extern int rmlilnf _((short, struct rmsprms *, int));
extern int rmlilnr _((short, struct rmsprms *, int, int));
extern int rmlinw _((struct rmnprms *));
extern int rmlinwa _((struct rmnprms *, int));
extern int rmlinwf _((short, struct rmnprms *, int));
extern int rmlinwr _((short, struct rmnprms *, int, int));
extern int rmlipl _((struct rmpprms *));
extern int rmlifipl _((short, short *, int));
extern int rmlisk _((struct rmskprms *));
extern int rmliskfd _((FLDID, short *, int));
extern int rmlock _((short, int));
extern int rmmod _((struct rmcurs *, struct rmbfr *));
extern int rmmodf _((struct rmcurs *, FBFR *));
extern int rmnext _((short, struct rmcurs *, struct rmbfr *, struct rmbfr *));
extern int rmprev _((short, struct rmcurs *, struct rmbfr *, struct rmbfr *));
extern int rmnextf _((short, struct rmcurs *, FBFR *));
extern int rmprevf _((short, struct rmcurs *, FBFR *));
extern int rmnxnw _((short, struct rmcurs *, short *, struct rmbfr *));
extern int rmpvnw _((short, struct rmcurs *, short *, struct rmbfr *));
extern int rmnxnwf _((short, struct rmcurs *, short *, FBFR *));
extern int rmpvnwf _((short, struct rmcurs *, short *, FBFR *));
extern int rmopen _((char *, int));
extern int rmowned _((short, struct rmcurs *));
extern int rmowner _((short, struct rmcurs *, struct rmcurs *));
extern int rmownnw _((short, RMCURS *, RMCURS *, short *));
extern int rmprtc _((FILE *, struct rmcurs *));
extern int rmread _((short, struct rmcurs *, struct rmbfr *, struct rmbfr *));
extern int rmreadf _((short, struct rmcurs *, FBFR *));
extern int rmreadsk _((short, struct rmcurs *, FBFR *));
extern int rmnextsk _((short, struct rmcurs *, FBFR *));
extern int rmreconn _((short, struct rmcurs *, struct rmcurs *));
extern int rmrevsc _((struct rmcurs *));
extern int rmsetc _((short, struct rmcurs *));
extern int rmsetcons _((short));
extern int rmabort _((TRANID, short));
extern int rmcommit _((TRANID));
extern TRANID rmstart _((short, short, int));
extern int rmstatus _((TRANID));
extern int rmdeleg _((TRANID, int));
extern int rmchopt _((TRANID, short));
extern int rmtrparms _((TRANID, struct trparms *));
extern int rmalltrparms _((struct trparms *, int));
extern int rmmfflush _((short));
extern long rmhash _((char *, unsigned short, long, short));
extern int *_rmget_rmerror_addr _((void));

#if defined(__cplusplus)
}
#endif

#define rmerror	(*_rmget_rmerror_addr())

extern TRANID *_rmgetranid _((void));
#define Logid (*_rmgetranid())


#endif
