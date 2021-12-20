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
      * #ident	"@(#) cobol/cobatmi/TPSVCRET.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPSVCRET.cbl	$Revision: 1.3 $";
      *
      *  TPSVCRET.cbl
      *
	05 TP-RETURN-VAL PIC S9(9) COMP-5.
		88 TPSUCCESS  VALUE 0.
		88 TPFAIL     VALUE 1.
		88 TPEXIT     VALUE 2.
		88 TPLONGJUMP VALUE 3.
		88 TPBREAK    VALUE 4.
	05 APPL-CODE 	 PIC S9(9) COMP-5.

