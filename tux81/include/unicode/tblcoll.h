/*
******************************************************************************
* Copyright (C) 1996-2001, International Business Machines Corporation and
* others. All Rights Reserved.
******************************************************************************
*/

/**
* File tblcoll.h
*
* Created by: Helena Shih
*
* Modification History:
*
*  Date        Name        Description
*  2/5/97      aliu        Added streamIn and streamOut methods.  Added
*                          constructor which reads RuleBasedCollator object from
*                          a binary file.  Added writeToFile method which streams
*                          RuleBasedCollator out to a binary file.  The streamIn
*                          and streamOut methods use istream and ostream objects
*                          in binary mode.
*  2/12/97     aliu        Modified to use TableCollationData sub-object to
*                          hold invariant data.
*  2/13/97     aliu        Moved several methods into this class from Collation.
*                          Added a private RuleBasedCollator(Locale&) constructor,
*                          to be used by Collator::createDefault().  General
*                          clean up.
*  2/20/97     helena      Added clone, operator==, operator!=, operator=, and copy
*                          constructor and getDynamicClassID.
*  3/5/97      aliu        Modified constructFromFile() to add parameter
*                          specifying whether or not binary loading is to be
*                          attempted.  This is required for dynamic rule loading.
* 05/07/97     helena      Added memory allocation error detection.
*  6/17/97     helena      Added IDENTICAL strength for compare, changed getRules to
*                          use MergeCollation::getPattern.
*  6/20/97     helena      Java class name change.
*  8/18/97     helena      Added internal API documentation.
* 09/03/97     helena      Added createCollationKeyValues().
* 02/10/98     damiba      Added compare with "length" parameter
* 08/05/98     erm         Synched with 1.2 version of RuleBasedCollator.java
* 04/23/99     stephen     Removed EDecompositionMode, merged with
*                          Normalizer::EMode
* 06/14/99     stephen     Removed kResourceBundleSuffix
* 11/02/99     helena      Collator performance enhancements.  Eliminates the
*                          UnicodeString construction and special case for NO_OP.
* 11/23/99     srl         More performance enhancements. Updates to NormalizerIterator
*                          internal state management.
* 12/15/99     aliu        Update to support Thai collation.  Move NormalizerIterator
*                          to implementation file.
* 01/29/01     synwee      Modified into a C++ wrapper which calls C API
*                          (ucol.h)
*/

#ifndef TBLCOLL_H
#define TBLCOLL_H

#include "unicode/coll.h"
#include "unicode/sortkey.h"
#include "unicode/normlzr.h"

U_NAMESPACE_BEGIN

class StringSearch;
class CollationElementIterator;

/**
 * The RuleBasedCollator class provides the simple implementation of
 * Collator, using data-driven tables. The user can create a customized
 * table-based collation.
 * <P>
 * <em>Important: </em>The ICU collation service has been reimplemented 
 * in order to achieve better performance and UCA compliance. 
 * For details, see the 
 * <a href="http://oss.software.ibm.com/cvs/icu/~checkout~/icuhtml/design/collation/ICU_collation_design.htm">
 * collation design document</a>.
 * <p>
 * RuleBasedCollator is a thin C++ wrapper over the C implementation.
 * <p>
 * For more information about the collation service see 
 * <a href="http://oss.software.ibm.com/icu/userguide/Collate_Intro.html">the users guide</a>.
 * <p>
 * Collation service provides correct sorting orders for most locales supported in ICU. 
 * If specific data for a locale is not available, the orders eventually falls back
 * to the <a href="http://www.unicode.org/unicode/reports/tr10/">UCA sort order</a>. 
 * <p>
 * Sort ordering may be customized by providing your own set of rules. For more on
 * this subject see the <a href="http://oss.software.ibm.com/icu/userguide/Collate_Customization.html">
 * Collation customization</a> section of the users guide.
 * <p>
 * @see        Collator
 * @version    2.0 11/15/2001
 */
class U_I18N_API RuleBasedCollator : public Collator
{
public:

  // constructor -------------------------------------------------------------

