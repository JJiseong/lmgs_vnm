/*	(c) 2002 BEA Systems, Inc. All Rights Reserved.

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.

	Copyright (c) 1994 Novell Inc.
*/

/* #ident	"@(#) trpc/dceserver.c	$Revision: 1.5 $" */

/* DEFINITIONS FOR APPLICATION MANAGER */

/* Define the name of the server in the directory */
#define SERVER_NAME		"/.:/<INTERFACE>_<HOST>"

/* If you want to export the name to a group, define the group */
/* #define GROUP_NAME_TUX	"/.:/<INTERFACE>_group"  */

/* Annotation for the server - optional */
#define SERVER_ANNOTATION	"<ANNOTATION>"

/*
 * Athentication information:
 *  If you want to be able to run the server as a daemon without doing
 *  a dce_login, you need to define the principal and the key table
 *  which is created via the following command:
rgy_edit<<!
ktadd -p SERVER_PRINCIPAL -pw PASSWORD -f SERVER_KEYTAB
!
 */
/*
 * define the following for Windows NT only if DCE on NT supports
 * the DCE security API
 */                 
#ifndef WIN32
#define SERVER_KEYTAB		"/<DIRECTORY>/.<INTERFACE>_tab"
#define SERVER_PRINCIPAL_NAME	"<PRINCIPAL>"
#endif

/* interface specification */
#define INTERFACE_SPEC		<INTERFACE>_v<MAJOR>_<MINOR>_s_ifspec

/* entry point vector */
#define INTERFACE_EPV		NULL

/* interface header */
#define INTERFACE_HDR		"<INTERFACE>.h"

/* END DEFINITIONS FOR APPLICATION MANAGER */

#include <stdio.h>
#include <stdlib.h>
#if defined(TPSVRINIT) || defined(TCLIENT)
#include <atmi.h>		/* TUXEDO function prototypes */
#include <userlog.h>		/* TUXEDO function prototypes */
#endif
#include <tx.h>
#include <dce/dce_error.h>	/* required to call dce_error_inq_text */
#include <pthread.h>		/* threads to refresh login context and
				 * manage secret key.  */
#include <dce/rpcexc.h>    	/* needed if app uses exception handlers */

#include <dce/idlbase.h>	/* base data types */
#include <dce/rpc.h>		/* rpc_ data types and function prototypes */
#ifdef WIN32
#include <dce/keymgmt.h>
#endif                 
#if !defined(TPSVRINIT)
#include INTERFACE_HDR		/* header created by the IDL compiler */
#endif


/* status checking macro */
#define RESUME 0
#define ABORT  1

#define CHECK_STATUS(input_status, comment, action) \
{ \
	if(input_status != rpc_s_ok) { \
		dce_error_inq_text(input_status, error_string, &error_stat); \
		fprintf(stderr, "%s %s\n", comment, error_string); \
		if(action == ABORT) \
			exit(1); \
	} \
}
static int            error_stat;		/* status of last failure */
static unsigned char  error_string[dce_c_error_string_len]; /* failure string */
/* end status checking */

#if defined(__alpha)
#define bigger_stack
#endif

void establish_identity(unsigned32 *status);

#ifdef TCLIENT
int doinit(void);
#endif

