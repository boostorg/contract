
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

/** @file */

#include <boost/contract/aux_/condition/check_pre_only.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

// TODO: Make sure all friend declarations are at bottom of public if part of
// public API, or at bottom of private if part of private API.

// TODO: Do I need to store contracts as shared_ptr or unique_ptr is sufficient?

class set_nothing {
public:
    // No set function members here.

private:
    explicit set_nothing(boost::shared_ptr<
            boost::contract::aux::check_pre_only> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_only> check_;

    // Friendship used to limit library's public API.
    friend class scoped;
    friend class set_precondition_only;
    template<typename R> friend class set_postcondition_only;
};

} } // namespace

#endif // #include guard

