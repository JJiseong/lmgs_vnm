/*
* Copyright (C) {1997-2001}, International Business Machines Corporation and others. All Rights Reserved.
*******************************************************************************
*
* File SMPDTFMT.H
*
* Modification History:
*
*   Date        Name        Description
*   02/19/97    aliu        Converted from java.
*   07/09/97    helena      Make ParsePosition into a class.
*   07/21/98    stephen     Added GMT_PLUS, GMT_MINUS
*                            Changed setTwoDigitStartDate to set2DigitYearStart
*                            Changed getTwoDigitStartDate to get2DigitYearStart
*                            Removed subParseLong
*                            Removed getZoneIndex (added in DateFormatSymbols)
*   06/14/99    stephen     Removed fgTimeZoneDataSuffix
*   10/14/99    aliu        Updated class doc to describe 2-digit year parsing
*                           {j28 4182066}.
*******************************************************************************
*/

#ifndef SMPDTFMT_H
#define SMPDTFMT_H

#include "unicode/utypes.h"
#include "unicode/datefmt.h"

U_NAMESPACE_BEGIN

class DateFormatSymbols;
class DateFormat;

/**
 * SimpleDateFormat is a concrete class for formatting and parsing dates in a
 * language-independent manner. It allows for formatting (millis -> text),
 * parsing (text -> millis), and normalization. Formats/Parses a date or time,
 * which is the standard milliseconds since 24:00 GMT, Jan 1, 1970.
 * <P>
 * Clients are encouraged to create a date-time formatter using DateFormat::getInstance(),
 * getDateInstance(), getDateInstance(), or getDateTimeInstance() rather than
 * explicitly constructing an instance of SimpleDateFormat.  This way, the client
 * is guaranteed to get an appropriate formatting pattern for whatever locale the
 * program is running in.  However, if the client needs something more unusual than
 * the default patterns in the locales, he can construct a SimpleDateFormat directly
 * and give it an appropriate pattern (or use one of the factory methods on DateFormat
 * and modify the pattern after the fact with toPattern() and applyPattern().
 * <P>
 * Date/Time format syntax:
 * <P>
 * The date/time format is specified by means of a string time pattern. In this
 * pattern, all ASCII letters are reserved as pattern letters, which are defined
 * as the following:
 * <pre>
 * \code
 *    Symbol   Meaning                 Presentation       Example
 *    ------   -------                 ------------       -------
 *    G        era designator          (Text)             AD
 *    y        year                    (Number)           1996
 *    Y        year/week of year       (Number)           1996
 *    M        month in year           (Text & Number)    July & 07
 *    d        day in month            (Number)           10
 *    h        hour in am/pm (1~12)    (Number)           12
 *    H        hour in day (0~23)      (Number)           0
 *    m        minute in hour          (Number)           30
 *    s        second in minute        (Number)           55
 *    S        millisecond             (Number)           978
 *    E        day of week             (Text)             Tuesday
 *    e        day of week/local (1~7) (Number)           2
 *    D        day of year             (Number)           189
 *    F        day of week in month    (Number)           2 (2nd Wed in July)
 *    w        week in year            (Number)           27
 *    W        week in month           (Number)           2
 *    a        am/pm marker            (Text)             PM
 *    k        hour in day (1~24)      (Number)           24
 *    K        hour in am/pm (0~11)    (Number)           0
 *    z        time zone               (Text)             Pacific Standard Time
 *    '        escape for text
 *    ''       single quote                               '
 * \endcode
 * </pre>
 * The count of pattern letters determine the format.
 * <P>
 * (Text): 4 or more, use full form, &lt;4, use short or abbreviated form if it
 * exists. (e.g., "EEEE" produces "Monday", "EEE" produces "Mon")
 * <P>
 * (Number): the minimum number of digits. Shorter numbers are zero-padded to
 * this amount (e.g. if "m" produces "6", "mm" produces "06"). Year is handled
 * specially; that is, if the count of 'y' is 2, the Year will be truncated to 2 digits.
 * (e.g., if "yyyy" produces "1997", "yy" produces "97".)
 * <P>
 * (Text & Number): 3 or over, use text, otherwise use number.  (e.g., "M" produces "1",
 * "MM" produces "01", "MMM" produces "Jan", and "MMMM" produces "January".)
 * <P>
 * Any characters in the pattern that are not in the ranges of ['a'..'z'] and
 * ['A'..'Z'] will be treated as quoted text. For instance, characters
 * like ':', '.', ' ', '#' and '@' will appear in the resulting time text
 * even they are not embraced within single quotes.
 * <P>
 * A pattern containing any invalid pattern letter will result in a failing
 * UErrorCode result during formatting or parsing.
 * <P>
 * Examples using the US locale:
 * <pre>
 * \code
 *    Format Pattern                         Result
 *    --------------                         -------
 *    "yyyy.MM.dd G 'at' HH:mm:ss z"    ->>  1996.07.10 AD at 15:08:56 PDT
 *    "EEE, MMM d, ''yy"                ->>  Wed, July 10, '96
 *    "h:mm a"                          ->>  12:08 PM
 *    "hh 'o''clock' a, zzzz"           ->>  12 o'clock PM, Pacific Daylight Time
 *    "K:mm a, z"                       ->>  0:00 PM, PST
 *    "yyyyy.MMMMM.dd GGG hh:mm aaa"    ->>  1996.July.10 AD 12:08 PM
 * \endcode
 * </pre>
 * Code Sample:
 * <pre>
 * \code
 *     UErrorCode success = U_ZERO_ERROR;
 *     SimpleTimeZone* pdt = new SimpleTimeZone(-8 * 60 * 60 * 1000, "PST");
 *     pdt->setStartRule( Calendar::APRIL, 1, Calendar::SUNDAY, 2*60*60*1000);
 *     pdt->setEndRule( Calendar::OCTOBER, -1, Calendar::SUNDAY, 2*60*60*1000);
 *
 *     // Format the current time.
 *     SimpleDateFormat* formatter
 *         = new SimpleDateFormat ("yyyy.MM.dd G 'at' hh:mm:ss a zzz", success );
 *     GregorianCalendar cal(success);
 *     UDate currentTime_1 = cal.getTime(success);
 *     FieldPosition fp(0);
 *     UnicodeString dateString;
 *     formatter->format( currentTime_1, dateString, fp );
 *     cout << "result: " << dateString << endl;
 *
 *     // Parse the previous string back into a Date.
 *     ParsePosition pp(0);
 *     UDate currentTime_2 = formatter->parse(dateString, pp );
 * \endcode
 * </pre>
 * In the above example, the time value "currentTime_2" obtained from parsing
 * will be equal to currentTime_1. However, they may not be equal if the am/pm
 * marker 'a' is left out from the format pattern while the "hour in am/pm"
 * pattern symbol is used. This information loss can happen when formatting the
 * time in PM.
 *
 * <p>
 * When parsing a date string using the abbreviated year pattern ("y" or "yy"),
 * SimpleDateFormat must interpret the abbreviated year
 * relative to some century.  It does this by adjusting dates to be
 * within 80 years before and 20 years after the time the SimpleDateFormat
 * instance is created. For example, using a pattern of "MM/dd/yy" and a
 * SimpleDateFormat instance created on Jan 1, 1997,  the string
 * "01/11/12" would be interpreted as Jan 11, 2012 while the string "05/04/64"
 * would be interpreted as May 4, 1964.
 * During parsing, only strings consisting of exactly two digits, as defined by
 * <code>Unicode::isDigit()</code>, will be parsed into the default century.
 * Any other numeric string, such as a one digit string, a three or more digit
 * string, or a two digit string that isn't all digits (for example, "-1"), is
 * interpreted literally.  So "01/02/3" or "01/02/003" are parsed, using the
 * same pattern, as Jan 2, 3 AD.  Likewise, "01/02/-3" is parsed as Jan 2, 4 BC.
 *
 * <p>
 * If the year pattern has more than two 'y' characters, the year is
 * interpreted literally, regardless of the number of digits.  So using the
 * pattern "MM/dd/yyyy", "01/11/12" parses to Jan 11, 12 A.D.
 *
 * <P>
 * For time zones that have no names, SimpleDateFormat uses strings GMT+hours:minutes or
 * GMT-hours:minutes.
 * <P>
 * The calendar defines what is the first day of the week, the first week of the
 * year, whether hours are zero based or not (0 vs 12 or 24), and the timezone.
 * There is one common number format to handle all the numbers; the digit count
 * is handled programmatically according to the pattern.
 */
