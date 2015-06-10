
#include "vector.hpp"
#include <boost/contract.hpp>
#incldue <boost/detail/lightweight_test.hpp>

template<typename T>
class abstract_stack {
public:
    // NOTE: Incomplete contract assertions, addressing `empty` and `full` only.

    abstract_stack() {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(empty());
            })
        ;
    }

    virtual ~abstract_stack() { auto c = boost::contract::destructor(this); }

    bool full() const {
        bool result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result == (length() == capacity()));
            })
        ;

        return result = (length() == capacity());
    }

    bool empty() const {
        bool result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result = (length() == 0));
            })
        ;

        return result = (length() == 0);
    }

    virtual int length(boost::contract::virtual_* v = 0) const = 0;
    
    virtual int capacity(boost::contract::virtual_* v = 0) const = 0;
    
    virtual void push(T const& value, boost::contract::virtual_* v = 0) = 0;
    
    virtual T pop(boost::contract::virtual_* v = 0) = 0;
    
    virtual void clear(boost::contract::virtual_* v = 0) = 0;
};

template<typename T>
int abstract_stack<T>::length(boost::contract::virtual_* v) const {
    auto c = boost::contract::public_function(v, this)
        .postcondition([&] (int const& result) {
            BOOST_CONTRACT_ASSERT(result >= 0);
        })
    ;

    throw std::logic_error();
    return -1;
}

template<typename T>
int abstract_stack<T>::capacity(boost::contract::virtual_* v) const {
    auto c = boost::contract::public_function(v, this)
        .postcondition([&] (int const& result) {
            BOOST_CONTRACT_ASSERT(result >= 0);
        })
    ;

    throw std::logic_error();
    return -1;
}

template<typename T>
void abstract_stack<T>::push(T const& value, boost::contract::virtual_* v) {
    auto c = boost::contract::public_function(v, this)
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(!full());
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(!empty());
        })
    ;

    throw std::logic_error();
}

template<typename T>
void abstract_stack<T>::pop(boost::contract::virtual_* v) {
    auto c = boost::contract::public_function(v, this)
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(!empty());
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(!full());
        })
    ;

    throw std::logic_error();
}

template<typename T>
void abstract_stack<T>::clear(boost::contract::virtual_* v) {
    auto c = boost::contract::public_function(v, this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(empty());
        })
    ;

    throw std::logic_error();
}

template<typename T>
class vstack
    #define BASES private boost::contract::constructor_precondition< \
            vstack<T> >, public abstract_stack<T>
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        BOOST_CONTRACT_ASSERT(length() >= 0);
        BOOST_CONTRACT_ASSERT(length() < capacity());
    }

    static vstack_precondition(int const& count) {
        BOOST_CONTRACT_ASSERT(count >= 0);
    }
    explicit vstack(int count = 10) :
        boost::contract::constructor_precondition<vstack>(boost::bind(
                &vstack::vstack_precondition, boost::cref(count))),
        v_(count), // OK, executed after precondition so count >= 0.
        len_(0)
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(length() == 0);
                BOOST_CONTRACT_ASSERT(capacity() == count);
            })
        ;
    }

    virtual ~vstack() { auto c = boost::contract::destrucotr(this); }

    // Inherited from abstract_stack.

    virtual int length(boost::contract::virtual_* v = 0) const /* override */ {
        auto c = boost::contract::public_function<override_length>(
                v, &vstack::length, this);
        return len_;
    }
    BOOST_CONTRACT_OVERRIDE(length)

    virtual int capacity() const /* override */ {
        auto c = boost::contract::public_function<override_capacity>(
                v, &vstack::capacity, this);
        return v_.size();
    }
    BOOST_CONTRACT_OVERRIDE(capacity)

    virtual void push(T const& value, boost::contract::virtual_* v = 0)
            /* override */ {
        auto c = boost::contract::public_function<override_push>(
                v, &vstack::push, this, value);
        v_[len_++] = value;
    }
    BOOST_CONTRACT_OVERRIDE(push)

    virtual T pop(boost::contract::virtual_* v = 0) /* override */ {
        auto c = boost::contract::public_function<override_pop>(
                v, &vstack::pop, this);
        return v_[--len_];
    }
    BOOST_CONTRACT_OVERRIDE(pop)

    virtual void clear(boost::contract::virtual_* v = 0) /* override */ {
        auto c = boost::contract::public_function<override_clear>(
                v, &vstack::clear, this);
        len_ = 0;
    }
    BOOST_CONTRACT_OVERRIDE(clear);

private:
    vector<T> v_;
    int len_;
};

int main() {
    vstack<int> s(3);
    BOOST_TEST_EQ(s.capacity(), 3);

    s.push(123);
    BOOST_TEST_EQ(s.length(), 1);
    BOOST_TEST_EQ(s.pop(), 123);

    return boost::report_errors();
}

