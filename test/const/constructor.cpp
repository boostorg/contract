
#include <boost/contract/constructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/contract/bind.hpp>
#include <boost/bind.hpp>

struct b
    #define BASES private boost::contract::constructor_precondition<b>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const { std::clog << "b::inv" << std::endl; }
    static void static_invariant() {
        std::clog << "b::static_inv" << std::endl;
    }

    int y;

    static void b_precondition(int const j) {
        std::clog << "b::ctor::pre" << std::endl; 
        BOOST_CONTRACT_ASSERT(j > 0);
    }
    void b_contract(int const j, boost::contract::call c) const {
        boost::shared_ptr<int const> old_j = BOOST_CONTRACT_OLDOF(c, j);
        boost::contract::constructor(c, this)
            .postcondition([&] {
                std::clog << "b::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(y == *old_j);
                BOOST_CONTRACT_ASSERT(j == -2);
            })
        ;
    }
    explicit b(int& j) :
        boost::contract::constructor_precondition<b>(
                boost::bind(&b::b_precondition, j))
    {
        boost::contract::scoped contract = boost::contract::bind(
                &b::b_contract, this, j);
        std::clog << "b::ctor::body" << std::endl;
        y = j;
        j = -2;
    }
};

struct a
    #define BASES private boost::contract::constructor_precondition<a>, public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const { std::clog << "a::inv" << std::endl; }
    static void static_invariant() {
        std::clog << "a::static_inv" << std::endl;
    }

    int x;

    static void a_precondition(int const i) {
        std::clog << "a::ctor::pre" << std::endl; 
        BOOST_CONTRACT_ASSERT(i > 0);
    }
    void a_contract(int const i, boost::contract::call c) const {
        boost::shared_ptr<int const> old_i = BOOST_CONTRACT_OLDOF(c, i);
        boost::contract::constructor(c, this)
            .postcondition([&] {
                std::clog << "a::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x == *old_i);
                BOOST_CONTRACT_ASSERT(i == -1);
            })
        ;
    }
    explicit a(int& i) :
        boost::contract::constructor_precondition<a>(
                boost::bind(&a::a_precondition, i)),
        b(i)
    {
        boost::contract::scoped contract = boost::contract::bind(
                &a::a_contract, this, i);
        std::clog << "a::ctor::body" << std::endl;
        x = i;
        i = -1;
    }
};

int main() {
    int i = 123;
    a aa(i);
    return 0;
}

