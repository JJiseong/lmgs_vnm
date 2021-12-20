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
      * #ident	"@(#) cobol/cobatmi/TPINFDEF.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPINFDEF.cbl	$Revision: 1.3 $";
      *
      *  TPINFDEF.cbl
      *
	05 USRNAME	PIC X(30).
	05 CLTNAME	PIC X(30).
	05 PASSWD	PIC X(30).
	05 GRPNAME   	PIC X(30).
	05 NOTIFICATION-FLAG	PIC S9(9) COMP-5.
	   88  TPU-SIG 	VALUE 	1.
	   88  TPU-DIP 	VALUE 	2.
	   88  TPU-IGN 	VALUE 	3.
	05 ACCESS-FLAG		PIC S9(9) COMP-5.
	   88  TPSA-FASTPATH 	VALUE  	1.
	   88  TPSA-PROTECTED 	VALUE 	2.
	05 CONTEXTS-FLAG	PIC S9(9) COMP-5.
	   88  TP-SINGLE-CONTEXT	VALUE  	0.
	   88  TP-MULTI-CONTEXTS	VALUE 	1.
	05 DATALEN	PIC S9(9) COMP-5.
