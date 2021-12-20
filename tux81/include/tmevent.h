/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1995 Novell
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF NOVELL
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.

#ident	"@(#) tuxedo/include/tmevent.h	$Revision: 1.3 $"
*/
/*
	Warning: This file should not be changed in any
	way, doing so will destroy the compatibility with TUXEDO programs
	and libraries.
*/
#ifndef _TMEVENT_H
#define _TMEVENT_H
#ifndef NOWHAT
static	char	h_tmevent[] = "@(#) tuxedo/include/tmevent.h	$Revision: 1.3 $";
#endif

#include <stdio.h>
#include <atmi.h>
#include <tmbase.h>
#include <fml32.h>
#include <tmmsg.h>


/* Subscription version numbers */
#define	EB_SUBS_VERSION_1	1
#define	EB_SUBS_VERSION_2	2
#define	EB_SUBS_CURR_VERSION	2


/* Structures for allocating sequence numbers */
typedef struct ebhblk_t EBHBLK;
struct ebhblk_t {
	EBHBLK *next_hblk;
	EBHBLK *prev_hblk;
	long min;
	long max;
};

typedef struct ebhctl_t EBHCTL;
struct ebhctl_t {
	EBHBLK *found_hblk;  /* most recently found HBLK */
	EBHBLK *last_hblk;  /* last HBLK allocated from */
	EBHBLK *hdr_hblk;  /* point to HBLK which is root of circular chain */
	long in_use_count;
	long next_hndl;  /* next handle number to allocate */
};


/* Kinds of subscriptions */
#define ALPHANUMERIC	1
#define WILDCARD	2
#define PREALLOCATED	3

/* Kind of filter associated with a subscription */
#define EB_NOFILTER		0
#define EB_EVENT_FILTER 	1
#define EB_EVENT_FILTER_BINARY	2

/* Error -  eb_info->eb_error */
#define EB_FOPEN_ERROR		1
#define EB_FPRINT_ERROR		2

/* Maximum lengths of various fields */
#define EB_TA_EVENTNAME_MAXLEN			31
#define EB_TA_COMMAND_MAXLEN			255
#define EB_TA_USERLOG_MAXLEN			255
#define EB_TA_EVENT_EXPR_MAXLEN			255
#define EB_TA_EVENT_FILTER_MAXLEN		255
#define EB_TA_EVENT_FILTER_BINARY_MAXLEN	64000
#define EB_TA_QSPACE_MAXLEN			15
#define EB_TA_QNAME_MAXLEN			15
#define EB_TA_CLIENTID_MAXLEN			78

/* Notification mechanisms -> EB_ACTION->class */
#define T_EVENT_USERLOG		1
#define T_EVENT_COMMAND		2
#define T_EVENT_SERVICE		3
#define T_EVENT_QUEUE		4
#define T_EVENT_CLIENT		5
#define T_EVENT_SYSLOGD		6
#define T_EVENT_PREALLOCATED	7

/*
 * For checking the sanity of message queues.
 * eb_info->msg_state
 */
#define	EB_MSGQ_CHECK_COUNTER		10

/* Value set in the composite buffer */
#define TPPOST				1
#define TP_EB_GET_SUB_DB		2

/* Flags for service notification */
#define EB_PERSIST	0x01
#define EB_EVENT_TRAN	0x02
#define EB_SET_HANDLE	0x04
#define EB_SET_BLOB	0x08
#define EB_UNIQUE	0x10

/* Type of Broker - eb_info->broker_type */
#define SYSTEM_EVENT_BROKER	0x00000001
#define USER_EVENT_BROKER	0x00000002	

#define SYSBRKR_SEQNUM_START	1
#define USRBRKR_SEQNUM_START	1000000000

#define FLD_NOT_PRESENT	(-1)
#define FLD_INVALID_LEN (-2)
#define NOMEM		(-3)

#define	DYNAMIC_MEM	1
#define	STATIC_MEM	2

#define	EB_CLIENT	0x001
#define	EB_WSC		0x010
#define	EB_SERVER	0x100

/*
 * Event expression. Is a regular-expression.
 */
 typedef struct eb_event_expression {
   char *event_expr;			/* Null-terminated event expression */
   char *compiled_event_expr;		/* Compiled event expression */
 } EVENT_EXPRESSION;

