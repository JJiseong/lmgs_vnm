      *
      *	Copyright (c) 1992 USL
      * All rights reserved
      *
      *	THIS IS UNPUBLISHED PROPRIETARY
      *	SOURCE CODE OF USL
      *	The copyright notice above does not
      *	evidence any actual or intended
      *	publication of such source code.
      *
      *   Copyright:   (c) 1991, 1992, by BULL HN Information Systems Ltd
      * This Source Code has been provided by Bull Information Systems Ltd. 
      * under a License Agreement containing restrictions on its disclosure.  
      * This software contains proprietary information constituting valuable 
      * Bull trade secrets and is also protected by copyright law as an 
      * unpublished work.   
      *
      * #ident	"@(#) cobol/cobatmi/TPSVCDEF.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPSVCDEF.cbl	$Revision: 1.3 $";
      *
      *  TPSVCDEF.cbl	
      *
	05 COMM-HANDLE		PIC S9(9) COMP-5.
	05 TPBLOCK-FLAG 	PIC S9(9) COMP-5.
		88 TPBLOCK	 VALUE 0.
		88 TPNOBLOCK	 VALUE 1.
	05 TPTRAN-FLAG 	PIC S9(9) COMP-5.
		88 TPTRAN	VALUE 0.
		88 TPNOTRAN  	VALUE 1.  
	05 TPREPLY-FLAG 	PIC S9(9) COMP-5.
		88 TPREPLY	VALUE 0.
		88 TPNOREPLY	VALUE 1.
	05 TPACK-FLAG 	PIC S9(9) COMP-5 REDEFINES TPREPLY-FLAG.
		88 TPNOACK 	VALUE 0.
		88 TPACK	VALUE 1.
	05 TPTIME-FLAG 	PIC S9(9) COMP-5.
		88 TPTIME	VALUE 0.
		88 TPNOTIME	VALUE 1.
	05 TPSIGRSTRT-FLAG 	PIC S9(9) COMP-5.
		88 TPNOSIGRSTRT	VALUE 0.
		88 TPSIGRSTRT	VALUE 1.
	05 TPGETANY-FLAG 	PIC S9(9) COMP-5.
		88 TPGETHANDLE 	VALUE 0.
		88 TPGETANY 	VALUE 1.
	05 TPSENDRECV-FLAG 	PIC S9(9) COMP-5.
		88 TPSENDONLY 	VALUE 0.
		88 TPRECVONLY	VALUE 1.
	05 TPNOCHANGE-FLAG 	PIC S9(9) COMP-5.
		88 TPCHANGE	VALUE 0.
		88 TPNOCHANGE 	VALUE 1.
	05 TPSERVICETYPE-FLAG 	PIC S9(9) COMP-5.
		88  TPREQRSP	VALUE IS 0.
		88  TPCONV	VALUE IS 1.
      *
	05 APPKEY		PIC S9(9) COMP-5.
	05 CLIENTID OCCURS 4 TIMES PIC S9(9) COMP-5.
	05 SERVICE-NAME		PIC X(15).
