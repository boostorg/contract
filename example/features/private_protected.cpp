
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>
#include <limits>
#include <cassert>

//[private_protected
class counter {
protected:
    int get() const { // Protected function (like non-member functions).
        int result;
        boost::contract::guard c = boost::contract::function()
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result == n_);
            })
        ;

        return result = n_; // Function body.
    }

private:
    void dec() { // Private function (like non-member functions).
        boost::contract::old_ptr<int> old_n = BOOST_CONTRACT_OLDOF(n_);
        boost::contract::guard c = boost::contract::function()
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(n_ > std::numeric_limits<int>::min());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(n_ == *old_n - 1);
            })
        ;

        --n_; // Function body.
    }

    int n_;
    
    /* ... */
//]

    friend struct test_counter;
public:
    counter() : n_(0) {}
};

struct test_counter {
    static void run() {
        counter cnt;
        assert(cnt.get() == 0);
        cnt.dec();
        assert(cnt.get() == -1);
    }
};

int main() {
    test_counter::run();
    return 0;
}

