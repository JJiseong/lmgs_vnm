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
#ifndef FSH
#define FSH 1
/* #ident	"@(#) dux/libfs/fs.h	$Revision: 1.4 $" */
#ifndef TMENV_H
#include <tmenv.h>
#endif
#ifndef NOWHAT
static	char	h_fs[] = "@(#) dux/libfs/fs.h	$Revision: 1.4 $";
#endif

/*
 *	FS DEFINITIONS NEEDED BY USER APPLICATION PROGRAMS.
 *
 *
 *	Warning: This TUXEDO header file should not be changed in any
 *	way.  Doing so will destroy the compatibility with TUXEDO programs
 *	and libraries.
 */

#include <Uunix.h>
#include <oxa.h>

/*
 *	System configuration parameters.
 */
/* set PAGESIZE for machine - unit of raw i/o */
#undef PAGESIZE
#define PAGESIZE	_TMPAGESIZE

#if PAGESIZE >= 4096
#define MAXBLKL		(4*PAGESIZE)	/* max logical block size */
#else
#define MAXBLKL		(16*PAGESIZE)	/* max logical block size */
#endif

#define MAXDEV		25		/* max number of devices which
					   database may span -
					   (Some systems may be limited by the
					   number of UNIX files which a process 
					   may have open) */

#define EXTPERFI	50		/* extents per file - maximum number
					   that can be allocated */

#define MAXFNAME	14		/* max fs file name length */

#ifndef GP_DEVICE_NAME
#define GP_DEVICE_NAME	256		/* max fs device name length */
#define GP_SHORT_DEVICE_NAME	64	/* max fs device name length */
#define GP_NDMAP   	50	        /* number of partitions for free
					   space for a device in the device
					   list */
#define GP_LOGICAL_NAME	18		/* logical name of devices/tables */
#define GP_N_UDLDEV	25		/* maximum number of devices in
					   universal device list */
#endif

/* for upward compatibility */
#define NDMAP		GP_NDMAP
#define MAXDNAME	GP_DEVICE_NAME
#define NFSDEV		GP_N_UDLDEV

/*
 *	file modes for open, dbopen, locks.
 */

#define FSRDONLY  1	/* corresponds to a share lock */
#define FSWRONLY  2	/* corresponds to an exclusive lock */
#define	FSRDWR    3	/* corresponds to an exclusive lock */

/*
 *	Special flag for dbopen. 
 *	(Used in combination with file open modes.)
 * 	Disables the default the automatic Warm Start.
 *	Mainly for use with C programs calling fslog().
 */
#define FSNOSTART  	002000	/* No Warm Start, (ok if DB not ready) */

/* 
 *	process flags 
 */
#define	 PACTIVE	000001	/* process is active */
#define  PWAITLCK	000002	/* process is waiting for a lock */
#define  PWAITSEM	000004	/* process waits for semaphore */
#define  PWAITCA	000010	/* process waits for Commit Area */
#define  PDEAD		000020	/* process is dead */
#define  PDETACH	000040	/* process is detached */
#define  PTCOMMIT	000100	/* transaction in process is commiting. */
				/* includes pre-committing. */
#define  PWAITLOG	000200	/* process waits for synchronous logging */
#define	 PWAITDELEG	000400	/* process waiting for delegation */


/*
 *	transaction status values
 */
#define TRABORT		010001	/* transaction is aborting or MUST ABORT. */
#define TRWAIT		011002	/* transaction is waiting for resource. */
#define TRPRECOM	032011	/* precommit phase. */
#define TR1PCOM		032017  /* Completed first phase commit. May abort */
#define TRCOMMIT	022013	/* Completed precommit. May not abort */
#define TRACTIVE	070023	/* Transaction is active. */

/*	status argument for rmabort() */
#define TRTEMP          TRABORT  /* used only as arg to rmabort(). */
#define TRFATAL         TRABORT  /* used only as arg to rmabort(). */

/*
 *	transaction flags (options for rmstart())
 */
#define NOLRW		   000		/* option by default: NO of all*/
#define NOWAIT             000		/* no waiting for resources */
#define LOGGING		   001		/* logging if on-- no logging if off */
#define RESTART		   002		/* restartable on--no restart if off*/
#define PSWAIT		   004		/* wait--process is suspended */
#define NPWAIT		   010		/* wait--process is not suspended*/
#define TRDONLY		  0200		/* tran declared to be rdonly by user */
#define SYNCLOGGING      01001		/* synchronous logging if on */
#define TRPUBLIC	 04000		/* TA is public (may be delegated 
					   by other procs.) */

/*
 *	transaction degrees of consistency for concurrency control
 */

