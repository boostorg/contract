
#ifndef BOOST_CONTRACT_AUX_TEST_FRIEND_HPP_
#define BOOST_CONTRACT_AUX_TEST_FRIEND_HPP_

#include <boost/contract/core/virtual.hpp>

namespace boost { namespace contract { namespace aux { namespace test {

// Made friend by a few library's types to access them to test them.
class friend_ {
public:
    static bool checking_post(boost::contract::virtual_* v) {
        return !v || v->action_ == boost::contract::virtual_::check_post ||
                v->action_ == boost::contract::virtual_::check_this_post;
    }
};

} } } } // namespace

#endif // #include guard

