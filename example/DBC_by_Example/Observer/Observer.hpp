/* $Id$ */

#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <dbc.hpp>

/** Observer for "observer framework". */
class Observer DBC_INHERIT_OBJECT(Observer) {
    friend class Subject; // Subject invokes update().
public:
    // Creation //

    /** Constructor observer. */
    Observer()
    DBC_CONSTRUCTOR( (public) (Observer)(), {
    }, {
    }, {})

    /** Destroy observer. */
    virtual ~Observer()
    DBC_DESTRUCTOR( (public) (virtual) (Observer)(), {})

protected:
    // Commands //

    /** If up to date with its subject. */
    virtual bool upToDateWithSubject() const
    DBC_MEM_FUN( (protected) (virtual) (bool) (Observer) 
            (upToDateWithSubject)() (const), {
    }, {
    }, = 0;)
    
    /** Bring this observer up to date with its subject. */
    virtual void update()
    DBC_MEM_FUN( (protected) (virtual) (void) (Observer) (update)(), {
    }, {
        DBC_ASSERT(self.now.upToDateWithSubject(), "up-to-date with subject");
    }, = 0;)

private:
    DBC_INVARIANT(Observer, {})
};

#endif // OBSERVER_HPP_

