
#ifndef BOOST_CONTRACT_AUX_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/base_function.hpp>
#include <boost/contract/aux_/function_key.hpp>
#include <boost/contract/aux_/bases.hpp>
#include <boost/contract/aux_/invariant.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/contract/type.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/noncopyable.hpp>
#include <exception>
#include <cassert>

// TODO: Modelling after Clang message for assert() failure:
// assertion "(Key != boost::contract::aux::constructor)" failed: file "..\include/boost/contract/aux_/function.hpp", line 156
// This library should say:
// precondition/postcondition/invariant/... "..." failed: file "...", line ...
// for exception classes precondition/postcondition/..._failure (inheriting from
// assertion_failure base exception to be thrown by CONTRACT_ASSERT) and failure
// handlers [set_]precondition_failed.

// TODO: Consider splitting this class into aux_/constructor, aux_/destructor,
// etc. bases on Key while keeping all check_... functions in a
// aux_/basic_function base class (or even in contract::type directly). The code
// might be more clear without all the switch on Key.

namespace boost { namespace contract { namespace aux {

template<
    boost::contract::aux::function_key Key,
    class Class = boost::contract::aux::none,
    class Intro = boost::contract::aux::none,
    typename Func = boost::contract::aux::none,
    typename Arg0 = boost::contract::aux::none
> class function : public boost::contract::type, private boost::noncopyable {
    friend class boost::contract::aux::base_function<function, Intro, Func>;
    
    // Base types as pointers because mpl::for_each will construct them.
    typedef typename boost::mpl::transform<
        typename boost::mpl::eval_if<boost::contract::aux::has_bases<Class>,
            boost::contract::aux::bases_of<Class>
        ,
            boost::mpl::identity<boost::mpl::vector<> >
        >::type,
        boost::add_pointer<boost::mpl::placeholders::_1>
    >::type base_ptrs;

#if !BOOST_CONTRACT_CONFIG_PERMISSIVE
    // TODO: Fix those.
    //BOOST_STATIC_ASSERT_MSG(!boost::contract::aux::has_mutable_invariant<
    //        Class>::value, "class invariant function must be const");
    //BOOST_STATIC_ASSERT_MSG(
    //    (!boost::mpl::and_<
    //        boost::contract::aux::has_bases<Class>,
    //        boost::mpl::or_<
    //            boost::is_same<Intro, boost::contract::aux::none>,
    //            boost::is_same<Func, boost::contract::aux::none>
    //        >
    //    >::value),
    //    "must specify introspection type, function type, and function "
    //    "arguments for member contract of class with bases"
    //);
    // TODO: static_assert(Func == none || class<Func>::type == Class)
#endif

public:
    // Called for public members with virtual body and with or without bases.
    function(boost::contract::virtual_body const virt, Class* const obj,
            Arg0 arg0) :
        base_func_(), virt_(virt), obj_(obj), arg0_(arg0)
    {
        BOOST_CONTRACT_AUX_DEBUG((Key == boost::contract::aux::public_member));
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Class,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Intro,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((!boost::is_same<Func,
                boost::contract::aux::none>::value));
        BOOST_CONTRACT_AUX_DEBUG((obj_));

        init();
    }
    
    function(Class* const obj, Arg0 arg0) :
        base_func_(), virt_(boost::contract::virtual_body::user_call),
                obj_(obj), arg0_(arg0)
    { init(); }

    
    function(boost::contract::virtual_body const virt, Class* const obj) :
        base_func_(), virt_(virt), obj_(obj) 
    { init(); }
    
    explicit function(Class* const obj) :
        base_func_(), virt_(boost::contract::virtual_body::user_call),
                obj_(obj) 
    { init(); }
    
    function() :
        base_func_(), virt_(boost::contract::virtual_body::user_call),
                obj_(0) 
    { init(); }
    

    // Contract execution entry/exit points (use virt_ and Key as needed).

private:
    void init() { // Entry point for inv.
        BOOST_CONTRACT_AUX_DEBUG(virt_.action == boost::contract::virtual_body::
                user_call || Key == boost::contract::aux::public_member);

        base_func_.derived_function(this);

        if(
            Key == boost::contract::aux::constructor ||
            Key == boost::contract::aux::destructor ||
            Key == boost::contract::aux::protected_member
        ) {
            check_inv(/* static_inv_only = */ true);
        } else if(Key != boost::contract::aux::private_member &&
                Key != boost::contract::aux::free_function) {
            if(virt_.action == boost::contract::virtual_body::user_call) {
                check_subcontracted_inv();
            } else if(virt_.action ==
                    boost::contract::virtual_body::check_inv_only) {
                check_subcontracted_inv();
                throw boost::contract::aux::no_error();
            } else if(virt_.action ==
                // TODO: Do I really need the check_static_inv_only action or
                // static-inv-check-only applies only to check_inv() and not
                // to check_subcontracted_inv()?
                    boost::contract::virtual_body::check_static_inv_only) {
                check_subcontracted_inv(/* static_inv_only = */ true);
                throw boost::contract::aux::no_error();
            } // Else (check only pre, post, etc.) do nothing.
        }
    }

    void pre_available() { // Entry point for pre.
        BOOST_CONTRACT_AUX_DEBUG((Key != boost::contract::aux::constructor));
        BOOST_CONTRACT_AUX_DEBUG((Key != boost::contract::aux::destructor));

        if(
            Key == boost::contract::aux::protected_member ||
            Key == boost::contract::aux::private_member ||
            Key == boost::contract::aux::free_function
        ) {
            check_pre();
        } else if(virt_.action == boost::contract::virtual_body::user_call) {
            check_subcontracted_pre();
        } else if(virt_.action ==
                boost::contract::virtual_body::check_pre_only) {
            check_subcontracted_pre();
            throw boost::contract::aux::no_error();
        } // Else (check only inv, post, etc.) do nothing.
    }
    
    void post_available() { // "Normal exit" point when only post.
        if(virt_.action == boost::contract::virtual_body::check_post_only) {
            check_subcontracted_post();
            throw boost::contract::aux::no_error();
        } // Else (check only inv, pre, etc.) do nothing.
    }
    
public:
    ~function() { // Exit point for inv and post when user call.
        bool const body_threw = std::uncaught_exception();
        if(virt_.action == boost::contract::virtual_body::user_call) {
            if(Key == boost::contract::aux::constructor) {
                check_inv(/* static_inv_only = */ body_threw);
                if(!body_threw) check_post();
            } else if(Key == boost::contract::aux::destructor) {
                check_inv(/* static_inv_only = */ !body_threw);
                if(!body_threw) check_post();
            } else if(Key == boost::contract::aux::protected_member) {
                check_subcontracted_inv(/* static_inv_only = */ true);
                if(!body_threw) check_post();
            } else if(
                Key == boost::contract::aux::private_member ||
                Key == boost::contract::aux::free_function
            ) {
                if(!body_threw) check_post();
            } else {
                check_subcontracted_inv();
                if(!body_threw) check_subcontracted_post();
            }
        }
    }

    // Actual checks (should not use virt_ or Key).

private:
    void check_subcontracted_inv(bool const static_inv_only = false) {
        if(!boost::mpl::empty<base_ptrs>::value && obj_) {
            boost::mpl::for_each<base_ptrs>(base_func_.action(
                static_inv_only ?
                    boost::contract::virtual_body::check_static_inv_only
                :
                    boost::contract::virtual_body::check_inv_only
            ));
        }
        check_inv(static_inv_only);
    }

    void check_inv(bool const static_inv_only = false) {
        check_static_inv(boost::mpl::bool_<boost::contract::aux::
                has_static_invariant<Class>::value>());
        if(!static_inv_only && obj_) {
            check_cv_inv(boost::mpl::bool_<boost::contract::aux::
                    has_const_invariant<Class>::value>());
        }
    }

    void check_static_inv(boost::mpl::false_ const&) {}
    void check_static_inv(boost::mpl::true_ const&) {
        Class::BOOST_CONTRACT_CONFIG_STATIC_INVARIANT();
    }
        
    void check_cv_inv(boost::mpl::false_ const&) {}
    void check_cv_inv(boost::mpl::true_ const&) {
        typename boost::add_const<Class>::type* const const_obj = obj_;
        const_obj->BOOST_CONTRACT_CONFIG_INVARIANT();
    }
            
    void check_subcontracted_pre() {
        try {
            if(!boost::mpl::empty<base_ptrs>::value && obj_) {
                boost::mpl::for_each<base_ptrs>(base_func_.action(
                        boost::contract::virtual_body::check_pre_only));
            }
            check_pre(); // Pre logic-or: Last check, error if also throws.
        } catch(boost::contract::aux::no_error const&) {
            // Pre logic-or: Stop at 1st no_error (thrown by callee).
        }
    }

    void check_pre() { if(pre_) pre_(); }
    
    void check_subcontracted_post() {
        if(!boost::mpl::empty<base_ptrs>::value && obj_) {
            boost::mpl::for_each<base_ptrs>(base_func_.action(
                    boost::contract::virtual_body::check_post_only));
        }
        check_post();
    }
        
    void check_post() { if(post_) post_(); }

    boost::contract::aux::base_function<function, Intro, Func> base_func_;
    boost::contract::virtual_body const virt_;
    Class* const obj_;
    // TODO: add_reference/perfect fwd to all these Arg-i types.
    // TODO: Support 0-to-n args.
    Arg0 arg0_;
};

} } } // namespace

#endif // #include guard

