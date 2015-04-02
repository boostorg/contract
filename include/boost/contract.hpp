
#ifndef BOOST_CONTRACT_HPP_
#define BOOST_CONTRACT_HPP_

#include <boost/contract/class.hpp>
#include <boost/contract/class_invariant.hpp>
#include <boost/contract/function.hpp>
#include <boost/function.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#include <boost/mpl/at.hpp>
#include <typeinfo>
#include <iostream>

/* PUBLIC */

#define BOOST_CONTRACT_BASE_ENUM(va_seq) BOOST_CONTRACT_BASES_(va_seq, 0)

#define BOOST_CONTRACT_BASE_TYPES(va_seq) BOOST_CONTRACT_BASES_(va_seq, 1)

/* PRIVATE */

#define BOOST_CONTRACT_BASES_(va_seq, is_type) \
    BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONTRACT_BASE_, is_type, \
            BOOST_PP_VARIADIC_SEQ_TO_SEQ(va_seq))

#define BOOST_CONTRACT_BASE_(r, is_type, i, parenthesized_base) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_IIF(is_type, \
        BOOST_CONTRACT_BASE_TYPE_ \
    , \
        BOOST_PP_TUPLE_REM(0) \
    ) parenthesized_base

#define BOOST_CONTRACT_BASE_TYPE_(prefix, ...) \
    BOOST_CONTRACT_BASE_REMOVE_IIF_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VIRTUAL_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_VIRTUAL_REMOVE_FRONT, \
    BOOST_CONTRACT_BASE_REMOVE_IIF_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PUBLIC_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PUBLIC_REMOVE_FRONT, \
    BOOST_CONTRACT_BASE_REMOVE_IIF_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PROTECTED_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE_FRONT, \
    BOOST_CONTRACT_BASE_REMOVE_IIF_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PRIVATE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PRIVATE_REMOVE_FRONT, \
    BOOST_CONTRACT_BASE_REMOVE_IIF_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VIRTUAL_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_VIRTUAL_REMOVE_FRONT, \
        prefix \
    ))))) \
    BOOST_PP_COMMA_IF(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)) \
    __VA_ARGS__
    
#define BOOST_CONTRACT_BASE_REMOVE_IIF_(is_macro, remove_macro, tokens) \
    BOOST_PP_IIF(is_macro(tokens), remove_macro, BOOST_PP_TUPLE_REM(1))(tokens)

/* CODE */

namespace boost { namespace contract {

struct control {
    /* implicit */ control ( int ) {}
};

template<
    template<
        class Base,
        typename ResultType,
        typename ParameterTypes,
        class = boost::function_types::null_tag
    > class HasFunction
    , class Base0
    , class Base1
>
struct function {
    template<
        typename FunctionPtr,
        class Class,
        typename Precondition,
        typename Postcondition
    >
    function (
        control const& c,
        FunctionPtr function_ptr,
        Class* const object,
        Precondition const& precondition,
        Postcondition const& postcondition
    ) : 
        precondition_(precondition),
        postcondition_(postcondition)
    {

        std::cout << "here!" << std::endl;
        
        typedef boost::function_types::result_type<FunctionPtr>::type
                result_type;
        typedef boost::function_types::parameter_types<
                FunctionPtr, boost::mpl::identity<boost::mpl::_> > member_types;
        typedef boost::mpl::pop_front<member_types>::type parameter_types;

        std::cout << std::endl;
        check_invariant<Base0>(object, boost::mpl::bool_<
                HasFunction<Base0, result_type, parameter_types>::value>());
        //check_invariant<Base1>(object, boost::mpl::bool_<
        //        HasFunction<Base1, result_type, parameter_types>::value>());
        object->invariant();
        
        std::cout << std::endl;
        std::cout << typeid(FunctionPtr).name() << std::endl;
        Base0* const base0 = object;
        //(base0->*function_ptr)(-1, 0);

        //typedef boost::function_types::member_function_pointer<
        //    result_type,
        //    boost::mpl::push_front<Base0, parameter_types>
        //>::type base_function_ptr0;
        //std::cout << typeid(base_function_ptr0).name() << std::endl;
        
        std::cout << std::endl;

#ifndef BOOST_CONTRACT_CONFIG_NO_STATIC_CHECKS
        BOOST_STATIC_ASSERT_MSG(
            boost::is_same<boost::mpl::front<member_types>::type, Class>::value,
            "specified function pointer is not a member of class type"
        );
        BOOST_STATIC_ASSERT_MSG(boost::is_base_of<Base0, Class>::value,
                "class type is not derived from 1st specified base");
        BOOST_STATIC_ASSERT_MSG(boost::is_base_of<Base1, Class>::value,
                "class type is not derived from 2nd specified base");
#endif
    }

private:
    template< class Base, class Class >
    void check_invariant (
            Class const* const object, boost::mpl::true_ const& ) {
        Base const* const base = object;
        base->invariant();
    }
    
    template< class Base, class Class >
    void check_invariant (
            Class const* const object, boost::mpl::false_ const& ) { }

    boost::function<void ( )> const precondition_;
    boost::function<void ( )> const postcondition_;
};

} } // namespace

#endif // #include guard

