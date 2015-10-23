
#ifndef BOOST_CONTRACT_OLDOF_HPP_
#define BOOST_CONTRACT_OLDOF_HPP_

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
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>
/** @endcond */

// TODO: Consider providing an .old(...) setter for all contracts that will be
// called to copy old-values before body execution but after pre/inv, and will
// call postcondition failure handler in case oldof calc throws (instead of
// making function throw).

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
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::old( \
        boost::contract::copy_old() ? (value) : boost::contract::old() \
    ))

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_2( \
        v, value) \
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::old(v, \
        boost::contract::copy_old(v) ? (value) : boost::contract::old() \
    ))

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#   define BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value) /* nothing */
#else
/** @cond */
#   include <boost/typeof/typeof.hpp>
/** @endcond */
// Explicitly force shared_ptr<T const> conversion to allow for C++11 auto decl.
#   define BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value) \
        boost::shared_ptr<BOOST_TYPEOF(value) const>
#endif

#endif // VARIADICS

/* CODE */

namespace boost { namespace contract {

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

// TODO: Rename this make_old (that is is different from .old(...)) and add
// old_ptr so with and without macros:
//  auto x = BOOST_CONTRACT_OLDOF(v, x);
//  old_ptr<T> x = BOOST_CONTRACT_OLDOF(v, x);
//  old_ptr<T> x = make_old(v, copy_old(v) ? x : make_old());
// plus, make_old() return old_erasure type without operator old_ptr<T> so
// following correctly gives compiler error:
//  old_ptr<T> = copy_old(v) ? x : make_old();
// 
// template<typename T>
// class old_ptr {
// public:
//     T const& operator*() const;
//     T const* operator->() const;
// 
// private:
//     boost::shared_ptr<T> ptr_;
// };
// 
// class old_erasure {
// public:
//     // Implicitly called by using ternary operator `... ? ... : make_old()`.
//     template<typename T>
//     /* implicit */ old_erasure(T const& old);
// 
//     friend old_erasure make_old() { return old_erasure(); }
// 
// private:
//     explicit old_erasure();
// };
// 
// class old_unerasure {
// public:
//     // Implicitly called by constructor init `old_ptr<T> old_x = ...`.
//     template<typename T>
//     operator old_ptr<T>();
// 
//     friend old_unerasure make_old(old_erasure const& old) {
//         return old_unerasure(0, old);
//     }
//     
//     friend old_unerasure make_old(virtual_* v, old_erasure const& old) {
//         return old_unerasure(v, old);
//     }
// 
// private:
//     explicit old_unerasure(virtual_* v, old_erasure const& old);
// };
class old { // Copyable (as *).
public:
    explicit old() : v_(0), value_() {}

    explicit old(virtual_* v, old const& other) : v_(v), value_(other.value_) {}

    template<typename T>
    /* implicit */ old(T const& old_value) : v_(0),
            value_(boost::make_shared<T>(old_value)) {} // T's one single copy.

    // TODO: I might be able to use unique_ptr here instead of shared_ptr. That
    // might be true for the pointer that holds contract and call as well...
    // do some testing to figure that out (unique_ptr adds less overhead).

    template<typename T>
    operator boost::shared_ptr<T const>() {
        if(!v_ && boost::contract::aux::check_guard::checking()) {
            // Return null shared ptr (see after if statement).
        } else if(!v_) {
            BOOST_CONTRACT_AUX_DEBUG(value_);
            boost::shared_ptr<T const> old_value =
                    boost::static_pointer_cast<T const>(value_);
            BOOST_CONTRACT_AUX_DEBUG(old_value);
            return old_value;
        } else if(v_->action_ == boost::contract::virtual_::push_old_init ||
                v_->action_ == boost::contract::virtual_::push_old_copy) {
            BOOST_CONTRACT_AUX_DEBUG(value_);
            if(v_->action_ == boost::contract::virtual_::push_old_init) {
                v_->old_inits_.push(value_);
            } else {
                v_->old_copies_.push(value_);
            }
            return boost::shared_ptr<T const>();
        } else if(v_->action_ == boost::contract::virtual_::pop_old_init ||
                v_->action_ == boost::contract::virtual_::pop_old_copy) {
            BOOST_CONTRACT_AUX_DEBUG(!value_);
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
            boost::shared_ptr<T const> old_value =
                    boost::static_pointer_cast<T const>(value);
            BOOST_CONTRACT_AUX_DEBUG(old_value);
            return old_value;
        }
        BOOST_CONTRACT_AUX_DEBUG(!value_);
        return boost::shared_ptr<T const>();
    }

private:
    virtual_* v_;
    boost::shared_ptr<void> value_;
};

} } // namespace

#endif // #include guard

