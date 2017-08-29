/* $Id$ */

#ifndef SUBJECT_HPP_
#define SUBJECT_HPP_

#include "Observer.hpp"
#include <dbc.hpp>
#include <list>
#include <algorithm>

/** Subject for "observer framework". */
class Subject DBC_INHERIT_OBJECT(Subject) {
public:
    // Creation //

    /** Construct subject. */
    Subject()
    DBC_CONSTRUCTOR( (public) (Subject)(), {
    }, {
    }, {})

    virtual ~Subject()
    DBC_DESTRUCTOR( (public) (virtual) (Subject)(), {})

    // Queries //

    /** If specified observer is attached. */
    bool attached(const Observer* o) const 
    DBC_MEM_FUN( (public) (bool) (Subject) 
            (attached)( (const Observer*)(o) ) (const), {
    }, {
        const std::list<const Observer*>& os = self.now.observers();
        DBC_ASSERT(
                result == (os.end() != std::find(os.begin(), os.end(), o.now)),
                "result consistent with observers");
    }, {
        return observers_.end() != std::find(observers_.begin(), 
                observers_.end(), o);
    })

    // Commands //

    /** Remember specified object as on of this subject's observers. */
    void attach(Observer* o)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(Subject)
            (attach)( DBC_COPYABLE(Observer*)(o) ), {
        DBC_ASSERT(o, "observer exists");
        DBC_ASSERT_STREAM(!self.attached(o),  "not alreayd attached",
                err << "observer " << o << " alreayd attached");
    }, {
        DBC_ASSERT_STREAM(self.now.attached(o.now), "attached",
                err << "observer " << o.now << " not attached");

        // Frame rule (could be written more compactly...).
        std::list<const Observer*> oldOs = self.old.observers();
        std::list<const Observer*> os = self.now.observers();
        std::remove(os.begin(), os.end(), o.old);
        std::list<const Observer*>::iterator oIt = os.begin();
        std::list<const Observer*>::iterator oldOIt = oldOs.begin();
        while (os.end() != oIt && oldOs.end() != oldOIt) {
            DBC_ASSERT_STREAM(*oIt == *oldOIt, "all other observers unchanged",
                    err << "observer " << *oIt << " changed from "
                    << *oldOIt);
            ++oIt;
            ++oldOIt;
        }
    }, {
        observers_.push_back(o);
    })

protected:
    /** Update all attached observers. */
    void notify()
    DBC_MEM_FUN( (protected) (void) (Subject) (notify)(), {
    }, {
        const std::list<const Observer*>& os = self.now.observers();
        for (std::list<const Observer*>::const_iterator i = os.begin();
                os.end() != i; ++i) {
            const Observer* o = *i;
            DBC_ASSERT(o, "observer exists");
            DBC_ASSERT_STREAM(o->upToDateWithSubject(), "up-to-date",
                    err << "observer " << o << " not up-to-date");
        }
    }, {
        for (std::list<Observer*>::iterator i = observers_.begin();
                observers_.end() != i; ++i) {
            Observer* o = *i;
            if (o) { o->update(); }
        }
    })
    
    /** All observers attached to this subject. */
    // This is protected as it is intended to support specification only and 
    // should NOT be used as part of the public API of this class. However, 
    // derived classes can still use this query to wirte their contracts. See 
    // related discussion in book "Design By Contract, by Example" Section 9.9.
    const std::list<const Observer*> observers() const
    DBC_MEM_FUN( (protected) (const std::list<const Observer*>) (Subject)
            (observers)() (const), {
    }, {
    }, {
        std::list<const Observer*> os;
        for (std::list<Observer*>::const_iterator i = observers_.begin();
                observers_.end() != i; ++i) {
            os.push_back(*i);
        }
        return os; 
    })

private:
    DBC_INVARIANT(Subject, {})
    
    std::list<Observer*> observers_;
};

#endif // SUBJECT_HPP_

