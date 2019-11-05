#include<iostream>
using namespace std;

template<typename T>
class Complex{
  private:
    T real;
    T image;
  public:
    Complex(T r, T i):real(r),image(i){}
    // Complex():real(0.0),image(0.0){}
    Complex() = default;
    ~Complex() = default;
    // void print(){
    //     if(image<0)
    //         cout << real << "-" << -image << "i ";
    //     else
    //         cout << real << "+" << image << "i ";
    // }
    
    // There exists assignment sentences in main() function, so I made "=" overloaded.
    Complex operator=(const Complex & c){
        real = c.real;
        image = c.image;
        return *this;
    }

    // friend function of overloaded "+" and "-"
    friend Complex operator+(const Complex & c1, const Complex &c2) {
        return Complex(c1.real + c2.real, c1.image + c2.image);
    }
    // friend Complex operator-(const Complex & c1, const Complex &c2) {
    //     return Complex(c1.real - c2.real, c1.image - c2.image);
    // }

    // member function of overloaded "*" and "/"
    // Complex operator*(const Complex & c) const {
    //     return Complex(real * c.real - image * c.image,
    //                    real * c.image + image * c.real);
    // }
    // Complex operator/(const Complex & c) const {
    //     return Complex((real * c.real + image * c.image) / (c.real * c.real + c.image * c.image),
    //                    (image * c.real - real * c.image) / (c.real * c.real + c.image * c.image));
    // }

    // //friend funciton of overloaded prefix-"++"
    // friend Complex operator++(Complex & c) {
    //     return Complex(++c.real, ++c.image);
    // }

    // //member function of overloaded suffix-"++"
    // Complex operator++(int){
    //     return Complex(real++, image++);
    // }

    //exp4
    friend ostream & operator<<(ostream & os, const Complex & c){
        if(c.image<0)
            os << c.real << "-" << -c.image << "i ";
        else
            os << c.real << "+" << c.image << "i ";
        return os;
    }

    friend istream & operator>>(istream & is, Complex & c){
        is >> c.real >> c.image;
        return is;
    }
};

int main(){
    Complex<double> A1(2.3, 4.6), A2(3.6, 2.8), A3;
    Complex<int> A4(3, 4), A5(-3, -5), A6;
    A3 = A1 + A2;
    A6 = A4 + A5;
    cout << A1 << A2 << A3 << endl;
    cout << A4 << A5 << A6 << endl;
    // Complex A1(2.3, 4.6), A2(3.6, 2.8);
    // // Complex A1,A2;
    // // cin >> A1 >> A2;
    // Complex A3, A4, A5, A6;
    
    // A3 = A1 + A2;
    // A4 = A1 - A2;
    // A5 = A1 * A2;
    // A6 = A1 / A2;
    
    // cout << "A1=";
    // A1.print();
    // // cout << A1;
    // cout << endl
    //      << "A2=";
    // A2.print();
    // // cout << A2;
    // cout << endl
    //      << "A3=A1+A2=";
    // A3.print();
    // cout << endl
    //      << "A4=A1-A2=";
    // A4.print();
    // cout << endl
    //      << "A5=A1*A2=";
    // A5.print();
    // cout << endl
    //      << "A6=A1/A2=";
    // A6.print();
    
    // A3 = ++A1;
    // cout << endl
    //      << "after A3=++A1, ";
    // cout << "A1=";
    // A1.print();
    // cout << "A3=";
    // A3.print();
    
    // A4 = A2++;
    // cout << endl
    //      << "after A4=++A2, ";
    // cout << "A2=";
    // A2.print();
    // cout << "A4=";
    // A4.print();

    return 0;
}