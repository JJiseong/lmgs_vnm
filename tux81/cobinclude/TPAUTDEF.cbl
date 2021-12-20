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
      * #ident	"@(#) cobol/cobatmi/TPAUTDEF.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/TPAUTDEF.cbl	$Revision: 1.3 $";
      *
      *  TPAUTDEF.cbl
      *
	05 AUTH-FLAG	PIC S9(9) COMP-5.
		88  TPNOAUTH  VALUE 0.
		88  TPSYSAUTH VALUE 1.
		88  TPAPPAUTH VALUE 2.
