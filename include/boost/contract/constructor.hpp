
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
#if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #include <boost/contract/detail/operation/constructor.hpp>
#endif
#if     !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #include <boost/contract/detail/checking.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for constructors.
This is used to specify postconditions, old value assignments at body, and
check class invariants for constructors (see
@RefClass{boost::contract::constructor_precondition} to specify preconditions
for constructors instead).

For optimization, this can be omitted for constructors that do not have
postconditions when the enclosing class has no invariants.
@see @RefSect{tutorial, Tutorial}
@param obj The object @c this from the scope of the contracted constructor.
@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::guard} declared locally just before the body
        of the contracted constructor (otherwise this library will generate a
        run-time error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
*/
template<class Class>
specify_old_postcondition_except<> constructor(Class* obj) {
    // Must #if also on ..._PRECONDITIONS here because specify_... is generic.
    #if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
        return specify_old_postcondition_except<>(
                new boost::contract::detail::constructor<Class>(obj));
    #else
        return specify_old_postcondition_except<>();
    #endif
}

/**
Program preconditions for constructors.
This class must be the very first base class of the contracted class. Also the
contracted class shall privately inherit from this base class (to not alter the
contracted class public interface).

Unions cannot have base classes in C++ so this class can be used to declare a
local object within the constructor function just before
@RefFunc{boost::contract::constructor} is used (see
@RefSect{advanced_topics, Advanced Topics}).
@see @RefSect{tutorial, Tutorial}
@tparam Class Class of contracted constructor.
*/
template<class Class>
class constructor_precondition { // Copyable (has no data).
public:
    /**
    Construct this object without specifying constructor preconditions.
    This is implicitly called for those constructors of the contracted class
    that do not specify preconditions.
    */
    constructor_precondition() {}

    /**
    Construct this object specifying constructor preconditions.
    @param f    Functor called by this library to check constructor
                preconditions @c f(). Precondition assertions within this
                functor call are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a precondition failure (and will
                result in this library calling
                @RefFunc{boost::contract::precondition_failure}). This functor
                must be a nullary functor. This functor can capture variables by
                value, or better by (constant) reference to avoid extra copies.
    */
    template<typename F>
    explicit constructor_precondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            try {
                #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                    if(boost::contract::detail::checking::already()) return;
                    #ifndef BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                        boost::contract::detail::checking k;
                    #endif
                #endif
                f();
            } catch(...) { precondition_failure(from_constructor); }
        #endif
    }

    // Default copy operations (so user's derived classes can be copied, etc.).
};

} } // namespace

#endif // #include guard

