/* coding: utf-8 */
#include<iostream>
using namespace std;
class Base{
  public:
    int i;
    Base(int x):i(x){}
    void Show(){
        cout << "i in Base is: " << i << endl;
    }
};

class Derived:public Base{
  public:
    Derived(int x): Base(x){}
    void Show(){
        cout << "i in Derived is: " << i << endl;
    }
};

int main(){
    Base b1(1);//1
    cout << "基类对象 b1.show():\n";
    b1.Show();
    Derived d1(2);//2
    b1 = d1;//3
    cout << "基类b1=d1, b1.show():\n";
    b1.Show();
    cout << "派生类对象 d1.show():\n";
    d1.Show();
    Base &b2 = d1;//4
    cout << "引用b2=d1, b2.show():\n";
    b2.Show();
    Base *b3 = &d1;//5
    cout << "基类指针b3=&d1,b3->show():\n";
    b3->Show();
    Derived *d4 = new Derived(3);//6
    Base *b4 = d4;
    cout << "基类指针b4=d4, b4->show():\n";
    b4->Show();
    cout << "派生类指针d4, d4->show():\n";
    d4->Show();

    // Derived d5=b1;
	// Derived &d6=b1;
	// Derived *d7=&b1;
    // d7=b3;

    return 0;
}