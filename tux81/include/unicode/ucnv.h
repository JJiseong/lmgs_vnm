/*
**********************************************************************
*   Copyright (C) 1999-2001, International Business Machines
*   Corporation and others.  All Rights Reserved.
**********************************************************************
 *  ucnv.h:
 *  External APIs for the ICU's codeset conversion library
 *  Bertrand A. Damiba
 *
 * Modification History:
 *
 *   Date        Name        Description
 *   04/04/99    helena      Fixed internal header inclusion.
 *   05/11/00    helena      Added setFallback and usesFallback APIs.
 *   06/29/2000  helena      Major rewrite of the callback APIs.
 *   12/07/2000  srl         Update of documentation
 */

/**
 * \file
 * \brief C API: Character conversion 
 *
 * <h2>Character Conversion C API </h2>
 *
 */

#ifndef UCNV_H
#define UCNV_H

/** Forward declaring the UConverter structure. @stable */
struct UConverter;

/** @stable */
typedef struct UConverter UConverter;

#include "unicode/utypes.h"
#include "unicode/ucnv_err.h"

U_CDECL_BEGIN

/* maximum length of the converter names */
#define UCNV_MAX_CONVERTER_NAME_LENGTH 60
#define UCNV_MAX_FULL_FILE_NAME_LENGTH (600+UCNV_MAX_CONVERTER_NAME_LENGTH)

#define  UCNV_SI 0x0F           /*Shift in for EBDCDIC_STATEFUL and iso2022 states */
#define  UCNV_SO 0x0E           /*Shift out for EBDCDIC_STATEFUL and iso2022 states */

/**
 * Enum for specifying basic types of converters
 * @see ucnv_getType
 * @stable
 */
typedef enum {
    UCNV_UNSUPPORTED_CONVERTER = -1,
    UCNV_SBCS = 0,
    UCNV_DBCS = 1,
    UCNV_MBCS = 2,
    UCNV_LATIN_1 = 3,
    UCNV_UTF8 = 4,
    UCNV_UTF16_BigEndian = 5,
    UCNV_UTF16_LittleEndian = 6,
    UCNV_UTF32_BigEndian = 7,
    UCNV_UTF32_LittleEndian = 8,
    UCNV_EBCDIC_STATEFUL = 9,
    UCNV_ISO_2022 = 10,

    UCNV_LMBCS_1 = 11,
    UCNV_LMBCS_2, 
    UCNV_LMBCS_3,
    UCNV_LMBCS_4,
    UCNV_LMBCS_5,
    UCNV_LMBCS_6,
    UCNV_LMBCS_8,
    UCNV_LMBCS_11,
    UCNV_LMBCS_16,
    UCNV_LMBCS_17,
    UCNV_LMBCS_18,
    UCNV_LMBCS_19,
    UCNV_LMBCS_LAST = UCNV_LMBCS_19,
    UCNV_HZ,
    UCNV_SCSU,
    UCNV_ISCII,
    UCNV_US_ASCII,
    UCNV_UTF7,

    /* Number of converter types for which we have conversion routines. */
    UCNV_NUMBER_OF_SUPPORTED_CONVERTER_TYPES
   
} UConverterType;

/**
 * Enum for specifying which platform a converter ID refers to.
 * The use of platform/CCSID is not recommended. See ucnv_openCCSID().
 *
 * @see ucnv_getPlatform
 * @see ucnv_openCCSID
 * @see ucnv_getCCSID
 * @stable
 */
typedef enum {
    UCNV_UNKNOWN = -1,
    UCNV_IBM = 0
} UConverterPlatform;

/**
 * Function pointer for error callback in the codepage to unicode direction.
 * Called when an error has occured in conversion to unicode, or on open/close of the callback (see reason).
 * @param context Pointer to the callback's private data
 * @param args Information about the conversion in progress
 * @param codePoints Points to 'length' bytes of the concerned codepage sequence
 * @param length Size (in bytes) of the concerned codepage sequence
 * @param reason Defines the reason the callback was invoked
 * @see ucnv_setToUCallBack
 * @see UConverterToUnicodeArgs
 * @stable
 */
typedef void (U_EXPORT2 *UConverterToUCallback) (
                  const void* context,
                  UConverterToUnicodeArgs *args,
                  const char *codePoints,
                  int32_t length,
                  UConverterCallbackReason reason,
                  UErrorCode *);

/**
 * Function pointer for error callback in the unicode to codepage direction.
 * Called when an error has occured in conversion from unicode, or on open/close of the callback (see reason).
 * @param context Pointer to the callback's private data
 * @param args Information about the conversion in progress
 * @param codeUnits Points to 'length' UChars of the concerned Unicode sequence
 * @param length Size (in bytes) of the concerned codepage sequence
 * @param codePoint Single UChar32 (UTF-32) containing the concerend Unicode codepoint.
 * @param reason Defines the reason the callback was invoked
 * @see ucnv_setFromUCallBack
 * @stable
 */
typedef void (U_EXPORT2 *UConverterFromUCallback) (
                    const void* context,
                    UConverterFromUnicodeArgs *args,
                    const UChar* codeUnits,
                    int32_t length,
                    UChar32 codePoint,
                    UConverterCallbackReason reason,
                    UErrorCode *);

U_CDECL_END

/**
 * Character that separates converter names from options and options from each other.
 * @see ucnv_open
 * @stable
 */
#define UCNV_OPTION_SEP_CHAR ','

/**
 * String version of UCNV_OPTION_SEP_CHAR. 
 * @see ucnv_open
 * @stable
 */
#define UCNV_OPTION_SEP_STRING ","

/**
 * Character that separates a converter option from its value.
 * @see ucnv_open
 * @stable
 */
#define UCNV_VALUE_SEP_CHAR '='

/**
 * String version of UCNV_VALUE_SEP_CHAR. 
 * @see ucnv_open
 * @stable
 */
#define UCNV_VALUE_SEP_STRING "="

/**
 * Converter option for specifying a locale.
 * @see ucnv_open
 * @stable
 */
#define UCNV_LOCALE_OPTION_STRING ",locale="

/**
 * Do a fuzzy compare of a two converter/alias names.  The comparison
 * is case-insensitive.  It also ignores the characters '-', '_', and
 * ' ' (dash, underscore, and space).  Thus the strings "UTF-8",
 * "utf_8", and "Utf 8" are exactly equivalent.
 * 
 * @param name1 a converter name or alias, zero-terminated
 * @param name2 a converter name or alias, zero-terminated
 * @return 0 if the names match, or a negative value if the name1
 * lexically precedes name2, or a positive value if the name1
 * lexically follows name2.
 * @stable
 */
U_CAPI int U_EXPORT2
ucnv_compareNames(const char *name1, const char *name2);


/**
 * Creates a UConverter object with the names specified as a C string.
 * The actual name will be resolved with the alias file
 * using a case-insensitive string comparison that ignores
 * the delimiters '-', '_', and ' ' (dash, underscore, and space).
 * E.g., the names "UTF8", "utf-8", and "Utf 8" are all equivalent.
 * If <code>NULL</code> is passed for the converter name, it will create one with the
 * getDefaultName return value.
 *
 * <p>A converter name for ICU 1.5 and above may contain options
 * like a locale specification to control the specific behavior of
 * the newly instantiated converter.
 * The meaning of the options depends on the particular converter.
 * If an option is not defined for or recognized by a given converter, then it is ignored.</p>
 *
 * <p>Options are appended to the converter name string, with a
 * <code>UCNV_OPTION_SEP_CHAR</code> between the name and the first option and
 * also between adjacent options.</p>
 *
 * @param converterName : name of the uconv table, may have options appended
 * @param err outgoing error status <TT>U_MEMORY_ALLOCATION_ERROR, U_FILE_ACCESS_ERROR</TT>
 * @return the created Unicode converter object, or <TT>NULL</TT> if an error occured
 * @see ucnv_openU
 * @see ucnv_openCCSID
 * @see ucnv_close
 * @stable
 */
U_CAPI UConverter* U_EXPORT2 
ucnv_open   (const char *converterName, UErrorCode * err);


/**
 * Creates a Unicode converter with the names specified as unicode string. 
 * The name should be limited to the ASCII-7 alphanumerics range.
 * The actual name will be resolved with the alias file
 * using a case-insensitive string comparison that ignores
 * the delimiters '-', '_', and ' ' (dash, underscore, and space).
 * E.g., the names "UTF8", "utf-8", and "Utf 8" are all equivalent.
 * If <TT>NULL</TT> is passed for the converter name, it will create 
 * one with the ucnv_getDefaultName() return value.
 * @param converterName : name of the uconv table in a zero terminated 
 *        Unicode string
 * @param err outgoing error status <TT>U_MEMORY_ALLOCATION_ERROR, 
 *        U_FILE_ACCESS_ERROR</TT>
 * @return the created Unicode converter object, or <TT>NULL</TT> if an 
 *        error occured
 * @see ucnv_open
 * @see ucnv_openCCSID
 * @see ucnv_close
 * @see ucnv_getDefaultName
 * @stable
 */
U_CAPI UConverter* U_EXPORT2 
ucnv_openU (const UChar * name,
            UErrorCode * err);

/**
 * Creates a UConverter object from a CCSID number and platform pair.
 * Note that the usefulness of this function is limited to platforms with numeric
 * encoding IDs. Only IBM and Microsoft platforms use numeric (16-bit) identifiers for
 * encodings.
 *
 * In addition, IBM CCSIDs and Unicode conversion tables are not 1:1 related.
 * For many IBM CCSIDs there are multiple (up to six) Unicode conversion tables, and
 * for some Unicode conversion tables there are multiple CCSIDs.
 * Some "alternate" Unicode conversion tables are provided by the
 * IBM CDRA conversion table registry.
 * The most prominent example of a systematic modification of conversion tables that is
 * not provided in the form of conversion table files in the repository is
 * that S/390 Unix System Services swaps the codes for Line Feed and New Line in all
 * EBCDIC codepages, which requires such a swap in the Unicode conversion tables as well.
 *
 * Only IBM default conversion tables are accessible with ucnv_openCCSID().
 * ucnv_getCCSID() will return the same CCSID for all conversion tables that are associated
 * with that CCSID.
 *
 * Currently, the only "platform" supported in the ICU converter API is UCNV_IBM.
 *
 * In summary, the use of CCSIDs and the associated API functions is not recommended.
 *
 * In order to open a converter with the default IBM CDRA Unicode conversion table,
 * you can use this function or use the prefix "ibm-":
 * \code
 *     char name[20];
 *     sprintf(name, "ibm-%hu", ccsid);
 *     cnv=ucnv_open(name, &errorCode);
 * \endcode
 *
 * In order to open a converter with the IBM S/390 Unix System Services variant of a Unicode/EBCDIC conversion table,
 * you can use the prefix "ibm-" together with the suffix "-s390":
 * \code
 *     char name[20];
 *     sprintf(name, "ibm-%hu-s390", ccsid);
 *     cnv=ucnv_open(name, &errorCode);
 * \endcode
 *
 * In order to open a converter from a Microsoft codepage number, use the prefix "cp":
 * \code
 *     char name[20];
 *     sprintf(name, "cp%hu", codepageID);
 *     cnv=ucnv_open(name, &errorCode);
 * \endcode
 *
 * @param codepage codepage number to create
 * @param platform the platform in which the codepage number exists
 * @param err error status <TT>U_MEMORY_ALLOCATION_ERROR, U_FILE_ACCESS_ERROR</TT>
 * @return the created Unicode converter object, or <TT>NULL</TT> if an error
 *   occured.
 * @see ucnv_open
 * @see ucnv_openU
 * @see ucnv_close
 * @see ucnv_getCCSID
 * @see ucnv_getPlatform
 * @see UConverterPlatform
 * @stable
 */
