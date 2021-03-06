/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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
 * originally based on software copyright (c) 2001, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Id: RegularExpression.hpp,v 1.1 2002/05/11 20:36:57 bhavani Exp $
 */

#if !defined(REGULAREXPRESSION_HPP)
#define REGULAREXPRESSION_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/regx/Op.hpp>
#include <xercesc/util/regx/TokenFactory.hpp>
#include <xercesc/util/regx/BMPattern.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/Mutexes.hpp>
#include <xercesc/util/regx/ModifierToken.hpp>
#include <xercesc/util/regx/ConditionToken.hpp>
#include <xercesc/util/regx/OpFactory.hpp>

// ---------------------------------------------------------------------------
//  Forward Declaration
// ---------------------------------------------------------------------------
class Token;
class BMPattern;
class RangeToken;
class Match;
class TokenFactory;

class XMLUTIL_EXPORT RegularExpression {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    RegularExpression(const char* const pattern);
    RegularExpression(const char* const pattern, const char* const options);
    RegularExpression(const XMLCh* const pattern);
    RegularExpression(const XMLCh* const pattern, const XMLCh* const options);
    ~RegularExpression();

    // -----------------------------------------------------------------------
    //  Public Constants
    // -----------------------------------------------------------------------
    static const unsigned int   MARK_PARENS;
    static const unsigned int   IGNORE_CASE;
    static const unsigned int   SINGLE_LINE;
    static const unsigned int   MULTIPLE_LINE;
    static const unsigned int   EXTENDED_COMMENT;
    static const unsigned int   USE_UNICODE_CATEGORY;
    static const unsigned int   UNICODE_WORD_BOUNDARY;
    static const unsigned int   PROHIBIT_HEAD_CHARACTER_OPTIMIZATION;
    static const unsigned int   PROHIBIT_FIXED_STRING_OPTIMIZATION;
    static const unsigned int   XMLSCHEMA_MODE;
    static const unsigned int   SPECIAL_COMMA;
    static const unsigned short WT_IGNORE;
    static const unsigned short WT_LETTER;
    static const unsigned short WT_OTHER;

    // -----------------------------------------------------------------------
    //  Public Helper methods
    // -----------------------------------------------------------------------
    static int getOptionValue(const XMLCh ch);

    // -----------------------------------------------------------------------
    //  Matching methods
    // -----------------------------------------------------------------------
    bool matches(const char* const matchString);
    bool matches(const char* const matchString, const int start,
                 const int end);
    bool matches(const char* const matchString, Match* const pMatch);
    bool matches(const char* const matchString, const int start,
                 const int end, Match* const pMatch);

    bool matches(const XMLCh* const matchString);
    bool matches(const XMLCh* const matchString, const int start,
                 const int end);
    bool matches(const XMLCh* const matchString, Match* const pMatch);
    bool matches(const XMLCh* const matchString, const int start,
                 const int end, Match* const pMatch);

private:
    // -----------------------------------------------------------------------
    //  Private data types
    // -----------------------------------------------------------------------
    class Context
    {
        public :
            Context();
            ~Context();

            inline const XMLCh* getString() const { return fString; }
            void reset(const XMLCh* const string, const int start,
                       const int limit, const int noClosures);
            bool nextCh(XMLInt32& ch, int& offset, const short direction);

            bool      fInUse;
            bool      fAdoptMatch;
            int       fStart;
            int       fLimit;
            int       fLength;
            int       fSize;
            int*      fOffsets;
            Match*    fMatch;
            XMLCh*    fString;

            friend class Janitor<Context>;
    };

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    RegularExpression(const RegularExpression&);
    void operator=(const RegularExpression&);

    // -----------------------------------------------------------------------
    //  Cleanup methods
    // -----------------------------------------------------------------------
    void cleanUp();

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setPattern(const XMLCh* const pattern, const XMLCh* const options=0);

    // -----------------------------------------------------------------------
    //  Private Helper methods
    // -----------------------------------------------------------------------
    void prepare();
    int parseOptions(const XMLCh* const options);
    bool isSet(const int options, const int flag);
    unsigned short getWordType(const XMLCh* const target, const int begin,
                               const int end, const int offset);
    unsigned short getCharType(const XMLCh ch);
    unsigned short getPreviousWordType(const XMLCh* const target,
                                       const int start, const int end,
                                       int offset);

    /**
      *    Matching helpers
      */
    int match(Context* const context, const Op* const operations, int offset,
              const short direction);
    bool matchIgnoreCase(const XMLInt32 ch1, const XMLInt32 ch2);

    /**
      *    Helper methods used by match(Context* ...)
      */
    bool matchChar(Context* const context, const XMLInt32 ch, int& offset,
                   const short direction, const bool ignoreCase);
    bool matchDot(Context* const context, int& offset, const short direction);
    bool matchRange(Context* const context, const Op* const op,
                    int& offset, const short direction, const bool ignoreCase);
    bool matchAnchor(Context* const context, const XMLInt32 ch,
                     const int offset);
    bool matchBackReference(Context* const context, const XMLInt32 ch,
                            int& offset, const short direction,
                            const bool ignoreCase);
    bool matchString(Context* const context, const XMLCh* const literal,
                     int& offset, const short direction, const bool ignoreCase);
    int  matchUnion(Context* const context, const Op* const op, int offset,
                    const short direction);
    int matchCapture(Context* const context, const Op* const op, int offset,
                     const short direction);
    bool matchCondition(Context* const context, const Op* const op, int offset,
                        const short direction);
    int matchModifier(Context* const context, const Op* const op, int offset,
                      const short direction);

