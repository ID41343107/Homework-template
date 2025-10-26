#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Polynomial; // forward declaration

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream& output, const Polynomial& Poly);
private:
    float coef; // 系數
    int exp;    // 指數
};

class Polynomial {
private:
    Term* termArray;  // 儲存非零項的動態陣列
    int capacity;     // 陣列大小
    int terms;        // 非零項數量

public:
    // p(x) = 0
    Polynomial() : capacity(10), terms(0) {
        termArray = new Term[capacity];
    }
    ~Polynomial() {
        delete[] termArray;
    }

    void NewTerm(const float c, const int e) {
        if (c == 0) return;
        if (terms == capacity) {
            capacity *= 2;
            Term* temp = new Term[capacity];
            copy(termArray, termArray + terms, temp);
            delete[] termArray;
            termArray = temp;
        }
        termArray[terms].coef = c;
        termArray[terms++].exp = e;
    }

    Polynomial operator+(const Polynomial& poly) const {
        Polynomial result;
        int a = 0, b = 0;
        while (a < terms && b < poly.terms) {
            if (termArray[a].exp == poly.termArray[b].exp) {
                float sum = termArray[a].coef + poly.termArray[b].coef;
                if (sum != 0)
                    result.NewTerm(sum, termArray[a].exp);
                a++; b++;
            }
            else if (termArray[a].exp > poly.termArray[b].exp) {
                result.NewTerm(termArray[a].coef, termArray[a].exp);
                a++;
            }
            else {
                result.NewTerm(poly.termArray[b].coef, poly.termArray[b].exp);
                b++;
            }
        }
        for (; a < terms; a++)
            result.NewTerm(termArray[a].coef, termArray[a].exp);
        for (; b < poly.terms; b++)
            result.NewTerm(poly.termArray[b].coef, poly.termArray[b].exp);
        return result;
    }

    Polynomial operator*(const Polynomial& poly) const {
        Polynomial result;
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < poly.terms; j++) {
                float c = termArray[i].coef * poly.termArray[j].coef;
                int e = termArray[i].exp + poly.termArray[j].exp;
                bool found = false;
                for (int k = 0; k < result.terms; k++) {
                    if (result.termArray[k].exp == e) {
                        result.termArray[k].coef += c;
                        found = true;
                        break;
                    }
                }
                if (!found)
                    result.NewTerm(c, e);
            }
        }
        sort(result.termArray, result.termArray + result.terms,
            [](Term a, Term b) { return a.exp > b.exp; });
        return result;
    }

    float operator()(float x) const {
        float sum = 0;
        for (int i = 0; i < terms; i++)
            sum += termArray[i].coef * pow(x, termArray[i].exp);
        return sum;
    }

    friend istream& operator>>(istream& input, Polynomial& Poly) {
        int n;
        float coef;
        int exp;
        input >> n;
        for (int i = 0; i < n; i++) {
            input >> coef >> exp;
            Poly.NewTerm(coef, exp);
        }
        return input;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        if (poly.terms == 0) {
            os << "0";
            return os;
        }
        for (int i = 0; i < poly.terms; i++) {
            if (i > 0 && poly.termArray[i].coef > 0)
                os << " + ";
            else if (poly.termArray[i].coef < 0)
                os << " ";
            os << poly.termArray[i].coef;
            if (poly.termArray[i].exp != 0)
                os << "x^" << poly.termArray[i].exp;
        }
        return os;
    }
};

int main() {
    Polynomial a, b;

    cout << "多項式 a(x):" << endl;
    cin >> a;
    cout << "\n多項式 b(x):" << endl;
    cin >> b;

    cout << "\na(x) = " << a << endl;
    cout << "b(x) = " << b << endl;

    cout << "\na + b = " << a + b << endl;
    cout << "a * b = " << a * b << endl;

    float x;
    cout << "\n要代入的 x ：";
    cin >> x;
    cout << "a(" << x << ") = " << a(x) << endl;
    cout << "b(" << x << ") = " << b(x) << endl;

    return 0;
}
