
#ifndef BOOST_CONTRACT_OLDOF_HPP_
#define BOOST_CONTRACT_OLDOF_HPP_

/** @file */

#include <boost/contract/core/virtual.hpp>
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
    BOOST_CONTRACT_OLDOF_AUTO_(value)(boost::contract::old( \
        boost::contract::copy_old() ? (value) : boost::contract::old() \
    ))

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_2( \
        v, value) \
    BOOST_CONTRACT_OLDOF_AUTO_(value)(boost::contract::old(v, \
        boost::contract::copy_old(v) ? (value) : boost::contract::old() \
    ))

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#   define BOOST_CONTRACT_OLDOF_AUTO_(value) /* nothing */
#else
/** @cond */
#   include <boost/typeof/typeof.hpp>
/** @endcond */
// Explicitly force shared_ptr<T const> conversion to allow for C++11 auto decl.
#   define BOOST_CONTRACT_OLDOF_AUTO_(value) \
        boost::shared_ptr<BOOST_TYPEOF(value) const>
#endif

#endif // VARIADICS

/* CODE */

namespace boost { namespace contract {

bool copy_old() {
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return false; // Post checking disabled, so never copy old values.
#else
    return true;
#endif
}

bool copy_old(virtual_* v) {
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return false; // Post checking disabled, so never copy old values.
#else
    return !v || v->action_ == boost::contract::virtual_::copy_oldof;
#endif
}

class old { // Copyable (as *).
public:
    explicit old() : v_(0), value_() {}

    explicit old(virtual_* v, old const& other) : v_(v), value_(other.value_) {}

    template<typename T>
    /* implicit */ old(T const& old_value) :
            value_(boost::make_shared<T>(old_value)) { // T's one single copy.
    }

    // TODO: I might be able to use unique_ptr here instead of shared_ptr. That
    // might be the true for the pointer that holds contract and call as well...
    // do some testing to figure that out (unique_ptr adds less overhead).

    template<typename T>
    operator boost::shared_ptr<T const>() {
        if(!v_) {
            BOOST_CONTRACT_AUX_DEBUG(value_);
            boost::shared_ptr<T const> old_value =
                    boost::static_pointer_cast<T const>(value_);
            BOOST_CONTRACT_AUX_DEBUG(old_value);
            return old_value;
        } else if(v_->action_ == boost::contract::virtual_::copy_oldof) {
            BOOST_CONTRACT_AUX_DEBUG(value_);
            v_->old_values_.push(value_);
            return boost::shared_ptr<T const>();
        } else if(v_->action_ == boost::contract::virtual_::check_post) {
            BOOST_CONTRACT_AUX_DEBUG(!value_);
            boost::shared_ptr<void> value = v_->old_values_.front();
            BOOST_CONTRACT_AUX_DEBUG(value);
            v_->old_values_.pop();
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

