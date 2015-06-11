
#ifndef BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/operation/public_function.hpp>
#include <boost/contract/aux_/operation/public_static_function.hpp>
#include <boost/contract/aux_/type_traits/base_types.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/optional.hpp>
#include <boost/make_shared.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/static_assert.hpp>
/** @endcond */

/* PRIVATE */

// This check is strictly not necessary because compilation will fail anyways,
// but it helps limiting cryptic compiler's errors.
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_ARITY(F, arity) \
    BOOST_STATIC_ASSERT_MSG( \
        /* -2 for both `this` and `virtual_*` extra parameters */ \
        boost::function_types::function_arity<F>::value - 2 == arity, \
        "missing one or more arguments for specified function" \
    );

// Always enforce this so base contracts can always specify postconditions with
// result, without need to change derived contracts.
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_VOID_RESULT_(F) \
    BOOST_STATIC_ASSERT_MSG( \
        boost::is_same< \
            typename boost::function_types::result_type<F>::type, \
            void \
        >::value, \
        "missing result argument for non-void function" \
    );

#define BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_RESULT_(F, R) \
    BOOST_STATIC_ASSERT_MSG( \
        boost::is_same< \
            typename boost::remove_reference<typename boost::function_types:: \
                    result_type<F>::type>::type, \
            typename boost::contract::public_function_:: \
                    remove_optional<R>::type \
        >::value, \
        "miss-matching result type for specified function" \
    );

// Always enforce this so this lib can check and enforce override.
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_BASE_TYPES_(C) \
    BOOST_STATIC_ASSERT_MSG( \
        boost::contract::aux::has_base_types<C>::value, \
        "enclosing class missing 'base types' typdef" \
    );

/* CODE */

namespace boost { namespace contract {

namespace public_function_ {
    template<typename R>
    struct remove_optional { typedef R type; };

    template<typename R>
    struct remove_optional<boost::optional<R> > {
        typedef typename boost::remove_reference<R>::type type;
    };
}

// For static member functions.
template<class C>
set_precondition_postcondition<> public_function() {
    return set_precondition_postcondition<>(boost::make_shared<
            boost::contract::aux::public_static_function<C> >());
}

// For non-virtual, non-overriding member functions.
template<class C>
set_precondition_postcondition<> public_function(C* obj) {
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_function<
            boost::contract::aux::none,
            boost::contract::aux::none,
            boost::contract::aux::none,
            C,
            boost::contract::aux::none, boost::contract::aux::none
        >
    >(
        static_cast<boost::contract::virtual_*>(0),
        obj,
        boost::contract::aux::none::value,
        boost::contract::aux::none::value, boost::contract::aux::none::value
    ));
}

// NOTE: O and R (optionally) allowed only when v is present because:
// * An overriding func must override a base func declared virtual so with
//   v extra param, thus the overriding func must also always have v (i.e., O
//   might be present only if v is also present).
//   However, the first appearing virtual func (e.g., in root class) will not
//   override any previously declared virtual func so does not need O (i.e., O
//   always optional).
//   Furthermore, F needs to be specified only together with O.
// * R is only used for virtual functions (i.e., R might be present only if v
//   is also present).
//   However, R is never specified, not even for virtual functions, when the
//   return type is void (i.e., R always optional).

// For virtual, non-overriding, void function.
template<class C>
set_precondition_postcondition<> public_function(virtual_* v, C* obj) {
    // NOTE: No F so cannot enforce enclosing function is void (up to user).
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_function<
            boost::contract::aux::none,
            boost::contract::aux::none,
            boost::contract::aux::none,
            C,
            boost::contract::aux::none, boost::contract::aux::none
        >
    >(v, obj, boost::contract::aux::none::value, boost::contract::aux::none::
            value, boost::contract::aux::none::value));
}

