
#ifndef BOOST_CONTRACT_CALL_IF_HPP_
#define BOOST_CONTRACT_CALL_IF_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Statically disable execution but also compilation of functor calls.
*/

// Do not include all_core_headers here (call_if is essentially standalone).
#include <boost/contract/detail/always_true.hpp>
#include <boost/contract/detail/none.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
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
Unspecialized class template to control execution and compilation of functor
calls via a static boolean condition.
This class template has no member because it should never be used directly, it
should only be used via its specializations.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam Cond Static boolean condition controlling functor calls.
@tparam Then Type of functor to call when the static condition if true.
@tparam R Return type of then-branch functor.
*/
template<bool Cond, typename Then, typename R =
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
@note   <c>result_of<Then()></c> should be evaluated only when the static
        condition is already checked to be true (because @c Then() is
        required to compile only in that case). Thus, this template
        specialization introduces an extra level of indirectly necessary to the
        proper lazy evaluation of that result-of.
The base class is a call-if statement so the else statement and other else-if
can be specified if needed. Ultimately this will return the return value of the
functor being compiled and called.
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
    @param f    Then-branch nullary functor, called or compiled in this case.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    */
    explicit call_if_statement(Then f) : call_if_statement<true, Then,
            BOOST_CONTRACT_CALL_IF_RESULT_OF_(Then)>(f) {}
};

/**
Template specialization to handle true static conditions for then-branch functor
calls returning non-void.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam Then Type of functor to call when the static condition if true.
@tparam R Non-void return type of the then-branch functor call.
*/
template<typename Then, typename R>
struct call_if_statement<true, Then, R> { // Copyable (as *).
    /**
    Construct this object with the then-branch functor.
    @param f    Then-branch nullary functor, called and compiled in this case.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    */
    explicit call_if_statement(Then f) : r_(boost::make_shared<R>(f())) {}

    /** Return value returned by the call to the then-branch functor. */
    operator R const&() const { return *r_; }

    /** Return value returned by the call to the then-branch functor. */
    operator R&() { return *r_; }

    /**
    Specify the else-branch functor.
    @param f    Else-branch nullary functor, never called or compiled in this
                case.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    @return Return value returned by the call to the then-branch functor.
    */
    template<typename Else>
    R const& else_(Else const& f) const { return *r_; }
    
    /**
    Specify the else-branch functor.
    @param f    Else-branch nullary functor, never called or compiled in this
                case.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    @return Return value returned by the call to the then-branch functor.
    */
    template<typename Else>
    R& else_(Else const& f) { return *r_; }

    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary functor, never called or compiled in this
                case.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    @tparam ElseIfCond Static boolean condition controlling functor calls.
    @return The call-if statement so the else statement and other else-if can be
            specified if needed. Ultimately will return the return value of the
            then-branch functor in this case.
    */
    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, R> else_if_c(ElseIfThen const& f) const {
        return *this;
    }

    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary functor, never called or compiled in this
                case.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    @tparam ElseIfCond  Static boolean nullary meta-function controlling functor
                        calls.
    @return The call-if statement so the else statement and other else-if can be
            specified if needed. Ultimately will return the return value of the
            then-branch functor in this case.
    */
    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, R> else_if(ElseIfThen const& f) const {
        return *this;
    }
    
private:
    boost::shared_ptr<R> r_;
};

/**
Template specialization to handle true static conditions for then-branch functor
calls returning void.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam Then Type of functor to call when the static condition if true.
*/
template<typename Then>
struct call_if_statement<true, Then, void> { // Copyable (no data).
    /**
    Construct this object with the then-branch functor.
    @param f    Then-branch nullary functor, called and compiled in this case.
                The return type of this functor as well as of all other
                specified functors for the call-if object must be @c void in
                this case.
    */
    explicit call_if_statement(Then f) { f(); }
    
    // Cannot provide `operator R()` here, because R is void.

    /**
    Specify the else-branch functor.
    @param f    Else-branch nullary functor, never called or compiled in this
                case.
                The return type of this functor as well as of all other
                specified functors for the call-if object must be @c void in
                this case.
    */
    template<typename Else>
    void else_(Else const& f) const {}
    
    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary functor, never called or compiled in this
                case.
                The return type of this functor as well as of all other
                specified functors for the call-if object must be @c void in
                this case.
    @tparam ElseIfCond Static boolean condition controlling functor calls.
    @return The call-if statement so the else statement and other else-if can be
            specified if needed. Ultimately @c void will be returned in this
            case.
    */
    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, void> else_if_c(ElseIfThen const& f) const {
        return *this;
    }

    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary functor, never called or compiled in this
                case.
                The return type of this functor as well as of all other
                specified functors for the call-if object must be @c void in
                this case.
    @tparam ElseIfCond  Static boolean nullary meta-function controlling functor
                        calls.
    @return The call-if statement so the else statement and other else-if can be
            specified if needed. Ultimately @c void will be returned in this
            case.
    */
    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, void> else_if(ElseIfThen const& f) const {
        return *this;
    }
};

