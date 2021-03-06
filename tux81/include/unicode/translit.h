/*
* Copyright (C) 1999-2001, International Business Machines Corporation and others. All Rights Reserved.
**********************************************************************
*   Date        Name        Description
*   11/17/99    aliu        Creation.
**********************************************************************
*/
#ifndef TRANSLIT_H
#define TRANSLIT_H

#include "unicode/unistr.h"
#include "unicode/parseerr.h"
#include "unicode/utrans.h" // UTransPosition, UTransDirection

U_NAMESPACE_BEGIN

class Replaceable;
class UnicodeFilter;
class UnicodeSet;
class TransliterationRuleData;
class U_I18N_API UVector;
class CompoundTransliterator;
class TransliteratorParser;
class NormalizationTransliterator;
class TransliteratorIDParser;

/**
 * <code>Transliterator</code> is an abstract class that
 * transliterates text from one format to another.  The most common
 * kind of transliterator is a script, or alphabet, transliterator.
 * For example, a Russian to Latin transliterator changes Russian text
 * written in Cyrillic characters to phonetically equivalent Latin
 * characters.  It does not <em>translate</em> Russian to English!
 * Transliteration, unlike translation, operates on characters, without
 * reference to the meanings of words and sentences.
 *
 * <p>Although script conversion is its most common use, a
 * transliterator can actually perform a more general class of tasks.
 * In fact, <code>Transliterator</code> defines a very general API
 * which specifies only that a segment of the input text is replaced
 * by new text.  The particulars of this conversion are determined
 * entirely by subclasses of <code>Transliterator</code>.
 *
 * <p><b>Transliterators are stateless</b>
 *
 * <p><code>Transliterator</code> objects are <em>stateless</em>; they
 * retain no information between calls to
 * <code>transliterate()</code>.  (However, this does <em>not</em>
 * mean that threads may share transliterators without synchronizing
 * them.  Transliterators are not immutable, so they must be
 * synchronized when shared between threads.)  This1 might seem to
 * limit the complexity of the transliteration operation.  In
 * practice, subclasses perform complex transliterations by delaying
 * the replacement of text until it is known that no other
 * replacements are possible.  In other words, although the
 * <code>Transliterator</code> objects are stateless, the source text
 * itself embodies all the needed information, and delayed operation
 * allows arbitrary complexity.
 *
 * <p><b>Batch transliteration</b>
 *
 * <p>The simplest way to perform transliteration is all at once, on a
 * string of existing text.  This is referred to as <em>batch</em>
 * transliteration.  For example, given a string <code>input</code>
 * and a transliterator <code>t</code>, the call
 *
 * <blockquote><code>String result = t.transliterate(input);
 * </code></blockquote>
 *
 * will transliterate it and return the result.  Other methods allow
 * the client to specify a substring to be transliterated and to use
 * {@link Replaceable} objects instead of strings, in order to
 * preserve out-of-band information (such as text styles).
 *
 * <p><b>Keyboard transliteration</b>
 *
 * <p>Somewhat more involved is <em>keyboard</em>, or incremental
 * transliteration.  This is the transliteration of text that is
 * arriving from some source (typically the user's keyboard) one
 * character at a time, or in some other piecemeal fashion.
 *
 * <p>In keyboard transliteration, a <code>Replaceable</code> buffer
 * stores the text.  As text is inserted, as much as possible is
 * transliterated on the fly.  This means a GUI that displays the
 * contents of the buffer may show text being modified as each new
 * character arrives.
 *
 * <p>Consider the simple <code>RuleBasedTransliterator</code>:
 *
 * <blockquote><code>
 * th&gt;{theta}<br>
 * t&gt;{tau}
 * </code></blockquote>
 *
 * When the user types 't', nothing will happen, since the
 * transliterator is waiting to see if the next character is 'h'.  To
 * remedy this, we introduce the notion of a cursor, marked by a '|'
 * in the output string:
 *
 * <blockquote><code>
 * t&gt;|{tau}<br>
 * {tau}h&gt;{theta}
 * </code></blockquote>
 *
 * Now when the user types 't', tau appears, and if the next character
 * is 'h', the tau changes to a theta.  This is accomplished by
 * maintaining a cursor position (independent of the insertion point,
 * and invisible in the GUI) across calls to
 * <code>transliterate()</code>.  Typically, the cursor will
 * be coincident with the insertion point, but in a case like the one
 * above, it will precede the insertion point.
 *
 * <p>Keyboard transliteration methods maintain a set of three indices
 * that are updated with each call to
 * <code>transliterate()</code>, including the cursor, start,
 * and limit.  Since these indices are changed by the method, they are
 * passed in an <code>int[]</code> array. The <code>START</code> index
 * marks the beginning of the substring that the transliterator will
 * look at.  It is advanced as text becomes committed (but it is not
 * the committed index; that's the <code>CURSOR</code>).  The
 * <code>CURSOR</code> index, described above, marks the point at
 * which the transliterator last stopped, either because it reached
 * the end, or because it required more characters to disambiguate
 * between possible inputs.  The <code>CURSOR</code> can also be
 * explicitly set by rules in a <code>RuleBasedTransliterator</code>.
 * Any characters before the <code>CURSOR</code> index are frozen;
 * future keyboard transliteration calls within this input sequence
 * will not change them.  New text is inserted at the
 * <code>LIMIT</code> index, which marks the end of the substring that
 * the transliterator looks at.
 *
 * <p>Because keyboard transliteration assumes that more characters
 * are to arrive, it is conservative in its operation.  It only
 * transliterates when it can do so unambiguously.  Otherwise it waits
 * for more characters to arrive.  When the client code knows that no
 * more characters are forthcoming, perhaps because the user has
 * performed some input termination operation, then it should call
 * <code>finishTransliteration()</code> to complete any
 * pending transliterations.
 *
 * <p><b>Inverses</b>
 *
 * <p>Pairs of transliterators may be inverses of one another.  For
 * example, if transliterator <b>A</b> transliterates characters by
 * incrementing their Unicode value (so "abc" -> "def"), and
 * transliterator <b>B</b> decrements character values, then <b>A</b>
 * is an inverse of <b>B</b> and vice versa.  If we compose <b>A</b>
 * with <b>B</b> in a compound transliterator, the result is the
 * indentity transliterator, that is, a transliterator that does not
 * change its input text.
 *
 * The <code>Transliterator</code> method <code>getInverse()</code>
 * returns a transliterator's inverse, if one exists, or
 * <code>null</code> otherwise.  However, the result of
 * <code>getInverse()</code> usually will <em>not</em> be a true
 * mathematical inverse.  This is because true inverse transliterators
 * are difficult to formulate.  For example, consider two
 * transliterators: <b>AB</b>, which transliterates the character 'A'
 * to 'B', and <b>BA</b>, which transliterates 'B' to 'A'.  It might
 * seem that these are exact inverses, since
 *
 * <blockquote>"A" x <b>AB</b> -> "B"<br>
 * "B" x <b>BA</b> -> "A"</blockquote>
 *
 * where 'x' represents transliteration.  However,
 *
 * <blockquote>"ABCD" x <b>AB</b> -> "BBCD"<br>
 * "BBCD" x <b>BA</b> -> "AACD"</blockquote>
 *
 * so <b>AB</b> composed with <b>BA</b> is not the
 * identity. Nonetheless, <b>BA</b> may be usefully considered to be
 * <b>AB</b>'s inverse, and it is on this basis that
 * <b>AB</b><code>.getInverse()</code> could legitimately return
 * <b>BA</b>.
 *
 * <p><b>IDs and display names</b>
 *
 * <p>A transliterator is designated by a short identifier string or
 * <em>ID</em>.  IDs follow the format <em>source-destination</em>,
 * where <em>source</em> describes the entity being replaced, and
 * <em>destination</em> describes the entity replacing
 * <em>source</em>.  The entities may be the names of scripts,
 * particular sequences of characters, or whatever else it is that the
 * transliterator converts to or from.  For example, a transliterator
 * from Russian to Latin might be named "Russian-Latin".  A
 * transliterator from keyboard escape sequences to Latin-1 characters
 * might be named "KeyboardEscape-Latin1".  By convention, system
 * entity names are in English, with the initial letters of words
 * capitalized; user entity names may follow any format so long as
 * they do not contain dashes.
 *
 * <p>In addition to programmatic IDs, transliterator objects have
 * display names for presentation in user interfaces, returned by
 * {@link #getDisplayName}.
 *
 * <p><b>Factory methods and registration</b>
 *
 * <p>In general, client code should use the factory method
 * <code>getInstance()</code> to obtain an instance of a
 * transliterator given its ID.  Valid IDs may be enumerated using
 * <code>getAvailableIDs()</code>.  Since transliterators are mutable,
 * multiple calls to <code>getInstance()</code> with the same ID will
 * return distinct objects.
 *
 * <p>In addition to the system transliterators registered at startup,
 * user transliterators may be registered by calling
 * <code>registerInstance()</code> at run time.  A registered instance
 * acts a template; future calls to <tt>getInstance()</tt> with the ID
 * of the registered object return clones of that object.  Thus any
 * object passed to <tt>registerInstance()</tt> must implement
 * <tt>clone()</tt> propertly.  To register a transliterator subclass
 * without instantiating it (until it is needed), users may call
 * <code>registerClass()</code>.  In this case, the objects are
 * instantiated by invoking the zero-argument public constructor of
 * the class.
 *
 * <p><b>Subclassing</b>
 *
 * Subclasses must implement the abstract method
 * <code>handleTransliterate()</code>.  <p>Subclasses should override
 * the <code>transliterate()</code> method taking a
 * <code>Replaceable</code> and the <code>transliterate()</code>
 * method taking a <code>String</code> and <code>StringBuffer</code>
 * if the performance of these methods can be improved over the
 * performance obtained by the default implementations in this class.
 *
 * @author Alan Liu
 * @stable
 */
