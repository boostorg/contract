/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_LOOP_HPP_
#define DBC_LOOP_HPP_

#include "detail/pp/defines.hpp" // Must be 1st include.

#ifdef DBC

#include "assertion.hpp"
#include "detail/logging.hpp"
#include <limits>
#include <string>

namespace dbc {

class loop {
protected:
    inline void run(const char* file = "", const int& line = 0) {
#ifdef DBC_CHECK_LOOP
        unsigned int old_var = std::numeric_limits<unsigned int>::quiet_NaN();
        unsigned int count = 1;
        check_invariant(count);
        old_var = check_variant(old_var, count, file, line);
#endif // DBC_CHECK_LOOP
        
        while (!until()) {
            body();

#ifdef DBC_CHECK_LOOP
            check_invariant(count);
            old_var = check_variant(old_var, count, file, line);
            ++count;
#endif // DBC_CHECK_LOOP

        } // while()
    }

    inline virtual void invariant() {}
    
    /**
     * @return If std::numeric_limits<unsgined int>::quiet_NaN() is returned,
     *  the variant has no effect (the variant condition will always be true). 
     */
    inline virtual unsigned int variant() 
        { return std::numeric_limits<unsigned int>::quiet_NaN(); }
    
    virtual bool until() = 0;
    
    virtual void body() = 0;
    
private:
    unsigned int check_variant(const unsigned int& old_variant,
            const unsigned int& count, const char* file, const int& line) {
        unsigned int var = variant();
        try {
            if (std::numeric_limits<unsigned int>::quiet_NaN() != var && 
                    std::numeric_limits<unsigned int>::quiet_NaN() 
                    != old_variant) {
                bool var_violated = var < old_variant; // Must not decrease.
                if (!var_violated || log_level_ >= LOG_LEVEL_VIOLATION) {
                    oassertionstream oas(var_violated, 
                        "not-decreasing variant", file, line, "");
                    oas << "variant " << var << " decreased from " 
                            << old_variant << raise<>();
                }
            }
        } catch (condition_violation& ex) {
            std::ostringstream oss;
            oss << ex.what() << " (iteration #" << count << ")";
            throw variant_violation(oss.str());
        }
        return var;
    }
    
    void check_invariant(const unsigned int& count) {
        try { invariant(); }
        catch (condition_violation& ex) {
            std::ostringstream oss;
            oss << ex.what() << " (iteration #" << count << ")";
            throw invariant_violation(oss.str());
        }
    }
};

} // namespace dbc

#endif // DBC

#endif // DBC_LOOP_HPP_

