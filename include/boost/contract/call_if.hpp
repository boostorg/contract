
#ifndef BOOST_CONTRACT_CALL_IF_HPP_
#define BOOST_CONTRACT_CALL_IF_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Statically disable compilation and execution of functor calls.
*/

#include <boost/contract/detail/none.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

// Boost.ResultOf not always able to deduce lambda result type (on MSVC).
#ifndef BOOST_NO_CXX11_DECL_TYPE
    #include <boost/utility/declval.hpp>
    #define BOOST_CONTRACT_CALL_IF_RESULT_OF_(F) \
        decltype(boost::declval<F>()())
#else
    #include <boost/utility/result_of.hpp>
    #define BOOST_CONTRACT_CALL_IF_RESULT_OF_(F) \
        typename boost::result_of<F()>::type
#endif

/** @endcond */

/* CODE */

namespace boost { namespace contract {

/**
Class template to select compilation and execution of functor calls via a static
boolean condition.
This class template has no members because it is never used directly, it is only
used via its specializations.

Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam Cond    Static boolean condition selecting which functor call to compile
                and execute.
@tparam Then Type of functor to call when the static condition if true.
@tparam ThenResult Return type of then-branch functor call.
*/
template<bool Cond, typename Then, typename ThenResult =
    #ifndef DOXYGEN
        boost::contract::detail::none
    #else
        unspecified
    #endif
>
struct call_if_statement {}; // Empty so cannot be used (but copyable).

/**
Template specialization to dispatch between then-branch functor calls that
return void and the ones that return non-void.
The base class is a call-if statement so the else and else-if statements can be
specified if needed.

Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.
@note   The <c>result_of<Then()>::type</c> expression should be evaluated only
        when the static condition is already checked to be true (because
        @c Then() is required to compile only in that case). This template
        specialization introduces an extra level of indirection necessary for
        the proper lazy evaluation of this result-of expression.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam Then Type of functor to call when the static condition if true.
*/
template<typename Then>
struct call_if_statement<true, Then,
    #ifndef DOXYGEN
        boost::contract::detail::none
    #else
        unspecified
    #endif
> :
    call_if_statement<true, Then,
        #ifndef DOXYGEN
            BOOST_CONTRACT_CALL_IF_RESULT_OF_(Then)
        #else
            typename result_of<Then()>::type
        #endif
    >
{ // Copyable (as its base).
    /**
    Construct this object with the then-branch functor.
    @param f    Then-branch nullary templated functor. The functor @c f() is
                compiled and called in this case (because the if-statement
                static condition is true for this template specialization). The
                return type of @c f() must be the same as (or implicitly
                convertible to) the return type of all other functor calls
                specified for this call-if object.
    */
    explicit call_if_statement(Then f) : call_if_statement<true, Then,
            BOOST_CONTRACT_CALL_IF_RESULT_OF_(Then)>(f) {}
};

/**
Template specialization to handle true static conditions for then-branch functor
calls that do not return @c void.
Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam Then Type of functor to call when the static condition if true.
@tparam ThenResult Non-void return type of the then-branch functor call.
*/
template<typename Then, typename ThenResult>
struct call_if_statement<true, Then, ThenResult> { // Copyable (as *).
    /**
    Construct this object with the then-branch functor.
    @param f    Then-branch nullary templated functor. The functor call @c f()
                is compiled and executed in this case (because the if-statement
                static condition is true for this template specialization). The
                return type of @c f() must be the same as (or implicitly
                convertible to) the @p ThenResult type.
    */
    explicit call_if_statement(Then f) :
            r_(boost::make_shared<ThenResult>(f())) {}

    /**
    This implicit type conversion returns a copy of the value returned by the
    call to the then-branch functor.
    */
    operator ThenResult() const { return *r_; }

