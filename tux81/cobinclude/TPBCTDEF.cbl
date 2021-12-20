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
      * #ident	"@(#) cobol/cobatmi/TPBCTDEF.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPBCTDEF.cbl	$Revision: 1.3 $";
      *
      *  TPBCTDEF.cbl	
      *
	05 TPBLOCK-FLAG 	PIC S9(9) COMP-5.
		88 TPBLOCK	 VALUE 0.
		88 TPNOBLOCK	 VALUE 1.
	05 TPTIME-FLAG 	PIC S9(9) COMP-5.
		88 TPTIME	VALUE 0.
		88 TPNOTIME	VALUE 1.
	05 TPSIGRSTRT-FLAG 	PIC S9(9) COMP-5.
		88 TPNOSIGRSTRT	VALUE 0.
		88 TPSIGRSTRT	VALUE 1.
	05 LMID 		PIC X(30).
	05 USERNAME 		PIC X(30).
	05 CLTNAME 		PIC X(30).
