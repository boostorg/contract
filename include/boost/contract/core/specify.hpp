
#ifndef BOOST_CONTRACT_SPECIFY_HPP_
#define BOOST_CONTRACT_SPECIFY_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// TODO: Document that set_except_failure shall never be set to throw because that will cause the contract failure handler to throw an exception while there's already an active exception (the reason .except() functor is being executed) so C++ will always call std::terminate in this case (again, not a good idea to throw on contract failures, especially from destructors but also for all .except() failures).

/** @file
Facilities to specify preconditions, old value assignments, and postconditions.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/decl.hpp>
#if     defined(BOOST_CONTRACT_STATIC_LINK) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/contract/detail/condition/cond_base.hpp>
    #include <boost/contract/detail/condition/cond_post.hpp>
    #include <boost/contract/detail/auto_ptr.hpp>
    #include <boost/contract/detail/none.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/contract/detail/debug.hpp>
#endif
#include <boost/config.hpp>

// NOTE: No inheritance for faster run-times (macros to avoid duplicated code).

/* PRIVATE */

#if     defined(BOOST_CONTRACT_STATIC_LINK) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #define BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(class_type, cond_type) \
        /* data member */ \
        boost::contract::detail::auto_ptr<cond_type> cond_; \
        /* constructor */ \
        explicit class_type(cond_type* cond) : cond_(cond) {} \
        /* copy operations (private to force `auto c = ...` error) */ \
        class_type(class_type const& other) : cond_(other.cond_) {} \
        class_type& operator=(class_type const& other) { \
            cond_ = other.cond_; \
            return *this; \
        }
    
    #define BOOST_CONTRACT_SPECIFY_COND_RELEASE_ cond_.release()