class U_I18N_API Transliterator {

private:

    /**
     * Programmatic name, e.g., "Latin-Arabic".
     */
    UnicodeString ID;

    /**
     * This transliterator's filter.  Any character for which
     * <tt>filter.contains()</tt> returns <tt>false</tt> will not be
     * altered by this transliterator.  If <tt>filter</tt> is
     * <tt>null</tt> then no filtering is applied.
     */
    UnicodeFilter* filter;

    int32_t maximumContextLength;

 public:

    /**
     * A context integer or pointer for a factory function, passed by
     * value.
     */
    union Token {
        int32_t integer;
        void*   pointer;
    };

    /**
     * Return a token containing an integer.
     */
    inline static Token integerToken(int32_t);

    /**
     * Return a token containing a pointer.
     */
    inline static Token pointerToken(void*);

    /**
     * A function that creates and returns a Transliterator.  When
     * invoked, it will be passed the ID string that is being
     * instantiated, together with the context pointer that was passed
     * in when the factory function was first registered.  Many
     * factory functions will ignore both parameters, however,
     * functions that are registered to more than one ID may use the
     * ID or the context parameter to parameterize the transliterator
     * they create.
     */
    typedef Transliterator* (*Factory)(const UnicodeString& ID, Token context);

protected:

    /**
     * Default constructor.
     * @param ID the string identifier for this transliterator
     * @param adoptedFilter the filter.  Any character for which
     * <tt>filter.contains()</tt> returns <tt>false</tt> will not be
     * altered by this transliterator.  If <tt>filter</tt> is
     * <tt>null</tt> then no filtering is applied.
     */
    Transliterator(const UnicodeString& ID, UnicodeFilter* adoptedFilter);

