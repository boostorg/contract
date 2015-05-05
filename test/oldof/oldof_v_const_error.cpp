
#include <boost/contract/public_member.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/introspect.hpp>

// Test virtual old value declarations must be const.

struct num {
    int x;

    void inc(int const delta, boost::contract::virtual_body v = 0) {
        boost::shared_ptr<int> old_x = BOOST_CONTRACT_OLDOF(v, x); // Error.
        auto c = boost::contract::public_member<introspect_inc>(v,
                this, &num::inc, delta)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(*old_x == x - delta); // OK.
            })
        ;
        inc_body(delta);
    }
    virtual void inc_body(int const delta) { x = x + delta; }
    BOOST_CONTRACT_INTROSPECT(inc)
};

int main() {
    num n;
    n.x = 10;
    n.inc(5);
    return 0;
}