class U_I18N_API SimpleDateFormat: public DateFormat {
public:
    /**
     * Construct a SimpleDateFormat using the default pattern for the default
     * locale.
     * <P>
     * [Note:] Not all locales support SimpleDateFormat; for full generality,
     * use the factory methods in the DateFormat class.
     * @stable
     */
    SimpleDateFormat(UErrorCode& status);

    /**
     * Construct a SimpleDateFormat using the given pattern and the default locale.
     * The locale is used to obtain the symbols used in formatting (e.g., the
     * names of the months), but not to provide the pattern.
     * <P>
     * [Note:] Not all locales support SimpleDateFormat; for full generality,
     * use the factory methods in the DateFormat class.
     * @stable
     */
    SimpleDateFormat(const UnicodeString& pattern,
                     UErrorCode& status);

    /**
     * Construct a SimpleDateFormat using the given pattern and locale.
     * The locale is used to obtain the symbols used in formatting (e.g., the
     * names of the months), but not to provide the pattern.
     * <P>
     * [Note:] Not all locales support SimpleDateFormat; for full generality,
     * use the factory methods in the DateFormat class.
     * @stable
     */
    SimpleDateFormat(const UnicodeString& pattern,
                     const Locale& locale,
                     UErrorCode& status);

    /**
     * Construct a SimpleDateFormat using the given pattern and locale-specific
     * symbol data.  The formatter takes ownership of the DateFormatSymbols object;
     * the caller is no longer responsible for deleting it.
     * @stable
     */
    SimpleDateFormat(const UnicodeString& pattern,
                     DateFormatSymbols* formatDataToAdopt,
                     UErrorCode& status);

