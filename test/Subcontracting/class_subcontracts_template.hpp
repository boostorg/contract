/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef CLASS_SUBCONTRACTS_TEMPLATE_HPP_
#define CLASS_SUBCONTRACTS_TEMPLATE_HPP_

#include "base_template.hpp"
#include <dbc.hpp>

class derived: public base<int> DBC_MULTI_INHERIT_OBJECT(derived) {
public:
    int f(const int& x) const
#ifdef DBC
    { return DBC_CONTRACT(f, (x))().call(*this, &derived::DBC_BODY(f), x, 
    "f"); }
protected:
    class DBC_CONTRACT(f, (x)): public dbc::fun<int, const int&>::
            mem<const derived, base<int>::DBC_CONTRACT(f, (x))> {
        void require(const derived& self, const int& x) {
            DBC_ASSERT(false, "derived precondition -- but base's pass");
        }
        void ensure(const dbc::post<derived>& self, const dbc::post<int>& x, 
                const int& result) {
            DBC_ASSERT(true, "derived postcondition");
        }
    };
    int DBC_BODY(f)(const int& x) const
#endif // DBC
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