/*
 * Filter for an event. Is a regular-expression.
 */
 typedef struct eb_event_filter {
   int filter_chosen;			/* EB_EVENT_FILTER or EB_BINARY_FILTER */
   union {
     struct {
       char *event_filter;		/* Null-terminated event filter */
       int length_of_ascii_filter;	/* Length of ascii filter */
     } ascii_filter;
     struct {
       char *binary_filter;		/* binary filter */
       unsigned long length_of_binary_filter;	/* Length of binary filter */
     } binary_filter;
   } ev_filter;
 } EVENT_FLTR;

/*
 * Action to be taken when an event occurs.
 */
 typedef struct eb_action {
   CLIENTID proc_clientid;		/* Always populated with the CLIENTID of the subscriber */
   TM32I rflags;			/* Subscriber's registry entry type - WSC, CLIENT, or SERVER */
   int clss;				/* action-dependent */
   long version;
   int bloblen;
   void *blobvalue;
   char *blobtype;
   union {
     struct {
       CLIENTID cltid; 
     } clt_info;			/* Client info for notification */
     struct { 
       char *servicename;		/* svc to be invoked */
       long flags;			/* TPEVTRAN and/or TPEVPERSIST */
     } svc_info;			/* Info for the svc to be dispatched */
     struct {
       char *qspace;			/* Name of qspace */
       char *qname;			/* qname within the qspace */
       TPQCTL qctl;			/* control structure for tpenqueue */
       long flags;			/* TPEVTRAN and/or TPEVPERSIST */
      } queue_info;			/* Info for the queuing operation */
      struct {
        char *userlog;			/* string that will be logged */
      } userlog_info;			/* String that needs to be logged */
      struct {
        char *cmd;			/* string that will be system()'ed */
      } cmd_info;			/* String that will be an arg to system(3) */
   } action_desc;
 } EB_ACTION;

/*
 * Subscription event info.
 */
 typedef struct eb_event {
   EVENT_EXPRESSION *event_expr;
   EVENT_FLTR *event_filter;
   short expr_type;
 } EB_EVENT;

/*
 * Header of all entries in hash tables.
 */
 typedef struct elem_hdr {
   char *next_elem;
   char *prev_elem;
   char *hash_hdr;
 } ELEM_HDR;

/*
 * Subscription handle info.
 */
 typedef struct eb_subscription *EB_SUBSCRIPTION_PTR;
 typedef struct eb_sub_hndl *EB_SUB_HNDL_PTR;
 typedef struct eb_sub_hndl {
   ELEM_HDR hdr;
   long seqno;				/* tpsubscribe() returns this value */	
   EB_SUBSCRIPTION_PTR sub_ptr;	/* Pointer to subscription entry */
} EB_SUB_HNDL;

/*
 * Info of the process that subscribed to an event 
 */
 typedef struct eb_proc_hndl {
   ELEM_HDR hdr;
   EB_SUBSCRIPTION_PTR sub_ptr;	/* Pointer to subscription entry */
} EB_PROC_HNDL;


/*
 * Subscribed event and action info.
 */
#define EB_SUBSCRIPTION_ACTIVE		0
#define EB_SUBSCRIPTION_SUSPENDED	1
 typedef struct eb_subscription {
   ELEM_HDR hdr;
   long state;				/* EB_SUBSCRIPTION_ACTIVE, EB_SUBSCRIPTION_SUSPENDED */
   long seqno;				/* tpsubscribe() returns this value */	
   short garbage_collected;		/* 1 if garbage collected */
   long wildcardsub_idx;
   TMPROC subscriber_proc;		/* Identity of the subscriber */
   EB_EVENT *event;			
   EB_ACTION *action;			/* action to be taken */
   EB_SUB_HNDL_PTR sub_hndl_ptr;	/* pointer to subscription handle */
   EB_PROC_HNDL	*proc_ptr;		/* pointer to proc entry */
} EB_SUBSCRIPTION;


/* Start of hash table info */
#define EB_NUM_OF_HASH_BKTS	101

