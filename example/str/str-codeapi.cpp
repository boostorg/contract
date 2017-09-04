/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <cstring>
#include <iostream>

/** 
 * Demonstrate DBC code API usage implementing a simple of string type. 
 * Code API gives much more control to programmer, allows to see how library 
 * works respect to macro API, but it requires to write much more "setup" 
 * code and does not provide automatic contract documentation. 
 */
class str DBC_INHERIT_OBJECT(str) { // Derive from dbc::object (using macro).
public:
    /** Max limit on string length. */
    static const size_t MAX_SIZE = 16000;

    /**
     * Construct from C-style null-terminated string.
     * @param[in] chars C-style null-terminated string.
     */
    str(const char* chars): size_(), chars_()
    // Instead of DBC_CONSTRUCTOR( (public) (str)( (const char*)(chars) ), ... .
#ifdef DBC // Complely remove contract from object code if no DBC_CHECK_... .
        // Using DBC_CONTRACT() macro to name contract classes ensures allows
        // subcontracting between contracts specified with macro and code API.
        { DBC_CONTRACT(init, (chars))().call(*this, &str::DBC_BODY(init), 
        chars, "init"); }
protected:
    friend class DBC_CONTRACT(init, (chars)); // Not need on modern compilers.
    class DBC_CONTRACT(init, (chars)): public dbc::fun<void, 
            const char*>::constr<str> {
        void require(/* no self */ const char* chars) {
            // Constructor preconditions.
            size_t len = strlen(chars); // Code allowed (but keep it simple).
            // Use DBC_ASSERT() or DBC_ASSERT_STREAM() to assert conditions.
            DBC_ASSERT(len >= 0 && len < str::MAX_SIZE, "size in range");
        }
        void ensure(const dbc::post<str>& self,
                const dbc::post<char*>& chars) {
            // Constructor postconditions.
            DBC_ASSERT(self.now.size() == strlen(chars.now), "size set");
            DBC_ASSERT(strcmp(self.now.chars_, chars.now) == 0, "chars set");
        }
    };
    // Body function named using DBC_BODY() macro.
    void DBC_BODY(init)(const char* chars)
#endif // DBC
    { // Use ';' for body impl. when separating declaration from definition.
        // Constructor body.
        size_ = strlen(chars);
        chars_ = new char[size_ + 1];
        strcpy(chars_, chars);
    }
public: // Restore original access level.
    
    /** Destroy. */
    virtual ~str()
    // Instead of DBC_DESTRUCTOR( (public) (virtual) (str)(), ...).
#ifdef DBC
        { DBC_CONTRACT(del, ())().call(*this, &str::DBC_BODY(del), "del"); }
    friend class DBC_CONTRACT(del, ());
    class DBC_CONTRACT(del, ()): public dbc::fun<void>::destr<str> {
        // No preconditions and no postconditions.
    };
    void DBC_BODY(del)()
#endif // DBC
    { delete[] chars_; } // Invariant already checked chars_ != 0.
public: // Restore original access level.

    /**
     * Return character at specified index.
     * @param[in] index Index position.
     * @return str's character at specified position.
     */
    char& operator[](const size_t& index)
    // Instead of DBC_MEM_FUN( (public) (char&) DBC_COPYABLE(str) (operator_at)
    // ( (const size_t&)(index) ), ...).
#ifdef DBC
        { return DBC_CONTRACT(operator_at, (index))().call(*this, 
        &str::DBC_BODY(operator_at), index, "operator_at"); }
protected:
    friend class DBC_CONTRACT(operator_at, (index));
    class DBC_CONTRACT(operator_at, (index)): public dbc::fun<char&, 
            // dbc::copyable<> used instead of DBC_COPYABLE().
            const size_t&>::mem<dbc::copyable<str> > {
        void require(const str& self, const size_t& index) {
            // Member function preconditions.
            DBC_ASSERT(index >= 0 && index < self.size(), "index in range");
        }
        void ensure(const dbc::post<dbc::copyable<str> >& self, 
                const dbc::post<size_t>& index, const char& result) {
            // Member function postconditions.
            // Not a const mem fun, use 'self.old' for object before body.
            DBC_ASSERT(result == self.old.chars_[index.now],
                    "returning char at index");
        }
    };
    char& DBC_BODY(operator_at)(const size_t& index)
#endif // DBC
    {
        // Member function body.
        return chars_[index];
    }
public: // Restore original access level.

    /**
     * Return size (total number of characters).
     * @return str's size.
     */
    size_t size() const
    // Instead of DBC_MEM_FUN( (public) (size_t) (str) (size)() (const), ...).
#ifdef DBC
        { return DBC_CONTRACT(size, ())().call(*this, &str::DBC_BODY(size), 
        "size"); }
protected:
    friend class DBC_CONTRACT(size, ()); // No need on moder compilers.
    class DBC_CONTRACT(size, ()): public dbc::fun<size_t>::mem<
            const str /* const class type because const mem fun */> {
        void require(const str& self) {} // No preconditions.
        void ensure(const dbc::post<str>& self, const size_t& result) {
            DBC_ASSERT(result == self.now.size_, "returning size");
        }
    };
    size_t DBC_BODY(size)() const
#endif // DBC
        { return size_; }
public: // Restore original access level.

private:
    /** Internal string size. */
    size_t size_; // Unsgined so size_ >= 0 check could be removed...
    /** Internal string representation. */
    char* chars_;

    // Invariants are still specified using macro.
    DBC_INVARIANT(str, {
        // Invariants.
        DBC_ASSERT(self.chars_ != 0, "chars exist");
        DBC_ASSERT(self.size_ >= 0 && self.size_ < str::MAX_SIZE,
                "size in range");
        // Assertions above passed, chars_[size_] can be accessed.
        DBC_ASSERT(self.chars_[self.size_] == '\0', "null-terminated");
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

