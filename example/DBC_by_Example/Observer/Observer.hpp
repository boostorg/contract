/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <dbc.hpp>

/** Observer for "observer framework". */
class Observer DBC_INHERIT_OBJECT(Observer) {
public:
    // Creation //

    /** Constructor observer. */
    Observer(void)
    DBC_CONSTRUCTOR( (public) (Observer)( (void) ), {
    }, {
    }, {})

    /** Destroy observer. */
    virtual ~Observer(void)
    DBC_DESTRUCTOR( (public) (virtual) (Observer)( (void) ), {})

    // Commands //
    
    // The following commands could be made protected and Subject could
    // be made a friend. However, this will only work for compilers that
    // implement the fix to C++ standard defect allowing member class
    // full access to enclosing class (so here they are made public to
    // work with all compilers).

    /** If up to date with its subject. */
    virtual bool upToDateWithSubject(void) const
    DBC_MEM_FUN( (public) (virtual) (bool) (Observer) 
            (upToDateWithSubject)( (void) ) (const), {
    }, {
    }, = 0;)
    
    /** Bring this observer up to date with its subject. */
    virtual void update(void)
    DBC_MEM_FUN( (public) (virtual) (void) (Observer) (update)( (void) ), {
    }, {
        DBC_ASSERT(self.now.upToDateWithSubject(), "up-to-date with subject");
    }, = 0;)

private:
    DBC_INVARIANT(Observer, {})
};

#endif // OBSERVER_HPP_