    /**
    Specify the else-branch functor.
    @param f    Else-branch nullary templated functor. The functor call @c f()
                is never compiled and executed in this case (because the
                if-statement static condition is true for this template
                specialization). The return type of @c f() must be the same as
                (or implicitly convertible to) the @p ThenResult type.
    @return A copy of the value returned by the call to the then-branch functor
            (because the else-branch functor call is not executed in this case).
    */
    template<typename Else>
    ThenResult else_(Else const& f) const { return *r_; }
    
    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary templated functor. The functor call
                @c f() is never compiled and executed in this case (because the
                if-statement static condition is true for this template
                specialization). The return type of @c f() must be the same as
                (or implicitly convertible to) the @p ThenResult type.
    @tparam ElseIfCond  Static boolean condition selecting which functor call to
                        compile and execute.
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed. Ultimately it will return the
            return value of the then-branch functor call in this case (because
            the if-statement static condition is true for this template
            specialization).
    */
    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, ThenResult> else_if_c(ElseIfThen const& f)
            const { return *this; }

    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary templated functor. The functor call
                @c f() is never compiled and executed in this case (because the
                if-statement static condition is true for this template
                specialization). The return type of @c f() must be the same as
                (or implicitly convertible to) the @p ThenResult type.
    @tparam ElseIfCond  Static boolean nullary meta-function selecting which
                        functor call to compile and execute.
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed. Ultimately it will return the
            return value of the then-branch functor call in this case (because
            the if-statement static condition is true for this template
            specialization).
    */
    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, ThenResult> else_if(ElseIfThen const& f)
            const { return *this; }
    
private:
    boost::shared_ptr<ThenResult> r_;
};

/**
Template specialization to handle true static conditions for then-branch functor
calls that return @c void.
Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam Then Type of functor to call when the static condition if true.
*/
template<typename Then>
struct call_if_statement<true, Then, void> { // Copyable (no data).
    /**
    Construct this object with the then-branch functor.
    @param f    Then-branch nullary templated functor. The functor call @c f()
                is compiled and executed in this case (because the if-statement
                static condition is true for this template specialization). The
                return type of @c f() must be @c void in this case (because the
                then-branch functor calls return @c void for this template
                specialization).
    */
    explicit call_if_statement(Then f) { f(); }
    
    // Cannot provide `operator ThenResult()` here, because ThenResult is void.

