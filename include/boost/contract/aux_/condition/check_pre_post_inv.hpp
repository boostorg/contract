
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
/** @cond */
#include <boost/utility/enable_if.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<typename R, class C>
class check_pre_post_inv : public check_pre_post<R> { // Non-copyable base.
public:
    #if BOOST_CONTRACT_INVARIANTS && !defined(BOOST_CONTRACT_CONFIG_PERMISSIVE)
        BOOST_STATIC_ASSERT_MSG(
            !boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl:: vector<>
            >::value,
            "static invariant member function cannot be mutable "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            !boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::const_non_volatile
            >::value,
            "static invariant member function cannot be const qualified "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            !boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::volatile_non_const
            >::value,
            "static invariant member function cannot be volatile qualified "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            !boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::cv_qualified
            >::value,
            "static invariant member function cannot be const volatile "
            "qualified (it must be static instead)"
        );

        BOOST_STATIC_ASSERT_MSG(
            !boost::contract::access::has_invariant_s<
                C, void, boost::mpl::vector<>
            >::value,
            "non-static invariant member function cannot be static "
            "(it must be either const or const volatile qualified instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            !boost::contract::access::has_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::non_cv
            >::value,
            "non-static invariant member function cannot be mutable "
            "(it must be either const or const volatile qualified instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            !boost::contract::access::has_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::volatile_non_const
            >::value,
            "non-static invariant member function cannot be volatile qualified "
            "(it must be const or const volatile qualified instead)"
        );
    #endif

    // obj can be 0 for static member functions.
    explicit check_pre_post_inv(boost::contract::from from, C* obj) :
        check_pre_post<R>(from)
        #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
                BOOST_CONTRACT_INVARIANTS
            , obj_(obj)
        #endif
    {}
    
protected:
    #if BOOST_CONTRACT_ENTRY_INVARIANTS
        void check_entry_inv() { check_inv(true, false); }
        void check_entry_static_inv() { check_inv(true, true); }
    #endif
    
    #if BOOST_CONTRACT_EXIT_INVARIANTS
        void check_exit_inv() { check_inv(false, false); }
        void check_exit_static_inv() { check_inv(false, true); }
    #endif

    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        C* object() { return obj_; }
    #endif

private:
    #if BOOST_CONTRACT_INVARIANTS
        void check_inv(bool on_entry, bool static_inv_only) {
            if(this->failed()) return;
            try {
                // Static members only check static inv.
                check_static_inv<C>();
                if(!static_inv_only) {
                    // Volatile (const or not) members check static and cv inv.
                    check_cv_inv<C>();
                    // Other members (const or not) check static, cv, and const.
                    check_const_inv<C>();
                }
            } catch(...) {
                if(on_entry) {
                    this->fail(&boost::contract::entry_invariant_failure);
                } else this->fail(&boost::contract::exit_invariant_failure);
            }
        }

        template<class C_>
        typename boost::enable_if<
                boost::contract::access::has_static_invariant<C_> >::type
        check_static_inv() {
            // SFINAE HAS_STATIC_... returns true even when member is inherited
            // so extra run-time check here (not the same for non static).
            if(!inherited<boost::contract::access::has_static_invariant,
                    boost::contract::access::static_invariant_addr>::apply()) {
                boost::contract::access::static_invariant<C_>();
            }
        }

        template<class C_>
        typename boost::disable_if<
                boost::contract::access::has_static_invariant<C_> >::type
        check_static_inv() {}

        template<class C_>
        typename boost::enable_if<
                boost::contract::access::has_cv_invariant<C_> >::type
        check_cv_inv() { boost::contract::access::cv_invariant(obj_); }
        
        template<class C_>
        typename boost::disable_if<
                boost::contract::access::has_cv_invariant<C_> >::type
        check_cv_inv() {}

        template<class C_>
        struct call_const_inv :
            boost::mpl::and_<
                boost::contract::access::has_const_invariant<C_>,
                // Volatile (like const) cannot be stripped so [const] volatile
                // members only check cv invariant, and cannot check const inv.
                boost::mpl::not_<boost::is_volatile<C_> >
            >
        {};
        
        template<class C_>
        typename boost::enable_if<call_const_inv<C_> >::type
        check_const_inv() { boost::contract::access::const_invariant(obj_); }

        template<class C_>
        typename boost::disable_if<call_const_inv<C_> >::type
        check_const_inv() {}
        
        // Check is class's func is inherited from its base types or not.
        template<template<class> class HasFunc, template<class> class FuncAddr>
        struct inherited {
            static bool apply() {
                try {
                    boost::mpl::for_each<
                        // For now, no reason to deeply search inheritance tree
                        // (SFINAE HAS_STATIC_... already fails in that case).
                        typename boost::mpl::transform<
                            typename boost::mpl::copy_if<
                                typename boost::mpl::eval_if<boost::contract::
                                        access::has_base_types<C>,
                                    typename boost::contract::access::
                                            base_types_of<C>
                                ,
                                    boost::mpl::vector<>
                                >::type,
                                HasFunc<boost::mpl::_1>
                            >::type,
                            boost::add_pointer<boost::mpl::_1>
                        >::type
                    >(compare_func_addr());
                } catch(signal_equal const&) { return true; }
                return false;
            }

        private:
            class signal_equal {}; // Except. to stop for_each as soon as found.

            struct compare_func_addr {
                template<typename B>
                void operator()(B*) {
                    // Inherited func has same addr as in its base.
                    if(FuncAddr<C>::apply() == FuncAddr<B>::apply()) {
                        throw signal_equal();
                    }
                }
            };
        };
    #endif

    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        C* obj_;
    #endif
};

} } } // namespace

#endif // #include guard

