
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[n1962_vector
#include <boost/contract.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/utility.hpp>
#include <vector>
#include <functional>
#include <iterator>
#include <memory>
#include <cassert>

// Could be programmed at call site with C++14 generic lambdas.
struct all_of_equal_to {
    typedef bool result_type;

    template<typename InputIter, typename T>
    result_type operator()(InputIter first, InputIter last, T const& value) {
        return boost::algorithm::all_of_equal(first, last, value);
    }
};

// STL vector requires T copyable but not equality comparable.
template<typename T, class Allocator = std::allocator<T> >
class vector {
    friend class boost::contract::access;

    void invariant() const {
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
        BOOST_CONTRACT_ASSERT(std::distance(begin(), end()) == int(size()));
        BOOST_CONTRACT_ASSERT(std::distance(rbegin(), rend()) == int(size()));
        BOOST_CONTRACT_ASSERT(size() <= capacity());
        BOOST_CONTRACT_ASSERT(capacity() <= max_size());
    }

public:
    typedef typename std::vector<T, Allocator>::allocator_type allocator_type;
    typedef typename std::vector<T, Allocator>::pointer pointer;
    typedef typename std::vector<T, Allocator>::const_pointer const_pointer;
    typedef typename std::vector<T, Allocator>::reference reference;
    typedef typename std::vector<T, Allocator>::const_reference const_reference;
    typedef typename std::vector<T, Allocator>::value_type value_type;
    typedef typename std::vector<T, Allocator>::iterator iterator;
    typedef typename std::vector<T, Allocator>::const_iterator const_iterator;
    typedef typename std::vector<T, Allocator>::size_type size_type;
    typedef typename std::vector<T, Allocator>::difference_type difference_type;
    typedef typename std::vector<T, Allocator>::reverse_iterator
            reverse_iterator;
    typedef typename std::vector<T, Allocator>::const_reverse_iterator
            const_reverse_iterator;

    vector() : vect_() {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(empty());
            })
        ;
    }
    
    explicit vector(Allocator const& alloc) : vect_(alloc) {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(empty());
                BOOST_CONTRACT_ASSERT(get_allocator() == alloc);
            })
        ;
    }

    explicit vector(size_type count) : vect_(count) {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(all_of_equal_to(), begin(), end(), T())
                    )
                );
            })
        ;
    }

    vector(size_type count, T const& value) : vect_(count, value) {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(all_of_equal_to(), begin(), end(),
                                boost::cref(value))
                    )
                );
            })
        ;
    }

    vector(size_type count, const T& value, Allocator const& alloc) :
            vect_(count, value, alloc) {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(all_of_equal_to(), begin(), end(),
                                boost::cref(value))
                    )
                );
                BOOST_CONTRACT_ASSERT(alloc == get_allocator());
            })
        ;
    }

    template<typename InputIter>
    vector(InputIter first, InputIter last) : vect_(first, last) {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, last) ==
                        int(size()));
            })
        ;
    }
    
    template<typename InputIter>
    vector(InputIter first, InputIter last, Allocator const& alloc) :
            vect_(first, last, alloc) {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, last) ==
                        int(size()));
                BOOST_CONTRACT_ASSERT(get_allocator() == alloc);
            })
        ;
    }

    /* implicit */ vector(vector const& other) : vect_(other.vect_) {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(*this), boost::cref(other))
                    )
                );
            })
        ;
    }

    vector& operator=(vector const& other) {
        boost::optional<vector&> result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(*this), boost::cref(other))
                    )
                );
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(*result), boost::cref(*this))
                    )
                );
            })
        ;

        if(this != &other) vect_ = other.vect_;
        return *(result = *this);
    }

    virtual ~vector() {
        boost::contract::guard c = boost::contract::destructor(this);
    }

    void reserve(size_type count) {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(count < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(capacity() >= count);
            })
        ;

        vect_.reserve(count);
    }

    size_type capacity() const {
        size_type result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result >= size());
            })
        ;

        return result = vect_.capacity();
    }

    iterator begin() {
        iterator result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
            })
        ;

        return result = vect_.begin();
    }

    const_iterator begin() const {
        const_iterator result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
            })
        ;

        return result = vect_.begin();
    }

    iterator end() {
        boost::contract::guard c = boost::contract::public_function(this);
        return vect_.end();
    }
    
    const_iterator end() const {
        boost::contract::guard c = boost::contract::public_function(this);
        return vect_.end();
    }
    
    reverse_iterator rbegin() {
        iterator result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == rend());
            })
        ;

        return result = vect_.rbegin();
    }

    const_reverse_iterator rbegin() const {
        const_reverse_iterator result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == rend());
            })
        ;

        return result = vect_.rbegin();
    }

    reverse_iterator rend() {
        boost::contract::guard c = boost::contract::public_function(this);
        return vect_.rend();
    }
    
    const_reverse_iterator rend() const {
        boost::contract::guard c = boost::contract::public_function(this);
        return vect_.rend();
    }

    void resize(size_type count, T const& value = T()) {
        boost::contract::old_ptr<size_type> old_size =
                BOOST_CONTRACT_OLD(size());
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                if(count > *old_size) {
                    BOOST_CONTRACT_ASSERT(
                        boost::contract::condition_if<boost::has_equal_to<T> >(
                            boost::bind(all_of_equal_to(), begin() + *old_size,
                                    end(), boost::cref(value))
                        )
                    );
                }
            })
        ;

        vect_.resize(count, value);
    }

    size_type size() const {
        size_type result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result <= capacity());
            })
        ;

        return result = vect_.size();
    }

    size_type max_size() const {
        size_type result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result >= capacity());
            })
        ;

        return result = vect_.max_size();
    }

    bool empty() const {
        bool result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result == (size() == 0));
            })
        ;

        return vect_.empty();
    }

    Allocator get_allocator() const {
        boost::contract::guard c = boost::contract::public_function(this);
        return vect_.get_allocator();
    }

    reference at(size_type index) {
        // No precondition because throws out_of_range for invalid index.
        boost::contract::guard c = boost::contract::public_function(this);
        return vect_.at(index);
    }
    
    const_reference at(size_type index) const {
        // No precondition because throws out_of_range for invalid index.
        boost::contract::guard c = boost::contract::public_function(this);
        return vect_.at(index);
    }

    reference operator[](size_type index) {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;

        return vect_[index];
    }
    
    const_reference operator[](size_type index) const {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;

        return vect_[index];
    }

    reference front() {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        return vect_.front();
    }
    
    const_reference front() const {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        return vect_.front();
    }

    reference back() {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        return vect_.back();
    }
    
    const_reference back() const {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        return vect_.back();
    }

    void push_back(T const& value) {
        boost::contract::old_ptr<size_type> old_size =
                BOOST_CONTRACT_OLD(size());
        boost::contract::old_ptr<size_type> old_capacity =
                BOOST_CONTRACT_OLD(capacity());
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
                BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<T>(), boost::cref(back()),
                                boost::cref(value))
                    )
                );
            })
        ;

        vect_.push_back(value);
    }

    void pop_back() {
        boost::contract::old_ptr<size_type> old_size =
                BOOST_CONTRACT_OLD(size());
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size - 1);
            })
        ;

        vect_.pop_back();
    }

    template<typename InputIter>
    void assign(InputIter first, InputIter last) {
        boost::contract::guard c = boost::contract::public_function(this)
            // Precondition: [begin(), end()) does not contain [first, last).
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, last) ==
                        int(size()));
            })
        ;

        vect_.assign(first, last);
    }

    void assign(size_type count, T const& value) {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(count <= max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(all_of_equal_to(), begin(), end(),
                                boost::cref(value))
                    )
                );
            })
        ;

        vect_.assign(count, value);
    }

    iterator insert(iterator where, T const& value) {
        iterator result;
        boost::contract::old_ptr<size_type> old_size =
                BOOST_CONTRACT_OLD(size());
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<T>(), boost::cref(*result),
                                boost::cref(value))
                    )
                    //  if(capacity() > old(capacity()))
                    //      [begin(), end()) is invalid
                    //  else
                    //      [where, end()) is invalid
                );
            })
        ;

        return result = vect_.insert(where, value);
    }

    void insert(iterator where, size_type count, T const& value) {
        boost::contract::old_ptr<size_type> old_size =
                BOOST_CONTRACT_OLD(size());
        boost::contract::old_ptr<size_type> old_capacity =
                BOOST_CONTRACT_OLD(capacity());
        boost::contract::old_ptr<iterator> old_where =
                BOOST_CONTRACT_OLD(where);
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() + count < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + count);
                BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
                if(capacity() == *old_capacity) {
                    BOOST_CONTRACT_ASSERT(
                        boost::contract::condition_if<boost::has_equal_to<T> >(
                            boost::bind(all_of_equal_to(),
                                boost::prior(*old_where),
                                boost::prior(*old_where) + count,
                                boost::cref(value)
                            )
                        )
                    );
                    // [where, end()) is invalid
                }
                // else [begin(), end()) is invalid
            })
        ;

        vect_.insert(where, count, value);
    }

    template<typename InputIter>
    void insert(iterator where, InputIter first, InputIter last) {
        boost::contract::old_ptr<size_type> old_size =
                BOOST_CONTRACT_OLD(size());
        boost::contract::old_ptr<size_type> old_capacity =
                BOOST_CONTRACT_OLD(capacity());
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() + std::distance(first, last) <
                        max_size());
                // [first, last) not contained in [begin(), end())
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size() +
                        std::distance(first, last));
                BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
            })
        ;

        vect_.insert(where, first, last);
    }

    iterator erase(iterator where) {
        iterator result;
        boost::contract::old_ptr<size_type> old_size =
                BOOST_CONTRACT_OLD(size());
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
                BOOST_CONTRACT_ASSERT(where != end());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size - 1);
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
                // [where, end()) is invalid
            })
        ;

        return result = vect_.erase(where);
    }

    iterator erase(iterator first, iterator last) {
        iterator result;
        boost::contract::old_ptr<size_type> old_size =
                BOOST_CONTRACT_OLD(size());
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() >= std::distance(first, last));
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size -
                        std::distance(first, last));
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
                // [first, last) is invalid
            })
        ;

        return result = vect_.erase(first, last);
    }

    void clear() {
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(empty());
            })
        ;

        vect_.clear();
    }

    void swap(vector& other) {
        boost::contract::old_ptr<vector> old_me = BOOST_CONTRACT_OLD(*this);
        boost::contract::old_ptr<vector> old_other = BOOST_CONTRACT_OLD(other);
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<
                            vector<T> > >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(*this), boost::cref(*old_other))
                    )
                );
                BOOST_CONTRACT_ASSERT(
                    boost::contract::condition_if<boost::has_equal_to<
                            vector<T> > >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(other), boost::cref(*old_me))
                    )
                );
            })
        ;

        vect_.swap(other);
    }

    friend bool operator==(vector const& left, vector const& right) {
        return left.vect_ == right.vect_;
    }

private:
    std::vector<T, Allocator> vect_;
};
    
int main() {
    // char type has operator==.

    vector<char> v(3);
    assert(v.size() == 3);
    assert(boost::algorithm::all_of_equal(v, '\0'));

    vector<char> const& cv = v;
    assert(cv == v);

    vector<char> w(v);
    assert(w == v);

    typename vector<char>::iterator i = v.begin();
    assert(*i == '\0');

    typename vector<char>::const_iterator ci = cv.begin();
    assert(*ci == '\0');

    v.insert(i, 2, 'a');
    assert(v[0] == 'a');
    assert(v[1] == 'a');

    v.push_back('b');
    assert(v.back() == 'b');

    struct x {}; // x type doest not have operator==.

    vector<x> y(3);
    assert(y.size() == 3);

    vector<x> const& cy = y;
    vector<x> z(y);

    typename vector<x>::iterator j = y.begin();
    assert(j != y.end());
    typename vector<x>::const_iterator cj = cy.begin();
    assert(cj != cy.end());

    y.insert(j, 2, x());
    y.push_back(x());

    return 0;
}
//]

