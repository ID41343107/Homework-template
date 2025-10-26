# Homework-2

## Figure 1. Abstract data type of Polynomial class

```cpp
class Polynomial {
// p(x) = ax + ... en + anx"; a set of ordered pairs of <e₁, a¡>,
// where a; is a nonzero float coefficient and e; is a non-negative integer exponent.
public:
Polynomial();
// Construct the polynomial p(x) = 0
Polynomial Add(Polynomial poly);
// Return the sum of the polynomials *this and poly.
Polynomial Mult(Polynomial poly);
// Return the product of the polynomials *this and poly.
float Eval(float f);
// Evaluate the polynomial *this at f and return the result.
};
```

## Figure 2. The private data members of Polynomial class

```cpp
class Polynomial; // forward declaration
class Term {
friend Polynomial;
private:
float coef; // coefficient
int exp; // exponent
};
The private data members of Polynomial are defined as follows:
private:
Term *termArray;
// array of nonzero terms
int capacity;
// size of termArray
int terms;
// number of nonzero terms
```
## Problems

1. Implement the Polynomial class its ADT Implement and private data members are shown in

   Figure 1 and 2, respectively.
   
2. Write C++ functions to input and output polynomials represented as Figure 2. Your functions
  
   should overload the << andand >>operators.operators.