    /**
     * Copy constructor.
     */
    Transliterator(const Transliterator&);

    /**
     * Assignment operator.
     */
    Transliterator& operator=(const Transliterator&);
    
    /**
     * Create a transliterator from a basic ID.  This is an ID
     * containing only the forward direction source, target, and
     * variant.
     * @param id a basic ID of the form S-T or S-T/V.
     * @param canon canonical ID to assign to the object, or
     * NULL to leave the ID unchanged
     * @return a newly created Transliterator or null if the ID is
     * invalid.
     */
    static Transliterator* createBasicInstance(const UnicodeString& id,
                                               const UnicodeString* canon);

    friend class TransliteratorParser; // for parseID()
    friend class TransliteratorIDParser; // for createBasicInstance()

public:

    /**
     * Destructor.
     * @stable
     */
    virtual ~Transliterator();

    /**
     * Implements Cloneable.
     * All subclasses are encouraged to implement this method if it is
     * possible and reasonable to do so.  Subclasses that are to be
     * registered with the system using <tt>registerInstance()<tt>
     * are required to implement this method.  If a subclass does not
     * implement clone() properly and is registered with the system
     * using registerInstance(), then the default clone() implementation
     * will return null, and calls to createInstance() will fail.
     *
     * @see #registerInstance
     * @stable
     */
    virtual Transliterator* clone() const { return 0; }

    /**
     * Transliterates a segment of a string, with optional filtering.
     *
     * @param text the string to be transliterated
     * @param start the beginning index, inclusive; <code>0 <= start
     * <= limit</code>.
     * @param limit the ending index, exclusive; <code>start <= limit
     * <= text.length()</code>.
     * @return The new limit index.  The text previously occupying <code>[start,
     * limit)</code> has been transliterated, possibly to a string of a different
     * length, at <code>[start, </code><em>new-limit</em><code>)</code>, where
     * <em>new-limit</em> is the return value. If the input offsets are out of bounds,
     * the returned value is -1 and the input string remains unchanged.
     * @stable
     */
    virtual int32_t transliterate(Replaceable& text,
                                  int32_t start, int32_t limit) const;

    /**
     * Transliterates an entire string in place. Convenience method.
     * @param text the string to be transliterated
     * @stable
     */
    virtual void transliterate(Replaceable& text) const;