    /**
      *    Converts a token tree into an operation tree
      */
    void compile(const Token* const token);
    Op*  compile(const Token* const token, Op* const next,
                 const bool reverse);
    /**
      *    Helper methods used by compile
      */
    Op* compileSingle(const Token* const token, Op* const next,
                      const unsigned short tokType);
    Op* compileUnion(const Token* const token, Op* const next,
                     const bool reverse);
    Op* compileCondition(const Token* const token, Op* const next,
                         const bool reverse);
    Op* compileParenthesis(const Token* const token, Op* const next,
                           const bool reverse);
    Op* compileLook(const Token* const token, const Op* const next,
                    const bool reverse, const unsigned short tokType);
    Op* compileConcat(const Token* const token, Op* const next,
                      const bool reverse);
    Op* compileClosure(const Token* const token, Op* const next,
                       const bool reverse, const unsigned short tokType);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    bool               fHasBackReferences;
    bool               fFixedStringOnly;
    int                fNoGroups;
    int                fMinLength;
    int                fNoClosures;
    unsigned int       fOptions;
    Context*           fContext;
    BMPattern*         fBMPattern;
    XMLCh*             fPattern;
    XMLCh*             fFixedString;
    Op*                fOperations;
    Token*             fTokenTree;
    RangeToken*        fFirstChar;
    static RangeToken* fWordRange;
    OpFactory          fOpFactory;
    XMLMutex           fMutex;
    TokenFactory*      fTokenFactory;
};


// ---------------------------------------------------------------------------
//  RegularExpression: Cleanup methods
// ---------------------------------------------------------------------------
inline void RegularExpression::cleanUp() {

    delete [] fPattern;
    delete [] fFixedString;
    delete fContext;
    delete fBMPattern;
    delete fTokenFactory;
}

// ---------------------------------------------------------------------------
//  RegularExpression: Helper methods
// ---------------------------------------------------------------------------
inline bool RegularExpression::isSet(const int options, const int flag) {

    return (options & flag) == flag;
}

inline Op* RegularExpression::compileLook(const Token* const token,
                                          const Op* const next,
                                          const bool reverse,
                                          const unsigned short tokType) {

    Op*    ret = 0;
    Op*    result = compile(token->getChild(0), 0, reverse);

    switch(tokType) {
    case Token::LOOKAHEAD:
        ret = fOpFactory.createLookOp(Op::LOOKAHEAD, next, result);
        break;
    case Token::NEGATIVELOOKAHEAD:
        ret = fOpFactory.createLookOp(Op::NEGATIVELOOKAHEAD, next, result);
        break;
    case Token::LOOKBEHIND:
        ret = fOpFactory.createLookOp(Op::LOOKBEHIND, next, result);
        break;
    case Token::NEGATIVELOOKBEHIND:
        ret = fOpFactory.createLookOp(Op::NEGATIVELOOKBEHIND, next, result);
        break;
    case Token::INDEPENDENT:
        ret = fOpFactory.createIndependentOp(next, result);
        break;
    case Token::MODIFIERGROUP:
        ret = fOpFactory.createModifierOp(next, result,
                                   ((ModifierToken *) token)->getOptions(),
                                   ((ModifierToken *) token)->getOptionsMask());
        break;
    }


    return ret;
}

inline Op* RegularExpression::compileSingle(const Token* const token,
                                            Op* const next,
                                            const unsigned short tokType) {

    Op* ret = 0;

    switch (tokType) {
    case Token::DOT:
        ret = fOpFactory.createDotOp();
        break;
    case Token::CHAR:
        ret = fOpFactory.createCharOp(token->getChar());
        break;
    case Token::ANCHOR:
        ret = fOpFactory.createAnchorOp(token->getChar());
        break;
    case Token::RANGE:
    case Token::NRANGE:
        ret = fOpFactory.createRangeOp(token);
        break;
    case Token::EMPTY:
        ret = next;
        break;
    case Token::STRING:
        ret = fOpFactory.createStringOp(token->getString());
        break;
    case Token::BACKREFERENCE:
        ret = fOpFactory.createBackReferenceOp(token->getReferenceNo());
        break;
    }

    if (tokType != Token::EMPTY)
        ret->setNextOp(next);

    return ret;
}


inline Op* RegularExpression::compileUnion(const Token* const token,
                                           Op* const next,
                                           const bool reverse) {

    int tokSize = token->size();
    UnionOp* uniOp = fOpFactory.createUnionOp(tokSize);

    for (int i=0; i<tokSize; i++) {

        uniOp->addElement(compile(token->getChild(i), next, reverse));
    }

    return uniOp;
}


