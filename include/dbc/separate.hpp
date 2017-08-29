/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under Eiffel for C++ Software License.
 */

#ifndef DBC_SEPARATE_HPP_
#define DBC_SEPARATE_HPP_

#include "separators/boost_thread_separator.hpp"
#include "detail/logging.hpp"
#include "detail/separating/functor.hpp"
#include "detail/separating/variator.hpp"
#include <boost/preprocessor.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <iostream>

/** @note Overloading and optional arguments.
 * Optional arguments are not directly supported via mem ptr and functors.
 * They only work if mem ptr are used without functors (i.e., with the code
 * automatically synthetized by the C++ compiler). However, overloading can be
 * used to obtain the same effect as default arguments (via an overloaded
 * definition of a function but without one re more arguments makes them 
 * optional). Unfortunately, mem ptr and functor (and not the C++ synth code)
 * require the use of huggly stati_cast<> to resolve type selection ambiugities
 * manually when overloading a function. A static_cast<> will result in a
 * compiler error if not matching function declared, other casting will result
 * only in a dangerous runtime segfault in this case, ONLY USE STATIC CASTING!
 * @code
 *  class C {
 *  public:
 *      ...
 *      // This is not supported when using functors with mem ptr.
 *      // std::string opt(const std::string& i = "") { ... }
 *
 *      // Overloading can be used instead but requires static_cast<>.
 *      std::string opt(const std::string& i) { ... }
 *      std::string opt() { return opt(""); } // i defaults to "".
 *  };
 *
 *  ...
 *  dbc::separate<C> s;
 *  // Invokes version with 1 argument.
 *  (s->*static_cast<std::string (C::*)(const std::string&)>(&C::opt))("zzz");
 *  // Invokes version with no arguments.
 *  (s->*static_cast<std::string (C::*)()>(&C::opt))();
 *  // Ivalid static_cast will give compile-time error.
 * @endcode
 */

/** @note Passing an invalid member pointer (0, etc) to operator->* results in
 * unspecified behaviour, likely a segfault -- this just the way that C++
 * member poitners work, it does not have to do with separate<>. However,
 * it is difficult to pass an invalid member pointer as it requires passing for
 * a variable and assigning it to 0 or leaving it unitialized. If no temporary
 * vairable is used to store the member pointer but the address is directly
 * taken from the class type as "&C::member-name" any time the operator->* is
 * invoked then the member pointer will always contain the correct address. */

/** @todo Cannot return ptr/ref (cannot return by "business card").
 * Static assertions should enforce this rule.
 * It cannot be allowed to return prt or ref as this could be used to return
 * ptr or ref to object's state so the sate could be accessed via ptr/ref
 * skipping the sync enforced by separate<>. Specifically, functions cannot
 * return ptr (T*), ref (T&), or they cannot have an argument as ptr to ptr
 * (T**), ref to ptr (T*&). See this example:
 * @code
 *     #include <iostream>
 *     
 *     // Bad is C's internal state can be exposed by ptr or ref.
 *     class C {
 *     public:
 *         int& x_;
 *         
 *         C(int& x): x_(x) {}
 *     
 *         void f(int& x) { x = x_ = 10; } // OK.
 *         
 *         void r(int*& x) { // Bad.
 *             x_ = 10;
 *             x = &x_;
 *         }
 *     
 *         int& g() { return x_; } // Bad.
 *     
 *         void h(int* x) { *x = x_ = 10; } // OK.
 *         // { x_ = 10; x = &x_; } // OK -- only *x is out, x is not.
 *         
 *         void j(int** x) { // Bad.
 *             x_ = 10;
 *             *x = &x_;
 *         }
 *     
 *         int* k() { return &x_; } // Bad.
 *     };
 *     
 *     int main() {
 *         int y = -10;
 *         C c(y);
 *         
 *         int i = -1;
 *         int& x = i;
 *         c.f(x);
 *         std::cout << "f(): " << x << " " << c.x_ << std::endl;
 *         x = -1;
 *         std::cout << "f(): " << x << " " << c.x_ << std::endl;
 *         
 *         int* m = 0;
 *         c.r(m);
 *         *m = -1;
 *         std::cout << "r(): " << *m << " " << c.x_ << std::endl;
 *     
 *         int& z = c.g();
 *         z = -1;
 *         std::cout << "g(): " << z << " " << c.x_ << std::endl;
 *         
 *         int w = -1;
 *         c.h(&w);
 *         std::cout << "h(): " << w << " " << c.x_ << std::endl;
 *         w = -1;
 *         std::cout << "h(): " << w << " " << c.x_ << std::endl;
 *         
 *         int* p = 0;
 *         c.j(&p);
 *         *p = -1;
 *         std::cout << "j(): " << *p << " " << c.x_ << std::endl;
 *         
 *         int* q = c.k();
 *         *q = -1;
 *         std::cout << "k(): " << *q << " " << c.x_ << std::endl;
 *     
 *         return 0;
 *     }
 * @endcode
 */

