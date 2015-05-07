
#ifndef BOOST_CONTRACT_AUX_OLDOF_HPP_
#define BOOST_CONTRACT_AUX_OLDOF_HPP_

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract { namespace aux {

class oldof { // Must allow copies (shallow pointer copies).
public:
    oldof() : virt_(), value_() {} // Null value ptr when no oldof.

    explicit oldof(boost::contract::virtual_* const virt, oldof const& old) :
            virt_(virt), value_(old.value_) {}

    template<typename T>
    /* implicit */ oldof(T const& old_value) :
            value_(boost::make_shared<T>(old_value)) {} // One single copy of T.

    // Pointer so it can be null (for when no post) and shared because owned by
    // this lib for virtual calls (stored in v) but owned by user's stack value
    // for non-virtual calls (so shared ownership to handle both cases).
    template<typename T>
    operator boost::shared_ptr<T const>() {
        if(!virt_) {
            BOOST_CONTRACT_AUX_DEBUG(value_);
            boost::shared_ptr<T const> result = 
                    boost::static_pointer_cast<T const>(value_);
            BOOST_CONTRACT_AUX_DEBUG(result);
            return result;
        } else if(
            virt_->action_ == boost::contract::virtual_::user_call ||
            virt_->action_ == boost::contract::virtual_::copy_oldof
        ) {
            BOOST_CONTRACT_AUX_DEBUG(value_);
            virt_->old_values_.push(value_);
            std::clog << "pushed" << std::endl;
            return boost::shared_ptr<T const>();
        } else if(
            virt_->action_ == boost::contract::virtual_::check_post ||
            virt_->action_ == boost::contract::virtual_::check_this_post
        ) {
            BOOST_CONTRACT_AUX_DEBUG(!value_);
            boost::shared_ptr<void> value = virt_->old_values_.front();
            virt_->old_values_.pop();
            std::clog << "popped" << std::endl;
            BOOST_CONTRACT_AUX_DEBUG(value);
            boost::shared_ptr<T const> result = 
                    boost::static_pointer_cast<T const>(value);
            BOOST_CONTRACT_AUX_DEBUG(result);
            return result;
        }
        BOOST_CONTRACT_AUX_DEBUG(!value_);
        return boost::shared_ptr<T>();
    }

private:
    boost::contract::virtual_* virt_;
    boost::shared_ptr<void> value_; // Type erased to `void*`.
};

} } } // namespace

#endif // #include guard