    /**
     * Transliterates the portion of the text buffer that can be
     * transliterated unambiguosly after new text has been inserted,
     * typically as a result of a keyboard event.  The new text in
     * <code>insertion</code> will be inserted into <code>text</code>
     * at <code>index.limit</code>, advancing
     * <code>index.limit</code> by <code>insertion.length()</code>.
     * Then the transliterator will try to transliterate characters of
     * <code>text</code> between <code>index.cursor</code> and
     * <code>index.limit</code>.  Characters before
     * <code>index.cursor</code> will not be changed.
     *
     * <p>Upon return, values in <code>index</code> will be updated.
     * <code>index.start</code> will be advanced to the first
     * character that future calls to this method will read.
     * <code>index.cursor</code> and <code>index.limit</code> will
     * be adjusted to delimit the range of text that future calls to
     * this method may change.
     *
     * <p>Typical usage of this method begins with an initial call
     * with <code>index.start</code> and <code>index.limit</code>
     * set to indicate the portion of <code>text</code> to be
     * transliterated, and <code>index.cursor == index.start</code>.
     * Thereafter, <code>index</code> can be used without
     * modification in future calls, provided that all changes to
     * <code>text</code> are made via this method.
     *
     * <p>This method assumes that future calls may be made that will
     * insert new text into the buffer.  As a result, it only performs
     * unambiguous transliterations.  After the last call to this
     * method, there may be untransliterated text that is waiting for
     * more input to resolve an ambiguity.  In order to perform these
     * pending transliterations, clients should call {@link
     * #finishTransliteration} after the last call to this
     * method has been made.
     *
     * @param text the buffer holding transliterated and untransliterated text
     * @param index an array of three integers.
     *
     * <ul><li><code>index.start</code>: the beginning index,
     * inclusive; <code>0 <= index.start <= index.limit</code>.
     *
     * <li><code>index.limit</code>: the ending index, exclusive;
     * <code>index.start <= index.limit <= text.length()</code>.
     * <code>insertion</code> is inserted at
     * <code>index.limit</code>.
     *
     * <li><code>index.cursor</code>: the next character to be
     * considered for transliteration; <code>index.start <=
     * index.cursor <= index.limit</code>.  Characters before
     * <code>index.cursor</code> will not be changed by future calls
     * to this method.</ul>
     *
     * @param insertion text to be inserted and possibly
     * transliterated into the translation buffer at
     * <code>index.limit</code>.  If <code>null</code> then no text
     * is inserted.
     * @see #handleTransliterate
     * @exception IllegalArgumentException if <code>index</code>
     * is invalid
     * @see UTransPosition
     * @stable
     */
    virtual void transliterate(Replaceable& text, UTransPosition& index,
                               const UnicodeString& insertion,
                               UErrorCode& status) const;

    /**
     * Transliterates the portion of the text buffer that can be
     * transliterated unambiguosly after a new character has been
     * inserted, typically as a result of a keyboard event.  This is a
     * convenience method; see {@link
     * #transliterate(Replaceable, int[], String)} for details.
     * @param text the buffer holding transliterated and
     * untransliterated text
     * @param index an array of three integers.  See {@link
     * #transliterate(Replaceable, int[], String)}.
     * @param insertion text to be inserted and possibly
     * transliterated into the translation buffer at
     * <code>index.limit</code>.
     * @see #transliterate(Replaceable, int[], String)
     * @stable
     */
    virtual void transliterate(Replaceable& text, UTransPosition& index,
                               UChar32 insertion,
                               UErrorCode& status) const;

    /**
     * Transliterates the portion of the text buffer that can be
     * transliterated unambiguosly.  This is a convenience method; see
     * {@link #transliterate(Replaceable, int[], String)} for
     * details.
     * @param text the buffer holding transliterated and
     * untransliterated text
     * @param index an array of three integers.  See {@link
     * #transliterate(Replaceable, int[], String)}.
     * @see #transliterate(Replaceable, int[], String)
     * @stable
     */
    virtual void transliterate(Replaceable& text, UTransPosition& index,
                               UErrorCode& status) const;

    /**
     * Finishes any pending transliterations that were waiting for
     * more characters.  Clients should call this method as the last
     * call after a sequence of one or more calls to
     * <code>transliterate()</code>.
     * @param text the buffer holding transliterated and
     * untransliterated text.
     * @param index the array of indices previously passed to {@link
     * #transliterate}
     * @stable
     */
    virtual void finishTransliteration(Replaceable& text,
                                       UTransPosition& index) const;

private:

    /**
     * This internal method does incremental transliteration.  If the
     * 'insertion' is non-null then we append it to 'text' before
     * proceeding.  This method calls through to the pure virtual
     * framework method handleTransliterate() to do the actual
     * work.
     */
    void _transliterate(Replaceable& text,
                        UTransPosition& index,
                        const UnicodeString* insertion,
                        UErrorCode &status) const;

protected:

    /**
     * Abstract method that concrete subclasses define to implement
     * keyboard transliteration.  This method should transliterate all
     * characters between <code>pos.start</code> and
     * <code>pos.contextLimit</code> that can be unambiguously
     * transliterated, regardless of future insertions of text at
     * <code>pos.contextLimit</code>.  <code>pos.start</code> should
     * be advanced past committed characters (those that will not
     * change in future calls to this method).
     * <code>pos.contextLimit</code> should be updated to reflect text
     * replacements that shorten or lengthen the text between
     * <code>pos.start</code> and <code>pos.contextLimit</code>.  Upon
     * return, neither <code>pos.start</code> nor
     * <code>pos.contextLimit</code> should be less than the initial value
     * of <code>pos.start</code>.  <code>pos.contextStart</code>
     * should <em>not</em> be changed.
     *
     * <p>Subclasses may safely assume that all characters in
     * [pos.start, pos.limit) are unfiltered.  In other words, the
     * filter has already been applied by the time this method is
     * called.  See filteredTransliterate().
     *
     * <p>This method is <b>not</b> for public consumption.  Calling
     * this method directly will transliterate [pos.start,
     * pos.limit) without applying the filter.  End user code that
     * wants to call this method should be calling transliterate().
     * Subclass code that wants to call this method should probably be
     * calling filteredTransliterate().
     *
     * <p>If incremental is true, then upon return pos.start may be
     * less than pos.limit, if some characters are unprocessed.  If
     * incremental is false, then pos.start should be equal to pos.limit.
     *
     * @param text the buffer holding transliterated and
     * untransliterated text
     * @param pos the start and limit of the text, the position
     * of the cursor, and the start and limit of transliteration.
     * @param incremental if true, assume more text may be coming after
     * pos.contextLimit.  Otherwise, assume the text is complete.
     * @see #transliterate
     */ 
    virtual void handleTransliterate(Replaceable& text,
                                     UTransPosition& pos,
                                     UBool incremental) const = 0;