U_CAPI UConverter* U_EXPORT2
ucnv_openCCSID (int32_t codepage,
                UConverterPlatform platform,
                UErrorCode * err);

/**
 * Thread safe cloning operation
 * @param cnv converter to be cloned
 * @param stackBuffer user allocated space for the new clone. If NULL new memory will be allocated. 
 *  If buffer is not large enough, new memory will be allocated.
 *  Clients can use the U_CNV_SAFECLONE_BUFFERSIZE. This will probably be enough to avoid memory allocations.
 * @param pBufferSize pointer to size of allocated space. 
 *  If *pBufferSize == 0, a sufficient size for use in cloning will 
 *  be returned ('pre-flighting')
 *  If *pBufferSize is not enough for a stack-based safe clone, 
 *  new memory will be allocated.
 * @param status to indicate whether the operation went on smoothly or there were errors
 *  An informational status value, U_SAFECLONE_ALLOCATED_ERROR, is used if any allocations were necessary.
 * @return pointer to the new clone
 * @draft ICU 1.8
 */
U_CAPI UConverter * U_EXPORT2 
ucnv_safeClone(const UConverter *cnv, 
               void             *stackBuffer,
               int32_t          *pBufferSize, 
               UErrorCode       *status);

/** @draft ICU 1.8 */
#define U_CNV_SAFECLONE_BUFFERSIZE 512

/**
 * Deletes the unicode converter and releases resources associated
 * with just this instance.
 * Does not free up shared converter tables.
 *
 * @param converter the converter object to be deleted
 * @see ucnv_open
 * @see ucnv_openU
 * @see ucnv_openCCSID
 * @stable
 */
U_CAPI void  U_EXPORT2
ucnv_close (UConverter * converter);

/**
 * Fills in the output parameter, subChars, with the substitution characters
 * as multiple bytes.
 *
 * @param converter the Unicode converter
 * @param subChars the subsitution characters
 * @param len on input the capacity of subChars, on output the number 
 * of bytes copied to it
 * @param  err the outgoing error status code.
 * If the substitution character array is too small, an
 * <TT>U_INDEX_OUTOFBOUNDS_ERROR</TT> will be returned.
 * @see ucnv_setSubstChars
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_getSubstChars (const UConverter * converter,
                    char *subChars,
                    int8_t * len,
                    UErrorCode * err);

/**
 * Sets the substitution chars when converting from unicode to a codepage. The
 * substitution is specified as a string of 1-4 bytes, and may contain
 *  <TT>NULL</TT> byte.
 * @param converter the Unicode converter
 * @param subChars the substitution character byte sequence we want set
 * @param len the number of bytes in subChars
 * @param err the error status code.  <TT>U_INDEX_OUTOFBOUNDS_ERROR </TT> if
 * len is bigger than the maximum number of bytes allowed in subchars
 * @see ucnv_getSubstChars
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_setSubstChars (UConverter * converter,
                    const char *subChars,
                    int8_t len,
                    UErrorCode * err);

/**
 * Fills in the output parameter, errBytes, with the error characters from the
 * last failing conversion.
 *
 * @param converter the Unicode converter
 * @param errBytes the codepage bytes which were in error
 * @param len on input the capacity of errBytes, on output the number of
 *  bytes which were copied to it
 * @param err the error status code.
 * If the substitution character array is too small, an
 * <TT>U_INDEX_OUTOFBOUNDS_ERROR</TT> will be returned.
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_getInvalidChars (const UConverter * converter,
                      char *errBytes,
                      int8_t * len,
                      UErrorCode * err);

/**
 * Fills in the output parameter, errChars, with the error characters from the
 * last failing conversion.
 *
 * @param converter the Unicode converter
 * @param errUChars the UChars which were in error
 * @param len on input the capacity of errUChars, on output the number of 
 *  UChars which were copied to it
 * @param err the error status code.
 * If the substitution character array is too small, an
 * <TT>U_INDEX_OUTOFBOUNDS_ERROR</TT> will be returned.
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_getInvalidUChars (const UConverter * converter,
                       UChar *errUChars,
                       int8_t * len,
                       UErrorCode * err);

/**
 * Resets the state of a converter to the default state. This is used
 * in the case of an error, to restart a conversion from a known default state.
 * It will also empty the internal output buffers.
 * @param converter the Unicode converter
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_reset (UConverter * converter);

/**
 * Resets the to-Unicode part of a converter state to the default state.
 * This is used in the case of an error to restart a conversion to
 * Unicode to a known default state. It will also empty the internal
 * output buffers used for the conversion to Unicode codepoints.
 * @param converter the Unicode converter
 * @draft ICU 1.8
 */
U_CAPI void U_EXPORT2 
ucnv_resetToUnicode(UConverter *converter);

/**
 * Resets the from-Unicode part of a converter state to the default state.
 * This is used in the case of an error to restart a conversion from
 * Unicode to a known default state. It will also empty the internal output
 * buffers used for the conversion from Unicode codepoints.
 * @param converter the Unicode converter
 * @draft ICU 1.8
 */
