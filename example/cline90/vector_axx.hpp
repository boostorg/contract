
//[cline90_vector_axx
// Extra newlines, etc used to align text with this library code.





template< typename T>
class vector
{
    legal: size() >= 0; // Class invariants (legal).

    public: explicit vector ( int count = 10 )
        : data_(new T[count]), size_(count)
    {
        for(int i = 0; i < size_; ++i) data_[i] = T();
    }

    public: virtual ~vector ( void )
    {
        delete[] data_;
    }

    public: int size ( void ) const
    {
        return size_; 
    }
    
    public: void resize ( int count )
    {
        T* slice = new T[count];
        for(int i = 0; i < count && i < size_; ++i) slice[i] = data_[i];
        delete[] data_;
        data_ = slice;
        size_ = count;
    }

    public: T& operator[] ( int index )
    {
        return data_[index];
    }

    // Preconditions (require) and postconditions (promise) for each function.
    axioms: [ int count; require count >= 0; promise size() == count ]
            vector(count);
    axioms: [ int count; require count >= 0; promise size() == count ]
            resize(count);
    axioms: [ int index; require index >= 0 && index < size() ]
            (*this)[x];

    private: T* data_;
    private: int size_;
};










//]

