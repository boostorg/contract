
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

template<typename R>
class set_postcondition_only {
public:
    template<typename F>
    set_nothing postcondition(F const& f) {
        check_->set_post(f);
        return set_nothing(check_);
    }

private:
    explicit set_postcondition_only(boost::shared_ptr<
            boost::contract::aux::check_pre_post<R> > check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_post<R> > check_;

    // Friendship used to limit library's public API.
    friend class scoped;
    template<typename> friend class set_precondition_postcondition;
};

} } // namespace

#endif // #include guard

