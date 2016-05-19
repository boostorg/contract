
#ifndef BOOST_CONTRACT_OLD_HPP_
#define BOOST_CONTRACT_OLD_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Facilities for old values.
*/

#include <boost/contract/detail/all_core_headers.hpp>
#include <boost/contract/detail/check_guard.hpp>
#include <boost/contract/detail/operator_safe_bool.hpp>
#include <boost/contract/detail/debug.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_copy_constructible.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/config/config.hpp>

#if !BOOST_PP_VARIADICS

#define BOOST_CONTRACT_OLDOF \
BOOST_CONTRACT_ERROR_macro_OLDOF_requires_variadic_macros_otherwise_manually_program_old_values

#else // variadics

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
    #define BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value) /* nothing */
#else
    #include <boost/typeof/typeof.hpp>
    // Explicitly force old_ptr<...> conversion to allow for C++11 auto decl.
    #define BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value) \
        boost::contract::old_ptr<BOOST_TYPEOF(value)>
#endif

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_2( \
        v, value) \
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::make_old(v, \
        boost::contract::copy_old(v) ? (value) : boost::contract::null_old() \
    ))

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_1( \
        value) \
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::make_old( \
        boost::contract::copy_old() ? (value) : boost::contract::null_old() \
    ))

/** @endcond */

/* PUBLIC */

// NOTE: Leave this #defined the same regardless of ..._POSTCONDITIONS.
/**
Macro typically used to copy old value expressions.
This is a variadic macro, program the old value expression copy manually on
compilers that do not support variadic macros (see
also @RefSect{advanced_topics, Advanced Topics}).
@see @RefSect{tutorial, Tutorial}.
@param ...  This macro usually takes a single parameter as the expressions to
            be assigned to the old value. However, in virtual or overriding
            public functions where the extra
            @RefClass{boost::contract::virtual_}<c>*</c> function parameter must
            be used, this macro takes two parameters: The first parameter is
            the pointer to @RefClass{boost::contract::virtual_} and then the
            old value expression to be copied.
@return The expression expanded by this macro should be assigned to an old
        value pointer, either @RefClass{boost::contract::old_ptr} or
        @RefClass{boost::contract::old_ptr_noncopyable}.
*/
#define BOOST_CONTRACT_OLDOF(...) \
    BOOST_PP_CAT( /* CAT(..., EMTPY()) required on MSVC */ \
        BOOST_PP_OVERLOAD( \
  BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_, \
            __VA_ARGS__ \
        )(__VA_ARGS__), \
        BOOST_PP_EMPTY() \
    )

#endif // variadics

/* CODE */

/** @cond */
namespace boost {
    namespace contract {
        class unconvertible_old;
    }

    // Needed because `unconvertible_old` incomplete type when trait used.
    template<>
    struct is_copy_constructible<contract::unconvertible_old> : true_type {};
}
/** @endcond */

namespace boost { namespace contract {

template<typename T>
class old_ptr_noncopyable;

/**
Old value pointer (requires pointed old value type to be copyable).
@see @RefSect{tutorial, Tutorial}.
@tparam T   Type of pointed old value. If this type is not copyable, this
            pointer will always be left null and this library will generate a
            compile-time error when this pointer is dereferenced of accessed.
*/
template<typename T>
class old_ptr { /* copyable (as *) */
public:
    /** Pointed old value type. */
    typedef T element_type;

    /** Construct this object as a null old value pointer. */
    old_ptr() {}

    /**
    Dereference this old value pointer.
    This will generate a run-time error if this pointer is null and a
    compile-time error if the pointed type is not copyable.
    @return The old value (contract assertions should not change the state of
            the program so the old value is always returned as a constant
            reference and this member function is @c const).
    */
    T const& operator*() const {
        BOOST_STATIC_ASSERT_MSG(
            boost::is_copy_constructible<T>::value,
"old_ptr<T> requires T copy constructor, otherwise use old_ptr_noncopyable<T>"
        );
        BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
        return *ptr_;
    }

    /**
    Access the pointed old value.
    This will generate a compile-time error if the pointed type is not copyable.
    @return The old value (contract assertions should not change the state of
            the program so the old value is always returned as a pointer to
            constant object and this member function is @c const).
    */
    T const* operator->() const {
        BOOST_STATIC_ASSERT_MSG(
            boost::is_copy_constructible<T>::value,
"old_ptr<T> requires T copy constructor, otherwise use old_ptr_noncopyable<T>"
        );
        return ptr_.operator->();
    }