int
#if defined(TPSVRINIT)
tpsvrinit(int argc, char *argv[])
#else
main(int argc, char *argv[])
#endif
{
	unsigned32 status;			/* error status */

#if !defined(TPSVRINIT)
	unsigned_char_t *server_name;		/* name service entry name */
	rpc_binding_vector_t *bind_vector_p;	/* binding handle list */

	/* Register interface with the RPC Runtime. */
	rpc_server_register_if(			/* register interface */
		INTERFACE_SPEC,			/* interface specification */
		NULL,				/* manager type */
		INTERFACE_EPV,			/* entry point vector or NULL */
		&status);
	CHECK_STATUS(status, "unable to register interface", ABORT);

	/* Use all supported protocol sequences. */
	rpc_server_use_all_protseqs(
		rpc_c_protseq_max_reqs_default,	/* all supported protocols */
		&status);
	CHECK_STATUS(status, "use_all_protseqs failed", ABORT);
#endif	/* !TPSVRINIT */

#if defined(SERVER_KEYTAB) && defined(SERVER_PRINCIPAL_NAME)
	/*
	 * Establish this server's identity by setting up the
	 * appropriate login context.
	 */
	establish_identity(&status);
	CHECK_STATUS(status, "Cannot establish server identity", ABORT);

	/*
	 * Register authentication info with RPC.
	 */
	rpc_server_register_auth_info(
		(unsigned_char_t *)SERVER_PRINCIPAL_NAME, /* principal name */
		rpc_c_authn_dce_secret,	/* DCE shared-secret key authen. */
		NULL,			/* default key retrieval function */
		SERVER_KEYTAB,		/* server keytab file */
		&status);
	CHECK_STATUS(status, "server_register_auth_info failed", ABORT);
#endif

#if !defined(TPSVRINIT)
	/*
	 * Continue with the normal initialization sequence.
	 * Get the bindings.
	 */
	rpc_server_inq_bindings(	/* get all binding info for server */
		&bind_vector_p,		/* list of binding info */
		&status);
	CHECK_STATUS(status, "server_inq_bindings failed", ABORT);

	/* Register binding information with the endpoint map. */
	rpc_ep_register(		/* add endpoints to the local ep map */
		INTERFACE_SPEC,		/* interface specification */
		bind_vector_p, 		/* list of binding info */
		NULL, 			/* object UUIDs to register */
		(unsigned_char_t *)SERVER_ANNOTATION,	/* annotation */
		&status);
	CHECK_STATUS(status, "ep_register failed", ABORT);

	/*
	 * Export binding information into the namespace.
	 */
	rpc_ns_binding_export(		/* export to name service database */
		rpc_c_ns_syntax_default,/* syntax of entry name */
		(unsigned_char_t *)SERVER_NAME,	/* entry in name service */
		INTERFACE_SPEC,		/* interface specification */
		bind_vector_p, 		/* list of binding information */
		NULL,			/* object UUIDs exported */
		&status);
	CHECK_STATUS(status, "binding export failed", ABORT);


#ifdef GROUP_NAME_TUX
	/*
	 * Depending on the application, it may be desirable to
	 * add the service to a group that is location in-dependent
	 * (e.g., the name doesn't have the host name appended).
	 */
	rpc_ns_group_mbr_add(		/* add as member of ns group */
		rpc_c_ns_syntax_default,/* syntax of group name */
		GROUP_NAME_TUX,		/* name of group in name service */
		rpc_c_ns_syntax_default,/* syntax of member name */
		SERVER_NAME, 		/* name of member in name service */
		&status);
	CHECK_STATUS(status, "Can't add member to name service group", RESUME);
#endif

	TRY			/* exception handling */

#ifdef TCLIENT
	if (doinit() != -1) {
		/* Listen for remote calls. */
		fprintf(stderr, "Server ready.\n");

		rpc_server_listen(	/* listen for requests */
			1,		/* NOTE: PROCESS ONE RPC AT A TIME */
			&status);
		CHECK_STATUS(status, "server_listen failed", RESUME);
	}
#else
	/* Listen for remote calls. */
	fprintf(stderr, "Server ready.\n");

	rpc_server_listen(	/* listen for requests */
		rpc_c_listen_max_calls_default,
		&status);
	CHECK_STATUS(status, "server_listen failed", RESUME);
#endif

	FINALLY			/* error recovery and cleanup */

#ifdef TCLIENT
	(void)tpterm();
#endif

	rpc_ep_unregister(	/* remove endpoints from local endpoint map */
		INTERFACE_SPEC,		/* interface specification */
		bind_vector_p,		/* list of binding information */
		NULL,			/* object UUID's */
		&status);
	CHECK_STATUS(status, "Can't remove endpoints from map", RESUME);

	rpc_binding_vector_free(	/* free server binding handles */
		&bind_vector_p,		/* list of binding information */
		&status);
	CHECK_STATUS(status, "binding vector free failed", RESUME);

	fprintf(stderr, "Server exiting\n");
	ENDTRY
	return(0);
#else
	/* process application command line arguments, if any */

	/* open resource manager, if any */
	tperrno = 0;

	if (tx_open() < 0) {
		(void) userlog("ERROR: tpopen failed - %s",tpstrerror(tperrno));
		return(-1);
	}
	return(1);
#endif
}

#if defined(SERVER_KEYTAB) && defined(SERVER_PRINCIPAL_NAME)
/*
 * Internal routine to establish this server as the SERVER_PRINCIPAL_NAME
 * principal.
 */
#include <dce/sec_login.h>
static void key_mgmt_rtn (void);
static void refresh_login_context_rtn(sec_login_handle_t login_context);

