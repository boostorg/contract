// From: David Maley [d.maley@stmarys-belfast.ac.uk]
// Sent: Thursday, September 27, 2007 9:02 AM
// To: Lorenzo Caminiti
// Cc: I.Spence@qub.ac.uk
// Subject: RE: Design by Contract in C++

// dbc.h

// template definitions to support Design by Contract in C++

#ifdef DBC_ON

class Assertion {
  const char* theExpr;
  const char* theFile;
  int theLine;
public:
  Assertion(const char* expr, const char* file, int line) :
theExpr(expr), theFile(file), theLine(line) {}
  friend ostream& operator<<(ostream &, Assertion); };

ostream& operator<<(ostream &s, Assertion a) {
  s<<"Assertion "<<a.theExpr<<" failed in file "<<a.theFile<<" at line "<<a.theLine<<endl;
  return s;
}

template <typename FunctionObject, typename ReturnType, typename
Formal1>
ReturnType dbc(FunctionObject fo, ReturnType, Formal1 f1) {
  return fo(f1);
}

template <typename ReturnType, typename Formal1, int MethodNumber=0> class DBC1 {
  template <typename Derived, bool Top=false, typename Dummy = typename Derived::Base>
  class DBC : public ::DBC1<ReturnType, Formal1,
MethodNumber>::DBC<typename Derived::Base, false, typename
Derived::Base::Base> {
    typedef ReturnType (Derived::* BodyType)(Formal1);
    typedef typename Derived::Base BaseType; 
    typedef ReturnType (BaseType::* AncestorBodyType)(Formal1);
    typedef typename ::DBC1<ReturnType, Formal1,
MethodNumber>::DBC<Derived, Top, Dummy> This;
    typedef typename ::DBC1<ReturnType, Formal1,
MethodNumber>::DBC<typename Derived::Base, false, typename
Derived::Base::Base> Ancestor;
    bool pre(Formal1) const { return true; }
    void preFailure() const { throw Assertion("preFailure", __FILE__, __LINE__); }
    bool post(Formal1) const { return true; }
    void postFailure() const { throw Assertion("postFailure", __FILE__, __LINE__); }
    BodyType _body;
    void handleOld(const Derived*);
    const Derived* _object;
    Derived* _mutableObject;
  protected:
    bool effectivePre(Formal1 f1) const { return This::pre(f1) || Ancestor::effectivePre(f1); }
    bool effectivePost(Formal1 f1) const { return This::post(f1) && Ancestor::effectivePost(f1); }
    bool effectiveInvariant() const { return This::_object->invariant() && Ancestor::effectiveInvariant(); }
    const Derived* old() const { return static_cast<const Derived*>(Ancestor::old()); }
  public:
    DBC(Derived* object, BodyType body) : _body(body), _mutableObject(object), _object(object), Ancestor(object,
static_cast<AncestorBodyType>(body)) { handleOld(object); }
    ReturnType operator()(Formal1);
  };

  template <typename Base>
  class DBC<Base, false, Base> {
    typedef ReturnType (Base::* BodyType)(Formal1);
    typedef typename ::DBC1<ReturnType, Formal1,
MethodNumber>::DBC<Base, false, Base> This;
    bool pre(Formal1) const { return true; }
    void preFailure() const { throw Assertion("preFailure", __FILE__, __LINE__); }
    bool post(Formal1) const { return true; }
    void postFailure() const { throw Assertion("postFailure", __FILE__, __LINE__); }
    BodyType _body;
    const Base* _object;
    Base* _mutableObject;
  protected:
    bool effectivePre(Formal1 f1) const { return This::pre(f1); }
    bool effectivePost(Formal1 f1) const { return This::post(f1); }
    bool effectiveInvariant() const { return This::_object->invariant(); }
    const Base* _old;
    ReturnType* _result;
  public:
    DBC(Base* object, BodyType body) : _body(body), _mutableObject(object), _object(object), _old(new Base(*object)),
_result() { }
    ~DBC() { if (_old) delete _old; }
    const Base* const old() const { return _old; }
    ReturnType const result() const { return *_result; }
    ReturnType operator()(Formal1);
  };
};

