
#ifndef BOOST_CONTRACT_SET_PRECONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_HPP_

/** @file */

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_pre_only.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

class set_precondition_only {
public:
    template<typename F>
    set_nothing precondition(F const& f) {
        check_->set_pre(f);
        return set_nothing(check_);
    }

private:
    explicit set_precondition_only(boost::shared_ptr<
            boost::contract::aux::check_pre_only> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_only> check_;

    // Friendship used to limit library's public API.
    friend class scoped;
    template<typename R> friend class set_precondition_postcondition;

};

} } // namespace

#endif // #include guard

