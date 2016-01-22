
#ifndef BOOST_CONTRACT_AUX_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_FUNCTION_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/condition/check_subcontracted_pre_post_inv.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/tvariadic.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/config.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

template<
    class O, typename R, typename F, class C
    BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_CONFIG_MAX_ARGS)
    BOOST_CONTRACT_AUX_TVARIADIC_TPARAMS_Z(1, BOOST_CONTRACT_CONFIG_MAX_ARGS,
            Args)
>
class public_function : // Non-copyable base.
    public check_subcontracted_pre_post_inv<
        O, R, F, C
        BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_CONFIG_MAX_ARGS)
        BOOST_CONTRACT_AUX_TVARIADIC_ARGS_Z(1, BOOST_CONTRACT_CONFIG_MAX_ARGS,
                Args)
    >
{
public:
    explicit public_function(
        boost::contract::virtual_* v, C* obj, R& r
        BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_CONFIG_MAX_ARGS)
        BOOST_CONTRACT_AUX_TVARIADIC_FPARAMS_Z(1,
                BOOST_CONTRACT_CONFIG_MAX_ARGS, Args, &, args)
    ) :
        check_subcontracted_pre_post_inv<
            O, R, F, C
            BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_CONFIG_MAX_ARGS)
            BOOST_CONTRACT_AUX_TVARIADIC_ARGS_Z(1,
                    BOOST_CONTRACT_CONFIG_MAX_ARGS, Args)
        >(
            boost::contract::from_function, v, obj, r
            BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_CONFIG_MAX_ARGS)
            BOOST_CONTRACT_AUX_TVARIADIC_ARGS_Z(1,
                    BOOST_CONTRACT_CONFIG_MAX_ARGS, args)
        )
    {}

private:
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        void init() /* override */ {
            #if BOOST_CONTRACT_POSTCONDITIONS
                this->init_subcontracted_old();
            #endif
            if(!this->base_call()) {
                #if     BOOST_CONTRACT_PRECONDITIONS || \
                        BOOST_CONTRACT_POSTCONDITIONS || \
                        BOOST_CONTRACT_INVARIANTS
                    if(check_guard::checking()) return;
                    {
                        check_guard checking;
                        #if BOOST_CONTRACT_ENTRY_INVARIANTS
                            this->check_subcontracted_entry_inv();
                        #endif
                        #if BOOST_CONTRACT_PRECONDITIONS
                            this->check_subcontracted_pre();
                        #endif
                    }
                    #if BOOST_CONTRACT_POSTCONDITIONS
                        this->copy_subcontracted_old();
                    #endif
                #endif
            } else {
                #if     BOOST_CONTRACT_PRECONDITIONS || \
                        BOOST_CONTRACT_POSTCONDITIONS || \
                        BOOST_CONTRACT_INVARIANTS
                    #if BOOST_CONTRACT_ENTRY_INVARIANTS
                        this->check_subcontracted_entry_inv();
                    #endif
                    #if BOOST_CONTRACT_PRECONDITIONS
                        this->check_subcontracted_pre();
                    #endif
                    #if BOOST_CONTRACT_POSTCONDITIONS
                        this->copy_subcontracted_old();
                    #endif
                    #if BOOST_CONTRACT_EXIT_INVARIANTS
                        this->check_subcontracted_exit_inv();
                    #endif
                    #if BOOST_CONTRACT_POSTCONDITIONS
                        if(!std::uncaught_exception()) {
                            this->check_subcontracted_post();
                        }
                    #endif
                #endif
            }
        }
    #endif

public:
    #if BOOST_CONTRACT_EXIT_INVARIANTS || BOOST_CONTRACT_POSTCONDITIONS
        ~public_function() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(!this->base_call()) {
                if(check_guard::checking()) return;
                check_guard checking;

                #if BOOST_CONTRACT_EXIT_INVARIANTS
                    this->check_subcontracted_exit_inv();
                #endif
                #if BOOST_CONTRACT_POSTCONDITIONS
                    if(!std::uncaught_exception()) {
                        this->check_subcontracted_post();
                    }
                #endif
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard

