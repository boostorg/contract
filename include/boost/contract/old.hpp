
#ifndef BOOST_CONTRACT_OLD_HPP_
#define BOOST_CONTRACT_OLD_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Facilities to support old values.
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
Macro typically used to copy an old value expression and assign it to an old
value pointer.
The expression expanded by this macro should be assigned to an old value
pointer of type @RefClass{boost::contract::old_ptr} or
@RefClass{boost::contract::old_ptr_noncopyable}.

This is a variadic macro. On compilers that do not support variadic macros,
programmers can manually copy old value expressions without using this macro
(see @RefSect{advanced_topics, Advanced Topics}).
@see @RefSect{tutorial, Tutorial}
@param ...  This macro usually takes a single parameter as the old value
            expression to be copied. However, for virtual and overriding public
            functions where the extra
            @RefClass{boost::contract::virtual_}<c>*</c> function parameter must
            be used, this macro takes two parameters: The first parameter is
            the pointer to @RefClass{boost::contract::virtual_} and the second
            parameter is the old value expression to be copied.
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
        class old_value;
    }

    // Needed because `old_value` incomplete type when trait used.
    template<>
    struct is_copy_constructible<contract::old_value> : true_type {};
}
/** @endcond */

namespace boost { namespace contract {

template<typename T>
class old_ptr_noncopyable;

/**
Old value pointer (that requires the pointed old value type to be copy
constructible).
This is set to point to an actual old value via either
@RefMacro{BOOST_CONTRACT_OLDOF} or @RefFunc{boost::contract::make_old} (that is
why this class does not have public non-default constructors).
@see @RefSect{tutorial, Tutorial}
@tparam T Type of the pointed old value. This type must be copy constructible,
        otherwise this pointer will always be null and this library will
        generate a compile-time error if this pointer is dereferenced.
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
    compile-time error if the pointed type @c T is not copy constructible.
    @return The old value (contract assertions should not change the state of
            the program so this member function is @c const and it returns the
            old value as a constant reference).
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
    Structure-dereference this old value pointer.
    This will generate a compile-time error if the pointed type @c T is not
    copy constructible.
    @return The old value (contract assertions should not change the state of
            the program so this member function is @c const and it returns the
            old value as a constant pointer to a constant object).
    */
    T const* const operator->() const {
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
        Check if this old value pointer is null or not (safe-bool operator).
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

    friend class old_pointer;
    friend class old_ptr_noncopyable<T>;
/** @endcond */
};

/**
Old value pointer (that does not require the pointed old value type to be copy
constructible).
This is set to point to an actual old value via either
@RefMacro{BOOST_CONTRACT_OLDOF} or @RefFunc{boost::contract::make_old}.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam T   Type of pointed old value. If this type is not copy constructible,
            this pointer will always be null (but this library will not generate
            compile-time errors when this pointer is dereferenced).
*/
template<typename T>
class old_ptr_noncopyable { /* copyable (as *) */
public:
    /** Pointed old value type. */
    typedef T element_type;

    /** Construct this object as a null old value pointer. */
    old_ptr_noncopyable() {}
    
    /**
    Construct this object from an old value pointer of copyable-only types.
    This constructor is implicitly called by this library when assigning an
    object of this type using @RefMacro{BOOST_CONTRACT_OLDOF}.
    @param other Copyable-only old value pointer.
    */
    /* implicit */ old_ptr_noncopyable(old_ptr<T> const& other) :
            ptr_(other.ptr_) {}

    /**
    Dereference this old value pointer.
    This will generate a run-time error if this pointer is null (but no
    compile-time error if the pointed type @c T is not copy constructible).
    @return The old value (contract assertions should not change the state of
            the program so this member function is @c const and it returns the
            old vale as a constant reference).
    */
    T const& operator*() const {
        BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
        return *ptr_;
    }

    /**
    Structure-dereference this old value pointer.
    (This will not generate a compile-time error if the pointed type @c T is not
    copy constructible.)
    @return The old value (contract assertions should not change the state of
            the program so this member function is @c const and it returns the
            old value as a constant pointer to a constant object).
    */
    T const* const operator->() const {
        return ptr_.operator->();
    }

    #ifndef DOXYGEN
        BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(old_ptr_noncopyable<T>, !!ptr_)
    #else
        /**
        Check if this old value pointer is null or not (safe-bool operator).
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

    friend class old_pointer;
/** @endcond */
};

/**
Convert user expressions in old values.
This class is often only implicitly used by this library and it does not
explicitly appear in user code.

On older compilers that cannot correctly deduce the
@c boost::is_copy_constructible trait, programmers can manually specialize that
trait to make sure that only old value types that are copy constructible are
actually copied (see the @c boost::is_copy_constructible documentation).
@see @RefSect{advanced_topics, Advanced Topics}
*/
class old_value { // Copyable (as *). 
public:
    // Following implicitly called by ternary operator `... ? ... : null_old()`.

