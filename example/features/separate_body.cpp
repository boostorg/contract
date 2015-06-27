
// Vector of unique integer numbers.
//[unique_identifiers_constructor
// An identifier can be pushed only once in this container.
class unique_identifiers
    : private boost::contract::constructor_precondition<unique_identifiers>
{
public:

    // Create this container with all identifiers in range [from, to]. 
    unqiue_identifiers(int from, int to) :
        boost::contract::constructor_precondition<unique_identifiers>([&] {
            BOOST_CONTRACT_ASSERT(from <= to);
        })
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == (to - from));
            })
        ;

        // Constructor body.
        for(id = from; id <= to; ++id) vect_.push_back(id);
    }

    /* ... */
//]
    
    //[unique_identifiers_destructor
    // Destroy this container.
    virtual ~unique_identifiers() {
        auto c = boost::contract::destructor(this); // Check invariants.
        // Destructor body here...
    }
    //]

    int size() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return vect_.size();
    }

    //[unique_identifiers_find
    // Check if specified identifier is in container.
    bool find(int id) const {
        bool result;
        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                if(size() == 0) BOOST_CONTRACT_ASSERT(!result);
            })
        ;

        // Function body.
        return result = std::find(vect_.begin(), vect_.end(), id) !=
                vect_.end();
    }
    //]

    //[unique_identifiers_push_back
    // Specified identifier must not already be in container.
    virtual int push_back(int id, boost::contract::virtual_* v = 0) {
        int result;
        auto old_find = BOOST_CONTRACT_OLDOF(v, find(id));
        auto old_size = BOOST_CONTRACT_OLDOF(v, size());
        auto c = boost::contract::public_function(v, result, this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!find(id)); // Already in, not allowed.
            })
            .postcondition([&] (int result) {
                if(!*old_find) { // Pushed in container.
                    BOOST_CONTRACT_ASSERT(find(id));
                    BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
                }
                BOOST_CONTRACT_ASSERT(result == id);
            })
        ;

        // Function body.
        vect_.push_back(id);
        return result = id;
    }
    //]
    
    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() >= 0);
    }

private:
    std::vector<int> vect_;
};

//[identifiers_push_back
// Can push same identifier multiple times in container (but with no effect).
class identifiers
    #define BASES public unique_identifiers
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    void invariant() const { // Check in AND with bases.
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
    }

    // Do nothing if specified identifier already in container.
    int push_back(int id, boost::contract::virtual_* v = 0) /* override */ {
        int result;
        auto old_find = BOOST_CONTRACT_OLDOF(v, find(id));
        auto old_size = BOOST_CONTRACT_OLDOF(v, size());
        auto c = boost::contract::public_function<override_push_back>(
                v, result, &identifiers::push_back, this, id)
            .precondition([&] { // Check in OR with bases.
                BOOST_CONTRACT_ASSERT(find(id)); // Already in, now allowed.
            })
            .postcondition([&] (int result) { // Check in AND with bases.
                if(*old_find) { // Not added.
                    BOOST_CONTRACT_ASSERT(size() == *old_size);
                }
            })
        ;

        // Function body.
        if(!find(id)) unique_identifiers::push_back(id); // Else, do nothing.
        return result = id;
    }
    BOOST_CONTRACT_OVERRIDE(push_back); // Define `override_push_back`.

    /* ... */
//]

    bool empty() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return size() == 0;
    }
};

//[multi_identifiers
class multi_identifiers
    #define BASES \
        private boost::contract::constructor_precondition<multi_identifiers>, \
        public identifiers, public virtual pushable, \
        protected sizer, private capacitor
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    /* ... */
//]
};

