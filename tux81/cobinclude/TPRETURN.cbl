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
      * #ident	"@(#) cobol/cobatmi/TPRETURN.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPRETURN.cbl	$Revision: 1.3 $";
      *
      *  TPRETURN.cbl
      *
      * Call TPRETURN, and exit the program immediately afterwards to
      * ensure that the service will terminate with the results
      * sent back to the caller.
      *
	CALL "TPRETURN" USING TPSVCRET-REC 
		TPTYPE-REC 
		DATA-REC 
		TPSTATUS-REC
	EXIT PROGRAM.
      *