void
establish_identity(error_status_t *o_status)
{
	pthread_attr_t attr;
	sec_login_handle_t login_context;
	sec_login_auth_src_t auth_src;
	void *server_key;
	error_status_t status;
	boolean32 identity_valid;
	boolean32 reset_passwd;
	pthread_t refresh_login_context_thread;
	pthread_t key_mgmt_thread;

	/*
	 * Set up the network identity for this server principal.
	 * The network credentials obtained are sealed and must be
	 * unsealed with the server's secret key before they can
	 * be used.
	 */
	sec_login_setup_identity(
		(unsigned_char_t *)SERVER_PRINCIPAL_NAME,/* principal name */
		sec_login_no_flags,		/* flags */
		&login_context,			/* returned login context */
		&status);
	CHECK_STATUS(status, "unable to set up identity", ABORT);

	/*
	 * Retrieve the server's secret key from the private keytab
	 * file.
	 */
	sec_key_mgmt_get_key(
		rpc_c_authn_dce_secret,	/* DCE shared-secret key authen. */
		SERVER_KEYTAB, 		/* server keytab file */
		SERVER_PRINCIPAL_NAME, 	/* principal name */
		0,			/* return most recent version */
		&server_key,		/* returned secret key */
		&status);
	CHECK_STATUS(status, "unable to retrive key", ABORT);

	/*
	 * Unseal the network identity using the server's secret key.
	 */
	identity_valid = sec_login_validate_identity(
		login_context, 		/* current login ocntext */
		server_key,		/* secret key */
		&reset_passwd,		/* true if expired */
		&auth_src,		/* how context was authorized */
		&status);

	/*
	 * Free the secret key as soon as we are done with it.
	 */
	sec_key_mgmt_free_key(
		&server_key,		/* secret key */
		&status);
	CHECK_STATUS(status, "unable to free key", ABORT);

	if (identity_valid) {
		/*
		 * Make sure that the server identity was validated by
		 * the network -
		 * i.e., the security server, instead of local data.
		 */
		if (auth_src != sec_login_auth_src_network) {
			fprintf (stderr, "Server has no network credentials\n");
			exit (1);
		}

		/*
		 * We make this login context the default for this process.
		 */
		sec_login_set_context(
			login_context,	/* current login context */
			&status);
		CHECK_STATUS(status, "unable to set login context", ABORT);

		/*
		 * Start up a thread to refresh the login context when it
		 * expires.
		 */
		if (pthread_attr_create(&attr) < 0) {
			fprintf(stderr, "pthread_attr_create failed\n");
			exit(1);
		}
#ifdef bigger_stack
		/*
		 * Set thread stack size bigger.
		 */
		if (pthread_attr_setstacksize(&attr, 200000) < 0) {
			fprintf(stderr, "pthread_attr_setstacksize failed\n");
			exit(1);
		}
#endif
		if ((pthread_create (&refresh_login_context_thread, 
			attr, 
			(pthread_startroutine_t) refresh_login_context_rtn, 
			(pthread_addr_t)login_context) ) == -1)
			exit (1);

		/*
		 * Start up a thread to manage our secret key.
		 */
		if ((pthread_create (&key_mgmt_thread, attr, 
			(pthread_startroutine_t) key_mgmt_rtn, 
			(pthread_addr_t)NULL) ) == -1)
			exit (1);

		 *o_status = status;
	}
	else {
		error_status_t temp_status;

		CHECK_STATUS(status, "unable to validate network identity", 
			RESUME);

		/* Reclaim the storage */
		sec_login_purge_context(
			&login_context,	/* current login context */
			&temp_status);
		CHECK_STATUS(temp_status, "unable to purge login context", 
			ABORT);
		*o_status = status;
		return;
	}
}

/*
 * A thread to periodically change the server's secret key.
 */
static void
key_mgmt_rtn(void)
{
	error_status_t status;

	while (1) {
		sec_key_mgmt_manage_key(
			rpc_c_authn_dce_secret,	/* DCE secret key authen. */
			SERVER_KEYTAB,		/* server keytab file */
			SERVER_PRINCIPAL_NAME,	/* principal name */
			&status);
		CHECK_STATUS(status, "key mgmt failure", ABORT);
	}
}

/*
 * A thread to periodically refresh the credentials contained in a
 * login context.
 */
#ifndef WIN32
#include <sys/time.h>
#else
#include <time.h>
#endif

