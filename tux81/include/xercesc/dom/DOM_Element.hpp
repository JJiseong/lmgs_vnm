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
 * $Log: DOM_Element.hpp,v $
 * Revision 1.1  2002/05/11 19:49:30  bhavani
 * CR#CR062582# adding xercesc 1.7 file
 *
 * Revision 1.3  2002/02/20 18:17:00  tng
 * [Bug 5977] Warnings on generating apiDocs.
 *
 * Revision 1.2  2002/02/04 20:03:48  tng
 * Add DOM Level missing functions:
 * 1. NodeIterator::getRoot
 * 2. TreeWalker::getRoot
 * 3. Element::hasAttribute
 * 4. Element::hasAttributeNS
 * 5. Node::hasAttributes
 * 6. Node::isSupported
 *
 * Revision 1.1.1.1  2002/02/01 22:21:45  peiyongz
 * sane_include
 *
 * Revision 1.9  2001/05/11 13:25:20  tng
 * Copyright update.
 *
 * Revision 1.8  2001/05/03 19:17:26  knoaman
 * TraverseSchema Part II.
 *
 * Revision 1.7  2000/03/02 19:53:55  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.6  2000/02/24 20:11:27  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.5  2000/02/17 17:47:24  andyh
 * Update Doc++ API comments
 * NameSpace update to track W3C
 * Changes were made by Chih Hsiang Chou
 *
 * Revision 1.4  2000/02/06 07:47:29  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.3  2000/01/05 01:16:07  andyh
 * DOM Level 2 core, namespace support added.
 *
 * Revision 1.2  1999/12/21 07:47:06  robweir
 * Patches to support Xalan, where we need to create a
 * "special" DOM with subclassed Nodes.
 *
 * 1. Export the NodeImpl-derived classes
 * 2. Ensure that their constructors have at least protected access
 *
 * Revision 1.1.1.1  1999/11/09 01:08:57  twl
 * Initial checkin
 *
 * Revision 1.3  1999/11/08 20:44:17  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */

#ifndef DOM_Element_HEADER_GUARD_
#define DOM_Element_HEADER_GUARD_

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOM_Node.hpp>

class DOM_Attr;
class DOM_NodeList;
class ElementImpl;

/**
 * By far the vast majority of objects (apart from text) that authors
 * encounter when traversing a document are <code>DOM_Element</code> nodes.
 *
 * Assume the following XML document:&lt;elementExample id="demo"&gt;
 * &lt;subelement1/&gt;
 * &lt;subelement2&gt;&lt;subsubelement/&gt;&lt;/subelement2&gt;
 * &lt;/elementExample&gt;
 * <p>When represented using DOM, the top node is an <code>DOM_Element</code> node
 * for "elementExample", which contains two child <code>DOM_Element</code> nodes,
 * one for "subelement1" and one for "subelement2". "subelement1" contains no
 * child nodes.
 * <p>Elements may have attributes associated with them; since the
 * <code>DOM_Element</code> interface inherits from <code>DOM_Node</code>, the generic
 *  <code>DOM_Node</code> interface method <code>getAttributes</code> may be used
 * to retrieve the set of all attributes for an element.  There are methods on
 *  the <code>DOM_Element</code> interface to retrieve either an <code>DOM_Attr</code>
 *  object by name or an attribute value by name. In XML, where an attribute
 * value may contain entity references, an <code>DOM_Attr</code> object should be
 * retrieved to examine the possibly fairly complex sub-tree representing the
 * attribute value. On the other hand, in HTML, where all attributes have
 * simple string values, methods to directly access an attribute value can
 * safely be used as a convenience.
 */

class CDOM_EXPORT DOM_Element: public DOM_Node {
private:

public:
    /** @name Constructors and assignment operator */
    //@{
    /**
    * Default constructor for DOM_Element.  The resulting object does not
    * refer to an actual Element node; it will compare == to 0, and is similar
    * to a null object reference variable in Java.  It may subsequently be
    * assigned to refer to an actual Element node.
    * <p>
    * New comment nodes are created by DOM_Document::createElement().
      *
      */
    DOM_Element();

    /**
      * Copy constructor.  Creates a new <code>DOM_Element</code> that refers to the
      * same underlying actual element as the original.
      *
      * @param other The object to be copied
      */
    DOM_Element(const DOM_Element &other);

