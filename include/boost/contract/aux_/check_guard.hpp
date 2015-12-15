
#ifndef BOOST_CONTRACT_AUX_CHECK_GUARD_HPP_
#define BOOST_CONTRACT_AUX_CHECK_GUARD_HPP_

/** @cond */
#include <boost/noncopyable.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// TODO: Consider what to do with multi-threads... shall I use multi-reads/one-write locks via boost::shared_mutex? should each thread have its own contract checking bool resource? If global locks must be introduced, provide a NO_TREAD_SAFE configuration macro to disable them.

class check_guard :
    private boost::noncopyable // Non-copyable resource (might use mutex, etc.).
{
public:
    explicit check_guard() { checking_ = true; }
    ~check_guard() { checking_ = false; }
    
    static bool checking() { return checking_; }

private:
    static bool checking_;
};

// TODO: This and all other lib states must go into a .cpp with dyn linking (DLL). Also move as much as code as possible to .cpp files (and try to minimize template is not strictly necessary) so to speed up compilation.
bool check_guard::checking_ = false;

} } } // namespace

#endif // #include guard

