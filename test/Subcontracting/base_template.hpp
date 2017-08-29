/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef BASE_TEMPLATE_HPP_
#define BASE_TEMPLATE_HPP_

#include <dbc.hpp>

template<typename T>
class base DBC_INHERIT_OBJECT(base<T>) {
public:
    virtual T f(const T& x) const
#ifdef DBC
    {
        return DBC_CONTRACT( (f)(x) (const) )().call(*this, &base::DBC_BODY(f),
                x, "f");
    }
protected:
    class DBC_CONTRACT( (f)(x) (const) ):
            public dbc::fun<T, const T&>::template mem<const base>::this_type {
        void require(const base& self, const T& x) {
            DBC_ASSERT(true, "base precondition");
        }
        void ensure(const dbc::post<base>& self, const dbc::post<T>& x, 
                const T& result) {
            DBC_ASSERT(true, "base postcondition");
            // Test for required().
            DBC_ASSERT(this->required(), "base preconditions passed"); 
        }
    };
    virtual T DBC_BODY(f)(const T& x) const
#endif
        { return x; }
public:

    virtual T f_m(const T& x) const
    DBC_MEM_FUN( (public) (virtual) (T) (template)(base) 
            (f_m)( (const T&)(x) ) (const), {
        DBC_ASSERT(true, "macro base precondition");
    }, {
        DBC_ASSERT(true, "macro base postcondition");
        // Test for required().
        DBC_ASSERT(this->required(), "base preconditions passed");
    }, {
        return x;
    })

private:
    DBC_INVARIANT(base, {
        DBC_ASSERT(true, "base invariant");
    })
};

#endif // BASE_TEMPLATE_HPP_

