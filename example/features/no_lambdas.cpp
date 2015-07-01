
#include "separate_body.hpp"

//[no_lambdas_cpp
template<typename T, std::size_t MaxSize>
int array<T, MaxSize>::instances_ = 0;

template<typename T, std::size_t MaxSize>
array<T, MaxSize>::array(std::size_t count) :
    boost::contract::constructor_precondition<unique_identifiers>(
            &array::constructor_precondition),
    values_(new T[MaxSize]) // Member initialization can be here.
{
    boost::shared_ptr<int const> old_instances;
    auto c = boost::contract::constructor(this)
        .old(boost::bind(&array::constructor_old, boost::ref(old_instances))
        .postcondition(boost::bind(&array::constructor_postcondition, this))
    ;

    for(std::size_t i = 0; i < count; ++i) values_[i] = T();
    size_ = count;
    ++instances_;
}

template<typename T, std::size_t MaxSize>
array<T, MaxSize>::~array() {
    boost::shared_ptr<int const> old_instances;
    auto c = boost::contract::destructor(this)
        .old(boost::bind(&array::destructor_old, boost::ref(old_instances))
        .postcondition(&array::destructor_postcondition)
    ;
    
    delete[] values_;
    --instances_;
}

template<typename T, std::size_t MaxSize>
void array::push_back_body(T const& value) {
    boost::shared_ptr<std::size_t const> old_size;
    auto c = boost::contract::public_function(v, this)
        .precondition(boost::bind(&array::push_back_precondition,
                this, boost::cref(value)))
        .old(boost::bind(&array::push_back_old, this, boost::ref(old_size))
        .postcondition(boost::bind(&array::push_back_postcondition,
                this, boost::cref(value), old_size))
    ;

    values_[size_++] == value;
}

template<typename T, std::size_t MaxSize>
std::size_t array::size_body() const {
    auto c = boost::contract::public_function(this); // Check invariants.
    return size_;
}

template<typename T, std::size_t MaxSize>
int array::instance() {
    auto c = boost::contract::public_function<array>(); // Check invariants.
    return instances_;
}
//]