    /**
      * Assignment operator.
      *
      * @param other The object to be copied.
      */
    DOM_Element & operator = (const DOM_Element &other);

    /**
      * Assignment operator.  This overloaded variant is provided for
      *   the sole purpose of setting a DOM_Node reference variable to
      *   zero.  Nulling out a reference variable in this way will decrement
      *   the reference count on the underlying Node object that the variable
      *   formerly referenced.  This effect is normally obtained when reference
      *   variable goes out of scope, but zeroing them can be useful for
      *   global instances, or for local instances that will remain in scope
      *   for an extended time,  when the storage belonging to the underlying
      *   node needs to be reclaimed.
      *
      * @param val   Only a value of 0, or null, is allowed.
      */
    DOM_Element & operator = (const DOM_NullPtr *val);

    //@}
    /** @name Destructor. */
    //@{
	 /**
      * Destructor.  The object being destroyed is the reference
      * object, not the underlying Element itself.
	  *
	  */
    ~DOM_Element();
    //@}
    /** @name Getter functions. */
    //@{

  /**
   * The name of the element.
   *
   * For example, in: &lt;elementExample
   * id="demo"&gt;  ... &lt;/elementExample&gt; , <code>tagName</code> has
   * the value <code>"elementExample"</code>. Note that this is
   * case-preserving in XML, as are all of the operations of the DOM.
   */
  DOMString         getTagName() const;

  /**
   * Retrieves an attribute value by name.
   *
   * @param name The name of the attribute to retrieve.
   * @return The <code>DOM_Attr</code> value as a string, or the empty  string if
   *   that attribute does not have a specified or default value.
   */
  DOMString         getAttribute(const DOMString &name) const;

  /**
   * Retrieves an <code>DOM_Attr</code> node by name.
   *
   * @param name The name (<CODE>nodeName</CODE>) of the attribute to retrieve.
   * @return The <code>DOM_Attr</code> node with the specified name (<CODE>nodeName</CODE>) or
   *   <code>null</code> if there is no such attribute.
   */
  DOM_Attr        getAttributeNode(const DOMString &name) const;

  /**
   * Returns a <code>NodeList</code> of all descendant elements with a given
   * tag name, in the order in which they would be encountered in a preorder
   * traversal of the <code>DOM_Element</code> tree.
   *
   * @param name The name of the tag to match on. The special value "*"
   *   matches all tags.
   * @return A list of matching <code>DOM_Element</code> nodes.
   */
  DOM_NodeList    getElementsByTagName(const DOMString &name) const;

  //@}
  /** @name Set functions. */
  //@{

  /**
   * Adds a new attribute.
   *
   * If an attribute with that name is already present
   * in the element, its value is changed to be that of the value parameter.
   * This value is a simple string, it is not parsed as it is being set. So
   * any markup (such as syntax to be recognized as an entity reference) is
   * treated as literal text, and needs to be appropriately escaped by the
   * implementation when it is written out. In order to assign an attribute
   * value that contains entity references, the user must create an
   * <code>DOM_Attr</code> node plus any <code>Text</code> and
   * <code>EntityReference</code> nodes, build the appropriate subtree, and
   * use <code>setAttributeNode</code> to assign it as the value of an
   * attribute.
   * @param name The name of the attribute to create or alter.
   * @param value Value to set in string form.
   * @exception DOMException
   *   INVALID_CHARACTER_ERR: Raised if the specified name contains an
   *   illegal character.
   *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
   */
   void             setAttribute(const DOMString &name,
                                 const DOMString &value);
   /**
    * Adds a new attribute.
    *
    * If an attribute with that name (<CODE>nodeName</CODE>) is already present
    * in the element, it is replaced by the new one.
    * @param newAttr The <code>DOM_Attr</code> node to add to the attribute list.
    * @return If the <code>newAttr</code> attribute replaces an existing
    *   attribute, the replaced
    *   <code>DOM_Attr</code> node is returned, otherwise <code>null</code> is
    *   returned.
    * @exception DOMException
    *   WRONG_DOCUMENT_ERR: Raised if <code>newAttr</code> was created from a
    *   different document than the one that created the element.
    *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
    *   <br>INUSE_ATTRIBUTE_ERR: Raised if <code>newAttr</code> is already an
    *   attribute of another <code>DOM_Element</code> object. The DOM user must
    *   explicitly clone <code>DOM_Attr</code> nodes to re-use them in other
    *   elements.
    */
   DOM_Attr        setAttributeNode(DOM_Attr newAttr);

