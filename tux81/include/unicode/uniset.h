/*
**********************************************************************
* Copyright (C) 1999, International Business Machines Corporation and others. All Rights Reserved.
**********************************************************************
*   Date        Name        Description
*   10/20/99    alan        Creation.
**********************************************************************
*/

#ifndef UNICODESET_H
#define UNICODESET_H

#include "unicode/unifilt.h"
#include "unicode/utypes.h"
#include "unicode/unistr.h"

U_NAMESPACE_BEGIN

class ParsePosition;
class SymbolTable;
class TransliterationRuleParser;
class TransliterationRule;
class Transliterator;
class TransliteratorParser;

/**
 * A mutable set of Unicode characters.  Objects of this class
 * represent <em>character classes</em> used in regular expressions.
 * A character specifies a subset of Unicode code points.  Legal
 * code points are U+0000 to U+10FFFF, inclusive.
 *
 * <p><code>UnicodeSet</code> supports two APIs. The first is the
 * <em>operand</em> API that allows the caller to modify the value of
 * a <code>UnicodeSet</code> object. It conforms to Java 2's
 * <code>java.util.Set</code> interface, although
 * <code>UnicodeSet</code> does not actually implement that
 * interface. All methods of <code>Set</code> are supported, with the
 * modification that they take a character range or single character
 * instead of an <code>Object</code>, and they take a
 * <code>UnicodeSet</code> instead of a <code>Collection</code>.  The
 * operand API may be thought of in terms of boolean logic: a boolean
 * OR is implemented by <code>add</code>, a boolean AND is implemented
 * by <code>retain</code>, a boolean XOR is implemented by
 * <code>complement</code> taking an argument, and a boolean NOT is
 * implemented by <code>complement</code> with no argument.  In terms
 * of traditional set theory function names, <code>add</code> is a
 * union, <code>retain</code> is an intersection, <code>remove</code>
 * is an asymmetric difference, and <code>complement</code> with no
 * argument is a set complement with respect to the superset range
 * <code>MIN_VALUE-MAX_VALUE</code>
 *
 * <p>The second API is the
 * <code>applyPattern()</code>/<code>toPattern()</code> API from the
 * <code>java.text.Format</code>-derived classes.  Unlike the
 * methods that add characters, add categories, and control the logic
 * of the set, the method <code>applyPattern()</code> sets all
 * attributes of a <code>UnicodeSet</code> at once, based on a
 * string pattern.
 *
 * <p><b>Pattern syntax</b></p>
 *
 * Patterns are accepted by the constructors and the
 * <code>applyPattern()</code> methods and returned by the
 * <code>toPattern()</code> method.  These patterns follow a syntax
 * similar to that employed by version 8 regular expression character
 * classes:
 *
 * <blockquote>
 *   <table>
 *     <tr align="top">
 *       <td nowrap valign="top" align="right"><code>pattern :=&nbsp; </code></td>
 *       <td valign="top"><code>('[' '^'? item* ']') |
 *       property</code></td>
 *     </tr>
 *     <tr align="top">
 *       <td nowrap valign="top" align="right"><code>item :=&nbsp; </code></td>
 *       <td valign="top"><code>char | (char '-' char) | pattern-expr<br>
 *       </code></td>
 *     </tr>
 *     <tr align="top">
 *       <td nowrap valign="top" align="right"><code>pattern-expr :=&nbsp; </code></td>
 *       <td valign="top"><code>pattern | pattern-expr pattern |
 *       pattern-expr op pattern<br>
 *       </code></td>
 *     </tr>
 *     <tr align="top">
 *       <td nowrap valign="top" align="right"><code>op :=&nbsp; </code></td>
 *       <td valign="top"><code>'&amp;' | '-'<br>
 *       </code></td>
 *     </tr>
 *     <tr align="top">
 *       <td nowrap valign="top" align="right"><code>special :=&nbsp; </code></td>
 *       <td valign="top"><code>'[' | ']' | '-'<br>
 *       </code></td>
 *     </tr>
 *     <tr align="top">
 *       <td nowrap valign="top" align="right"><code>char :=&nbsp; </code></td>
 *       <td valign="top"><em>any character that is not</em><code> special<br>
 *       | ('\u005C' </code><em>any character</em><code>)<br>
 *       | ('\u005Cu' hex hex hex hex)<br>
 *       </code></td>
 *     </tr>
 *     <tr align="top">
 *       <td nowrap valign="top" align="right"><code>hex :=&nbsp; </code></td>
 *       <td valign="top"><em>any character for which
 *       </em><code>Character.digit(c, 16)</code><em>
 *       returns a non-negative result</em></td>
 *     </tr>
 *     <tr>
 *       <td nowrap valign="top" align="right"><code>property :=&nbsp; </code></td>
 *       <td valign="top"><em>a Unicode property set pattern</td>
 *     </tr>
 *   </table>
 *   <br>
 *   <table border="1">
 *     <tr>
 *       <td>Legend: <table>
 *         <tr>
 *           <td nowrap valign="top"><code>a := b</code></td>
 *           <td width="20" valign="top">&nbsp; </td>
 *           <td valign="top"><code>a</code> may be replaced by <code>b</code> </td>
 *         </tr>
 *         <tr>
 *           <td nowrap valign="top"><code>a?</code></td>
 *           <td valign="top"></td>
 *           <td valign="top">zero or one instance of <code>a</code><br>
 *           </td>
 *         </tr>
 *         <tr>
 *           <td nowrap valign="top"><code>a*</code></td>
 *           <td valign="top"></td>
 *           <td valign="top">one or more instances of <code>a</code><br>
 *           </td>
 *         </tr>
 *         <tr>
 *           <td nowrap valign="top"><code>a | b</code></td>
 *           <td valign="top"></td>
 *           <td valign="top">either <code>a</code> or <code>b</code><br>
 *           </td>
 *         </tr>
 *         <tr>
 *           <td nowrap valign="top"><code>'a'</code></td>
 *           <td valign="top"></td>
 *           <td valign="top">the literal string between the quotes </td>
 *         </tr>
 *       </table>
 *       </td>
 *     </tr>
 *   </table>
 * </blockquote>
 *
 * Any character may be preceded by a backslash in order to remove any special
 * meaning.  White space characters, as defined by UCharacter.isWhitespace(), are
 * ignored, unless they are escaped.
 *
 * <p>Property patterns specify a set of characters having a certain
 * property as defined by the Unicode standard.  Both the POSIX-like
 * "[:Lu:]" and the Perl-like syntax "\p{Lu}" are recognized.  For a
 * complete list of supported property patterns, see the User's Guide
 * for UnicodeSet at
 * <a href="http://oss.software.ibm.com/icu/userguide/unicodeset.html">
 * http://oss.software.ibm.com/icu/userguide/unicodeset.html</a>.
 * Actual determination of property data is defined by the underlying
 * Unicode database as implemented by UCharacter.
 *
 * <p>Patterns specify individual characters, ranges of characters, and
 * Unicode property sets.  When elements are concatenated, they
 * specify their union.  To complement a set, place a '^' immediately
 * after the opening '['.  Property patterns are inverted by modifying
 * their delimiters; "[:^foo]" and "\P{foo}".  In any other location,
 * '^' has no special meaning.
 *
 * <p>Ranges are indicated by placing two a '-' between two
 * characters, as in "a-z".  This specifies the range of all
 * characters from the left to the right, in Unicode order.  If the
 * left character is greater than or equal to the
 * right character it is a syntax error.  If a '-' occurs as the first
 * character after the opening '[' or '[^', or if it occurs as the
 * last character before the closing ']', then it is taken as a
 * literal.  Thus "[a\u005C-b]", "[-ab]", and "[ab-]" all indicate the same
 * set of three characters, 'a', 'b', and '-'.
 *
 * <p>Sets may be intersected using the '&' operator or the asymmetric
 * set difference may be taken using the '-' operator, for example,
 * "[[:L:]&[\u005Cu0000-\u005Cu0FFF]]" indicates the set of all Unicode letters
 * with values less than 4096.  Operators ('&' and '|') have equal
 * precedence and bind left-to-right.  Thus
 * "[[:L:]-[a-z]-[\u005Cu0100-\u005Cu01FF]]" is equivalent to
 * "[[[:L:]-[a-z]]-[\u005Cu0100-\u005Cu01FF]]".  This only really matters for
 * difference; intersection is commutative.
 *
 * <table>
 * <tr valign=top><td nowrap><code>[a]</code><td>The set containing 'a'
 * <tr valign=top><td nowrap><code>[a-z]</code><td>The set containing 'a'
 * through 'z' and all letters in between, in Unicode order
 * <tr valign=top><td nowrap><code>[^a-z]</code><td>The set containing
 * all characters but 'a' through 'z',
 * that is, U+0000 through 'a'-1 and 'z'+1 through U+10FFFF
 * <tr valign=top><td nowrap><code>[[<em>pat1</em>][<em>pat2</em>]]</code>
 * <td>The union of sets specified by <em>pat1</em> and <em>pat2</em>
 * <tr valign=top><td nowrap><code>[[<em>pat1</em>]&[<em>pat2</em>]]</code>
 * <td>The intersection of sets specified by <em>pat1</em> and <em>pat2</em>
 * <tr valign=top><td nowrap><code>[[<em>pat1</em>]-[<em>pat2</em>]]</code>
 * <td>The asymmetric difference of sets specified by <em>pat1</em> and
 * <em>pat2</em>
 * <tr valign=top><td nowrap><code>[:Lu:] or \p{Lu}</code>
 * <td>The set of characters having the specified
 * Unicode property; in
 * this case, Unicode uppercase letters
 * <tr valign=top><td nowrap><code>[:^Lu:] or \P{Lu}</code>
 * <td>The set of characters <em>not</em> having the given
 * Unicode property
 * </table>
 * @author Alan Liu
 * @stable
 */
