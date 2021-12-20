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
      * #ident	"@(#) cobol/cobatmi/TPSTATUS.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPSTATUS.cbl	$Revision: 1.3 $";
      *
      *  TPSTATUS.cbl
      *
	05 TP-STATUS  PIC S9(9) COMP-5.
		88 TPOK       		VALUE 0.
		88 TPEABORT    		VALUE 1.
		88 TPEBADDESC  		VALUE 2.
		88 TPEBLOCK    		VALUE 3.
		88 TPEINVAL    		VALUE 4.
		88 TPELIMIT    		VALUE 5.
		88 TPENOENT    		VALUE 6.
		88 TPEOS       		VALUE 7.
		88 TPEPERM     		VALUE 8.
		88 TPEPROTO    		VALUE 9.
		88 TPESVCERR   		VALUE 10.
		88 TPESVCFAIL  		VALUE 11.
		88 TPESYSTEM   		VALUE 12.
		88 TPETIME     		VALUE 13.
		88 TPETRAN     		VALUE 14.
		88 TPEGOTSIG   		VALUE 15.
		88 TPERMERR    		VALUE 16.
		88 TPEITYPE    		VALUE 17.
		88 TPEOTYPE    		VALUE 18.
		88 TPERELEASE  		VALUE 19.
		88 TPEHAZARD   		VALUE 20.
		88 TPEHEURISTIC 	VALUE 21.
		88 TPEEVENT     	VALUE 22.
		88 TPEMATCH     	VALUE 23.
		88 TPEDIAGNOSTIC    	VALUE 24.
		88 TPEMIB	    	VALUE 25.
		88 TPEMAXVAL    	VALUE 26.
      *
	05 TPEVENT		PIC S9(9) COMP-5.
		88 TPEV-NOEVENT 	VALUE 0.
		88 TPEV-DISCONIMM 	VALUE 1.
		88 TPEV-SENDONLY  	VALUE 2.  
		88 TPEV-SVCERR		VALUE 3.
		88 TPEV-SVCFAIL 	VALUE 4.
		88 TPEV-SVCSUCC 	VALUE 5.
      *
	05 APPL-RETURN-CODE	PIC S9(9) COMP-5.