U_CAPI void U_EXPORT2 
ucnv_resetFromUnicode(UConverter *converter);

/**
 * Returns the maximum length of bytes used by a character. This varies 
 * between 1 and 4
 * @param converter the Unicode converter
 * @return the maximum number of bytes allowed by this particular converter
 * @see ucnv_getMinCharSize
 * @stable
 */
U_CAPI int8_t U_EXPORT2
ucnv_getMaxCharSize (const UConverter * converter);


/**
 * Returns the minimum byte length for characters in this codepage. 
 * This is either 1 or 2 for all supported codepages.
 * @param converter the Unicode converter
 * @return the minimum number of bytes allowed by this particular converter
 * @see ucnv_getMaxCharSize
 * @stable
 */
U_CAPI int8_t U_EXPORT2
ucnv_getMinCharSize (const UConverter * converter);

/**
 * Returns the display name of the converter passed in based on the Locale 
 * passed in. If the locale contains no display name, the internal ASCII
 * name will be filled in.
 *
 * @param converter the Unicode converter.
 * @param displayLocale is the specific Locale we want to localised for
 * @param displayName user provided buffer to be filled in
 * @param displayNameCapacty size of displayName Buffer
 * @param err error status code
 * @return displayNameLength number of UChar needed in displayName
 * @see ucnv_getName
 * @stable
 */
U_CAPI int32_t U_EXPORT2
ucnv_getDisplayName (const UConverter * converter,
                     const char *displayLocale,
                     UChar * displayName,
                     int32_t displayNameCapacity,
                     UErrorCode * err);

/**
 * Gets the internal, canonical name of the converter (zero-terminated).
 * The lifetime of the returned string will be that of the converter 
 * passed to this function.
 * @param converter the Unicode converter
 * @param err UErrorCode status
 * @return the internal name of the converter
 * @see ucnv_getDisplayName
 * @stable
 */
U_CAPI const char * U_EXPORT2 
ucnv_getName (const UConverter * converter, UErrorCode * err);


/**
 * Gets a codepage number associated with the converter. This is not guaranteed
 * to be the one used to create the converter. Some converters do not represent
 * platform registered codepages and return zero for the codepage number.
 * The error code fill-in parameter indicates if the codepage number
 * is available.
 * Does not check if the converter is <TT>NULL</TT> or if converter's data
 * table is <TT>NULL</TT>.
 *
 * Important: The use of CCSIDs is not recommended because it is limited
 * to only two platforms in principle and only one (UCNV_IBM) in the current
 * ICU converter API.
 * Also, CCSIDs are insufficient to identify IBM Unicode conversion tables precisely.
 * For more details see ucnv_openCCSID().
 *
 * @param converter the Unicode converter
 * @param err the error status code.
 * @return If any error occurrs, -1 will be returned otherwise, the codepage number
 * will be returned
 * @see ucnv_openCCSID
 * @see ucnv_getPlatform
 * @stable
 */
U_CAPI int32_t U_EXPORT2
ucnv_getCCSID (const UConverter * converter,
               UErrorCode * err);

/**
 * Gets a codepage platform associated with the converter. Currently, 
 * only <TT>UCNV_IBM</TT> will be returned.
 * Does not test if the converter is <TT>NULL</TT> or if converter's data 
 * table is <TT>NULL</TT>. 
 * @param converter the Unicode converter
 * @param err the error status code.
 * @return The codepage platform
 * @stable
 */
U_CAPI UConverterPlatform U_EXPORT2
ucnv_getPlatform (const UConverter * converter,
                  UErrorCode * err);

/**
 * Gets the type of the converter
 * e.g. SBCS, MBCS, DBCS, UTF8, UTF16_BE, UTF16_LE, ISO_2022, 
 * EBCDIC_STATEFUL, LATIN_1
 * @param converter a valid, opened converter
 * @return the type of the converter
 * @stable
 */
U_CAPI UConverterType U_EXPORT2
ucnv_getType (const UConverter * converter);

/**
 * Gets the "starter" (lead) bytes for converters of type MBCS.
 * Will fill in an <TT>U_ILLEGAL_ARGUMENT_ERROR</TT> if converter passed in
 * is not MBCS. Fills in an array of type UBool, with the value of the byte 
 * as offset to the array. For example, if (starters[0x20] == TRUE) at return,
 * it means that the byte 0x20 is a starter byte in this converter.
 * Context pointers are always owned by the caller.
 * 
 * @param converter a valid, opened converter of type MBCS
 * @param starters an array of size 256 to be filled in
 * @param err error status, <TT>U_ILLEGAL_ARGUMENT_ERROR</TT> if the 
 * converter is not a type which can return starters.
 * @see ucnv_getType
 * @stable
 */
U_CAPI void U_EXPORT2 ucnv_getStarters(const UConverter* converter, 
                                       UBool starters[256],
                                       UErrorCode* err);