class U_I18N_API UnicodeSet : public UnicodeFilter {

    int32_t len; // length of list used; 0 <= len <= capacity
    int32_t capacity; // capacity of list
    int32_t bufferCapacity; // capacity of buffer
    UChar32* list; // MUST be terminated with HIGH
    UChar32* buffer; // internal buffer, may be NULL

    /**
     * The pattern representation of this set.  This may not be the
     * most economical pattern.  It is the pattern supplied to
     * applyPattern(), with variables substituted and whitespace
     * removed.  For sets constructed without applyPattern(), or
     * modified using the non-pattern API, this string will be empty,
     * indicating that toPattern() must generate a pattern
     * representation from the inversion list.
     */
    UnicodeString pat;

public:

    /**
     * Minimum value that can be stored in a UnicodeSet.
     */
    static const UChar32 MIN_VALUE;

    /**
     * Maximum value that can be stored in a UnicodeSet.
     */
    static const UChar32 MAX_VALUE;

    //----------------------------------------------------------------
    // Constructors &c
    //----------------------------------------------------------------

public:

    /**
     * Constructs an empty set.
     * @stable
     */
    UnicodeSet();

    /**
     * Constructs a set containing the given range. If <code>end >
     * start</code> then an empty set is created.
     *
     * @param start first character, inclusive, of range
     * @param end last character, inclusive, of range
     */
    UnicodeSet(UChar32 start, UChar32 end);

