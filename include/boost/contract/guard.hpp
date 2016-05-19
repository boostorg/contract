
#ifndef BOOST_CONTRACT_GUARD_HPP_
#define BOOST_CONTRACT_GUARD_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
RAII object that checks the contracts.
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
values when it is constructed. It then checks exit invariants and postconditions
when it is destructed. However, special attention in placed in marking sure
postconditions are checked only if the body did not throw an exception,
constructors never check entry invariants, destructor check exit invariants only
if their body throws, etc. (see also
@RefSect{contract_programming_overview, Contract Programming Overview}).
@see @RefSect{tutorial, Tutorial}.
*/
class guard { // Non-copyable (but copy ctor ~= move via ptr release).
public:
    /**
    Construct this object copying it from specified one.
    This object will check the contract, the copied-from object will not (i.e.,
    contract checking ownership is transfered to the this object).
    */
    guard(guard const& other) // Copy ctor moves check_ pointer to dest.
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            : check_(const_cast<guard&>(other).check_.release())
        #endif
    {}

    /**
    Construct this object from specified contract.
    Check entry invariants (as they apply for specified contract).
    Implicit so initialization operator @c = can be used.

    <b>Throws:</b>  This can throw any exception (exception specification
                    <c>noexcept(false)</c>) to allow to configure this library
                    to throw on contract failure.
    @param contract Contract to be guarded by this object.
    @tparam R   Return type of operation being contracted if that operation is a
                non-void virtual or overriding public function, otherwise this
                is always void.
    */
    template<typename R>
    /* implicit */ guard(set_precondition_old_postcondition<R> const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_GUARD_CTOR_DEF_(set_precondition_old_postcondition<R>)
    #else
        ;
    #endif
    
    /**
    Construct this object from specified contract.
    Check entry invariants (as they apply for specified contract) and check 
    preconditions.
    Implicit so initialization operator @c = can be used.

    <b>Throws:</b>  This can throw any exception (exception specification
                    <c>noexcept(false)</c>) to allow to configure this library
                    to throw on contract failure.
    @param contract Contract to be guarded by this object.
    @tparam R   Return type of operation being contracted if that operation is a
                non-void virtual or overriding public function, otherwise this
                is always void.
    */
    template<typename R>
    /* implicit */ guard(set_old_postcondition<R> const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_GUARD_CTOR_DEF_(set_old_postcondition<R>)
    #else
        ;
    #endif
    
    /**
    Construct this object from specified contract.
    Check entry invariants (as they apply for specified contract), check
    preconditions, and assign old values.
    Implicit so initialization operator @c = can be used.

    <b>Throws:</b>  This can throw any exception (exception specification
                    <c>noexcept(false)</c>) to allow to configure this library
                    to throw on contract failure.
    @param contract Contract to be guarded by this object.
    @tparam R   Return type of operation being contracted if that operation is a
                non-void virtual or overriding public function, otherwise this
                is always void.
    */
    template<typename R>
    /* implicit */ guard(set_postcondition_only<R> const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_GUARD_CTOR_DEF_(set_postcondition_only<R>)
    #else
        ;
    #endif
    
    /**
    Construct this object from specified contract.
    Check entry invariants (as they apply for specified contract), check
    preconditions, and assign old values. (In this case, the destructor of this
    object will also check postconditions.)
    Implicit so initialization operator @c = can be used.

    <b>Throws:</b>  This can throw any exception (exception specification
                    <c>noexcept(false)</c>) to allow to configure this library
                    to throw on contract failure.
    @param contract Contract to be guarded by this object.
    @tparam R   Return type of operation being contracted if that operation is a
                non-void virtual or overriding public function, otherwise this
                is always void.
    */
    /* implicit */ guard(set_nothing const& contract)
    #ifndef DOXYGEN
        BOOST_CONTRACT_GUARD_CTOR_DEF_(set_nothing)
    #else
        ;
    #endif

    /**
    Destroy this object.
    Check exit invariants (as they apply for specified contract). Check
    postconditions (if the body did not throw and postconditions where
    specified for the contract specified when constructing this object).

    <b>Throws:</b>  This can throw any exception (exception specification
                    <c>noexcept(false)</c>) to allow to configure this library
                    to throw on contract failure.
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

