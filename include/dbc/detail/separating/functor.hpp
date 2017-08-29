/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under Eiffel for C++ Software License.
 */

#if !BOOST_PP_IS_ITERATING
#   ifndef DBC_SEPARATING_FUNCTOR_HPP_ // Include guard.
#       define DBC_SEPARATING_FUNCTOR_HPP_

#       include "type_traits.hpp"
#       include "../none.hpp"
#       include "../../config.hpp"
#       include <boost/preprocessor.hpp>
#       include <boost/bind.hpp>
#       include <boost/mpl/vector.hpp>

// Iterate over arg num.
#       define BOOST_PP_ITERATION_PARAMS_1 (3, (0, DBC_CONFIG_MAX_ARGC, \
                DBC_CONFIG_FUNCTOR_HPP_FILE_PATH))
#       include BOOST_PP_ITERATE()
#   endif // DBC_SEPARATING_FUNCTOR_HPP_

// Iterate over void/non-void.
#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_PP_ITERATION_PARAMS_2 (3, (0, 1, \
            DBC_CONFIG_FUNCTOR_HPP_FILE_PATH))
#   include BOOST_PP_ITERATE()

// Iterate over const/non-const.
#elif BOOST_PP_ITERATION_DEPTH() == 2
#   define BOOST_PP_ITERATION_PARAMS_3 (3, (0, 1, \
            DBC_CONFIG_FUNCTOR_HPP_FILE_PATH))
#   include BOOST_PP_ITERATE()

// Code for a given arg mun, void or non-void, const or non-const.
#elif BOOST_PP_ITERATION_DEPTH() == 3

    // Arg num.
#   define DBC_rest_arg_num BOOST_PP_FRAME_ITERATION(1)
#   define DBC_arg_num BOOST_PP_SUB(BOOST_PP_FRAME_FINISH(1), \
            DBC_rest_arg_num)
    // Void or not.
#   define DBC_is_void BOOST_PP_FRAME_ITERATION(2)
#   define DBC_is_not_void BOOST_PP_NOT(DBC_is_void)
    // Const or not.
#   define DBC_is_const BOOST_PP_FRAME_ITERATION(3)
#   define DBC_is_not_const BOOST_PP_NOT(DBC_is_const)
    // Template specialization or not.
#   define DBC_is_spec BOOST_PP_OR(DBC_is_void, DBC_rest_arg_num)
#   define DBC_is_not_spec BOOST_PP_NOT(DBC_is_spec)

#   define DBC_functor_name BOOST_PP_IF(DBC_is_const, const_functor, functor)
#   define DBC_const_keyword BOOST_PP_EXPR_IF(DBC_is_const, const)
#   define DBC_typename_An_none(z, n, data) BOOST_PP_CAT(typename A, n) \
            BOOST_PP_EXPR_IF(DBC_is_not_spec, = none_)
#   define DBC_none(z, n, data) none_
#   define DBC_An_argn(z, n, data) BOOST_PP_CAT(A, n) BOOST_PP_CAT(arg, n)

namespace dbc {

template<class C, typename S> class separate; // For friendship.

namespace separating {

/**
 * A functor is an object behaving like a function with specified return type R
 * and argument types A0, A1, etc.
 * It provides the `R operator(A0, A1, ...)' operation to call the function.
 * Only this operation is public so users cannot copy this object and they have
 * to use it in place via a function call (therefore constructors and other
 * operations are made accessible to selected classes via friendship only).
 * @tparam D Object type -- it must be a type derived from C or C itself.
 * @tparam S Separator class type.
 * @tparam R Member function return type.
 * @tparam C Class type of which the function is member of.
 * @tparam A0, A1, ... Member function argument types.
 */
template<class D, class S
        BOOST_PP_COMMA_IF(DBC_is_not_void)
        BOOST_PP_EXPR_IF(DBC_is_not_void, typename R)
        , class C
        // , typename A0 = none_, ...
        BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_typename_An_none, ~)
        >
class DBC_functor_name // functor or const_functor
        // <D, S
        BOOST_PP_EXPR_IF(DBC_is_spec, <D)
        BOOST_PP_COMMA_IF(DBC_is_spec)
        BOOST_PP_EXPR_IF(DBC_is_spec, S)
        // , void -or- , R
        BOOST_PP_COMMA_IF(DBC_is_spec)
        BOOST_PP_IF(DBC_is_void,
                void, BOOST_PP_EXPR_IF(DBC_rest_arg_num, R))
        // ,C
        BOOST_PP_COMMA_IF(DBC_is_spec)
        BOOST_PP_EXPR_IF(DBC_is_spec, C)
        // , A0, ...
        BOOST_PP_COMMA_IF(BOOST_PP_AND(DBC_is_spec, DBC_arg_num))
        BOOST_PP_IF(DBC_is_spec, BOOST_PP_ENUM_PARAMS,
                BOOST_PP_TUPLE_EAT(2))(DBC_arg_num, A)
        // , none_, ...
        BOOST_PP_ENUM_TRAILING(DBC_rest_arg_num, DBC_none, ~)
        BOOST_PP_EXPR_IF(DBC_is_spec, >) {
    friend class separate<D, S>; // Only `R (A0, A1, ...)' public.
    BOOST_PP_EXPR_IF(DBC_is_void, typedef void R;)

public:
    R operator()( BOOST_PP_ENUM(DBC_arg_num, DBC_An_argn, ~) )
            DBC_const_keyword {
        boost::function0<R> f = boost::bind(mem_fun_, obj_
                BOOST_PP_ENUM_TRAILING_PARAMS(DBC_arg_num, arg) );
        BOOST_PP_IF(DBC_is_not_void,
            // Here, SYNC always true because is_query<non-void, ...> is true.
            return separator_->sync(f);
        , /* else (void, can be either sync of async) */
            if (SYNC) { separator_->sync(f); }
            else { separator_->async(f); }
        ) /* endif */
    }

private:
    /** Query fun (not returning value and with no output arg) exec sync. */
    static const bool SYNC = is_query<R, boost::mpl::vector<
            BOOST_PP_ENUM_PARAMS(DBC_arg_num, A) > >::value;

    typedef R (C::* mem_fun_type)(BOOST_PP_ENUM_PARAMS(DBC_arg_num, A) )
            DBC_const_keyword; // Tralining 'const' must appear here.

    DBC_functor_name(
            DBC_const_keyword boost::shared_ptr<D>& obj,
            DBC_const_keyword boost::shared_ptr<S>& separator,
            mem_fun_type mem_fun):
            obj_(obj), separator_(separator), mem_fun_(mem_fun) {}
    
    /** Copy constructor required to return this object from functions. */
    DBC_functor_name(const DBC_functor_name& o):
            obj_(o.obj_), separator_(o.separator_), mem_fun_(o.mem_fun_) {}
    
    DBC_functor_name& operator=(const DBC_functor_name&); // No copy operator=.

    DBC_const_keyword boost::shared_ptr<D> obj_;
    DBC_const_keyword boost::shared_ptr<S> separator_;
    mem_fun_type mem_fun_;
};

#undef DBC_rest_arg_num
#undef DBC_arg_num
#undef DBC_is_void
#undef DBC_is_not_void
#undef DBC_is_const
#undef DBC_is_not_const
#undef DBC_is_spec
#undef DBC_is_not_spec
#undef DBC_functor_name
#undef DBC_const_keyword
#undef DBC_typename_An_none
#undef DBC_none
#undef DBC_An_argn

} // namespace separating
} // namespace dbc

#else // Error, should never happen.
#   error "Preprocessor iteration out-of-range (internal library error)"

#endif // BOOST_PP_ITERATING