/*
 * Subscriptions that do not have any wildcard characters are accessed
 * through a hash table. Hashing is done on event expression.
 * Within in a hash chain, entries are sorted by event expression such that
 * lookup will be faster.
 */
 typedef struct eb_hash_hdr {
   int tot_num_of_bkts;			/* Total # of buckets in the hash table */
   int curr_num_of_elems;		/* Current # of elements in the hash table */
  int chain_last_cleaned;		/* Last chain that was garbage collected */
#if defined(_TMALIGNPTR) && (_TMALIGNPTR == 8 || _TMALIGNPTR == 16)
  /*
   * because the eb_hash_hdr is followed by the eb_chain_hdr table, and
   * eb_chain_hdr contains pointers that need to be properly aligned
   * (e.g. 8-byte alignment on DEC ALPHA and 16-byte alignment on AS400),
   * the eb_hash_hdr struct must be padded accordingly.
   */
  int dummy;	
#endif
 } EB_HASH_HDR;


/*
 * Header of an individual chain. Points to the first element and has count of
 * elements in this chain.
 */
 typedef struct eb_chain_hdr {
   ELEM_HDR hdr;
   int num_of_elems_in_chain;
#ifdef _TMLONG64
   int dummy;
#endif
} EB_HASH_CHAIN_HDR;


/* End of hash table info */


#define EB_ACTION_NUM_INIT	20
#define EB_ACTION_NUM_INCR	10

/*
 * List of actions to be taken for the current event.
 */
 typedef struct eb_actions {
   long max_num_of_actions;
   long curr_num_of_actions;
   EB_SUBSCRIPTION **subs;
 } EB_ACTIONS;


 typedef struct eb_current_actions {
   EB_ACTIONS *tx_acts;
   EB_ACTIONS *nontx_acts;
 } EB_CURRENT_ACTIONS;


 typedef struct tpcall_handles {
   int curr_num_of_outstanding_handles;
   int handles[TM_MAXHANDLES];
 } TPCALL_HANDLES;

   
/*
 * Header for wild-card subscriptions.
 */
 typedef struct eb_wildcard_subs {
   long max_num_of_subs;
   long curr_num_of_subs;
   EB_SUBSCRIPTION **subs;
 } EB_WILDCARD_SUBS; 


typedef struct eb_info_t {
  int broker_type;
  long eb_error;		/* Error */
  long curr_seqno;
  long primary;
  long poll_interval;		/* Poll the primary periodically at this interval (in secs) */
  int trantime;			/* timeout for tx begun by EB */
  long boot_time;		/* In secs from Epoch */
  long last_polled;		/* Time last polled in secs */
  long num_of_times_polled_primary;	
  long num_of_times_received_full_data;
  long num_of_postings;		/* No. of postings processed */
  long num_of_subscriptions;
  long num_of_unsubscriptions;
  short init_done;		/* Set to 1 just before returning from tpsvrinit() */
  char *control_file;
  FBFR32 *fbfr32;
  FLDLEN32 fbfr32_sz;
  FILE *good_rec_file_ptr;	/* Write all good records in this file */
  FILE *bad_rec_file_ptr;	/* Write all bad records in this file */
  char unload_file[256];
  int unload_file_sz_v1;		/* Size of v1 part of subscription database file */
  int unload_file_sz_v2;		/* Size of v1 & v2 parts of subscription database file */
  char *subscription_database;	/* in-memory copy of subscription DB */
  int subscription_database_max_ptr_sz;
  long seqno_when_db_unloaded;
  long primary_seqno;
  int got_signal;		/* Did we get a signal while waiting on the queue */
  EB_WILDCARD_SUBS *wildcard_subs;
  EB_HASH_HDR *alphanum_hash_hdr;
  EB_HASH_HDR *sub_hand_hash_hdr;
  EB_HASH_HDR *proc_hash_hdr;
  EB_CURRENT_ACTIONS *curr_actions;
  EB_ACTIONS *delete_subs;	/* List of subscriptions that need to be deleted */
  long num_deleted;		/* No. of subscriptions deleted in one operation */
  long num_of_nontx_notifications;	/* No. of non-transactional notifications processes in one tppost() */
  long num_of_tx_notifications;		/* No. of transactional notifications processes in one tppost() */
  TMPROC curr_proc;		/* Info of the process that sent the the current rqst */
  CLIENTID curr_cltid;
  int _tperrno;		/* for passing the errno to the requester */
  char *replybuf;
  TPCALL_HANDLES tpcall_handles;
  int tran_allowed;		/* Can this EB begin tx's */

  char *msg_data;
  int chk_msgq_counter;	/* When the count reaches EB_MSGQ_CHECK_COUNTER,
			 * we either send a message or expect a reply.
			 */
  int chk_msgq;
  int database_changes;
  TM32I rflags;		/* accessers' type */
  EBHCTL *hblk_ctl;
} EB_INFO_T;

