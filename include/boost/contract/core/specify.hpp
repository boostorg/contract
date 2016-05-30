
#ifndef BOOST_CONTRACT_SPECIFY_HPP_
#define BOOST_CONTRACT_SPECIFY_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Facilities to specify preconditions, old value assignments, and postconditions.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/decl.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/condition/check_base.hpp>
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

        template<typename VR>
        class specify_precondition_old_postcondition;
        
        template<typename VR>
        class specify_old_postcondition;
        
        template<typename VR>
        class specify_postcondition_only;
    }
}

namespace boost { namespace contract {

/**
Used to prevent setting other contract conditions after postconditions.
This class has no member function so it is used to prevent specifying contract
functors.
@see @RefSect{tutorial, Tutorial}
*/
class specify_nothing { // Copyable (as *).
public:
    /**
    Destruct this object.
    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    */
    ~specify_nothing() BOOST_NOEXCEPT_IF(false) {}
    
    // No set member functions here.

/** @cond */
private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::detail::check_base check_type;

        explicit specify_nothing(check_type* check) : check_(check) {}
        
        boost::contract::detail::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).

    friend class guard;

    template<typename VR>
    friend class specify_precondition_old_postcondition;
    
    template<typename VR>
    friend class specify_old_postcondition;

    template<typename VR>
    friend class specify_postcondition_only;
/** @endcond */
};

/**
Allow to specify postconditions.
Allow to program functors this library will call to check postconditions.
@see @RefSect{tutorial, Tutorial}
@tparam VirtualResult   Return type of the contracted function if that is either
                        a virtual or an overriding public function, otherwise
                        this is always @c void.
*/
template<typename VirtualResult = void>
class specify_postcondition_only { // Copyable (as *).
public:
    /**
    Destruct this object.
    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    */
    ~specify_postcondition_only() BOOST_NOEXCEPT_IF(false) {}

    /**
    Allow to specify postconditions.
    @param f    Functor called by this library to check postconditions @c f().
                Postcondition assertions within this functor call are usually
                programmed using @RefMacro{BOOST_CONTRACT_ASSERT}, but any
                exception thrown by a call to this functor indicates a
                postcondition failure (and will result in this library calling
                @RefFunc{boost::contract::postcondition_failure}). This
                functor must be a nullary functor if @c VirtualResult is
                @c void, otherwise it must be a unary functor taking the return
                value as a parameter of type <c>VirtualResult const&</c> (to
                avoid extra copies, or @c VirtualResult and also
                <c>VirtualResult const</c> if extra copies of the return value
                are irrelevant). This functor should capture variables by
                (constant) references (to access the values they will have at
                function exit).
    @return After postconditions have been specified, return object that does
            not allow to specify any additional contract.
    */
    template<typename F>
    specify_nothing postcondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_post(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return specify_nothing(check_.release());
        #else
            return specify_nothing();
        #endif
    }

/** @cond */
private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::detail::check_pre_post<typename boost::contract
                ::detail::none_if_void<VirtualResult>::type> check_type;

        explicit specify_postcondition_only(check_type* check) :
                check_(check) {}
        
        boost::contract::detail::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).
    friend class guard;
    friend class specify_precondition_old_postcondition<VirtualResult>;
    friend class specify_old_postcondition<VirtualResult>;
/** @endcond */
};

/**
Allow to specify old value assignments and postconditions.
Allow to program functors this library will call to assign old values before
body execution and to check postconditions.
@see @RefSect{tutorial, Tutorial}
@tparam VirtualResult   Return type of the contracted function if that is either
                        a virtual or an overriding public function, otherwise
                        this is always @c void.
*/
template<typename VirtualResult = void>
class specify_old_postcondition { // Copyable (as *).
public:
    /**
    Destruct this object.
    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    */
    ~specify_old_postcondition() BOOST_NOEXCEPT_IF(false) {}
    
    /**
    Allow to specify old value assignments to execute just before the function
    body.
    In most cases, it should be sufficient to initialize old value pointers as
    soon as they are declared so it should not be necessary to use this function
    (see @RefSect{advanced_topics, Advanced Topics}).
    @param f    Functor called by this library to assign old values @c f(). This
                functor is called just before the function body is executed, but
                after precondition and class invariants are checked (when they
                are specified). Old value pointers within this functor call are
                usually assigned using @RefMacro{BOOST_CONTRACT_OLDOF}. Any
                exception thrown by a call to this functor is handled as a
                postcondition failure (and will result in this library calling
                @RefFunc{boost::contract::postcondition_failure} because old
                values are ultimately used to assert postconditions). This
                functor must be a nullary functor. This functor should capture
                old value pointers by references so they can be assigned (all
                other variables needed to evaluate old value expressions can be
                captured by (constant) value, or better by (constant) reference
                to avoid extra copies).
    @return After old value assignments have been specified, return object that
            allows to optionally specify postconditions.
    */
    template<typename F>
    specify_postcondition_only<VirtualResult> old(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_old(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return specify_postcondition_only<VirtualResult>(check_.release());
        #else
            return specify_postcondition_only<VirtualResult>();
        #endif
    }

    /**
    Allow to specify postconditions.
    @param f    Functor called by this library to check postconditions @c f().
                Postcondition assertions within this functor call are usually
                programmed using @RefMacro{BOOST_CONTRACT_ASSERT}, but any
                exception thrown by a call to this functor indicates a
                postcondition failure (and will result in this library calling
                @RefFunc{boost::contract::postcondition_failure}). This
                functor must be a nullary functor if @c VirtualResult is
                @c void, otherwise it must be a unary functor taking the return
                value as a parameter of type <c>VirtualResult const&</c> (to
                avoid extra copies, or @c VirtualResult and also
                <c>VirtualResult const</c> if extra copies of the return value
                are irrelevant). This functor should capture variables by
                (constant) references (to access the values they will have at
                function exit).
    @return After postconditions have been specified, return object that does
            not allow to specify any additional contract.
    */
    template<typename F>
    specify_nothing postcondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_post(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return specify_nothing(check_.release());
        #else
            return specify_nothing();
        #endif
    }

/** @cond */
private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::detail::check_pre_post<typename boost::contract
                ::detail::none_if_void<VirtualResult>::type> check_type;

        explicit specify_old_postcondition(check_type* check) :
                check_(check) {}
        
        boost::contract::detail::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).