#define NOCONS  1	/* corresponds to Gray's Level 0 */
#define LOCONS	2	/* corresponds to Gray's Level 2 */
#define HICONS 	3	/* corresponds to Gray's Level 3 */
#define DNOCONS 4	/* deferred NOCONS -- Gray's level 1 */

#define NORPOINT	-1		/* Invalid restart point */

/*
 *	Values for fs_flags
 */
#define FSSTATSON	001		/* statistics enabled */

/*
 *	Indices into pseu_ext array (when it is used)
 */
#define FSNPSEUFI	5		/* number of pseudo files */

#define FSFCB		0		/* file control block */
#define FSSPR		1		/* superblock */
#define FSFSP		2		/* free space list */
#define FSSWP		3		/* swap area */
#define FSCMT		4		/* commit area */

/* defines for file incore types */
#define NINCORE		00		/* on-disk -- standard file */
#define PINCORE		01		/* fixed incore forever */
#define MINCORE		04		/* memory incore file -- shadowed */
#define CPINCORE	020		/* contiguous permanent incore */

/*
 *	---------- Type Definitions ----------
 */
typedef long	TRANID;			/* Transaction Identifier */

/*
 *	---------- Data structures ----------
 */

struct	fs_freemap {		/* Free space map info. */
	long size;		/* No of pages in free space fragment. */
	unsigned long addr;	/* Physical page no. of free space frag. */
};

struct dbdlparms {		/* parameters for device list ddl */
	short	fs_dbindex;	/* index in UDL device list */
	long	fs_dbstart;	/* starting physical block */
	long	fs_dbsize;	/* size in physical blocks */
	long 	fs_dbnmap;	/* No. of free space entries in use in map.*/
	long 	fs_dbnavail;	/* No. of unused entries available in map.*/
	struct	fs_freemap *fs_dbfreemap; /* Malloc'd free Space map */
};

struct dlparms {			/* parameters for device list ddl */
	short	fs_dlindex;		/* index in device list */
	char	fs_dlname[GP_DEVICE_NAME+1];	/* device name */
	long	fs_dlstart;		/* starting physical block */
	long	fs_dlsize;		/* size in physical blocks */
	long 	fs_dlnmap;	/* # of free space entries in use in map.*/
	long 	fs_dlnavail;	/* # unused entries available in map.*/
	struct	fs_freemap fs_dlfreemap[NDMAP];	/* Free Space map */
};

struct fs_dev {
	short	fs_device;		/* device index */
	long	fs_size;		/* number pages */
};

struct pseu_ext {
	short	fs_numexts;		/* number of user-defined extents
					   for this pseudo file */
	struct fs_dev fs_ext[EXTPERFI];	/* user-defined extents */
};

struct dbparms {			/* parameters for data base ddl */
	short	fs_dbindex;		/* index in toc */
	char	fs_dbname[MAXFNAME+1];	/* data base name */
	short	fs_nfiles;		/* number of files */
	short	fs_nttbl;		/* number of entries in tran tbl */
	short	fs_nbtbl;		/* number of entries in block tbl */
	short	fs_nltbl;		/* number of entries in lock tbl */
	short	fs_nptbl;		/* number of entries in process tbl */
	short	fs_maxdv;		/* max number of devices */
	short	fs_ndv;			/* number of devices	*/
	short	fs_bfactor;		/* blocking factor for logger */
	long	fs_flags;		/* data base flags */
/* the next element is hard-coded as a long instead of key_t
   since it is part of the user interface and also stored in the database
 */
	long	fs_ipckey;		/* ipc key for this data base */
	long	fs_bps;			/* buffer pool size (pages) */
	long	fs_sln;			/* swap area length (pages) */
	long	fs_cln;			/* commit area length (pages) */
	short	fs_parts;		/* free space partitions/device */
	unsigned short fs_uid;		/* owner uid */
	unsigned short fs_gid;		/* owner gid */
	short	fs_perm;		/* data base permissions */
	struct fs_dev fs_dev[MAXDEV];	/* devices */
	short	fs_ccatype;		/* concurrency control algorithm */
	struct pseu_ext *pseu_ext;	/* start of array of user-defined
					   extents for pseudo files (user
					   must include FSNPSEUFI elements
					   in the array if it is used) */
};

struct fsparms {			/* parameters for file ddl */
	short	fs_fid;			/* file id */
	char	fs_filenm[MAXFNAME+1];	/* file name */
	long	fsize;			/* file size (logical blocks) */
	unsigned short	bksz;		/* block size (bytes) */
	short	ftype;			/* file type: 1 (PINCORE),2 (UINCORE) */
	long	fs_perm;		/* file permissions */
	unsigned short fs_uid;		/* owner uid */
	unsigned short fs_gid;		/* owner gid */
	short	finit;			/* to be initialized: 1  */
	short	fs_maxwtr;		/* max # of trans on a wait queue */
	short	fs_extno;		/* 0 sys alloc extent, otherwise user */
	struct {			/* extents		*/
		short	fs_device;	/* device index	*/
		long	fs_size;	/* number of blocks */
		long	fs_strtno;	/* page on device where file starts */
	} fs_ext[EXTPERFI];
};

