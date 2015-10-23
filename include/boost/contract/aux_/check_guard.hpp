
#ifndef BOOST_CONTRACT_AUX_CHECK_GUARD_HPP_
#define BOOST_CONTRACT_AUX_CHECK_GUARD_HPP_

namespace boost { namespace contract { namespace aux {

// TODO: Consider what to do with multi-threads... multi-reads/one-write locks
// via boost::shared_mutex? should each thread have each own contract checking
// bool resource?

struct check_guard {
    explicit check_guard() { checking_ = true; }
    ~check_guard() { checking_ = false; }
    
    static bool checking() { return checking_; }

private:
    static bool checking_;
};

// TODO: This state must go into a .cpp with dyn linking (for DLLs).
bool check_guard::checking_ = false;

} } } // namespace

#endif // #include guard