/**
 * Gets the current calback function used by the converter when an illegal
 *  or invalid codepage sequence is found. 
 * Context pointers are always owned by the caller.
 *
 * @param converter the unicode converter
 * @param action fillin: returns the callback function pointer
 * @param context fillin: returns the callback's private void* context
 * @see ucnv_setToUCallBack
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_getToUCallBack (const UConverter * converter,
                     UConverterToUCallback *action,
                     const void **context);

/**
 * Gets the current callback function used by the converter when illegal 
 * or invalid Unicode sequence is found.
 * Context pointers are always owned by the caller.
 *
 * @param converter the unicode converter
 * @param action fillin: returns the callback function pointer
 * @param context fillin: returns the callback's private void* context
 * @see ucnv_setFromUCallBack
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_getFromUCallBack (const UConverter * converter,
                       UConverterFromUCallback *action,
                       const void **context);

/**
 * Changes the callback function used by the converter when
 * an illegal or invalid sequence is found.
 * Context pointers are always owned by the caller.
 *
 * @param converter the unicode converter
 * @param newAction the new callback function
 * @param newContext the new toUnicode callback context pointer
 * @param oldAction fillin: returns the old callback function pointer
 * @param oldContext fillin: returns the old callback's private void* context
 * @param err The error code status
 * @see ucnv_getToUCallBack
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_setToUCallBack (UConverter * converter,
                     UConverterToUCallback newAction,
                     const void* newContext,
                     UConverterToUCallback *oldAction,
                     const void** oldContext,
                     UErrorCode * err);

/**
 * Changes the current callback function used by the converter when
 * an illegal or invalid sequence is found.
 * Context pointers are always owned by the caller.
 *
 * @param converter the unicode converter
 * @param newAction the new callback function
 * @param newContext the new fromUnicode callback context pointer
 * @param oldAction fillin: returns the old callback function pointer
 * @param oldContext fillin: returns the old callback's private void* context
 * @param err The error code status
 * @see ucnv_getFromUCallBack
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_setFromUCallBack (UConverter * converter,
                       UConverterFromUCallback newAction,
                       const void *newContext,
                       UConverterFromUCallback *oldAction,
                       const void **oldContext,
                       UErrorCode * err);

/**
 * Converts an array of unicode characters to an array of codepage
 * characters. This function is optimized for converting a continuous
 * stream of data in buffer-sized chunks, where the entire source and
 * target does not fit in available buffers.
 * 
 * The source pointer is an in/out parameter. It starts out pointing where the 
 * conversion is to begin, and ends up pointing after the last UChar consumed. 
 * 
 * Target similarly starts out pointer at the first available byte in the output
 * buffer, and ends up pointing after the last byte written to the output.
 * 
 * The converter always attempts to consume the entire source buffer, unless 
 * (1.) the target buffer is full, or (2.) a failing error is returned from the
 * current callback function.  When a successful error status has been
 * returned, it means that all of the source buffer has been
 *  consumed. At that point, the caller should reset the source and
 *  sourceLimit pointers to point to the next chunk.
 * 
 * This is a <I>stateful</I> conversion. Additionally, even when all source data has
 * been consumed, some data may be in the converters' internal state.
 * Call this function repeatedly, updating the target pointers with
 * the next empty chunk of target in case of a
 * <TT>U_BUFFER_OVERFLOW_ERROR</TT>, and updating the source  pointers
 *  with the next chunk of source when a successful error status is
 * returned, until there are no more chunks of source data.
 * @param converter the Unicode converter
 * @param target I/O parameter. Input : Points to the beginning of the buffer to copy
 *  codepage characters to. Output : points to after the last codepage character copied
 *  to <TT>target</TT>.
 * @param targetLimit the pointer just after last of the <TT>target</TT> buffer
 * @param source I/O parameter, pointer to pointer to the source Unicode character buffer. 
 * @param sourceLimit the pointer just after the last of the source buffer
 * @param offsets if NULL is passed, nothing will happen to it, otherwise it needs to have the same number
 * of allocated cells as <TT>target</TT>. Will fill in offsets from target to source pointer
 * e.g: <TT>offsets[3]</TT> is equal to 6, it means that the <TT>target[3]</TT> was a result of transcoding <TT>source[6]</TT>
 * For output data carried across calls, and other data without a specific source character
 * (such as from escape sequences or callbacks)  -1 will be placed for offsets. 
 * @param flush set to <TT>TRUE</TT> if the current source buffer is the last available
 * chunk of the source, <TT>FALSE</TT> otherwise. Note that if a failing status is returned,
 * this function may have to be called multiple times wiht flush set to <TT>TRUE</TT> until
 * the source buffer is consumed.
 * @param err the error status.  <TT>U_ILLEGAL_ARGUMENT_ERROR</TT> will be set if the
 * converter is <TT>NULL</TT>.
 * <code>U_BUFFER_OVERFLOW_ERROR</code> will be set if the target is full and there is 
 * still data to be written to the target.
 * @see ucnv_fromUChars
 * @see ucnv_convert
 * @see ucnv_getMinCharSize
 * @see ucnv_setToUCallBack
 * @stable
 */
U_CAPI void U_EXPORT2 
ucnv_fromUnicode (UConverter * converter,
                  char **target,
                  const char *targetLimit,
                  const UChar ** source,
                  const UChar * sourceLimit,
                  int32_t* offsets,
                  UBool flush,
                  UErrorCode * err);

