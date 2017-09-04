/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <cstring>
#include <iostream>

/** Demonstrate Design By Contract use implementing a simple string type. */
class str DBC_INHERIT_OBJECT(str) { // Derive from dbc::object.
public:
    /** Max limit on string length. */
    static const size_t MAX_SIZE = 16000;

    /**
     * Construct from C-style null-terminated string.
     * @param[in] chars C-style null-terminated string.
     */
    str(const char* chars): size_(), chars_()
    DBC_CONSTRUCTOR( (public) (str)( (const char*)(chars) ), {
        // Constructor preconditions.
        size_t size = strlen(chars); // Code allowed but keep it simple.
        // Use DBC_ASSERT() or DBC_ASSERT_STREAM() to assert conditions.
        DBC_ASSERT(size >= 0 && size < str::MAX_SIZE, "size in range");
    }, {
        // Constructor postconditions.
        DBC_ASSERT(self.now.size() == strlen(chars.now), "size set");
        DBC_ASSERT(strncmp(self.now.chars_, chars.now, self.now.size_) == 0,
                "chars set");
    }, {
        // Constructor body.
        size_ = strlen(chars);
        chars_ = new char[size_];
        strncpy(chars_, chars, size_);
    })

    /**
     * Construct copying from another string object.
     * Copy constructor is used by library to support "old" in postcond. User
     * defined copy constr is needed for pointer deep copy.
     * @note To avoid code duplication, this and the above constructor could 
     *  be refactored delegating implementation and contract to an init() func.
     * @param[in] other Other string object.
     */
    str(const str& other): size_(), chars_()
    DBC_CONSTRUCTOR( (public) (str)( (const str&)(other) ), {
        // Use other.size() not other.size_ as precond should use public member.
        DBC_ASSERT(other.size() >= 0 && other.size() < str::MAX_SIZE,
                "size in range");
    }, {
        DBC_ASSERT(self.now.size() == other.now.size_, "size set");
        DBC_ASSERT(strncmp(self.now.chars_, other.now.chars_, other.now.size_)
                == 0, "chars set");
    }, {
        size_ = other.size_;
        chars_ = new char[size_];
        strncpy(chars_, other.chars_, size_);
    })
    
    /** Destroy. */
    virtual ~str()
    DBC_DESTRUCTOR( (public) (virtual) (str)(), {
        // Destructor body.
        delete[] chars_; // Invariant already checked chars_ != 0.
    })

    /**
     * Return character at specified index.
     * @param[in] index Index position.
     * @return str's character at specified position.
     */
    char& operator[](const size_t& index)
    DBC_MEM_FUN( (public) (char&) DBC_COPYABLE(str)
            (operator_at)( (const size_t&)(index) ), {
        // Member function preconditions.
        DBC_ASSERT(index >= 0 && index < self.size(), "index in range");
    }, {
        // Member function postconditions.
        // Not a const mem fun, use 'self.old' for object before body and
        // make class type DBC_COPYABLE().
        DBC_ASSERT(result == self.old.chars_[index.now],
                "returning char at index");
    }, {
        // Member function body.
        return chars_[index];
    })

    /**
     * Return size (total number of characters).
     * @return str's size.
     */
    size_t size() const
    DBC_MEM_FUN( (public) (size_t) (str) (size)() (const), {
    }, {
        DBC_ASSERT(result == self.now.size_, "returning size");
    }, { 
        return size_;
    })

private:
    /** Internal string size. */
    size_t size_; // Unsgined so size_ >= 0 check could be removed...
    /** Internal string representation. */
    char* chars_;

    DBC_INVARIANT(str, {
        // Invariants.
        DBC_ASSERT(self.chars_ != 0, "chars exist");
        DBC_ASSERT(self.size_ >= 0 && self.size_ < str::MAX_SIZE,
                "size in range");
    })
};

/** Main program. */
int main() {
    std::cout << std::endl << "init()..." << std::endl;
    str s("Galileo Galilei");

    std::cout << std::endl << "operator[](0)..." << std::endl;
    std::cout << s[0] << std::endl;

    std::cout << std::endl << "del()..." << std::endl;
    return 0;
}

