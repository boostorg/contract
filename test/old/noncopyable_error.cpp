
// Test forcing compiler error for old values of non-copyable types.

#include <boost/contract/function.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>
#include <boost/noncopyable.hpp>

template<typename T>
void next(T& x) {
    boost::contract::old_ptr<T> old_x = BOOST_CONTRACT_OLDOF(x);
    boost::contract::guard c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(x > *old_x); // No need to check if(old_x)...
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

    next(i); // OK.
    next(c); // OK.
    next(n); // Error.

    return 0;
}

