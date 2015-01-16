
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ_HPP_

#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/control/iif.hpp>

// NOTE: This algorithm is not so generic because it requires that the
// enumerated elements can be checked using IS_NIL (that assumption is usually
// only true for declaration traits so this is programmed here in the traits).

/* PRIVATE */

// Wrapped with parenthesis after removal of NIL so to make it a pp-seq elem.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ_REMOVE_NIL_(back) \
    (BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(back))

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ_BACK_(seq, back) \
    BOOST_PP_SEQ_POP_BACK(seq) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(back), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ_REMOVE_NIL_ \
    )(back)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ_(seq) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ_BACK_(seq, \
            BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq))

/* PUBLIC */

// Expand `x, ..., y[,]` (note a trailing commas is optionally allowed similarly
// to C++ enum declarations) to `(x)...(y)`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ(...) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ_( \
            BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__ BOOST_PP_NIL))

#endif // #include guard

