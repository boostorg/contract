/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef PUSH_BUTTON_HPP_
#define PUSH_BUTTON_HPP_

/** A button. */
class PushButton {
public:
    // Creation //

    /** Create button. */
    PushButton(): enabled_(true) {}

    /** Invoked by external event handler when this button has been clicked. */
    virtual void onBnClicked() = 0;

    /** If button enabled. */
    bool enabled() const { return enabled_; }
    /** Enable this button. */
    void enable() { enabled_ = true; }
    /** Disable this button. */
    void disable() { enabled_ = false; }

private:
    bool enabled_;
};

#endif // PUSH_BUTTON_HPP_

