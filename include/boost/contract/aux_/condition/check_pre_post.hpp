
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/contract/core/exception.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp> // TODO: Can I reduce boost.function overhead?
/** @endcond */

namespace boost { namespace contract { namespace aux {

// TODO: Does this need to be copied? Copying function<> could copy captures
// (if function is a lambda) and it could be expensive... check all classes
// that MUST be copiable, make sure their copies are effecient, make all other
// calsses noncopyable.
class check_pre_post {
public:
    explicit check_pre_post(boost::contract::from from) : from_(from) {}
    
    virtual ~check_pre_post() {}

    template<typename F>
    void set_pre(F const& f) { pre_ = f; pre_available(); }

    template<typename F>
    void set_post(F const& f) { post_ = f; post_available(); }

protected:
    void check_pre(bool throw_on_failure = false) {
        if(pre_) {
            try { pre_(); }
            catch(...) {
                // Subcontracted pre must throw on failure (instead of
                // calling failure handler) so to be checked in logic-or.
                if(throw_on_failure) throw;
                boost::contract::precondition_failed(from_);
            }
        }
    }

    void check_post() {
        if(post_) {
            try { post_(); }
            catch(...) { boost::contract::postcondition_failed(from_); }
        }
    }
    
    virtual void pre_available() {}
    virtual void post_available() {}

    boost::contract::from from() const { return from_; }

private:
    boost::contract::from from_;
    boost::function<void ()> pre_;
    boost::function<void ()> post_;
};

} } }

#endif // #include guard