    #ifndef DOXYGEN
        BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(old_ptr<T>, !!ptr_)
    #else
        /**
        Safe-bool operator.
        @return True if this pointer is not null, false otherwise.
        */
        explicit operator bool() const;
    #endif

/** @cond */
private:
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        explicit old_ptr(boost::shared_ptr<T const> ptr) :
                ptr_(ptr) {}
    #endif

    boost::shared_ptr<T const> ptr_;

    friend class convertible_old;
    friend class old_ptr_noncopyable<T>;
/** @endcond */
};

/**
Old value pointer (does not require pointed old value type to be copyable).
@see @RefSect{advanced_topics, Advanced Topics}.
@tparam T   Type of pointed old value. If this type is not copyable, this
            pointer will always be left null (but this library will not generate
            compile-time errors when this pointer is dereferenced of accessed).
*/
template<typename T>
class old_ptr_noncopyable { /* copyable (as *) */
public:
    /** Pointed old value type. */
    typedef T element_type;

    /** Construct this object as a null old value pointer. */
    old_ptr_noncopyable() {}
    
    /**
    Construct this object from a old value pointer for copyable-only types.
    Implicitly called when assign an object of this type to
    @RefMacro{BOOST_CONTRACT_OLDOF}.
    @param other Copyable-only old value pointer.
    */
    /* implicit */ old_ptr_noncopyable(old_ptr<T> const& other) :
            ptr_(other.ptr_) {}

    // Only const access (contracts should not change old values).
    
    /**
    Dereference this old value pointer.
    This will generate a run-time error if this pointer is null (but no
    compile-time error if the pointed type is not copyable).
    @return The old value (contract assertions should not change the state of
            the program so the old value is always returned as a constant
            reference and this member function is @c const).
    */
    T const& operator*() const {
        BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
        return *ptr_;
    }

    /**
    Access the pointed old value.
    (This will not generate a compile-time error if the pointed type is not
    copyable.)
    @return The old value (contract assertions should not change the state of
            the program so the old value is always returned as a pointer to
            constant object and this member function is @c const).
    */
    T const* operator->() const {
        return ptr_.operator->();
    }

    #ifndef DOXYGEN
        BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(old_ptr_noncopyable<T>, !!ptr_)
    #else
        /**
        Safe-bool operator.
        @return True if this pointer is not null, false otherwise.
        */
        explicit operator bool() const;
    #endif

/** @cond */
private:
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        explicit old_ptr_noncopyable(boost::shared_ptr<T const> ptr) :
                ptr_(ptr) {}
    #endif

    boost::shared_ptr<T const> ptr_;

    friend class convertible_old;
/** @endcond */
};

/**
Internally hold old value copies.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
class unconvertible_old { // Copyable (as *). 
public:
    // Following implicitly called by ternary operator `... ? ... : null_old()`.

    /**
    Construct this object from the specified old value (for copyable old value
    types).
    The specified old value is copied one time and the related old value pointer
    will not be null (as long as postconditions are being checked, see
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}).
    @tparam T Old value type.
    @param old_value Old value to be copied.
    */
    template<typename T>
    /* implicit */ unconvertible_old(
        T const& old_value,
        typename boost::enable_if<boost::is_copy_constructible<T> >::type* = 0
    )
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            : ptr_(boost::make_shared<T>(old_value)) // The one single T's copy.
        #endif // Else, leave ptr_ null (and no copy of T).
    {}
    
    /**
    Construct this object from the specified old value (for non-copyable old
    value types).
    The specified old value cannot and so it is not copied in this case, thus
    the related old value pointer will always be null.
    @tparam T Old value type.
    @param old_value Old value (that will not be copied in this case).
    */
    template<typename T>
    /* implicit */ unconvertible_old(
        T const& old_value,
        typename boost::disable_if<boost::is_copy_constructible<T> >::type* = 0
    ) {} // Leave ptr_ null (and no copy of T).

/** @cond */
private:
    explicit unconvertible_old() {}
    
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        boost::shared_ptr<void> ptr_;
    #endif

    friend class convertible_old;

    friend unconvertible_old null_old();
/** @endcond */
};

/**
Internally convert old value copies to old value pointers.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
class convertible_old { // Copyable (as *).
public:
    /**
    Convert this object to an old value pointer.
    For example, implicitly called when assigning or initializing an old value
    pointer.
    @tparam T Type of pointed old value (might or might be copyable).
    */
    template<typename T>
    /* implicit */ operator old_ptr_noncopyable<T>() {
        return ptr<old_ptr_noncopyable<T> >();
    }
    
    /**
    Convert this object to an old value pointer.
    For example, implicitly called when assigning or initializing an old value
    pointer.
    @tparam T Type of pointed old value (must be copyable).
    */
    template<typename T>
    /* implicit */ operator old_ptr<T>() {
        return ptr<old_ptr<T> >();
    }

/** @cond */
private:
    explicit convertible_old(virtual_* v, unconvertible_old const& old)
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            : v_(v), ptr_(old.ptr_)
        #endif
    {}
    
