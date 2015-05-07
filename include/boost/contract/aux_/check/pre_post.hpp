
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/contract/aux_/exception.hpp>
#include <boost/function.hpp>

namespace boost { namespace contract { namespace aux { namespace check {

class pre_post {
public:
    explicit pre_post(boost::contract::from const& from) : from_(from) {}

    virtual ~pre_post() {}

    template<typename Pre>
    void set_pre(Pre const& pre) { pre_ = pre; pre_available(); }

    template<typename Post>
    void set_post(Post const& post) { post_ = post; post_available(); }

protected:
    // Allow to throw on failure for relaxing subcontracted pre.
    void check_pre(bool const throw_on_failure = false) {
        if(pre_) {
            try { pre_(); }
            catch(...) {
                if(throw_on_failure) throw;
                boost::contract::aux::pre_failure_handler(from());
            }
        }
    }

    void check_post() {
        if(post_) {
            try { post_(); }
            catch(...) { boost::contract::aux::post_failure_handler(from()); }
        }
    }

    virtual void pre_available() {}
    virtual void post_available() {}

    boost::contract::from from() { return from_; }

private:
    boost::contract::from const from_;
    boost::function<void ()> pre_;
    boost::function<void ()> post_;
};

} } } } // namespace

#endif // #include guard

