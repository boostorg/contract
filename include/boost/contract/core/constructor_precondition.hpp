
#ifndef BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Class to check constructor preconditions.
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #include <boost/contract/core/exception.hpp>
    #ifdef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
        #include <boost/contract/detail/checking.hpp>
    #endif
#endif

namespace boost { namespace contract {

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