    friend class guard;
    friend class specify_precondition_old_postcondition<VirtualResult>;

    template<class C>
    friend specify_old_postcondition<> constructor(C*);

    template<class C>
    friend specify_old_postcondition<> destructor(C*);
/** @endcond */
};

/**
Allow to specify preconditions, old value assignments, and postconditions.
Allow to program functors this library will call to check preconditions, assign
old values before body execution, and check postconditions.
@see @RefSect{tutorial, Tutorial}
@tparam VirtualResult   Return type of the contracted function if that is either
                        a virtual or an overriding public function, otherwise
                        this is always @c void.
*/
template<
    typename VirtualResult /* = void (already in fwd decl from decl.hpp) */
    #ifdef DOXYGEN
        = void
    #endif
>
class specify_precondition_old_postcondition { // Copyable (as *).
public:
    /**
    Destruct this object.
    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    */
    ~specify_precondition_old_postcondition() BOOST_NOEXCEPT_IF(false) {}
    
    /**
    Allow to specify preconditions.
    @param f    Functor called by this library to check preconditions @c f().
                Precondition assertions within this functor call are usually
                programmed using @RefMacro{BOOST_CONTRACT_ASSERT}, but any
                exception thrown by a call to this functor indicates a
                precondition failure (and will result in this library calling
                @RefFunc{boost::contract::precondition_failure}). This functor
                must be a nullary functor. This functor can capture variables by
                (constant) value, or better by (constant) reference to avoid
                extra copies.
    @return After preconditions have been specified, return object that allows
            to optionally specify old value assignments and postconditions.
    */
    template<typename F>
    specify_old_postcondition<VirtualResult> precondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_pre(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return specify_old_postcondition<VirtualResult>(check_.release());
        #else
            return specify_old_postcondition<VirtualResult>();
        #endif
    }

    /**
    Allow to specify old value assignments to execute just before the function
    body.
    In most cases, it should be sufficient to initialize old value pointers as
    soon as they are declared so it should not be necessary to use this function
    (see @RefSect{advanced_topics, Advanced Topics}).
    @param f    Functor called by this library to assign old values @c f(). This
                functor is called just before the function body is executed, but
                after precondition and class invariants are checked (when they
                are specified). Old value pointers within this functor call are
                usually assigned using @RefMacro{BOOST_CONTRACT_OLDOF}. Any
                exception thrown by a call to this functor is handled as a
                postcondition failure (and will result in this library calling
                @RefFunc{boost::contract::postcondition_failure} because old
                values are ultimately used to assert postconditions). This
                functor must be a nullary functor. This functor should capture
                old value pointers by references so they can be assigned (all
                other variables needed to evaluate old value expressions can be
                captured by (constant) value, or better by (constant) reference
                to avoid extra copies).
    @return After old value assignments have been specified, return object that
            allows to optionally specify postconditions.
    */
    template<typename F>
    specify_postcondition_only<VirtualResult> old(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_old(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return specify_postcondition_only<VirtualResult>(check_.release());
        #else
            return specify_postcondition_only<VirtualResult>();
        #endif
    }

    /**
    Allow to specify postconditions.
    @param f    Functor called by this library to check postconditions @c f().
                Postcondition assertions within this functor call are usually
                programmed using @RefMacro{BOOST_CONTRACT_ASSERT}, but any
                exception thrown by a call to this functor indicates a
                postcondition failure (and will result in this library calling
                @RefFunc{boost::contract::postcondition_failure}). This
                functor must be a nullary functor if @c VirtualResult is
                @c void, otherwise it must be a unary functor taking the return
                value as a parameter of type <c>VirtualResult const&</c> (to
                avoid extra copies, or @c VirtualResult and also
                <c>VirtualResult const</c> if extra copies of the return value
                are irrelevant). This functor should capture variables by
                (constant) references (to access the values they will have at
                function exit).
    @return After postconditions have been specified, return object that does
            not allow to specify any additional contract.
    */
    template<typename F>
    specify_nothing postcondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_post(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return specify_nothing(check_.release());
        #else
            return specify_nothing();
        #endif
    }

/** @cond */
private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::detail::check_pre_post<typename boost::contract
                ::detail::none_if_void<VirtualResult>::type> check_type;

        explicit specify_precondition_old_postcondition(check_type* check) :
                check_(check) {}

        boost::contract::detail::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).

    friend class guard;
    friend specify_precondition_old_postcondition<> function();

    template<class C>
    friend specify_precondition_old_postcondition<> public_function();

    template<class C>
    friend specify_precondition_old_postcondition<> public_function(C*);
    
    template<class C>
    friend specify_precondition_old_postcondition<> public_function(
            virtual_*, C*);

    template<typename VR, class C>
    friend specify_precondition_old_postcondition<VR> public_function(
            virtual_*, VR&, C*);

    BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(1,
            O, VR, F, C, Args, v, r, f, obj, args)
/** @endcond */
};

} } // namespace

#endif // #include guard