template <typename ReturnType, typename Formal1, int MethodNumber>
  template <typename Derived, bool Top, typename Dummy>
    void DBC1<ReturnType, Formal1, MethodNumber>::DBC<Derived, Top,
Dummy>::handleOld(const Derived* dp)
    {
      if (Top) {
        if (_old)
          delete _old;
        _old = new Derived(*dp);
      }
    }
    
template <typename ReturnType, typename Formal1, int MethodNumber>
  template <typename Derived, bool Top, typename Dummy>
    ReturnType DBC1<ReturnType, Formal1, MethodNumber>::DBC<Derived, Top, Dummy>::operator()(Formal1 f1)
    {
      if (!effectivePre(f1) || !effectiveInvariant())
        preFailure();
      handleOld(_object);
      _result = new ReturnType((_mutableObject->*_body)(f1));
      if (!effectivePost(f1) || !effectiveInvariant())
        postFailure();
      return *_result;
    }
    
template <typename ReturnType, typename Formal1, int MethodNumber>
  template <typename Derived>
    ReturnType DBC1<ReturnType, Formal1, MethodNumber>::DBC<Derived, false, Derived>::operator()(Formal1 f1)
    {
      if (!effectivePre(f1) || !effectiveInvariant())
        preFailure();
      _result = new ReturnType((_mutableObject->*_body)(f1));
      if (!effectivePost(f1) || !effectiveInvariant())
        postFailure();
      return *_result;
    }  



template <typename ReturnType, typename Formal1, typename Formal2, int MethodNumber=0> class DBC2 {
  template <typename Derived, bool Top=false, typename Dummy = typename Derived::Base>
  class DBC : public ::DBC2<ReturnType, Formal1, Formal2,
MethodNumber>::DBC<typename Derived::Base, false, typename
Derived::Base::Base> {
    typedef ReturnType (Derived::* BodyType)(Formal1, Formal2);
    typedef typename Derived::Base BaseType; 
    typedef ReturnType (BaseType::* AncestorBodyType)(Formal1, Formal2);
    typedef typename ::DBC2<ReturnType, Formal1, Formal2,
MethodNumber>::DBC<Derived, Top, Dummy> This;
    typedef typename ::DBC2<ReturnType, Formal1, Formal2,
MethodNumber>::DBC<typename Derived::Base, false, typename
Derived::Base::Base> Ancestor;
    bool pre(Formal1, Formal2) const { return true; }
    void preFailure() const { throw Assertion("preFailure", __FILE__, __LINE__); }
    bool post(Formal1, Formal2) const { return true; }
    void postFailure() const { throw Assertion("postFailure", __FILE__, __LINE__); }
    BodyType _body;
    void handleOld(const Derived*);
    const Derived* _object;
    Derived* _mutableObject;
  protected:
    bool effectivePre(Formal1 f1, Formal2 f2) const { return This::pre(f1, f2) || Ancestor::effectivePre(f1, f2); }
    bool effectivePost(Formal1 f1, Formal2 f2) const { return This::post(f1, f2) && Ancestor::effectivePost(f1, f2); }
    bool effectiveInvariant() const { return This::_object->invariant() && Ancestor::effectiveInvariant(); }
    const Derived* old() const { return static_cast<const Derived*>(Ancestor::old()); }
  public:
    DBC(Derived* object, BodyType body) : _body(body), _mutableObject(object), _object(object), Ancestor(object,
static_cast<AncestorBodyType>(body)) { handleOld(object); }
    ReturnType operator()(Formal1, Formal2);
  };

  template <typename Base>
  class DBC<Base, false, Base> {
    typedef ReturnType (Base::* BodyType)(Formal1, Formal2);
    typedef typename ::DBC2<ReturnType, Formal1, Formal2,
MethodNumber>::DBC<Base, false, Base> This;
    bool pre(Formal1, Formal2) const { return true; }
    void preFailure() const { throw Assertion("preFailure", __FILE__, __LINE__); }
    bool post(Formal1, Formal2) const { return true; }
    void postFailure() const { throw Assertion("postFailure", __FILE__, __LINE__); }
    BodyType _body;
    const Base* _object;
    Base* _mutableObject;
  protected:
    bool effectivePre(Formal1 f1, Formal2 f2) const { return This::pre(f1, f2); }
    bool effectivePost(Formal1 f1, Formal2 f2) const { return This::post(f1, f2); }
    bool effectiveInvariant() const { return This::_object->invariant(); }
    const Base* _old;
    ReturnType* _result;
  public:
    DBC(Base* object, BodyType body) : _body(body), _mutableObject(object), _object(object), _old(new Base(*object)),
_result() { }
    ~DBC() { if (_old) delete _old; }
    const Base* const old() const { return _old; }
    ReturnType const result() const { return *_result; }
    ReturnType operator()(Formal1, Formal2);
  };
};

