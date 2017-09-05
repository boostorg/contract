// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Subcontracting example (ported from Eiffel code).

#ifndef NAMES_HPP_
#define NAMES_HPP_

#include <contract.hpp>
#include <string>
#include <list>

/** List of names. */
class name_list {
    
    CONTRACT_INVARIANT( ({}) )

public:
    // Creation //

    /** Create object. */
    name_list(void): names_()
    CONTRACT_CONSTRUCTOR( (class) (name_list)
            (public) (name_list)( (void) )
    (body) (
        ;
    ) )

    /** Destroy object. */
    virtual ~name_list(void)
    CONTRACT_DESTRUCTOR( (class) (name_list)
            (public) (virtual) (name_list)( (void) )
    (body) (
        ;
    ) )
    
    // Queries //

    /** If specified names is in list. */
    bool has(const std::string& name) const
    CONTRACT_FUNCTION( (class) (name_list)
            (public) (bool) (has)( (const std::string&)(name) )
            (const)
    (body) (
        ;
    ) )

    /** Number of names in list. */
    unsigned int count(void) const
    CONTRACT_FUNCTION( (class) (name_list)
            (public) (unsigned int) (count)( (void) ) (const)
    (body) (
        ;
    ) )

    // Commands //

    /** Add name to list. */
    virtual void put(const std::string& name)
    CONTRACT_FUNCTION( (class) (copyable)(name_list)
            (public) (virtual) (void) (put)(
                    (const std::string&)(name) )
    (precondition) ({
        CONTRACT_ASSERT( !has(name) );
    })
    (postcondition) ({
        // If-guard to allow subcontracts to relax postconditions.
        if (!CONTRACT_OLDOF(this)->has(name)) {
            CONTRACT_ASSERT( has(name) );
            CONTRACT_ASSERT( count() ==
                    (CONTRACT_OLDOF(this)->count() + 1) );
        }
    })
    (body) (
        ;
    ) )

private:
    std::list<std::string> names_;
};

/** List of names that allows for duplicates. */
class relaxed_name_list: public name_list {

    CONTRACT_INVARIANT( ({}) )

public:
    // Creation //

    relaxed_name_list(void): name_list()
    CONTRACT_CONSTRUCTOR( (class) (relaxed_name_list)
            (public) (relaxed_name_list)( (void) )
    (body) (
        ;
    ) )

    virtual ~relaxed_name_list(void)
    CONTRACT_DESTRUCTOR( (class) (relaxed_name_list)
            (public) (virtual) (relaxed_name_list)( (void) )
    (body) (
        ;
    ) )

    // Commands //

    void put(const std::string& name)
    CONTRACT_FUNCTION( (class) (copyable)(relaxed_name_list)
            (inherit)(name_list)
            (public) (void) (put)( (const std::string&)(name) )
    (precondition) ({
        // Relax inherited precondition `!has(name)`.
        CONTRACT_ASSERT( has(name) );
    })
    (postcondition) ({
        // Inherited postcondition not checked because of its if-guard.
        if (CONTRACT_OLDOF(this)->has(name)) CONTRACT_ASSERT(
                count() == CONTRACT_OLDOF(this)->count() );
    })
    (body) (
        ;
    ) )
};

#endif // #include guard
    
