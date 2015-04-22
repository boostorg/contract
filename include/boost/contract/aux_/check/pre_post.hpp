
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/function.hpp>

namespace boost { namespace contract { namespace aux { namespace check {

class pre_post {
public:
    template<typename Pre>
    void set_pre(Pre const& pre) { pre_ = pre; pre_available(); }

    template<typename Post>
    void set_post(Post const& post) { post_ = post; post_available(); }

protected:
    pre_post() {}
    virtual ~pre_post() {}

    void check_pre() { if(pre_) pre_(); }
    void check_post() { if(post_) post_(); }

    virtual void pre_available() {}
    virtual void post_available() {}

private:
    boost::function<void ()> pre_;
    boost::function<void ()> post_;
};

} } } } // namespace

#endif // #include guard