template <typename ReturnType, typename Formal1, typename Formal2, int
MethodNumber>
  template <typename Derived, bool Top, typename Dummy>
    void DBC2<ReturnType, Formal1, Formal2, MethodNumber>::DBC<Derived, Top, Dummy>::handleOld(const Derived* dp)
    {
      if (Top) {
        if (_old)
          delete _old;
        _old = new Derived(*dp);
      }
    }
    
template <typename ReturnType, typename Formal1, typename Formal2, int
MethodNumber>
  template <typename Derived, bool Top, typename Dummy>
    ReturnType DBC2<ReturnType, Formal1, Formal2,
MethodNumber>::DBC<Derived, Top, Dummy>::operator()(Formal1 f1, Formal2
f2)
    {
      if (!effectivePre(f1, f2) || !effectiveInvariant())
        preFailure();
      handleOld(_object);
      _result = new ReturnType((_mutableObject->*_body)(f1, f2));
      if (!effectivePost(f1, f2) || !effectiveInvariant())
        postFailure();
      return *_result;
    }
    
template <typename ReturnType, typename Formal1, typename Formal2, int
MethodNumber>
  template <typename Derived>
    ReturnType DBC2<ReturnType, Formal1, Formal2,
MethodNumber>::DBC<Derived, false, Derived>::operator()(Formal1 f1,
Formal2 f2)
    {
      if (!effectivePre(f1, f2) || !effectiveInvariant())
        preFailure();
      _result = new ReturnType((_mutableObject->*_body)(f1, f2));
      if (!effectivePost(f1, f2) || !effectiveInvariant())
        postFailure();
      return *_result;
    }
#endif // DBC_ON


// implementing Meyer's example of predicate inheritance

// the following matrix representations are used:

// [ a b c ]
// [ d e f ]
// [ g h i ]

// [ _m[0] _m[1] _m[2] ]
// [ _m[3] _m[4] _m[5] ]
// [ _m[6] _m[7] _m[8] ]

// [ get(1, 1) get(1, 2) get(1, 3) ]
// [ get(2, 1) get(2, 2) get(2, 3) ]
// [ get(3, 1) get(3, 2) get(3, 3) ]

// test matrix is currently:

// [ 1.101, 2.198, 3.125 ]
// [ 2.145, 1.186, 1.174 ]
// [ 3.148, 2.199, 1.104 ]

// inverse is:

// [-0.277165, 0.9684, -0.245254]
// [0.289232, -1.87829, 1.17868]
// [0.214217, 0.979929, -0.74263]

#define DBC_ON

#include <iostream>
#include <math.h>

#ifdef DBC_ON

#include "dbc.h"
typedef ::DBC1<bool, const double&> Invert; typedef ::DBC2<double, int, int> Get;

#endif // DBC_ON

#define ROW_SIZE 3
#define MATRIX_SIZE ROW_SIZE*ROW_SIZE
#define BASE_PRECISION 0.000001
#define SUBTYPE_PRECISION 0.00000000000000000001

int max(int x, int y) { return (x>y)?x:y; } int min(int x, int y) { return (x<y)?x:y; }