    /**
     * Transliterate a substring of text, as specified by index, taking filters
     * into account.  This method is for subclasses that need to delegate to
     * another transliterator, such as CompoundTransliterator.
     * @param text the text to be transliterated
     * @param index the position indices
     * @param incremental if TRUE, then assume more characters may be inserted
     * at index.limit, and postpone processing to accomodate future incoming
     * characters
     */
    virtual void filteredTransliterate(Replaceable& text,
                                       UTransPosition& index,
                                       UBool incremental) const;

    friend class CompoundTransliterator; // for filteredTransliterate()

private:

    /**
     * Top-level transliteration method, handling filtering, incremental and
     * non-incremental transliteration, and rollback.  All transliteration
     * public API methods eventually call this method with a rollback argument
     * of TRUE.  Other entities may call this method but rollback should be
     * FALSE.
     * 
     * <p>If this transliterator has a filter, break up the input text into runs
     * of unfiltered characters.  Pass each run to
     * <subclass>.handleTransliterate().
     *
     * <p>In incremental mode, if rollback is TRUE, perform a special
     * incremental procedure in which several passes are made over the input
     * text, adding one character at a time, and committing successful
     * transliterations as they occur.  Unsuccessful transliterations are rolled
     * back and retried with additional characters to give correct results.
     *
     * @param text the text to be transliterated
     * @param index the position indices
     * @param incremental if TRUE, then assume more characters may be inserted
     * at index.limit, and postpone processing to accomodate future incoming
     * characters
     * @param rollback if TRUE and if incremental is TRUE, then perform special
     * incremental processing, as described above, and undo partial
     * transliterations where necessary.  If incremental is FALSE then this
     * parameter is ignored.
     */
    virtual void filteredTransliterate(Replaceable& text,
                                       UTransPosition& index,
                                       UBool incremental,
                                       UBool rollback) const;

public:

    /**
     * Returns the length of the longest context required by this transliterator.
     * This is <em>preceding</em> context.  The default implementation supplied
     * by <code>Transliterator</code> returns zero; subclasses
     * that use preceding context should override this method to return the
     * correct value.  For example, if a transliterator translates "ddd" (where
     * d is any digit) to "555" when preceded by "(ddd)", then the preceding
     * context length is 5, the length of "(ddd)".
     *
     * @return The maximum number of preceding context characters this
     * transliterator needs to examine
     * @stable
     */
    int32_t getMaximumContextLength(void) const;

protected:

    /**
     * Method for subclasses to use to set the maximum context length.
     * @see #getMaximumContextLength
     */
    void setMaximumContextLength(int32_t maxContextLength);

public:

    /**
     * Returns a programmatic identifier for this transliterator.
     * If this identifier is passed to <code>getInstance()</code>, it
     * will return this object, if it has been registered.
     * @see #registerInstance
     * @see #registerClass
     * @see #getAvailableIDs
     * @stable
     */
    virtual const UnicodeString& getID(void) const;

    /**
     * Returns a name for this transliterator that is appropriate for
     * display to the user in the default locale.  See {@link
     * #getDisplayName(Locale)} for details.
     * @stable
     */
    static UnicodeString& getDisplayName(const UnicodeString& ID,
                                         UnicodeString& result);

    /**
     * Returns a name for this transliterator that is appropriate for
     * display to the user in the given locale.  This name is taken
     * from the locale resource data in the standard manner of the
     * <code>java.text</code> package.
     *
     * <p>If no localized names exist in the system resource bundles,
     * a name is synthesized using a localized
     * <code>MessageFormat</code> pattern from the resource data.  The
     * arguments to this pattern are an integer followed by one or two
     * strings.  The integer is the number of strings, either 1 or 2.
     * The strings are formed by splitting the ID for this
     * transliterator at the first '-'.  If there is no '-', then the
     * entire ID forms the only string.
     * @param inLocale the Locale in which the display name should be
     * localized.
     * @see java.text.MessageFormat
     * @stable
     */
    static UnicodeString& getDisplayName(const UnicodeString& ID,
                                         const Locale& inLocale,
                                         UnicodeString& result);

    /**
     * Returns the filter used by this transliterator, or <tt>NULL</tt>
     * if this transliterator uses no filter.
     * @stable
     */
    const UnicodeFilter* getFilter(void) const;