/**
 * Converts a buffer of codepage bytes into an array of unicode UChars
 * characters. This function is optimized for converting a continuous
 * stream of data in buffer-sized chunks, where the entire source and
 * target does not fit in available buffers.
 * 
 * The source pointer is an in/out parameter. It starts out pointing where the 
 * conversion is to begin, and ends up pointing after the last byte of source consumed. 
 * 
 * Target similarly starts out pointer at the first available UChar in the output
 * buffer, and ends up pointing after the last UChar written to the output. 
 * It does NOT necessarily keep UChar sequences together.
 * 
 * The converter always attempts to consume the entire source buffer, unless 
 * (1.) the target buffer is full, or (2.) a failing error is returned from the
 * current callback function.  When a successful error status has been
 * returned, it means that all of the source buffer has been
 *  consumed. At that point, the caller should reset the source and
 *  sourceLimit pointers to point to the next chunk.
 * 
 * This is a <I>stateful</I> conversion. Additionally, even when all source data has
 * been consumed, some data may be in the converters' internal state.
 * Call this function repeatedly, updating the target pointers with
 * the next empty chunk of target in case of a
 * <TT>U_BUFFER_OVERFLOW_ERROR</TT>, and updating the source  pointers
 *  with the next chunk of source when a successful error status is
 * returned, until there are no more chunks of source data.
 * @param converter the Unicode converter
 * @param target I/O parameter. Input : Points to the beginning of the buffer to copy
 *  UChars into. Output : points to after the last UChar copied.
 * @param targetLimit the pointer just after the end of the <TT>target</TT> buffer
 * @param source I/O parameter, pointer to pointer to the source codepage buffer. 
 * @param sourceLimit the pointer to the byte after the end of the source buffer
 * @param offsets if NULL is passed, nothing will happen to it, otherwise it needs to have the same number
 * of allocated cells as <TT>target</TT>. Will fill in offsets from target to source pointer
 * e.g: <TT>offsets[3]</TT> is equal to 6, it means that the <TT>target[3]</TT> was a result of transcoding <TT>source[6]</TT>
 * For output data carried across calls, and other data without a specific source character
 * (such as from escape sequences or callbacks)  -1 will be placed for offsets. 
 * @param flush set to <TT>TRUE</TT> if the current source buffer is the last available
 * chunk of the source, <TT>FALSE</TT> otherwise. Note that if a failing status is returned,
 * this function may have to be called multiple times wiht flush set to <TT>TRUE</TT> until
 * the source buffer is consumed.
 * @param err the error status.  <TT>U_ILLEGAL_ARGUMENT_ERROR</TT> will be set if the
 * converter is <TT>NULL</TT>.
 * <code>U_BUFFER_OVERFLOW_ERROR</code> will be set if the target is full and there is 
 * still data to be written to the target. 
 * @see ucnv_fromUChars
 * @see ucnv_convert
 * @see ucnv_getMinCharSize
 * @see ucnv_setFromUCallBack
 * @see ucnv_getNextUChar
 * @stable
 */
U_CAPI void U_EXPORT2 
ucnv_toUnicode (UConverter * converter,
                UChar ** target,
                const UChar * targetLimit,
                const char **source,
                const char *sourceLimit,
                int32_t* offsets,
                UBool flush,
                UErrorCode * err);


/**
 * Convert the Unicode string into a codepage string using an existing UConverter.
 * The output string is NUL-terminated if possible.
 *
 * This function is a more convenient but less powerful version of ucnv_fromUnicode().
 * It is only useful for whole strings, not for streaming conversion.
 *
 * The maximum output buffer capacity required (barring output from callbacks) will be
 * srcLength*ucnv_getMaxCharSize(cnv).
 *
 * @param cnv the converter object to be used (ucnv_resetFromUnicode() will be called)
 * @param src the input Unicode string
 * @param srcLength the input string length, or -1 if NUL-terminated
 * @param dest destination string buffer, can be NULL if destCapacity==0
 * @param destCapacity the number of chars available at dest
 * @param errorCode normal ICU error code;
 *                  common error codes that may be set by this function include
 *                  U_BUFFER_OVERFLOW_ERROR, U_STRING_NOT_TERMINATED_WARNING,
 *                  U_ILLEGAL_ARGUMENT_ERROR, and conversion errors
 * @return the length of the output string, not counting the terminating NUL;
 *         if the length is greater than destCapacity, then the string will not fit
 *         and a buffer of the indicated length would need to be passed in
 * @see ucnv_fromUnicode
 * @see ucnv_convert
 * @draft ICU 2.0 (new NUL-termination semantics)
 */
U_CAPI int32_t U_EXPORT2
ucnv_fromUChars(UConverter *cnv,
                char *dest, int32_t destCapacity,
                const UChar *src, int32_t srcLength,
                UErrorCode *pErrorCode);


/**
 * Convert the codepage string into a Unicode string using an existing UConverter.
 * The output string is NUL-terminated if possible.
 *
 * This function is a more convenient but less powerful version of ucnv_toUnicode().
 * It is only useful for whole strings, not for streaming conversion.
 *
 * The maximum output buffer capacity required (barring output from callbacks) will be
 * 2*srcLength (each char may be converted into a surrogate pair).
 *
 * @param cnv the converter object to be used (ucnv_resetToUnicode() will be called)
 * @param src the input codepage string
 * @param srcLength the input string length, or -1 if NUL-terminated
 * @param dest destination string buffer, can be NULL if destCapacity==0
 * @param destCapacity the number of UChars available at dest
 * @param errorCode normal ICU error code;
 *                  common error codes that may be set by this function include
 *                  U_BUFFER_OVERFLOW_ERROR, U_STRING_NOT_TERMINATED_WARNING,
 *                  U_ILLEGAL_ARGUMENT_ERROR, and conversion errors
 * @return the length of the output string, not counting the terminating NUL;
 *         if the length is greater than destCapacity, then the string will not fit
 *         and a buffer of the indicated length would need to be passed in
 * @see ucnv_toUnicode
 * @see ucnv_convert
 * @draft ICU 2.0 (new NUL-termination semantics)
 */
U_CAPI int32_t U_EXPORT2
ucnv_toUChars(UConverter *cnv,
              UChar *dest, int32_t destCapacity,
              const char *src, int32_t srcLength,
              UErrorCode *pErrorCode);

