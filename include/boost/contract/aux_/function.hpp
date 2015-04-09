
#ifndef BOOST_CONTRACT_AUX_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/base_function.hpp>
#include <boost/contract/aux_/bases.hpp>
#include <boost/contract/aux_/invariant.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/contract/type.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/noncopyable.hpp>

namespace boost { namespace contract { namespace aux {

template<
    class Intro,
    class Class,
    typename FuncPtr,
    typename Arg0
> class function : public boost::contract::type, private boost::noncopyable {
public:
#if !BOOST_CONTRACT_CONFIG_PERMISSIVE
    BOOST_STATIC_ASSERT_MSG(!boost::contract::aux::has_mutable_invariant<
            Class>::value, "class invariant function must be const");
    BOOST_STATIC_ASSERT_MSG(
        (!boost::mpl::and_<
            boost::contract::aux::has_bases<Class>,
            boost::mpl::or_<
                boost::is_same<Intro, boost::contract::aux::none>,
                boost::is_same<FuncPtr, boost::contract::aux::none>
            >
        >::value),
        "must specify introspection type, function type, and function "
        "arguments for member contract of class with bases"
    );
    // TODO: static_assert(FuncPtr == none || class<FuncPtr>::type == Class)
#endif

    function ( Class* const obj, Arg0 arg0 ) :
        obj_(obj), virt_(boost::contract::virtual_body::user_call), arg0_(arg0)
    { init(); }
    
    function ( Class* const obj, Arg0 arg0,
            boost::contract::virtual_body const virt ) :
        obj_(obj), virt_(virt), arg0_(arg0)
    { init(); }
    
    function ( Class* const obj, boost::contract::virtual_body const virt ) :
        obj_(obj), virt_(virt)
    { init(); }

    ~function ( ) {
        // TODO: Do not check post on throw... inv can be checked on throw, but
        // not all the times... try to use use std::uncaught_exception for this.
        if(virt_.action == boost::contract::virtual_body::user_call) {
            check_inv();
            check_post();
        }
    }

private:
    friend class boost::contract::aux::base_function<
            Intro, Class, FuncPtr, Arg0>;
    
    // Base types as pointers because mpl::for_each will construct them.
    typedef typename boost::mpl::transform<
        typename boost::mpl::eval_if<boost::contract::aux::has_bases<Class>,
            boost::contract::aux::bases_of<Class>
        ,
            boost::mpl::identity<boost::mpl::vector<> >
        >::type,
        boost::add_pointer<boost::mpl::placeholders::_1>
    >::type base_ptrs;

    void init ( ) {
        assert(obj_);
        base_func_.derived_function(this);

        if(virt_.action == boost::contract::virtual_body::user_call) {
            check_inv();
        } else if(virt_.action ==
                boost::contract::virtual_body::check_inv_only) {
            check_inv();
            throw boost::contract::aux::no_error();
        }
    }

    void pre_available ( ) {
        if(virt_.action == boost::contract::virtual_body::user_call) {
            check_pre();
        } else if(virt_.action ==
                boost::contract::virtual_body::check_pre_only) {
            check_pre();
            throw boost::contract::aux::no_error();
        }
    }

    void post_available ( ) {
        if(virt_.action == boost::contract::virtual_body::check_post_only) {
            check_post();
            throw boost::contract::aux::no_error();
        }
    }
    
    void check_inv ( ) {
        boost::mpl::for_each<base_ptrs>(base_func_.action(
                boost::contract::virtual_body::check_inv_only));
        check_inv(boost::mpl::bool_<boost::contract::aux::has_invariant<Class>::
                value>());
    }

    void check_inv ( boost::mpl::false_ const& ) {}
    void check_inv ( boost::mpl::true_ const& ) {
        typename boost::add_const<Class>::type* const const_obj = obj_;
        const_obj->BOOST_CONTRACT_CONFIG_INVARIANT();
    }
            
    void check_pre ( ) {
        try {
            boost::mpl::for_each<base_ptrs>(base_func_.action(
                    boost::contract::virtual_body::check_pre_only));
            if(pre_) pre_(); // Pre logic-or: Last check, error if also throws.
        } catch(boost::contract::aux::no_error const&) {
            // Pre logic-or: Stop at 1st no_error (thrown by callee).
        }
    }
    
    void check_post ( ) {
        boost::mpl::for_each<base_ptrs>(base_func_.action(
                boost::contract::virtual_body::check_post_only));
        if(post_) post_();
    }

    boost::contract::aux::base_function<Intro, Class, FuncPtr, Arg0>
            base_func_;
    Class* const obj_;
    boost::contract::virtual_body const virt_;
    // TODO: add_reference to all these Arg-i types.
    // TODO: Support 0-to-n args.
    Arg0 arg0_;
};

} } } // namespace

#endif // #include guard

