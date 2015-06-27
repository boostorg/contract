
#include <boost/contract.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/utility.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>
#include <functional>
#include <iterator>
#include <memory>

// TODO: Is there any way around this? Probably not...
// This can be programmed directly at call site with C++14 generic lambdas.
struct all_of_equal {
    typedef bool result_type;

    template<typename InputIter, typename T>
    result_type operator()(InputIter first, InputIter last, T const& value) {
        return boost::algorithm::all_of_equal(first, last, value);
    }
};

// TODO: Try if this is still the case with MSVC 2013...
// This is required on MSVC (which cannot always deduce lambda result type).
template<typename T>
struct always_call {
    typedef T result_type;

    explicit always_call(T const& r) : r_(r) {}

    result_type operator()(...) const { return r_; }

private:
    T r_;
};
template<typename T>
always_call<T> always(T const& r) { return always_call<T>(r); }

// TODO: Fix all code below to use helpers above...

template<typename T, class Alloc = std::allocator<T> >
class vector {
public:
    typedef typename std::vector<T, Alloc>::allocator_type allocator_type;
    typedef typename std::vector<T, Alloc>::pointer pointer;
    typedef typename std::vector<T, Alloc>::const_pointer const_pointer;
    typedef typename std::vector<T, Alloc>::reference reference;
    typedef typename std::vector<T, Alloc>::const_reference const_reference;
    typedef typename std::vector<T, Alloc>::value_type value_type;
    typedef typename std::vector<T, Alloc>::iterator iterator;
    typedef typename std::vector<T, Alloc>::const_iterator const_iterator;
    typedef typename std::vector<T, Alloc>::size_type size_type;
    typedef typename std::vector<T, Alloc>::difference_type difference_type;
    typedef typename std::vector<T, Alloc>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T, Alloc>::const_reverse_iterator
            const_reverse_iterator;

    void invariant() const {
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
        BOOST_CONTRACT_ASSERT(std::distance(begin(), end()) == int(size()));
        BOOST_CONTRACT_ASSERT(std::distance(rbegin(), rend()) == int(size()));
        BOOST_CONTRACT_ASSERT(size() <= capacity());
        BOOST_CONTRACT_ASSERT(capacity() <= max_size());
    }

    vector() : vect_() {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;
    }
    
