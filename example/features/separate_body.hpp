
#ifndef SEPARATE_BODY_HPP_
#define SEPARATE_BODY_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>

//[separate_body_hpp
template<typename T, unsigned MaxSize>
class array :
        private boost::contract::constructor_precondition<array<T, MaxSize> > {
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() <= MaxSize);
    }

    explicit array(unsigned count) :
        boost::contract::constructor_precondition<array>([&] {
            BOOST_CONTRACT_ASSERT(count <= MaxSize);
        }),
        values_(new T[MaxSize]) // Still, member initializations must be here.
    {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
            })
        ;
        constructor_body(count); // Separate constructor body implementation.
    }

    virtual ~array() {
        boost::contract::guard c = boost::contract::destructor(this); // Inv.
        destructor_body(); // Separate destructor body implementation.
    }

    virtual void push_back(T const& value, boost::contract::virtual_* v = 0) {
        boost::contract::old_ptr<unsigned> old_size =
                BOOST_CONTRACT_OLDOF(v, size());
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() < MaxSize);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
            })
        ;
        push_back_body(value);
    }

private:
    // Contracts in class declaration (above), but body implementations are not.
    void constructor_body(unsigned count);
    void destructor_body();
    void push_back_body(T const& value);

    /* ... */
//]
    
public:
    unsigned size() const {
        // Check invariants.
        boost::contract::guard c = boost::contract::public_function(this);
        return size_body();
    }
    
private:
    unsigned size_body() const;

    T* values_;
    unsigned size_;
};

#endif // #include guard

