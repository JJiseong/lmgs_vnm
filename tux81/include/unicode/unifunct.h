/*
**********************************************************************
*   Copyright (c) 2002, International Business Machines Corporation
*   and others.  All Rights Reserved.
**********************************************************************
*   Date        Name        Description
*   01/14/2002  aliu        Creation.
**********************************************************************
*/
#ifndef UNIFUNCT_H
#define UNIFUNCT_H

#include "unicode/utypes.h"

U_NAMESPACE_BEGIN

class UnicodeMatcher;
class UnicodeReplacer;
class TransliterationRuleData;

/**
 * <code>UnicodeFunctor</code> is an abstract base class for objects
 * that perform match and/or replace operations on Unicode strings.
 * @author Alan Liu
 */
class U_I18N_API UnicodeFunctor {

 public:

    /**
     * Destructor
     */
    virtual ~UnicodeFunctor();

    /**
     * Return a copy of this object.  All UnicodeFunctor objects
     * have to support cloning in order to allow classes using
     * UnicodeFunctor to implement cloning.
     */
    virtual UnicodeFunctor* clone() const = 0;

    /**
     * Cast 'this' to a UnicodeMatcher* pointer and return the
     * pointer, or null if this is not a UnicodeMatcher*.  Subclasses
     * that mix in UnicodeMatcher as a base class must override this.
     * This protocol is required because a pointer to a UnicodeFunctor
     * cannot be cast to a pointer to a UnicodeMatcher, since
     * UnicodeMatcher is a mixin that does not derive from
     * UnicodeFunctor.
     */
    virtual UnicodeMatcher* toMatcher() const;

    /**
     * Cast 'this' to a UnicodeReplacer* pointer and return the
     * pointer, or null if this is not a UnicodeReplacer*.  Subclasses
     * that mix in UnicodeReplacer as a base class must override this.
     * This protocol is required because a pointer to a UnicodeFunctor
     * cannot be cast to a pointer to a UnicodeReplacer, since
     * UnicodeReplacer is a mixin that does not derive from
     * UnicodeFunctor.
     */
    virtual UnicodeReplacer* toReplacer() const;

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
     * Returns a unique class ID <b>polymorphically</b>.  This method
     * is to implement a simple version of RTTI, since not all C++
     * compilers support genuine RTTI.  Polymorphic operator==() and
     * clone() methods call this method.
     * 
     * <p>Concrete subclasses of UnicodeFunctor that wish clients to
     * be able to identify them should implement getDynamicClassID()
     * and also a static method and data member:
     * 
     * <pre>
     * static UClassID getStaticClassID() { return (UClassID)&fgClassID; }
     * static char fgClassID;
     * </pre>
     *
     * Subclasses that do not implement this method will have a
     * dynamic class ID of UnicodeFunctor::getStatisClassID().
     *
     * @return The class ID for this object. All objects of a given
     * class have the same class ID.  Objects of other classes have
     * different class IDs.
     */
    virtual UClassID getDynamicClassID(void) const { return getStaticClassID(); };

    /**
     * Set the data object associated with this functor.  The data
     * object provides context for functor-to-standin mapping.  This
     * method is required when assigning a functor to a different data
     * object.  This function MAY GO AWAY later if the architecture is
     * changed to pass data object pointers through the API.
     * @draft
     */
    virtual void setData(const TransliterationRuleData*) = 0;

 protected:

    UnicodeFunctor();

 private:

    /**
     * Class identifier for subclasses of UnicodeFunctor that do not
     * define their class (anonymous subclasses).
     */
    static const char fgClassID;
};

inline UnicodeFunctor::UnicodeFunctor() {}
inline UnicodeFunctor::~UnicodeFunctor() {}

U_NAMESPACE_END

#endif