    /**
     * Constructs a set from the given pattern.  See the class
     * description for the syntax of the pattern language.
     * @param pattern a string specifying what characters are in the set
     * @exception <code>IllegalArgumentException</code> if the pattern
     * contains a syntax error.
     * @stable
     */
    UnicodeSet(const UnicodeString& pattern,
               UErrorCode& status);

    /**
     * DEPRECATED Constructs a set from the given Unicode character category.
     * @param category an integer indicating the character category as
     * defined in uchar.h.
     * @deprecated To be removed after 2002-DEC-31
     */
    UnicodeSet(int8_t category, UErrorCode& status);

    /**
     * Constructs a set that is identical to the given UnicodeSet.
     * @stable
     */
    UnicodeSet(const UnicodeSet& o);

    /**
     * Destructs the set.
     * @stable
     */
    virtual ~UnicodeSet();

    /**
     * Assigns this object to be a copy of another.
     * @stable
     */
    UnicodeSet& operator=(const UnicodeSet& o);

    /**
     * Compares the specified object with this set for equality.  Returns
     * <tt>true</tt> if the two sets
     * have the same size, and every member of the specified set is
     * contained in this set (or equivalently, every member of this set is
     * contained in the specified set).
     *
     * @param o set to be compared for equality with this set.
     * @return <tt>true</tt> if the specified set is equal to this set.
     * @stable
     */
    virtual UBool operator==(const UnicodeSet& o) const;

