
#ifndef BOOST_CONTRACT_AUX_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_MEMBER_HPP_

#include <boost/contract/aux_/call.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

template<class C>
class public_member : public boost::contract::aux::check_pre_post_inv<C> {
public:
    explicit public_member(C const* obj) :
        boost::contract::aux::check_pre_post_inv<C>(
                boost::contract::from_public_member, obj)
    { init(); }

    explicit public_member(boost::shared_ptr<boost::contract::aux::call> call,
            C const* obj) :
        boost::contract::aux::check_pre_post_inv<C>(
                boost::contract::from_public_member, call, obj)
    { init(); }

private:
    void init() {
        this->check_entry_inv();
        if(this->call()) this->check_exit_inv(); // Throw (so not in dtor).
    }

    void pre_available() /* override */ { this->check_pre(); }

    void post_available() /* override */ {
        if(this->call()) this->check_post(); // Throw (so not in dtor).
    }
    
public:
    ~public_member() {
        if(!this->call() && !std::uncaught_exception()) { // Body didn't throw.
            this->check_exit_inv();
            this->check_post();
        }
    }
};

} } } // namespace

#endif // #include guard

