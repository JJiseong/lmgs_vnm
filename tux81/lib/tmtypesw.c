/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*      Copyright (c) 1988 AT&T; 1991 USL; 1994 Novell, Inc.
        All rights reserved

        THIS IS UNPUBLISHED PROPRIETARY
        SOURCE CODE OF Novell, Inc.
        The copyright notice above does not
        evidence any actual or intended
        publication of such source code.
*/
/* #ident	"@(#) tuxedo/libbuft/tmtypesw.c	$Revision: 1.7 $" */
#include <tmenv.h>
#ifndef NOWHAT
static  char    sccsid[] = "@(#) tuxedo/libbuft/tmtypesw.c	$Revision: 1.7 $";
#endif

#include <stdio.h>
#include <tmtypes.h>

#ifdef _TM_NETWARE
#include <signal.h>
#include <process.h>
	static int LibHandle, threadGroupID;
#endif /* _TM_NETWARE */

/* application buffer type switch */

/*
 * Initialization of the buffer type switch.
 */

static struct tmtype_sw_t tm_typesw[] = {
{
	"CARRAY",	/* type */
	"*",		/* subtype */
	0		/* dfltsize */
},
{
	"STRING",	/* type */
	"*",		/* subtype */
	512,		/* dfltsize */
	NULL,		/* initbuf */
	NULL,		/* reinitbuf */
	NULL,		/* uninitbuf */
	_strpresend,	/* presend */
	NULL,		/* postsend */
	NULL,		/* postrecv */
	_strencdec,	/* encdec */
	NULL,		/* route */
#if !defined(_TMDOWN) || defined(WIN32)
	_sfilter,	/* filter */
	_sformat,	/* format */
#else
	NULL,		/* filter - not available on this platform */
	NULL,		/* format - not available on this platform */
#endif
	NULL		/* presend2 */
},
{
	"FML",		/* type */
	"*",		/* subtype */
	1024,		/* dfltsize */
	_finit,		/* initbuf */
	_freinit,	/* reinitbuf */
	_funinit,	/* uninitbuf */
	_fpresend,	/* presend */
	_fpostsend,	/* postsend */
	_fpostrecv,	/* postrecv */
	_fencdec,	/* encdec */
	_froute,	/* route */
#if !defined(_TMDOWN) || defined(WIN32)
	_ffilter,	/* filter */
	_fformat,	/* format */
#else
	NULL,		/* filter - not available on this platform */
	NULL,		/* format - not available on this platform */
#endif
	NULL		/* presend2 */
},
{
	"VIEW",		/* type */
	"*",		/* subtype */
	1024,		/* dfltsize */
	_vinit,		/* initbuf */
	_vreinit,	/* reinitbuf */
	NULL,		/* uninitbuf */
	_vpresend,	/* presend */
	NULL,		/* postsend */
	NULL,		/* postrecv */
	_vencdec,	/* encdec */
	_vroute,	/* route */
#if !defined(_TMDOWN) || defined(WIN32)
	_vfilter,	/* filter */
	_vformat,	/* format */
#else
	NULL,		/* filter - not available on this platform */
	NULL,		/* format - not available on this platform */
#endif
	NULL		/* presend2 */
},
{	/* XATMI - identical to CARRAY */
	"X_OCTET",	/* type */
	"*",		/* subtype */
	0 		/* dfltsize */
},
{	/* XATMI - identical to VIEW */
#if (defined(__OS2__) && defined(__32BIT__) && defined(__IBMC__)) || defined(_as400_)
	"X_C_TYPE",	/* type */
#else
	{'X','_','C','_','T','Y','P','E'},	/* type */
#endif
	"*",		/* subtype */
	1024,		/* dfltsize */
	_vinit,		/* initbuf */
	_vreinit,	/* reinitbuf */
	NULL,		/* uninitbuf */
	_vpresend,	/* presend */
	NULL,		/* postsend */
	NULL,		/* postrecv */
	_vencdec,	/* encdec */
	_vroute,	/* route */
#if !defined(_TMDOWN) || defined(WIN32)
	_vfilter,	/* filter */
	_vformat,	/* format */
#else
	NULL,		/* filter - not available on this platform */
	NULL,		/* format - not available on this platform */
#endif
	NULL		/* presend2 */
},
{	/* XATMI - identical to VIEW */
#if (defined(__OS2__) && defined(__32BIT__) && defined(__IBMC__)) || defined(_as400_)
	"X_COMMON",
#else
	{'X','_','C','O','M','M','O','N'},	/* type */
#endif
	"*",		/* subtype */
	1024,		/* dfltsize */
	_vinit,		/* initbuf */
	_vreinit,	/* reinitbuf */
	NULL,		/* uninitbuf */
	_vpresend,	/* presend */
	NULL,		/* postsend */
	NULL,		/* postrecv */
	_vencdec,	/* encdec */
	_vroute,	/* route */
#if !defined(_TMDOWN) || defined(WIN32)
	_vfilter,	/* filter */
	_vformat,	/* format */
#else
	NULL,		/* filter - not available on this platform */
	NULL,		/* format - not available on this platform */
#endif
	NULL		/* presend2 */
},
{
	"FML32",	/* type */
	"*",		/* subtype */
	1024,		/* dfltsize */
	_finit32,	/* initbuf */
	_freinit32,	/* reinitbuf */
	_funinit32,	/* uninitbuf */
	_fpresend32,	/* presend */
	_fpostsend32,	/* postsend */
	_fpostrecv32,	/* postrecv */
	_fencdec32,	/* encdec */
	_froute32,	/* route */
#if !defined(_TMDOWN) || defined(WIN32)
	_ffilter32,	/* filter */
	_fformat32,	/* format */
#else
	NULL,		/* filter - not available on this platform */
	NULL,		/* format - not available on this platform */
#endif
	_fpresend232,	/* presend2 */
	_fmbconv32	/* multi-byte codeset data conversion */
},
{
	"VIEW32",	/* type */
	"*",		/* subtype */
	1024,		/* dfltsize */
	_vinit32,	/* initbuf */
	_vreinit32,	/* reinitbuf */
	NULL,		/* uninitbuf */
	_vpresend32,	/* presend */
	NULL,		/* postsend */
	NULL,		/* postrecv */
	_vencdec32,	/* encdec */
	_vroute32,	/* route */
#if !defined(_TMDOWN) || defined(WIN32)
	_vfilter32,	/* filter */
	_vformat32,	/* format */
#else
	NULL,		/* filter - not available on this platform */
	NULL,		/* format - not available on this platform */
#endif
	NULL		/* presend2 */
},
{
	"XML",	/* type */
	"*",		/* subtype */
	0,		/* dfltsize */
	NULL,		/* _xinit - not available */
	NULL,		/* _xreinit - not available */
	NULL,		/* _xuninit - not available */
	NULL,		/* _xpresend - not available */
	NULL,		/* _xpostsend - not available */
	NULL,		/* _xpostrecv - not available */
	NULL,		/* _xencdec - not available */
	_xroute,	/* _xroute */
	NULL,		/* filter - not available */
	NULL		/* format - not available */
},
{
#if (defined(__OS2__) && defined(__32BIT__) && defined(__IBMC__)) || defined(_as400_)
	"MBSTRING",	/* type */
#else
	{'M','B','S','T','R','I','N','G'},	/* type */
#endif
	"*",		/* subtype */
	0,		/* dfltsize */
	_mbsinit,	/* initbuf */
	NULL,		/* reinitbuf */
	NULL,		/* uninitbuf */
	NULL,		/* presend */
	NULL,		/* postsend */
	NULL,		/* postrecv */
	NULL,		/* encdec */
	NULL,		/* route */
	NULL,		/* filter */
	NULL,		/* format */
	NULL,		/* presend2 */
	_mbsconv	/* multi-byte codeset data conversion */
},
{
""
}
};


