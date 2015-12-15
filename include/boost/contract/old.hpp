
#ifndef BOOST_CONTRACT_OLD_HPP_
#define BOOST_CONTRACT_OLD_HPP_

/** @file */

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/operator_safe_bool.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_copy_constructible.hpp>
#include <boost/utility/enable_if.hpp>
/** @endcond */

/** @cond */
#include <boost/preprocessor/config/config.hpp>
/** @endcond */
#if !BOOST_PP_VARIADICS
#   define BOOST_CONTRACT_OLDOF \
BOOST_CONTRACT_ERROR_macro_OLDOF_requires_variadic_macros_otherwise_manually_program_old_values
#else

/** @cond */
#include <boost/config.hpp>
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>
/** @endcond */

/* PUBLIC */

#define BOOST_CONTRACT_OLDOF(...) \
    BOOST_PP_CAT( /* CAT(..., EMTPY()) required on MSVC */ \
        BOOST_PP_OVERLOAD( \
BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_, \
            __VA_ARGS__ \
        )(__VA_ARGS__), \
        BOOST_PP_EMPTY() \
    )

/* PRIVATE */

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_1( \
        value) \
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::make_old( \
        boost::contract::copy_old() ? (value) : boost::contract::null_old() \
    ))

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_2( \
        v, value) \
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::make_old(v, \
        boost::contract::copy_old(v) ? (value) : boost::contract::null_old() \
    ))

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#   define BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value) /* nothing */
#else
/** @cond */
#   include <boost/typeof/typeof.hpp>
/** @endcond */
// Explicitly force shared_ptr<T const> conversion to allow for C++11 auto decl.
#   define BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value) \
        boost::contract::old_ptr<BOOST_TYPEOF(value)>
#endif

#endif // VARIADICS

/* CODE */

// Specialization because `unconvertible_old` incomplete type when trait used.
namespace boost {
    namespace contract {
        class unconvertible_old;
    }

    template<>
    struct is_copy_constructible<contract::unconvertible_old> : true_type {};
}

namespace boost { namespace contract {

// Used to avoid exposing entire shared_ptr API (e.g., client stealing
// ownership of this pointer could break this lib).
template<typename T>
class old_ptr { // Copyable (as *).
public:
    explicit old_ptr() {}
    
    T const& operator*() const { return ptr_.operator*(); }

    T const* operator->() const { return ptr_.operator->(); }

    BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL(old_ptr<T>, !!ptr_)

private:
    explicit old_ptr(boost::shared_ptr<T const> ptr) : ptr_(ptr) {}

    boost::shared_ptr<T const> ptr_;

    friend class convertible_old;
};

class unconvertible_old { // Copyable (as *). 
public:
    // Following implicitly called by ternary operator `... ? ... : null_old()`.

    template<typename T>
    /* implicit */ unconvertible_old(
        T const& old_value,
        typename boost::enable_if<boost::is_copy_constructible<T> >::type* = 0
    ) : ptr_(boost::make_shared<T>(old_value)) {} // The one single copy of T.
    
    template<typename T>
    /* implicit */ unconvertible_old(
        T const&,
        typename boost::disable_if<boost::is_copy_constructible<T> >::type* = 0
    ) : ptr_() {} // Null ptr, no copy of T.

private:
    explicit unconvertible_old() {}

    boost::shared_ptr<void> ptr_;

    friend class convertible_old;
    friend unconvertible_old null_old();
};

class convertible_old { // Copyable (as *).
public:
    // Implicitly called by constructor init `old_ptr<T> old_x = ...`.
    template<typename T>
    /* implicit */ operator old_ptr<T>() {
        if(!boost::is_copy_constructible<T>::value) {
            BOOST_CONTRACT_AUX_DEBUG(!ptr_); // Non-copyable so no old...
            return old_ptr<T>(); // ...and return null.
        } else if(!v_ && boost::contract::aux::check_guard::checking()) {
            // Return null shared ptr (see after if statement).
        } else if(!v_) {
            BOOST_CONTRACT_AUX_DEBUG(ptr_);
            boost::shared_ptr<T const> old =
                    boost::static_pointer_cast<T const>(ptr_);
            BOOST_CONTRACT_AUX_DEBUG(old);
            return old_ptr<T>(old);
        } else if(v_->action_ == boost::contract::virtual_::push_old_init ||
                v_->action_ == boost::contract::virtual_::push_old_copy) {
            BOOST_CONTRACT_AUX_DEBUG(ptr_);
            if(v_->action_ == boost::contract::virtual_::push_old_init) {
                v_->old_inits_.push(ptr_);
            } else {
                v_->old_copies_.push(ptr_);
            }
            return old_ptr<T>();
        } else if(v_->action_ == boost::contract::virtual_::pop_old_init ||
                v_->action_ == boost::contract::virtual_::pop_old_copy) {
            BOOST_CONTRACT_AUX_DEBUG(!ptr_);
            boost::shared_ptr<void> ptr;
            if(v_->action_ == boost::contract::virtual_::pop_old_init) {
                ptr = v_->old_inits_.front();
            } else {
                ptr = v_->old_copies_.top();
            }
            BOOST_CONTRACT_AUX_DEBUG(ptr);
            if(v_->action_ == boost::contract::virtual_::pop_old_init) {
                v_->old_inits_.pop();
            } else {
                v_->old_copies_.pop();
            }
            boost::shared_ptr<T const> old =
                    boost::static_pointer_cast<T const>(ptr);
            BOOST_CONTRACT_AUX_DEBUG(old);
            return old_ptr<T>(old);
        }
        BOOST_CONTRACT_AUX_DEBUG(!ptr_);
        return old_ptr<T>();
    }

private:
    explicit convertible_old(virtual_* v, unconvertible_old const& old) :
            v_(v), ptr_(old.ptr_) {}

    virtual_* v_;
    boost::shared_ptr<void> ptr_;
    
    friend convertible_old make_old(unconvertible_old const&);
    friend convertible_old make_old(virtual_*, unconvertible_old const&);
};
    
unconvertible_old null_old() { return unconvertible_old(); }

convertible_old make_old(unconvertible_old const& old) {
    return convertible_old(0, old);
}

convertible_old make_old(virtual_* v, unconvertible_old const& old) {
    return convertible_old(v, old);
}

bool copy_old() {
#if BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return false; // Post checking disabled, so never copy old values.
#else
    return !boost::contract::aux::check_guard::checking();
#endif
}

bool copy_old(virtual_* v) {
#if BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return false; // Post checking disabled, so never copy old values.
#else
    if(!v) return !boost::contract::aux::check_guard::checking();
    return v->action_ == boost::contract::virtual_::push_old_init ||
            v->action_ == boost::contract::virtual_::push_old_copy;
#endif
}

} } // namespace

#endif // #include guard