    /**
     * Compares the specified object with this set for equality.  Returns
     * <tt>true</tt> if the specified set is not equal to this set.
     * @stable
     */
    UBool operator!=(const UnicodeSet& o) const;

    /**
     * Returns a copy of this object.  All UnicodeFunctor objects have
     * to support cloning in order to allow classes using
     * UnicodeFunctors, such as Transliterator, to implement cloning.
     * @draft ICU 2.0
     */
    virtual UnicodeFunctor* clone() const;

    /**
     * Returns the hash code value for this set.
     *
     * @return the hash code value for this set.
     * @see Object#hashCode()
     * @stable
     */
    virtual int32_t hashCode(void) const;

    //----------------------------------------------------------------
    // Public API
    //----------------------------------------------------------------

    /**
     * Make this object represent the range <code>start - end</code>.
     * If <code>end > start</code> then this object is set to an
     * an empty range.
     *
     * @param start first character in the set, inclusive
     * @rparam end last character in the set, inclusive
     */
    void set(UChar32 start, UChar32 end);

    /**
     * Return true if the given position, in the given pattern, appears
     * to be the start of a UnicodeSet pattern.
     */
    static UBool resemblesPattern(const UnicodeString& pattern,
                                  int32_t pos);

    /**
     * Modifies this set to represent the set specified by the given
     * pattern, optionally ignoring white space.  See the class
     * description for the syntax of the pattern language.
     * @param pattern a string specifying what characters are in the set
     * @exception <code>IllegalArgumentException</code> if the pattern
     * contains a syntax error.
     * @stable
     */
    virtual void applyPattern(const UnicodeString& pattern,
                              UErrorCode& status);

    /**
     * Returns a string representation of this set.  If the result of
     * calling this function is passed to a UnicodeSet constructor, it
     * will produce another set that is equal to this one.
     * @param result the string to receive the rules.  Previous
     * contents will be deleted.
     * @param escapeUnprintable if TRUE then convert unprintable
     * character to their hex escape representations, \uxxxx or
     * \Uxxxxxxxx.  Unprintable characters are those other than
     * U+000A, U+0020..U+007E.
     * @draft ICU 2.0
     */
    virtual UnicodeString& toPattern(UnicodeString& result,
                                     UBool escapeUnprintable = FALSE) const;

    /**
     * Returns the number of elements in this set (its cardinality),
     * <em>n</em>, where <code>0 <= </code><em>n</em><code> <= 65536</code>.
     *
     * @return the number of elements in this set (its cardinality).
     * @stable
     */
    virtual int32_t size(void) const;

    /**
     * Returns <tt>true</tt> if this set contains no elements.
     *
     * @return <tt>true</tt> if this set contains no elements.
     * @stable
     */
    virtual UBool isEmpty(void) const;

    /**
     * Returns <tt>true</tt> if this set contains the specified range
     * of chars.
     *
     * @return <tt>true</tt> if this set contains the specified range
     * of chars.
     * @draft ICU 2.0
     */
    virtual UBool contains(UChar32 start, UChar32 end) const;

