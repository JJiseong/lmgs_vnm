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
      * #ident	"@(#) cobol/cobatmi/TPPRIDEF.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPPRIDEF.cbl	$Revision: 1.3 $";
      *
      *  TPPRIDEF.cbl	
      *
	05 PRIORITY 	PIC S9(9) COMP-5.
	05 PRIO-FLAG    PIC S9(9) COMP-5.
		88 TPABSOLUTE    VALUE 0.  
		88 TPRELATIVE  	 VALUE 1.
      *
