/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_HPP_
#define DBC_PP_FUN_HPP_

#include "fun_parse/access.hpp"
#include "fun_parse/virtual.hpp"
#include "fun_parse/result_type.hpp"
#include "fun_parse/class_type.hpp"
#include "fun_parse/base_type.hpp"
#include "fun_parse/name.hpp"
#include "fun_parse/args.hpp"
#include "fun_parse/const.hpp"
#include "fun_parse/util/validate.hpp"
#include "fun_parse/util/match_not.hpp"
#include "fun_parse/util/append_traits.hpp"
#include "keywords.hpp"
#include "fun_traits.hpp"
#include <boost/preprocessor.hpp>

/**
 * Parse specified member function signature.
 * Different function traits can be inspected from this parse result using
 * the macros in file "pp/fun_traits.hpp".
 * @param signature Boost.Preprocessor sequence representing the member
 *  function signature in the following format:
 *      {(private)||(protected)||(public)} [(virtual)] (result_type)
 *      [(template)][DBC_COPYABLE](class_type)[DBC_BASE(base_class_type)]
 *      (name)( {[DBC_COPYABLE](arg_type) (arg_name)}* )
 *      [(const)]
 *  Where:  () wrap a Boost.Preprocessor sequence token (they must be used).
 *          [] indicate an optional expression.
 *          {} is the result of expression within parenthesis.
 *          || the "or" logical operator.
 *          * preceding expression repeated 0 or more times.
 *          result_type are any valid type identifier.
 *          DBC_COPIABLE(type) indicate specified type has copy contructor.
 *          Spaces can be used more or less freely.
 * @return Boost.Preprocessor tuple of 3 elements "(remaining-signature, 
 *  traits, (error-code, error-message))". "remaining-signature" is the 
 *  sequence of signature token that are still left to parse (it should be an
 *  empty sequence unless there was an error). "traits" are the function traits
 *  (or attributes) as parsed from the signature, they can be inspected using 
 *  the macros in fun_tratis.hpp (the tratis sequence may not be complete in 
 *  case of error, so you should use it only if error-code is 0). "(error-code,
 *  error-message)" is in turn another tuple of 2-elements that where 
 *  "error-code" is 0 only if there was no error and "error-message" is a 
 *  C-style (null terminated) string containing the error description.
 */
#define DBC_PP_MEM_FUN_(signature) \
    DBC_PP_FUN_PARSE_VALIDATE_(DBC_PP_FUN_TRAITS_COUNT_, \
    DBC_PP_FUN_PARSE_CONST_( /* [(const)] */ \
    DBC_PP_FUN_PARSE_ARGS_(DBC_PP_FUN_PARSE_ARGS_INFINITY_, \
            /* {[DBC_COPYABLE](arg_type) (arg_name)}* ) */ \
    DBC_PP_FUN_PARSE_NAME_( /* (name) */ \
    DBC_PP_FUN_PARSE_BASE_TYPE_( /* [DBC_BASE(base_type)] */\
    DBC_PP_FUN_PARSE_CLASS_TYPE_( /* [(template)][DBC_COPYABLE](class_type) */\
    DBC_PP_FUN_PARSE_RESULT_TYPE_( /* (result_type) */ \
    DBC_PP_FUN_PARSE_VIRTUAL_( /* [(virtual)] */ \
    DBC_PP_FUN_PARSE_ACCESS_( /* {(private)||(protected)||(public)} */\
            /* init sign_attr_err 3-elem tuple */ \
            ( signature (BOOST_PP_EMPTY) /* fun signature to parse */, \
            /* parsed fun attributes (empty sequence to start) */, \
            (0, "") /* error (code, message) */ ) \
    ))))))))) 