    /**
     * Returns <tt>true</tt> if this set contains the specified char.
     *
     * @return <tt>true</tt> if this set contains the specified char.
     * @draft ICU 2.0
     */
    virtual UBool contains(UChar32 c) const;

    /**
     * Implement UnicodeMatcher::matches()
     */
    UMatchDegree matches(const Replaceable& text,
                         int32_t& offset,
                         int32_t limit,
                         UBool incremental);
    
    /**
     * Returns the index of the given character within this set, where
     * the set is ordered by ascending code point.  If the character
     * is not in this set, return -1.  The inverse of this method is
     * <code>charAt()</code>.
     * @return an index from 0..size()-1, or -1
     */
    int32_t indexOf(UChar32 c) const;

    /**
     * Returns the character at the given index within this set, where
     * the set is ordered by ascending code point.  If the index is
     * out of range, return (UChar32)-1.  The inverse of this method is
     * <code>indexOf()</code>.
     * @param index an index from 0..size()-1
     * @return the character at the given index, or (UChar32)-1.
     */
    UChar32 charAt(int32_t index) const;

    /**
     * Adds the specified range to this set if it is not already
     * present.  If this set already contains the specified range,
     * the call leaves this set unchanged.  If <code>end > start</code>
     * then an empty range is added, leaving the set unchanged.
     * This is equivalent to a boolean logic OR, or a set UNION.
     *
     * @param start first character, inclusive, of range to be added
     * to this set.
     * @param end last character, inclusive, of range to be added
     * to this set.
     * @draft ICU 2.0
     */
    virtual void add(UChar32 start, UChar32 end);

    /**
     * Adds the specified character to this set if it is not already
     * present.  If this set already contains the specified character,
     * the call leaves this set unchanged.
     * @draft ICU 2.0
     */
    void add(UChar32 c);

    /**
     * Retain only the elements in this set that are contained in the
     * specified range.  If <code>end > start</code> then an empty range is
     * retained, leaving the set empty.  This is equivalent to
     * a boolean logic AND, or a set INTERSECTION.
     *
     * @param start first character, inclusive, of range to be retained
     * to this set.
     * @param end last character, inclusive, of range to be retained
     * to this set.
     * @draft ICU 2.0
     */
    virtual void retain(UChar32 start, UChar32 end);


    /**
     * Retain the specified character from this set if it is present.
     * @draft ICU 2.0
     */
    void retain(UChar32 c);

    /**
     * Removes the specified range from this set if it is present.
     * The set will not contain the specified range once the call
     * returns.  If <code>end > start</code> then an empty range is
     * removed, leaving the set unchanged.
     *
     * @param start first character, inclusive, of range to be removed
     * from this set.
     * @param end last character, inclusive, of range to be removed
     * from this set.
     * @draft ICU 2.0
     */
    virtual void remove(UChar32 start, UChar32 end);

    /**
     * Removes the specified character from this set if it is present.
     * The set will not contain the specified range once the call
     * returns.
     * @draft ICU 2.0
     */
    void remove(UChar32 c);

    /**
     * Inverts this set.  This operation modifies this set so that
     * its value is its complement.  This is equivalent to
     * <code>complement(MIN_VALUE, MAX_VALUE)</code>.
     * @stable
     */
    virtual void complement(void);

    /**
     * Complements the specified range in this set.  Any character in
     * the range will be removed if it is in this set, or will be
     * added if it is not in this set.  If <code>end > start</code>
     * then an empty range is complemented, leaving the set unchanged.
     * This is equivalent to a boolean logic XOR.
     *
     * @param start first character, inclusive, of range to be removed
     * from this set.
     * @param end last character, inclusive, of range to be removed
     * from this set.
     * @draft ICU 2.0
     */
    virtual void complement(UChar32 start, UChar32 end);


    /**
     * Complements the specified character in this set.  The character
     * will be removed if it is in this set, or will be added if it is
     * not in this set.
     * @draft ICU 2.0
     */
    void complement(UChar32 c);

