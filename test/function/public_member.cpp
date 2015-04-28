
#include "../aux_/oteststream.hpp"
#include <boost/contract/public_member.hpp>
#include <boost/contract/introspect.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test public member contracts for classes with and without bases, with and
// without virtual bodies.

boost::contract::aux::test::oteststream out;

// Test inheritance level 0 (no bases).
template<typename T>
struct e {
    void invariant() const {
        out << "e::inv" << std::endl;
    }
    
    static void static_invariant() {
        out << "e::static_inv" << std::endl;
    }

    virtual ~e() {}

    // Test contract allows (but does not require) extra introspection,
    // function pointer, etc. parameter because class has no bases.
    void f(T& x, boost::contract::virtual_body v = 0) {
        auto c = boost::contract::public_member<introspect_f>(v, this, &e::f, x)
            .precondition([&]() {
                out << "e::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(false); // To check subcontracted pre.
            })
            .postcondition([&]() {
                out << "e::f::post" << std::endl;
            })
        ;
        f_body(x);
    }
    virtual void f_body(T& x) = 0;
    BOOST_CONTRACT_INTROSPECT(f)
};

// Test inheritance level 0 (no bases).
template<typename T>
struct d {
    void invariant() const {
        out << "d::inv" << std::endl;
    }
    
    static void static_invariant() {
        out << "d::static_inv" << std::endl;
    }

    virtual ~d() {}

    // Test contract does not require (but allows) extra introspection,
    // function pointer, etc. parameter because class has no bases.
    void f(T& x, boost::contract::virtual_body v = 0) {
        auto c = boost::contract::public_member(v, this)
            .precondition([&]() {
                out << "d::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(false); // To check subcontracted pre.
            })
            .postcondition([&]() {
                out << "d::f::post" << std::endl;
            })
        ;
        f_body(x);
    }
    virtual void f_body(T& x) = 0;
};

// Test inheritance level 1 and multiple inheritance (both contracted bases).
template<typename T, typename S>
struct c
    #define BASES public e<T>, public d<T>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "c::inv" << std::endl;
    }
    
    static void static_invariant() {
        out << "c::static_inv" << std::endl;
    }
    
    virtual ~c() {}
    
    // Test virtual overrides virtual function.
    void f(T& x, boost::contract::virtual_body v = 0) {
        auto c = boost::contract::public_member<introspect_f>(v, this, &c::f, x)
            .precondition([&]() {
                out << "c::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(false); // To check subcontracted pre.
            })
            .postcondition([&]() {
                out << "c::f::post" << std::endl;
            })
        ;
        f_body(x);
    }
    virtual void f_body(T& x) {}
    BOOST_CONTRACT_INTROSPECT(f)

    // Test non-contracted virtual function in contracted base.
    virtual void k() = 0;
};

// Test a non-contracted base.
template<typename S>
struct b {
    virtual ~b() {}
    virtual void g() = 0;
    virtual void h() {}
};
    
// Test inheritance level 2 and multiple inheritance (one contracted base,
// and one not).
template<typename T, typename S = unsigned int>
struct a
    #define BASES public c<T, S>, public b<S>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "a::inv" << std::endl;
    }

    static void static_invariant() {
        out << "a::static_inv" << std::endl;
    }

    virtual ~a() {}
    
    // Test non-virtual overrides virtual function.
    void f(T& x) {
        auto c = boost::contract::public_member<introspect_f>(
                this, &a::f, x)
            .precondition([&]() {
                out << "a::f::pre" << std::endl;
            })
            .postcondition([&]() {
                out << "a::f::post" << std::endl;
            }) 
        ;
        f_body(x);
    }
    void f_body(T& x) { out << "a::f::body" << std::endl; }
    BOOST_CONTRACT_INTROSPECT(f)

    void k() {}

private:
    void g() {}
};

int main() {
    std::ostringstream ok;

    a<int> aa;
    int x = 123;
    
    out.str("");
    aa.f(x);
    ok.str("");
    ok
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl

        << "e::f::pre" << std::endl
        << "d::f::pre" << std::endl
        << "c::f::pre" << std::endl
        << "a::f::pre" << std::endl
        
        << "a::f::body" << std::endl
        
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "e::f::post" << std::endl
        << "d::f::post" << std::endl
        << "c::f::post" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    return boost::report_errors();
}