#define DBC_max_arg_num BOOST_PP_ADD(DBC_CONFIG_MAX_ARGC, 1)
#define DBC_An(z, n, data) BOOST_PP_CAT(A, n)
#define DBC_argn(z, n, data) BOOST_PP_CAT(arg, n)
#define DBC_typename_An(z, n, data) typename DBC_An(z, n, data)
#define DBC_An_argn(z, n, data) \
    DBC_An(z, n, data) DBC_argn(z, n, data)
#define DBC_const_functor_if(is_const) \
        BOOST_PP_IF(is_const, const_functor, functor)
#define DBC_const_if(is_const) BOOST_PP_EXPR_IF(is_const, const)

namespace dbc {

/**
 * Class used to access separate object of specified class type C.
 * This class implements the following Simple Concurrent Object-Oriented
 * Programming (SCOOP) rules:
 * -#   If return value (return not void) and/or output argument (argument is
 *      non-const reference & and/or pointer *) then synchronous access, else
 *      asynchronous access.
 * -#   Only one member variable or function can be accessed at any given time
 *      for an object of class C (i.e., member access is mutually exclusive).
 * -#   Every separate object of class C "separate<C>" is handled by a
 *      separate processor.
 * -#   During the execution of a function, all its separate arguments
 *      separate<C>::arg are locked (the function execution will wait to start
 *      until locks can be acquired for all its separate arguments and it will
 *      release all the locks at the function exit).
 * -#   Locking must be recursive (allowing the same object to obtain the lock
 *      again if it already has it).
 *
 * Provides same constructors as C.
 * All class C public member variables and functions can be accessed from
 * separate<C> via operator->*.
 * @note C++ does not allow overloading of the access operator.* so the access
 *  operator->* was used here. Therefore, accessing members of C via
 *  separate<C> can be seen as if separate<C> was a "pointer" to C and members
 *  were accessed via pointers to member variable and functions. However, only
 *  in this sense separate<C> should be regarded as a "pointer".
 * Separate objects can be copied. The copied object is like a smart pointer
 * to source object, no new separate object is created by the copy. Once all
 * copies to a given separate object are destroyed, the actual separate object
 * is also destroyed.
 *
 * Arguments of separate<C> should be passed using the type separate<C>::arg
 * (without any extra reference & of pointer * qualifier) to allow for proper
 * locking of separate arguments during the function execution.
 * @tparam C Separated object class type.
 * @tparam S Separator class. By default separate object using threading with
 *  support from the Boost.Thread library. As suggested by the SCOOP approach,
 *  different separators could be used in the future to support object
 *  separation via CORBA or similar (e.g., omniorb_corba_separator would
 *  implement separation using CORBA with support from the CORBA OmniORB
 *  library) -- not yet implemented.
 */
template<class C, class S = boost_thread_separator>
class separate { // This is copyable (it's a just a shared ptr).
public:
    /**
     * Separate argument that automatically aquires and release exclusive lock.
     * This type locks the separate object in its constructor and releases the
     * lock in its destructor. Therefore it is a scoped recursive lock on the
     * separate object. To correctly implement the SCOOP rules, this class
     * must only be used to pass separate<> objects argument by value.
     * @remark Do not add any qualifier to this type. To allow for proper
     *  locking of the separate object, separate arguments must be passed
     *  by value and not by reference & or by pointer *.
     * Inherits accessors operator->*() from separate<> so it can be used
     * to access the separated object the same wahy separate<> is used.
     */
    class arg: public separate {
    public:
        arg(separate& sep): separate(sep), lock_(*separator_) {
                DBC_LOG_DEBUG_(log << "Separator " << separator_
                        << ": Locking separate argument " << this);
        }
        