class Matrix {
  double _m[MATRIX_SIZE];
public:
  Matrix() { for (int i=0; i<MATRIX_SIZE; i++) _m[i]=0; }
  Matrix(double, double, double, double, double, double, double, double, double);
  Matrix(const Matrix& n) { for (int i=0; i<MATRIX_SIZE; i++) { _m[i]=n._m[i]; } }
  void set(double value, int row, int column) { _m[3*(row-1)+column-1]=value; }
  double get(int row, int column) const;
  bool invariant() const;
  virtual double determinant() const;
  void transpose();
  virtual bool invert(const double&);
  double norm();
  Matrix operator*(const Matrix&);
  const Matrix& operator-(const Matrix&);
  const Matrix& operator=(const Matrix& n) { for (int i=0; i<MATRIX_SIZE; i++) _m[i]=n._m[i]; return *this; }
  void deductRowFromRow(int, int, double);

#ifdef DBC_ON
  typedef Matrix Base;
  typedef ::Invert::DBC<Matrix, false, Matrix> Invert;
  bool invert_body(const double&);
  typedef ::Get::DBC<const Matrix, false, const Matrix> Get;
  double get_body(int, int) const;
#endif // DBC_ON
  friend ostream& operator<<(ostream &, Matrix); };

Matrix I;

ostream& operator<<(ostream &s, Matrix r) {
  s<<"["<<r.get(1, 1)<<", "<<r.get(1, 2)<<", "<<r.get(1, 3)<<"]"<<endl;
  s<<"["<<r.get(2, 1)<<", "<<r.get(2, 2)<<", "<<r.get(2, 3)<<"]"<<endl;
  s<<"["<<r.get(3, 1)<<", "<<r.get(3, 2)<<", "<<r.get(3, 3)<<"]"<<endl;
  return s;
}

Matrix::Matrix(double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8) {
  _m[0]=v0; _m[1]=v1; _m[2]=v2;
  _m[3]=v3; _m[4]=v4; _m[5]=v5;
  _m[6]=v6; _m[7]=v7; _m[8]=v8;
}

bool Matrix::invariant() const
{
//  cout<<"invariant evaluated for Matrix\n";
  return true;
}

void Matrix::transpose()
{
  double b=_m[1], c=_m[2], f=_m[5];
  _m[1]=_m[3]; _m[2]=_m[6]; _m[5]=_m[7];
  _m[3]=b; _m[6]=c; _m[7]=f;
}

double Matrix::norm()
{
  double sumOfSquares=0;
  for (int i=0; i<MATRIX_SIZE; i++)
    sumOfSquares+=_m[i]*_m[i];
  return sqrt(sumOfSquares);
}  

Matrix Matrix::operator*(const Matrix& m) {
  Matrix result;
  for (int i=1; i<=ROW_SIZE; i++)
    for (int j=1; j<=ROW_SIZE; j++) {
      double sum=0;
      for (int k=1; k<=ROW_SIZE; k++) {
        sum+=get(i, k)*m.get(k, j);
      }
      result.set(sum, i, j); 
    }
  return result;
}

const Matrix& Matrix::operator-(const Matrix& m) {
  Matrix result;
  for (int i=1; i<=ROW_SIZE; i++)
    for (int j=1; j<=ROW_SIZE; j++)
      result.set(get(i, j)-m.get(i, j), i, j);
  return result;
}

void Matrix::deductRowFromRow(int targetRow, int sourceRow, double
multiple)
{
  for (int i=0; i<3; i++)
    _m[i+3*(targetRow-1)]-=_m[i+3*(sourceRow-1)]*multiple;
}

double Matrix::determinant() const
{
  cout<<" Matrix::determinant() called\n";
  Matrix workCopy;
  workCopy = *this;
  workCopy.deductRowFromRow(2, 1, workCopy.get(2, 1)/workCopy.get(1, 1));
  workCopy.deductRowFromRow(3, 1, workCopy.get(3, 1)/workCopy.get(1, 1));
  workCopy.deductRowFromRow(3, 2, workCopy.get(3, 2)/workCopy.get(2, 2));
  return workCopy.get(1, 1)*workCopy.get(2, 2)*workCopy.get(3, 3); }

double Matrix::get(int row, int column) const #ifdef DBC_ON {
  Get dbc(this, &Matrix::get_body);
  return dbc(row, column);
}

bool Matrix::Get::pre(int row, int column) const {
  return 0<row && row<=ROW_SIZE && 0<column && column<=ROW_SIZE; }

bool Matrix::Get::post(int row, int column) const { //  cout<<"postcondition evaluated for Matrix::Get\n";
  return true;
}

double Matrix::get_body(int row, int column) const #endif { return _m[3*(row-1)+column-1]; }
  
bool Matrix::invert(const double& epsilon) #ifdef DBC_ON {
  Invert dbc(this, &Matrix::invert_body);
  return dbc(epsilon);
}

