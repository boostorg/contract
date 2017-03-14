
#ifndef BOOST_CONTRACT_CHECK_HPP_
#define BOOST_CONTRACT_CHECK_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
RAII object to check contracts.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/check_macro.hpp>
#include <boost/contract/core/specify.hpp>
#include <boost/contract/core/exception.hpp> // For set_... (if always in code).
#if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/condition/cond_base.hpp>
    #include <boost/contract/detail/auto_ptr.hpp>
    #include <boost/contract/detail/debug.hpp>
#endif
#include <boost/contract/detail/check.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

#if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    #define BOOST_CONTRACT_CHECK_CTOR_DEF_(contract_type) \
        : cond_(const_cast<contract_type&>(contract).cond_.release()) \
        { \
            BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
            cond_->initialize(); \
        }
#else
    #define BOOST_CONTRACT_CHECK_CTOR_DEF_(contract_type) {}
#endif

/** @endcond */

/* CODE */

namespace boost { namespace contract {

/**
RAII object that checks the contracts.

In general, this object checks entry invariants, preconditions, and assigns old
values when it is constructed.
Then it checks exit invariants and postconditions or exception guarantees when
it is destructed.
That said, this object also enforces the following (see also
@RefSect{contract_programming_overview, Contract Programming Overview}):

@li Postconditions are checked only if the body does not throw an exception.
@li Exceptions guarantee are checked only if the body throws an exception.
@li Constructors never check entry invariants.
@li Destructors check exit invariants only if their bodies throw an exception.
@li Static invariants are always checked at entry and exit, etc.

Plus, one of the constructors of this object can be used to program
implementation checks.

@see    @RefSect{tutorial, Tutorial},
        @RefSect{advanced_topics.implementation_checks, Implementation Checks}
*/
class check { // Copy ctor only (as move via ptr release).
public:
    // f must be a valid callable object (not null func ptr, empty ftor, etc.
    /**
    Construct this object for implementation checks.

    This can be used to program checks within implementation code (body, etc.).
    
    @b Throws:  This can throw (i.e., declared @c noexcept(false)) in case
                programmers specify failure handlers that throw exceptions
                instead of terminating the program (see
                @RefSect{advanced_topics.throw_on_failure, Throw on Failure}).

    @param f    Nullary functor that asserts implementation checks @c f() will
                be called as soon as this object is constructed at the point it
                is declared within the body code.
    */
    template<typename F> // Cannot check `if(f) ...` as f can be a lambda.
    /* implicit */ check(F const& f) { BOOST_CONTRACT_DETAIL_CHECK({ f(); }) }

    /**
    Construct this object copying it from the specified one.

    This object will check the contract, the copied-from object will not (i.e.,
    contract check ownership is transferred from the copied object to the new
    object being created by this constructor).

    @param other    Copied-from object.
    */
    check(check const& other) // Copy ctor moves cond_ pointer to dest.
        #if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
                defined(BOOST_CONTRACT_STATIC_LINK)
            : cond_(const_cast<check&>(other).cond_.release())
        #endif
    {}

    /**
    Construct this object from the specified contract.

    Check entry invariants (if they apply to the specified contract).
    This constructor is not declared @c explicit so initializations can use
    operator @c = syntax.
    
    @b Throws:  This can throw (i.e., declared @c noexcept(false)) in case
                programmers specify failure handlers that throw exceptions
                instead of terminating the program (see
                @RefSect{advanced_topics.throw_on_failure, Throw on Failure}).

    @param contract Contract to be checked.

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function.
                            Otherwise, this is always @c void.
    */
    template<typename VirtualResult>
    /* implicit */ check(specify_precondition_old_postcondition_except<
            VirtualResult> const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(
                specify_precondition_old_postcondition_except<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object from the specified contract.

    Check entry invariants (if they apply to the specified contract) and check 
    preconditions.
    This constructor is not declared @c explicit so initializations can use
    operator @c = syntax.
    
    @b Throws:  This can throw (i.e., declared @c noexcept(false)) in case
                programmers specify failure handlers that throw exceptions
                instead of terminating the program (see
                @RefSect{advanced_topics.throw_on_failure, Throw on Failure}).

    @param contract Contract to be checked.

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function.
                            Otherwise, this is always @c void.
    */
    template<typename VirtualResult>
    /* implicit */ check(specify_old_postcondition_except<VirtualResult> const&
            contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(
                specify_old_postcondition_except<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object from the specified contract.

    Check entry invariants (if they apply to the specified contract) and check 
    preconditions, and assign old values.
    This constructor is not declared @c explicit so initializations can use
    operator @c = syntax.
    
    @b Throws:  This can throw (i.e., declared @c noexcept(false)) in case
                programmers specify failure handlers that throw exceptions
                instead of terminating the program (see
                @RefSect{advanced_topics.throw_on_failure, Throw on Failure}).

    @param contract Contract to be checked.

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function.
                            Otherwise, this is always @c void.
    */
    template<typename VirtualResult>
    /* implicit */ check(specify_postcondition_except<VirtualResult> const&
            contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(
                specify_postcondition_except<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object from the specified contract.

    Check entry invariants (if they apply to the specified contract) and check 
    preconditions, and assign old values (plus the destructor of this object
    will also check postconditions in this case).
    This constructor is not declared @c explicit so initializations can use
    operator @c = syntax.
    
    @b Throws:  This can throw (i.e., declared @c noexcept(false)) in case
                programmers specify failure handlers that throw exceptions
                instead of terminating the program (see
                @RefSect{advanced_topics.throw_on_failure, Throw on Failure}).

    @param contract Contract to be checked.

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function.
                            Otherwise, this is always @c void.
    */
    /* implicit */ check(specify_except const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(specify_except)
    #else
        ;
    #endif
    
    /**
    Construct this object from the specified contract.

    Check entry invariants (if they apply to the specified contract) and check 
    preconditions, and assign old values (plus the destructor of this object
    will also check postconditions and exception guarantees in this case).
    This constructor is not declared @c explicit so initializations can use
    operator @c = syntax.
    
    @b Throws:  This can throw (i.e., declared @c noexcept(false)) in case
                programmers specify failure handlers that throw exceptions
                instead of terminating the program (see
                @RefSect{advanced_topics.throw_on_failure, Throw on Failure}).

    @param contract Contract to be checked.

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function.
                            Otherwise, this is always @c void.
    */
    /* implicit */ check(specify_nothing const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(specify_nothing)
    #else
        ;
    #endif

    /**
    Destruct this object.
    Check exit invariants (if they apply to the contract specified at
    construction) and postconditions (if they apply to the contract specified at
    construction and the enclosing function body did not throw) or exception
    guarantees (if they apply to the contract specified at construction and the
    enclosing function body threw).

    @b Throws:  This can throw (i.e., declared @c noexcept(false)) in case
                programmers specify failure handlers that throw exceptions
                instead of terminating the program (see
                @RefSect{advanced_topics.throw_on_failure, Throw on Failure}).
    */
    ~check() BOOST_NOEXCEPT_IF(false) {} // Allow auto_ptr dtor to throw.

/** @cond */
private:
    check& operator=(check const&); // Cannot copy outside of `check c = ...`.

    #if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
            defined(BOOST_CONTRACT_STATIC_LINK)
        boost::contract::detail::auto_ptr<boost::contract::detail::cond_base>
                cond_;
    #endif
/** @endcond */
};

} } // namespace

#endif // #include guard

