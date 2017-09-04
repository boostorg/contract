
#ifndef TEMPLATE_SUBCONTRACTS_CLASS_HPP_
#define TEMPLATE_SUBCONTRACTS_CLASS_HPP_

#include "base_class.hpp"
#include <dbc.hpp>

template<typename T>
class derived: public base DBC_TRAILING_OBJECT(derived<T>) {
public:
    T f(const T& x) const
#ifdef DBC
    { return dbc_f_x()(*this, &derived::DBC_BODY(f), x, "f"); }
protected:
    class dbc_f_x: public dbc::fun<T, const T&>::template
            mem<const derived, base::dbc_f_x>::this_type {
        void require(const derived& self, const T& x) {
            DBC_ASSERT(false, "derived precondition -- but base's pass");
        }
        void ensure(const dbc::post<derived>& self, const dbc::post<T>& x, 
                const T& result) {
            DBC_ASSERT(true, "derived postcondition");
        }
    };
    T DBC_BODY(f)(const T& x) const
#endif
    { return -x; }
public:

    T f_m(const T& x) const
    DBC_MEM_FUN( (public) (T) (template)(derived)DBC_BASE(base)
            (f_m)( (const T&)(x) ) (const), {
        DBC_ASSERT(false, "macro derived precondition -- but base's pass ");
    }, {
        DBC_ASSERT(true, "macro derived postcondition");
    }, {
        return -x;
    })

private:
    DBC_INVARIANT(derived, {
        DBC_ASSERT(true, "derived invariant");
    })
};

#endif // TEMPLATE_SUBCONTRACTS_CLASS_HPP_

