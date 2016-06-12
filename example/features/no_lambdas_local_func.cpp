
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>
#include <boost/bind.hpp>
#include <cassert>

//[no_lambdas_local_func
#include <boost/local_function.hpp>

template<typename T, unsigned MaxSize>
class array :
        private boost::contract::constructor_precondition<array<T, MaxSize> > {
public:
    static void static_invariant() {
        BOOST_CONTRACT_ASSERT(instances() >= 0);
    }

    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() <= MaxSize);
    }

    static void constructor_pre(unsigned const count) {
        BOOST_CONTRACT_ASSERT(count <= MaxSize);
    }
    explicit array(unsigned count) :
        boost::contract::constructor_precondition<array>(boost::bind(
                &array::constructor_pre, count)),
        values_(new T[MaxSize])
    {
        boost::contract::old_ptr<int> old_instances;
        void BOOST_LOCAL_FUNCTION_TPL(bind& old_instances) {
            old_instances = BOOST_CONTRACT_OLDOF(array::instances());
        } BOOST_LOCAL_FUNCTION_NAME_TPL(old)
        void BOOST_LOCAL_FUNCTION_TPL(const bind this_, const bind& count,
                const bind& old_instances) { 
            BOOST_CONTRACT_ASSERT(this_->size() == count);
            BOOST_CONTRACT_ASSERT(this_->instances() == *old_instances + 1);
        } BOOST_LOCAL_FUNCTION_NAME_TPL(post)
        boost::contract::guard c = boost::contract::constructor(this)
                .old(old).postcondition(post);

        for(unsigned i = 0; i < count; ++i) values_[i] = T();
        size_ = count;
        ++instances_;
    }

    virtual ~array() {
        boost::contract::old_ptr<int> old_instances;
        void BOOST_LOCAL_FUNCTION_TPL(const bind this_, bind& old_instances) {
            old_instances = BOOST_CONTRACT_OLDOF(this_->instances());
        } BOOST_LOCAL_FUNCTION_NAME_TPL(old)
        void BOOST_LOCAL_FUNCTION_TPL(const bind& old_instances) {
            BOOST_CONTRACT_ASSERT(array::instances() == *old_instances - 1);
        } BOOST_LOCAL_FUNCTION_NAME_TPL(post)
        boost::contract::guard c = boost::contract::destructor(this)
                .old(old).postcondition(post);
    
        delete[] values_;
        --instances_;
    }

    virtual void push_back(T const& value, boost::contract::virtual_* v = 0) {
        boost::contract::old_ptr<unsigned> old_size;
        void BOOST_LOCAL_FUNCTION_TPL(const bind this_) {
            BOOST_CONTRACT_ASSERT(this_->size() < MaxSize);
        } BOOST_LOCAL_FUNCTION_NAME_TPL(pre)
        void BOOST_LOCAL_FUNCTION_TPL(const bind v, const bind this_,
                bind& old_size) {
            old_size = BOOST_CONTRACT_OLDOF(v, this_->size());
        } BOOST_LOCAL_FUNCTION_NAME_TPL(old)
        void BOOST_LOCAL_FUNCTION_TPL(const bind this_, const bind& old_size) {
            BOOST_CONTRACT_ASSERT(this_->size() == *old_size + 1);
        } BOOST_LOCAL_FUNCTION_NAME_TPL(post)
        boost::contract::guard c = boost::contract::public_function(v, this)
                .precondition(pre).old(old).postcondition(post);

        values_[size_++] = value;
    }
    
    unsigned size() const {
        // Check invariants.
        boost::contract::guard c = boost::contract::public_function(this);
        return size_;
    }

    static int instances() {
        // Check static invariants.
        boost::contract::guard c = boost::contract::public_function<array>();
        return instances_;
    }

private:
    T* values_;
    unsigned size_;
    static int instances_;
};

template<typename T, unsigned MaxSize>
int array<T, MaxSize>::instances_ = 0;
//]

int main() {
    array<char, 3> a(2);
    assert(a.size() == 2);
    a.push_back('x');
    assert(a.size() == 3);
    return 0;
}