inline Op* RegularExpression::compileCondition(const Token* const token,
                                               Op* const next,
                                               const bool reverse) {

    Token* condTok = ((ConditionToken*) token)->getConditionToken();
    Token* yesTok  = token->getChild(0);
    Token* noTok   = token->getChild(1);
    int    refNo   = token->getReferenceNo();
    Op*    condOp  = (condTok == 0) ? 0 : compile(condTok, 0, reverse);
    Op*    yesOp   = compile(yesTok, next, reverse);
    Op*    noOp    = (noTok == 0) ? 0 : compile(noTok, next, reverse);

    return fOpFactory.createConditionOp(next, refNo, condOp, yesOp, noOp);
}


inline Op* RegularExpression::compileParenthesis(const Token* const token,
                                                 Op* const next,
                                                 const bool reverse) {

    if (token->getNoParen() == 0)
        return compile(token->getChild(0), next, reverse);

    Op* captureOp    = 0;

    if (reverse) {

        captureOp = fOpFactory.createCaptureOp(token->getNoParen(), next);
        captureOp = compile(token->getChild(0), captureOp, reverse);

        return fOpFactory.createCaptureOp(-token->getNoParen(), captureOp);
    }

    captureOp = fOpFactory.createCaptureOp(-token->getNoParen(), next);
    captureOp = compile(token->getChild(0), captureOp, reverse);

    return fOpFactory.createCaptureOp(token->getNoParen(), captureOp);
}

inline Op* RegularExpression::compileConcat(const Token* const token,
                                            Op*  const next,
                                            const bool reverse) {

    Op* ret = next;
    int tokSize = token->size();

    if (!reverse) {

        for (int i= tokSize - 1; i>=0; i--) {
            ret = compile(token->getChild(i), ret, false);
        }
    }
    else {

        for (int i= 0; i< tokSize; i++) {
            ret = compile(token->getChild(i), ret, true);
        }
    }

    return ret;
}

inline Op* RegularExpression::compileClosure(const Token* const token,
                                             Op* const next,
                                             const bool reverse,
                                             const unsigned short tokType) {

    Op*    ret      = 0;
    Token* childTok = token->getChild(0);
    int    min      = token->getMin();
    int    max      = token->getMax();

    if (min >= 0 && min == max) {

        ret = next;
        for (int i=0; i< min; i++) {
            ret = compile(childTok, ret, reverse);
        }

        return ret;
    }

    if (min > 0 && max > 0)
        max -= min;

    if (max > 0) {

        ret = next;
        for (int i=0; i<max; i++) {

            ChildOp* childOp = fOpFactory.createQuestionOp(
                tokType == Token::NONGREEDYCLOSURE);

            childOp->setNextOp(next);
            childOp->setChild(compile(childTok, ret, reverse));
            ret = childOp;
        }
    }
    else {

        ChildOp* childOp = 0;

        if (tokType == Token::NONGREEDYCLOSURE) {
            childOp = fOpFactory.createNonGreedyClosureOp();
        }
        else {

            if (childTok->getMinLength() == 0)
                childOp = fOpFactory.createClosureOp(fNoClosures++);
            else
                childOp = fOpFactory.createClosureOp(-1);
        }

        childOp->setNextOp(next);
        childOp->setChild(compile(childTok, childOp, reverse));
        ret = childOp;
    }

    if (min > 0) {

        for (int i=0; i< min; i++) {
            ret = compile(childTok, ret, reverse);
        }
    }

    return ret;
}

inline int RegularExpression::matchUnion(Context* const context,
                                         const Op* const op, int offset,
                                         const short direction)
{
    unsigned int opSize = op->getSize();
    int ret = -1;

    for (unsigned int i=0; i < opSize; i++) {

        ret = match(context, op->elementAt(i), offset, direction);

        if (ret == context->fLimit)
            return ret;
    }

    return -1;
}

inline int RegularExpression::matchModifier(Context* const context,
                                            const Op* const op, int offset,
                                            const short direction)
{
    int saveOptions = fOptions;
    fOptions |= (int) op->getData();
    fOptions &= (int) ~op->getData2();

    int ret = match(context, op->getChild(), offset, direction);

    fOptions = saveOptions;

    return ret;
}

inline unsigned short RegularExpression::getWordType(const XMLCh* const target
                                                     , const int begin
                                                     , const int end
                                                     , const int offset)
{
    if (offset < begin || offset >= end)
        return WT_OTHER;

    return getCharType(target[offset]);
}

inline
unsigned short RegularExpression::getPreviousWordType(const XMLCh* const target
                                                      , const int start
                                                      , const int end
                                                      , int offset)
{
    unsigned short ret = getWordType(target, start, end, --offset);

    while (ret == WT_IGNORE) {
        ret = getWordType(target, start, end, --offset);
    }

    return ret;
}

inline bool RegularExpression::matchIgnoreCase(const XMLInt32 ch1,
                                               const XMLInt32 ch2)
{

    //REVISIT - for now we will return a case sensitive match
    return (ch1 == ch2);
}

#endif
/**
  * End of file RegularExpression.hpp
  */