   //@}
   /** @name Functions which modify the Element. */
   //@{
  /**
   * Removes the specified attribute node.
   * If the removed <CODE>DOM_Attr</CODE>
   *   has a default value it is immediately replaced. The replacing attribute
   *   has the same namespace URI and local name, as well as the original prefix,
   *   when applicable.
   *
   * @param oldAttr The <code>DOM_Attr</code> node to remove from the attribute
   *   list.
   * @return The <code>DOM_Attr</code> node that was removed.
   * @exception DOMException
   *   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
   *   <br>NOT_FOUND_ERR: Raised if <code>oldAttr</code> is not an attribute
   *   of the element.
   */
  DOM_Attr        removeAttributeNode(DOM_Attr oldAttr);

  /**
   * Removes an attribute by name.
   *
   * If the removed attribute
   *   is known to have a default value, an attribute immediately appears
   *   containing the default value as well as the corresponding namespace URI,
   *   local name, and prefix when applicable.<BR>To remove an attribute by local
   *   name and namespace URI, use the <CODE>removeAttributeNS</CODE> method.
   * @param name The name of the attribute to remove.
   * @exception DOMException
   *   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
   */
  void              removeAttribute(const DOMString &name);

  //@}
  /** @name Functions introduced in DOM Level 2. */
  //@{

  /**
   * Retrieves an attribute value by local name and namespace URI.
   *
   * @param namespaceURI The <em>namespace URI</em> of
   *    the attribute to retrieve.
   * @param localName The <em>local name</em> of the
   *    attribute to retrieve.
   * @return The <code>DOM_Attr</code> value as a string, or an <CODE>null</CODE> if
   *    that attribute does not have a specified or default value.
   */
  DOMString         getAttributeNS(const DOMString &namespaceURI,
	const DOMString &localName) const;

  /**
   * Adds a new attribute. If an attribute with the same
   * local name and namespace URI is already present on the element, its prefix
   * is changed to be the prefix part of the <CODE>qualifiedName</CODE>, and
   * its value is changed to be the <CODE>value</CODE> parameter. This value is
   * a simple string, it is not parsed as it is being set. So any markup (such
   * as syntax to be recognized as an entity reference) is treated as literal
   * text, and needs to be appropriately escaped by the implementation when it
   * is written out. In order to assign an attribute value that contains entity
   * references, the user must create an <CODE>DOM_Attr</CODE>
   * node plus any <CODE>DOM_Text</CODE> and <CODE>DOM_EntityReference</CODE>
   * nodes, build the appropriate subtree, and use
   * <CODE>setAttributeNodeNS</CODE> or <CODE>setAttributeNode</CODE> to assign
   * it as the value of an attribute.
   *
   * @param namespaceURI The <em>namespace URI</em> of
   *    the attribute to create or alter.
   * @param qualifiedName The <em>qualified name</em> of the
   *    attribute to create or alter.
   * @param value The value to set in string form.
   * @exception DOMException
   *   INVALID_CHARACTER_ERR: Raised if the specified qualified name contains an
   *   illegal character.
   *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
   * <br>
   *   NAMESPACE_ERR: Raised if the <CODE>qualifiedName</CODE> is
   *        malformed, if the <CODE>qualifiedName</CODE> has a prefix and the
   *        <CODE>namespaceURI</CODE> is <CODE>null</CODE> or an empty string,
   *        if the <CODE>qualifiedName</CODE> has a prefix that is "xml" and the
   *        <CODE>namespaceURI</CODE> is different from
   *        "http://www.w3.org/XML/1998/namespace", if the
   *        <CODE>qualifiedName</CODE> has a prefix that is "xmlns" and the
   *        <CODE>namespaceURI</CODE> is different from
   *        "http://www.w3.org/2000/xmlns/", or if the
   *        <CODE>qualifiedName</CODE> is "xmlns" and the
   *        <CODE>namespaceURI</CODE> is different from
   *        "http://www.w3.org/2000/xmlns/".
   */
   void             setAttributeNS(const DOMString &namespaceURI,
	const DOMString &qualifiedName, const DOMString &value);

