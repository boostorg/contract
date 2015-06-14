
#include <boost/contract.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <vector>
#include <memory>
#include <iterator>

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
        BOOST_CONTRACT_ASSERT(std::distance(cbegin(), cend()) == int(size()));
        BOOST_CONTRACT_ASSERT(std::distance(rcbegin(), rcend()) == int(size()));
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
                BOOST_CONTRACT_ASSERT(size() == count);
//                BOOST_CONTRACT_ASSERT(
//                    boost::contract::check_if<boost::has_equal_to<T> >(
//                        boost::bind(&boost::algorithm::all_of_equal, cbegin(),
//                                cend(), boost::cref(T()))
//                    )
//                );
            })
        ;
    }

    vector(size_type count, T const& value) : vect_(count, value) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::bind(&boost::algorithm::all_of_equal, cbegin(),
                                cend(), boost::cref(value))
                    )
                );
            })
        ;
    }

    template<typename InputIter>
    vector(InputIter first, InputIter last) : vect_(first, last) {
        auto c = boost::contract::construcotr(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, last) ==
                        int(size()));
            })
        ;
    }
    
    template<typename InputIter>
    vector(InputIter first, InputIter last, Alloc const& allocator) :
            vect_(first, last, allocator) {
        auto c = boost::contract::construcotr(this)
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
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::bind(&std::equal_to, boost::cref(*this),
                                boost::cref(other))
                    )
                );
            })
        ;
    }

    vector& operator=(vector const& other) {
        boost::optional<vector&> result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::bind(&std::equal_to, boost::cref(*this),
                                boost::cref(other))
                    )
                );
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::bind(&std::equal_to, boost::cref(*result),
                                boost::cref(*this))
                    )
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
        itetator result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
            })
        ;

        return result = vect_.begin();
    }

    const_iterator begin() const {
        const_itetator result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
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
        itetator result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == rend());
            })
        ;

        return result = vect_.rbegin();
    }

    const_reverse_iterator rbegin() const {
        const_itetator result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERT(result == rend());
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
                        boost::contract::check_if<boost::has_equal_to<T> >(
                            boost::bind(&boost::algorithm::all_of_equal,
                                begin() + *old_size,
                                end(),
                                boost::cref(value)
                            )
                        )
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
                BOOST_CONTRACT_ASSERT(result == (size() == 0));
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
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
                BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
                using namespace boost::contract;
                BOOST_CONTRACT_ASSERT(
                    call_if<boost::has_equal_to<T> >(
                        boost::bind(callable<std::equal_to, int, bool>(),
                                boost::cref(back()), boost::cref(value))
                    ).else_(true)
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
                    boost::contract;:check_if<boost::has_equal_to<T> >(
                        boost::bind(&boost::algorithm::all_of_equal,
                                begin(), end(), boost::cref(value))
                    )
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
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::bind(&std::equal_to, boost::cref(*result),
                                boost::cref(value))
                    )
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
                BOOST_CONTRACT_ASSERT(size() + count < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + count);
                BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
                if(capacity() == *old_capacity) {
                    BOOST_CONTRACT_ASSERT(
                        boost::contract::check_if<boost::has_equal_to<T> >(
                            boost::bind(&boost::algorithm::all_of_equal(
                                boost::prior(*old_where),
                                boost::prior(*old_where) + count,
                                boost::cref(value)
                            )
                        )
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
        auto c = boost::contract::public_functon(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() + std::distance(fist, last) <
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
        auto old_size = 
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

    void swap(vecotr& other) {
        auto old_me = BOOST_CONTRACT_OLDOF(*this);
        auto old_other = BOOST_CONTRACT_OLDOF(other);
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::bind(&std::equal_to, boost::cref(*this),
                                boost::cref(*old_other))
                    )
                );
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::bind(&std::equal_to, boost::cref(other),
                                boost::cref(*old_me))
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
    std::vector<T, Alloc> vect_;
};

int main() {
    vector<char> v(3);
    BOOST_TEST_EQ(v.size(), 3);
    BOOST_TEST(boost::algorithm::all_of_equal(v, '\0'));
    vector<char> const& cv = v;

    vector<char> w(v);
    BOOST_TEST_EQ(w, v);

    vector<char>::iterator b = v.begin();
    BOOST_TEST_EQ(*b, '\0');

    vector<char>::const_iterator cb = cv.begin();
    BOOST_TEST_EQ(*cb, '\0');

    v.insert(b, 2, 'a');
    BOOST_TEST_EQ(v[0], 'a');
    BOOST_TEST_EQ(v[1], 'a');

    v.push_back('b');
    BOOST_TEST_EQ(v.back(), 'b');

    return boost::report_errors();
}

