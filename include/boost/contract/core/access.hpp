
#ifndef BOOST_CONTRACT_ACCESS_HPP_
#define BOOST_CONTRACT_ACCESS_HPP_

#include <boost/contract/core/config.hpp>
// Include instead of fwd decl to avoid warnings on tparam default value redef.
#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/aux_/type_traits/introspection.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/vector.hpp>
/** @endcond */

// TODO: Try to remove all friendship relations everywhere in the library and see if tests compile any faster by making internal API public instead. If that is the case, I could use AUX_SYMBOL instead of private...

namespace boost {
    namespace contract {
        class virtual_;

        namespace aux {
            template<class, typename, typename, class, typename, typename>
            class check_subcontracted_pre_post_inv;

            template<typename, class>
            class check_pre_post_inv;
        }
    }
}

namespace boost { namespace contract {

// NOTE: Not making this class friend will cause compiler errors on some
// compilers (e.g., MSVC) because the private members needed for contracts
// will not be accessible. On other compilers (e.g., GCC and CLang), the
// private access will instead simply fail SFINAE and no compiler error will be
// reported but invariants and subcontracting checking will be silently skipped
// at run-time. Therefore programmers must make sure to either declare contract
// members public or to make this class a friend.
class access {
    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_TYPE(has_base_types,
            BOOST_CONTRACT_CONFIG_BASE_TYPES)

    template<class C>
    struct base_types_of {
        typedef typename C::BOOST_CONTRACT_CONFIG_BASE_TYPES type;
    };

    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION(
            has_invariant_func, BOOST_CONTRACT_CONFIG_INVARIANT)
    
    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION(
        has_non_static_invariant_func,
        BOOST_CONTRACT_CONFIG_STATIC_INVARIANT
    )

    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_STATIC_MEMBER_FUNCTION(
            has_static_invariant_func, BOOST_CONTRACT_CONFIG_STATIC_INVARIANT)

    // TODO: Unless PERMISSIVE, enforce: !has_invariant<C> || has_const_invariant<C> || has_const_volatile_invariant<C> 

    template<typename T>
    struct has_const_invariant : has_invariant_func<T, void,
            boost::mpl::vector<>, boost::function_types::const_non_volatile> {};

    template<typename T>
    struct has_const_volatile_invariant : has_invariant_func<T, void,
            boost::mpl::vector<>, boost::function_types::cv_qualified> {};

    template<typename T>
    struct has_invariant : has_invariant_func<T, void,
            boost::mpl::vector<> > {};

    // TODO: Unless PERMISSIVE, enforce: !has_non_static_invariant<Class>

    template<typename T>
    struct has_static_invariant : has_static_invariant_func<T, void,
                boost::mpl::vector<> > {};

    template<typename T>
    struct has_non_static_invariant : has_non_static_invariant_func<T, void,
            boost::mpl::vector<> > {};
 
    template<typename C>
    static void static_invariant() {
        C::BOOST_CONTRACT_CONFIG_STATIC_INVARIANT();
    }

    template<typename C>
    static void const_invariant(C const* obj) {
        BOOST_CONTRACT_AUX_DEBUG(obj);
        obj->BOOST_CONTRACT_CONFIG_INVARIANT();
    }

    // Friendship used to limit library's public API.

    template<class, typename, typename, class, typename, typename>
    friend class boost::contract::aux::check_subcontracted_pre_post_inv;
            
    template<typename, class>
    friend class boost::contract::aux::check_pre_post_inv;

    template<class O, typename F, class C>
    friend set_precondition_old_postcondition<> public_function(
            virtual_*, F, C*);
    
    template<class O, typename R, typename F, class C>
    friend set_precondition_old_postcondition<R> public_function(
            virtual_*, R&, F, C*);

    template<class O, typename F, class C, typename A0>
    friend set_precondition_old_postcondition<> public_function(
            virtual_*, F, C*, A0&);

    template<class O, typename R, typename F, class C, typename A0>
    friend set_precondition_old_postcondition<R> public_function(
            virtual_*, R&, F, C*, A0&);
    
    template<class O, typename F, class C, typename A0, typename A1>
    friend set_precondition_old_postcondition<> public_function(
            virtual_*, F, C*, A0&, A1&);

    template<class O, typename R, typename F, class C, typename A0, typename A1>
    friend set_precondition_old_postcondition<R> public_function(
            virtual_*, R&, F, C*, A0&, A1&);
};

} } // namespace

#endif // #include guard

