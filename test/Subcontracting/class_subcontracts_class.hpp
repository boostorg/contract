/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef CLASS_SUBCONTRACTS_CLASS_HPP_
#define CLASS_SUBCONTRACTS_CLASS_HPP_

#include "base_class.hpp"
#include <dbc.hpp>

class derived: public base DBC_MULTI_INHERIT_OBJECT(derived) {
public:
    int f(const int& x) const
#ifdef DBC
    { return dbc_f_x()(*this, &derived::DBC_BODY(f), x, "f"); }
protected:
    class dbc_f_x: public dbc::fun<int, const int&>::
            mem<const derived, base::dbc_f_x> {
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
    { return -x; }
public:

    int f_m(const int& x) const
    DBC_MEM_FUN( (public) (int) (derived)DBC_BASE(base)
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

#endif // CLASS_SUBCONTRACTS_CLASS_HPP_