    /**
     * Returns <tt>true</tt> if the specified set is a <i>subset</i>
     * of this set.
     *
     * @param c set to be checked for containment in this set.
     * @return <tt>true</tt> if this set contains all of the elements of the
     *         specified set.
     * @stable
     */
    virtual UBool containsAll(const UnicodeSet& c) const;

 private:
    friend class NormalizationTransliterator;
    // TODO: Make this public
    /**
     * Return TRUE if every character in s is in this set.
     */
    UBool containsAll(const UnicodeString& s) const;

 public:

    /**
     * Adds all of the elements in the specified set to this set if
     * they're not already present.  This operation effectively
     * modifies this set so that its value is the <i>union</i> of the two
     * sets.  The behavior of this operation is unspecified if the specified
     * collection is modified while the operation is in progress.
     *
     * @param c set whose elements are to be added to this set.
     * @see #add(char, char)
     * @stable
     */
    virtual void addAll(const UnicodeSet& c);

    /**
     * Retains only the elements in this set that are contained in the
     * specified set.  In other words, removes from this set all of
     * its elements that are not contained in the specified set.  This
     * operation effectively modifies this set so that its value is
     * the <i>intersection</i> of the two sets.
     *
     * @param c set that defines which elements this set will retain.
     * @stable
     */
    virtual void retainAll(const UnicodeSet& c);

    /**
     * Removes from this set all of its elements that are contained in the
     * specified set.  This operation effectively modifies this
     * set so that its value is the <i>asymmetric set difference</i> of
     * the two sets.
     *
     * @param c set that defines which elements will be removed from
     *          this set.
     * @stable
     */
    virtual void removeAll(const UnicodeSet& c);

    /**
     * Complements in this set all elements contained in the specified
     * set.  Any character in the other set will be removed if it is
     * in this set, or will be added if it is not in this set.
     *
     * @param c set that defines which elements will be xor'ed from
     *          this set.
     */
    virtual void complementAll(const UnicodeSet& c);

    /**
     * Removes all of the elements from this set.  This set will be
     * empty after this call returns.
     * @stable
     */
    virtual void clear(void);

    /**
     * Iteration method that returns the number of ranges contained in
     * this set.
     * @see #getRangeStart
     * @see #getRangeEnd
     */
    virtual int32_t getRangeCount(void) const;

    /**
     * Iteration method that returns the first character in the
     * specified range of this set.
     * @see #getRangeCount
     * @see #getRangeEnd
     */
    virtual UChar32 getRangeStart(int32_t index) const;

    /**
     * Iteration method that returns the last character in the
     * specified range of this set.
     * @see #getRangeStart
     * @see #getRangeEnd
     */
    virtual UChar32 getRangeEnd(int32_t index) const;

    /**
     * Reallocate this objects internal structures to take up the least
     * possible space, without changing this object's value.
     */
    virtual void compact();

    /**
     * Return the class ID for this class.  This is useful only for
     * comparing to a return value from getDynamicClassID().  For example:
     * <pre>
     * .      Base* polymorphic_pointer = createPolymorphicObject();
     * .      if (polymorphic_pointer->getDynamicClassID() ==
     * .          Derived::getStaticClassID()) ...
     * </pre>
     * @return          The class ID for all objects of this class.
     * @stable
     */
    static UClassID getStaticClassID(void) { return (UClassID)&fgClassID; }

    /**
     * Implement UnicodeFunctor API.
     *
     * @return The class ID for this object. All objects of a given
     * class have the same class ID.  Objects of other classes have
     * different class IDs.
     */
    virtual UClassID getDynamicClassID(void) const { return getStaticClassID(); };

private:

    static const char fgClassID;

private:

    //----------------------------------------------------------------
    // RuleBasedTransliterator support
    //----------------------------------------------------------------

    friend class Transliterator;
    friend class TransliteratorParser;
    friend class TransliteratorIDParser;
    friend class TransliterationRule;