    /**
     * Construct a SimpleDateFormat using the given pattern and locale-specific
     * symbol data.  The DateFormatSymbols object is NOT adopted; the caller
     * remains responsible for deleting it.
     * @stable
     */
    SimpleDateFormat(const UnicodeString& pattern,
                     const DateFormatSymbols& formatData,
                     UErrorCode& status);

    /**
     * Copy constructor.
     * @stable
     */
    SimpleDateFormat(const SimpleDateFormat&);

    /**
     * Assignment operator.
     * @stable
     */
    SimpleDateFormat& operator=(const SimpleDateFormat&);

    /**
     * Destructor.
     * @stable
     */
    virtual ~SimpleDateFormat();

    /**
     * Clone this Format object polymorphically. The caller owns the result and
     * should delete it when done.
     * @stable
     */
    virtual Format* clone(void) const;

    /**
     * Return true if the given Format objects are semantically equal. Objects
     * of different subclasses are considered unequal.
     * @stable
     */
    virtual UBool operator==(const Format& other) const;

    /**
     * Format a date or time, which is the standard millis since 24:00 GMT, Jan
     * 1, 1970. Overrides DateFormat pure virtual method.
     * <P>
     * Example: using the US locale: "yyyy.MM.dd e 'at' HH:mm:ss zzz" ->>
     * 1996.07.10 AD at 15:08:56 PDT
     *
     * @param cal           a Calendar set to the date and time to be formatted
     *                      into a date/time string.
     * @param toAppendTo    The result of the formatting operation is appended to this
     *                      string.
     * @param pos           The formatting position. On input: an alignment field,
     *                      if desired. On output: the offsets of the alignment field.
     * @return              A reference to 'toAppendTo'.
     * @draft ICU 2.1
     */
    virtual UnicodeString& format(  Calendar& cal,
                                    UnicodeString& toAppendTo,
                                    FieldPosition& pos) const;

    /**
     * Format a date or time, which is the standard millis since 24:00 GMT, Jan
     * 1, 1970. Overrides DateFormat pure virtual method.
     * <P>
     * Example: using the US locale: "yyyy.MM.dd e 'at' HH:mm:ss zzz" ->>
     * 1996.07.10 AD at 15:08:56 PDT
     *
     * @param obj           A Formattable containing the date-time value to be formatted
     *                      into a date-time string.  If the type of the Formattable
     *                      is a numeric type, it is treated as if it were an
     *                      instance of Date.
     * @param toAppendTo    The result of the formatting operation is appended to this
     *                      string.
     * @param pos           The formatting position. On input: an alignment field,
     *                      if desired. On output: the offsets of the alignment field.
     * @return              A reference to 'toAppendTo'.
     * @stable
     */
    virtual UnicodeString& format(  const Formattable& obj,
                                    UnicodeString& toAppendTo,
                                    FieldPosition& pos,
                                    UErrorCode& status) const;