    /**
     * Returns the filter used by this transliterator, or <tt>NULL</tt> if this
     * transliterator uses no filter.  The caller must eventually delete the
     * result.  After this call, this transliterator's filter is set to
     * <tt>NULL</tt>.
     */
    UnicodeFilter* orphanFilter(void);

#ifdef U_USE_DEPRECATED_TRANSLITERATOR_API
    /**
     * Changes the filter used by this transliterator.  If the filter
     * is set to <tt>null</tt> then no filtering will occur.
     *
     * <p>Callers must take care if a transliterator is in use by
     * multiple threads.  The filter should not be changed by one
     * thread while another thread may be transliterating.
     *
     * @deprecated This method will be made NON-VIRTUAL in Aug 2002.
     */
    virtual void adoptFilter(UnicodeFilter* adoptedFilter);
#else
    /**
     * Changes the filter used by this transliterator.  If the filter
     * is set to <tt>null</tt> then no filtering will occur.
     *
     * <p>Callers must take care if a transliterator is in use by
     * multiple threads.  The filter should not be changed by one
     * thread while another thread may be transliterating.
     * @draft ICU 2.0
     */
    void adoptFilter(UnicodeFilter* adoptedFilter);
#endif

    /**
     * Returns this transliterator's inverse.  See the class
     * documentation for details.  This implementation simply inverts
     * the two entities in the ID and attempts to retrieve the
     * resulting transliterator.  That is, if <code>getID()</code>
     * returns "A-B", then this method will return the result of
     * <code>getInstance("B-A")</code>, or <code>null</code> if that
     * call fails.
     *
     * <p>Subclasses with knowledge of their inverse may wish to
     * override this method.
     *
     * @return a transliterator that is an inverse, not necessarily
     * exact, of this transliterator, or <code>null</code> if no such
     * transliterator is registered.
     * @see #registerInstance
     * @stable
     */
    Transliterator* createInverse(UErrorCode& status) const;

    /**
     * Returns a <code>Transliterator</code> object given its ID.
     * The ID must be either a system transliterator ID or a ID registered
     * using <code>registerInstance()</code>.
     *
     * @param ID a valid ID, as enumerated by <code>getAvailableIDs()</code>
     * @return A <code>Transliterator</code> object with the given ID
     * @see #registerInstance
     * @see #getAvailableIDs
     * @see #getID
     * @draft ICU 2.0
     */
    static Transliterator* createInstance(const UnicodeString& ID,
                                          UTransDirection dir,
                                          UParseError& parseError,
                                          UErrorCode& status);

    /**
     * Returns a <code>Transliterator</code> object given its ID.
     * The ID must be either a system transliterator ID or a ID registered
     * using <code>registerInstance()</code>.
     * @draft ICU 2.0
     */
    static Transliterator* createInstance(const UnicodeString& ID,
                                          UTransDirection dir,
                                          UErrorCode& status);
    /**
     * Returns a <code>Transliterator</code> object constructed from
     * the given rule string.  This will be a RuleBasedTransliterator,
     * if the rule string contains only rules, or a
     * CompoundTransliterator, if it contains ID blocks, or a
     * NullTransliterator, if it contains ID blocks which parse as
     * empty for the given direction.
     * @draft ICU 2.0
     */
    static Transliterator* createFromRules(const UnicodeString& ID,
                                           const UnicodeString& rules,
                                           UTransDirection dir,
                                           UParseError& parseError,
                                           UErrorCode& status);

    /**
     * Create a rule string that can be passed to createFromRules()
     * to recreate this transliterator.
     * @param result the string to receive the rules.  Previous
     * contents will be deleted.
     * @param escapeUnprintable if TRUE then convert unprintable
     * character to their hex escape representations, \uxxxx or
     * \Uxxxxxxxx.  Unprintable characters are those other than
     * U+000A, U+0020..U+007E.
     * @draft ICU 2.0
     */
    virtual UnicodeString& toRules(UnicodeString& result,
                                   UBool escapeUnprintable) const;

public:

    /**
     * Registers a factory function that creates transliterators of
     * a given ID.
     * @param id the ID being registered
     * @param factory a function pointer that will be copied and
     * called later when the given ID is passed to createInstance()
     * @param context a context pointer that will be stored and
     * later passed to the factory function when an ID matching
     * the registration ID is being instantiated with this factory.
     * @draft ICU 2.0
     */
    static void registerFactory(const UnicodeString& id,
                                Factory factory,
                                Token context);

    /**
     * Registers a instance <tt>obj</tt> of a subclass of
     * <code>Transliterator</code> with the system.  When
     * <tt>createInstance()</tt> is called with an ID string that is
     * equal to <tt>obj->getID()</tt>, then <tt>obj->clone()</tt> is
     * returned.
     *
     * After this call the Transliterator class owns the adoptedObj
     * and will delete it.
     *
     * @param obj an instance of subclass of
     * <code>Transliterator</code> that defines <tt>clone()</tt>
     * @see #getInstance
     * @see #registerClass
     * @see #unregister
     * @stable
     */
    static void registerInstance(Transliterator* adoptedObj);

protected:

