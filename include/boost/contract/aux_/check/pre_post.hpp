
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/contract/type.hpp>

// TODO: Consider moving this to an aux_/check/ dir and namespace.

namespace boost { namespace contract { namespace aux { namespace check {

// TODO: check_pre/post should probably just be made protected members of
// class containing pre_/post_ so those can be made private data members.
class pre_post : public boost::contract::type {
protected:
    void check_pre() { if(pre_) pre_(); }
    void check_post() { if(post_) post_(); }
};

} } } } // namespace

#endif // #include guard

