
#ifndef BOOST_CONTRACT_AUX_INLINED_AUX_CHECK_GUARD_HPP_
#define BOOST_CONTRACT_AUX_INLINED_AUX_CHECK_GUARD_HPP_

#include <boost/contract/aux_/check_guard.hpp>

namespace boost { namespace contract { namespace aux {

check_guard::check_guard() { checking_ = true; }

check_guard::~check_guard() { checking_ = false; }

bool check_guard::checking() { return checking_; }

bool check_guard::checking_ = false;

} } } // namespace

#endif

