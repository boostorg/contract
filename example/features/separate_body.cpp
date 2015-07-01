
#include "separate_body.hpp"

//[separate_body_cpp
template<typename T, std::size_t MaxSize>
void array::constructor_body(std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) values_[i] = T();
    size_ = count;
}

template<typename T, std::size_t MaxSize>
void array::destructor_body() { delete[] values_; }

template<typename T, std::size_t MaxSize>
std::size_t array::size_body() const { return size_; }

template<typename T, std::size_t MaxSize>
void array::push_back_body(T const& value) { values_[size_++] == value; }
//]