static void
refresh_login_context_rtn(sec_login_handle_t login_context)
{
	struct timeval current_time;
#ifdef BSD
	struct timezone tz;
#elif defined(WIN32)
	time_t ltime;
#endif
	struct timespec delay;
	signed32 expiration;
	signed32 delay_time;
	unsigned32 used_kvno;
	boolean32 reset_passwd;
	boolean32 identity_valid;
	void *server_key;
	sec_login_auth_src_t auth_src;
	error_status_t status;

#define MINUTE 60

	while (1) {

#ifdef BSD
		/* BSD version of gettimeofday has a timezone parameter. */
		gettimeofday (&current_time, &tz);
#elif defined(WIN32)
		time(&ltime);
#else
		gettimeofday (&current_time);
#endif

		sec_login_get_expiration(
			login_context,		/* current login context */
			&expiration,		/* lifetime */
			&status);

		if (status != rpc_s_ok && status != sec_login_s_not_certified) {
			fprintf (stderr,
				"Cannot get login context expiration time\n");
			exit (1);
		}

		/* Wait until shortly before the login context expires. */
#ifdef WIN32
		delay_time = expiration - ltime - (10*MINUTE);
#else
		delay_time = expiration - current_time.tv_sec - (10*MINUTE);
#endif

		if (delay_time > 0) {
			delay.tv_sec = delay_time;
			delay.tv_nsec = 0;
			pthread_delay_np(&delay);
		}

		sec_login_refresh_identity(
			login_context,		/* login context */
			&status);
		CHECK_STATUS(status, "cannot refresh identity", ABORT);

		/*
		 * Retrieve the server's secret key from the private keytab
		 * file.
		 */
		sec_key_mgmt_get_key(
			rpc_c_authn_dce_secret,	/* DCE secret key authen. */
			SERVER_KEYTAB, 		/* server keytab file */
			SERVER_PRINCIPAL_NAME, 	/* principal name */
			0,			/* return most recent version */
			&server_key,		/* returned secret key */
			&status);
		CHECK_STATUS(status, "unable to retrive key", ABORT);

		/*
		 * The refreshed login context still needs to be validated.
		 */
		identity_valid = sec_login_validate_identity(
			login_context, 		/* login context */
			server_key,		/* secret key */
			&reset_passwd,		/* true if expired */
			&auth_src,		/* how context was authorized */
			&status);

		/*
		 * Free the secret key as soon as we are done with it.
		 */
		sec_key_mgmt_free_key(
			&server_key,		/* secret key */
			&status);
		CHECK_STATUS(status, "unable to free key", ABORT);

		if (! identity_valid) {
			error_status_t temp_status;

			/* Reclaim the storage */
			sec_login_purge_context(
				&login_context,	/* login context */
				&temp_status);
			CHECK_STATUS(temp_status, "unable to purge login context", ABORT);

			/* Report original error. */
			CHECK_STATUS(status, 
				"unable to validate network identity", ABORT);
		}

	}

}

#ifdef TCLIENT
#define APPDATALEN 100	/* SET APPLICATION AUTHENTICATION DATA LENGTH */
doinit()
{
	int	ret = 0;
	int	authtype;
	TPINIT	*tpinfo;

	/* Allocate a TPINIT buffer */
	tpinfo = (TPINIT *)tpalloc("TPINIT", (char *)NULL,
		TPINITNEED(APPDATALEN));

	if (tpinfo == (TPINIT *)NULL) {
		(void) fprintf(stderr,"ERROR: tpalloc for TPINIT failed - %s\n",
			tpstrerror(tperrno));
		return(-1);
	}

	(void)strcpy(tpinfo->usrname, "myname");	/* SET USER NAME */
	tpinfo->passwd[0] = '\0';
	tpinfo->datalen = (long) 0;

	switch(authtype = tpchkauth()) {
	case -1:
		(void) fprintf(stderr,
			"ERROR: cannot determine authentication level\n");
		tpfree((char *) tpinfo);
		return(-1);

	case	TPNOAUTH:
		break;
	case	TPSYSAUTH:
	case	TPAPPAUTH:
		(void)strcpy(tpinfo->passwd, "password");/* SET PASSWORD */

		if (authtype == TPSYSAUTH)
			break;

		/* SET APPLICATION DATA */
		(void)strcpy((char *)&tpinfo->data, "appdata");

		tpinfo->datalen=strlen((char *)&tpinfo->data)+1;
		break;
	}
	(void)strcpy(tpinfo->cltname, "DCECLIENT");	/* SET CLIENT NAME */

	tpinfo->flags = TPU_IGN;	/* turn off unsolicited notification */

	ret = tpinit(tpinfo);
	if (ret == -1) {
		(void) fprintf(stderr,"ERROR: tpinit() failed - %s\n",
			tpstrerror(tperrno));
	}
	(void)tpfree((char *)tpinfo);
	return(ret);
}
#endif	/* TCLIENT */

#endif	/* !TPSVRINIT */