  /**
   * RuleBasedCollator constructor. This takes the table rules and builds a
   * collation table out of them. Please see RuleBasedCollator class
   * description for more details on the collation rule syntax.
   * @param rules the collation rules to build the collation table from.
   * @param status reporting a success or an error.
   * @see Locale
   * @stable
   */
    RuleBasedCollator(const UnicodeString& rules, UErrorCode& status);

  /**
   * RuleBasedCollator constructor. This takes the table rules and builds a
   * collation table out of them. Please see RuleBasedCollator class
   * description for more details on the collation rule syntax.
   * @param rules the collation rules to build the collation table from.
   * @param collationStrength default strength for comparison
   * @param status reporting a success or an error.
   * @see Locale
   * @stable
   */
  RuleBasedCollator(const UnicodeString& rules,
                       ECollationStrength collationStrength,
                       UErrorCode& status);

  /**
   * RuleBasedCollator constructor. This takes the table rules and builds a
   * collation table out of them. Please see RuleBasedCollator class
   * description for more details on the collation rule syntax.
   * @param rules the collation rules to build the collation table from.
   * @param decompositionMode the normalisation mode
   * @param status reporting a success or an error.
   * @see Locale
   * @stable
   */
  RuleBasedCollator(const UnicodeString& rules,
                    UColAttributeValue decompositionMode,
                    UErrorCode& status);

  /**
   * RuleBasedCollator constructor. This takes the table rules and builds a
   * collation table out of them. Please see RuleBasedCollator class
   * description for more details on the collation rule syntax.
   * @param rules the collation rules to build the collation table from.
   * @param collationStrength default strength for comparison
   * @param decompositionMode the normalisation mode
   * @param status reporting a success or an error.
   * @see Locale
   * @stable
   */
  RuleBasedCollator(const UnicodeString& rules,
                    ECollationStrength collationStrength,
                    UColAttributeValue decompositionMode,
                    UErrorCode& status);

  /**
   * Copy constructor.
   * @param the RuleBasedCollator object to be copied
   * @see Locale
   * @stable
   */
    RuleBasedCollator(const RuleBasedCollator& other);

  // destructor --------------------------------------------------------------

  /**
   * Destructor.
   * @stable
   */
    virtual ~RuleBasedCollator();

  // public methods ----------------------------------------------------------

  /**
   * Assignment operator.
   * @param other other RuleBasedCollator object to compare with.
   * @stable
   */
    RuleBasedCollator& operator=(const RuleBasedCollator& other);

  /**
   * Returns true if argument is the same as this object.
   * @param other Collator object to be compared.
   * @return true if arguments is the same as this object.
   * @stable
   */
  virtual UBool operator==(const Collator& other) const;

  /**
   * Returns true if argument is not the same as this object.
   * @param other Collator object to be compared
   * @return returns true if argument is not the same as this object.
   * @stable
   */
  virtual UBool operator!=(const Collator& other) const;

  /**
   * Makes a deep copy of the object.
   * The caller owns the returned object.
   * @return the cloned object.
   * @stable
   */
  virtual Collator* clone(void) const;

  /**
   * Creates a collation element iterator for the source string. The caller of
   * this method is responsible for the memory management of the return
   * pointer.
   * @param source the string over which the CollationElementIterator will
   *        iterate.
   * @return the collation element iterator of the source string using this as
   *         the based Collator.
   * @draft ICU 1.8
   */
    virtual CollationElementIterator* createCollationElementIterator(
                                           const UnicodeString& source) const;

  /**
   * Creates a collation element iterator for the source. The caller of this
   * method is responsible for the memory management of the returned pointer.
   * @param source the CharacterIterator which produces the characters over
   *        which the CollationElementItgerator will iterate.
   * @return the collation element iterator of the source using this as the
   *         based Collator.
   * @draft ICU 1.8
   */
  virtual CollationElementIterator* createCollationElementIterator(
                                       const CharacterIterator& source) const;

  /**
   * Compares a range of character data stored in two different strings based
   * on the collation rules. Returns information about whether a string is
   * less than, greater than or equal to another string in a language.
   * This can be overriden in a subclass.
   * @param source the source string.
   * @param target the target string to be compared with the source string.
   * @return the comparison result. GREATER if the source string is greater
   *         than the target string, LESS if the source is less than the
   *         target. Otherwise, returns EQUAL.
   * @stable
   */
  virtual EComparisonResult compare(const UnicodeString& source,
                                    const UnicodeString& target) const;


