/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 1999-2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Log: XMLReader.hpp,v $
 * Revision 1.1  2002/05/11 20:19:15  bhavani
 * CR#CR062582# adding xercesc 1.7 file
 *
 * Revision 1.1.1.1  2002/02/01 22:22:02  peiyongz
 * sane_include
 *
 * Revision 1.18  2001/12/06 17:47:04  tng
 * Performance Enhancement.  Modify the handling of the fNEL option so that it results in fgCharCharsTable being modified, instead of having all of the low-level routines check the option.  This seemed acceptable because the code appears to only permit the option to be turned on and not turned off again.   By Henry Zongaro.
 *
 * Revision 1.17  2001/07/12 18:50:13  tng
 * Some performance modification regarding standalone check and xml decl check.
 *
 * Revision 1.16  2001/05/11 13:26:17  tng
 * Copyright update.
 *
 * Revision 1.15  2001/05/03 18:42:51  knoaman
 * Added new option to the parsers so that the NEL (0x85) char can be treated as a newline character.
 *
 * Revision 1.14  2001/01/25 19:16:58  tng
 * const should be used instead of static const.  Fixed by Khaled Noaman.
 *
 * Revision 1.13  2000/07/25 22:33:05  aruna1
 * Char definitions in XMLUni moved to XMLUniDefs
 *
 * Revision 1.12  2000/07/08 00:17:13  andyh
 * Cleanup of yesterday's speedup changes.  Merged new bit into the
 * scanner character properties table.
 *
 * Revision 1.11  2000/07/07 01:08:44  andyh
 * Parser speed up in scan of XML content.
 *
 * Revision 1.10  2000/07/06 21:00:52  jpolast
 * inlined getNextCharIfNot() for better performance
 *
 * Revision 1.9  2000/05/11 23:11:33  andyh
 * Add missing validity checks for stand-alone documents, character range
 * and Well-formed parsed entities.  Changes contributed by Sean MacRoibeaird
 * <sean.Macroibeaird@ireland.sun.com>
 *
 * Revision 1.8  2000/03/02 19:54:29  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.7  2000/02/24 20:18:07  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.6  2000/02/06 07:47:53  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.5  2000/01/25 01:04:21  roddey
 * Fixes a bogus error about ]]> in char data.
 *
 * Revision 1.4  2000/01/22 00:01:08  roddey
 * Simple change to get rid of two hard coded 'x' type characters, which won't
 * work on EBCDIC systems.
 *
 * Revision 1.3  1999/12/18 00:20:00  roddey
 * More changes to support the new, completely orthagonal, support for
 * intrinsic encodings.
 *
 * Revision 1.2  1999/12/15 19:48:03  roddey
 * Changed to use new split of transcoder interfaces into XML transcoders and
 * LCP transcoders, and implementation of intrinsic transcoders as pluggable
 * transcoders, and addition of Latin1 intrinsic support.
 *
 * Revision 1.1.1.1  1999/11/09 01:08:22  twl
 * Initial checkin
 *
 * Revision 1.3  1999/11/08 20:44:47  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */

#if !defined(XMLREADER_HPP)
#define XMLREADER_HPP

#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/XMLRecognizer.hpp>
#include <xercesc/framework/XMLBuffer.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <fstream.h>
#include <iostream.h>

class InputSource;
class BinInputStream;
class ReaderMgr;
class XMLBuffer;
class XMLScanner;
class XMLTranscoder;


// Masks for the fgCharCharsTable array
const XMLByte   gBaseCharMask               = 0x1;
const XMLByte   gSpecialCharDataMask        = 0x2;
const XMLByte   gNameCharMask               = 0x4;
const XMLByte   gPlainContentCharMask       = 0x8;
const XMLByte   gSpecialStartTagCharMask    = 0x10;
const XMLByte   gLetterCharMask             = 0x20;
const XMLByte   gXMLCharMask                = 0x40;
const XMLByte   gWhitespaceCharMask         = 0x80;


