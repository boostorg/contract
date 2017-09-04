
#ifndef DBC_POST_HPP_
#define DBC_POST_HPP_

#ifdef DBC

#include "copyable.hpp"
#include "detail/logging.hpp"
#include "detail/type_traits.hpp"

#define DBC_ADD_POST_(typename_keyword, the_type) \
    ::dbc::post<typename_keyword ::dbc::remove_const_ref_< the_type >::type>

#define DBC_ADD_POST_CONST_REF_(typename_keyword, the_type) \
    const DBC_ADD_POST_(typename_keyword, the_type)&

namespace dbc {

/** Primary template, does not assume T is copyable (old unavailable). */
template<typename T>
class post {
public:
    const typename remove_const_ref_<T>::type& now; // A ref (no obj copy).

    explicit post(const typename remove_const_ref_<T>::type& orig): 
            now(orig) {}

    template<typename D>
    explicit post(const D& derived): now(derived.now) {}
};

/** Specialization for copyable T (old is available). */
template<typename T>
class post<copyable<T> > {
public:
    const typename remove_const_ref_<T>::type old; // Not a ref, will copy obj!
    const typename remove_const_ref_<T>::type& now; // A ref (no obj copy).

    explicit post(const typename remove_const_ref_<T>::type& orig): 
            old(orig), now(orig) {
        DBC_LOG_DEBUG_(log << "post<" << typeid(T).name() 
                << ">: copied from original object");
    }

    template<typename D>
    explicit post(const D& derived): old(derived.old), now(derived.now) {
        DBC_LOG_DEBUG_(log << "post< " << typeid(T).name() 
                << ">: copied from derived object of type " 
                << typeid(D).name());
    }
};

} // namespace dbc

#endif // DBC

#endif // DBC_POST_HPP_