    /**
     * Redeclared DateFormat method.
     * @draft ICU 2.1
     */
    UnicodeString& format(UDate date,
                          UnicodeString& result,
                          FieldPosition& fieldPosition) const;

    /**
     * Redeclared DateFormat method.
     * @stable
     */
    UnicodeString& format(const Formattable& obj,
                          UnicodeString& result,
                          UErrorCode& status) const;

    /**
     * Redeclared DateFormat method.
     * @stable
     */
    UnicodeString& format(UDate date, UnicodeString& result) const;

    /**
     * Parse a date/time string beginning at the given parse position. For
     * example, a time text "07/10/96 4:5 PM, PDT" will be parsed into a Date
     * that is equivalent to Date(837039928046).
     * <P>
     * By default, parsing is lenient: If the input is not in the form used by
     * this object's format method but can still be parsed as a date, then the
     * parse succeeds. Clients may insist on strict adherence to the format by
     * calling setLenient(false).
     *
     * @param text  The date/time string to be parsed
     * @param pos   On input, the position at which to start parsing; on
     *              output, the position at which parsing terminated, or the
     *              start position if the parse failed.
     * @return      A valid UDate if the input could be parsed.
     * @draft ICU 2.1
     */
    virtual void parse( const UnicodeString& text,
                        Calendar& cal,
                        ParsePosition& pos) const;

    /**
     * Parse a date/time string starting at the given parse position. For
     * example, a time text "07/10/96 4:5 PM, PDT" will be parsed into a Date
     * that is equivalent to Date(837039928046).
     * <P>
     * By default, parsing is lenient: If the input is not in the form used by
     * this object's format method but can still be parsed as a date, then the
     * parse succeeds. Clients may insist on strict adherence to the format by
     * calling setLenient(false).
     *
     * @see DateFormat::setLenient(boolean)
     *
     * @param text  The date/time string to be parsed
     * @param pos   On input, the position at which to start parsing; on
     *              output, the position at which parsing terminated, or the
     *              start position if the parse failed.
     * @return      A valid UDate if the input could be parsed.
     * @stable
     */
    UDate parse( const UnicodeString& text,
                 ParsePosition& pos) const;


    /**
     * Parse a date/time string. For example, a time text "07/10/96 4:5 PM, PDT"
     * will be parsed into a UDate that is equivalent to Date(837039928046).
     * Parsing begins at the beginning of the string and proceeds as far as
     * possible.  Assuming no parse errors were encountered, this function
     * doesn't return any information about how much of the string was consumed
     * by the parsing.  If you need that information, use the version of
     * parse() that takes a ParsePosition.
     *
     * @param text  The date/time string to be parsed
     * @param status Filled in with U_ZERO_ERROR if the parse was successful, and with
     *              an error value if there was a parse error.
     * @return      A valid UDate if the input could be parsed.
     * @stable
     */
    virtual UDate parse( const UnicodeString& text,
                        UErrorCode& status) const;

    /**
     * Set the start UDate used to interpret two-digit year strings.
     * When dates are parsed having 2-digit year strings, they are placed within
     * a assumed range of 100 years starting on the two digit start date.  For
     * example, the string "24-Jan-17" may be in the year 1817, 1917, 2017, or
     * some other year.  SimpleDateFormat chooses a year so that the resultant
     * date is on or after the two digit start date and within 100 years of the
     * two digit start date.
     * <P>
     * By default, the two digit start date is set to 80 years before the current
     * time at which a SimpleDateFormat object is created.
     * @stable
     */
    virtual void set2DigitYearStart(UDate d, UErrorCode& status);

    /**
     * Get the start UDate used to interpret two-digit year strings.
     * When dates are parsed having 2-digit year strings, they are placed within
     * a assumed range of 100 years starting on the two digit start date.  For
     * example, the string "24-Jan-17" may be in the year 1817, 1917, 2017, or
     * some other year.  SimpleDateFormat chooses a year so that the resultant
     * date is on or after the two digit start date and within 100 years of the
     * two digit start date.
     * <P>
     * By default, the two digit start date is set to 80 years before the current
     * time at which a SimpleDateFormat object is created.
     * @stable
     */
    UDate get2DigitYearStart(UErrorCode& status) const;

    /**
     * Return a pattern string describing this date format.
     * @stable
     */
    virtual UnicodeString& toPattern(UnicodeString& result) const;

