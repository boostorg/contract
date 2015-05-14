
#ifndef BOOST_CONTRACT_AUX_TEST_OLD_HPP_
#define BOOST_CONTRACT_AUX_TEST_OLD_HPP_

namespace boost { namespace contract { namespace aux { namespace test {

// Helper to test old values only evaluated and copied once by OLDOF.
template<class Tag, typename T>
struct old {
    T value;
    old() : value() {}

    old(old const& other) : value(other.value) { ++copies_; }
    static old const& eval(old const& me) { ++me.evals_; return me; }

    static unsigned copies() { return copies_; }
    static unsigned evals() { return evals_; }

private:
    old& operator=(old const&) /* = delete */;
    
    static unsigned copies_;
    static unsigned evals_;
};

template<class Tag, typename T> unsigned old<Tag, T>::copies_ = 0;
template<class Tag, typename T> unsigned old<Tag, T>::evals_ = 0;
    
} } } } // namespace

#endif // #include guard