        /** Copy constructor (but not operator=) automatically used by C++
         * during argument passing by-value. */
        arg(const arg& other): separate(other), lock_(*separator_) {
            DBC_LOG_DEBUG_(log << "Separator " << separator_
                    << ": Locking copied separate argument " << this);
        }

        ~arg() {
            DBC_LOG_DEBUG_(log << "Separator " << separator_
                    << ": Unlocking separate argument " << this);
        } // Releases scoped lock_.

        // Inherit binders operator->*() from separate<>.

    private:
        arg& operator=(const arg&); // Only copy constr (no operator=).

        /** @note I could declared private "operator&" and "operator new"
         * attempting to prevent getting an address to pass this type by
         * pointer... but there is no way I can prevent passing by reference,
         * by passing a local variable of type separate<>::arg, etc. Then the
         * correct use of separate<>::arg is just left up to the programmer. */

        typename S::recursive_scoped_lock lock_;
    };

    // Creation //

    explicit separate(): // Requires C to have a default constr.
            obj_(new C()), separator_(new S()) {}

    // template<typename A0, ...>
    // explicit separate(A0, ...);
#define DBC_constr(z, n, data) \
    template< BOOST_PP_ENUM(n, DBC_typename_An, ~) > \
    explicit separate( BOOST_PP_ENUM(n, DBC_An_argn, ~) ): \
            obj_(new C( BOOST_PP_ENUM(n, DBC_argn, ~) )), \
            separator_(new S()) {}
    BOOST_PP_REPEAT_FROM_TO(1, DBC_max_arg_num, DBC_constr, ~)
#undef DBC_constr

    // Implicit Type-Conversion //
    
    /** Require class type C copy constructor. This must be implicit. */
    explicit separate(const C& obj): obj_(new C(obj)), separator_(new S()) {}

    /** Used to convert arg back to separate. This must be implicit. */
    separate(const arg& arg): obj_(arg.obj_), separator_(arg.separator_) {}
    
    // Member Function Access //
    
    /**
     * Meta-code for const/non-const binder to access void/non-void
     * const/non-const member function.
     * @param is_const_seq (v)(f)(m) where:
     *  v is 1 iff this a binder for a non-void function;
     *  f is 1 iff this is a binder for a constat function;
     *  m is 1 iff this is a constant binder.
     *  The binder can be const (m = 1) only for const mem fun (f = 1).
     */
#define DBC_binder(z, n, attrs) \
    template< \
            BOOST_PP_EXPR_IF(BOOST_PP_SEQ_ELEM(0, attrs), typename R) \
            BOOST_PP_COMMA_IF(BOOST_PP_SEQ_ELEM(0, attrs)) \
            class B \
            BOOST_PP_ENUM_TRAILING(n, DBC_typename_An, ~) > \
    separating::DBC_const_functor_if(BOOST_PP_SEQ_ELEM(1, attrs)) \
            < C, S, \
            BOOST_PP_IF(BOOST_PP_SEQ_ELEM(0, attrs), R, void) \
            , B BOOST_PP_ENUM_TRAILING(n, DBC_An, ~) > \
            operator->*( \
            BOOST_PP_IF(BOOST_PP_SEQ_ELEM(0, attrs), R, void) \
            (B::* mem_fun)( BOOST_PP_ENUM(n, DBC_An, ~) ) \
            DBC_const_if(BOOST_PP_SEQ_ELEM(1, attrs))) \
            DBC_const_if(BOOST_PP_SEQ_ELEM(2, attrs)) { \
        /** @todo[LC] Static assert Ai != ptr, ref, ref-to-ptr, ptr-to-ptr */ \
        return separating::DBC_const_functor_if(BOOST_PP_SEQ_ELEM(1, attrs)) \
                < C, S, \
                BOOST_PP_IF(BOOST_PP_SEQ_ELEM(0, attrs), R, void) \
                , B BOOST_PP_ENUM_TRAILING(n, DBC_An, ~) >( \
                obj_, separator_, mem_fun); \
    } 
    
