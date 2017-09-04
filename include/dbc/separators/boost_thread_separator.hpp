/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under Eiffel for C++ Software License.
 */

#ifndef DBC_BOOST_THREAD_SEPARATOR_HPP_
#define DBC_BOOST_THREAD_SEPARATOR_HPP_

#include "../detail/logging.hpp"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <queue>

namespace dbc {

/** @todo[LC] Check this class for thread-safety! This is the only code
 * executed by multiple threads -- the separated thread (created here) and
 * the caller thread. */
class boost_thread_separator: boost::noncopyable {
public:
    class recursive_scoped_lock {
    public:
        recursive_scoped_lock(boost_thread_separator& separator):
                lock_(separator.mutex_) {}
        // Destructor will unlock.
    private:
        boost::recursive_mutex::scoped_lock lock_;
    };
    
    boost_thread_separator(): destroying_(false), thread_(), async_calls_() {}
    
    virtual ~boost_thread_separator() {
        destroying_ = true; // Notify thread to finish.
        if (thread_) {
            DBC_LOG_DEBUG_(log << "Separator " << this
                    << ": Stopping separate thread " << thread_);
            thread_.get()->join();
        }
    }
    
    void async(const boost::function0<void>& f) {
        async_calls_.push(f);
        DBC_LOG_DEBUG_(log << "Separator " << this
                << ": User thread scheduling asynchronous call "
                << &(async_calls_.front()));
        if (!thread_) { start(); } // Start th only if async call pending.
    }

    template<typename R>
    R sync(const boost::function0<R>& f) {
        // All ops are mutually exclusive.
        // Here we lock when executing an sync op.
        boost::recursive_mutex::scoped_lock lock(mutex_);
        DBC_LOG_DEBUG_(log << "Separator " << this
                << ": User thread executing synchronous call " << &f);
        return f();
    } // Unlock mutex.

private:
    void start() {
        boost::function0<void> threadEntry =
                boost::bind(&boost_thread_separator::run, this);
        thread_ = boost::shared_ptr<boost::thread>(
                new boost::thread(threadEntry));
        DBC_LOG_DEBUG_(log << "Separator " << this
                << ": Swapped separate thread " << thread_);
    }

    void run() {
        // If destroying, th still runs until all async calls completed
        // (plus new async calls requested while destroying are accepted
        // and must be completed too).
        while (!destroying_ || !async_calls_.empty()) {
            if (!async_calls_.empty()) {
                boost::function0<void> f(async_calls_.front());
                // This pointer is for logging only! Use copied f obj instead! 
                boost::function0<void>* p = &(async_calls_.front());
                async_calls_.pop();
                {
                    // All ops are mutually exclusive.
                    // Here We lock when executing an async ops.
                    boost::recursive_mutex::scoped_lock lock(mutex_);
                    DBC_LOG_DEBUG_(log << "Separator " << this << ": Separate "
                            << "thread executing asynchronous call " << p);
                    f();
                } // Unlock mutex.
            }
            /** @todo[LC] Shall I sleep/wait here? Are resources starved
             * if I don't? I should "wait until async_calls_ not empty" to
             * be exact.. */
        }
    }

    boost::recursive_mutex mutex_;
    bool destroying_;
    boost::shared_ptr<boost::thread> thread_;
    std::queue<boost::function0<void> > async_calls_;
};

} // namespace dbc

#endif // DBC_BOOST_THREAD_SEPARATOR_HPP_

