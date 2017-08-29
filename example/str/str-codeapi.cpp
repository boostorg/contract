/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <cstring>
#include <iostream>

/** 
 * Demonstrate the use of Design By Contract for C++ code-based API
 * implementing a simple of string type. 
 * Compared with the macro-based API, the code-based API gives much more
 * control to programmer and allows to see how the library works, but it
 * requires to write much more "setup" code reducing code readability and it
 * does not provide automatic contract documentation. Therefore, the code-based
 * API should be used only when the macro-based API does not suffice.
 * @see "example/str/str.cpp" for same example using macro-based API.
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
    {
        DBC_CONTRACT( (init)(chars) ) contract;
        contract.call(*this, &str::DBC_BODY(init), chars, "init");
    }
protected:
    friend class DBC_CONTRACT( (init)(chars) ); // Not need on modern compilers.
    class DBC_CONTRACT( (init)(chars) ): public dbc::fun<void, 
            const char*>::constr<str> {
        void require(/* no self */ const char* chars) {
            // Constructor preconditions.
            size_t size = strlen(chars); // Code allowed (but keep it simple).
            // Use DBC_ASSERT() or DBC_ASSERT_STREAM() to assert conditions.
            DBC_ASSERT(size >= 0 && size < str::MAX_SIZE, "size in range");
        }
        void ensure(const dbc::post<str>& self,
                const dbc::post<char*>& chars) {
            // Constructor postconditions.
            DBC_ASSERT(self.now.size() == strlen(chars.now), "size set");
            DBC_ASSERT(strncmp(self.now.chars_, chars.now,
                    self.now.size()) == 0, "chars set");
        }
    };
    // Body function named using DBC_BODY() macro.
    void DBC_BODY(init)(const char* chars)
#endif // DBC
    { // Use ';' for body impl. when separating declaration from definition.
        // Constructor body.
        size_ = strlen(chars);
        chars_ = new char[size_];
        strncpy(chars_, chars, size_);
    }
public: // Restore original access level.
    
    /**
     * Copy constructor. 
     * @param[in] other Other string object.
     */
    str(const str& other): size_(), chars_()
#ifdef DBC
    {
        DBC_CONTRACT( (init)(other) ) contract;
        contract.call(*this, &str::DBC_BODY(init), other, "init");
    }
protected:
    friend class DBC_CONTRACT( (init)(other) );
    class DBC_CONTRACT( (init)(other) ): public dbc::fun<void, 
            const str&>::constr<str> {
        void require(const str& other) {
            DBC_ASSERT(other.size() >= 0 && other.size() < str::MAX_SIZE,
                    "size in range");
        }
        void ensure(const dbc::post<str>& self,
                const dbc::post<str>& other) {
            DBC_ASSERT(self.now.size() == other.now.size(), "size set");
            DBC_ASSERT(strncmp(self.now.chars_, other.now.chars_,
                    self.now.size()) == 0, "chars set");
        }
    };
    void DBC_BODY(init)(const str& other)
#endif // DBC
    {
        delete[] chars_;
        size_ = other.size_;
        chars_ = new char[size_];
        strncpy(chars_, other.chars_, size_);
    }
public: // Restore original access level.
    
    /** Destroy. */
    virtual ~str()
    // Instead of DBC_DESTRUCTOR( (public) (virtual) (str)(), ...).
#ifdef DBC
    {
        DBC_CONTRACT( (del) ) contract;
        contract.call(*this, &str::DBC_BODY(del), "del");
    }
    friend class DBC_CONTRACT( (del) );
    class DBC_CONTRACT( (del) ): public dbc::fun<void>::destr<str> {
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
    {
        DBC_CONTRACT( (operator_at)(index) ) contract;
        return contract.call(*this,  &str::DBC_BODY(operator_at), index,
                "operator_at");
    }
protected:
    friend class DBC_CONTRACT( (operator_at)(index) );
    class DBC_CONTRACT( (operator_at)(index) ): public dbc::fun<char&, 
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
    {
        DBC_CONTRACT( (size) ) contract;
        return contract.call(*this, &str::DBC_BODY(size), "size");
    }
protected:
    friend class DBC_CONTRACT( (size) ); // No need on moder compilers.
    class DBC_CONTRACT( (size) ): public dbc::fun<size_t>::mem<
            const str /* const class type because const mem fun */> {
        void require(const str& self) {} // No preconditions.
        void ensure(const dbc::post<str>& self, const size_t& result) {
            DBC_ASSERT(result == self.now.size_, "returning size");
        }
    };
    size_t DBC_BODY(size)() const
#endif // DBC
    { 
        return size_; 
    }
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

