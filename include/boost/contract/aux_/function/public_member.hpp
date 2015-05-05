
#ifndef BOOST_CONTRACT_AUX_FUNCTION_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_PUBLIC_MEMBER_HPP_

#include <boost/contract/virtual_body.hpp>
#include <boost/contract/exception.hpp>
#include <boost/contract/aux_/check/subcontracted_pre_post_inv.hpp>
#include <boost/contract/aux_/virtual_call.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/debug.hpp>
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
        boost::contract::aux::check::subcontracted_pre_post_inv<
            Class, Intro, Func, Arg0
        >(boost::contract::from_public_member, virt, obj, arg0)
    {
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Intro,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Func,
                boost::contract::aux::none>::value));
        entry();
    }
    
    // Can be used when bases and no virtual body.
    explicit public_member(Class* const obj, Arg0 arg0) :
        boost::contract::aux::check::subcontracted_pre_post_inv<
            Class, Intro, Func, Arg0
        >(boost::contract::from_public_member, /* virt = */ 0, obj, arg0)
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
        boost::contract::aux::check::subcontracted_pre_post_inv<
            Class, Intro, Func, Arg0
        >(boost::contract::from_public_member, virt, obj)
    {
        BOOST_CONTRACT_AUX_DEBUG((boost::is_same<Intro,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((boost::is_same<Func,
                boost::contract::aux::none>::value));
        entry();
    }
    
    // Can be used when no bases and no virtual body.
    explicit public_member(Class* const obj) :
        boost::contract::aux::check::subcontracted_pre_post_inv<
            Class, Intro, Func, Arg0
        >(boost::contract::from_public_member, /* virt = */ 0, obj)
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
        if(
            this->virtual_call()->action ==
                    boost::contract::aux::virtual_call::user_call ||
            this->virtual_call()->action ==
                    boost::contract::aux::virtual_call::copy_oldof
        ) {
            this->copy_subcontracted_oldof();
            if(this->virtual_call()->action !=
                    boost::contract::aux::virtual_call::user_call) {
                throw boost::contract::aux::no_error();
            }
        }

        if( // When inv only, also must check exit inv here to skip body.
            this->virtual_call()->action ==
                    boost::contract::aux::virtual_call::user_call ||
            this->virtual_call()->action ==
                    boost::contract::aux::virtual_call::check_entry_inv ||
            this->virtual_call()->action ==
                    boost::contract::aux::virtual_call::check_exit_inv
        ) {
            if(this->virtual_call()->action ==
                    boost::contract::aux::virtual_call::check_exit_inv) {
                this->check_subcontracted_exit_inv();
            } else { // For both user call and entry inv only.
                this->check_subcontracted_entry_inv();
            }
            if(this->virtual_call()->action !=
                    boost::contract::aux::virtual_call::user_call) {
                throw boost::contract::aux::no_error();
            }
        } // Else (check only pre, post, etc.) do nothing.
    }

    // Check subcontracted pre (as soon as related functor set).
    void pre_available() /* override */ {
        if(
            this->virtual_call()->action ==
                    boost::contract::aux::virtual_call::user_call ||
            this->virtual_call()->action ==
                    boost::contract::aux::virtual_call::check_pre
        ) {
            this->check_subcontracted_pre(
                /* throw_on_failure = */ this->virtual_call()->action !=
                        boost::contract::aux::virtual_call::user_call
            );
            if(this->virtual_call()->action !=
                    boost::contract::aux::virtual_call::user_call) {
                throw boost::contract::aux::no_error();
            }
        } // Else (check only inv, post, etc.) do nothing.
    }
    
    // Check post here only if check-post-only mode (otherwise check at exit).
    void post_available() /* override */ {
        if(this->virtual_call()->action ==
                boost::contract::aux::virtual_call::check_post) {
            this->check_subcontracted_post();
            throw boost::contract::aux::no_error();
        } // Else (check only inv, pre, etc.) do nothing.
    }
    
    // Check static and non-static subcontracted invariant and, if body did not
    // throw, also check subcontracted post.
    void exit() {
        bool const body_threw = std::uncaught_exception();
        if(this->virtual_call()->action ==
                boost::contract::aux::virtual_call::user_call) {
            this->check_subcontracted_exit_inv();
            if(!body_threw) this->check_subcontracted_post();
        }
    }
};

} } } } // namespace

#endif // #include guard

