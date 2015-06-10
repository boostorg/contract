
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/check/check_pre_post.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost {
    namespace contract {
        template<typename>
        class set_precondition_postcondition;
    }
}

namespace boost { namespace contract {
    
template<typename R = void>
class set_postcondition_only { // Copyable as shared * (OK also for RAII).
public:
    template<typename F>
    set_nothing postcondition(F const& f) {
        check_->set_post(f);
        return set_nothing(check_);
    }

private:
    typedef boost::shared_ptr<boost::contract::aux::check_pre_post<
            typename boost::contract::aux::none_if_void<R>::type> > check_ptr;

    explicit set_postcondition_only(check_ptr check) : check_(check) {}

    check_ptr check_;

    // Friendship used to limit library's public API.
    friend class guard;
    friend class set_precondition_postcondition<R>;

    template<class C>
    friend set_postcondition_only constructor(C*);

    template<class C>
    friend set_postcondition_only destructor(C*);
};

} } // namespace

#endif // #include guard

