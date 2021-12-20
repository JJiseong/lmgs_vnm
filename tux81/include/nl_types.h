/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1990 AT&T; 1991 USL
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF USL
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ifndef NL_TYPES_H
#define NL_TYPES_H
/* #ident	"@(#) gp/libgp/i18n/nl_types.h	$Revision: 1.3 $" */
#ifndef TMENV_H
#include <tmenv.h>
#endif

#ifndef NOWHAT
static	char	nl_types_h[] = "@(#) gp/libgp/i18n/nl_types.h	$Revision: 1.3 $";
#endif

#ifndef NL_ARGMAX
#define NL_ARGMAX	9
#endif

#ifndef NL_MSGMAX
#define NL_MSGMAX	32767
#endif

#ifndef NL_TEXTMAX
#define	NL_TEXTMAX	512
#endif

#ifndef NL_SETMAX
#define	NL_SETMAX	255		/* max set number */
#endif

#define NL_MAXPATHLEN	1024
#define NL_PATH		"NLSPATH"
#define NL_LANG		"LANG"
#define NL_DEF_LANG	"english"

typedef int nl_item;

typedef struct {
	char *catd_set;
	char *catd_msgs;
	char *catd_data;
	int catd_set_nr;
	char catd_type;
} nl_catd_t;

typedef nl_catd_t *nl_catd;

#define CATNULL 0

/*
 * type fields for nl_catd_t
 */
#define MALLOC		'M'	/* old style malloc	   */

#ifdef _TMPROTOTYPES

#if defined(__cplusplus)
extern "C" {
#endif

int catclose(nl_catd);
char *catgets(nl_catd, int, int, char *);
nl_catd _TMDLLENTRY catopen(const char *, int);

#if defined(__cplusplus)
}
#endif

#else
int catclose();
char *catgets();
nl_catd _TMDLLENTRY catopen();
#endif

#endif