  /**
   * Removes an attribute by local name and namespace URI. If the
   * removed attribute has a default value it is immediately replaced.
   * The replacing attribute has the same namespace URI and local name, as well as
   * the original prefix.
   *
   * @param namespaceURI The <em>namespace URI</em> of
   *    the attribute to remove.
   * @param localName The <em>local name</em> of the
   *    attribute to remove.
   * @exception DOMException
   *   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
   */
  void              removeAttributeNS(const DOMString &namespaceURI,
	const DOMString &localName);

  /**
   * Retrieves an <code>DOM_Attr</code> node by local name and namespace URI.
   *
   * @param namespaceURI The <em>namespace URI</em> of
   *    the attribute to retrieve.
   * @param localName The <em>local name</em> of the
   *    attribute to retrieve.
   * @return The <code>DOM_Attr</code> node with the specified attribute local
   *    name and namespace URI or <code>null</code> if there is no such attribute.
   */
  DOM_Attr        getAttributeNodeNS(const DOMString &namespaceURI,
	const DOMString &localName) const;

   /**
    * Adds a new attribute.
    *
    * If an attribute with that local name and namespace URI is already present
    * in the element, it is replaced by the new one.
    *
    * @param newAttr The <code>DOM_Attr</code> node to add to the attribute list.
    * @return If the <code>newAttr</code> attribute replaces an existing
    *    attribute with the same <em>local name</em> and <em>namespace URI</em>,
    *    the replaced <code>DOM_Attr</code> node is
    *    returned, otherwise <code>null</code> is returned.
    * @exception DOMException
    *   WRONG_DOCUMENT_ERR: Raised if <code>newAttr</code> was created from a
    *   different document than the one that created the element.
    *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
    *   <br>INUSE_ATTRIBUTE_ERR: Raised if <code>newAttr</code> is already an
    *   attribute of another <code>DOM_Element</code> object. The DOM user must
    *   explicitly clone <code>DOM_Attr</code> nodes to re-use them in other
    *   elements.
    */
   DOM_Attr        setAttributeNodeNS(DOM_Attr newAttr);

  /**
   * Returns a <code>DOM_NodeList</code> of all the <code>DOM_Element</code>s
   * with a given local name and namespace URI in the order in which they
   * would be encountered in a preorder traversal of the
   * <code>DOM_Document</code> tree, starting from this node.
   *
   * @param namespaceURI The <em>namespace URI</em> of
   *    the elements to match on. The special value "*" matches all
   *    namespaces.
   * @param localName The <em>local name</em> of the
   *    elements to match on. The special value "*" matches all local names.
   * @return A new <code>DOM_NodeList</code> object containing all the matched
   *    <code>DOM_Element</code>s.
   */
  DOM_NodeList    getElementsByTagNameNS(const DOMString &namespaceURI,
	const DOMString &localName) const;

    /**
     *  Returns whether this node (if it is an element) has any attributes.
     * @return <code>true</code> if this node has any attributes,
     *   <code>false</code> otherwise.
     */
    bool         hasAttributes() const;

    /**
     * Returns <code>true</code> when an attribute with a given name is
     * specified on this element or has a default value, <code>false</code>
     * otherwise.
     * @param name The name of the attribute to look for.
     * @return <code>true</code> if an attribute with the given name is
     *   specified on this element or has a default value, <code>false</code>
     *    otherwise.
     */
    bool         hasAttribute(const DOMString &name) const;

    /**
     * Returns <code>true</code> when an attribute with a given local name and
     * namespace URI is specified on this element or has a default value,
     * <code>false</code> otherwise. HTML-only DOM implementations do not
     * need to implement this method.
     * @param namespaceURI The namespace URI of the attribute to look for.
     * @param localName The local name of the attribute to look for.
     * @return <code>true</code> if an attribute with the given local name
     *   and namespace URI is specified or has a default value on this
     *   element, <code>false</code> otherwise.
     * @since DOM Level 2
     */
    bool         hasAttributeNS(const DOMString &namespaceURI,
                                const DOMString &localName) const;

  //@}

  protected:
     DOM_Element(ElementImpl *impl);

     friend class DOM_Document;
     friend class DOM_Attr;
     friend class TraverseSchema;
};

#endif


