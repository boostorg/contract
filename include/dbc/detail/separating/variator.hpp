/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under Eiffel for C++ Software License.
 */

#if !BOOST_PP_IS_ITERATING
#   ifndef DBC_SEPARATING_VARIATOR_HPP_ // Include guard.
#       define DBC_SEPARATING_VARIATOR_HPP_

#       include "../../config.hpp"
#       include <boost/preprocessor.hpp>

// Iterate over const/non-const.
#       define BOOST_PP_ITERATION_PARAMS_1 (3, (0, 1, \
                DBC_CONFIG_VARIATOR_HPP_FILE_PATH))
#       include BOOST_PP_ITERATE()
#   endif // DBC_SEPARATING_VARIATOR_HPP_

// Code for a given cosnt or non-const.
#elif BOOST_PP_ITERATION_DEPTH() == 1

#   define DBC_is_const BOOST_PP_FRAME_ITERATION(1)
#   define DBC_is_not_const BOOST_PP_NOT(DBC_is_const)

#   define DBC_variator_name \
            BOOST_PP_IF(DBC_is_const, const_variator, variator)
#   define DBC_const_keyword BOOST_PP_EXPR_IF(DBC_is_const, const)

namespace dbc {

template<class C, typename S> class separate; // For friendship.

namespace separating {

/**
 * A variabor is an object behaving like a variable of the specified type V.
 * It provides the `void opearor=(const V&)' and `opeator V()' operation to
 * set and get the variable's value. Only these two operations are public so
 * users cannot copy this object and they have to use it in place via either a
 * set or a get (therefore constructors and other operations are made
 * accessible to selected classes via friendship only).
 * To resolve the ambiguities that can generate from the implicit type
 * conversion `operator V()' use one of the following forms (in order of
 * preference): (1) "var->*&C::name" works if there is no ambiguity; (2)
 * "V(var->*&C::name)" or "V v = var->*&C::name;" force evaluation of ->*
 * expression as of type V so invoking the `operator V()' via V copy
 * constructor (most compilers will optimize away the extra copy constructor
 * call); (3) "var->*&C::name).operator V()" directly invokes the type
 * conversion operator.
 * @note The name follows from the similar "functor" object.
 * @tparam D Object type -- it must be a type derived from C or C itself.
 * @tparam S Separatator.
 * @tparam V Member variable type. It must have a copy constructor.
 * @tparam C Class type of which the variable is member of.
 */
template<class D, class S, typename V, class C>
class DBC_variator_name { // variator or const_variator class
    friend class separate<D, S>; // Only operators `=' anv `V()' public.
public:
    /**
     * Asynchronously write variable value.
     * Usual C++ operator= return a reference to the copied object. However,
     * this operator must return void because it is executed asynchronously.
     */
BOOST_PP_EXPR_IF(DBC_is_not_const, // Not for const_variator.
    void operator=(V value) {
        boost::function0<void> f = setter(obj_, mem_var_, value);
        separator_->async(f);
    }
) // DBC_is_not_const
    
    /**
     * Synchronously read and returns variable value.
     * Use ".V()" explicit syntax to resolve ambiguities.
     */
    operator V() const {
        boost::function0<V> f = getter(obj_, mem_var_);
        return separator_->sync(f);
    }

private:
    typedef DBC_const_keyword V C::* mem_var_type;
    
    class setter { // Must be copyable.
    public:
        setter(boost::shared_ptr<D>& obj, mem_var_type mem_var, V value):
                obj_(obj), mem_var_(mem_var), value_(value) {}
        void operator()() { ((*obj_).*mem_var_) = value_; }
    private:
        boost::shared_ptr<D> obj_;
        mem_var_type mem_var_;
        V value_; // Requires V copy constr.
    };
    
    class getter { // Must be copyable.
    public:
        getter(const boost::shared_ptr<D>& obj, const mem_var_type mem_var):
                obj_(obj), mem_var_(mem_var) {}
        V operator()() const { return (*obj_).*mem_var_; }
    private:
        const boost::shared_ptr<D> obj_;
        const mem_var_type mem_var_;
    };

    DBC_variator_name(
            DBC_const_keyword boost::shared_ptr<D>& obj,
            DBC_const_keyword boost::shared_ptr<S>& separator,
            mem_var_type mem_var):
            obj_(obj), separator_(separator), mem_var_(mem_var) {}

    /** Copy constructor required to return this object from functions. */
    DBC_variator_name(const DBC_variator_name& o):
            obj_(o.obj_), separator_(o.separator_), mem_var_(o.mem_var_) {}
    
    DBC_variator_name& operator=(const DBC_variator_name&); // No copy op=.

    DBC_const_keyword boost::shared_ptr<D> obj_;
    DBC_const_keyword boost::shared_ptr<S> separator_;
    mem_var_type mem_var_;
};

#undef DBC_is_const
#undef DBC_is_not_const
#undef DBC_variator_name
#undef DBC_const_keyword

} // namespace separating
} // namespace dbc

#else // Error, should never happen.
#   error "Preprocessor iteration out-of-range (internal library error)"

#endif // BOOST_PP_ITERATING