    /**
     * Return a localized pattern string describing this date format.
     * In most cases, this will return the same thing as toPattern(),
     * but a locale can specify characters to use in pattern descriptions
     * in place of the ones described in this class's class documentation.
     * (Presumably, letters that would be more mnemonic in that locale's
     * language.)  This function would produce a pattern using those
     * letters.
     *
     * @param result    Receives the localized pattern.
     * @param status    Output param set to success/failure code on
     *                  exit. If the pattern is invalid, this will be
     *                  set to a failure result.
     * @stable
     */
    virtual UnicodeString& toLocalizedPattern(UnicodeString& result,
                                              UErrorCode& status) const;

    /**
     * Apply the given unlocalized pattern string to this date format.
     * (i.e., after this call, this formatter will format dates according to
     * the new pattern)
     *
     * @param pattern   The pattern to be applied.
     * @stable
     */
    virtual void applyPattern(const UnicodeString& pattern);

    /**
     * Apply the given localized pattern string to this date format.
     * (see toLocalizedPattern() for more information on localized patterns.)
     *
     * @param pattern   The localized pattern to be applied.
     * @param status    Output param set to success/failure code on
     *                  exit. If the pattern is invalid, this will be
     *                  set to a failure result.
     * @stable
     */
    virtual void applyLocalizedPattern(const UnicodeString& pattern,
                                       UErrorCode& status);

    /**
     * Gets the date/time formatting symbols (this is an object carrying
     * the various strings and other symbols used in formatting: e.g., month
     * names and abbreviations, time zone names, AM/PM strings, etc.)
     * @return a copy of the date-time formatting data associated
     * with this date-time formatter.
     * @stable
     */
    virtual const DateFormatSymbols* getDateFormatSymbols(void) const;

    /**
     * Set the date/time formatting symbols.  The caller no longer owns the
     * DateFormatSymbols object and should not delete it after making this call.
     * @param newFormatData the given date-time formatting data.
     * @stable
     */
    virtual void adoptDateFormatSymbols(DateFormatSymbols* newFormatSymbols);

    /**
     * Set the date/time formatting data.
     * @param newFormatData the given date-time formatting data.
     * @stable
     */
    virtual void setDateFormatSymbols(const DateFormatSymbols& newFormatSymbols);

    /**
     * Return the class ID for this class. This is useful only for comparing to
     * a return value from getDynamicClassID(). For example:
     * <pre>
     * .   Base* polymorphic_pointer = createPolymorphicObject();
     * .   if (polymorphic_pointer->getDynamicClassID() ==
     * .       erived::getStaticClassID()) ...
     * </pre>
     * @return          The class ID for all objects of this class.
     * @stable
     */
    static UClassID getStaticClassID(void) { return (UClassID)&fgClassID; }

    /**
     * Returns a unique class ID POLYMORPHICALLY. Pure virtual override. This
     * method is to implement a simple version of RTTI, since not all C++
     * compilers support genuine RTTI. Polymorphic operator==() and clone()
     * methods call this method.
     *
     * @return          The class ID for this object. All objects of a
     *                  given class have the same class ID.  Objects of
     *                  other classes have different class IDs.
     * @stable
     */
    virtual UClassID getDynamicClassID(void) const { return getStaticClassID(); }

private:
    static const char fgClassID;

    static const char fgDateTimePatternsTag[];   // resource bundle tag for default date and time patterns

    static const UChar fgDefaultPattern[];    // date/time pattern of last resort

    friend class DateFormat;

    /**
     * Gets the index for the given time zone ID to obtain the timezone strings
     * for formatting. The time zone ID is just for programmatic lookup. NOT
     * LOCALIZED!!!
     *
     * @param DateFormatSymbols     a DateFormatSymbols object contianing the time zone names
     * @param ID        the given time zone ID.
     * @return          the index of the given time zone ID.  Returns -1 if
     *                  the given time zone ID can't be located in the
     *                  DateFormatSymbols object.
     * @see SimpleTimeZone
     */
    //int32_t getZoneIndex(const DateFormatSymbols&, const UnicodeString& ID) const;

    void initializeDefaultCentury(void);

    /**
     * Used by the DateFormat factory methods to construct a SimpleDateFormat.
     */
    SimpleDateFormat(EStyle timeStyle, EStyle dateStyle, const Locale& locale, UErrorCode& status);

    /**
     * Construct a SimpleDateFormat for the given locale.  If no resource data
     * is available, create an object of last resort, using hard-coded strings.
     * This is an internal method, called by DateFormat.  It should never fail.
     */
    SimpleDateFormat(const Locale& locale, UErrorCode& status); // Use default pattern