// ---------------------------------------------------------------------------
//  Instances of this class are used to manage the content of entities. The
//  scanner maintains a stack of these, one for each entity (this means entity
//  in the sense of any parsed file or internal entity) currently being
//  scanned. This class, given a binary input stream will handle reading in
//  the data and decoding it from its external decoding into the internal
//  Unicode format. Once internallized, this class provides the access
//  methods to read in the data in various ways, maintains line and column
//  information, and provides high performance character attribute checking
//  methods.
//
//  This is NOT to be derived from.
//
// ---------------------------------------------------------------------------
class XMLPARSER_EXPORT XMLReader
{
public:
    // -----------------------------------------------------------------------
    //  Public types
    // -----------------------------------------------------------------------
    enum Types
    {
        Type_PE
        , Type_General
    };

    enum Sources
    {
        Source_Internal
        , Source_External
    };

    enum RefFrom
    {
        RefFrom_Literal
        , RefFrom_NonLiteral
    };


    // -----------------------------------------------------------------------
    //  Public, static methods
    // -----------------------------------------------------------------------
    static bool isAllSpaces
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    static bool containsWhiteSpace
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );


    static bool isBaseChar(const XMLCh toCheck);
    static bool isFirstNameChar(const XMLCh toCheck);
    static bool isNameChar(const XMLCh toCheck);
    static bool isPlainContentChar(const XMLCh toCheck);
    static bool isPublicIdChar(const XMLCh toCheck);
    static bool isSpecialCharDataChar(const XMLCh toCheck);
    static bool isSpecialStartTagChar(const XMLCh toCheck);
    static bool isXMLLetter(const XMLCh toCheck);
    static bool isXMLChar(const XMLCh toCheck);
    static bool isWhitespace(const XMLCh toCheck);

    /**
      * Return the value of fgNEL flag.
      */
    static bool isNELRecognized();


    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XMLReader
    (
        const   XMLCh* const                pubId
        , const XMLCh* const                sysId
        ,       BinInputStream* const       streamToAdopt
        , const RefFrom                     from
        , const Types                       type
        , const Sources                     source
        , const bool                        throwAtEnd = false
        , const bool                        urlCaching = false
        , const XMLCh* const                diskCachePath = 0
    );

    XMLReader
    (
        const   XMLCh* const                pubId
        , const XMLCh* const                sysId
        ,       BinInputStream* const       streamToAdopt
        , const XMLCh* const                encodingStr
        , const RefFrom                     from
        , const Types                       type
        , const Sources                     source
        , const bool                        throwAtEnd = false
        , const bool                        urlCaching = false
        , const XMLCh* const                diskCachePath = 0
    );

    ~XMLReader();


    // -----------------------------------------------------------------------
    //  Character buffer management methods
    // -----------------------------------------------------------------------
    unsigned long charsLeftInBuffer() const;
    bool refreshCharBuffer();


    // -----------------------------------------------------------------------
    //  Scanning methods
    // -----------------------------------------------------------------------
    bool getName(XMLBuffer& toFill, const bool token);
    bool getNextChar(XMLCh& chGotten);
    bool getNextCharIfNot(const XMLCh chNotToGet, XMLCh& chGotten);
    void movePlainContentChars(XMLBuffer &dest);
    bool getSpaces(XMLBuffer& toFill);
    bool getUpToCharOrWS(XMLBuffer& toFill, const XMLCh toCheck);
    bool peekNextChar(XMLCh& chGotten);
    bool skipIfQuote(XMLCh& chGotten);
    bool skipSpaces(bool& skippedSomething);
    bool skippedChar(const XMLCh toSkip);
    bool skippedSpace();
    bool skippedString(const XMLCh* const toSkip);
    bool peekString(const XMLCh* const toPeek);


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    unsigned int getColumnNumber() const;
    const XMLCh* getEncodingStr() const;
    unsigned int getLineNumber() const;
    bool getNoMoreFlag() const;
    const XMLCh* getPublicId() const;
    unsigned int getReaderNum() const;
    RefFrom getRefFrom() const;
    Sources getSource() const;
    unsigned int getSrcOffset() const;
    const XMLCh* getSystemId() const;
    bool getThrowAtEnd() const;
    Types getType() const;
    bool getURLEntityCaching() const;


    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    bool setEncoding
    (
        const   XMLCh* const    newEncoding
    );
    void setReaderNum(const unsigned int newNum);
    void setThrowAtEnd(const bool newValue);


