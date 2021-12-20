/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1994 Novell, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Novell, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ifndef FMLTARG_H
#define FMLTARG_H

/* #ident	"@(#) fml/libfml/fmltarg.h	$Revision: 1.3 $" */
#include <tmenv.h>
#ifndef NOWHAT
static	char	fmltarg_h[] = "@(#) fml/libfml/fmltarg.h	$Revision: 1.3 $";
#endif

#ifdef _as400_
#include "decimal.h"
#else
#include <decimal.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct fmltarget_t {
	long (_TM_FAR *char_to_targ) _((unsigned char _TM_FAR *c_char, unsigned char _TM_FAR *targ_char, long c_len, long left));
	long (_TM_FAR *dec_to_targ) _((dec_t _TM_FAR *c_dec, unsigned char _TM_FAR *targ_dec, int targbytes, int decpl, long left));
	long (_TM_FAR *float_to_targ) _((float c_float, unsigned char _TM_FAR *targ_float, long left));
	long (_TM_FAR *double_to_targ) _((double c_double, unsigned char _TM_FAR *targ_double, long left));
	long (_TM_FAR *long_to_targ) _((long c_long, unsigned char _TM_FAR *targ_long, long left));
	long (_TM_FAR *TM32U_to_targ) _((TM32U c_ulong, unsigned char _TM_FAR *targ_ulong, long left));
	long (_TM_FAR *short_to_targ) _((short c_short, unsigned char _TM_FAR *targ_short, long left));
	long (_TM_FAR *ushort_to_targ) _((unsigned short c_ushort, unsigned char _TM_FAR *targ_ushort, long left));
	long (_TM_FAR *targ_to_char) _((unsigned char _TM_FAR *targ_char, unsigned char _TM_FAR *c_char, long c_len));
	long (_TM_FAR *targ_to_dec) _((unsigned char _TM_FAR *targ_dec, dec_t _TM_FAR *c_dec, int targbytes, int decpl));
	long (_TM_FAR *targ_to_float) _((unsigned char _TM_FAR *targ_float, float _TM_FAR *c_float));
	long (_TM_FAR *targ_to_double) _((unsigned char _TM_FAR *targ_double, double _TM_FAR *c_double));
	long (_TM_FAR *targ_to_long) _((unsigned char _TM_FAR *targ_long, long _TM_FAR *c_long));
	long (_TM_FAR *targ_to_TM32U) _((unsigned char _TM_FAR *targ_ulong, TM32U _TM_FAR *c_ulong));
	long (_TM_FAR *targ_to_short) _((unsigned char _TM_FAR *targ_short, short _TM_FAR *c_short));
	long (_TM_FAR *targ_to_ushort) _((unsigned char _TM_FAR *targ_ushort, unsigned short _TM_FAR *c_ushort));
};

struct fmltarget_t _TM_FAR * _TMDLLENTRY Fsettarg _((struct fmltarget_t _TM_FAR *targ));
struct fmltarget_t _TM_FAR * _TMDLLENTRY Fsettarg32 _((struct fmltarget_t _TM_FAR *targ));

#if !defined(FML32)
extern void fml_init_FML_s370 _((struct fmltarget_t *));
#elif !defined(_TM_MAC)
extern void fml_init_F32_s370 _((struct fmltarget_t *));
#endif

#ifdef __cplusplus
}
#endif

#endif