#define EB_T_RESOURCE		1
#define EB_T_MACHINE		2
#define EB_T_NETWORK		3
#define EB_T_SERVER		4
#define EB_T_CLIENT		5
#define EB_T_TRANSACTION	6
#define EB_T_EVENT		7
#define EB_T_GROUP		8
/*
 * Key fields for retrieving object attributes
 * before dispatching the buffer to Event Broker.
 */
typedef struct eb_key_fields {
  int clss;
  struct {
    long flags;
  } resource;
  struct {
    char lmid[MAXTIDENT+1];
  } machine; 
  struct {
    char lmid0[MAXTIDENT+1];
    char lmid1[MAXTIDENT+1];
  } network; 
  struct {
    char srvname[MAXTSTRING+1];
    char srvgrp[MAXTIDENT+1];
    long srvid;
  } server;
  struct {
    char cltid[MAXTSTRING+1];
    char usrname[MAXTIDENT+1];
    char lmid[MAXTIDENT+1];
  } client;
  struct {
    char gtrid[MAXTSTRING+1];
    long grpno;
  } tran;
  struct {
    char lmid[MAXTIDENT+1];
  } event; 
  struct {
    char grpname[MAXTIDENT+1];
    char lmid[2*MAXTIDENT+2];
  } group; 
} EB_KEY_FIELDS;


#define EVENT_EXPR(A)		((A)->event->event_expr->event_expr)
#define COMPILED_EVENT_EXPR(A)	((A)->event->event_expr->compiled_event_expr)
#define FILTER_CHOSEN(A)	((A)->event->event_filter->filter_chosen) 
#define EVENT_FILTER(A)		((A)->event->event_filter->ev_filter.ascii_filter.event_filter) 
#define EVENT_FILTER_LEN(A)	((A)->event->event_filter->ev_filter.ascii_filter.length_of_ascii_filter) 
#define EVENT_FILTER_BINARY(A)	((A)->event->event_filter->ev_filter.binary_filter.binary_filter) 
#define EVENT_FILTER_BINARY_LEN(A)	((A)->event->event_filter->ev_filter.binary_filter.length_of_binary_filter) 
#define EVENT_BLOB_TYPE(A)	((A)->action->blobtype)
#define EVENT_BLOB_VALUE(A)	((A)->action->blobvalue)
#define EVENT_BLOB_LEN(A)	((A)->action->bloblen)
#define EVENT_CMD(A)		((A)->action->action_desc.cmd_info.cmd)
#define EVENT_USERLOG(A)	((A)->action->action_desc.userlog_info.userlog)
#define EVENT_SERVICE(A)	((A)->action->action_desc.svc_info.servicename)
#define EVENT_CLTID(A)		((A)->action->action_desc.clt_info.cltid)
#define EVENT_TRAN(A)		\
	(((A)->action->clss==T_EVENT_SERVICE &&\
	  ((A)->action->action_desc.svc_info.flags & EB_EVENT_TRAN)) ||\
	 ((A)->action->clss==T_EVENT_QUEUE &&\
	  ((A)->action->action_desc.queue_info.flags & EB_EVENT_TRAN)))
#define EVENT_QSPACE(A)		((A)->action->action_desc.queue_info.qspace)
#define EVENT_QNAME(A)		((A)->action->action_desc.queue_info.qname)
#define EVENT_CORRID(A)		((A)->action->action_desc.queue_info.qctl.corrid)
#define EVENT_REPLYQUEUE(A)	((A)->action->action_desc.queue_info.qctl.replyqueue)
#define EVENT_QCTL(A)		((A)->action->action_desc.queue_info.qctl)

#define EB_FREE(A)		if (A) \
					free((A))
#define EB_SET_TPERRNO(A)	(eb_info->_tperrno = (A))
#define EB_TOTAL_NOTIFICATIONS	(eb_info->num_of_nontx_notifications+eb_info->num_of_tx_notifications)

#endif