/*
 * _tmtypeswaddr():  
 *	Return the address of the application buffer type switch.
 *	This routine should always be used instead of the "tm_typesw"
 *	symbol, because some dynamic linking environments cannot
 *	access data symbols across libraries.
 */
TMTYPESW _TM_FAR * 
#ifdef _TMPROTOTYPES
_TMDLLENTRY
_tmtypeswaddr(void)
#else
_tmtypeswaddr()
#endif
{
#if defined(sun) && !defined(SOLARIS)
	/* On SunOS 4.x this forces proper loading of this library */
	(void) time(0);
#endif
	return(tm_typesw);
}

#ifdef _TM_WIN

#include <windows.h>

int FAR PASCAL
WEP (int bSystemExit)
{
	bSystemExit = bSystemExit;      /* unused */
	return(1);
}

int FAR PASCAL
LibMain(HANDLE hModule, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine)
{
	hModule = hModule;
	wDataSeg = wDataSeg;
	cbHeapSize = cbHeapSize;
	lpszCmdLine = lpszCmdLine;
	return(1);
}

#endif

#ifdef _TM_OS2_32
unsigned long _System _DLL_InitTerm(unsigned long hModule, unsigned long ulFlag)
{
	switch(ulFlag) {
		case 0:
		if(_CRT_init() == -1)
			return(0UL);
		break;

		case 1:
		_CRT_term();
		break;
	}
	return(1UL);
}
#endif

#ifdef _TM_NETWARE
static void bufCleanup(int);
static int bufCleanupNLM(void *);

int
#ifdef _TMPROTOTYPES
main(int argc, char *argv[])
#else
main(argc, argv)
int argc;
char *argv[];
#endif
{
	LibHandle = RegisterLibrary(bufCleanupNLM);
	_e_signal(NULL, SIGTERM, bufCleanup);
	ExitThread(TSR_THREAD, 0);
}

static int
#ifdef _TMPROTOTYPES
bufCleanupNLM(void *arg)
#else
bufCleanupNLM(arg)
void *arg;
#endif
{
	(void) printf("Client 0x%lx exits\n", arg);
	free_data(arg);
	return(0);
}

static void
#ifdef _TMPROTOTYPES
bufCleanup(int sig)
#else
bufCleanup(sig)
int sig;
#endif
{
	/* Free all the contexts */
	(void) printf("GP Signal Cleanup function called\n");
	DeregisterLibrary(LibHandle);
	return;
}

#endif /* _TM_NETWARE */
