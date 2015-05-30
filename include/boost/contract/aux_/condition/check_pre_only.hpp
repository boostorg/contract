
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_ONLY_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_ONLY_HPP_

#include <boost/contract/core/exception.hpp>
/** @cond */
#include <boost/function.hpp> // TODO: Can I reduce boost.function overhead?
/** @endcond */

namespace boost { namespace contract { namespace aux {

// Also used as base to hold all contract objects for RAII.
class check_pre_only {
public:
    explicit check_pre_only(boost::contract::from from) : from_(from) {}

    virtual ~check_pre_only() {}
    
    template<typename F>
    void set_pre(F const& f) { pre_ = f; pre_available(); }

protected:
    void check_pre(bool throw_on_failure = false) {
        if(pre_) {
            try { pre_(); }
            catch(...) {
                // Subcontracted pre must throw on failure (instead of
                // calling failure handler) so to be checked in logic-or.
                if(throw_on_failure) throw;
                boost::contract::precondition_failed(from());
            }
        }
    }
    
    virtual void pre_available() {}

    boost::contract::from from() const { return from_; }

private:
    boost::contract::from from_;
    boost::function<void ()> pre_;
};

} } } // namespace

#endif // #include guard