/**
Template specialization to handle false static conditions.
This single specialization can handle both else-branch functor calls that
return void and that return non-void.
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
    @param f    Then-branch nullary functor, never called or compiled in this
                case.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    */
    explicit call_if_statement(Then const& f) {}

    // Do not provide `operator result_type()` here, require else_ instead.

    /**
    Specify the else-branch functor.
    @note   <c>result_of<Else()></c> should be evaluated only when the static
            condition is already checked to be false (because @c Else() is
            required to compile only in that case). Thus, that result-of is
            evaluate lazily only in this template instantiation.
    @param f    Else-branch nullary functor, called and compiled in this case.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    @return The return value of the call to the else-branch functor.
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
    @param f    Else-if-branch nullary functor, called and compiled if and only
                if @c ElseIfCond is @c true.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    @tparam ElseIfCond Static boolean condition controlling functor calls.
    @return The call-if statement so the else statement and other else-if can be
            specified if needed. Ultimately will return the return value of the
            functor call being compiled and executed.
    */
    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<ElseIfCond, ElseIfThen> else_if_c(ElseIfThen f) const {
        return call_if_statement<ElseIfCond, ElseIfThen>(f);
    }
    
    /**
    Specify an else-if-branch functor.
    @param f    Else-if-branch nullary functor, called and compiled if and only
                if @c ElseIfCond::value is @c true.
                The return type of this functor must be the same or implicitly
                convertible into the return type of all other functors specified
                for the call-if object.
    @tparam ElseIfCond  Static boolean nullary meta-function controlling functor
                        calls.
    @return The call-if statement so the else statement and other else-if can be
            specified if needed. Ultimately will return the return value of the
            functor call being compiled and executed.
    */
    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<ElseIfCond::value, ElseIfThen> else_if(ElseIfThen f)
            const {
        return call_if_statement<ElseIfCond::value, ElseIfThen>(f);
    }
};

/**
Make a call-if object with the specified then-branch functor
@param f    Then-branch nullary functor, called and compiled if and only if
            @c Cond if @c true.
            The return type of this functor must be the same or implicitly
            convertible into the return type of all other functors specified
            for the call-if object.
@tparam Cond Static boolean condition controlling functor compilation and calls.
@return The call-if statement so the else statement and other else-if can be
        specified if needed. Ultimately will return the return value of the
        functor call being compiled and executed.
*/
template<bool Cond, typename Then>
call_if_statement<Cond, Then> call_if_c(Then f) {
    return call_if_statement<Cond, Then>(f);
}

/**
Make a call-if object with the specified then-branch functor
@param f    Then-branch nullary functor, called and compiled if and only if
            @c Cond::value if @c true.
            The return type of this functor must be the same or implicitly
            convertible into the return type of all other functors specified
            for the call-if object.
@tparam Cond Static boolean nullary meta-function controlling functor calls.
@return The call-if statement so the else statement and other else-if can be
        specified if needed. Ultimately will return the return value of the
        functor call being compiled and executed.
*/
template<class Cond, typename Then>
call_if_statement<Cond::value, Then> call_if(Then f) {
    return call_if_statement<Cond::value, Then>(f);
}

/**
Return value of specified functor call if and only if specified static condition
is true, otherwise return true.
@param f    Nullary boolean functor to call and compile if and only if @c Cond
            is @c true.
@tparam Cond Static boolean condition controlling functor compilation and call.
@return Boolean value returned by @c f() if static condition if true, otherwise
        simply return @c true (i.e., check trivially passed).
*/
template<bool Cond, typename F>
bool check_if_c(F f) {
    return call_if_c<Cond>(f).else_(
            boost::contract::detail::always_true());
}

/**
Return value of specified functor call if and only if specified static condition
is true, otherwise return true.
@param f    Nullary boolean functor to call and compile if and only if
            @c Cond::value is @c true.
@tparam Cond Static boolean nullary meta-function controlling functor calls.
@return Boolean value returned by @c f() if static condition if true, otherwise
        simply return @c true (i.e., check trivially passed).
*/
template<class Cond, typename F>
bool check_if(F f) {
    return call_if_c<Cond::value>(f).else_(
            boost::contract::detail::always_true());
}

} } // namespace

#endif // #include guard

