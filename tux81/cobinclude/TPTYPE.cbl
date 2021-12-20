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
      * #ident	"@(#) cobol/cobatmi/TPTYPE.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPTYPE.cbl	$Revision: 1.3 $";
      *
      *  TPTYPE.cbl
      *
	05 REC-TYPE 	PIC X(8).
		88 X-OCTET   VALUE "X_OCTET".
		88 X-COMMON  VALUE "X_COMMON".
	05 SUB-TYPE 	PIC X(16).
	05 LEN 		PIC S9(9) COMP-5.
		88 NO-LENGTH VALUE 0.
	05 TPTYPE-STATUS PIC S9(9) COMP-5.
		88 TPTYPEOK     VALUE 0.
		88 TPTRUNCATE   VALUE 1.
      *