    explicit vector(Alloc const& allocator) : vect_(allocator) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(empty());
                BOOST_CONTRACT_ASSERT(get_allocator() == allocator);
            })
        ;
    }

    explicit vector(size_type count) : vect_(count) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(this->size() == count);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<T> >(
                        boost::bind(all_of_equal(), begin(), end(), T())
                    ).else_(always(true))
                );
            })
        ;
    }

    vector(size_type count, T const& value) : vect_(count, value) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<T> >(
                        boost::bind(
                            &boost::algorithm::all_of_equal<
                                    const_iterator, T>,
                            begin(), end(), boost::cref(value)
                        )
                    ).else_([] { return true; })
                );
            })
        ;
    }

    template<typename InputIter>
    vector(InputIter first, InputIter last) : vect_(first, last) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, last) ==
                        int(size()));
            })
        ;
    }
    
    template<typename InputIter>
    vector(InputIter first, InputIter last, Alloc const& allocator) :
            vect_(first, last, allocator) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, last) ==
                        int(size()));
                BOOST_CONTRACT_ASSERT(get_allocator() == allocator);
            })
        ;
    }

    /* implicit */ vector(vector const& other) : vect_(other.vect_) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(*this), boost::cref(other))
                    ).else_(always(true))
                );
            })
        ;
    }

    vector& operator=(vector const& other) {
        boost::optional<vector&> result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<
                            vector<T> > >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(*this), boost::cref(other))
                    ).else_([] { return true; })
                );
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<
                            vector<T> > >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(*result), boost::cref(*this))
                    ).else_([] { return true; })
                );
            })
        ;
        if(this != &other) vect_ = other.vect_;
        return *(result = *this);
    }

    virtual ~vector() { auto c = boost::contract::destructor(this); }

    void reserve(size_type count) {
        auto c = boost::contract::public_function(this)
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
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result >= size());
            })
        ;

        return result = vect_.capacity();
    }

    iterator begin() {
        iterator result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(this->empty()) BOOST_CONTRACT_ASSERT(result == end());
            })
        ;

        return result = vect_.begin();
    }

    const_iterator begin() const {
        const_iterator result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(this->empty()) BOOST_CONTRACT_ASSERT(result == end());
            })
        ;

        return result = vect_.begin();
    }

    iterator end() {
        auto c = boost::contract::public_function(this);
        return vect_.end();
    }
    
    const_iterator end() const {
        auto c = boost::contract::public_function(this);
        return vect_.end();
    }
    
    reverse_iterator rbegin() {
        iterator result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == rend());
            })
        ;

        return result = vect_.rbegin();
    }

    const_reverse_iterator rbegin() const {
        const_reverse_iterator result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(this->empty()) BOOST_CONTRACT_ASSERT(result == rend());
            })
        ;

        return result = vect_.rbegin();
    }

    reverse_iterator rend() {
        auto c = boost::contract::public_function(this);
        return vect_.rend();
    }
    
    const_reverse_iterator rend() const {
        auto c = boost::contract::public_function(this);
        return vect_.rend();
    }

    void resize(size_type count, T const& value = T()) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                if(count > *old_size) {
                    BOOST_CONTRACT_ASSERT(
                        boost::contract::call_if<boost::has_equal_to<T> >(
                            boost::bind(
                                &boost::algorithm::all_of_equal<
                                        const_iterator, T>,
                                begin() + *old_size,
                                end(),
                                boost::cref(value)
                            )
                        ).else_([] { return true; })
                    );
                }
            })
        ;

        vect_.resize(count, value);
    }

    size_type size() const {
        size_type result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result <= capacity());
            })
        ;

        return result = vect_.size();
    }

    size_type max_size() const {
        size_type result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result >= capacity());
            })
        ;

        return result = vect_.max_size();
    }

    bool empty() const {
        bool result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result == (this->size() == 0));
            })
        ;

        return vect_.empty();
    }

    Alloc get_allocator() const {
        auto c = boost::contract::public_function(this);
        return vect_.get_allocator();
    }

    reference at(size_type index) {
        // No precondition because throws out_of_range for invalid index.
        auto c = boost::contract::public_function(this);
        return vect_.at(index);
    }
    
    const_reference at(size_type index) const {
        // No precondition because throws out_of_range for invalid index.
        auto c = boost::contract::public_function(this);
        return vect_.at(index);
    }

    reference operator[](size_type index) {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;

        return vect_[index];
    }
    
    const_reference operator[](size_type index) const {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;

        return vect_[index];
    }

    reference front() {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        return vect_.front();
    }
    
    const_reference front() const {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        return vect_.front();
    }

    reference back() {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        return vect_.back();
    }
    
    const_reference back() const {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        return vect_.back();
    }

    void push_back(T const& value) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto old_capacity = BOOST_CONTRACT_OLDOF(capacity());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(this->size() < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(this->size() == *old_size + 1);
                BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<T>(), boost::cref(back()),
                                boost::cref(value))
                    ).else_([] { return true; })
                );
            })
        ;

        vect_.push_back(value);
    }

    void pop_back() {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_function(this)
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
        auto c = boost::contract::public_function(this)
            // Precondition: [begin(), end()) does not contain [first, last).
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, last) ==
                        int(size()));
            })
        ;

        vect_.assign(first, last);
    }

    void assign(size_type count, T const& value) {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(count <= max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<T> >(
                        boost::bind(
                            &boost::algorithm::all_of_equal<
                                    const_iterator, T>,
                            begin(), end(), boost::cref(value)
                        )
                    ).else_([] { return true; })
                );
            })
        ;

        vect_.assign(count, value);
    }

    iterator insert(iterator where, T const& value) {
        iterator result;
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<T>(), boost::cref(*result),
                                boost::cref(value))
                    ).else_([] { return true; })
                    //  if(capacity() > oldof capacity())
                    //      [begin(), end()) is invalid
                    //  else
                    //      [where, end()) is invalid
                );
            })
        ;

        return result = vect_.insert(where, value);
    }

    void insert(iterator where, size_type count, T const& value) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto old_capacity = BOOST_CONTRACT_OLDOF(capacity());
        auto old_where = BOOST_CONTRACT_OLDOF(where);
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(this->size() + count < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(this->size() == *old_size + count);
                BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
                if(capacity() == *old_capacity) {
                    BOOST_CONTRACT_ASSERT(
                        boost::contract::call_if<boost::has_equal_to<T> >(
                            boost::bind(all_of_equal(),
                                boost::prior(*old_where),
                                boost::prior(*old_where) + count,
                                boost::cref(value)
                            )
                        ).else_(always(true))
                    );
                }
            })
        ;

        vect_.insert(where, count, value);
    }

    template<typename InputIter>
    void insert(iterator where, InputIter first, InputIter last) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto old_capacity = BOOST_CONTRACT_OLDOF(capacity());
        auto c = boost::contract::public_function(this)
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
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
                BOOST_CONTRACT_ASSERT(where != end());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
                // [where, end()) is invalid
            })
        ;

        return result = vect_.erase(where);
    }

    iterator erase(iterator first, iterator last) {
        iterator result;
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() >= std::distance(first, last));
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size +
                        std::distance(first, last));
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
                // [first, last) is invalid
            })
        ;

        return result = vect_.erase(first, last);
    }

    void clear() {
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(empty());
            })
        ;

        vect_.clear();
    }

    void swap(vector& other) {
        auto old_me = BOOST_CONTRACT_OLDOF(*this);
        auto old_other = BOOST_CONTRACT_OLDOF(other);
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<
                            vector<T> > >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(*this), boost::cref(*old_other))
                    ).else_([] { return true; })
                );
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<
                            vector<T> > >(
                        boost::bind(std::equal_to<vector<T> >(),
                                boost::cref(other), boost::cref(*old_me))
                    ).else_([] { return true; })
                );
            })
        ;

        vect_.swap(other);
    }

    friend bool operator==(vector const& left, vector const& right) {
        return left.vect_ == right.vect_;
    }

