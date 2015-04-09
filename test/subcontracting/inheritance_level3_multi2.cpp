
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

std::ostringstream out;

// Test inheritance level 1 and no multiple inheritance.
template< typename T >
struct e {
    void invariant ( ) const {
        out << "e::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(true);
    }

    // Test contract allows (but does not require) extra introspection,
    // function pointer, etc. parameter because class has no bases.
    void f ( T& x, boost::contract::virtual_body v = 0 ) {
        boost::contract::type contract = boost::contract::function<
                introspect_f>(this, &e::f, x, v)
            .precondition([&] ( ) {
                out << "e::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(false);
            })
            .postcondition([&] ( ) {
                out << "e::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(true);
            })
        ;
        f_body(x);
    }
    virtual void f_body ( T& x ) = 0;

private:
    BOOST_CONTRACT_INTROSPECT(f)
};

// Test inheritance level 1 and no multiple inheritance.
template< typename T >
struct d {
    void invariant ( ) const {
        out << "d::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(true);
    }

    // Test contract does not require (but allows) extra introspection,
    // function pointer, etc. parameter because class has no bases.
    void f ( T& x, boost::contract::virtual_body v = 0 ) {
        boost::contract::type contract = boost::contract::function(this, v)
            .precondition([&] ( ) {
                out << "d::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(false);
            })
            .postcondition([&] ( ) {
                out << "d::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(true);
            })
        ;
        f_body(x);
    }
    virtual void f_body ( T& x ) = 0;
};

// Test inheritance level 2 and multiple inheritance 2 (both contracted bases).
#define BASES e<T>, d<T>
template< typename T, class S >
struct c : BASES {
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) BOOST_CONTRACT_BASES;
#   undef BASES

    void invariant ( ) const {
        out << "c::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(true);
    }

    virtual ~c ( ) {}
    
    // Test virtual overrides virtual function.
    void f ( T& x, boost::contract::virtual_body v = 0 ) {
        boost::contract::type contract = boost::contract::function<
                introspect_f>(this, &c::f, x, v)
            .precondition([&] ( ) {
                out << "c::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(false);
            })
            .postcondition([&] ( ) {
                out << "c::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(true);
            })
        ;
        f_body(x);
    }
    virtual void f_body ( T& x ) {}

    // Test non-contracted virtual function in contracted base.
    virtual void k ( ) = 0;

private:
    BOOST_CONTRACT_INTROSPECT(f)
};

// Test a non-contracted base.
template< class S >
struct b {
    virtual ~b ( ) {}
    virtual void g ( ) = 0;
    virtual void h ( ) {}
};
    
// Test inheritance level 3 and multiple inheritance 2 (one contracted base,
// and one not).
#define BASES public c<T, S>, private b<S>
template< typename T, class S = unsigned int >
struct a : BASES {
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) BOOST_CONTRACT_BASES;
#   undef BASES

    void invariant ( ) const {
        out << "a::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(true);
    }
    
    // Test non-virtual overrides virtual function.
    void f ( T& x ) {
        boost::contract::type contract = boost::contract::function<
                introspect_f>(this, &a::f, x)
            .precondition([&] ( ) {
                out << "a::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(true);
            })
            .postcondition([&] ( ) {
                out << "a::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(true);
            }) 
        ;
        f_body(x);
    }
    void f_body ( T& x ) { out << "a::f::body" << std::endl; }
    
    void k ( ) {}

private:
    void g ( ) {}

    BOOST_CONTRACT_INTROSPECT(f)
};
        
int main ( ) {
    std::ostringstream ok;

    a<int> aa;
    int x = 123;
    
    out << std::endl;
    aa.f(x);
    ok  << std::endl
        << "e::inv" << std::endl
        << "d::inv" << std::endl
        << "c::inv" << std::endl
        << "a::inv" << std::endl
        << "e::f::pre" << std::endl
        << "d::f::pre" << std::endl
        << "c::f::pre" << std::endl
        << "a::f::pre" << std::endl
        << "a::f::body" << std::endl
        << "e::inv" << std::endl
        << "d::inv" << std::endl
        << "c::inv" << std::endl
        << "a::inv" << std::endl
        << "e::f::post" << std::endl
        << "d::f::post" << std::endl
        << "c::f::post" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST_EQ(out.str(), ok.str());

    return boost::report_errors();
}

