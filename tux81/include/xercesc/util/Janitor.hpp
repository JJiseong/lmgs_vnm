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
 * $Log: Janitor.hpp,v $
 * Revision 1.1  2002/05/11 20:32:22  bhavani
 * CR#CR062582# adding xercesc 1.7 file
 *
 * Revision 1.1.1.1  2002/02/01 22:22:10  peiyongz
 * sane_include
 *
 * Revision 1.7  2000/10/13 22:45:12  andyh
 * Complete removal of ArrayJanitory::operator->().  Was just commented out earlier.
 *
 * Revision 1.6  2000/10/10 23:52:11  andyh
 * From Janitor, remove the addition that is having compile problems in MSVC.
 *
 * Revision 1.5  2000/10/09 18:32:31  jberry
 * Add some auto_ptr functionality to allow modification of monitored
 * pointer value. This eases use of Janitor in some situations.
 *
 * Revision 1.4  2000/03/02 19:54:40  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.3  2000/02/24 20:05:24  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.2  2000/02/06 07:48:02  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.1.1.1  1999/11/09 01:04:27  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:45:08  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */


#if !defined(JANITOR_HPP)
#define JANITOR_HPP

#include <xercesc/util/XercesDefs.hpp>


template <class T> class Janitor
{
public  :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    Janitor(T* const toDelete);
    ~Janitor();

    // -----------------------------------------------------------------------
    //  Public, non-virtual methods
    // -----------------------------------------------------------------------
    void orphan();

	//	small amount of auto_ptr compatibility
	T&	operator*() const;
	T*	operator->() const;
	T*	get() const;
	T*	release();
	void reset(T* p = 0);

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
	Janitor();
    Janitor(const Janitor<T>&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fData
    //      This is the pointer to the object or structure that must be
    //      destroyed when this object is destroyed.
    // -----------------------------------------------------------------------
    T*  fData;
};



template <class T> class ArrayJanitor
{
public  :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    ArrayJanitor(T* const toDelete);
    ~ArrayJanitor();


    // -----------------------------------------------------------------------
    //  Public, non-virtual methods
    // -----------------------------------------------------------------------
    void orphan();

	//	small amount of auto_ptr compatibility
	T&	operator[](int index) const;
	T*	get() const;
	T*	release();
	void reset(T* p = 0);

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
	ArrayJanitor();
    ArrayJanitor(const ArrayJanitor<T>& copy);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fData
    //      This is the pointer to the object or structure that must be
    //      destroyed when this object is destroyed.
    // -----------------------------------------------------------------------
    T*  fData;
};


#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/Janitor.c>
#endif

#endif
