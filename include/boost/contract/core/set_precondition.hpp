
#ifndef BOOST_CONTRACT_SET_PRECONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_HPP_

/** @file */

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

class set_precondition {
public:
    template<typename F>
    set_nothing precondition(F f) {
        check_->set_pre(f);
        return set_nothing(check_);
    }

private: // Friendship to minimize lib's public API.
    friend class scoped;
    friend class set_precondition_postcondition;

    explicit set_precondition(boost::shared_ptr<boost::contract::
            aux::check_pre_post> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_post> check_;
};

} } // namespace

#endif // #include guard

