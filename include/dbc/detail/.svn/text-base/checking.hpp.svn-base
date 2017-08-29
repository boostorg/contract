
#ifndef DBC_CHECKING_HPP_
#define DBC_CHECKING_HPP_

#include "threading/sync.hpp"

namespace dbc {

/** True iff is checking a contract within any object. */
/** @todo[LC] Does this effectivelly sync all objects within the systems since
 * it is a global lock? If there any way around this? This is required from a
 * DBC checking policy "assertions are (globally) disabled within 
 * assertions"... */
static sync_<bool, false> globally_checking_contract_;

} // namespace dbc

#endif // DBC_CHECKING_HPP_