/**
 * Will convert a codepage buffer into unicode one character at a time.
 * <p>This function was written to be efficient when transcoding small
 * amounts of data at a time.
 * In that case it will be more efficient than \Ref{ucnv_toUnicode}.
 * When converting large buffers use \Ref{ucnv_toUnicode}.</p>
 *
 * <p>Handling of surrogate pairs and supplementary-plane code points:<br>
 * There are two different kinds of codepages that provide mappings for surrogate characters:
 * <ul>
 *   <li>Codepages like UTF-8, UTF-32, and GB 18030 provide direct representations for Unicode
 *       code points U+10000-U+10ffff as well as for single surrogates U+d800-U+dfff.
 *       Each valid sequence will result in exactly one returned code point.
 *       If a sequence results in a single surrogate, then that will be returned
 *       by itself, even if a neighboring sequence encodes the matching surrogate.</li>
 *   <li>Codepages like SCSU and LMBCS (and UTF-16) provide direct representations only for BMP code points
 *       including surrogates. Code points in supplementary planes are represented with
 *       two sequences, each encoding a surrogate.
 *       For these codepages, matching pairs of surrogates will be combined into single
 *       code points for returning from this function.
 *       (Note that SCSU is actually a mix of these codepage types.)</li>
 * </ul></p>
 *
 * @param converter an open UConverter
 * @param source the address of a pointer to the codepage buffer, will be
 *  updated to point after the bytes consumed in the conversion call.
 * @param sourceLimit points to the end of the input buffer
 * @param err fills in error status (see ucnv_toUnicode)
 * <code>U_INDEX_OUTOFBOUNDS_ERROR</code> will be set if the input 
 * is empty or does not convert to any output (e.g.: pure state-change 
 * codes SI/SO, escape sequences for ISO 2022,
 * or if the callback did not output anything, ...).
 * This function will not set a <code>U_BUFFER_OVERFLOW_ERROR</code> because
 *  the "buffer" is the return code. However, there might be subsequent output
 *  stored in the converter object
 * that will be returned in following calls to this function.
 * @return a UChar32 resulting from the partial conversion of source
 * @see ucnv_toUnicode
 * @see ucnv_toUChars
 * @see ucnv_convert
 * @stable
 */
U_CAPI UChar32 U_EXPORT2
ucnv_getNextUChar (UConverter * converter,
                   const char **source,
                   const char * sourceLimit,
                   UErrorCode * err);


/**
 * Will convert a sequence of bytes from one codepage to another.
 * This is <STRONG>NOT AN EFFICIENT</STRONG> way to transcode.
 * use \Ref{ucnv_toUnicode} and \Ref{ucnv_fromUnicode} for efficiency.
 * @param toConverterName The name of the converter that will be used
 *  in conversion from unicode into the output buffer
 * @param fromConverterName: The name of the converter that will be used
 *  in conversion from the source buffer into intermediate unicode.
 * @param target Pointer to the output buffer
 * @param targetCapacity capacity of the target, in bytes
 * @param source Pointer to the input buffer
 * @param sourceLength capacity of the source, in bytes
 * @param err error status. 
 * <code>U_BUFFER_OVERFLOW_ERROR</code> will be set if the target is full and there is still input left in the source.
 * @return  will be filled in with the number of bytes needed in target
 * @see ucnv_fromUnicode
 * @see ucnv_toUnicode
 * @see ucnv_fromUChars
 * @see ucnv_toUChars
 * @see ucnv_getNextUChar
 * @stable
 */
U_CAPI int32_t U_EXPORT2
ucnv_convert (const char *toConverterName,
              const char *fromConverterName,
              char *target,
              int32_t targetCapacity,
              const char *source,
              int32_t sourceLength,
              UErrorCode * err);

/**
 * Frees up memory occupied by unused, cached converter shared data.
 *
 * @return the number of cached converters successfully deleted
 * @see ucnv_close
 * @stable
 */
U_CAPI int32_t U_EXPORT2
ucnv_flushCache (void);


/**
 * returns the number of available converters, as per the alias file.
 *
 * @return the number of available converters
 * @see ucnv_getAvailableName
 * @stable
 */
U_CAPI int32_t U_EXPORT2
ucnv_countAvailable (void);

/**
 * Gets the name of the specified converter from a list of all converters
 * contaied in the alias file.
 * @param n the index to a converter available on the system (in the range <TT>[0..ucnv_countAvaiable()]</TT>)
 * @return a pointer a string (library owned), or <TT>NULL</TT> if the index is out of bounds.
 * @see ucnv_countAvailable
 * @stable
 */
U_CAPI const char* U_EXPORT2
ucnv_getAvailableName (int32_t n);

/**
 * Gives the number of aliases for a given converter or alias name.
 * Note that additional aliases are recognized by ucnv_open().
 * This method only enumerates the listed entries in the alias file.
 * @param alias alias name
 * @param pErrorCode error status
 * @return number of names on alias list for given alias
 * @stable
 */
U_CAPI uint16_t U_EXPORT2 
ucnv_countAliases(const char *alias, UErrorCode *pErrorCode);

/**
 * Gives the name of the alias at given index of alias list.
 * Note that additional aliases are recognized by ucnv_open().
 * This method only enumerates the listed entries in the alias file.
 * @param alias alias name
 * @param n index in alias list
 * @param pErrorCode result of operation
 * @return returns the name of the alias at given index
 * @see ucnv_countAliases
 * @stable
 */
U_CAPI const char * U_EXPORT2 
ucnv_getAlias(const char *alias, uint16_t n, UErrorCode *pErrorCode);

