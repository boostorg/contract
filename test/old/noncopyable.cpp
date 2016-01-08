
// Test old values of non-copyable types.

#include <boost/contract/public_function.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/detail/lightweight_test.hpp>

unsigned old_checks;

template<typename T>
struct b {
    virtual void next(T& x, boost::contract::virtual_* v = 0) {
        boost::contract::old_ptr<T> old_x = BOOST_CONTRACT_OLDOF(v, x);
        boost::contract::guard c = boost::contract::public_function(v, this)
            .postcondition([&] {
                if(old_x) {
                    BOOST_CONTRACT_ASSERT(x > *old_x);
                    ++old_checks;
                }
            })
        ;
        ++x;
    }
    BOOST_CONTRACT_OVERRIDE(next)
};

template<typename T>
struct a
    #define BASES public b<T>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    virtual void next(T& x, boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::old_ptr<T> old_x = BOOST_CONTRACT_OLDOF(v, x);
        boost::contract::guard c = boost::contract::public_function<
                override_next>(v, &a::next, this, x)
            .postcondition([&] {
                if(old_x) {
                    BOOST_CONTRACT_ASSERT(x > *old_x);
                    ++old_checks;
                }
            })
        ;
        ++x;
    }
    BOOST_CONTRACT_OVERRIDE(next)
};

template<typename T>
void next(T& x) {
    boost::contract::old_ptr<T> old_x = BOOST_CONTRACT_OLDOF(x);
    boost::contract::guard c = boost::contract::function()
        .postcondition([&] {
            if(old_x) {
                BOOST_CONTRACT_ASSERT(x > *old_x);
                ++old_checks;
            }
        })
    ;
    ++x;
}

struct cp {
    explicit cp(int value) : value_(value) {}

    friend cp& operator++(cp& me) { ++me.value_; return me; }

    friend bool operator>(cp const& left, cp const& right) {
        return left.value_ > right.value_;
    }

private:
    int value_;
};

struct ncp : private boost::noncopyable {
    explicit ncp(int value) : value_(value) {}

    friend ncp& operator++(ncp& me) { ++me.value_; return me; }

    friend bool operator>(ncp const& left, ncp const& right) {
        return left.value_ > right.value_;
    }

private:
    int value_;
};

int main() {
    int i = 1; // Test built-in copyable type.
    cp c(1); // Test custom copyable type.
    ncp n(1); // Test non-copyable type.

    // Test free functions (old values without `v`).

    unsigned cnt =
        #if BOOST_CONTRACT_POSTCONDITIONS
            1
        #else
            0
        #endif
    ;

    old_checks = 0;
    next(i);
    BOOST_TEST_EQ(old_checks, cnt);
    
    old_checks = 0;
    next(c);
    BOOST_TEST_EQ(old_checks, cnt);

    old_checks = 0;
    next(n);
    BOOST_TEST_EQ(old_checks, 0);

    // Test virtual functions (old values with `v`).
    
    cnt =
        #if BOOST_CONTRACT_POSTCONDITIONS
            2
        #else
            0
        #endif
    ;

    a<int> ai;
    old_checks = 0;
    ai.next(i);
    BOOST_TEST_EQ(old_checks, cnt);
    
    a<cp> ac;
    old_checks = 0;
    ac.next(c);
    BOOST_TEST_EQ(old_checks, cnt);

    a<ncp> an;
    old_checks = 0;
    an.next(n);
    BOOST_TEST_EQ(old_checks, 0);

    return boost::report_errors();
}