    /**
     * Constructs a set from the given pattern.  See the class description
     * for the syntax of the pattern language.

     * @param pattern a string specifying what characters are in the set
     * @param pos on input, the position in pattern at which to start parsing.
     * On output, the position after the last character parsed.
     * @param varNameToChar a mapping from variable names (String) to characters
     * (Character).  May be null.  If varCharToSet is non-null, then names may
     * map to either single characters or sets, depending on whether a mapping
     * exists in varCharToSet.  If varCharToSet is null then all names map to
     * single characters.
     * @param varCharToSet a mapping from characters (Character objects from
     * varNameToChar) to UnicodeSet objects.  May be null.  Is only used if
     * varNameToChar is also non-null.
     * @exception <code>IllegalArgumentException</code> if the pattern
     * contains a syntax error.
     */
    UnicodeSet(const UnicodeString& pattern, ParsePosition& pos,
               const SymbolTable& symbols,
               UErrorCode& status);

    /**
     * Constructs a set from the given pattern.  Identical to the
     * 4-parameter ParsePosition contstructor, but does not take a
     * SymbolTable, and does not recognize embedded variables.
     */
    UnicodeSet(const UnicodeString& pattern, ParsePosition& pos,
               UErrorCode& status);

    /**
     * Returns <tt>true</tt> if this set contains any character whose low byte
     * is the given value.  This is used by <tt>RuleBasedTransliterator</tt> for
     * indexing.
     */
    virtual UBool matchesIndexValue(uint8_t v) const;

private:

    //----------------------------------------------------------------
    // Implementation: Pattern parsing
    //----------------------------------------------------------------

    /**
     * Parses the given pattern, starting at the given position.  The
     * character at pattern.charAt(pos.getIndex()) must be '[', or the
     * parse fails.  Parsing continues until the corresponding closing
     * ']'.  If a syntax error is encountered between the opening and
     * closing brace, the parse fails.  Upon return from a successful
     * parse, the ParsePosition is updated to point to the character
     * following the closing ']', and a StringBuffer containing a
     * pairs list for the parsed pattern is returned.  This method calls
     * itself recursively to parse embedded subpatterns.
     *
     * @param pattern the string containing the pattern to be parsed.
     * The portion of the string from pos.getIndex(), which must be a
     * '[', to the corresponding closing ']', is parsed.
     * @param pos upon entry, the position at which to being parsing.
     * The character at pattern.charAt(pos.getIndex()) must be a '['.
     * Upon return from a successful parse, pos.getIndex() is either
     * the character after the closing ']' of the parsed pattern, or
     * pattern.length() if the closing ']' is the last character of
     * the pattern string.
     * @return a StringBuffer containing a pairs list for the parsed
     * substring of <code>pattern</code>
     * @exception IllegalArgumentException if the parse fails.
     */
    void applyPattern(const UnicodeString& pattern,
                      ParsePosition& pos,
                      const SymbolTable* symbols,
                      UErrorCode& status);

    //----------------------------------------------------------------
    // Implementation: Utility methods
    //----------------------------------------------------------------

    void ensureCapacity(int32_t newLen);

    void ensureBufferCapacity(int32_t newLen);

    void swapBuffers(void);

    void _applyPattern(const UnicodeString& pattern,
                       ParsePosition& pos,
                       const SymbolTable* symbols,
                       UnicodeString& rebuiltPat,
                       UErrorCode& status);

    UnicodeString& _toPattern(UnicodeString& result,
                              UBool escapeUnprintable) const;

    UnicodeString& _generatePattern(UnicodeString& result,
                                    UBool escapeUnprintable) const;

    static void _appendToPat(UnicodeString& buf, UChar32 c, UBool escapeUnprintable);

    //----------------------------------------------------------------
    // Implementation: Fundamental operators
    //----------------------------------------------------------------

    void exclusiveOr(const UChar32* other, int32_t otherLen, int8_t polarity);

    void add(const UChar32* other, int32_t otherLen, int8_t polarity);

    void retain(const UChar32* other, int32_t otherLen, int8_t polarity);
};

inline UBool UnicodeSet::operator!=(const UnicodeSet& o) const {
    return !operator==(o);
}

U_NAMESPACE_END

#endif
