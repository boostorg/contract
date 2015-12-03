
#ifndef BOOST_CONTRACT_AUX_AUTO_PTR_HPP_
#define BOOST_CONTRACT_AUX_AUTO_PTR_HPP_

#include <boost/contract/aux_/operator_safe_bool.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/config.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// Using this instead of std::auto_ptr because std::auto_ptr will be removed in
// C++17 (this library always uses release() to avoid ownership issues).
template<typename T>
class auto_ptr {
public:
    explicit auto_ptr(T* ptr = 0) : ptr_(ptr) {}

    ~auto_ptr() BOOST_NOEXCEPT_IF(false) { delete ptr_; }

    T* release() {
        T* ptr = ptr_;
        ptr_ = 0;
        return ptr;
    }

    T& operator*() { BOOST_CONTRACT_AUX_DEBUG(ptr_); return *ptr_; }
    T const& operator*() const { BOOST_CONTRACT_AUX_DEBUG(ptr_); return *ptr_; }

    T* operator->() { return ptr_; }
    T const* operator->() const { return ptr_; }

    BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL(auto_ptr<T>, !!ptr_)

private:
    T* ptr_;
};

} } } // namespace

#endif // #include guard