  /**
   * Compares a range of character data stored in two different strings based
   * on the collation rules up to the specified length. Returns information
   * about whether a string is less than, greater than or equal to another
   * string in a language. This can be overriden in a subclass.
   * @param source the source string.
   * @param target the target string to be compared with the source string.
   * @param length compares up to the specified length
   * @return the comparison result. GREATER if the source string is greater
   *         than the target string, LESS if the source is less than the
   *         target. Otherwise, returns EQUAL.
   * @stable
   */
  virtual EComparisonResult compare(const UnicodeString& source,
                                    const UnicodeString&  target,
                                    int32_t length) const;

  /**
   * The comparison function compares the character data stored in two
   * different string arrays. Returns information about whether a string array
   * is less than, greater than or equal to another string array.
   * <p>Example of use:
   * <pre>
   * .       UChar ABC[] = {0x41, 0x42, 0x43, 0};  // = "ABC"
   * .       UChar abc[] = {0x61, 0x62, 0x63, 0};  // = "abc"
   * .       UErrorCode status = U_ZERO_ERROR;
   * .       Collator *myCollation =
   * .                         Collator::createInstance(Locale::US, status);
   * .       if (U_FAILURE(status)) return;
   * .       myCollation->setStrength(Collator::PRIMARY);
   * .       // result would be Collator::EQUAL ("abc" == "ABC")
   * .       // (no primary difference between "abc" and "ABC")
   * .       Collator::EComparisonResult result =
   * .                             myCollation->compare(abc, 3, ABC, 3);
   * .       myCollation->setStrength(Collator::TERTIARY);
   * .       // result would be Collator::LESS ("abc" &lt;&lt;&lt; "ABC")
   * .       // (with tertiary difference between "abc" and "ABC")
   * .       result =  myCollation->compare(abc, 3, ABC, 3);
   * </pre>
   * @param source the source string array to be compared with.
   * @param sourceLength the length of the source string array. If this value
   *        is equal to -1, the string array is null-terminated.
   * @param target the string that is to be compared with the source string.
   * @param targetLength the length of the target string array. If this value
   *        is equal to -1, the string array is null-terminated.
   * @return Returns a byte value. GREATER if source is greater than target;
   *         EQUAL if source is equal to target; LESS if source is less than
   *         target
   * @draft ICU 1.8
   */
  virtual EComparisonResult compare(const UChar* source, int32_t sourceLength,
                                    const UChar* target, int32_t targetLength)
                                    const;

  /**
  * Transforms a specified region of the string into a series of characters
  * that can be compared with CollationKey.compare. Use a CollationKey when
  * you need to do repeated comparisions on the same string. For a single
  * comparison the compare method will be faster.
  * @param source the source string.
  * @param key the transformed key of the source string.
  * @param status the error code status.
  * @return the transformed key.
  * @see CollationKey
  * @stable
  */
  virtual CollationKey& getCollationKey(const UnicodeString& source,
                                        CollationKey& key,
                                        UErrorCode& status) const;

  /**
  * Transforms a specified region of the string into a series of characters
  * that can be compared with CollationKey.compare. Use a CollationKey when
  * you need to do repeated comparisions on the same string. For a single
  * comparison the compare method will be faster.
  * @param source the source string.
  * @param key the transformed key of the source string.
  * @param status the error code status.
  * @return the transformed key.
  * @see CollationKey
  * @stable
  */
  virtual CollationKey& getCollationKey(const UChar *source,
                                        int32_t sourceLength,
                                        CollationKey& key,
                                        UErrorCode& status) const;

  /**
   * Generates the hash code for the rule-based collation object.
   * @return the hash code.
   * @stable
   */
  virtual int32_t hashCode(void) const;

  /**
  * Gets the locale of the Collator
  * @param type can be either requested, valid or actual locale. For more
  *             information see the definition of ULocDataLocaleType in
  *             uloc.h
  * @return locale where the collation data lives. If the collator
  *         was instantiated from rules, locale is empty.
  * @draft ICU 2.1
  */
  virtual const Locale getLocale(ULocDataLocaleType type, UErrorCode& status) const;

