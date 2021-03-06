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

/**
 * $Log: ValueVectorOf.c,v $
 * Revision 1.1  2002/05/11 21:15:46  bhavani
 * CR#CR062582# adding xercesc 1.7 file
 *
 * Revision 1.1.1.1  2002/02/01 22:22:13  peiyongz
 * sane_include
 *
 * Revision 1.5  2002/01/10 17:44:49  knoaman
 * Fix for bug 5786.
 *
 * Revision 1.4  2001/08/09 15:24:37  knoaman
 * add support for <anyAttribute> declaration.
 *
 * Revision 1.3  2000/03/02 19:54:47  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.2  2000/02/06 07:48:05  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.1.1.1  1999/11/09 01:05:31  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:45:18  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include <xercesc/util/ValueVectorOf.hpp>
#endif



// ---------------------------------------------------------------------------
//  ValueVectorOf: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TElem> ValueVectorOf<TElem>::
ValueVectorOf(const unsigned int maxElems) :

    fCurCount(0)
    , fMaxCount(maxElems)
    , fElemList(0)
{
    fElemList = new TElem[fMaxCount];
}

template <class TElem> ValueVectorOf<TElem>::
ValueVectorOf(const ValueVectorOf<TElem>& toCopy) :

    fCurCount(toCopy.fCurCount)
    , fMaxCount(toCopy.fMaxCount)
    , fElemList(0)
{
    fElemList = new TElem[fMaxCount];
    for (unsigned int index = 0; index < fCurCount; index++)
        fElemList[index] = toCopy.fElemList[index];
}

template <class TElem> ValueVectorOf<TElem>::~ValueVectorOf()
{
    delete [] fElemList;
}



// ---------------------------------------------------------------------------
//  ValueVectorOf: Operators
// ---------------------------------------------------------------------------
template <class TElem> ValueVectorOf<TElem>&
ValueVectorOf<TElem>::operator=(const ValueVectorOf<TElem>& toAssign)
{
    if (this == &toAssign)
        return *this;

    // Reallocate if required
    if (fMaxCount < toAssign.fCurCount)
    {
        delete [] fElemList;
        fElemList = new TElem[toAssign.fMaxCount];
        fMaxCount = toAssign.fMaxCount;
    }

    fCurCount = toAssign.fCurCount;
    for (unsigned int index = 0; index < fCurCount; index++)
        fElemList[index] = toAssign.fElemList[index];

    return *this;
}


// ---------------------------------------------------------------------------
//  ValueVectorOf: Element management
// ---------------------------------------------------------------------------
template <class TElem> void ValueVectorOf<TElem>::addElement(const TElem& toAdd)
{
    ensureExtraCapacity(1);
    fElemList[fCurCount] = toAdd;
    fCurCount++;
}

template <class TElem> void ValueVectorOf<TElem>::
setElementAt(const TElem& toSet, const unsigned int setAt)
{
    if (setAt >= fCurCount)
        ThrowXML(ArrayIndexOutOfBoundsException, XMLExcepts::Vector_BadIndex);
    fElemList[setAt] = toSet;
}

template <class TElem> void ValueVectorOf<TElem>::
insertElementAt(const TElem& toInsert, const unsigned int insertAt)
{
    if (insertAt == fCurCount)
    {
        addElement(toInsert);
        return;
    }

    if (insertAt > fCurCount)
        ThrowXML(ArrayIndexOutOfBoundsException, XMLExcepts::Vector_BadIndex);

    // Make room for the newbie
    for (unsigned int index = fCurCount; index > insertAt; index--)
        fElemList[index] = fElemList[index-1];

    // And stick it in and bump the count
    fElemList[insertAt] = toInsert;
    fCurCount++;
}

template <class TElem> void ValueVectorOf<TElem>::
removeElementAt(const unsigned int removeAt)
{
    if (removeAt >= fCurCount)
        ThrowXML(ArrayIndexOutOfBoundsException, XMLExcepts::Vector_BadIndex);

    if (removeAt == fCurCount-1)
    {
        fCurCount--;
        return;
    }

    // Copy down every element above remove point
    for (unsigned int index = removeAt; index < fCurCount-1; index++)
        fElemList[index] = fElemList[index+1];

    // And bump down count
    fCurCount--;
}

template <class TElem> void ValueVectorOf<TElem>::removeAllElements()
{
    fCurCount = 0;
}

template <class TElem> 
bool ValueVectorOf<TElem>::containsElement(const TElem& toCheck,
                                           const unsigned int startIndex) {

    for (unsigned int i = startIndex; i < fCurCount; i++) {
        if (fElemList[i] == toCheck) {
            return true;
        }
    }

    return false;
}


// ---------------------------------------------------------------------------
//  ValueVectorOf: Getter methods
// ---------------------------------------------------------------------------
template <class TElem> const TElem& ValueVectorOf<TElem>::
elementAt(const unsigned int getAt) const
{
    if (getAt >= fCurCount)
        ThrowXML(ArrayIndexOutOfBoundsException, XMLExcepts::Vector_BadIndex);
    return fElemList[getAt];
}

template <class TElem> TElem& ValueVectorOf<TElem>::
elementAt(const unsigned int getAt)
{
    if (getAt >= fCurCount)
        ThrowXML(ArrayIndexOutOfBoundsException, XMLExcepts::Vector_BadIndex);
    return fElemList[getAt];
}

template <class TElem> unsigned int ValueVectorOf<TElem>::curCapacity() const
{
    return fMaxCount;
}

template <class TElem> unsigned int ValueVectorOf<TElem>::size() const
{
    return fCurCount;
}



// ---------------------------------------------------------------------------
//  ValueVectorOf: Miscellaneous
// ---------------------------------------------------------------------------
template <class TElem> void ValueVectorOf<TElem>::
ensureExtraCapacity(const unsigned int length)
{
    unsigned int newMax = fCurCount + length;

    if (newMax < fMaxCount)
        return;

    // Avoid too many reallocations by expanding by a percentage
    unsigned int minNewMax = (unsigned int)((double)fCurCount * 1.25);
    if (newMax < minNewMax)
        newMax = minNewMax;

    TElem* newList = new TElem[newMax];
    for (unsigned int index = 0; index < fCurCount; index++)
        newList[index] = fElemList[index];

    delete [] fElemList;
    fElemList = newList;
    fMaxCount = newMax;
}

template <class TElem> const TElem* ValueVectorOf<TElem>::rawData() const
{
    return fElemList;
}



// ---------------------------------------------------------------------------
//  ValueVectorEnumerator: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TElem> ValueVectorEnumerator<TElem>::
ValueVectorEnumerator(       ValueVectorOf<TElem>* const toEnum
                     , const bool                        adopt) :
    fAdopted(adopt)
    , fCurIndex(0)
    , fToEnum(toEnum)
{
}

template <class TElem> ValueVectorEnumerator<TElem>::~ValueVectorEnumerator()
{
    if (fAdopted)
        delete fToEnum;
}


// ---------------------------------------------------------------------------
//  ValueVectorEnumerator: Enum interface
// ---------------------------------------------------------------------------
template <class TElem> bool
ValueVectorEnumerator<TElem>::hasMoreElements() const
{
    if (fCurIndex >= fToEnum->size())
        return false;
    return true;
}

template <class TElem> TElem& ValueVectorEnumerator<TElem>::nextElement()
{
    return fToEnum->elementAt(fCurIndex++);
}

template <class TElem> void ValueVectorEnumerator<TElem>::Reset()
{
    fCurIndex = 0;
}
