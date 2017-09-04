
#ifndef CLASS_SUBCONTRACTS_TEMPLATE_HPP_
#define CLASS_SUBCONTRACTS_TEMPLATE_HPP_

#include "base_template.hpp"
#include <dbc.hpp>

class derived: public base<int> DBC_TRAILING_OBJECT(derived) {
public:
    int f(const int& x) const
#ifdef DBC
    { return dbc_f_x()(*this, &derived::DBC_BODY(f), x, "f"); }
protected:
    class dbc_f_x: public dbc::fun<int, const int&>::
            mem<const derived, base<int>::dbc_f_x> {
        void require(const derived& self, const int& x) {
            DBC_ASSERT(false, "derived precondition -- but base's pass");
        }
        void ensure(const dbc::post<derived>& self, const dbc::post<int>& x, 
                const int& result) {
            DBC_ASSERT(true, "derived postcondition");
        }
    };
    int DBC_BODY(f)(const int& x) const
#endif
    { 
        // IMPORTANT: When invoking parent's function directly, you must use
        // the DBC_BODY() qualifier. Otherwise, the contract will recursively
        // be checked again and again forever...
        /** @todo[LC] If I use "return base<int>::f(-x);" w/out the DBC_BODY()
         * I get infinite recursion. Understand this issue better. */
        return base<int>::DBC_BODY(f)(-x); 
    }
public:

    int f_m(const int& x) const
    DBC_MEM_FUN( (public) (int) (derived)DBC_BASE(base<int>)
            (f_m)( (const int&)(x) ) (const), {
            DBC_ASSERT(false, "macro derived precondition -- but base's pass");
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

#endif // CLASS_SUBCONTRACTS_TEMPLATE_HPP_