private:
    // ---------------------------------------------------------------------------
    //  Class Constants
    //
    //  kCharBufSize
    //      The size of the character spool buffer that we use. Its not terribly
    //      large because its just getting filled with data from a raw byte
    //      buffer as we go along. We don't want to decode all the text at
    //      once before we find out that there is an error.
    //
    //      NOTE: This is a size in characters, not bytes.
    //
    //  kRawBufSize
    //      The size of the raw buffer from which raw bytes are spooled out
    //      as we transcode chunks of data. As it is emptied, it is filled back
    //      in again from the source stream.
    // ---------------------------------------------------------------------------
    enum Constants
    {
        kCharBufSize        = 16 * 1024
        , kRawBufSize       = 48 * 1024
    };


    // -----------------------------------------------------------------------
    //  Private static methods
    // -----------------------------------------------------------------------
    static bool checkTable
    (
        const   XMLCh* const    theTable
        , const XMLCh           toCheck
    );


    /**
      * Method to enable NEL char to be treated as white space char.
      */
    static void enableNELWS();

    // -----------------------------------------------------------------------
    //  Private helper methods
    // -----------------------------------------------------------------------
    void checkForSwapped();

    void doInitCharSizeChecks();

    void doInitDecode();

    XMLByte getNextRawByte
    (
        const   bool            eoiOk
    );

    void refreshRawBuffer();

    void writeToFile();

    void setTranscoder
    (
        const   XMLCh* const    newEncoding
    );

    unsigned int xcodeMoreChars
    (
                XMLCh* const            bufToFill
        ,       unsigned char* const    charSizes
        , const unsigned int            maxChars
    );


    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fCharIndex
    //      The index into the character buffer. When this hits fCharsAvail
    //      then its time to refill.
    //
    //  fCharBuf
    //      A buffer that the reader manager fills up with transcoded
    //      characters a small amount at a time.
    //
    //  fCharsAvail
    //      The characters currently available in the character buffer.
    //
    //  fCharSizeBuf
    //      This buffer is an array that contains the number of source chars
    //      eaten to create each char in the fCharBuf buffer. So the entry
    //      fCharSizeBuf[x] is the number of source chars that were eaten
    //      to make the internalized char fCharBuf[x]. This only contains
    //      useful data if fSrcOfsSupported is true.
    //
    //  fCurCol
    //  fCurLine
    //      The current line and column that we are in within this reader's
    //      text.
    //
    //  fEncoding
    //      This is the rough encoding setting. This enum is set during
    //      construction and just tells us the rough family of encoding that
    //      we are doing.
    //
    //  fEncodingStr
    //      This is the name of the encoding we are using. It will be
    //      provisionally set during construction, from the auto-sensed
    //      encoding. But it might be overridden when the XMLDecl is finally
    //      seen by the scanner. It can also be forced to a particular
    //      encoding, in which case fForcedEncoding is set.
    //
    //  fForcedEncoding
    //      If the encoding if forced then this is set and all other
    //      information will be ignored. This encoding will be taken as
    //      gospel. This is done by calling an alternate constructor.
    //
    //  fNoMore
    //      This is set when the source text is exhausted. It lets us know
    //      quickly that no more text is available.
    //
    //  fRawBufIndex
    //      The current index into the raw byte buffer. When its equal to
    //      fRawBytesAvail then we need to read another buffer.
    //
    //  fRawByteBuf
    //      This is the raw byte buffer that is used to spool out bytes
    //      from into the fCharBuf buffer, as we transcode in blocks.
    //
    //  fRawBytesAvail
    //      The number of bytes currently available in the raw buffer. This
    //      helps deal with the last buffer's worth, which will usually not
    //      be a full one.
    //
    //  fReaderNum
    //      Each reader from a particular reader manager (which means from a
    //      particular document) is given a unique number. The reader manager
    //      sets these numbers. They are used to catch things like partial
    //      markup errors.
    //
    //  fRefFrom
    //      This flag is provided in the ctor, and tells us if we represent
    //      some entity being expanded inside a literal. Sometimes things
    //      happen differently inside and outside literals.
    //
    //  fPublicId
    //  fSystemId
    //      These are the system and public ids of the source that this
    //      reader is reading.
    //
    //  fSentTrailingSpace
    //      If we are a PE entity being read and we not referenced from a
    //      literal, then a leading and trailing space must be faked into the
    //      data. This lets us know we've done the trailing space already (so
    //      we don't just keep doing it again and again.)
    //
    //  fSource
    //      Indicates whether the content this reader is spooling as already
    //      been internalized. This will prevent multiple processing of
    //      whitespace when an already internalized entity is being spooled
    //      out.
    //
    //  fSpareChar
    //      Some encodings can create two chars in an atomic way, e.g.
    //      surrogate pairs. We might not be able to store both, so we store
    //      it here until the next buffer transcoding operation.
    //
    //  fSrcOfsBase
    //      This is the base offset within the source of this entity. Values
    //      in the curent fCharSizeBuf array are relative to this value.
    //
    //  fSrcOfsSupported
    //      This flag is set to indicate whether source byte offset info
    //      is supported. For intrinsic encodings, its always set since we
    //      can always support it. For transcoder based encodings, we ask
    //      the transcoder if it supports it or not.
    //
    //  fStream
    //      This is the input stream that provides the data for the reader.
    //      Its always treated as a raw byte stream. The derived class will
    //      ask for buffers of text from it and will handle making some
    //      sense of it.
    //
    //  fSwapped
    //      If the encoding is one of the ones we do intrinsically, and its
    //      in a different byte order from our native order, then this is
    //      set to remind us to byte swap it during transcoding.
    //
    //  fThrowAtEnd
    //      Indicates whether the reader manager should throw an end of entity
    //      exception at the end of this reader instance. This is usually
    //      set for top level external entity references. It overrides the
    //      reader manager's global flag that controls throwing at the end
    //      of entities. Defaults to false.
    //
    //  fTranscoder
    //      If the encoding is not one that we handle intrinsically, then
    //      we use an an external transcoder to do it. This class is an
    //      abstraction that allows us to use pluggable external transcoding
    //      services (via XMLTransService in util.)
    //
    //  fType
    //      Indicates whether this reader represents a PE or not. If this
    //      flag is true and the fInLiteral flag is false, then we will put
    //      out an extra space at the end.
    //
    //  fURLEntityCaching
    //      Indicates whether the External entity files are to be cached to disk
    //      or not. The default is to cache it.
    //
    // -----------------------------------------------------------------------
    unsigned int                fCharIndex;
    XMLCh                       fCharBuf[kCharBufSize];
    unsigned int                fCharsAvail;
    unsigned char               fCharSizeBuf[kCharBufSize];
    unsigned int                fCurCol;
    unsigned int                fCurLine;
    XMLRecognizer::Encodings    fEncoding;
    XMLCh*                      fEncodingStr;
    bool                        fForcedEncoding;
    bool                        fNoMore;
    XMLCh*                      fPublicId;
    unsigned int                fRawBufIndex;
    XMLByte                     fRawByteBuf[kRawBufSize];
    unsigned int                fRawBytesAvail;
    unsigned int                fReaderNum;
    RefFrom                     fRefFrom;
    bool                        fSentTrailingSpace;
    Sources                     fSource;
    XMLCh                       fSpareCh;
    unsigned int                fSrcOfsBase;
    bool                        fSrcOfsSupported;
    XMLCh*                      fSystemId;
    BinInputStream*             fStream;
    bool                        fSwapped;
    bool                        fThrowAtEnd;
    XMLTranscoder*              fTranscoder;
    Types                       fType;
    bool                        fURLEntityCaching;
    char*                       fDiskCachePath;
    ofstream                    fDiskCacheFile;


    // -----------------------------------------------------------------------
    //  Static data members
    //
    //  fgCharCharsTable
    //      The character characteristics table. Bits in each byte, represent
    //      the characteristics of each character. It is generated via some
    //      code and then hard coded into the cpp file for speed.
    //
    //  fNEL
    //      Flag to respresents whether NEL whitespace recognition is enabled
    //      or disabled
    // -----------------------------------------------------------------------
    static XMLByte  fgCharCharsTable[0x10000];
    static bool     fNEL;

    friend class XMLPlatformUtils;
};


