
#ifndef BASE_CLASS_HPP_
#define BASE_CLASS_HPP_

#include <dbc.hpp>

class base DBC_INHERIT_OBJECT(base) {
public:
    virtual int f(const int& x) const
#ifdef DBC
    { return dbc_f_x()(*this, &base::DBC_BODY(f), x, "f"); }
protected:
    class dbc_f_x: public dbc::fun<int, const int&>::mem<const base> {
        void require(const base& self, const int& x) {
            DBC_ASSERT(true, "base precondition");
        }
        void ensure(const dbc::post<base>& self, const dbc::post<int>& x, 
                const int& result) {
            DBC_ASSERT(true, "base postcondition");
        }
    };
    virtual int DBC_BODY(f)(const int& x) const
#endif
    { return x; }
public:

    virtual int f_m(const int& x) const
    DBC_MEM_FUN( (public) (virtual) (int) (base) 
            (f_m)( (const int&)(x) ) (const), {
        DBC_ASSERT(true, "macro base precondition");
    }, {
        DBC_ASSERT(true, "macro base postcondition");
    }, {
        return x;
    })

private:
    DBC_INVARIANT(base, {
        DBC_ASSERT(true, "base invariant");
    })
};

#endif // BASE_CLASS_HPP_