  /**
   * Gets the table-based rules for the collation object.
   * @return returns the collation rules that the table collation object was
   *         created from.
   * @stable
   */
  const UnicodeString& getRules(void) const;

  /**
   * Gets the version information for a Collator. 
   * @param info the version # information, the result will be filled in
   * @stable
   */
  virtual void getVersion(UVersionInfo info) const;

  /**
   * Return the maximum length of any expansion sequences that end with the
   * specified comparison order.
   * @param order a collation order returned by previous or next.
   * @return maximum size of the expansion sequences ending with the collation
   *         element or 1 if collation element does not occur at the end of
   *         any expansion sequence
   * @see CollationElementIterator#getMaxExpansion
   * @stable
   */
  int32_t getMaxExpansion(int32_t order) const;

  /**
   * Returns a unique class ID POLYMORPHICALLY. Pure virtual override. This
   * method is to implement a simple version of RTTI, since not all C++
   * compilers support genuine RTTI. Polymorphic operator==() and clone()
   * methods call this method.
   * @return The class ID for this object. All objects of a given class have
   *         the same class ID. Objects of other classes have different class
   *         IDs.
   * @stable
   */
  virtual UClassID getDynamicClassID(void) const
  {
    return RuleBasedCollator::getStaticClassID();
  }

  /**
   * Returns the class ID for this class. This is useful only for comparing to
   * a return value from getDynamicClassID(). For example:
   * <pre>
   * Base* polymorphic_pointer = createPolymorphicObject();
   * if (polymorphic_pointer->getDynamicClassID() ==
   *                                          Derived::getStaticClassID()) ...
   * </pre>
   * @return The class ID for all objects of this class.
   * @stable
   */
  static UClassID getStaticClassID(void)
  {
    return (UClassID)&fgClassID;
  }

  /**
   * Returns the binary format of the class's rules. The format is that of
   * .col files.
   * @param length Returns the length of the data, in bytes
   * @param status the error code status.
   * @return memory, owned by the caller, of size 'length' bytes.
   * @draft ICU 1.8
   */
  uint8_t *cloneRuleData(int32_t &length, UErrorCode &status);

  /**
   * Returns current rules. Delta defines whether full rules are returned or
   * just the tailoring.
   * @param delta one of UCOL_TAILORING_ONLY, UCOL_FULL_RULES.
   * @param buffer UnicodeString to store the result rules
   * @draft ICU 1.8
   */
  void getRules(UColRuleOption delta, UnicodeString &buffer);

  /**
   * Universal attribute setter
   * @param attr attribute type
   * @param value attribute value
   * @param status to indicate whether the operation went on smoothly or there were errors
   * @draft ICU 1.8
   */
  virtual void setAttribute(UColAttribute attr, UColAttributeValue value,
                            UErrorCode &status);

  /**
   * Universal attribute getter.
   * @param attr attribute type
   * @param status to indicate whether the operation went on smoothly or there were errors
   * @return attribute value
   * @draft ICU 1.8
   */
  virtual UColAttributeValue getAttribute(UColAttribute attr,
                                          UErrorCode &status);

  /** 
   * Sets the variable top to a collation element value of a string supplied. 
   * @param varTop one or more (if contraction) UChars to which the variable top should be set
   * @param len length of variable top string. If -1 it is considered to be zero terminated.
   * @param status error code. If error code is set, the return value is undefined. Errors set by this function are: <br>
   *    U_CE_NOT_FOUND_ERROR if more than one character was passed and there is no such a contraction<br>
   *    U_PRIMARY_TOO_LONG_ERROR if the primary for the variable top has more than two bytes
   * @return a 32 bit value containing the value of the variable top in upper 16 bits. Lower 16 bits are undefined
   * @draft ICU 2.0
   */
  virtual uint32_t setVariableTop(const UChar *varTop, int32_t len, UErrorCode &status);

