
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>
#include <limits>
#include <cassert>

//[private_protected
class counter {
    // Private and protected functions use `function()` like non-members.

private:
    int n_;

    void dec() {
        boost::contract::old_ptr<int> old_get = BOOST_CONTRACT_OLDOF(get());
        boost::contract::guard c = boost::contract::function()
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(
                        get() + 1 >= std::numeric_limits<int>::min());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(get() == *old_get - 1);
            })
        ;

        set(get() - 1);
    }

protected:
    virtual void set(int n, boost::contract::virtual_* = 0) {
        boost::contract::guard c = boost::contract::function()
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(n <= 0);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(get() == n);
            })
        ;

        n_ = n;
    }

    /* ... */
//]

public:
    virtual int get(boost::contract::virtual_* v = 0) const {
        int result;
        boost::contract::guard c = boost::contract::public_function(
                v, result, this)
            .postcondition([&] (int const result) {
                BOOST_CONTRACT_ASSERT(result <= 0);
                BOOST_CONTRACT_ASSERT(result == n_);
            })
        ;

        return result = n_;
    }

    counter() : n_(0) {} // Should contract constructor and destructor too.
    
    void invariant() const {
        BOOST_CONTRACT_ASSERT(get() <= 0);
    }

    friend int main();
};

int main() {
    counter cnt;
    assert(cnt.get() == 0);
    cnt.dec();
    assert(cnt.get() == -1);
    return 0;
}