    /**
     * Called by format() to format a single field.
     *
     * @param result    Filled in with the result.
     * @param ch        The format character we encountered in the pattern.
     * @param count     Number of characters in the current pattern symbol (e.g.,
     *                  "yyyy" in the pattern would result in a call to this function
     *                  with ch equal to 'y' and count equal to 4)
     * @param beginOffset   Tells where the text returned by this function will go in
     *                  the finished string.  Used when this function needs to fill
     *                  in a FieldPosition
     * @param pos       The FieldPosition being filled in by the format() call.  If
     *                  this function is formatting the field specfied by pos, it
     *                  will fill in pos will the beginning and ending offsets of the
     *                  field.
     * @param status    Receives a status code, which will be U_ZERO_ERROR if the operation
     *                  succeeds.
     * @return A reference to "result".
     */
    UnicodeString& subFormat(   UnicodeString& result,
                                UChar ch,
                                int32_t count,
                                int32_t beginOffset,
                                FieldPosition& pos,
                                Calendar& cal,
                                UErrorCode& status) const; // in case of illegal argument

    /**
     * Used by subFormat() to format a numeric value.  Fills in "result" with a string
     * representation of "value" having a number of digits between "minDigits" and
     * "maxDigits".  Uses the DateFormat's NumberFormat.
     * @param result    Filled in with the formatted number.
     * @param value     Value to format.
     * @param minDigits Minimum number of digits the result should have
     * @param maxDigits Maximum number of digits the result should have
     * @return A reference to "result".
     */
    UnicodeString& zeroPaddingNumber(UnicodeString& result,
                                     int32_t value,
                                     int32_t minDigits,
                                     int32_t maxDigits) const;

    /**
     * Called by several of the constructors to load pattern data and formatting symbols
     * out of a resource bundle and initialize the locale based on it.
     * @param timeStyle     The time style, as passed to DateFormat::createDateInstance().
     * @param dateStyle     The date style, as passed to DateFormat::createTimeInstance().
     * @param locale        The locale to load the patterns from.
     * @param status        Filled in with an error code if loading the data from the
     *                      resources fails.
     */
    void construct(EStyle timeStyle, EStyle dateStyle, const Locale& locale, UErrorCode& status);

    /**
     * Called by construct() and the various constructors to set up the SimpleDateFormat's
     * Calendar and NumberFormat objects.
     * @param locale    The locale for which we want a Calendar and a NumberFormat.
     * @param statuc    Filled in with an error code if creating either subobject fails.
     */
    void initialize(const Locale& locale, UErrorCode& status);

    /**
     * Private code-size reduction function used by subParse.
     * @param text the time text being parsed.
     * @param start where to start parsing.
     * @param field the date field being parsed.
     * @param data the string array to parsed.
     * @return the new start position if matching succeeded; a negative number
     * indicating matching failure, otherwise.
     */
    int32_t matchString(const UnicodeString& text, int32_t start, Calendar::EDateFields field,
                        const UnicodeString* stringArray, int32_t stringArrayCount, Calendar& cal) const;

    /**
     * Private member function that converts the parsed date strings into
     * timeFields. Returns -start (for ParsePosition) if failed.
     * @param text the time text to be parsed.
     * @param start where to start parsing.
     * @param ch the pattern character for the date field text to be parsed.
     * @param count the count of a pattern character.
     * @param obeyCount if true then the count is strictly obeyed.
     * @return the new start position if matching succeeded; a negative number
     * indicating matching failure, otherwise.
     */
    int32_t subParse(const UnicodeString& text, int32_t& start, UChar ch, int32_t count,
                     UBool obeyCount, UBool ambiguousYear[], Calendar& cal) const;

    /**
     * Parse the given text, at the given position, as a numeric value, using
     * this object's NumberFormat. Return the corresponding long value in the
     * fill-in parameter 'value'. If the parse fails, this method leaves pos
     * unchanged and returns FALSE; otherwise it advances pos and
     * returns TRUE.
     */
    //UBool subParseLong(const UnicodeString& text, ParsePosition& pos, int32_t& value) const;

