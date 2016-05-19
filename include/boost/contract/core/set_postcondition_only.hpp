
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Allow to specify postconditions.
*/

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/core/config.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/condition/check_pre_post.hpp>
    #include <boost/contract/detail/auto_ptr.hpp>
    #include <boost/contract/detail/none.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/contract/detail/debug.hpp>
#endif
#include <boost/config.hpp>

namespace boost {
    namespace contract {
        template<typename RR>
        class set_precondition_old_postcondition;
        
        template<typename RR>
        class set_old_postcondition;
    }
}

namespace boost { namespace contract {

/**
Allow to specify postconditions.
Allow to program functors this library will call to check postconditions.
@tparam R   Return type of the function being contracted if that function is a
            non-void virtual or overriding public function, otherwise this is
            always @c void.
@see @RefSect{tutorial, Tutorial}, @RefSect{advanced_topics, Advances Topics}.
*/
template<typename R = void>
class set_postcondition_only { // Copyable (as *).
public:
    /** Destruct this object. */
    ~set_postcondition_only() BOOST_NOEXCEPT_IF(false) {}

    /**
    Allow to specify postconditions.
    @param f    Functor called by this library to check postconditions. Any
                exception thrown by a call to this functor indicates a
                postcondition failure. Assertions within this functor are
                usually programmed using @RefMacro{BOOST_CONTRACT_ASSERT}. This
                functor must be a nullary functor if @c R is @c void, otherwise
                it must be unary functor taking the return value as a parameter
                of type <c>R const&</c> (to avoid extra copies, or @c R and also
                <c>R const</c> if extra copies of the return value are
                irrelevant). This functor should capture variables by
                (constant) reference.
    @return After postconditions have been specified, return object that does
            not allow to specify any additional contract (i.e., set nothing).
    */
    template<typename F>
    set_nothing postcondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_post(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return set_nothing(check_.release());
        #else
            return set_nothing();
        #endif
    }

/** @cond */
private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::detail::check_pre_post<typename
                boost::contract::detail::none_if_void<R>::type> check_type;

        explicit set_postcondition_only(check_type* check) : check_(check) {}
        
        boost::contract::detail::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).

    friend class guard;

    friend class set_precondition_old_postcondition<R>;
    
    friend class set_old_postcondition<R>;
/** @endcond */
};

} } // namespace

#endif // #include guard

