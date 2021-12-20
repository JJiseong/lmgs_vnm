      *
      *	Copyright (c) 1994 Novell Inc.
      * All rights reserved
      *
      *	THIS IS UNPUBLISHED PROPRIETARY
      *	SOURCE CODE OF Novell Inc.
      *	The copyright notice above does not
      *	evidence any actual or intended
      *	publication of such source code.
      *
      * #ident	"@(#) cobol/cobatmi/FMLINFO.cbl	$Revision: 1.3 $" 
      * static	char	sccsid[] = "@(#) cobol/cobatmi/FMLINFO.cbl	$Revision: 1.3 $";
      *
      *  FMLINFO.cbl
      *
	05 FML-STATUS  PIC S9(9) COMP-5.
		88 FOK       		VALUE 0.
		88 FALIGNERR		VALUE 1.
		88 FNOTFLD		VALUE 2.
		88 FNOSPACE		VALUE 3.
		88 FNOTPRES		VALUE 4.
		88 FBADFLD		VALUE 5.
		88 FTYPERR		VALUE 6.
		88 FEUNIX		VALUE 7.
		88 FBADNAME		VALUE 8.
		88 FMALLOC		VALUE 9.
		88 FSYNTAX		VALUE 10.
		88 FFTOPEN		VALUE 11.
		88 FFTSYNTAX		VALUE 12.
		88 FEINVAL		VALUE 13.
		88 FBADTBL		VALUE 14.
		88 FBADVIEW		VALUE 15.
		88 FVFSYNTAX		VALUE 16.
		88 FVFOPEN		VALUE 17.
		88 FBADACM		VALUE 18.
		88 FNOCNAME		VALUE 19.
		88 FEBADOP		VALUE 20.
      *
	05 FML-LENGTH	PIC S9(9) COMP-5.
      *
	05 FML-MODE	PIC S9(9) COMP-5.
		88 FUPDATE 		VALUE 1.
		88 FCONCAT		VALUE 2.
		88 FJOIN	  	VALUE 3.
		88 FOJOIN	 	VALUE 4.
      *
	05 VIEWNAME	PIC X(33).