    /**
     * Translate a pattern, mapping each character in the from string to the
     * corresponding character in the to string. Return an error if the original
     * pattern contains an unmapped character, or if a quote is unmatched.
     * Quoted (single quotes only) material is not translated.
     */
    static void translatePattern(const UnicodeString& originalPattern,
                                UnicodeString& translatedPattern,
                                const UnicodeString& from,
                                const UnicodeString& to,
                                UErrorCode& status);
    /**
     * Given a zone ID, try to locate it in our time zone array. Return the
     * index (row index) of the found time zone, or -1 if we can't find it.
     */
    //int32_t getZoneIndex(const UnicodeString& ID) const;

    /**
     * Sets the starting date of the 100-year window that dates with 2-digit years
     * are considered to fall within.
     */
    void         parseAmbiguousDatesAsAfter(UDate startDate, UErrorCode& status);

    /**
     * Returns the beginning date of the 100-year window that dates with 2-digit years
     * are considered to fall within.
     */
    UDate         internalGetDefaultCenturyStart(void) const;

    /**
     * Returns the first year of the 100-year window that dates with 2-digit years
     * are considered to fall within.
     */
    int32_t          internalGetDefaultCenturyStartYear(void) const;

    /**
     * Initializes the 100-year window that dates with 2-digit years are considered
     * to fall within so that its start date is 80 years before the current time.
     */
    static void  initializeSystemDefaultCentury(void);

    /**
     * Last-resort string to use for "GMT" when constructing time zone strings.
     */
    // For time zones that have no names, use strings GMT+minutes and
    // GMT-minutes. For instance, in France the time zone is GMT+60.
    static const UChar fgGmtPlus[];
    static const UChar fgGmtMinus[];
    static const UChar fgGmt[];

    /**
     * Used to map pattern characters to Calendar field identifiers.
     */
    static const Calendar::EDateFields fgPatternIndexToCalendarField[];

    /**
     * Map index into pattern character string to DateFormat field number
     */
    static const DateFormat::EField fgPatternIndexToDateFormatField[];

    /**
     * The formatting pattern for this formatter.
     */
    UnicodeString       fPattern;

    /**
     * A pointer to an object containing the strings to use in formatting (e.g.,
     * month and day names, AM and PM strings, time zone names, etc.)
     */
    DateFormatSymbols*  fSymbols;   // Owned

    /**
     * If dates have ambiguous years, we map them into the century starting
     * at defaultCenturyStart, which may be any date.  If defaultCenturyStart is
     * set to SYSTEM_DEFAULT_CENTURY, which it is by default, then the system
     * values are used.  The instance values defaultCenturyStart and
     * defaultCenturyStartYear are only used if explicitly set by the user
     * through the API method parseAmbiguousDatesAsAfter().
     */
    UDate                fDefaultCenturyStart;

    /**
     * See documentation for defaultCenturyStart.
     */
    /*transient*/ int32_t   fDefaultCenturyStartYear;

    /**
     * The system maintains a static default century start date.  This is initialized
     * the first time it is used.  Before then, it is set to SYSTEM_DEFAULT_CENTURY to
     * indicate an uninitialized state.  Once the system default century date and year
     * are set, they do not change.
     */
    static UDate         fgSystemDefaultCenturyStart;

    /**
     * See documentation for systemDefaultCenturyStart.
     */
    static int32_t          fgSystemDefaultCenturyStartYear;

    /**
     * Default value that indicates the defaultCenturyStartYear is unitialized
     */
    static const int32_t    fgSystemDefaultCenturyYear;

public:
    /**
     * If a start date is set to this value, that indicates that the system default
     * start is in effect for this instance.
     */
    static const UDate        fgSystemDefaultCentury;
};

inline UDate
SimpleDateFormat::get2DigitYearStart(UErrorCode& /*status*/) const
{
    return fDefaultCenturyStart;
}

inline UnicodeString&
SimpleDateFormat::format(const Formattable& obj,
                         UnicodeString& result,
                         UErrorCode& status) const {
    // Don't use Format:: - use immediate base class only,
    // in case immediate base modifies behavior later.
    return DateFormat::format(obj, result, status);
}

inline UnicodeString&
SimpleDateFormat::format(UDate date,
                         UnicodeString& result,
                         FieldPosition& fieldPosition) const {
    // Don't use Format:: - use immediate base class only,
    // in case immediate base modifies behavior later.
    return DateFormat::format(date, result, fieldPosition);
}

inline UnicodeString&
SimpleDateFormat::format(UDate date, UnicodeString& result) const {
    return DateFormat::format(date, result);
}

U_NAMESPACE_END

#endif // _SMPDTFMT
//eof
