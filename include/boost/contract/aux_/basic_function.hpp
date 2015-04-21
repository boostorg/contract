
#ifndef BOOST_CONTRACT_AUX_BASIC_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_BASIC_FUNCTION_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/base_function.hpp>
#include <boost/contract/aux_/bases.hpp>
#include <boost/contract/aux_/invariant.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/contract/type.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/noncopyable.hpp>

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
    class Class = boost::contract::aux::none,
    class Intro = boost::contract::aux::none,
    typename Func = boost::contract::aux::none,
    typename Arg0 = boost::contract::aux::none
> class basic_function : public boost::contract::type,
        private boost::noncopyable {
    friend class boost::contract::aux::base_function<
            basic_function, Intro, Func>;
    
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
    explicit basic_function(Class* const obj, Arg0 arg0) : base_func_(),
            obj_(obj), arg0_(arg0) {
        BOOST_CONTRACT_AUX_DEBUG(obj_);
        base_func_.derived_function(this);
    }
    
    explicit basic_function(Class* const obj) : base_func_(), obj_(obj) {
        BOOST_CONTRACT_AUX_DEBUG(obj_);
        base_func_.derived_function(this);
    }
    
    explicit basic_function() : base_func_(), obj_(0) {
        base_func_.derived_function(this);
    }

protected:
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
    
private:
    void check_static_inv(boost::mpl::false_ const&) {}
    void check_static_inv(boost::mpl::true_ const&) {
        Class::BOOST_CONTRACT_CONFIG_STATIC_INVARIANT();
    }
        
    void check_cv_inv(boost::mpl::false_ const&) {}
    void check_cv_inv(boost::mpl::true_ const&) {
        typename boost::add_const<Class>::type* const const_obj = obj_;
        BOOST_CONTRACT_AUX_DEBUG(const_obj);
        const_obj->BOOST_CONTRACT_CONFIG_INVARIANT();
    }
            
    boost::contract::aux::base_function<basic_function, Intro, Func> base_func_;
    Class* const obj_;
    // TODO: add_reference/perfect fwd to all these Arg-i types.
    // TODO: Support 0-to-n args.
    Arg0 arg0_;
};

} } } // namespace

#endif // #include guard