struct ipcparms {			/* parameters for ipc - information */
/* the next element is hard-coded as a long instead of key_t
   since it is part of the user interface.
 */
	long	fs_ipckey;		/* key of ipc mechanisms */
	long	fs_smsize;		/* size of shared memory */
/* the next two elements are hard-coded as unsigned short instead of uid_t
   since they is part of the user interface.
 */
	unsigned short fs_uid;		/* uid of owner of db and ipc */
	unsigned short fs_gid;		/* gid of owner of db and ipc */
	int	fs_perm;		/* permissions on db and ipc */
};

/*
	Process parameters 
*/
struct	pidinfo {
/* the next element is hard-coded as a int instead of pid_t
   since it is part of the user interface and also stored in the database
 */
	int 	pid;		/* Unix Process Id */
unsigned short status;		/* Process status (See values above) */
};

/*
	transaction parameters (See flags and status above)
*/
struct trparms {
	TRANID 	trid;		/* transaction id */
	GTRID	gtrid;		/* global transaction id */
/* the next element is hard-coded as a long instead of time_t
   since it is part of the user interface.
 */
	long	sttim;		/* start time of transaction */
	short	dcon;		/* degree of consistency */
	short	status;		/* transaction termination status */
unsigned short	flags;		/* options */
};

/*
 * Database Size Calculation info.
 */
struct fs_dbcalc {
	struct {
		long bpsz;	/* buffer pool */
		long fcbsz;	/* space for FCB's (File Control Blocks) */
		long othersz;	/* space for other shmem structures */
		long totsz;	/* total size of shm */
	} mem;
	struct {
		long casz;	/* commit area */
		long sasz;	/* swap area */
		long fcbsz;	/* file control blocks */
		long othersz;	/* Other Disk over head */
		long totov;	 /* total overhead */
	} disk;
};


/*
 *	FS error return codes (thru fserror)
 */

#define	FSEMINVAL	0	/* bottom of errors */
#define	FSEOPRTN	1	/* bad operation */
#define FSEFILE		2	/* illegal file--file not found or dup name */
#define	FSENOSPACE	3	/* no space can be allocated for file	*/
#define	FSETROV		4	/* transaction table overflow */
#define	FSELOCKED	5	/* conflict: can't get lock */
#define	FSENOLOCKS	6	/* lock table overflow	*/
#define	FSENOBLOCKS	7	/* block table overflow	*/
#define	FSECORPT	8	/* corrupted database or different FS release */
#define FSENOFCB	9	/* no space for another file control block */
#define FSEMODE		10	/* invalid mode, lock type or file not opened */
#define FSEOFFS		11	/* offset out of range */
#define FSENOEXTS	12	/* extent table exceeded (per file table) */
#define FSEFSNAME	13	/* illegal database name--not found or dup */
#define FSENINI		14	/* database not opened */
#define FSEUNIX		15	/* UNIX sys call error return */
#define FSETRAN		16	/* invalid transaction identifier */
#define FSECHNGD	17	/* ddl applied to file by another tran */
#define FSELKTP		18	/* internal error --
				   bad lock type passed to 'fsbread' */
#define FSEFSNM		19	/* invalid FS name */
#define FSEBADEV	20	/* bad device type */
#define FSECMTSIZ	21	/* commit area size too small */
#define FSEBLKSZ	22	/* illegal block size specified for file */
#define	FSENOBUF	23	/* no space in the buffer pool */
#define FSEUPDC		24	/* max no of updates/transaction exceeded */
#define FSEMFREE	25	/* mfree failed */
#define FSEINIT		26	/* database already opened by this process */
#define FSENXLK		27	/* internal error --
				   fsbwrit called w/out LEXCLU lock owned */
#define FSEDGRE		28	/* invalid degree of cons. when starting TA */
#define FSEINTL		29	/* PANIC: internal inconsistency */
#define FSESWAP		30	/* swap area exceeded */
#define FSETRSTAT	31	/* TA is not active; should abort */
#define FSEXN		32	/* dblock while other process attached */
#define FSEXS		33	/* fs locked by another process */
#define FSENBR		34	/* internal error --
				   fsbrel or fsbwrit w/o prior fsbread */
