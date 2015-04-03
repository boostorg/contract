
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

#include <boost/contract/control.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/function.hpp>
#include <boost/function_types/components.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/contract/ext_/function_types.hpp>

#include <iostream>
#include <typeinfo>

namespace boost { namespace contract {

template< class FuncTraits = void, class BasePtrs = boost::mpl::vector<> >
struct function {
    template<
        typename FuncPtr,
        class Class,
        typename Arg0,
        typename Pre,
        typename Post
    >
    function (
        FuncPtr const func,
        Class* const obj,
        Arg0 const& arg0,
        boost::contract::control const ctrl,
        Pre const& pre,
        Post const& post
    ) : ctrl_(ctrl), pre_(pre), post_(post) {
        base_function<FuncPtr, Class, Arg0> base_function(obj, arg0);

        std::cout << std::endl;
        std::cout << "-- inv --" << std::endl;

        boost::mpl::for_each<BasePtrs>(base_function.call(
                boost::contract::control::check_inv_only));
        obj->invariant();
        
        std::cout << std::endl;
        std::cout << "-- pre --" << std::endl;
        
        boost::mpl::for_each<BasePtrs>(base_function.call(
                boost::contract::control::check_pre_only));
        pre_();
        
        std::cout << std::endl;
        
        //(obj->*func)(-123, 0);
    }

private:
    template< typename FuncPtr, class Class, typename Arg0 >
    struct base_function {
        base_function ( Class* const obj, Arg0 const& arg0 )
                : obj_(obj), arg0_(arg0) {}
        
    private:
        typedef typename boost::function_types::result_type<FuncPtr>::type
                result_type;
        typedef typename boost::mpl::pop_front<typename boost::function_types::
                parameter_types<FuncPtr>::type>::type param_types;

        struct caller {
            explicit caller (
                base_function& outer, boost::contract::control const ctrl
            ) : outer_(outer), ctrl_(ctrl) {}

            template< class Base >
            void operator() ( Base* ) {
                call<Base>(
                    boost::mpl::bool_<
                        FuncTraits::has_member_function<
                            Base, result_type, param_types
                        >::value
                    >()
                );
            }

        private:
            template< class Base >
            void call ( boost::mpl::false_ const& has_func ) {}

            template< class Base >
            void call ( boost::mpl::true_ const& has_func ) {
                typedef boost::function_types::components<FuncPtr,
                        boost::mpl::always<Base> > base_func_traits;
                typedef boost::function_types::member_function_pointer<
                        base_func_traits>::type base_func_ptr;

                base_func_ptr base_func = FuncTraits::member_function_ptr<
                        Base, base_func_ptr>();
                Base* const base = outer_.obj_;
                
                try {
                    (base->*base_func)(outer_.arg0_, ctrl_);
                } catch(boost::contract::aux::no_error const&) {
                } catch(...) {
                    throw;
                }
            }

            base_function outer_;
            boost::contract::control ctrl_;
        };

    public:
        caller call ( boost::contract::control const ctrl ) {
            return caller(*this, ctrl);
        }

    private:
        Class* const obj_;
        Arg0 const& arg0_;
    };

    boost::contract::control ctrl_;
    boost::function<void ( )> pre_;
    boost::function<void ( )> post_;
};

template< >
struct function< void, boost::mpl::vector<> > {
    template< class Class, typename Pre, typename Post >
    function (
        Class* const obj,
        boost::contract::control const ctrl,
        Pre const& pre, Post const& post
    ) : ctrl_(ctrl), post_(post) {
        if(ctrl_.action == boost::contract::control::check_inv_only) {
            obj->invariant();
            throw boost::contract::aux::no_error();
        } else if(ctrl_.action == boost::contract::control::check_pre_only) {
            pre();
        }
    }

private:
    boost::contract::control ctrl_;
    boost::function<void ( )> post_;
};

} } // namespace

#endif // #include guard