/**
 * Fill-up the list of alias names for the given alias.
 * Note that additional aliases are recognized by ucnv_open().
 * This method only enumerates the listed entries in the alias file.
 * @param alias alias name
 * @param aliases fill-in list, aliases is a pointer to an array of
 *        <code>ucnv_countAliases()</code> string-pointers
 *        (<code>const char *</code>) that will be filled in.
 *        The strings themselves are owned by the library.
 * @param pErrorCode result of operation
 * @stable
 */
U_CAPI void U_EXPORT2 
ucnv_getAliases(const char *alias, const char **aliases, UErrorCode *pErrorCode);

/**
 * Gives the number of standards associated to converter names.
 * @return number of standards
 * @stable
 */
U_CAPI uint16_t U_EXPORT2
ucnv_countStandards(void);

/**
 * Gives the name of the standard at given index of standard list.
 * @param n index in standard list
 * @param pErrorCode result of operation
 * @return returns the name of the standard at given index. Owned by the library.
 * @stable
 */
U_CAPI const char * U_EXPORT2
ucnv_getStandard(uint16_t n, UErrorCode *pErrorCode);

/**
 * Returns a standard name for a given converter name.
 *
 * @param name original converter name
 * @param standard name of the standard governing the names; MIME and IANA
 *        are such standards
 * @return returns the standard converter name;
 *         if a standard converter name cannot be determined,
 *         then <code>NULL</code> is returned. Owned by the library.
 * @stable
 */
U_CAPI const char * U_EXPORT2
ucnv_getStandardName(const char *name, const char *standard, UErrorCode *pErrorCode);

/**
 * returns the current default converter name.
 *
 * @return returns the current default converter name;
 *         if a default converter name cannot be determined,
 *         then <code>NULL</code> is returned.
 *         Storage owned by the library
 * @see ucnv_setDefaultName
 * @stable
 */
U_CAPI const char * U_EXPORT2
ucnv_getDefaultName (void);

/**
 * sets the current default converter name. Caller must own the storage for 'name'
 * and preserve it indefinitely. 
 * @param name the converter name to be the default (must exist).
 * @see ucnv_getDefaultName
 * @system SYSTEM API
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_setDefaultName (const char *name);

/**
 * Fixes the backslash character mismapping.  For example, in SJIS, the backslash 
 * character in the ASCII portion is also used to represent the yen currency sign.  
 * When mapping from Unicode character 0x005C, it's unclear whether to map the 
 * character back to yen or backslash in SJIS.  This function will take the input
 * buffer and replace all the yen sign characters with backslash.  This is necessary
 * when the user tries to open a file with the input buffer on Windows.
 * This function will test the converter to see whether such mapping is
 * required.  You can sometimes avoid using this function by using the correct version
 * of Shift-JIS.
 *
 * @param cnv The converter representing the target codepage.
 * @param source the input buffer to be fixed
 * @param sourceLength the length of the input buffer
 * @see ucnv_isAmbiguous
 * @stable
 */
U_CAPI void U_EXPORT2
ucnv_fixFileSeparator(const UConverter *cnv, UChar* source, int32_t sourceLen);

/**
 * Determines if the converter contains ambiguous mappings of the same
 * character or not.
 * @return TRUE if the converter contains ambiguous mapping of the same 
 * character, FALSE otherwise.
 * @stable
 */
U_CAPI UBool U_EXPORT2
ucnv_isAmbiguous(const UConverter *cnv);

/**
 * Sets the converter to use fallback mapping or not.
 * @param cnv The converter to set the fallback mapping usage on.
 * @param usesFallback TRUE if the user wants the converter to take advantage of the fallback 
 * mapping, FALSE otherwise.
 * @stable
 */
U_CAPI void U_EXPORT2 
ucnv_setFallback(UConverter *cnv, UBool usesFallback);

/**
 * Determines if the converter uses fallback mappings or not.
 * @return TRUE if the converter uses fallback, FALSE otherwise.
 * @stable
 */
U_CAPI UBool U_EXPORT2 
ucnv_usesFallback(const UConverter *cnv);

/**
 * Detects Unicode signatures in the given byte stream. The signature bytes are not consumed, 
 * instead the number of bytes that make up the signature is returned. The conversion APIs
 * donot discard signature bytes, so if the caller wishes to discard them, the caller should 
 * explicity add code to do that after calling this function.
 * <p>
 * Usage:
 * @code     
 *      UErrorCode err = U_ZERO_ERROR;
 *      char input[] = { '\xEF','\xBB', '\xBF','\x41','\x42','\x43' };
 *      char* source = input;
 *      int32_t signatureLength = 0;
 *      char* encoding = ucnv_detectUnicodeSignatures(source,sizeof(input),&signatureLength,&err);
 *      UConverter* conv = NULL;
 *      if(encoding!=NULL && U_SUCCESS(err)){
 *          // should signature be discarded ?
 *          if (discardSignature){
 *              source += signatureLength;
 *          }
 *          conv = ucnv_open(encoding, &err);
 *          .... do the conversion ....
 *      }
 *     
 * @endcode
 *
 * @param source            The source string in which the signature should be detected.
 * @param sourceLength      Length of the input string, or -1 if NUL-terminated.
 * @param signatureLength   A pointer to int8_t to receive the number of bytes that make up the signature 
 *                          of the detected UTF. 0 if not detected.
 * @param pErrorCode        A pointer to receive information about any errors that may occur during detection.
 *                          Must be a valid pointer to an error code value, which must not indicate a failure
 *                          before the function call.
 * @return The name of the encoding detected. NULL if encoding is not detected. 
 */
U_CAPI const char* U_EXPORT2
ucnv_detectUnicodeSignature( const char* source,
                             int32_t sourceLength,
                             int32_t* signatureLength,
                             UErrorCode* pErrorCode);

#endif
/*_UCNV*/

