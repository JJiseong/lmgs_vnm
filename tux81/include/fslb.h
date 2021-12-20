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

#ifndef FSLBH
#define FSLBH 1

/* #ident	"@(#) dux/libfs/fslb.h	$Revision: 1.3 $" */
#ifndef TMENV_H
#include <tmenv.h>
#endif
#ifndef NOWHAT
static	char	h_fslb[] = "@(#) dux/libfs/fslb.h	$Revision: 1.3 $";
#endif

/*
 *	FS DEFINITIONS NEEDED BY USER APPLICATION PROGRAMS.
 *
 *
 *	Warning: This TUXEDO header file should not be changed in any
 *	way.  Doing so will destroy the compatibility with TUXEDO programs
 *	and libraries.
 */

/*
 *	FS LOGGER AND BACKUP DEFINTIONS
 *
 */

#define FSNLBD 20	/* maximum number of log/bkup devices */

/* flags passed to logging/bkup functions */
#define	NOCHECK	01	/* don't check header on log/bkup device - overwrite
			   (default is to check so no device is overwritten) */
#define CYCLE	02	/* when last device/file filled, begin with first one
			   (default is to stop when last device filled) */
#define DUMPONLY 04	/* only recover from records within online bkup
			   (default is to recover from entire log) */
#define DEVWAIT	010	/* wait for user response when reading log/bkup
			   devices (default is to continue reading as
			   long as devices are available without interruption)*/
#define NONSTOP 020	/* always continue whenever possible (some errors
			   will still require intervention) */
#define DONTLOG	040	/* don't force logging of all transactions during
			   dump (default is to log all updates) */
#define NOREOPEN 0100	/* don't reopen log/bkup devices - always use
			   specified blocking factor */
#define DBGEN 0200	/* generate device list/database */
#define KILLOG 0400	/* kill logging process when finished */
#define LOGOBLIG	01000  /* obligatory logging is in force */  
#define SYNCLOGOBLIG	02000 /* synchronous obligatory logging is in force */
#define NEWDEV 04000	/* go to new log device when done with backup --
			 * mutually exclusive with KILLOG
			 */
#define CHECKSUM	020000  /* Perform checksumming on log records. */
#define RESUMEOP	0100000000	/* Resume logging or backup */

/* Following flags to indicate FS Area to be backed up */

#define FA_DEVLIST	  0100000	/* device list */
#define FA_SYS		 03400000	/* superblock, free space blocks,
					 * and user file control blocks */
#define FA_FCB		 04000000	/* user file control blocks */
#define FA_FILE		010000000	/* fs file */
#define FA_IFILE	020000000	/* bkup individual files */
#define FA_ALL		017500000	/* all of fs directory and database */
#define FA_DATABASE	017400000	/* all of database */


/* returns from information/warning/error handling function */
#define CONTINUE 1	/* continue normal processing - valid for
			   information and warning messages only */
#define NEXT	2	/* continue processing with next log device/file */
#define EXIT	3	/* cleanup and exit logger */


/* fatal errors */
#define	ACOMPL	101	/* abnormal completion */
#define	BADTRID	102	/* can't find transaction */
#define	BADUPDATE	103	/* can't update for page */
#define	COMREAD	104	/* read failed on commit area */
#define	COMWRT	105	/* write to commit area failed */
#define	DBINIT	106	/* database not initialized */
#define	DBPRIVATE	107	/* database opened in private mode */
#define	DBREAD	108	/* read failed on database */
#define	DBSEEK	109	/* seek failed on database */
#define	DEVOPEN	110	/* cannot open device list */
#define	EOLOG	111	/* eolog reached - transaction in progress */
#define	ETRST1	112	/* starting transaction with RECOV failed */
#define	IUSAGE	116	/* illegal command usage */
#define	LBDRD1	118	/* read failed on log/bkup device */
#define	LBDWRT1	119	/* write failed on log/bkup device */
#define	LOGSTART	120	/* can't start logger */
#undef MALLOC
#define	MALLOC	121	/* can't malloc buffer */
#define	NOLBD	122	/* no log/bkup devices specified */
#undef NOSPACE		/* known in some UNIX systems (MDSS) */
#define	NOSPACE	123	/* no more log/bkup devices */
#define	REALLOC	124	/* can't realloc buffer */
#define	SSEMLOCK	125	/* can't lock system semaphore */
#define	SSEMUNLK	126	/* unlock of system semaphore failed */
#define	USAGE	127	/* command usage */
#define	USEMLOCK	128	/* can't lock user-level semaphore */
#define	USEMUNLK	129	/* unlock of user-level semaphore failed */
#define DBWRT	130	/* write failed on database */
#define DBOPEN1	131	/* open failed on database */
#define DLCREAT	132	/* device list creation failed */
#define DBCREAT 133	/* database creation failed */
#define FICREAT 134	/* file creation failed */
#define ETRSTART 135	/* trstart failed */
#define LOGRUNNING 136	/* logger not running prior to warm start */
#define EMSGSND	137	/* msgsnd() error */
#define EMSGRCV 138	/* msgrcv() error */
#define	COMREL	139	/* release of commit area failed */
#define	BADMSG	140	/* bad message received */
#define LOGFAIL 141	/* attempt to log this transaction has failed */
#define LOGRUNNOW 142	/* another logger is already running */
#define EIPCRM	143	/* cannot remove ipc resources for database */
#define BADTIMES 144	/* log record timestamp out of sequence. */
#define EARGLIST 145	/* argument list too long */
#define ECHECKPT 146	/* cannot read or write checkpointing information */	
#define ECKPDDL  149	/* DDL between failure and checkpoint resumption */
#define EDLCKPI	 150	/* load checkpoint info present when dump checkpoint
			 * info expected or vice versa
			 */
