
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for constructors.
*/

#include <boost/contract/detail/all_core_headers.hpp>
#if !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #include <boost/contract/detail/operation/constructor.hpp>
#endif
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #include <boost/contract/detail/check_guard.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for constructors.
This is used to specify postconditions and check class invariants for
constructors (see @RefClass{boost::contract::constructor_precondition} to
specify preconditions for constructors instead).
@see @RefSect{tutorial, Tutorial}.
@param obj The object @c this in scope of the constructor being contracted.
@return The result of this function must be assigned to variable of type
        @RefClass{boost::contract::guard} declared locally within the
        constructor being contracted.
*/
template<class C>
set_old_postcondition<> constructor(C* obj) {
    // Must #if also on ..._PRECONDITIONS here because set_... is generic.
    #if !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
        return set_old_postcondition<>(
                new boost::contract::detail::constructor<C>(obj));
    #else
        return set_old_postcondition<>();
    #endif
}

// TODO: Document that constructor_precondition for unions must be called at the very beginning of ctor body before `boost::contract::guard c = ...` (because unions cannot have base classes, not even in C++11).
/**
Program constructor preconditions.
This class must be the very first base class of the class being contracted. Also
the contracted class must privately inherit from this base class.

Unions cannot have base classes so this class can be used to declare a local
object within the constructor function just before
@RefClass{boost::contract::constructor} is used (see
@RefSect{advanced_topics, Advanced Topics}).

@see @RefSect{tutorial, Tutorial}.
@tparam C   Class of constructor being contracted (CRTP used here to avoid
            multiple instances of same base class error).
*/
template<class C>
class constructor_precondition { // Copyable (no data).
public:
    /** Construct this object for constructor that do not have preconditions. */
    constructor_precondition() {}

    /**
    Constructor this object specifying constructor preconditions.
    @param f    Functor called by this library to check preconditions. Any
                exception thrown by a call to this functor indicates a
                precondition failure. Assertions within this functor are usually
                programmed using @RefMacro{BOOST_CONTRACT_ASSERT}. This functor
                must be a nullary functor. This functor could capture variables
                by value, or better by (constant) reference to void extra
                copies.
    */
    template<typename F>
    explicit constructor_precondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            if(boost::contract::detail::check_guard::checking()) return;
            try {
                #ifndef BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                    boost::contract::detail::check_guard checking;
                #endif
                f();
            } catch(...) { precondition_failure(from_constructor); }
        #endif
    }

    // Default copy operations (so user's derived classes can be copied, etc.).
};

} } // namespace

#endif // #include guard