  /** 
   * Sets the variable top to a collation element value of a string supplied. 
   * @param varTop an UnicodeString size 1 or more (if contraction) of UChars to which the variable top should be set
   * @param status error code. If error code is set, the return value is undefined. Errors set by this function are: <br>
   *    U_CE_NOT_FOUND_ERROR if more than one character was passed and there is no such a contraction<br>
   *    U_PRIMARY_TOO_LONG_ERROR if the primary for the variable top has more than two bytes
   * @return a 32 bit value containing the value of the variable top in upper 16 bits. Lower 16 bits are undefined
   * @draft ICU 2.0
   */
  virtual uint32_t setVariableTop(const UnicodeString varTop, UErrorCode &status);

  /** 
   * Sets the variable top to a collation element value supplied. Variable top is set to the upper 16 bits. 
   * Lower 16 bits are ignored.
   * @param varTop CE value, as returned by setVariableTop or ucol)getVariableTop
   * @param status error code (not changed by function)
   * @draft ICU 2.0
   */
  virtual void setVariableTop(const uint32_t varTop, UErrorCode &status);

  /** 
   * Gets the variable top value of a Collator. 
   * Lower 16 bits are undefined and should be ignored.
   * @param status error code (not changed by function). If error code is set, the return value is undefined.
   * @draft ICU 2.0
   */
  virtual uint32_t getVariableTop(UErrorCode &status) const;

  /**
   * Thread safe cloning operation.
   * @return pointer to the new clone, user should remove it.
   * @draft ICU 1.8
   */
  virtual Collator* safeClone(void);

  /**
   * Get the sort key as an array of bytes from an UnicodeString.
   * @param source string to be processed.
   * @param result buffer to store result in. If NULL, number of bytes needed
   *        will be returned.
   * @param resultLength length of the result buffer. If if not enough the
   *        buffer will be filled to capacity.
   * @return Number of bytes needed for storing the sort key
   */
  virtual int32_t getSortKey(const UnicodeString& source, uint8_t *result,
                             int32_t resultLength) const;

  /**
   * Get the sort key as an array of bytes from an UChar buffer.
   * @param source string to be processed.
   * @param sourceLength length of string to be processed. If -1, the string
   *        is 0 terminated and length will be decided by the function.
   * @param result buffer to store result in. If NULL, number of bytes needed
   *        will be returned.
   * @param resultLength length of the result buffer. If if not enough the
   *        buffer will be filled to capacity.
   * @return Number of bytes needed for storing the sort key
   * @draft ICU 1.8
   */
  virtual int32_t getSortKey(const UChar *source, int32_t sourceLength,
                             uint8_t *result, int32_t resultLength) const;

  /**
  * Determines the minimum strength that will be use in comparison or
  * transformation.
  * <p>E.g. with strength == SECONDARY, the tertiary difference is ignored
  * <p>E.g. with strength == PRIMARY, the secondary and tertiary difference
  * are ignored.
  * @return the current comparison level.
  * @see RuleBasedCollator#setStrength
  * @stable
  */
  virtual ECollationStrength getStrength(void) const;

  /**
  * Sets the minimum strength to be used in comparison or transformation.
  * @see RuleBasedCollator#getStrength
  * @param newStrength the new comparison level.
  * @stable
  */
  virtual void setStrength(ECollationStrength newStrength);

  // deprecated functions ---------------------------------------------------

  /**
   * RuleBasedCollator constructor. This takes the table rules and builds a
   * collation table out of them. Please see RuleBasedCollator class
   * description for more details on the collation rule syntax.
   * @param rules the collation rules to build the collation table from.
   * @param decompositionMode the normalisation mode
   * @param status reporting a success or an error.
   * @see Locale
   * @deprecated To be removed after 2002-sep-30, specify the decomposition mode with a UColAttributeValue.
   */
  RuleBasedCollator(const UnicodeString& rules,
                    Normalizer::EMode decompositionMode,
                    UErrorCode& status);

  /**
   * RuleBasedCollator constructor. This takes the table rules and builds a
   * collation table out of them. Please see RuleBasedCollator class
   * description for more details on the collation rule syntax.
   * @param rules the collation rules to build the collation table from.
   * @param collationStrength default strength for comparison
   * @param decompositionMode the normalisation mode
   * @param status reporting a success or an error.
   * @see Locale
   * @deprecated To be removed after 2002-sep-30, specify the decomposition mode with a UColAttributeValue.
   */
  RuleBasedCollator(const UnicodeString& rules,
                    ECollationStrength collationStrength,
                    Normalizer::EMode decompositionMode,
                    UErrorCode& status);

