
#ifndef STRING_HPP_
#define STRING_HPP_

// Must setup #defines before #including dbc.hpp.
#undef DBC_NO
#undef DBC_ALL
#undef DBC_CHECK_REQUIRE
#undef DBC_CHECK_ENSURE
#undef DBC_CHECK_INVARIANT
#undef DBC_CHECK_LOOP
// Make sure ONLY invariants and preconditions are checked.
#define DBC_CHECK_REQUIRE
#define DBC_CHECK_INVARIANT

#include <dbc.hpp>
#include <string>
#include <cstring>

/**
 * Example of invariant (and simple precondition) checking from [Str97].
 * In original example String from [Str97] only the implementation of 
 * operator[] and size() were provided. Therefore, from that example it was 
 * clear that operator[] was checking the invariant while size() was not. 
 * However, it was not indicaed if constrcutor and destructor were to check the
 * invaraint or not. I have implemented constructor and destructor here so they
 * check the invariant also (remove contract from delegated contrcuting 
 * function init() and destructor to prevent them from checking the invariant).
 * [Str97] "The C++ Programming Language", B. Stroustrup, 1997.
 */
/** @todo[LC] Read about inv and exception from [Str97]. */
class String DBC_INHERIT_OBJECT(String) {
public:
    /** Thrown when out of range indexspecified (precondition failure). */
    class Range {};
    /** Thrown on invarint failure. */
    class Invariant {};

    /** Max limit on string length. */
    enum { TOO_LARGE = 16000 };

    /** Construct from C-style null-terminated string. */
    String(const char* q): sz(), p() { init(std::string(q)); }
    
    /** Construct from C++ string. */
    String(const std::string& s): sz(), p() { init(s); }

    /** Destroy. */
    ~String()
    DBC_DESTRUCTOR( (public) (String)(), {
        delete[] p;
    })

    /** Returns character at specified index. */
    char& operator[](int i)
    DBC_MEM_FUN( (public) (char&) (String) (operator_at)( (int)(i) ), {
        DBC_ASSERT_STREAM(i >= 0 && i < self.sz, "i in range",
                err << dbc::uraise<Range>(Range()));
    }, {
    }, {
        return p[i];
    })

    /** Returns size (total number of characters). */
    int size() const
    DBC_MEM_FUN( (public) (int) (String) (size)() (const), {
    }, {
    }, { 
        return sz; 
    })

private:
    /** Internal string size. */
    int sz;
    /** Internal string representation. */
    char* p;

    /** Delegating initializator (call only from constructors). */
    void init(const std::string& s)
    DBC_CONSTRUCTOR( (public) (String)( (const std::string&)(s) ), {
    }, {
    }, {
        sz = s.size();
        p = new char[sz + 1];
        strcpy(p, s.c_str());
    })

    DBC_INVARIANT(String, {
        DBC_ASSERT_STREAM(self.p != 0, "p exists",
                err << dbc::uraise<Invariant>(Invariant()));
        DBC_ASSERT_STREAM(self.sz >= 0 && self.sz < String::TOO_LARGE, 
                "size in range", err << "size " << self.sz 
                << " out of range [0, " << String::TOO_LARGE << ")" 
                << dbc::uraise<Invariant>(Invariant()));
        // We can safely access p[sz] here bacause above assertions passed.
        DBC_ASSERT_STREAM(!self.p[self.sz], "p null-terminated", 
                err << dbc::uraise<Invariant>(Invariant()));
    })
};

#endif // STRING_HPP_

