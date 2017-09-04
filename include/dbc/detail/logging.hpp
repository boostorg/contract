/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_LOG_HPP_
#define DBC_LOG_HPP_

#include "../config.hpp"
#include <sstream>

/** 
 * Print log message when equal or more verbose than LOG_LEVEL_VIOLATION.
 * @param code Declare loval variable "log" that can be set by specified code. 
 * Uses DBC_CONF_LOG_VIOLATION() to print log message.
 */
#define DBC_LOG_VIOLATION_(code) \
    if (::dbc::log_level_ >= ::dbc::LOG_LEVEL_VIOLATION) { \
        std::ostringstream log; \
        { code; } \
        DBC_CONFIG_LOG_VIOLATION(log.str().c_str()); \
    }

/** 
 * Print log message when equal or more verbose than LOG_LEVEL_DEBUG.
 * @param code Declare loval variable "log" that can be set by specified code. 
 * Uses DBC_CONF_LOG_DEBUG() to print log message.
 */
#define DBC_LOG_DEBUG_(code) \
    if (::dbc::log_level_ >= ::dbc::LOG_LEVEL_DEBUG) { \
        std::ostringstream log; \
        { code; } \
        DBC_CONFIG_LOG_DEBUG(log.str().c_str()); \
    }

namespace dbc {

enum log_level_type_ {
    // Level definition order and start from 0 matters (actual values don't).
    LOG_LEVEL_NONE      = DBC_LOG_LEVEL_NONE,
    LOG_LEVEL_VIOLATION = DBC_LOG_LEVEL_VIOLATION,
    LOG_LEVEL_DEBUG     = DBC_LOG_LEVEL_DEBUG,
    LOG_LEVEL_ALL       = DBC_LOG_LEVEL_ALL,
};

static log_level_type_ log_level_ = log_level_type_(DBC_CONFIG_LOG_LEVEL);

} // namespace dbc

#endif // DBC_LOG_HPP_

