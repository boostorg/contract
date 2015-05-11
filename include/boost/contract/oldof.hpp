
#ifndef BOOST_CONTRACT_OLDOF_HPP_
#define BOOST_CONTRACT_OLDOF_HPP_

#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/call.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   define BOOST_CONTRACT_OLDOF \
BOOST_CONTRACT_ERROR_variadic_macros_required_by_BOOST_CONTRACT_OLDOF_otherwise_manually_program_old_values
#else

#include <boost/config.hpp>
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_OLDOF(...) \
    BOOST_PP_CAT( /* CAT(..., EMTPY()) required on MSVC */ \
        BOOST_PP_OVERLOAD( \
BOOST_CONTRACT_ERROR_invoked_macro_BOOST_CONTRACT_OLDOF_with_invalid_number_of_arguments_, \
            __VA_ARGS__ \
        )(__VA_ARGS__), \
        BOOST_PP_EMPTY() \
    )

/* PRIVATE */

#define \
BOOST_CONTRACT_ERROR_invoked_macro_BOOST_CONTRACT_OLDOF_with_invalid_number_of_arguments_1(value) \
    BOOST_CONTRACT_OLDOF_AUTO_(value)(boost::contract::oldof( \
        boost::contract::copy_oldof() ? (value) : boost::contract::oldof() \
    ))

#define \
BOOST_CONTRACT_ERROR_invoked_macro_BOOST_CONTRACT_OLDOF_with_invalid_number_of_arguments_2(c, value) \
    BOOST_CONTRACT_OLDOF_AUTO_(value)(boost::contract::oldof(c, \
        boost::contract::copy_oldof(c) ? (value) : boost::contract::oldof() \
    ))

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#   define BOOST_CONTRACT_OLDOF_AUTO_(value) /* nothing */
#else
#   include <boost/typeof/typeof.hpp>
// Explicitly force shared_ptr<T const> conversion to allow for C++11 auto decl.
#   define BOOST_CONTRACT_OLDOF_AUTO_(value) \
        boost::shared_ptr<BOOST_TYPEOF(value) const>
#endif

#endif // VARIADICS

/* CODE */

namespace boost { namespace contract {

bool copy_oldof() {
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return false; // Post checking disabled, so never copy old values.
#else
    return true;
#endif
}

bool copy_oldof(boost::contract::call const& c) {
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return false; // Post checking disabled, so never copy old values.
#else
    return c.call_ && c.call_->action == boost::contract::aux::call::copy_oldof;
#endif
}

class oldof {
public:
    explicit oldof() : call_(), value_() {}

    explicit oldof(boost::contract::call const& c, oldof const& old) :
            call_(c.call_), value_(old.value_) {}

    template<typename T>
    /* implicit */ oldof(T const& old_value) :
            value_(boost::make_shared<T>(old_value)) { // T's one single copy.
        std::clog << "oldof copy" << std::endl;
    }

    // TODO: I might be able to use unique_ptr here instead of shared_ptr. That
    // might be the true for the pointer that holds contract and call as well...
    // do some testing to figure that out (unique_ptr adds less overhead).

    template<typename T>
    operator boost::shared_ptr<T const>() {
        if(!call_) {
            BOOST_CONTRACT_AUX_DEBUG(value_);
            boost::shared_ptr<T const> old_value =
                    boost::static_pointer_cast<T const>(value_);
            BOOST_CONTRACT_AUX_DEBUG(old_value);
            std::clog << "oldof un-erased: " << *old_value << std::endl;
            return old_value;
        } else if(call_->action == boost::contract::aux::call::copy_oldof) {
            BOOST_CONTRACT_AUX_DEBUG(value_);
            call_->old_values.push(value_);
            std::clog << "oldof push" << std::endl;
            return boost::shared_ptr<T const>();
        } else if(call_->action == boost::contract::aux::call::check_post) {
            BOOST_CONTRACT_AUX_DEBUG(!value_);
            boost::shared_ptr<void> value = call_->old_values.front();
            BOOST_CONTRACT_AUX_DEBUG(value);
            call_->old_values.pop();
            boost::shared_ptr<T const> old_value =
                    boost::static_pointer_cast<T const>(value);
            BOOST_CONTRACT_AUX_DEBUG(old_value);
            std::clog << "oldof pop: " << *old_value << std::endl;
            return old_value;
        }
        BOOST_CONTRACT_AUX_DEBUG(!value_);
        return boost::shared_ptr<T const>();
    }

private:
    boost::shared_ptr<boost::contract::aux::call> call_;
    boost::shared_ptr<void> value_;
};

} } // namespace

#endif // #include guard

