
#ifndef BOOST_CONTRACT_TYPE_HPP_
#define BOOST_CONTRACT_TYPE_HPP_

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

class type { // This can be copied (as shallow smart pointer copy).
public:
    explicit type(boost::shared_ptr<type> const self) : self_(self) {}

    virtual ~type() {}

    // TODO: Following should return special types so user cannot set pre/post
    // multiple times.

    template<typename Precondition>
    type& precondition(Precondition const f) {
        self_->pre_ = f;
        self_->pre_available();
        return *this;
    }

    template<typename Postcondition>
    type& postcondition(Postcondition const f) {
        self_->post_ = f;
        self_->post_available();
        return *this;
    }
    
protected:
    type() {}

    virtual void pre_available() {} // Called when pre functor is set.
    virtual void post_available() {} // Called when post functor is set.
    
    boost::function<void ()> pre_;
    boost::function<void ()> post_;

private:
    boost::shared_ptr<type> self_;
};

} } // namespace

#endif // #include guard