bool Matrix::Invert::pre(const double& epsilon) const {
  cout<<"precondition evaluated for Matrix::Invert\n";
  return _object->determinant();
}

bool Matrix::Invert::post(const double& epsilon) const {
  cout<<"postcondition evaluated for Matrix::Invert\n";
  Matrix error=*const_cast<Matrix *>(old())*(*_object)-I;
  return error.norm()<epsilon/2;
}

bool Matrix::invert_body(const double& epsilon) #endif { //  cout<<"body executed for Matrix::Invert\n";
  double det=determinant();
  Matrix unT_result;
  for (int i=1; i<=ROW_SIZE; i++) {
    int rows[2];
    rows[0] = i%3+1;
    rows[1] = (i+1)%3+1;
    for (int j=1; j<=ROW_SIZE; j++) {
      int cols[2];
      cols[0] = j%3+1;
      cols[1] = (j+1)%3+1;      
      unT_result.set(pow(-1, i+j)*(get(min(rows[0], rows[1]), min(cols[0], cols[1]))* \
      get(max(rows[0], rows[1]), max(cols[0], cols[1]))- \
      get(max(rows[0], rows[1]), min(cols[0], cols[1]))* \
      get(min(rows[0], rows[1]), max(cols[0], cols[1])))/det, i, j);
    }

 }
 
  Matrix result;
  result=unT_result;
  result.transpose();
  *this = result;
  return true;
}

class NewMatrix : public Matrix {
public:
  NewMatrix() : Matrix() {}
  NewMatrix(double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8) : Matrix(v0, v1, v2, v3, v4, v5, v6, v7, v8) {}
  bool invariant() const;
  double determinant() const;
  void transpose();
  virtual bool invert(const double&);
  double norm(Matrix);
#ifdef DBC_ON
  typedef Matrix Base;
  typedef ::Invert::DBC<NewMatrix, true, Base> Invert;
  bool invert_body(const double&);
#endif // DBC_ON
  friend ostream& operator<<(ostream &, Matrix); };

bool NewMatrix::invariant() const
{
//  cout<<"invariant evaluated for NewMatrix\n";
  return true;
}

double NewMatrix::determinant() const
{
  cout<<" NewMatrix::determinant() called\n";
  double a=get(1, 1), b=get(1, 2), c=get(1, 3);
  double d=get(2, 1), e=get(2, 2), f=get(2, 3);
  double g=get(3, 1), h=get(3, 2), i=get(3, 3);
  return a*e*i+b*f*g+c*d*h-c*e*g-a*f*h-b*d*i;
}

bool NewMatrix::invert(const double& epsilon) #ifdef DBC_ON {
  Invert dbc(this, &Matrix::invert_body);
  return dbc(epsilon);
}

bool NewMatrix::Invert::pre(const double& epsilon) const { //  cout<<"precondition evaluated for NewMatrix::Invert\n";
  return true;
}

bool NewMatrix::Invert::post(const double& epsilon) const {
  cout<<"postcondition evaluated for NewMatrix::Invert\n";
  return true;
}
#else
{
  Matrix::invert(epsilon);
}
#endif

int main()
{
  for (int i=1; i<=ROW_SIZE; i++)
  I.set(1, i, i);
  NewMatrix nm1(1.101, 2.198, 3.125, 2.145, 1.186, 1.174, 3.148, 2.199, 1.104);
  Matrix m1 = nm1, m2 = nm1;
  Matrix *mp1=&nm1, *mp2=&m1;
cout<<mp1->determinant()<<", "<<mp2->determinant()<<", "<<endl; #ifdef DBC_ON
  try {
    mp2->invert(BASE_PRECISION); cout<<endl;
    mp1->invert(BASE_PRECISION); cout<<endl;
    mp1->invert(SUBTYPE_PRECISION); cout<<endl;
    cout<<m2<<*mp1<<m2*(*mp1)<<endl;
  }
  catch (NewMatrix) { cout<<"constraint violation for NewMatrix"<<endl; }
  catch (Matrix) { cout<<"constraint violation for Matrix"<<endl; }
  catch (Assertion a) { cout<<a<<endl; } #endif
  return 0;
}

