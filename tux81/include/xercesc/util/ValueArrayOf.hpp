/*
 * The Apache Software License, Version 1.1
 * 
 * Copyright (c) 1999-2000 The Apache Software Foundation.  All rights
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
 * $Log: ValueArrayOf.hpp,v $
 * Revision 1.1  2002/05/11 21:15:25  bhavani
 * CR#CR062582# adding xercesc 1.7 file
 *
 * Revision 1.1.1.1  2002/02/01 22:22:13  peiyongz
 * sane_include
 *
 * Revision 1.4  2000/03/02 19:54:47  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.3  2000/02/24 20:05:26  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.2  2000/02/06 07:48:05  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.1.1.1  1999/11/09 01:05:27  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:45:18  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */


#if !defined(VALUEARRAY_HPP)
#define VALUEARRAY_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLEnumerator.hpp>
#include <xercesc/util/ArrayIndexOutOfBoundsException.hpp>
#include <xercesc/util/IllegalArgumentException.hpp>

template <class TElem> class ValueArrayOf
{
public :
    // -----------------------------------------------------------------------
    //  Contructors and Destructor
    // -----------------------------------------------------------------------
    ValueArrayOf(const unsigned int size);
	ValueArrayOf(const TElem* values, const unsigned int size);
	ValueArrayOf(const ValueArrayOf<TElem>& source);
	~ValueArrayOf();


    // -----------------------------------------------------------------------
    //  Public operators
    // -----------------------------------------------------------------------
	TElem& operator[](const unsigned int index);
	const TElem& operator[](const unsigned int index) const;
	ValueArrayOf<TElem>& operator=(const ValueArrayOf<TElem>& toAssign);
	bool operator==(const ValueArrayOf<TElem>& toCompare) const;
	bool operator!=(const ValueArrayOf<TElem>& toCompare) const;


    // -----------------------------------------------------------------------
    //  Copy operations
    // -----------------------------------------------------------------------
    unsigned int copyFrom(const ValueArrayOf<TElem>& srcArray);


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
	unsigned int length() const;
	TElem* rawData() const;


    // -----------------------------------------------------------------------
    //  Miscellaneous methods
    // -----------------------------------------------------------------------
    void resize(const unsigned int newSize);


private :
    // -----------------------------------------------------------------------
    //  Data members
    // -----------------------------------------------------------------------
	unsigned int    fSize;
	TElem*          fArray;
};


//
//  An enumerator for a value array. It derives from the basic enumerator
//  class, so that value vectors can be generically enumerated.
//
template <class TElem> class ValueArrayEnumerator : public XMLEnumerator<TElem>
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    ValueArrayEnumerator
    (
                ValueArrayOf<TElem>* const toEnum
        , const bool                       adopt = false
    );
    ~ValueArrayEnumerator();


    // -----------------------------------------------------------------------
    //  Enum interface
    // -----------------------------------------------------------------------
    bool hasMoreElements() const;
    TElem& nextElement();
    void Reset();


private :    
    // -----------------------------------------------------------------------
    //  Data Members
    //
    //  fAdopted
    //      Indicates whether we have adopted the passed vector. If so then
    //      we delete the vector when we are destroyed.
    //
    //  fCurIndex
    //      This is the current index into the vector.
    //
    //  fToEnum
    //      The value array being enumerated.
    // -----------------------------------------------------------------------
    bool                    fAdopted;
    unsigned int            fCurIndex;
    ValueArrayOf<TElem>*    fToEnum;
};


#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/ValueArrayOf.c>
#endif

#endif