#else
    #define BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(class_type, cond_type) \
        /* (default) constructor */ \
        class_type() {} \
        /* copy operations (private to force `auto c = ...` error) */ \
        class_type(class_type const&) {} \
        class_type& operator=(class_type const&) {}

    #define BOOST_CONTRACT_SPECIFY_COND_RELEASE_ /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #define BOOST_CONTRACT_SPECIFY_PRECONDITION_IMPL_ \
        BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
        cond_->set_pre(f); \
        return specify_old_postcondition_except<VirtualResult>( \
                BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#else
    #define BOOST_CONTRACT_SPECIFY_PRECONDITION_IMPL_ \
        return specify_old_postcondition_except<VirtualResult>( \
                BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#endif
        
#if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #define BOOST_CONTRACT_SPECIFY_OLD_IMPL_ \
        BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
        cond_->set_old(f); \
        return specify_postcondition_except<VirtualResult>( \
                BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#else
    #define BOOST_CONTRACT_SPECIFY_OLD_IMPL_ \
        return specify_postcondition_except<VirtualResult>( \
                BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#endif
            
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #define BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_ \
        BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
        cond_->set_post(f); \
        return specify_except(BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#else
    #define BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_ \
        return specify_except(BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#endif
        
#ifndef BOOST_CONTRACT_NO_EXCEPTS
    #define BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_ \
        BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
        cond_->set_except(f); \
        return specify_nothing(BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#else
    #define BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_ \
        return specify_nothing(BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#endif

/* CODE */

namespace boost {
    namespace contract {
        class virtual_;
        
        template<typename VR>
        class specify_precondition_old_postcondition_except;
        
        template<typename VR>
        class specify_old_postcondition_except;
        
        template<typename VR>
        class specify_postcondition_except;
        
        class specify_except;
    }
}

namespace boost { namespace contract {

/**
Used to prevent setting other contract conditions after postconditions.
This class has no member function so it is used to prevent specifying contract
functors.
@see @RefSect{tutorial, Tutorial}
*/
class specify_nothing { // Privately copyable (as *).
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
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(specify_nothing,
            boost::contract::detail::cond_base)

    // Friends (used to limit library's public API).

    friend class check;

    template<typename VR>
    friend class specify_precondition_old_postcondition_except;
    
    template<typename VR>
    friend class specify_old_postcondition_except;

    template<typename VR>
    friend class specify_postcondition_except;

    friend class specify_except;
/** @endcond */
};

class specify_except { // Privately copyable (as *).
public:
    ~specify_except() BOOST_NOEXCEPT_IF(false) {}

    template<typename F>
    specify_nothing except(F const& f) {
        BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_
    }

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(specify_except,
            boost::contract::detail::cond_base)

    // Friends (used to limit library's public API).

    friend class check;

    template<typename VR>
    friend class specify_precondition_old_postcondition_except;
    
    template<typename VR>
    friend class specify_old_postcondition_except;
    
    template<typename VR>
    friend class specify_postcondition_except;
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
class specify_postcondition_except { // Privately copyable (as *).
public:
    /**
    Destruct this object.
    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    */
    ~specify_postcondition_except() BOOST_NOEXCEPT_IF(false) {}

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
    specify_except postcondition(F const& f) {
        BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_
    }
    
    template<typename F>
    specify_nothing except(F const& f) {
        BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_
    }

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(
        specify_postcondition_except,
        boost::contract::detail::cond_post<typename
                boost::contract::detail::none_if_void<VirtualResult>::type>
    )

    // Friends (used to limit library's public API).

    friend class check;
    friend class specify_precondition_old_postcondition_except<VirtualResult>;
    friend class specify_old_postcondition_except<VirtualResult>;
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
class specify_old_postcondition_except { // Privately copyable (as *).
public:
    /**
    Destruct this object.
    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    */
    ~specify_old_postcondition_except() BOOST_NOEXCEPT_IF(false) {}
    
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
    specify_postcondition_except<VirtualResult> old(F const& f) {
        BOOST_CONTRACT_SPECIFY_OLD_IMPL_
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
    specify_except postcondition(F const& f) {
        BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_
    }
    
    template<typename F>
    specify_nothing except(F const& f) {
        BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_
    }

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(
        specify_old_postcondition_except,
        boost::contract::detail::cond_post<typename
                boost::contract::detail::none_if_void<VirtualResult>::type>
    )

    // Friends (used to limit library's public API).

    friend class check;
    friend class specify_precondition_old_postcondition_except<VirtualResult>;

    template<class C>
    friend specify_old_postcondition_except<> constructor(C*);

    template<class C>
    friend specify_old_postcondition_except<> destructor(C*);
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
class specify_precondition_old_postcondition_except { // Priv. copyable (as *).
public:
    /**
    Destruct this object.
    @b Throws:  This can throw (i.e., @c noexcept(false)) in case programmers
                specify failure handlers that throw exceptions instead of
                terminating the program (see
                @RefFunc{boost::contract::set_precondition_failure}, etc.).
    */
    ~specify_precondition_old_postcondition_except() BOOST_NOEXCEPT_IF(false) {}
    
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
    specify_old_postcondition_except<VirtualResult> precondition(F const& f) {
        BOOST_CONTRACT_SPECIFY_PRECONDITION_IMPL_
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
    specify_postcondition_except<VirtualResult> old(F const& f) {
        BOOST_CONTRACT_SPECIFY_OLD_IMPL_
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
    specify_except postcondition(F const& f) {
        BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_
    }
    
    template<typename F>
    specify_nothing except(F const& f) {
        BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_
    }

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(
        specify_precondition_old_postcondition_except,
        boost::contract::detail::cond_post<typename
                boost::contract::detail::none_if_void<VirtualResult>::type>
    )

    // Friends (used to limit library's public API).

    friend class check;
    friend specify_precondition_old_postcondition_except<> function();

    template<class C>
    friend specify_precondition_old_postcondition_except<> public_function();

    template<class C>
    friend specify_precondition_old_postcondition_except<> public_function(C*);
    
    template<class C>
    friend specify_precondition_old_postcondition_except<> public_function(
            virtual_*, C*);

    template<typename VR, class C>
    friend specify_precondition_old_postcondition_except<VR> public_function(
            virtual_*, VR&, C*);

    BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(1,
            O, VR, F, C, Args, v, r, f, obj, args)
/** @endcond */
};

} } // namespace

#endif // #include guard

