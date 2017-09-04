/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef SHAPES_HPP_
#define SHAPES_HPP_

#include <dbc.hpp>

class shape DBC_INHERIT_OBJECT(shape) {
    DBC_INVARIANT(shape, {})
public:
    virtual ~shape()
    DBC_DESTRUCTOR( (public) (virtual) (shape)( (void) ), {})

    virtual int compute_area(void) const
    DBC_MEM_FUN( (public) (virtual) (int) (shape)
            (compute_area)( (void) ) (const), {
    }, {
        DBC_ASSERT(result > 0, "returning positive area");
    }, = 0;) // Body "= 0;" for pure virtual (as done in C++).
};

class circle: public shape DBC_MULTI_INHERIT_OBJECT(circle) {
    DBC_INVARIANT(circle, {})
public:
    int radius(void) const
    DBC_MEM_FUN( (public) (int) (circle) (radius)( (void) ) (const), {
    }, {
    }, {
        return 10;
    })

    virtual int compute_area(void) const
    // Simply add DBC_BASE(base-class) to subcontract.
    DBC_MEM_FUN( (public) (virtual) (int) (circle)DBC_BASE(shape)
            (compute_area)( (void) ) (const), {
    }, {
        DBC_ASSERT(result == int(3.14) * self.now.radius() * self.now.radius(),
                "returning circle area");
    }, {
        return int(3.14) * radius() * radius();
    })
};

#endif // SHAPES_HPP_

