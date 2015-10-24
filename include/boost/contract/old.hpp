
#ifndef BOOST_CONTRACT_OLD_HPP_
#define BOOST_CONTRACT_OLD_HPP_

/** @file */

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
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
#include <boost/spirit/home/classic/core/safe_bool.hpp>
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>
/** @endcond */

// TODO: Can I use unique_ptr instead of shared ptr? If not here... maybe for
// holding contracts, etc.

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
        boost::contract::copy_old() ? (value) : boost::contract::make_old() \
    ))

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_2( \
        v, value) \
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::make_old(v, \
        boost::contract::copy_old(v) ? (value) : boost::contract::make_old() \
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

namespace boost { namespace contract {

// Used to avoid exposing entire shared_ptr API (e.g., client stealing
// ownership of this pointer could break this lib).
template<typename T>
class old_ptr // Copyable (as *).
    : boost::spirit::classic::safe_bool<old_ptr<T> >
{ 
public:
    explicit old_ptr() {}
    
    // operator safe-bool() const (see below).

    T const& operator*() const { return ptr_.operator*(); }
    T const* operator->() const { return ptr_.operator->(); }

private:
    explicit old_ptr(boost::shared_ptr<T const> ptr) : ptr_(ptr) {}

    bool operator_bool() const { return ptr_.operator bool(); }

    boost::shared_ptr<T const> ptr_;

    friend struct boost::spirit::classic::safe_bool<old_ptr>;
    friend class convertible_old;
};

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

class unconvertible_old { // Copyable (as *). 
public:
    // Implicitly called by ternary operator `... ? ... : make_old()`.
    template<typename T>
    /* implicit */ unconvertible_old(T const& old_value) : 
            ptr_(boost::make_shared<T>(old_value)) {} // T's one single copy.

private:
    explicit unconvertible_old() {}

    boost::shared_ptr<void> ptr_;

    friend class convertible_old;
    friend unconvertible_old make_old();
};

class convertible_old { // Copyable (as *).
public:
    // Implicitly called by constructor init `old_ptr<T> old_x = ...`.
    template<typename T>
    /* implicit */ operator old_ptr<T>() {
        if(!v_ && boost::contract::aux::check_guard::checking()) {
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
            boost::shared_ptr<void> value;
            if(v_->action_ == boost::contract::virtual_::pop_old_init) {
                value = v_->old_inits_.front();
            } else {
                value = v_->old_copies_.top();
            }
            BOOST_CONTRACT_AUX_DEBUG(value);
            if(v_->action_ == boost::contract::virtual_::pop_old_init) {
                v_->old_inits_.pop();
            } else {
                v_->old_copies_.pop();
            }
            boost::shared_ptr<T const> old =
                    boost::static_pointer_cast<T const>(value);
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
    
unconvertible_old make_old() { return unconvertible_old(); }

convertible_old make_old(unconvertible_old const& old) {
    return convertible_old(0, old);
}

convertible_old make_old(virtual_* v, unconvertible_old const& old) {
    return convertible_old(v, old);
}

} } // namespace

#endif // #include guard