#define BADLOAD 151	/* bad backup dump on the last volume. */
#define BADLOG	152	/* bad log file on the last volume. */

/* numbers 200 - 299 are warning messages - not fatal but wait for response */
#define	BADCHK	201	/* bad checksum on log record */
#define	BADOP	202	/* bad log opcode */
#define	BLKREAD	203	/* read failed on block to be updated */
#define	DBLOCK	204	/* can't lock database in exclusive mode */
#define	DBOPEN2	205	/* dbopen failed */
#define	DUPLOG	206	/* duplicate log sequence number */
#define	DUPTRAN	207	/* found LOGCMIT record for existing transaction */
#define	ETRABORT	208	/* transaction abort failed */
#define	ETRCOMMIT	209	/* transaction commit failed */
#define	ETRST2	210	/* starting transaction with RECOV failed */
#define	LBDBKSZ	214	/* invalid change in block size */
#define	LBDCPL1	215	/* end of volume on single log/bkup device - wait
			   for volume to be ready again for reuse */
#define	LBDHDR1	216	/* header exists on log device/file */
#define	LBDMG1	217	/* bad header on log/bkup device */
#define	LBDMG2	218	/* bad header on log/bkup record */
#define	LBDOPEN	219	/* can't open log/bkup device */
#define	LBDRD2	220	/* read on log/bkup device failed */
#define	LBDSTR1	221	/* start of volume on log/bkup device */
#define	LBDWRT2	222	/* write failed log/bkup device */
#define	LBENTRY	223	/* can't create log/bkup entry on process table */
#define	LOGLEN	224	/* invalid log record length */
#define	LOGSEQ	225	/* log record out of sequence */
#define	NOLOGENTRY	226	/* no logger running */
#define EFILENM	227	/* bad filename specified for dumping */
#define	LBDHDR2	228	/* no header on log/bkup device */
#define	LKILL	229	/* kill to logger process failed */
#define	BADTRAIL 230	/* bad trailer on log record */
#define	LBDWRT3	231	/* write failed on log/bkup device */
#define	LBDRD3	232	/* read failed on log/bkup device */

/* numbers 300 - 499 are information numbers - don't await reply */
#define	COMPL	301	/* completed operation */
#define LBDCPL2	303	/* end of volume on log/bkup device */
#define LBDSTR2	304	/* start of volume on log/bkup device */
#define OSTART	305	/* operation starting */
#define SBKUPR	306	/* start recovery of backup transactions */
#define EBKUPR	307	/* start recovery of backup transactions */
#define BACKUP	308	/* section backed up */
#define GEN	309	/* section generated */
#define ENLBD	310	/* too many log/backup devices specified */



#if defined(__cplusplus)
extern "C" {
#endif

extern	int	fsbkupd _((char *, int, char **, int, int, int, char **));
extern	int	fsbkupl _((char *,int,char **, int, int, char *, int, char **));
extern	int	fslog _((char *, int, char **, int, int));
extern	int	fslogc _((char *, int, char **, int, int));
extern	int	fslogo _((char *, char *, char *, char *, int, int));
extern	int	fslogr _((char *, int, char **, int, int));
extern	int	fslogw _((char *, int, char **, int, int));

#if defined(__cplusplus)
}
#endif

#endif
