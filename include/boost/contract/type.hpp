
#ifndef BOOST_CONTRACT_TYPE_HPP_
#define BOOST_CONTRACT_TYPE_HPP_

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

class type {
public:
    explicit type ( boost::shared_ptr<type> const self ) : self_(self) {}

    virtual ~type ( ) {}

    // TODO: Following should return special types so user cannot set pre/post
    // multiple times.

    template< typename Pre >
    type& precondition ( Pre const pre ) {
        self_->pre_ = pre;
        self_->pre_available();
        return *this;
    }

    template< typename Post >
    type& postcondition ( Post const post ) {
        self_->post_ = post;
        self_->post_available();
        return *this;
    }
    
protected:
    type ( ) {}

    virtual void pre_available ( ) {}
    virtual void post_available ( ) {}
    
    boost::function<void ( )> pre_;
    boost::function<void ( )> post_;

private:
    boost::shared_ptr<type> self_;
};

} } // namespace

#endif // #include guard

