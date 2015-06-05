
#ifndef BOOST_CONTRACT_AUX_CHECK_GUARD_HPP_
#define BOOST_CONTRACT_AUX_CHECK_GUARD_HPP_

#include <boost/contract/aux_/name.hpp>
/** @cond */
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/preprocessor/cat.hpp>
/** @endcond */

/* PUBLIC */

// NOTE: These macros depend on their caller's code (e.g., has `base_call()`),
// but they are defined here to avoid code duplication at the callers' side.

#define BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN \
    if(boost::contract::aux::check_guard::checking()) return; \
    boost::contract::aux::check_guard BOOST_CONTRACT_AUX_CHECKING_GUARD_VAR_;

#define BOOST_CONTRACT_AUX_SUBCONTRACTED_CHECK_GUARD_OR_RETURN \
    boost::shared_ptr<boost::contract::aux::check_guard> \
            BOOST_CONTRACT_AUX_CHECKING_GUARD_VAR_; \
    if(!this->base_call()) { \
        if(boost::contract::aux::check_guard::checking()) return; \
        BOOST_CONTRACT_AUX_CHECKING_GUARD_VAR_ = \
                boost::make_shared<boost::contract::aux::check_guard>(); \
    }

/* PRIVATE */

#define BOOST_CONTRACT_AUX_CHECKING_GUARD_VAR_ \
    BOOST_CONTRACT_AUX_NAME1(BOOST_PP_CAT(checking, __LINE__))

/* CODE */

namespace boost { namespace contract { namespace aux {

// TODO: Consider what to do with multi-threads... multi-reads/one-write locks
// via boost::shared_mutex? should each thread have each own contract checking
// bool resource?

struct check_guard {
    explicit check_guard() { checking_ = true; }
    ~check_guard() { checking_ = false; }
    
    static bool checking() { return checking_; }

private:
    static bool checking_;
};

// TODO: This state must go into a .cpp with dyn linking (for DLLs).
bool check_guard::checking_ = false;

} } } // namespace

#endif // #include guard

