
#ifndef BOOST_CONTRACT_AUX_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_AUX_CONSTRUCTOR_HPP_

#include <boost/contract/aux_/basic_function.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

template<class Class>
class constructor : public boost::contract::aux::basic_function<Class> {
public:
    explicit constructor(Class* const obj) :
            boost::contract::aux::basic_function<Class>(obj) {
        BOOST_CONTRACT_AUX_DEBUG(obj);
        entry();
    }

    ~constructor() { exit(); }

private:
    // No object before ctor body so only static inv at entry.
    void entry() { this->check_inv(/* static_inv_only = */ true); }

    // Ctor pre checked by constructor_precondition at start of init list.
    void pre_available() { BOOST_CONTRACT_AUX_DEBUG(false); }
    
    // Ctor post always checked later, at exit (see below).
    void post_available() {}

    // If ctor body threw, only check static inv, otherwise obj constructed so
    // check also non-static inv and post (subcontracting implemented
    // automatically via C++ object constructor mechanism, so no calls to
    // check_subcontracted_... in this case).
    void exit() {
        bool const body_threw = std::uncaught_exception();
        this->check_inv(/* static_inv_only = */ body_threw);
        if(!body_threw) this->check_post();
    }

};

} } } // namespace

#endif // #include guard

