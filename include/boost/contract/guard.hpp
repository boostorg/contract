
#ifndef BOOST_CONTRACT_GUARD_HPP_
#define BOOST_CONTRACT_GUARD_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
RAII object to check contracts.
*/

#include <boost/contract/detail/all_core_headers.hpp>
#include <boost/contract/detail/condition/check_base.hpp>
#include <boost/contract/detail/auto_ptr.hpp>
#include <boost/contract/detail/debug.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #define BOOST_CONTRACT_GUARD_CTOR_DEF_(contract_type) \
            : check_(const_cast<contract_type&>(contract).check_.release()) \
        { \
            BOOST_CONTRACT_DETAIL_DEBUG(check_); \
            check_->guard(); \
        }
#else
    #define BOOST_CONTRACT_GUARD_CTOR_DEF_(contract_type) {}
#endif

/** @endcond */

/* CODE */

namespace boost { namespace contract {

/**
RAII object that checks the contracts.
In general, this object checks entry invariants, preconditions, and assigns old
values when it is constructed. Then it checks exit invariants and postconditions
when it is destructed. In addition, this object markes sure that postconditions
are checked only if the body does not throw an exception, constructors never
check entry invariants, destructors check exit invariants only if their bodies
throw an exception, static invariants are always checked at entry and exit, etc.
(see also @RefSect{contract_programming_overview,
Contract Programming Overview}).
@see @RefSect{tutorial, Tutorial}
*/
class guard { // Copy ctor only (as move via ptr release).
public:
    /**
    Construct this object copying it from the specified one.
    This object will check the contract, the copied-from object will not (i.e.,
    contract checking ownership is transfered from the copied object to this
    object).
    */
    guard(guard const& other) // Copy ctor moves check_ pointer to dest.
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            : check_(const_cast<guard&>(other).check_.release())
        #endif
    {}

    /**
    Construct this object from the specified contract.
    Check entry invariants (if they apply to the specified contract).
    This constructor is not @c explicit so initializations can use operator @c =
    syntax.

    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    @param contract Contract to be checked.
    @tparam VirtualResult   Return type of the contracted function if that is
                            either a virtual or an overriding public function,
                            otherwise this is always @c void.
    */
    template<typename VirtualResult>
    /* implicit */ guard(specify_precondition_old_postcondition<VirtualResult>
            const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_GUARD_CTOR_DEF_(
                specify_precondition_old_postcondition<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object from the specified contract.
    Check entry invariants (if they apply to the specified contract) and check 
    preconditions.
    This constructor is not @c explicit so initializations can use operator @c =
    syntax.

    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    @param contract Contract to be checked.
    @tparam VirtualResult   Return type of the contracted function if that is
                            either a virtual or an overriding public function,
                            otherwise this is always @c void.
    */
    template<typename VirtualResult>
    /* implicit */ guard(specify_old_postcondition<VirtualResult> const&
            contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_GUARD_CTOR_DEF_(specify_old_postcondition<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object from the specified contract.
    Check entry invariants (if they apply to the specified contract) and check 
    preconditions, and assign old values.
    This constructor is not @c explicit so initializations can use operator @c =
    syntax.

    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    @param contract Contract to be checked.
    @tparam VirtualResult   Return type of the contracted function if that is
                            either a virtual or an overriding public function,
                            otherwise this is always @c void.
    */
    template<typename VirtualResult>
    /* implicit */ guard(specify_postcondition_only<VirtualResult> const&
            contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_GUARD_CTOR_DEF_(
                specify_postcondition_only<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object from the specified contract.
    Check entry invariants (if they apply to the specified contract) and check 
    preconditions, and assign old values (plus the destructor of this object
    will also check postconditions in this case).
    This constructor is not @c explicit so initializations can use operator @c =
    syntax.

    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    @param contract Contract to be checked.
    */
    /* implicit */ guard(specify_nothing const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_GUARD_CTOR_DEF_(specify_nothing)
    #else
        ;
    #endif

    /**
    Destruct this object.
    Check exit invariants (if they apply to the contract specified at
    construction) and postconditions (if the body did not throw and
    postconditions apply to the contract specified at construction).

    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_postcondition_failure}, etc.).
    */
    ~guard() BOOST_NOEXCEPT_IF(false) {} // Allow auto_ptr dtor to throw.

/** @cond */
private:
    guard& operator=(guard const&); // Cannot copy outside of `guard c = ...`.

    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        boost::contract::detail::auto_ptr<boost::contract::detail::check_base>
                check_;
    #endif
/** @endcond */
};

} } // namespace

#endif // #include guard

