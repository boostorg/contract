
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_only.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/function.hpp> // TODO: Can I reduce boost.function overhead?
/** @endcond */

namespace boost { namespace contract { namespace aux {

// TODO: Does this need to be copied? Copying function<> could copy captures
// (if function is a lambda) and it could be expensive... check all classes
// that MUST be copiable, make sure their copies are effecient, make all other
// calsses noncopyable.
template<typename R>
class check_pre_post : public check_pre_only {
public:
    explicit check_pre_post(boost::contract::from from) :
            check_pre_only(from) {}

    virtual ~check_pre_post() {}

    template<typename F>
    void set_post(F const& f) { post_ = f; post_available(); }

protected:
    void check_post(R& r) {
        try { if(post_) post_(r); }
        catch(...) { boost::contract::postcondition_failed(from()); }
    }
    
    virtual void post_available() {}

private:
    boost::function<void (R const&)> post_;
};

// TODO: I should avoid repeating code between this and above...
template<>
class check_pre_post<none> : public check_pre_only {
public:
    explicit check_pre_post(boost::contract::from from) :
            check_pre_only(from) {}

    virtual ~check_pre_post() {}

    template<typename F>
    void set_post(F const& f) { post_ = f; post_available(); }

protected:
    void check_post() {
        try { if(post_) post_(); }
        catch(...) { boost::contract::postcondition_failed(from()); }
    }
    
    void check_post(none&) { check_post(); }
    
    virtual void post_available() {}

private:
    boost::function<void ()> post_;
};

} } }

#endif // #include guard

