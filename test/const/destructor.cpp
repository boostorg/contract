
#include <boost/contract/destructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/contract/bind.hpp>

struct b {
    void invariant() const { std::clog << "b::inv" << std::endl; }
    static void static_invariant() {
        std::clog << "b::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(y >= 0);
    }

    static int y;
    b() { ++y; }

    void dtor_contract(boost::contract::call c) const {
        boost::shared_ptr<int const> old_y = BOOST_CONTRACT_OLDOF(c, y);
        boost::contract::destructor(c, this)
            .postcondition([&] {
                std::clog << "b::dtor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(y == *old_y - 1);
            })
        ;
    }
    virtual ~b() {
        boost::contract::scoped contract = boost::contract::bind(
                &b::dtor_contract, this);
        std::clog << "b::dtor::body" << std::endl;
        --y;
    }
};
int b::y = 0;

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const { std::clog << "a::inv" << std::endl; }
    static void static_invariant() {
        std::clog << "a::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(x >= 0);
    }

    static int x;
    a() { ++x; }

    void dtor_contract(boost::contract::call c) const {
        boost::shared_ptr<int const> old_x = BOOST_CONTRACT_OLDOF(c, x);
        boost::contract::destructor(c, this)
            .postcondition([&] {
                std::clog << "a::dtor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x == *old_x - 1);
            })
        ;
    }
    ~a() {
        boost::contract::scoped contract = boost::contract::bind(
                &a::dtor_contract, this);
        std::clog << "a::dtor::body" << std::endl;
        --x;
    }
};
int a::x = 0;

int main() {
    a aa;
    return 0;
}