// ---------------------------------------------------------------------------
//  XMLReader: Public, static methods
// ---------------------------------------------------------------------------
inline bool XMLReader::isBaseChar(const XMLCh toCheck)
{
    return ((fgCharCharsTable[toCheck] & gBaseCharMask) != 0);
}

inline bool XMLReader::isNameChar(const XMLCh toCheck)
{
    return ((fgCharCharsTable[toCheck] & gNameCharMask) != 0);
}

inline bool XMLReader::isPlainContentChar(const XMLCh toCheck)
{
    return ((fgCharCharsTable[toCheck] & gPlainContentCharMask) != 0);
}


inline bool XMLReader::isSpecialCharDataChar(const XMLCh toCheck)
{
    return ((fgCharCharsTable[toCheck] & gSpecialCharDataMask) != 0);
}

inline bool XMLReader::isSpecialStartTagChar(const XMLCh toCheck)
{
    return ((fgCharCharsTable[toCheck] & gSpecialStartTagCharMask) != 0);
}

inline bool XMLReader::isXMLChar(const XMLCh toCheck)
{
    return ((fgCharCharsTable[toCheck] & gXMLCharMask) != 0);
}

inline bool XMLReader::isXMLLetter(const XMLCh toCheck)
{
    const XMLByte ourMask = gBaseCharMask | gLetterCharMask;
    return ((fgCharCharsTable[toCheck] & ourMask) != 0);
}