// For virtual, non-overriding, non-void member functions.
template<typename R, class C>
set_precondition_postcondition<R> public_function(virtual_* v, R& r, C* obj) {
    // NOTE: No F so cannot enforce enclosing function returns R (up to user).
    return set_precondition_postcondition<R>(boost::make_shared<
        boost::contract::aux::public_function<
            boost::contract::aux::none,
            R,
            boost::contract::aux::none,
            C,
            boost::contract::aux::none, boost::contract::aux::none
        >
    >(v, obj, r, boost::contract::aux::none::value,
            boost::contract::aux::none::value));
}

/* Overriding (arity = 0) */

// For virtual, overriding, void member functions.
template<class O, typename F, class C>
set_precondition_postcondition<> public_function(virtual_* v, F, C* obj) {
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_ARITY(F, 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_VOID_RESULT_(F)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_BASE_TYPES_(C)
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_function<
            O,
            boost::contract::aux::none,
            F,
            C,
            boost::contract::aux::none, boost::contract::aux::none
        >
    >(v, obj, boost::contract::aux::none::value, boost::contract::aux::none::
            value, boost::contract::aux::none::value));
}

// For virtual, overriding, non-void member functions of class with bases.
template<class O, typename R, typename F, class C>
set_precondition_postcondition<R> public_function(
        virtual_* v, R& r, F, C* obj) {
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_ARITY(F, 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_RESULT_(F, R)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_BASE_TYPES_(C)
    return set_precondition_postcondition<R>(boost::make_shared<
        boost::contract::aux::public_function<
            O,
            R,
            F,
            C,
            boost::contract::aux::none, boost::contract::aux::none
        >
    >(v, obj, r, boost::contract::aux::none::value,
            boost::contract::aux::none::value));
}

/* Overriding (arity = 1) */

template<class O, typename F, class C, typename A0>
set_precondition_postcondition<> public_function(
        virtual_* v, F, C* obj, A0& a0) {
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_ARITY(F, 1)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_VOID_RESULT_(F)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_BASE_TYPES_(C)
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_function<
            O,
            boost::contract::aux::none,
            F,
            C,
            A0, boost::contract::aux::none
        >
    >(v, obj, boost::contract::aux::none::value, a0,
            boost::contract::aux::none::value));
}

template<class O, typename R, typename F, class C, typename A0>
set_precondition_postcondition<R> public_function(
        virtual_* v, R& r, F, C* obj, A0& a0) {
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_ARITY(F, 1)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_RESULT_(F, R)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_BASE_TYPES_(C)
    return set_precondition_postcondition<R>(boost::make_shared<
        boost::contract::aux::public_function<
            O,
            R,
            F,
            C,
            A0, boost::contract::aux::none
        >
    >(v, obj, r, a0, boost::contract::aux::none::value));
}

/* Overriding (arity = 2) */

template<class O, typename F, class C, typename A0, typename A1>
set_precondition_postcondition<> public_function(
        virtual_* v, F, C* obj, A0& a0, A1& a1) {
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_ARITY(F, 2)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_VOID_RESULT_(F)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_BASE_TYPES_(C)
    return set_precondition_postcondition<>(boost::make_shared<
        boost::contract::aux::public_function<
            O,
            boost::contract::aux::none,
            F,
            C,
            A0, A1
        >
    >(v, obj, boost::contract::aux::none::value, a0, a1));
}
    
template<class O, typename R, typename F, class C, typename A0, typename A1>
set_precondition_postcondition<R> public_function(
        virtual_* v, R& r, F, C* obj, A0& a0, A1& a1) {
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_ARITY(F, 2)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_RESULT_(F, R)
    BOOST_CONTRACT_PUBLIC_FUNCTION_HAS_BASE_TYPES_(C)
    return set_precondition_postcondition<R>(boost::make_shared<
        boost::contract::aux::public_function<
            O,
            R,
            F,
            C,
            A0, A1
        >
    >(v, obj, r, a0, a1));
}

// TODO: Support configurable arity.

} } // namespace

#endif // #include guard