  /**
  * Set the decomposition mode of the Collator object. success is equal to
  * U_ILLEGAL_ARGUMENT_ERROR if error occurs.
  * @param the new decomposition mode
  * @see Collator#getDecomposition
  * @deprecated To be removed after 2002-sep-30; use setAttribute().
  */
  virtual void setDecomposition(Normalizer::EMode  mode);

  /**
  * Get the decomposition mode of the Collator object.
  * @return the decomposition mode
  * @see Collator#setDecomposition
  * @deprecated To be removed after 2002-sep-30; use getAttribute().
  */
  virtual Normalizer::EMode getDecomposition(void) const;

private:

  // private static constants -----------------------------------------------

  static const int32_t UNMAPPED;
  static const int32_t CHARINDEX;  // need look up in .commit()
  static const int32_t EXPANDCHARINDEX; // Expand index follows
  static const int32_t CONTRACTCHARINDEX;  // contract indexes follow

  static const int32_t PRIMARYORDERINCREMENT;
  static const int32_t SECONDARYORDERINCREMENT;
  static const int32_t TERTIARYORDERINCREMENT;
  static const int32_t PRIMARYORDERMASK;
  static const int32_t SECONDARYORDERMASK;
  static const int32_t TERTIARYORDERMASK;
  static const int32_t IGNORABLEMASK;
  static const int32_t PRIMARYDIFFERENCEONLY;
  static const int32_t SECONDARYDIFFERENCEONLY;
  static const int32_t PRIMARYORDERSHIFT;
  static const int32_t SECONDARYORDERSHIFT;

  static const int32_t COLELEMENTSTART;
  static const int32_t PRIMARYLOWZEROMASK;
  static const int32_t RESETSECONDARYTERTIARY;
  static const int32_t RESETTERTIARY;

  static const int32_t PRIMIGNORABLE;

  static const int16_t FILEID;
  static const char    kFilenameSuffix[];

  // private static variables -----------------------------------------------

  /**
  * static class id
  */
  static const char fgClassID;

  // private data members ---------------------------------------------------

  UBool dataIsOwned;

  /**
  * c struct for collation. All initialisation for it has to be done through
  * setUCollator().
  */
  UCollator *ucollator;

  /**
  * Rule UnicodeString
  */
  UnicodeString *urulestring;

  // friend classes --------------------------------------------------------

  /**
  * Used to iterate over collation elements in a character source.
  */
  friend class CollationElementIterator;

  /**
  * Collator ONLY needs access to RuleBasedCollator(const Locale&,
  *                                                       UErrorCode&)
  */
  friend class Collator;

  /**
  * Searching over collation elements in a character source
  */
  friend class StringSearch;

  // private constructors --------------------------------------------------

  /**
   * Default constructor
   */
  RuleBasedCollator();

  /**
  * Constructor that takes in a UCollator struct
  * @param collator UCollator struct
  */
  RuleBasedCollator(UCollator *collator, UnicodeString *rule);

  /**
   * RuleBasedCollator constructor. This constructor takes a locale. The
   * only caller of this class should be Collator::createInstance(). If
   * createInstance() happens to know that the requested locale's collation is
   * implemented as a RuleBasedCollator, it can then call this constructor.
   * OTHERWISE IT SHOULDN'T, since this constructor ALWAYS RETURNS A VALID
   * COLLATION TABLE. It does this by falling back to defaults.
   * @param desiredLocale locale used
   * @param status error code status
   */
  RuleBasedCollator(const Locale& desiredLocale, UErrorCode& status);

  /** common constructor implementation */
  void
  construct(const UnicodeString& rules,
            UColAttributeValue collationStrength,
            UColAttributeValue decompositionMode,
            UErrorCode& status);

  // private methods -------------------------------------------------------

  /**
  * Creates the c struct for ucollator
  * @param locale desired locale
  * @param status error status
  */
  void setUCollator(const Locale& locale, UErrorCode& status);