    /**
     * @internal
     */
    static void _registerFactory(const UnicodeString& id,
                                 Factory factory,
                                 Token context);

    /**
     * Register two targets as being inverses of one another.  For
     * example, calling registerSpecialInverse("NFC", "NFD", true) causes
     * Transliterator to form the following inverse relationships:
     *
     * <pre>NFC => NFD
     * Any-NFC => Any-NFD
     * NFD => NFC
     * Any-NFD => Any-NFC</pre>
     *
     * (Without the special inverse registration, the inverse of NFC
     * would be NFC-Any.)  Note that NFD is shorthand for Any-NFD, but
     * that the presence or absence of "Any-" is preserved.
     *
     * <p>The relationship is symmetrical; registering (a, b) is
     * equivalent to registering (b, a).
     *
     * <p>The relevant IDs must still be registered separately as
     * factories or classes.
     *
     * <p>Only the targets are specified.  Special inverses always
     * have the form Any-Target1 <=> Any-Target2.  The target should
     * have canonical casing (the casing desired to be produced when
     * an inverse is formed) and should contain no whitespace or other
     * extraneous characters.
     *
     * @param target the target against which to register the inverse
     * @param inverseTarget the inverse of target, that is
     * Any-target.getInverse() => Any-inverseTarget
     * @param bidirectional if true, register the reverse relation
     * as well, that is, Any-inverseTarget.getInverse() => Any-target
     * @internal
     */
    static void _registerSpecialInverse(const UnicodeString& target,
                                        const UnicodeString& inverseTarget,
                                        UBool bidirectional);

public:

    /**
     * Unregisters a transliterator or class.  This may be either
     * a system transliterator or a user transliterator or class.
     * Any attempt to construct an unregistered transliterator based
     * on its ID will fail.
     *
     * @param ID the ID of the transliterator or class
     * @return the <code>Object</code> that was registered with
     * <code>ID</code>, or <code>null</code> if none was
     * @see #registerInstance
     * @see #registerClass
     * @stable
     */
    static void unregister(const UnicodeString& ID);

public:

    /**
     * Return the number of IDs currently registered with the system.
     * To retrieve the actual IDs, call getAvailableID(i) with
     * i from 0 to countAvailableIDs() - 1.
     * @stable
     */
    static int32_t countAvailableIDs(void);

    /**
     * Return the index-th available ID.  index must be between 0
     * and countAvailableIDs() - 1, inclusive.  If index is out of
     * range, the result of getAvailableID(0) is returned.
     * @stable
     */
    static const UnicodeString& getAvailableID(int32_t index);

    /**
     * Return the number of registered source specifiers.
     * @draft ICU 2.0
     */
    static int32_t countAvailableSources(void);
    
    /**
     * Return a registered source specifier.
     * @param index which specifier to return, from 0 to n-1, where
     * n = countAvailableSources()
     * @param result fill-in paramter to receive the source specifier.
     * If index is out of range, result will be empty.
     * @return reference to result
     * @draft ICU 2.0
     */
    static UnicodeString& getAvailableSource(int32_t index,
                                             UnicodeString& result);
    
    /**
     * Return the number of registered target specifiers for a given
     * source specifier.
     * @draft ICU 2.0
     */
    static int32_t countAvailableTargets(const UnicodeString& source);
    
    /**
     * Return a registered target specifier for a given source.
     * @param index which specifier to return, from 0 to n-1, where
     * n = countAvailableTargets(source)
     * @param source the source specifier
     * @param result fill-in paramter to receive the target specifier.
     * If source is invalid or if index is out of range, result will
     * be empty.
     * @return reference to result
     * @draft ICU 2.0
     */
    static UnicodeString& getAvailableTarget(int32_t index,
                                             const UnicodeString& source,
                                             UnicodeString& result);
    
    /**
     * Return the number of registered variant specifiers for a given
     * source-target pair.
     * @draft ICU 2.0
     */
    static int32_t countAvailableVariants(const UnicodeString& source,
                                          const UnicodeString& target);
    
    /**
     * Return a registered variant specifier for a given source-target
     * pair.
     * @param index which specifier to return, from 0 to n-1, where
     * n = countAvailableVariants(source, target)
     * @param source the source specifier
     * @param target the target specifier
     * @param result fill-in paramter to receive the variant
     * specifier.  If source is invalid or if target is invalid or if
     * index is out of range, result will be empty.
     * @return reference to result
     * @draft ICU 2.0
     */
    static UnicodeString& getAvailableVariant(int32_t index,
                                              const UnicodeString& source,
                                              const UnicodeString& target,
                                              UnicodeString& result);

