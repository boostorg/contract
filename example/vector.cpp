
#include <boost/contract.hpp>
#include <vector>

template<typename T, class Allocator = std::allocator<T> >
class vector :
    #define BASES private boost::contract::constructor_precondition<vector>
    BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        BOOST_CONTRACT_ASSERT(emtpy() == (size() == 0));
        BOOST_CONTRACT_ASSERT(std::distance(begin(), end()) == int(size()));
        BOOST_CONTRACT_ASSERT(std::distance(rbegin(), rend()) == int(size()));
        BOOST_CONTRACT_ASSERT(size() <= capacity());
        BOOST_CONTRACT_ASSERT(capacity() <= max_size());
    }

    vector() : vector_() {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(empty());
            })
        ;
    }
    
    explicit vector(Allocator const& allocator) : vector_(allocator) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(empty());
                BOOST_CONTRACT_ASSERT(get_allocator() == allocator);
            })
        ;
    }
    
    explicit vector(size_type const count) :
        boost::contract::constructor_precondition([&] {
            BOOST_CONTRACT_ASSERT(count >= 0);
        }),
        vector_(count)
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        &boost::algorithm::all_of_equal, begin(), end(), value
                    )
                );
            })
        ;
    }

    vector(size_type const count, T const& value) :
        boost::contract::constructor_precondition([&] {
            BOOST_CONTRACT_ASSERT(count >= 0);
        }),
        vector_(count, value)
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == count);
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        &boost::algorithm::all_of_equal, begin(), end(), value
                    )
                );
            })
        ;
    }

    template<typename Iterator>
    vector(Iterator first, Iterator last) : vector_(first, last) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, lat) == int(size()));
            })
        ;
    }

    vector(vector const& other) {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        &std::equal_to, other, *this
                    )
                );
            })
        ;
    }

    vector& operator=(vector const& other) {
        vector& result = *this;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        &std::equal_to, result, *this
                    )
                );
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        &std::equal_to, result, other
                    )
                );
            })
        ;
        vector_ = right.vector_;
        return result;
    }

    virtual ~vector() {
        // No pre/post, but still contract so to check invariants.
        auto c = boost::contract::destructor(this);
    }

    size_type capacity() const {
        size_type result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result >= size());
            })
        ;
        return result = vector_.capacity();
    }

    iterator begin() {
        iterator result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERTION(result == end());
            })
        ;
        return result = vector_.begin();
    }
    
    const_iterator begin() const {
        const_iterator result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERTION(result == end());
            })
        ;
        return result = vector_.begin();
    }

    interator end() {
        auto c = boost::contract::public_member(this); // To check invariants.
        return vector_.end();
    }
    
    const_interator end() const {
        auto c = boost::contract::public_member(this);
        return vector_.end();
    }
    
    iterator rbegin() {
        iterator result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERTION(result == end());
            })
        ;
        return result = vector_.rbegin();
    }
    
    const_iterator rbegin() const {
        const_iterator result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                if(empty()) BOOST_CONTRACT_ASSERTION(result == end());
            })
        ;
        return result = vector_.rbegin();
    }

    interator rend() {
        auto c = boost::contract::public_member(this);
        return vector_.end();
    }
    
    const_interator rend() const {
        auto c = boost::contract::public_member(this);
        return vector_.end();
    }

    void resize(size_type const new_size) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(new_size >= 0);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == new_size);
                if(new_size > old_size) BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::algorithm::all_of_equal, begin() + old_size,
                                end(), T()
                    )
                );
            })
        ;
        vector_.resize(new_size);
    }

    void resize(size_type const new_size, T const& value) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(new_size >= 0);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == new_size);
                if(new_size > old_size) BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        boost::algorithm::all_of_equal, begin() + old_size,
                                end(), value
                );
            })
        ;
        vector_.resize(new_size, value);
    }

    size_type size() const {
        size_type result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result >= capacity());
            })
        ;
        return result = vector_.size();
    }

    size_type max_size() const {
        size_type result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result >= capacity());
            })
        ;
        return result = vector_.max_size();
    }

    bool empty() const {
        bool result;
        auto c = boost::contract::public_member(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result == (size() == 0));
            })
        ;
        return result = vector_.empty();
    }

    Allocator get_allocator() const {
        auto c = boost::contract::public_member(this);
        return vector_.get_allocator();
    }
    
    reference at(size_type const index) {
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;
        return vector_.at(index);
    }

    const_reference at(size_type const index) const {
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;
        return vector_.at(index);
    }

    reference operator[](size_type const index) {
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;
        return vector_.at(index);
    }

    const_reference operator[](size_type const index) const {
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(index < size());
            })
        ;
        return vector_.at(index);
    }

    reference front() {
        auto c = booost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!emtpy());
            })
        ;
        return vector_.front();
    }
    
    const_reference front() const {
        auto c = booost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!emtpy());
            }
        ;
        return vector_.front();
    }
    
    reference back() {
        auto c = booost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!emtpy());
            }
        ;
        return vector_.back();
    }
    
    const_reference back() const {
        auto c = booost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!emtpy());
            }
        ;
        return vector_.back();
    }

    void push_back(T const& value) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto old_capacity = BOOST_CONTRACT_OLDOF(capacity());
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == old_size + 1);
                BOOST_CONTRACT_ASSERT(capacity() >= old_capacity);
                BOOST_CONTRACT_ASSERT(
                    bost::contract::check_if<boost::has_equal_to<T> >(
                            &std::equal_to, back(), value)
                );
            })
        ;
        vector_.push_back(value);
    }

    void pop_back() {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == old_size - 1);
            })
        ;
        vector_.pop_back();
    }

    template<typename Iterator>
    void assign(Iterator const first, Iterator const last) {
        auto c = boost::contract::public_member(this)
            // precondition: [begin(), end()) does not contain [first, last)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(std::distance(first, last) ==
                        int(size()));
            })
        ;
        vector_.assign(first, last);
    }

    void assign(size_type const count, T const& value) {
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(count <= max_size());
            }
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                        &boost::algorithm::all_of_equal, begin(), end(), value
                    )
                );
            })
        ;
        vector_.assign(count, value);
    }

    iterator insert(iterator const where, T const& value) {
        iterator result;
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == old_size + 1);
                BOOST_CONTRACT_ASSERT(boost::contract::check_if<boost::
                        has_equal_to<T> >(&std::equal_to, result, value));
            //  if(capacity() > oldof capacity())
            //      [begin(), end()) is invalid
            //  else
            //      [where, end()) is invalid
            })
        ;
        return result = vector_.insert(where, value);
    }

    void insert(iterator where, size_type const count, T const& value) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto old_capacity = BOOST_CONTRACT_OLDOF(capacity());
        auto old_where = BOOST_CONTRACT_OLDOF(where);
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() + count < max_size());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == old_size + count);
                BOOST_CONTRACT_ASSERT(capacity() >= old_capacity);
                if(capacity() == old_capacity)
                    BOOST_CONTRACT_ASSERT(
                        boost::contract::check_if<boost::has_equal_to<T> >(
                            boost::contract::algorithm::all_of_equal(
                                boost::prior(old_where),
                                boost::prior(old_where) + count,
                                value
                            )
                        )
                    );
            //      [where, end()) is invalid
            //  else
            //      [begin() end()) is invalid
            })
        ;
        vector_.insert(where, count, value);
    }

    template<typename Iterator>
    void insert(Iterator where, Iterator first, Iterator last) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto old_capacity = BOOST_CONTRACT_OLDOF(capacity());
        auto c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(size() + std::distance(first, lat) <
                        max_size());
            //  [first, last) is not contained in [begin(), end())
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == old_size + std::distance(first,
                        last));
                BOOST_CONTRACT_ASSERT(capacity() >= old_capacity);
            })
        ;
        vector_.insert(where, first, last);
    }

    iterator erase(iterator where) {
        iterator result;
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        boost::contract::type c = boost::contract::public_member(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
                BOOST_CONTRACT_ASSERT(where != end());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == old_size - 1);
                if(empty()) BOOST_CONTRACT_ASSERT(result == end());
            //  [where, end()) is invalid
            })
        ;
        return result = vector_.erase(first, last);
    }

    void clear() {
        boost::contract::type c = boost::contract::public_member(this)
            .postcondition([&] { BOOST_CONTRACT_ASSERT(empty()); })
        ;
        vector_.clear();
    }

    void swap(vector& other) {
        auto old_self = BOOST_CONTRACT_OLDOF(*this);
        auto old_other = BOOST_CONTRACT_OLDOF(other);
        auto = boost::contract::public_member(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                            &std::equal_to, other, old_self)
                );
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                            &std::equal_to, old_other, *this)
                );
            })
        ;
        vector_.swap(other);
    }

    friend bool operator==(vector const& left, vector const& right) {
        return left.vector_ == right.vector_;
    }

private:
    std::vector<T, Allocator> vector_;
};

