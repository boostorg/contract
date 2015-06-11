
#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <boost/contract.hpp>
#include <boost/bind.hpp>

template<typename T>
class vector
    #define BASES private boost::contract::constructor_precondition<vector<T> >
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    // NOTE: Incomplete contract assertions, addressing only `size`.

    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() >= 0);
    }

    static void vector_precondition(int const& count) {
        BOOST_CONTRACT_ASSERT(count >= 0);
    }
    explicit vector(int count = 10) :
        boost::contract::constructor_precondition<vector>(boost::bind(
                &vector::vector_precondition, boost::cref(count))),
        data_(new T[count]),
        size_(count)
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(this->size() == count);
            })
        ;

        for(int i = 0; i < size_; ++i) data_[i] = T();
    }

    virtual ~vector() {
        auto c = boost::contract::destructor(this);
        delete[] data_;
    }

    int size() const {
        auto c = boost::contract::public_function(this);
        return size_; // Non-negative result already checked by invariant.
    }

    void resize(int count) {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(count >= 0);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(this->size() == count);
            })
        ;

        T* slice = new T[count];
        for(int i = 0; i < count && i < size_; ++i) slice[i] = data_[i];
        delete[] data_;
        data_ = slice;
        size_ = count;
    }

    T& operator[](int index) {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index >= 0);
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;

        return data_[index];
    }
    
    T const& operator[](int index) const {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index >= 0);
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;

        return data_[index];
    }

private:
    T* data_;
    int size_;
};

#endif // #include guard