  /**
  * Creates the c struct for ucollator
  * @param locale desired locale name
  * @param status error status
  */
  void setUCollator(const char* locale, UErrorCode& status);

  /**
  * Creates the c struct for ucollator
  * @param collator new ucollator data
  */
  void setUCollator(UCollator *collator);

  /**
  * Creates the c struct for ucollator. This used internally by StringSearch.
  * Hence the responsibility of cleaning up the ucollator is not done by
  * this RuleBasedCollator. The isDataOwned flag is set to FALSE.
  * @param collator new ucollator data
  * @param rules corresponding collation rules
  */
  void setUCollator(UCollator *collator, UnicodeString *rules);

  /**
  * Get UCollator data struct. Used only by StringSearch.
  * @return UCollator data struct
  */
  const UCollator * getUCollator();

  /**
  * Converts C's UCollationResult to EComparisonResult
  * @param result member of the enum UComparisonResult
  * @return EComparisonResult equivalent of UCollationResult
  */
  Collator::EComparisonResult getEComparisonResult(
                                          const UCollationResult &result) const;

  /**
  * Converts C's UCollationStrength to ECollationStrength
  * @param strength member of the enum UCollationStrength
  * @return ECollationStrength equivalent of UCollationStrength
  */
  Collator::ECollationStrength getECollationStrength(
                                      const UCollationStrength &strength) const;

  /**
  * Converts C++'s ECollationStrength to UCollationStrength
  * @param strength member of the enum ECollationStrength
  * @return UCollationStrength equivalent of ECollationStrength
  */
  UCollationStrength getUCollationStrength(
    const Collator::ECollationStrength &strength) const;
};

// inline method implementation ---------------------------------------------

inline UBool RuleBasedCollator::operator!=(const Collator& other) const
{
  return !(*this == other);
}

inline void RuleBasedCollator::setUCollator(const char *locale,
                                               UErrorCode &status)
{
  if (U_FAILURE(status))
    return;
  if (ucollator && dataIsOwned)
    ucol_close(ucollator);
  ucollator = ucol_open(locale, &status);
}

inline void RuleBasedCollator::setUCollator(const Locale &locale,
                                               UErrorCode &status)
{
  setUCollator(locale.getName(), status);
}

inline void RuleBasedCollator::setUCollator(UCollator *collator)
{
  if (ucollator && dataIsOwned) {
    ucol_close(ucollator);
  }
  ucollator = collator;
}

inline void RuleBasedCollator::setUCollator(UCollator     *collator, 
                                            UnicodeString *rules)
{
    if (ucollator && dataIsOwned) {
        ucol_close(ucollator);
        delete urulestring;
    }
    ucollator   = collator;
    urulestring = rules;
    dataIsOwned = FALSE;
}

inline const UCollator * RuleBasedCollator::getUCollator()
{
    return ucollator;
}

inline Collator::EComparisonResult RuleBasedCollator::getEComparisonResult(
                                           const UCollationResult &result) const
{
  switch (result)
  {
  case UCOL_LESS :
    return Collator::LESS;
  case UCOL_EQUAL :
    return Collator::EQUAL;
  default :
    return Collator::GREATER;
  }
}

inline Collator::ECollationStrength RuleBasedCollator::getECollationStrength(
                                       const UCollationStrength &strength) const
{
  switch (strength)
  {
  case UCOL_PRIMARY :
    return Collator::PRIMARY;
  case UCOL_SECONDARY :
    return Collator::SECONDARY;
  case UCOL_TERTIARY :
    return Collator::TERTIARY;
  case UCOL_QUATERNARY :
    return Collator::QUATERNARY;   
  default :
    return Collator::IDENTICAL;
  }
}

inline UCollationStrength RuleBasedCollator::getUCollationStrength(
                             const Collator::ECollationStrength &strength) const
{
  switch (strength)
  {
  case Collator::PRIMARY :
    return UCOL_PRIMARY;
  case Collator::SECONDARY :
    return UCOL_SECONDARY;
  case Collator::TERTIARY :
    return UCOL_TERTIARY;
  case Collator::QUATERNARY :
    return UCOL_QUATERNARY;
  default :
    return UCOL_IDENTICAL;
  }
}

U_NAMESPACE_END

#endif