    /** Access void member function. */
    // template<typename A0, ...> functor<void, A0, ...>
    //         operator->*(void (B::* mem_fun)(A0, ...));
    BOOST_PP_REPEAT_FROM_TO(0, DBC_max_arg_num, DBC_binder,
            (0)/* void fun */(0)/* non-const fun */(0)/* non-const mem */)
    
    /** Access void constant member function. */
    // template<typename A0, ...> const_functor<void, A0, ...>
    //         operator->*(void (B::* mem_fun)(A0, ...) const);
    BOOST_PP_REPEAT_FROM_TO(0, DBC_max_arg_num, DBC_binder,
            (0)/* void fun */(1)/* const fun */(0)/* non-const mem */)
    
    /** Access void constant member function via constant binder. */
    // template<typename A0, ...> const_functor<void, A0, ...>
    //         operator->*(void (B::* mem_fun)(A0, ...) const) const;
    BOOST_PP_REPEAT_FROM_TO(0, DBC_max_arg_num, DBC_binder,
            (0)/* void fun */(1)/* non-const fun */(1)/* const mem */)
    
    /** Access non-void member function. */
    // template<typename R, typename A0, ...> functor<R, A0, ...>
    //         operator->*(R (B::* mem_fun)(A0, ...));
    BOOST_PP_REPEAT_FROM_TO(0, DBC_max_arg_num, DBC_binder,
            (1)/* non-void fun */(0)/* non-const fun */(0)/* non-const mem */)
    
    /** Access non-void constant member function. */
    // template<typename R, typename A0, ...> const_functor<R, A0, ...>
    //         operator->*(R (B::* mem_fun)(A0, ...) const);
    BOOST_PP_REPEAT_FROM_TO(0, DBC_max_arg_num, DBC_binder,
            (1)/* non-void fun */(1)/* const fun */(0)/* non-const mem */)
    
    /** Access non-void constant member function via constant binder. */
    // template<typename R, typename A0, ...> const_functor<R, A0, ...>
    //         operator->*(R (B::* mem_fun)(A0, ...) const) const;
    BOOST_PP_REPEAT_FROM_TO(0, DBC_max_arg_num, DBC_binder,
            (1)/* non-void fun */(1)/* non-const fun */(1)/* const mem */)

#undef DBC_binder

    // Member Varaible Access //

    /** Access member variable. */
    template<typename V, class B>
    separating::variator<C, S, V, B> operator->*(V B::* mem_var) {
        return  separating::variator<C, S, V, B>(obj_, separator_, mem_var);
    }
    
    /** Access constant member variable. */
    template<typename V, class B>
    separating::const_variator<C, S, V, B>operator->*(const V B::* mem_var) {
        return separating::const_variator<C, S, V, B>(obj_, separator_,
                mem_var);
    }
    
    /* Access constant member variable via constant binder. */
    template<typename V, class B>
    separating::const_variator<C, S, V, B>operator->*(const V B::* mem_var)
            const {
        return separating::const_variator<C, S, V, B>(obj_, separator_,
                mem_var);
    }

    // I/O //

    /** Output separate<C> is like output C. */
    friend std::ostream& operator<<(std::ostream& s, const separate& o)
        { return s << *(o.obj_); } // C must have operator<<.
    
    /** Input separate<C> is like inputing C. */
    friend std::istream& operator>>(std::istream& s, const separate& o)
        { return s >> *(o.obj_); } // C must have operator>>.

protected:
    boost::shared_ptr<C> obj_;
    boost::shared_ptr<S> separator_;
};

} // namespace dbc

#undef DBC_max_arg_num
#undef DBC_An
#undef DBC_argn
#undef DBC_typename_An
#undef DBC_An_argn
#undef DBC_const_functor_if
#undef DBC_const_if

#endif // DBC_SEPARATE_HPP_