private:
    std::vector<T, Alloc> vect_;
};

struct x {};

template<typename F>
decltype(boost::declval<F>()()) r(F f) {
//    std::cout << typeid(t).name() << std::endl;
    return "abc";
}

int main() {
    // Test vector of equality comparable type `char`.

    vector<char> v(3);
    BOOST_TEST_EQ(v.size(), 3);
    BOOST_TEST(boost::algorithm::all_of_equal(v, '\0'));
    vector<char> const& cv = v;

    vector<char> w(v);
    BOOST_TEST(w == v); // Cannot use TEST_EQ here (because it'd print w and v).

    vector<char>::iterator i = v.begin();
    BOOST_TEST_EQ(*i, '\0');

    vector<char>::const_iterator ci = cv.begin();
    BOOST_TEST_EQ(*ci, '\0');

    v.insert(i, 2, 'a');
    BOOST_TEST_EQ(v[0], 'a');
    BOOST_TEST_EQ(v[1], 'a');

    v.push_back('b');
    BOOST_TEST_EQ(v.back(), 'b');

    // Test vector of non equality comparable type `x`.

    vector<x> y(3);
    BOOST_TEST_EQ(y.size(), 3);
    vector<x> const& cy = y;

    vector<x> z(y);

    vector<x>::iterator j = y.begin();
    
    vector<x>::const_iterator cj = cy.begin();

    y.insert(j, 2, x());

    return boost::report_errors();
}

