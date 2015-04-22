
#ifndef BOOST_CONTRACT_AUX_FUNCTION_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_PUBLIC_MEMBER_HPP_

#include <boost/contract/aux_/check/subcontracted_pre_post_inv.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/virtual_body.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux { namespace function {

template<
    class Class,
    class Intro = boost::contract::aux::none,
    typename Func = boost::contract::aux::none,
    typename Arg0 = boost::contract::aux::none
> class public_member : public boost::contract::aux::check::
        subcontracted_pre_post_inv<Class, Intro, Func, Arg0> {
public:
    // Must be used when bases and virtual body (but can also always be used).
    explicit public_member(boost::contract::virtual_body const virt,
            Class* const obj, Arg0 arg0) :
        boost::contract::aux::check::subcontracted_pre_post_inv<Class, Intro,
                Func, Arg0>(obj, arg0),
        virt_(virt)
    {
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Intro,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Func,
                boost::contract::aux::none>::value));
        entry();
    }
    
    // Can be used when bases and no virtual body.
    explicit public_member(Class* const obj, Arg0 arg0) :
        boost::contract::aux::check::subcontracted_pre_post_inv<Class, Intro,
                Func, Arg0>(obj, arg0),
        virt_(boost::contract::virtual_body::user_call)
    {
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Intro,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Func,
                boost::contract::aux::none>::value));
        entry();
    }
    
    // Can be used when no bases and virtual body.
    explicit public_member(boost::contract::virtual_body const virt,
            Class* const obj) :
        boost::contract::aux::check::subcontracted_pre_post_inv<Class, Intro,
                Func, Arg0>(obj),
        virt_(virt)
    {
        BOOST_CONTRACT_AUX_DEBUG((boost::is_same<Intro,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((boost::is_same<Func,
                boost::contract::aux::none>::value));
        entry();
    }
    
    // Can be used when no bases and no virtual body.
    explicit public_member(Class* const obj) :
        boost::contract::aux::check::subcontracted_pre_post_inv<Class, Intro,
                Func, Arg0>(obj),
        virt_(boost::contract::virtual_body::user_call)
    {
        BOOST_CONTRACT_AUX_DEBUG((boost::is_same<Intro,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((boost::is_same<Func,
                boost::contract::aux::none>::value));
        entry();
    }
    
    ~public_member() { exit(); }
    
private:
    // Check static and non-static subcontracted inv.
    void entry() {
        if(virt_.action == boost::contract::virtual_body::user_call ||
                virt_.action == boost::contract::virtual_body::check_inv_only) {
            this->check_subcontracted_inv();
            if(virt_.action != boost::contract::virtual_body::user_call)
                throw boost::contract::aux::no_error();
        } // Else (check only pre, post, etc.) do nothing.
    }

    // Check subcontracted pre (as soon as related functor set).
    void pre_available() /* override */ {
        if(virt_.action == boost::contract::virtual_body::user_call ||
                virt_.action == boost::contract::virtual_body::check_pre_only) {
            this->check_subcontracted_pre();
            if(virt_.action != boost::contract::virtual_body::user_call)
                throw boost::contract::aux::no_error();
        } // Else (check only inv, post, etc.) do nothing.
    }
    
    // Check post here only if check-post-only mode (otherwise check at exit).
    void post_available() /* override */ {
        if(virt_.action == boost::contract::virtual_body::check_post_only) {
            this->check_subcontracted_post();
            throw boost::contract::aux::no_error();
        } // Else (check only inv, pre, etc.) do nothing.
    }
    
    // Check static and non-static subcontracted invariant and, if body did not
    // throw, also check subcontracted post.
    void exit() {
        bool const body_threw = std::uncaught_exception();
        if(virt_.action == boost::contract::virtual_body::user_call) {
            this->check_subcontracted_inv();
            if(!body_threw) this->check_subcontracted_post();
        }
    }

    boost::contract::virtual_body const virt_;
};

} } } } // namespace

#endif // #include guard

