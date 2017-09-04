/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under Eiffel for C++ Software License.
 */

#ifndef DBC_PROCESS_HPP_
#define DBC_PROCESS_HPP_

namespace dbc {

class process {
public:
    process(): over_(false) {}
    
    virtual void setup() {}
    virtual void step() = 0;
    virtual void wrapup() {}
    
    bool over() const { return over_; }
    bool over(const bool& over) { return over_ = over; }

    void operator()() { live(); }
    
    virtual void live() {
        setup();
        while (!over()) { step(); }
        wrapup();
    }

private:
    bool over_;
};

} // namespace dbc

#endif // DBC_PROCESS_HPP_

