
#ifndef BOOST_CONTRACT_AUX_TEST_CPCNT_HPP_
#define BOOST_CONTRACT_AUX_TEST_CPCNT_HPP_

namespace boost { namespace contract { namespace aux { namespace test {

// Helper to count copies and evaluations of type (e.g., for old values).
template<class Tag, typename T>
struct cpcnt {
    T value;
    cpcnt() : value() {}

    cpcnt(cpcnt const& other) : value(other.value) { ++copies_; }
    static cpcnt const& eval(cpcnt const& me) { ++me.evals_; return me; }

    static unsigned copies() { return copies_; }
    static unsigned evals() { return evals_; }

private:
    cpcnt& operator=(cpcnt const&) /* = delete */;
    
    static unsigned copies_;
    static unsigned evals_;
};

template<class Tag, typename T> unsigned cpcnt<Tag, T>::copies_ = 0;
template<class Tag, typename T> unsigned cpcnt<Tag, T>::evals_ = 0;
    
} } } } // namespace

#endif // #include guard