    template<typename Ptr>
    Ptr ptr() {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            if(!boost::is_copy_constructible<
                    typename Ptr::element_type>::value) {
                BOOST_CONTRACT_DETAIL_DEBUG(!ptr_); // Non-copyable so no old...
                return Ptr(); // ...and return null.
            } else if(!v_ && boost::contract::detail::check_guard::checking()) {
                // Return null shared ptr (see after if statement).
            } else if(!v_) {
                BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
                boost::shared_ptr<typename Ptr::element_type const> old =
                    boost::static_pointer_cast<
                            typename Ptr::element_type const>(ptr_)
                ;
                BOOST_CONTRACT_DETAIL_DEBUG(old);
                return Ptr(old);
            } else if(v_->action_ == boost::contract::virtual_::push_old_init ||
                    v_->action_ == boost::contract::virtual_::push_old_copy) {
                BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
                if(v_->action_ == boost::contract::virtual_::push_old_init) {
                    v_->old_inits_.push(ptr_);
                } else {
                    v_->old_copies_.push(ptr_);
                }
                return Ptr();
            } else if(v_->action_ == boost::contract::virtual_::pop_old_init ||
                    v_->action_ == boost::contract::virtual_::pop_old_copy) {
                BOOST_CONTRACT_DETAIL_DEBUG(!ptr_);
                boost::shared_ptr<void> ptr;
                if(v_->action_ == boost::contract::virtual_::pop_old_init) {
                    ptr = v_->old_inits_.front();
                } else {
                    ptr = v_->old_copies_.top();
                }
                BOOST_CONTRACT_DETAIL_DEBUG(ptr);
                if(v_->action_ == boost::contract::virtual_::pop_old_init) {
                    v_->old_inits_.pop();
                } else {
                    v_->old_copies_.pop();
                }
                boost::shared_ptr<typename Ptr::element_type const> old =
                    boost::static_pointer_cast<
                            typename Ptr::element_type const>(ptr)
                ;
                BOOST_CONTRACT_DETAIL_DEBUG(old);
                return Ptr(old);
            }
            BOOST_CONTRACT_DETAIL_DEBUG(!ptr_);
        #endif
        return Ptr();
    }

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        virtual_* v_;
        boost::shared_ptr<void> ptr_;
    #endif
    
    friend convertible_old make_old(unconvertible_old const&);

    friend convertible_old make_old(virtual_*, unconvertible_old const&);
/** @endcond */
};

/**
Make a null old value copy (i.e., the related old value pointer will be null).
@see @RefSect{advanced_topics, Advanced Topics}.
*/
unconvertible_old null_old() { return unconvertible_old(); }

/**
Make an old value copy (for non virtual and not overriding public functions).
@see @RefSect{advanced_topics, Advanced Topics}.
@param old  Old value (implicitly and automatically wrapped in
            @RefClass{boost::contract::uncovertible_old}).
*/
convertible_old make_old(unconvertible_old const& old) {
    return convertible_old(0, old);
}

/**
Make an old value copy (for virtual and overriding public functions).
@see @RefSect{advanced_topics, Advanced Topics}.
@param v    Contracted virtual and overriding public function extra parameter.
@param old  Old value (implicitly and automatically wrapped in
            @RefClass{boost::contract::uncovertible_old}).
*/
convertible_old make_old(virtual_* v, unconvertible_old const& old) {
    return convertible_old(v, old);
}

/**
Return true if and only if old values need to be copied (for non virtual and
not overriding public functions).
For example, this function always returns false when postconditions are not
being checked (see @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}).
@see @RefSect{advanced_topics, Advanced Topics}.
*/
bool copy_old() {
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        return !boost::contract::detail::check_guard::checking();
    #else
        return false; // Post checking disabled, so never copy old values.
    #endif
}

/**
Return true if and only if old values need to be copied (for virtual and
overriding public functions).
For example, this function always returns false when postconditions are not
being checked (see @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}).
@see @RefSect{advanced_topics, Advanced Topics}.
@param v    Contracted virtual and overriding public function extra parameter.
*/
bool copy_old(virtual_* v) {
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        if(!v) return !boost::contract::detail::check_guard::checking();
        return v->action_ == boost::contract::virtual_::push_old_init ||
                v->action_ == boost::contract::virtual_::push_old_copy;
    #else
        return false; // Post checking disabled, so never copy old values.
    #endif
}

} } // namespace

#endif // #include guard

