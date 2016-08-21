
#ifndef BOOST_CONTRACT_DETAIL_CHECKING_HPP_
#define BOOST_CONTRACT_DETAIL_CHECKING_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/declspec.hpp>
#ifndef BOOST_CONTRACT_DISABLE_THREADS
    #include <boost/thread/mutex.hpp>
#endif
#include <boost/noncopyable.hpp>

namespace boost { namespace contract { namespace detail {

#ifdef BOOST_MSVC
    #pragma warning(push)
    #pragma warning(disable: 4251) // Member w/o DLL spec (mutex_ type).
#endif

// RAII facility to disable assertions while checking other assertions.
class BOOST_CONTRACT_DETAIL_DECLSPEC checking :
    private boost::noncopyable // Non-copyable resource (might use mutex, etc.).
{
public:
    explicit checking();
    ~checking();
    
    static bool already();

private:
    static bool checking_;
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        static boost::mutex mutex_;
    #endif
};

#ifdef BOOST_MSVC
    #pragma warning(pop)
#endif

} } } // namespace

/** @cond Needed because this header included by other public headers. */
#if BOOST_CONTRACT_HEADER_ONLY
    #include <boost/contract/detail/inlined/detail/check_guard.hpp>
#endif
/** @endcond */

#endif // #include guard