inline bool XMLReader::isWhitespace(const XMLCh toCheck)
{
    return ((fgCharCharsTable[toCheck] & gWhitespaceCharMask) != 0);
}

// ---------------------------------------------------------------------------
//  XMLReader: Buffer management methods
// ---------------------------------------------------------------------------
inline unsigned long XMLReader::charsLeftInBuffer() const
{
    return fCharsAvail - fCharIndex;
}


// ---------------------------------------------------------------------------
//  XMLReader: Getter methods
// ---------------------------------------------------------------------------
inline unsigned int XMLReader::getColumnNumber() const
{
    return fCurCol;
}

inline const XMLCh* XMLReader::getEncodingStr() const
{
    return fEncodingStr;
}

inline unsigned int XMLReader::getLineNumber() const
{
    return fCurLine;
}

inline bool XMLReader::getNoMoreFlag() const
{
    return fNoMore;
}

inline const XMLCh* XMLReader::getPublicId() const
{
    return fPublicId;
}

inline unsigned int XMLReader::getReaderNum() const
{
    return fReaderNum;
}

inline XMLReader::RefFrom XMLReader::getRefFrom() const
{
    return fRefFrom;
}

inline XMLReader::Sources XMLReader::getSource() const
{
    return fSource;
}

inline const XMLCh* XMLReader::getSystemId() const
{
    return fSystemId;
}

inline bool XMLReader::getThrowAtEnd() const
{
    return fThrowAtEnd;
}

inline XMLReader::Types XMLReader::getType() const
{
    return fType;
}

inline bool XMLReader::isNELRecognized() {

    return fNEL;
}

inline bool XMLReader::getURLEntityCaching() const
{
    return fURLEntityCaching;
}