    /**
    Construct this object from the specified old value when the old value type
    is copy constructible.
    The specified old value is copied (one time only) and the related old value
    pointer will be set to not null (no copy is made instead if postconditions
    are not being checked, see @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}).
    @tparam T Old value type.
    @param old Old value to be copied.
    */
    template<typename T>
    /* implicit */ old_value(
        T const& old,
        typename boost::enable_if<boost::is_copy_constructible<T> >::type* = 0
    )
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            : ptr_(boost::make_shared<T>(old)) // The one single T's copy.
        #endif // Else, leave ptr_ null (and no copy of T).
    {}
    
    /**
    Construct this object from the specified old value when the old value type
    is not copy constructible.
    The specified old value cannot be copied in this case so it is not copied
    and the related old value pointer will always be null.
    @tparam T Old value type.
    @param old Old value (that will not be copied in this case).
    */
    template<typename T>
    /* implicit */ old_value(
        T const& old,
        typename boost::disable_if<boost::is_copy_constructible<T> >::type* = 0
    ) {} // Leave ptr_ null (and no copy of T).

/** @cond */
private:
    explicit old_value() {}
    
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        boost::shared_ptr<void> ptr_;
    #endif

    friend class old_pointer;
    friend old_value null_old();
/** @endcond */
};

/**
Convert old value copies to old value pointers.
This class is often used only implicitly by this library and it does not
explicitly appear in user code (that is why this class does not have public
constructors, etc.).
@see @RefSect{advanced_topics, Advanced Topics}
*/
class old_pointer { // Copyable (as *).
public:
    /**
    Convert this object to an old value pointer (the old value type might or not
    be copy constructible).
    For example, this is implicitly called when assigning or initializing old
    value pointers.
    @tparam T Type of the pointed old value. The old value pointer will always
            be null if this type is not copy constructible (but this library
            will not generate a compile-time error).
    */
    template<typename T>
    /* implicit */ operator old_ptr_noncopyable<T>() {
        return ptr<old_ptr_noncopyable<T> >();
    }
    
    /**
    Convert this object to an old value pointer (the old value type must be
    copy constructible).
    For example, this is implicitly called when assigning or initializing old
    value pointers.
    @tparam T Type of the pointed old value. This type must be copy
            constructible, otherwise this library will generate a compile-time
            error if the old value pointer is dereferenced.
    */
    template<typename T>
    /* implicit */ operator old_ptr<T>() {
        return ptr<old_ptr<T> >();
    }

/** @cond */
private:
    explicit old_pointer(virtual_* v, old_value const& old)
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
    
    friend old_pointer make_old(old_value const&);
    friend old_pointer make_old(virtual_*, old_value const&);
/** @endcond */
};

/**
Make a null old value copy.
The related old value pointer will always be null.
@see @RefSect{advanced_topics, Advanced Topics}
@return Null old value copy.
*/
old_value null_old() { return old_value(); }

/**
Make an old value pointer (not to be used for for virtual and overriding public
functions).
The related old value pointer will not be null if the specified old value was
actually copied.
@see @RefSect{advanced_topics, Advanced Topics}
@param old  Old value (usually implicitly constructed from the user old value
            expression to be copied).
@return Old value pointer (usually implicitly converted to either
        @RefClass{boost::contract::old_ptr} or
        @RefClass{boost::contract::old_ptr_noncopyable} in user code).
*/
old_pointer make_old(old_value const& old) {
    return old_pointer(0, old);
}

/**
Make an old value pointer (to be used for virtual and overriding public
functions).
The related old value pointer will not be null if the specified old value was
actually copied.
@see @RefSect{advanced_topics, Advanced Topics}
@param v    The contracted virtual and overriding function extra trailing
            parameter of type @RefClass{boost::contract::virtual_}<c>*</c> and
            with default value @c 0.
@param old  Old value (usually implicitly constructed from the user old value
            expression to be copied).
@return Old value pointer (usually implicitly converted to either
        @RefClass{boost::contract::old_ptr} or
        @RefClass{boost::contract::old_ptr_noncopyable} in user code).
*/
old_pointer make_old(virtual_* v, old_value const& old) {
    return old_pointer(v, old);
}

/**
Check if old values need to be copied (not to be used for virtual and overriding
public functions).
For example, this function always returns false when postconditions are not
being checked (see @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}).
@see @RefSect{advanced_topics, Advanced Topics}
@return True if old values are being copied, false otherwise.
*/
bool copy_old() {
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        return !boost::contract::detail::check_guard::checking();
    #else
        return false; // Post checking disabled, so never copy old values.
    #endif
}

/**
Check if old values need to be copied (to be used for virtual and overriding
public functions).
For example, this function always returns false when postconditions are not
being checked (see @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}).
@see @RefSect{advanced_topics, Advanced Topics}
@param v    The contracted virtual and overriding function extra trailing
            parameter of type @RefClass{boost::contract::virtual_}<c>*</c> and
            with default value @c 0.
@return True if old values are being copied, false otherwise.
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