    /**
     * Return the class ID for this class.  This is useful only for
     * comparing to a return value from getDynamicClassID().  For example:
     * <pre>
     * .      Base* polymorphic_pointer = createPolymorphicObject();
     * .      if (polymorphic_pointer->getDynamicClassID() ==
     * .          Derived::getStaticClassID()) ...
     * </pre>
     * @return          The class ID for all objects of this class.
     * @draft ICU 2.0
     */
    static UClassID getStaticClassID(void) { return (UClassID)&fgClassID; }

    /**
     * Returns a unique class ID <b>polymorphically</b>.  This method
     * is to implement a simple version of RTTI, since not all C++
     * compilers support genuine RTTI.  Polymorphic operator==() and
     * clone() methods call this method.
     * 
     * <p>Concrete subclasses of Transliterator that wish clients to
     * be able to identify them should implement getDynamicClassID()
     * and also a static method and data member:
     * 
     * <pre>
     * static UClassID getStaticClassID() { return (UClassID)&fgClassID; }
     * static char fgClassID;
     * </pre>
     *
     * Subclasses that do not implement this method will have a
     * dynamic class ID of Transliterator::getStatisClassID().
     *
     * @return The class ID for this object. All objects of a given
     * class have the same class ID.  Objects of other classes have
     * different class IDs.
     * @draft ICU 2.0
     */
    virtual UClassID getDynamicClassID(void) const { return getStaticClassID(); };

private:

    /**
     * Class identifier for subclasses of Transliterator that do not
     * define their class (anonymous subclasses).
     */
    static const char fgClassID;

protected:

    /**
     * Set the ID of this transliterators.  Subclasses shouldn't do
     * this, unless the underlying script behavior has changed.
     */
    void setID(const UnicodeString& id);

private:
    static void initializeRegistry(void);

#ifdef U_USE_DEPRECATED_TRANSLITERATOR_API

public:
    /**
     * Returns a <code>Transliterator</code> object given its ID.
     * The ID must be either a system transliterator ID or a ID registered
     * using <code>registerInstance()</code>.
     *
     * @param ID a valid ID, as enumerated by <code>getAvailableIDs()</code>
     * @return A <code>Transliterator</code> object with the given ID
     * @exception IllegalArgumentException if the given ID is invalid.
     * @see #registerInstance
     * @see #getAvailableIDs
     * @see #getID
     * @deprecated Remove after Aug 2002 use factory mehod that takes UParseError
     * and UErrorCode
     */
    inline Transliterator* createInstance(const UnicodeString& ID, 
                                          UTransDirection dir=UTRANS_FORWARD,
                                          UParseError* parseError=0);
   /**
     * Returns this transliterator's inverse.  See the class
     * documentation for details.  This implementation simply inverts
     * the two entities in the ID and attempts to retrieve the
     * resulting transliterator.  That is, if <code>getID()</code>
     * returns "A-B", then this method will return the result of
     * <code>getInstance("B-A")</code>, or <code>null</code> if that
     * call fails.
     *
     * <p>This method does not take filtering into account.  The
     * returned transliterator will have no filter.
     *
     * <p>Subclasses with knowledge of their inverse may wish to
     * override this method.
     *
     * @return a transliterator that is an inverse, not necessarily
     * exact, of this transliterator, or <code>null</code> if no such
     * transliterator is registered.
     * @deprecated Remove after Aug 2002 use factory mehod that takes UErrorCode
     */
    inline Transliterator* createInverse() const;

protected:
    /**
     * Method for subclasses to use to obtain a character in the given
     * string, with filtering.  If the character at the given offset
     * is excluded by this transliterator's filter, then U+FFFE is returned.
     *
     * <p><b>Note:</b> Most subclasses that implement
     * handleTransliterator() will <em>not</em> want to use this
     * method, since characters they see are already filtered.  Only
     * subclasses with special requirements, such as those overriding
     * filteredTransliterate(), should need this method.
     *
     * @deprecated the new architecture provides filtering at the top
     * level.  This method will be removed Aug 2002.
     */
    UChar filteredCharAt(const Replaceable& text, int32_t i) const;

#endif
};

inline int32_t Transliterator::getMaximumContextLength(void) const {
    return maximumContextLength;
}

inline void Transliterator::setID(const UnicodeString& id) {
    ID = id;
}

inline Transliterator::Token Transliterator::integerToken(int32_t i) {
    Token t;
    t.integer = i;
    return t;
}

inline Transliterator::Token Transliterator::pointerToken(void* p) {
    Token t;
    t.pointer = p;
    return t;
}

/**
 * Definitions for deprecated API
 * @deprecated Remove after Aug 2002
 */
#ifdef U_USE_DEPRECATED_TRANSLITERATOR_API

inline Transliterator* Transliterator::createInstance(const UnicodeString& ID, 
                                                      UTransDirection dir,
                                                      UParseError* parseError){
        UErrorCode status = U_ZERO_ERROR;
        UParseError error;
        if(parseError == NULL){
            parseError = &error;
        }
        return Transliterator::createInstance(ID,dir,*parseError,status);
    }

inline Transliterator* Transliterator::createInverse() const{

    UErrorCode status = U_ZERO_ERROR;
    return createInverse(status);
}

#endif

U_NAMESPACE_END

#endif