/**
 * Parse specified constructor signature.
 * @param signature Boost.Preprocessor sequence representing the constructor
 *  function signature in the following format:
 *      {(private)||(protected)||(public)}
 *      [(template)](class_type)
 *      ( {[DBC_COPYABLE](arg_type) (arg_name)}* )
 * Note that respect to member functions, constructor signatures have no 
 * virtual, no result_type, class_type cannot be copyable, no base_class_type,
 * no name, no const qualifier (as from C++ constructors declaration syntax).
 * @see DBC_PP_MEM_FUN()
 */
#define DBC_PP_CONSTRUCTOR_(signature) \
    DBC_PP_FUN_PARSE_VALIDATE_(DBC_PP_FUN_TRAITS_COUNT_, \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (BOOST_PP_EMPTY) /* no const */, \
    DBC_PP_FUN_PARSE_MATCH_NOT_(DBC_PP_IS_CONST_, \
            DBC_ERROR_constructors_may_not_be_cv_qualified_, \
    DBC_PP_FUN_PARSE_ARGS_(DBC_PP_FUN_PARSE_ARGS_INFINITY_, \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (init) /* "init" for name */, \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (BOOST_PP_EMPTY) /* no base */, \
    DBC_PP_FUN_PARSE_UNCOPYABLE_CLASS_TYPE_( \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (void) /* no result */, \
    DBC_PP_FUN_PARSE_MATCH_NOT_(DBC_PP_IS_VOID_, \
            DBC_ERROR_constructor_cannot_have_return_value_not_even_void_, \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (BOOST_PP_EMPTY) /* no virtual */, \
    DBC_PP_FUN_PARSE_MATCH_NOT_(DBC_PP_IS_VIRTUAL_, \
            DBC_ERROR_return_type_specification_for_constructor_invalid_, \
    DBC_PP_FUN_PARSE_ACCESS_( \
            /* init sign_attr_err 3-elem tuple */ \
            ( signature (BOOST_PP_EMPTY) /* fun signature to parse */, \
            /* parsed fun attributes (empty sequence to start) */, \
            (0, "") /* error (code, message) */ ) \
    ))))))))))))

/**
 * Parse specified destructor signature.
 * @param signature Boost.Preprocessor sequence representing the destructor
 *  function signature in the following format:
 *      {(private)||(protected)||(public)} [(virtual)]
 *      [(template)](class_type)
 *      ()
 * Note that respect to member functions, destructor signatures have no 
 * result_type, class_type cannot be copyable, no name, empty argument list,
 * no const qualifier (as from C++ destructors declaration syntax).
 * @see DBC_PP_MEM_FUN()
 */
#define DBC_PP_DESTRUCTOR_(signature) \
    DBC_PP_FUN_PARSE_VALIDATE_(DBC_PP_FUN_TRAITS_COUNT_, \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (BOOST_PP_EMPTY) /* const */, \
    DBC_PP_FUN_PARSE_MATCH_NOT_(DBC_PP_IS_CONST_, \
            DBC_ERROR_destructors_may_not_be_cv_qualified_, \
    DBC_PP_FUN_PARSE_ARGS_(0 /* no args, must use () */, \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (del) /* "del" for name */, \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (BOOST_PP_EMPTY) /* no base */, \
    DBC_PP_FUN_PARSE_UNCOPYABLE_CLASS_TYPE_( \
    DBC_PP_FUN_PARSE_APPEND_TRAITS_( (void) /* no result */, \
    DBC_PP_FUN_PARSE_MATCH_NOT_(DBC_PP_IS_VOID_, \
            DBC_ERROR_return_type_specification_for_destructor_invalid_, \
    DBC_PP_FUN_PARSE_VIRTUAL_( \
    DBC_PP_FUN_PARSE_ACCESS_( \
            /* init sign_attr_err 3-elem tuple */ \
            ( signature (BOOST_PP_EMPTY) /* fun signature to parse */, \
            /* parsed fun attributes (empty sequence to start) */, \
            (0, "") /* error (code, message) */ ) \
    )))))))))))

#endif // DBC_PP_FUN_HPP_

