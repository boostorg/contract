/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "base_template.hpp"
#include <dbc.hpp>
#include <iostream>

// Derive once.
class derived1: public base<int> DBC_MULTI_INHERIT_OBJECT(derived1) {
public:
    // Code subcontracts from macro API.
    virtual int f(const int& x) const
    DBC_MEM_FUN( (public) (int) (derived1)DBC_BASE(base<int>)
            (f)( (const int&)(x) ) (const), {
        DBC_ASSERT(false, "macro derived1 precondition -- but base's pass");
    }, {
        DBC_ASSERT(true, "macro derived1 postcondition");
        DBC_ASSERT(!required(), "derived1 preconditions failed"); // Test req.
    }, {
        return -x;
    })

    // Macro subcontracts from code API.
    virtual int f_m(const int& x) const
#ifdef DBC
    {
        return DBC_CONTRACT( (f_m)(x) (const) )().call(*this,
                &derived1::DBC_BODY(f_m), x, "f_m");
    }
protected:
    class DBC_CONTRACT( (f_m)(x) (const) ): public dbc::fun<int, const int&>::
            mem<const derived1, base<int>::DBC_CONTRACT( (f_m)(x) (const) )> {
        void require(const derived1& self, const int& x) {
            DBC_ASSERT(false, "derived1 precondition -- but base's pass");
        }
        void ensure(const dbc::post<derived1>& self, const dbc::post<int>& x, 
                const int& result) {
            DBC_ASSERT(true, "derived1 postcondition");
            DBC_ASSERT(!required(), "derived1 preconditions failed");
        }
    };
    virtual int DBC_BODY(f_m)(const int& x) const
#endif
        { return -x; }
public:

private:
    DBC_INVARIANT(derived1, {
        DBC_ASSERT(true, "derived1 invariant");
    })
};

// Derive twice.
class derived2: public derived1 DBC_MULTI_INHERIT_OBJECT(derived2) {
public:
    // Macro subcontracts from code API.
    virtual int f(const int& x) const
#ifdef DBC
    {
            return DBC_CONTRACT( (f)(x) (const) )().call(*this, 
                    &derived2::DBC_BODY(f), x, "f");
    }
protected:
    class DBC_CONTRACT( (f)(x) (const) ): public dbc::fun<int, const int&>::
            mem<const derived2, derived1::DBC_CONTRACT( (f)(x) (const) )> {
        void require(const derived2& self, const int& x) {
            DBC_ASSERT(false, "derived2 precondition -- but base's pass");
        }
        void ensure(const dbc::post<derived2>& self, const dbc::post<int>& x, 
                const int& result) {
            DBC_ASSERT(true, "derived2 postcondition");
            DBC_ASSERT(!required(), "derived2 preconditions failed");
        }
    };
    virtual int DBC_BODY(f)(const int& x) const
#endif
        { return x * 2; }
public:

    // Code subcontracts from macro API.
    virtual int f_m(const int& x) const
    DBC_MEM_FUN( (public) (int) (derived2)DBC_BASE(derived1)
            (f_m)( (const int&)(x) ) (const), {
            DBC_ASSERT(false, "macro derived2 precondition -- but base's pass");
    }, {
            DBC_ASSERT(true, "macro derived2 postcondition");
            DBC_ASSERT(!required(), "derived2 preconditions failed");
    }, {
        return x * 2;
    })

private:
    DBC_INVARIANT(derived2, {
        DBC_ASSERT(true, "derived2 invariant");
    })
};

int main() {
    base<int> b;
    std::cout << std::endl << b.f(-10) << " " << b.f_m(-10) << std::endl;
    
    derived1 d1;
    std::cout << std::endl << d1.f(-10) << " " << d1.f_m(-10) << std::endl;
    
    derived2 d2;
    std::cout << std::endl << d2.f(-10) << " " << d2.f_m(-10) << std::endl;
}