//inline const XMLCh* XMLReader::getdiskCachePath() const
//{
//    return fDiskCachePath;
//}

// ---------------------------------------------------------------------------
//  XMLReader: Setter methods
// ---------------------------------------------------------------------------
inline void XMLReader::setReaderNum(const unsigned int newNum)
{
    fReaderNum = newNum;
}

inline void XMLReader::setThrowAtEnd(const bool newValue)
{
    fThrowAtEnd = newValue;
}



// ---------------------------------------------------------------------------
//
//  XMLReader: movePlainContentChars()
//
//       Move as many plain (no special handling of any sort required) content
//       characters as possible from this reader to the supplied destination buffer.
//
//       This is THE hottest performance spot in the parser.
//
// ---------------------------------------------------------------------------
inline void XMLReader::movePlainContentChars(XMLBuffer &dest)
{
    int count = 0;
    XMLCh *pStart = &fCharBuf[fCharIndex];
    XMLCh *pCurrent = pStart;
    XMLCh *pEnd     = &fCharBuf[fCharsAvail];


    while (pCurrent < pEnd)
    {
        if (! XMLReader::isPlainContentChar(*pCurrent++))
            break;
        count++;
    }

    if (count > 0)
    {
        fCharIndex += count;
        fCurCol    += count;
        dest.append(pStart, count);
    }
}




// ---------------------------------------------------------------------------
//  XMLReader: getNextCharIfNot() method inlined for speed
// ---------------------------------------------------------------------------
inline bool XMLReader::getNextCharIfNot(const XMLCh chNotToGet, XMLCh& chGotten)
{
    //
    //  See if there is at least a char in the buffer. Else, do the buffer
    //  reload logic.
    //
    if (fCharIndex < fCharsAvail)
    {
        // Check the next char
        if (fCharBuf[fCharIndex] == chNotToGet)
            return false;

        // Its not the one we want to skip so bump the index
        chGotten = fCharBuf[fCharIndex++];
    }
     else
    {
        // If fNoMore is set, then we have nothing else to give
        if (fNoMore)
            return false;

        // If the buffer is empty, then try to refresh
        if (fCharIndex == fCharsAvail)
        {
            if (!refreshCharBuffer())
            {
                // If still empty, then return false
                if (fCharIndex == fCharsAvail)
                    return false;
            }
        }

        // Check the next char
        if (fCharBuf[fCharIndex] == chNotToGet)
            return false;

        // Its not the one we want to skip so bump the index
        chGotten = fCharBuf[fCharIndex++];
    }

    // Handle end of line normalization and line/col member maintenance.
    if (chGotten == chCR)
    {
        //
        //  Do the normalization. We return chLF regardless of which was
        //  found. We also eat a chCR followed by an chLF.
        //
        //  We only do this if the content being spooled is not already
        //  internalized.
        //
        if (fSource == Source_External)
        {
            //
            //  See if we have another char left. If not, don't bother.
            //  Else, see if its an chLF to eat. If it is, bump the
            //  index again.
            //
            if (fCharIndex < fCharsAvail)
            {
                if (fCharBuf[fCharIndex] == chLF
                    || ((fCharBuf[fCharIndex] == chNEL) && fNEL))
                    fCharIndex++;
            }
             else
            {
                if (refreshCharBuffer())
                {
                    if (fCharBuf[fCharIndex] == chLF
                        || ((fCharBuf[fCharIndex] == chNEL) && fNEL))
                        fCharIndex++;
                }
            }

            // And return just an chLF
            chGotten = chLF;
        }

        // And handle the line/col stuff
        fCurCol = 1;
        fCurLine++;
    }
     else if (chGotten == chLF
              || ((chGotten == chNEL) && fNEL))
    {
        chGotten = chLF;
        fCurLine++;
        fCurCol = 1;
    }
     else if (chGotten)
    {
        //
        //  Only do this is not a null char. Null chars are not part of the
        //  real content. They are just marker characters inserted into
        //  the stream.
        //
        fCurCol++;
    }
    return true;
}

#endif
