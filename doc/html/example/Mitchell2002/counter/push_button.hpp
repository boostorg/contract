// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef PUSH_BUTTON_HPP_
#define PUSH_BUTTON_HPP_

#include <contract.hpp>

/** Basic button. */
class push_button {

    CONTRACT_INVARIANT( ({}) )

public:
    // Creation //

    /** Create button. */
    push_button(void): enabled_(true)
    CONTRACT_CONSTRUCTOR( (class) (push_button)
            (public) (push_button)( (void) )
    (body) ({
    }) )

    virtual ~push_button(void)
    CONTRACT_DESTRUCTOR( (class) (push_button)
            (public) (virtual) (push_button)( (void) )
    (body) ({
    }) )

    // Queries //
    
    /** If button enabled. */
    bool enabled(void) const
    CONTRACT_FUNCTION( (class) (push_button)
            (public) (bool) (enabled)( (void) ) (const)
    (body) ({
        return enabled_;
    }) )

    // Commands //

    /** Enable this button. */
    void enable(void)
    CONTRACT_FUNCTION( (class) (push_button)
            (public) (void) (enable)( (void) )
    (postcondition) ({
        CONTRACT_ASSERT( enabled() );
    })
    (body) ({
        enabled_ = true;
    }) )

    /** Disable this button. */
    void disable(void)
    CONTRACT_FUNCTION( (class) (push_button)
            (public) (void) (disable)( (void) )
    (postcondition) ({
        CONTRACT_ASSERT( !enabled() );
    })
    (body) ({
        enabled_ = false;
    }) )

    /** Invoked externally when this button is clicked. */
    virtual void on_bn_clicked(void)
    CONTRACT_FUNCTION( (class) (push_button)
            (public) (virtual) (void) (on_bn_clicked)( (void) )
    (body) (
        = 0;
    ) )

private:
    bool enabled_;
};

#endif // #include guard

