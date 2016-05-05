
#include "no_lambdas.hpp"
#include <boost/bind.hpp>
#include <cassert>

//[no_lambdas_cpp
template<typename T, unsigned MaxSize>
array<T, MaxSize>::array(unsigned count) :
    boost::contract::constructor_precondition<array>(boost::bind(
            &array::constructor_precondition, count)),
    values_(new T[MaxSize]) // Member initializations can be here.
{
    boost::contract::old_ptr<int> old_instances;
    boost::contract::guard c = boost::contract::constructor(this)
        .old(boost::bind(&array::constructor_old, boost::ref(old_instances)))
        .postcondition(boost::bind(&array::constructor_postcondition, this,
                boost::cref(count), boost::cref(old_instances)))
    ;

    for(unsigned i = 0; i < count; ++i) values_[i] = T();
    size_ = count;
    ++instances_;
}

template<typename T, unsigned MaxSize>
array<T, MaxSize>::~array() {
    boost::contract::old_ptr<int> old_instances;
    boost::contract::guard c = boost::contract::destructor(this)
        .old(boost::bind(&array::destructor_old, this,
                boost::ref(old_instances)))
        .postcondition(boost::bind(&array::destructor_postcondition,
                boost::cref(old_instances)))
    ;
    
    delete[] values_;
    --instances_;
}

template<typename T, unsigned MaxSize>
void array<T, MaxSize>::push_back(T const& value,
        boost::contract::virtual_* v) {
    boost::contract::old_ptr<unsigned> old_size;
    boost::contract::guard c = boost::contract::public_function(v, this)
        .precondition(boost::bind(&array::push_back_precondition, this))
        .old(boost::bind(&array::push_back_old, this, boost::cref(v),
                boost::ref(old_size)))
        .postcondition(boost::bind(&array::push_back_postcondition, this,
                boost::cref(old_size)))
    ;

    values_[size_++] = value;
}

template<typename T, unsigned MaxSize>
unsigned array<T, MaxSize>::size() const {
    // Check invariants.
    boost::contract::guard c = boost::contract::public_function(this);
    return size_;
}

template<typename T, unsigned MaxSize>
int array<T, MaxSize>::instances() {
    // Check static invariants.
    boost::contract::guard c = boost::contract::public_function<array>();
    return instances_;
}

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

