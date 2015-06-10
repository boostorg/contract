
#ifndef BASES_HPP_
#define BASES_HPP_

// Test public member function subcontracting (also with old and return values).

#include "../aux_/oteststream.hpp"
#include "../aux_/cpcnt.hpp"
#include <boost/contract/public_function.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/override.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

boost::contract::aux::test::oteststream out;

struct s_tag;
typedef boost::contract::aux::test::cpcnt<s_tag, std::string> s_type;

struct result_type {
    std::string value;
    explicit result_type(std::string const& s) : value(s) {}

private: // Test non-copyable and non-default-constructible result.
    result_type();
    result_type(result_type const&);
    result_type& operator=(result_type const&);
};

// Test base without additional bases and pure virtual.
template<char Id>
struct t {
    void invariant() const {
        out << Id << "::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(z.value != "");
    }
    static void static_invariant() { out << Id << "::static_inv" << std::endl; }

    struct z_tag;
    typedef boost::contract::aux::test::cpcnt<z_tag, std::string> z_type;
    z_type z;

    t() { z.value.push_back(Id); }

    virtual result_type& f(s_type& s, boost::contract::virtual_* v = 0) = 0;
};

template<char Id>
result_type& t<Id>::f(s_type& s, boost::contract::virtual_* v) {
    std::ostringstream r; r << "none-" << Id;
    static result_type result(r.str());
    boost::shared_ptr<z_type const> old_z =
            BOOST_CONTRACT_OLDOF(v, z_type::eval(z));
    boost::shared_ptr<s_type const> old_s =
            BOOST_CONTRACT_OLDOF(v, s_type::eval(s));
    boost::contract::guard c = boost::contract::public_function(v, result, this)
        .precondition([&] {
            out << Id << "::f::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(s.value[0] == Id);
        })
        .postcondition([&] (result_type const& result) {
            out << Id << "::f::post" << std::endl;
            BOOST_CONTRACT_ASSERT(z.value == old_z->value + old_s->value);
            BOOST_CONTRACT_ASSERT(s.value.find(old_z->value) !=
                    std::string::npos);
            BOOST_CONTRACT_ASSERT(result.value == old_s->value);
        })
    ;
    out << "t<" << Id << ">::body" << std::endl;
    return result;
}

// Test base with other bases, multiple inheritance, and no subcontracting from
// protected and private bases (even if fully contracted).
struct c
    #define BASES public t<'d'>, protected t<'p'>, private t<'q'>, public t<'e'>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "c::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(y.value != "");
    }
    static void static_invariant() { out << "c::static_inv" << std::endl; }

    struct y_tag;
    typedef boost::contract::aux::test::cpcnt<y_tag, std::string> y_type;
    y_type y;

    c() { y.value = "c"; }

    virtual result_type& f(s_type& s, boost::contract::virtual_* v = 0)
            /* override */ {
        static result_type result("none-c");
        boost::shared_ptr<y_type const> old_y =
                BOOST_CONTRACT_OLDOF(v, y_type::eval(y));
        boost::shared_ptr<s_type const> old_s =
                BOOST_CONTRACT_OLDOF(v, s_type::eval(s));
        boost::contract::guard c = boost::contract::public_function<
                override_f>(v, result, &c::f, this, s)
            .precondition([&] {
                out << "c::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(s.value == "C");
            })
            .postcondition([&] (result_type const& result) {
                out << "c::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(y.value == old_y->value + old_s->value);
                BOOST_CONTRACT_ASSERT(s.value.find(old_y->value) !=
                        std::string::npos);
                BOOST_CONTRACT_ASSERT(result.value == old_s->value);
            })
        ;

        out << "c::f::body" << std::endl;
        std::string save_s = s.value;

        std::string save = y.value;
        y.value += save_s;
        s.value = save;

        save = t<'d'>::z.value;
        t<'d'>::z.value += save_s;
        s.value += save;

        save = t<'e'>::z.value;
        t<'e'>::z.value += save_s;
        s.value += save;

        result.value = save_s;
        return result;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

// Test no subcontracting from not (fully) contracted base.
struct b {
    void invariant() const { out << "b::inv" << std::endl; }
    static void static_invariant() { out << "b::static_inv" << std::endl; }

    virtual ~b() {}

    virtual result_type& f(s_type& s) { // No contract.
        static result_type result("none-b");
        out << "b::f::body" << std::endl;
        result.value = s.value;
        return result;
    }
};

// Test public function with both non-contracted and contracted bases.
struct a
    #define BASES public b, public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "a::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(x.value != "");
    }
    static void static_invariant() { out << "a::static_inv" << std::endl; }

    struct x_tag;
    typedef boost::contract::aux::test::cpcnt<x_tag, std::string> x_type;
    x_type x;

    a() { x.value = "a"; }

    // Must use virtual_ even if no longer decl virtual for correct overloading.
    result_type& f(s_type& s, boost::contract::virtual_* v = 0)
            /* override */ {
        static result_type result("none-a");
        boost::shared_ptr<x_type const> old_x =
                BOOST_CONTRACT_OLDOF(v, x_type::eval(x));
        boost::shared_ptr<s_type const> old_s =
                BOOST_CONTRACT_OLDOF(v, s_type::eval(s));
        boost::contract::guard c = boost::contract::public_function<
                override_f>(v, result, &a::f, this, s)
            .precondition([&] {
                out << "a::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(s.value == "A");
            })
            .postcondition([&] (result_type const& result) {
                out << "a::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x.value == old_x->value + old_s->value);
                BOOST_CONTRACT_ASSERT(s.value.find(old_x->value) !=
                        std::string::npos);
                BOOST_CONTRACT_ASSERT(result.value == old_s->value);
            })
        ;

        out << "a::f::body" << std::endl;
        std::string save_s = s.value;

        std::string save = x.value;
        x.value += save_s;
        s.value = save;

        save = y.value;
        y.value += save_s;
        s.value += save;

        save = t<'d'>::z.value;
        t<'d'>::z.value += save_s;
        s.value += save;

        save = t<'e'>::z.value;
        t<'e'>::z.value += save_s;
        s.value += save;

        result.value = save_s;
        return result;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};
    
#endif // #include guard

