
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
#ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
    #include <boost/contract/detail/checking.hpp>
#endif
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

#define BOOST_CONTRACT_OLD \
BOOST_CONTRACT_ERROR_macro_OLD_requires_variadic_macros_otherwise_manually_program_old_values

#else // variadics

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
    #define BOOST_CONTRACT_OLD_AUTO_TYPEOF_(value) /* nothing */
#else
    #include <boost/typeof/typeof.hpp>
    // Explicitly force old_ptr<...> conversion to allow for C++11 auto decl.
    #define BOOST_CONTRACT_OLD_AUTO_TYPEOF_(value) \
        boost::contract::old_ptr<BOOST_TYPEOF(value)>
#endif

#define BOOST_CONTRACT_ERROR_macro_OLD_has_invalid_number_of_arguments_2( \
        v, value) \
    BOOST_CONTRACT_OLD_AUTO_TYPEOF_(value)(boost::contract::make_old(v, \
        boost::contract::copy_old(v) ? (value) : boost::contract::null_old() \
    ))

#define BOOST_CONTRACT_ERROR_macro_OLD_has_invalid_number_of_arguments_1( \
        value) \
    BOOST_CONTRACT_OLD_AUTO_TYPEOF_(value)(boost::contract::make_old( \
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
@RefClass{boost::contract::old_ptr_if_copyable}.

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
#define BOOST_CONTRACT_OLD(...) \
    BOOST_PP_CAT( /* CAT(..., EMTPY()) required on MSVC */ \
        BOOST_PP_OVERLOAD( \
  BOOST_CONTRACT_ERROR_macro_OLD_has_invalid_number_of_arguments_, \
            __VA_ARGS__ \
        )(__VA_ARGS__), \
        BOOST_PP_EMPTY() \
    )

#endif // variadics

/* CODE */

namespace boost { namespace contract {

template<typename T>
struct is_old_value_copyable : boost::is_copy_constructible<T> {};

/** @cond */
class old_value;

template<> // Needed because `old_value` incomplete type when trait first used.
struct is_old_value_copyable<old_value> : boost::true_type {};
/** @endcond */

template<typename T> // Used only if is_old_value_copyable<T>.
class old_value_copy {
public:
    explicit old_value_copy(T const& value) :
            value_(value) {} // This makes the one single copy of T.

    T const& value() const { return value_; }

private:
    T const value_;
};

template<typename T>
class old_ptr_if_copyable;

/**
Old value pointer (that requires the pointed old value type to be copy
constructible).
This is set to point to an actual old value via either
@RefMacro{BOOST_CONTRACT_OLD} or @RefFunc{boost::contract::make_old} (that is
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
            boost::contract::is_old_value_copyable<T>::value,
            "old_ptr<T> requires T copy constructible (see "
            "is_old_value_copyable<T>), otherwise use old_ptr_if_copyable<T>"
        );
        BOOST_CONTRACT_DETAIL_DEBUG(typed_copy_);
        return typed_copy_->value();
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
            boost::contract::is_old_value_copyable<T>::value,
            "old_ptr<T> requires T copy constructible (see "
            "is_old_value_copyable<T>), otherwise use old_ptr_if_copyable<T>"
        );
        if(typed_copy_) return &typed_copy_->value();
        return 0;
    }

    #ifndef DOXYGEN
        BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(old_ptr<T>,
                !!typed_copy_)
    #else
        /**
        Check if this old value pointer is null or not (safe-bool operator).
        @return True if this pointer is not null, false otherwise.
        */
        explicit operator bool() const;
    #endif

/** @cond */
private:
    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        explicit old_ptr(boost::shared_ptr<old_value_copy<T> > old)
                : typed_copy_(old) {}
    #endif

    boost::shared_ptr<old_value_copy<T> > typed_copy_;

    friend class old_pointer;
    friend class old_ptr_if_copyable<T>;
/** @endcond */
};

/**
Old value pointer (that does not require the pointed old value type to be copy
constructible).
This is set to point to an actual old value via either
@RefMacro{BOOST_CONTRACT_OLD} or @RefFunc{boost::contract::make_old}.
@see @RefSect{advanced_topics, Advanced Topics}
@tparam T   Type of pointed old value. If this type is not copy constructible,
            this pointer will always be null (but this library will not generate
            compile-time errors when this pointer is dereferenced).
*/
template<typename T>
class old_ptr_if_copyable { /* copyable (as *) */
public:
    /** Pointed old value type. */
    typedef T element_type;

    /** Construct this object as a null old value pointer. */
    old_ptr_if_copyable() {}

    // TODO: Document that auto old_x = BOOST_CONTRACT_OLD(...) will use old_ptr and not old_ptr_if_copyable (auto will by default not use old_ptr_if_conpyable because old_ptr is more stringent from a type requirement prospective, if users want to relax the copyable type requirements they need to explicitly use old_ptr_if_copyable instead of using auto).
    
    /**
    Construct this object from an old value pointer of copyable-only types.
    This constructor is implicitly called by this library when assigning an
    object of this type using @RefMacro{BOOST_CONTRACT_OLD}.
    @param other Copyable-only old value pointer.
    */
    /* implicit */ old_ptr_if_copyable(old_ptr<T> const& other) :
            typed_copy_(other.typed_copy_) {}

    /**
    Dereference this old value pointer.
    This will generate a run-time error if this pointer is null (but no
    compile-time error if the pointed type @c T is not copy constructible).
    @return The old value (contract assertions should not change the state of
            the program so this member function is @c const and it returns the
            old vale as a constant reference).
    */
    T const& operator*() const {
        BOOST_CONTRACT_DETAIL_DEBUG(typed_copy_);
        return typed_copy_->value();
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
        if(typed_copy_) return &typed_copy_->value();
        return 0;
    }

    #ifndef DOXYGEN
        BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(old_ptr_if_copyable<T>,
                !!typed_copy_)
    #else
        /**
        Check if this old value pointer is null or not (safe-bool operator).
        @return True if this pointer is not null, false otherwise.
        */
        explicit operator bool() const;
    #endif

/** @cond */
private:
    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        explicit old_ptr_if_copyable(boost::shared_ptr<old_value_copy<T> > old)
                : typed_copy_(old) {}
    #endif

    boost::shared_ptr<old_value_copy<T> > typed_copy_;

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
        typename boost::enable_if<boost::contract::is_old_value_copyable<T>
                >::type* = 0
    )
        #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_EXCEPTS)
            // TODO: Will this shared_ptr<void> destroy old_value_copy given its type is erased to void*?? Test it!
            : untyped_copy_(new old_value_copy<T>(old))
        #endif // Else, leave ptr_ null (thus no copy of T).
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
        typename boost::disable_if<boost::contract::is_old_value_copyable<T>
                >::type* = 0
    ) {} // Leave ptr_ null (thus no copy of T).

/** @cond */
private:
    explicit old_value() {}
    
    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        boost::shared_ptr<void> untyped_copy_; // Type erasure.
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
    /* implicit */ operator old_ptr_if_copyable<T>() {
        return get<old_ptr_if_copyable<T> >();
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
        return get<old_ptr<T> >();
    }

/** @cond */
private:
    explicit old_pointer(virtual_* v, old_value const& old)
        #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_EXCEPTS)
            : v_(v), untyped_copy_(old.untyped_copy_)
        #endif
    {}
    
    template<typename Ptr>
    Ptr get() {
        #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_EXCEPTS)
            if(!boost::contract::is_old_value_copyable<typename
                    Ptr::element_type>::value) {
                BOOST_CONTRACT_DETAIL_DEBUG(!untyped_copy_);
                return Ptr(); // Non-copyable so no old value and return null.
        #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
            } else if(!v_ && boost::contract::detail::checking::already()) {
                return Ptr(); // Not checking (so return null).
        #endif
            } else if(!v_) {
                BOOST_CONTRACT_DETAIL_DEBUG(untyped_copy_);
                typedef old_value_copy<typename Ptr::element_type> copied_type;
                boost::shared_ptr<copied_type> typed_copy = // Un-erase type.
                        boost::static_pointer_cast<copied_type>(untyped_copy_);
                BOOST_CONTRACT_DETAIL_DEBUG(typed_copy);
                return Ptr(typed_copy);
            } else if(v_->action_ == boost::contract::virtual_::push_old_init ||
                    v_->action_ == boost::contract::virtual_::push_old_copy) {
                BOOST_CONTRACT_DETAIL_DEBUG(untyped_copy_);
                if(v_->action_ == boost::contract::virtual_::push_old_init) {
                    v_->old_inits_.push(untyped_copy_);
                } else {
                    v_->old_copies_.push(untyped_copy_);
                }
                return Ptr(); // Push (so return null).
            } else if(boost::contract::virtual_::pop_old_init(v_->action_) ||
                    v_->action_ == boost::contract::virtual_::pop_old_copy) {
                BOOST_CONTRACT_DETAIL_DEBUG(!untyped_copy_); // Copy not null...
                boost::shared_ptr<void> untyped_copy; // ...but still pop this.
                if(boost::contract::virtual_::pop_old_init(v_->action_)) {
                    untyped_copy = v_->old_inits_.front();
                    BOOST_CONTRACT_DETAIL_DEBUG(untyped_copy);
                    v_->old_inits_.pop();
                } else {
                    untyped_copy = v_->old_copies_.top();
                    BOOST_CONTRACT_DETAIL_DEBUG(untyped_copy);
                    v_->old_copies_.pop();
                }
                typedef old_value_copy<typename Ptr::element_type> copied_type;
                boost::shared_ptr<copied_type> typed_copy = // Un-erase type.
                        boost::static_pointer_cast<copied_type>(untyped_copy);
                BOOST_CONTRACT_DETAIL_DEBUG(typed_copy);
                return Ptr(typed_copy);
            }
            BOOST_CONTRACT_DETAIL_DEBUG(!untyped_copy_);
        #endif
        return Ptr();
    }

    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        virtual_* v_;
        boost::shared_ptr<void> untyped_copy_; // Type erasure.
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
        @RefClass{boost::contract::old_ptr_if_copyable} in user code).
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
        @RefClass{boost::contract::old_ptr_if_copyable} in user code).
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
    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
            return !boost::contract::detail::checking::already();
        #else
            return true;
        #endif
    #else
        return false; // No post checking, so never copy old values.
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
    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        if(!v) {
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                return !boost::contract::detail::checking::already();
            #else
                return true;
            #endif
        }
        return v->action_ == boost::contract::virtual_::push_old_init ||
                v->action_ == boost::contract::virtual_::push_old_copy;
    #else
        return false; // No post checking, so never copy old values.
    #endif
}

} } // namespace

#endif // #include guard

