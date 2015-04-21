
#ifndef BOOST_CONTRACT_AUX_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_AUX_DESTRUCTOR_HPP_

#include <boost/contract/aux_/basic_function.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

template<class Class>
class destructor : public boost::contract::aux::basic_function<Class> {
public:
    explicit destructor(Class* const obj) :
            boost::contract::aux::basic_function<Class>(obj) {
        BOOST_CONTRACT_AUX_DEBUG(obj);
        entry();
    }

    ~destructor() { exit(); }

private:
    // Obj still exists (before dtor body) so check static and non-static inv
    // (subcontracting implemented automatically via C++ object destruction
    // mechanism, so no calls to check_subcontracted_... in this case).
    void entry() { this->check_inv(); }

    // Dtor cannot have pre because it has no parameters.
    void pre_available() { BOOST_CONTRACT_AUX_DEBUG(false); }
    
    // Ctor post always checked after body, at exit (see below).
    // NOTE: Even if there is no obj after dtor body, this library allows for
    // dtor post (e.g., to check static members for an instance counter class).
    void post_available() {}
    
    // If dtor body threw, obj still exists so check subcontracted static and
    // non-static inv (but no post because of throw), otherwise obj destructed
    // so check static static inv and post (subcontracting implemented
    // automatically via C++ object destruction mechanism, so no calls to
    // check_subcontracted_... in this case).
    // NOTE: In theory C++ destructors should not throw, but the language allows
    // for that so this library must handle such a case.
    void exit() {
        bool const body_threw = std::uncaught_exception();
        this->check_inv(/* static_inv_only = */ !body_threw);
        if(!body_threw) this->check_post();
    }
};

} } } // namespace

#endif // #include guard

