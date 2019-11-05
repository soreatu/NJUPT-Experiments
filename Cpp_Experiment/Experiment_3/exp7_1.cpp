#include<iostream>
using namespace std;
const double PI = 3.1415926;

class Container{
  protected:
    double radius;
  public:
    Container(double r):radius(r){}
    virtual double area() = 0;
    virtual double volumn() = 0;
    virtual void print() = 0;
};

class Cube: public Container{//1
  public:
    Cube(double r):Container(r){}
    double area(){
        return 6 * radius * radius;
    }
    double volumn(){
        return radius * radius * radius;
    }
    void print(){
        cout << "Cube's radius is " << radius << endl;
        cout << "Cube's area is " << area() << endl;
        cout << "Cube's volumn is " << volumn() << endl;
    }
};

class Sphere:public Container{//2
  public:
    Sphere(double r):Container(r){}
    double area(){
        return 4.0 * PI * radius * radius;
    }
    double volumn(){
        return 4.0 / 3.0 * PI * radius * radius * radius;
    }
    void print(){
        cout << "Sphere's radius is " << radius << endl;
        cout << "Sphere's area is " << area() << endl;
        cout << "Sphere's volumn is " << volumn() << endl;
    }
};

class Cylinder:public Container{//3
  private:
    double height;

  public:
    Cylinder(double r, double h) : Container(r){
        height = h;
    }
    double area(){
        return 2.0 * PI * radius * radius + 2.0 * PI * radius * height;
    }
    double volumn(){
        return PI * radius * radius * height;
    }
    void print(){
        cout << "Sphere's radius is " << radius << endl;
        cout << "Sphere's height is " << height << endl;
        cout << "Sphere's area is " << area() << endl;
        cout << "Sphere's volumn is " << volumn() << endl;
    }
};

int main(){
    Container *p;
    // Container c1(5);
    Cube c(1);
    Sphere s(2);
    Cylinder cy(3,4);
    p = &c;
    cout << p->area() << endl;
    cout << p->volumn() << endl;
    p->print();
    p = &s;
    cout << p->area() << endl;
    cout << p->volumn() << endl;
    p->print();
    p = &cy;
    cout << p->area() << endl;
    cout << p->volumn() << endl;
    p->print();

    return 0;
}

