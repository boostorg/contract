
#ifndef BOOST_CONTRACT_SET_PRECONDITION_OLD_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_OLD_POSTCONDITION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Allow to specify preconditions, old value assignments, and postconditions.
*/

#include <boost/contract/core/set_old_postcondition.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/decl.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/condition/check_pre_post.hpp>
    #include <boost/contract/detail/auto_ptr.hpp>
    #include <boost/contract/detail/none.hpp>
#endif
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/contract/detail/debug.hpp>
#endif
#include <boost/config.hpp>

namespace boost {
    namespace contract {
        class virtual_;
    }
}

namespace boost { namespace contract {

/**
Allow to specify preconditions, old value assignments, and postconditions.
Allow to program functors this library will call to check preconditions, assign
old values before body execution, and check postconditions.
@tparam R   Return type of the function being contracted if that function is a
            non-void virtual or overriding public function, otherwise this is
            always @c void.
@see @RefSect{tutorial, Tutorial}, @RefSect{advanced_topics, Advances Topics}.
*/
template<
    typename R /* = void (already in fwd decl from decl.hpp) */
    #ifdef DOXYGEN
        = void
    #endif
>
class set_precondition_old_postcondition { // Copyable (as *).
public:
    /** Destruct this object. */
    ~set_precondition_old_postcondition() BOOST_NOEXCEPT_IF(false) {}
    
    /**
    Allow to specify preconditions.
    @param f    Functor called by this library to check preconditions. Any
                exception thrown by a call to this functor indicates a
                precondition failure. Assertions within this functor are usually
                programmed using @RefMacro{BOOST_CONTRACT_ASSERT}. This functor
                must be a nullary functor. This functor could capture variables
                by value, or better by (constant) reference to avoid extra
                copies.
    @return After preconditions have been specified, return object that allows
            to optionally specify old value assignments and postconditions.
    */
    template<typename F>
    set_old_postcondition<R> precondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_pre(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return set_old_postcondition<R>(check_.release());
        #else
            return set_old_postcondition<R>();
        #endif
    }

    /**
    Allow to specify old value assignments to execute just before function body.
    @param f    Functor called by this library to assign old values. This
                functor is called just before the function body is executed, but
                after preconditions and class invariants are checked. Old values
                are usually assigned using @RefMacro{BOOST_CONTRACT_OLDOF}. This
                functor must be a nullary functor. This functor should capture
                old value pointers (and in general all other variables) by
                (constant) reference.
    @return After old value assignments have been specified, return object that
            allows to optionally specify postconditions.
    */
    template<typename F>
    set_postcondition_only<R> old(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_old(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return set_postcondition_only<R>(check_.release());
        #else
            return set_postcondition_only<R>();
        #endif
    }

    /**
    Allow to specify postconditions.
    @param f    Functor called by this library to check postconditions. Any
                exception thrown by a call to this functor indicates a
                postcondition failure. Assertions within this functor are
                usually programmed using @RefMacro{BOOST_CONTRACT_ASSERT}. This
                functor must be a nullary functor if @c R is @c void, otherwise
                it must be unary functor taking the return value as a parameter
                of type <c>R const&</c> (to avoid extra copies, or @c R and also
                <c>R const</c> if extra copies of the return value are
                irrelevant). This functor should capture variables by
                (constant) reference.
    @return After postconditions have been specified, return object that does
            not allow to specify any additional contract (i.e., set nothing).
    */
    template<typename F>
    set_nothing postcondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_post(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return set_nothing(check_.release());
        #else
            return set_nothing();
        #endif
    }

/** @cond */
private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::detail::check_pre_post<typename
                boost::contract::detail::none_if_void<R>::type> check_type;

        explicit set_precondition_old_postcondition(check_type* check) :
                check_(check) {}

        boost::contract::detail::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).

    friend class guard;

    friend set_precondition_old_postcondition<> function();

    template<class CC>
    friend set_precondition_old_postcondition<> public_function();

    template<class CC>
    friend set_precondition_old_postcondition<> public_function(CC* oobj);
    
    template<class CC>
    friend set_precondition_old_postcondition<> public_function(
            virtual_* vv, CC* oobj);

    template<typename RR, class CC>
    friend set_precondition_old_postcondition<RR> public_function(
            virtual_* vv, RR& rr, CC* oobj);

    BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(1,
            OO, RR, FF, CC, AArgs, vv, rr, ff, oobj, aargs)
/** @endcond */
};

} } // namespace

#endif // #include guard

