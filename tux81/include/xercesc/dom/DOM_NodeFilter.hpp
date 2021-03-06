/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 1999-2002 The Apache Software Foundation.  All rights
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
 * $Log: DOM_NodeFilter.hpp,v $
 * Revision 1.1  2002/05/11 19:50:56  bhavani
 * CR#CR062582# adding xercesc 1.7 file
 *
 * Revision 1.2  2002/02/04 19:57:15  tng
 * Remove the phrase "Experimental".
 *
 * Revision 1.1.1.1  2002/02/01 22:21:46  peiyongz
 * sane_include
 *
 * Revision 1.10  2000/10/20 22:03:04  andyh
 * DOM NodeFileter - define values for FilterAction enum to match those in the DOM spec.
 *
 * Revision 1.9  2000/05/11 00:07:38  abagchi
 * Removed tables. It was confusing doxygen
 *
 * Revision 1.8  2000/03/11 03:19:13  chchou
 * Fix bug # 19, add const keyword to API
 *
 * Revision 1.7  2000/02/24 20:11:28  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.6  2000/02/17 17:47:25  andyh
 * Update Doc++ API comments
 * NameSpace update to track W3C
 * Changes were made by Chih Hsiang Chou
 *
 * Revision 1.5  2000/02/15 23:17:37  andyh
 * Update Doc++ API comments
 * NameSpace bugfix and update to track W3C
 * Chih Hsiang Chou
 *
 * Revision 1.4  2000/02/10 21:47:12  abagchi
 * Added API docs
 *
 * Revision 1.3  2000/02/06 07:47:30  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.2  2000/02/04 01:49:28  aruna1
 * TreeWalker and NodeIterator changes
 *
 * Revision 1.1.1.1  1999/11/09 01:09:00  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:44:19  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */

// DOM_NodeFilter.h: interface for the DOM_NodeFilter class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DOM_NodeFilter_HEADER_GUARD_
#define DOM_NodeFilter_HEADER_GUARD_

#include "DOM_Node.hpp"

class NodeFilterImpl;


/**
 * Filters are objects that know how to "filter out" nodes. If a
 * <code>DOM_NodeIterator</code> or <code>DOM_TreeWalker</code> is given a
 * filter, it applies the filter before it returns the next node.
 *
 * If the filter says to accept the node, the iterator returns it; otherwise, the
 * iterator looks for the next node and pretends that the node that was rejected
 * was not there.
 *
 *  The DOM does not provide any filters. Filter is just an interface that users can
 *  implement to provide their own filters.
 *
 *  Filters do not need to know how to iterate, nor do they need to know anything
 *  about the data structure that is being iterated. This makes it very easy to write
 *  filters, since the only thing they have to know how to do is evaluate a single node.
 *  One filter may be used with a number of different kinds of iterators, encouraging
 *  code reuse.
 *
 */
class CDOM_EXPORT DOM_NodeFilter
{
    public:
	/** @name Enumerators for Node Filter */
        //@{
	/*
	  *		<table><tr><td>FILTER_ACCEPT</td>
      *            <td>Accept the node. Navigation methods defined for
      *                NodeIterator or TreeWalker will return this node.</td>
	  *			</tr>
	  *			<tr><td>
      *               FILTER_REJECT</td>
      *               <td>Reject the node. Navigation methods defined for
      *               NodeIterator or TreeWalker will not return this
      *               node. For TreeWalker, the children of this node will
      *               also be rejected. Iterators treat this as a synonym
      *               for FILTER_SKIP.</td>
	  *			</tr>
	  *			<tr><td>FILTER_SKIP</td>
      *              <td>Reject the node. Navigation methods defined for
      *                  NodeIterator or TreeWalker will not return this
      *                  node. For both NodeIterator and Treewalker, the
      *                  children of this node will still be considered.</td>
 	  *			</tr>
	  *		</table>
      *
	  */
        enum FilterAction {FILTER_ACCEPT = 1,
                           FILTER_REJECT = 2,
                           FILTER_SKIP   = 3};

        enum ShowType {
            SHOW_ALL                       = 0x0000FFFF,
            SHOW_ELEMENT                   = 0x00000001,
            SHOW_ATTRIBUTE                 = 0x00000002,
            SHOW_TEXT                      = 0x00000004,
            SHOW_CDATA_SECTION             = 0x00000008,
            SHOW_ENTITY_REFERENCE          = 0x00000010,
            SHOW_ENTITY                    = 0x00000020,
            SHOW_PROCESSING_INSTRUCTION    = 0x00000040,
            SHOW_COMMENT                   = 0x00000080,
            SHOW_DOCUMENT                  = 0x00000100,
            SHOW_DOCUMENT_TYPE             = 0x00000200,
            SHOW_DOCUMENT_FRAGMENT         = 0x00000400,
            SHOW_NOTATION                  = 0x00000800
        };
	//@}

        /** @name Constructors */
        //@{
        /**
          * Default constructor for DOM_NodeFilter.
          */
        DOM_NodeFilter();
        //@}

        /** @name Destructor. */
        //@{
	/**
	  * Destructor for DOM_NodeFilter.
	  */
        virtual ~DOM_NodeFilter();
        //@}

        /** @name Test function. */
        //@{
	/**
	  * Test whether a specified node is visible in the logical view of a DOM_TreeWalker
	  * or DOM_NodeIterator. This function will be called by the implementation of
	  * DOM_TreeWalker and DOM_NodeIterator; it is not intended to be called directly from user
	  * code.
          *
          * @param node The node to check to see if it passes the filter or not.
          * @return A constant to determine whether the node is accepted, rejected, or skipped.
	  */
        virtual short acceptNode (const DOM_Node &node) const =0;
        //@}

    private:
        DOM_NodeFilter(const DOM_NodeFilter &other);
        DOM_NodeFilter & operator = (const DOM_NodeFilter &other);
        bool operator == (const DOM_NodeFilter &other) const;
        bool operator != (const DOM_NodeFilter &other) const;
};

#endif