#define FSERDON		35	/* update attempted in read-only mode */
#define FSEFLLC		36 	/* file locked by other trans */
#define FSELMD		37	/* file locked for share and write tried */
#define FSEMAXDEV	38	/* invalid max number of devices */
#define FSEDEVICE	39	/* can't find device in dlist */
#define FSENOTOC	40	/* no space for another database */
#define FSENDEVICES	41	/* invalid number of devices */
#define FSEDIRINIT	42	/* FS device list not initialized */
#define FSENOTEMP	43	/* device or table not empty */
#define FSECONFIG	44	/* FSCONFIG not or incorrectly set */
#define FSEOVERLAP	45	/* overlapping devices */
#define FSEIPCKEY	46	/* bad ipc key */
#define FSEFSP		47	/* not enough free space partitions */
#define FSEOPEN		48	/* fs file already open */
#define FSEPERM		49	/* no permission */
#define FSEUNBLK	50	/* internal error -- illegal block unlock */
#define FSEIOP		51	/* illegal operation */
#define FSESEMLK	52	/* semaphore for internal tables locked */
#define FSEWAITING	53	/* transaction is waiting for a lock */
#define FSEHICONS	54	/* primitive should be used in HICONS mode */
#define FSEMAXWAIT	55	/* max limit of tran on wait queue exceded */
#define FSETEO		56	/* no space for another restartable tran */
#define FSEINVOPT	57	/* invalid option */
#define FSEINVRP	58	/* invalid restart point */
#define FSETRWAIT	59	/* transactions waiting for lock on a block */
#define FSESTCOMMIT	60	/* transaction started commit; can't abort */
#define FSENOPTE	61	/* no space for another process or invalid PID*/
#define FSEPSTR		62	/* one or more tran proc already started  */
#define FSEWPID		63	/* tran is not associated with this process */
#define FSETRCOM	64	/* a trans is already being committed by proc */
#define FSEEXIPCK	65	/* IPCKEY is already used */
#define FSENIREAD	66	/* read failed on UNIX file which was not
				   initialized */
#define FSENOREL	67	/* internal error --
				   commit w/o fsbrel() or fsbwrit() */
#define FSEBADOFST	68	/* Device 0 offset != FSOFFSET */
#define FSECLOSLK	69	/* can't close locked files */
#define FSEDBREADY	70	/* Cold/Warm Start when DB already started. */
#define FSEDBSTART	71	/* DB Cold/Warm Start is in progress. */
#define FSEWSTART	72	/* Automatic Warm start failure. */
#define FSELSTART	73	/* Warm Start needs the logger. */
#define FSEPARTIPC	74	/* Partial IPC resources exist. */
#define FSELOGNOTOK	75	/* logging transactions not allowed */
#define FSELOGFAIL	76	/* attempt to log transaction failed */
#define FSEBATCH	77	/* Incorrect FSBATCH usage. */
#define FSEBADSHMEM	78	/* Bad shared memory, doesn't match expected. */
#define FSERESTART	79	/* internal error --
				   CLWAIT transaction restarted	*/
#define FSEIDBOP	80	/* internal database open failed after
				   successful db change  */
#define FSEMAXVAL	81	/* highest error number + 1	*/

#define	FSSUCCESS	0	/* successful FS operation	*/

#define FSEDEADLCK	FSETRSTAT /* Included only for compatability */

/* flags to ntrdeleg() */
#define TRDEL_SUSPEND 01
#define TRDEL_NOSTEAL 02

/* EXTERNAL DEFINITIONS */
_TMIFS extern char	FSdbname[];	/* open db name */
_TMIFS extern short	FSfsmode;	/* open mode of database */

#ifdef _TMPROTOTYPES
#include <stdio.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif

extern int fscrdl _((struct dlparms *));
extern int fsfreedbdl _((struct dbdlparms *));
extern int fslidbdl _((struct dbdlparms *));
extern int fslidl _((struct dlparms *));
extern int fsindl _((short));
extern int fschdl _((struct dlparms *));
extern int fsdsdl _((short));
extern int fslitc _((short, char *));
extern int fscrdb _((struct dbparms *));
extern int fsindb _((void));
extern int fschdb _((struct dbparms *));
extern int fslidb _((struct dbparms *));
extern int fsmodb _((struct dbparms *));
extern int fsrmdb _((char *));
extern int fsdsdb _((void));
extern int dbclose _((void));
extern int dbclstat _((void));
extern int dblock _((int));
extern int dbopen _((char *, short));
extern int dbprstat _((FILE *, short));
extern int dbunlock _((void));
extern int fsdbcalc _((struct dbparms *, struct fs_dbcalc *));
extern int fsfindpid _((unsigned short));
extern int fspidinfo _((struct pidinfo *));
extern int fsrmpid _((int));
extern int *_fsget_fserror_addr _((void));

#if defined(__cplusplus)
}
#endif

#define fserror (*_fsget_fserror_addr())

#endif
