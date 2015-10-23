
#ifndef BOOST_CONTRACT_AUX_TEST_COUNTER_HPP_
#define BOOST_CONTRACT_AUX_TEST_COUNTER_HPP_

namespace boost { namespace contract { namespace aux { namespace test {

// Helper to count copies and evaluations of type (e.g., for old values).
template<class Tag, typename T>
struct counter {
    T value;

    counter() : value() { ++ctors_; }
    static unsigned ctors() { return ctors_; }

    ~counter() { ++dtors_; }
    static unsigned dtors() { return dtors_; }

    counter(counter const& other) : value(other.value) { ++copies_; ++ctors_; }
    static unsigned copies() { return copies_; }

    static counter const& eval(counter const& me) { ++me.evals_; return me; }
    static unsigned evals() { return evals_; }

private:
    counter& operator=(counter const&) /* = delete */;
    
    static unsigned ctors_; // Total constructions (including copies).
    static unsigned dtors_;
    static unsigned copies_;
    static unsigned evals_;
};

template<class Tag, typename T> unsigned counter<Tag, T>::ctors_ = 0;
template<class Tag, typename T> unsigned counter<Tag, T>::dtors_ = 0;
template<class Tag, typename T> unsigned counter<Tag, T>::copies_ = 0;
template<class Tag, typename T> unsigned counter<Tag, T>::evals_ = 0;
    
} } } } // namespace

#endif // #include guard

