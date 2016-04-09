
// Copyright (C) 2008-2015 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// Home at http://www.boost.org/libs/contract

#include <cassert>

//[introduction
#include <boost/contract.hpp>
#include <vector>
#include <cassert>

template<typename T> class pushable;

template<typename T>
class vector
    #define BASES public pushable<T>
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types; // Subcontracting.
    #undef BASES

    void invariant() const { // Checked in AND with base class invariants.
        BOOST_CONTRACT_ASSERT(size() <= capacity()); // Line 25.
    }

    virtual void push_back(T const& value, boost::contract::virtual_* v = 0)
            /* override */ {
        boost::contract::old_ptr<unsigned> old_size =
                BOOST_CONTRACT_OLDOF(v, size()); // Old values.
        boost::contract::guard c = boost::contract::public_function<
                override_push_back>(v, &vector::push_back, this, value)
            .precondition([&] { // Checked in OR with base preconditions.
                BOOST_CONTRACT_ASSERT(size() < max_size()); // Line 35.
            })
            .postcondition([&] { // Checked in AND with base postconditions.
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1); // Line 38.
            })
        ;

        vect_.push_back(value);
    }
    BOOST_CONTRACT_OVERRIDE(push_back) // For `override_push_back`.

    unsigned size() const { return vect_.size(); }
    unsigned max_size() const { return vect_.max_size(); }
    unsigned capacity() const { return vect_.capacity(); }

private:
    std::vector<T> vect_;
};
//]

template<typename T>
class pushable {
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(capacity() <= max_size());
    }

    virtual void push_back(T const& value, boost::contract::virtual_* v = 0)
            = 0;

protected:
    virtual unsigned capacity() const = 0;
    virtual unsigned max_size() const = 0;
};

template<typename T> // Contract for pure virtual function.
void pushable<T>::push_back(T const& value, boost::contract::virtual_* v) {
    boost::contract::old_ptr<unsigned> old_capacity =
            BOOST_CONTRACT_OLDOF(v, capacity());
    boost::contract::guard c = boost::contract::public_function(v, this)
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(capacity() < max_size());
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
        })
    ;
    assert(false); // Shall never execute this body.
}

int main() {
    vector<int> vect;
    vect.push_back(123);
    assert(vect.size() == 1);
    return 0;
}