    /**
    Specify the else-branch functor.
    @param f    Else-branch nullary templated functor. The functor call @c f()
                is never compiled and executed in this case (because the
                if-statement static condition is true for this template
                specialization). The return type of @c f() must be @c void in
                this case (because the then-branch functor calls return @c void
                for this template specialization).
    */
    template<typename Else>
    void else_(Else const& f) const {}
    
    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary templated functor. The functor call
                @c f() is never compiled and executed in this case (because the
                if-statement static condition is true for this template
                specialization). The return type of @c f() must be @c void in
                this case (because the then-branch functor calls return @c void
                for this template specialization).
    @tparam ElseIfCond  Static boolean condition selecting which functor call to
                        compile and execute.
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed. Ultimately it will return
            @c void in this case (because the then-branch functor calls return
            @c void for this template specialization).
    */
    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, void> else_if_c(ElseIfThen const& f) const {
        return *this;
    }

    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary templated functor. The functor call
                @c f() is never compiled and executed in this case (because the
                if-statement static condition is true for this template
                specialization). The return type of @c f() must be @c void in
                this case (because the then-branch functor calls return @c void
                for this template specialization).
    @tparam ElseIfCond  Static boolean nullary meta-function selecting which
                        functor call to compile and execute.
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed. Ultimately it will return
            @c void in this case (because the then-branch functor calls return
            @c void for this template specialization).
    */
    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, void> else_if(ElseIfThen const& f) const {
        return *this;
    }
};

/**
Template specialization to handle false static conditions.
This one specialization handles all else-branch functor calls (whether they
return @c void or not).

Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam Then Type of functor to call when the static condition if true.
*/
template<typename Then> // Copyable (no data).
struct call_if_statement<false, Then,
    #ifndef DOXYGEN
        boost::contract::detail::none
    #else
        unspecified
    #endif
> {
    /**
    Construct this object with the then-branch functor.
    @param f    Then-branch nullary templated functor. The functor call @c f()
                is never compiled and executed in this case (because the
                if-statement static condition is false for this template
                specialization). The return type of @c f() must be the same as
                (or implicitly convertible to) the return type of the other
                functor calls specified for this call-if object.
    */
    explicit call_if_statement(Then const& f) {}

    // Do not provide `operator result_type()` here, require else_ instead.

    /**
    Specify the else-branch functor.
    @note   The <c>result_of<Else()>::type</c> expression should be evaluated
            only when the static condition is already checked to be false
            (because @c Else() is required to compile only in that case). Thus,
            this result-of expression is evaluated lazily only in
            instantiations of this template.
    @param f    Else-branch nullary templated functor. The functor call @c f()
                is compiled and executed in this case (because the if-statement
                static condition is @c false for this template specialization).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the return type of the other functor calls
                specified for this call-if object.
    @return A copy of the value returned by the call to the else-branch functor
            @c f().
    */
    template<typename Else>
    #ifndef DOXYGEN
        BOOST_CONTRACT_CALL_IF_RESULT_OF_(Else)
    #else
        typename result_of<Else()>::type
    #endif
    else_(Else f) const { return f(); }
    
    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary templated functor. The functor call
                @c f() is compiled and executed if and only if @c ElseIfCond is
                @c true (because the if-statement static condition is @c false
                for this template specialization). The return type of @c f()
                must be the same as (or implicitly convertible to) the return
                type of the other functor calls specified for this call-if
                object.
    @tparam ElseIfCond  Static boolean condition selecting which functor call to
                        compile and execute.
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed. Ultimately this will return
            the return value of the functor call being compiled and executed.
    */
    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<ElseIfCond, ElseIfThen> else_if_c(ElseIfThen f) const {
        return call_if_statement<ElseIfCond, ElseIfThen>(f);
    }
    
    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary templated functor. The functor call
                @c f() is compiled and executed if and only if
                @c ElseIfCond::value is @c true (because the if-statement static
                condition is false for this template specialization). The return
                type of @c f() must be the same as (or implicitly convertible
                to) the return type of the other functor calls specified for
                this call-if object.
    @tparam ElseIfCond  Static boolean nullary meta-function selecting which
                        functor call to compile and execute.
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed. Ultimately this will return
            the return value of the functor call being compiled and executed.
    */
    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<ElseIfCond::value, ElseIfThen> else_if(ElseIfThen f)
            const {
        return call_if_statement<ElseIfCond::value, ElseIfThen>(f);
    }
};

/**
Select compilation and execution of functor calls via a static boolean
condition.
Make a call-if object with the specified then-branch functor.
@see @RefSect{advanced_topics, Advanced Topics}
@param f    Then-branch nullary templated functor. The functor call @c f() is
            compiled and executed if and only if @c Cond if @c true. The return
            type of other functor calls specified for this call-if statement
            (else-branches, else-if-branches, etc.) must be the same as (or
            implicitly convertible to) the return type of then-branch functor
            call @c f().
@tparam Cond    Static boolean condition selecting which functor call to compile
                and execute.
@return A call-if statement so else and else-if statements can be specified if
        needed. Ultimately this will return the return value of the
        functor call being compiled and executed.
*/
template<bool Cond, typename Then>
call_if_statement<Cond, Then> call_if_c(Then f) {
    return call_if_statement<Cond, Then>(f);
}

/**
Select compilation and execution of functor calls via a static boolean nullary
meta-function.
Make a call-if object with the specified then-branch functor.
@see @RefSect{advanced_topics, Advanced Topics}
@param f    Then-branch nullary templated functor. The functor call @c f() is
            compiled and executed if and only if @c Cond::value if @c true. The
            return type of other functor calls specified for this call-if
            statement (else-branches, else-if-branches, etc.) must be the same
            as (or implicitly convertible to) the return type of then-branch
            functor call @c f().
@tparam Cond    Static boolean nullary meta-function selecting which functor
                call to compile and execute.
@return A call-if statement so else and else-if statements can be specified if
        needed. Ultimately this will return the return value of the
        functor call being compiled and executed.
*/
template<class Cond, typename Then>
call_if_statement<Cond::value, Then> call_if(Then f) {
    return call_if_statement<Cond::value, Then>(f);
}

/**
Select compilation and execution of a boolean functor check via a static boolean
condition.
Compile and execute a boolean nullary functor call if and only if the specified
static condition is true, otherwise trivially return @c true.
@see @RefSect{advanced_topics, Advanced Topics}
@param f    Boolean nullary templated functor. The functor call @c f() is
            compiled and executed if and only if @c Cond is @c true.
@tparam Cond    Static boolean condition selecting when the functor call should
                be compiled and executed.
@return Boolean value returned by @c f() if the static condition if true,
        otherwise simply return @c true (i.e., check trivially passed).
*/
template<bool Cond, typename Then>
typename boost::enable_if_c<Cond, bool>::type
condition_if_c(Then f, bool else_ = true) { return f(); }

template<bool Cond, typename Then>
typename boost::disable_if_c<Cond, bool>::type
condition_if_c(Then f, bool else_ = true) { return else_; }

/**
Select compilation and execution of a boolean functor check via a static boolean
nullary meta-function.
Compile and execute a boolean nullary functor call if and only if the specified
static condition is true, otherwise trivially return @c true.
@see @RefSect{advanced_topics, Advanced Topics}
@param f    Boolean nullary templated functor. The functor call @c f() is
            compiled and executed if and only if @c Cond::value is @c true.
@tparam Cond    Static boolean nullary meta-function selecting when the functor
                call should be compiled and executed.
@return Boolean value returned by @c f() if the static condition if true,
        otherwise simply return @c true (i.e., check trivially passed).
*/
template<class Cond, typename Then>
bool condition_if(Then f, bool else_ = true) {
    return condition_if_c<Cond::value>(f, else_);
}

} } // namespace

#endif // #include guard

