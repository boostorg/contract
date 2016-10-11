
#ifndef BOOST_CONTRACT_CHECK_HPP_
#define BOOST_CONTRACT_CHECK_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// TODO: Experiment some more so see if using auto instead of explicit boost::checking can generate a compile time error (instead of just a run-time uninitialized error).

/** @file
RAII object to check contracts.
*/

#include <boost/contract/detail/all_core_headers.hpp>
#include <boost/contract/detail/condition/cond_base.hpp>
#include <boost/contract/detail/assert.hpp>
#ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
    #include <boost/contract/detail/checking.hpp>
#endif
#include <boost/contract/detail/auto_ptr.hpp>
#include <boost/contract/detail/debug.hpp>
#include <boost/contract/detail/name.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

#if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #define BOOST_CONTRACT_CHECK_CTOR_DEF_(contract_type) \
        : cond_(const_cast<contract_type&>(contract).cond_.release()) \
        { \
            BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
            cond_->initialize(); \
        }
#else
    #define BOOST_CONTRACT_CHECK_CTOR_DEF_(contract_type) {}
#endif

#ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
    #define BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ \
        if(!boost::contract::detail::checking::already())
    #define BOOST_CONTRACT_CHECK_CHECKING_VAR_(guard) \
        /* this name somewhat unique to min var shadow warnings */ \
        boost::contract::detail::checking BOOST_CONTRACT_DETAIL_NAME2( \
                guard, __LINE__);
#else
    #define BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ /* nothing */
    #define BOOST_CONTRACT_CHECK_CHECKING_VAR_(guard) /* nothing */
#endif
        
#ifndef BOOST_CONTRACT_NO_CHECKS
    #define BOOST_CONTRACT_CHECK_(assertion) \
        { \
            try { \
                BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ \
                { \
                    BOOST_CONTRACT_CHECK_CHECKING_VAR_(k) \
                    { assertion; } \
                } \
            } catch(...) { boost::contract::check_failure(); } \
        }
#else
    #define BOOST_CONTRACT_CHECK_(assertion) {}
#endif

/** @endcond */

/* PUBLIC */

// Requires trailing semicolon to be consistent with ASSERT.
#define BOOST_CONTRACT_CHECK(condition) \
    BOOST_CONTRACT_CHECK_(BOOST_CONTRACT_DETAIL_ASSERT(condition))

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
class check { // Copy ctor only (as move via ptr release).
public:
    // f must be a valid callable object (not null func ptr, empty ftor, etc.
    template<typename F> // Cannot check `if(f) ...` as f can be a lambda.
    /* implicit */ check(F const& f) { BOOST_CONTRACT_CHECK_({ f(); }) }

    /**
    Construct this object copying it from the specified one.
    This object will check the contract, the copied-from object will not (i.e.,
    contract check ownership is transfered from the copied object to this
    object).
    */
    check(check const& other) // Copy ctor moves cond_ pointer to dest.
        #if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
                !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_EXCEPTS)
            : cond_(const_cast<check&>(other).cond_.release())
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
    /* implicit */ check(specify_postcondition_except<VirtualResult> const&
            contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(
                specify_postcondition_except<VirtualResult>)
    #else
        ;
    #endif
    
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
    will also check postconditions in this case).
    This constructor is not @c explicit so initializations can use operator @c =
    syntax.

    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    @param contract Contract to be checked.
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
    construction) and postconditions (if the body did not throw and
    postconditions apply to the contract specified at construction).

    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_postcondition_failure}, etc.).
    */
    ~check() BOOST_NOEXCEPT_IF(false) {} // Allow auto_ptr dtor to throw.

/** @cond */
private:
    check& operator=(check const&); // Cannot copy outside of `check c = ...`.

    #if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        boost::contract::detail::auto_ptr<boost::contract::detail::cond_base>
                cond_;
    #endif
/** @endcond */
};

} } // namespace

#endif // #include guard

