#include<iostream>
#include<string>
using namespace std;

class Boy;
class Girl{
  private:
    string name;
    int age;
    friend Boy;
  public:
    //constructor
    Girl(string n, int a);
    
    //destructor
    ~Girl(){
        cout << "Girl destructing..." << endl;
    }

    //member function
    void Print();
    void VisitBoy(Boy &);
    friend void VisitBoyGirl(Boy &, Girl &);
};

class Boy{
  private:
    string name;
    int age;
    friend Girl;
  public:
    //constructor
    Boy(string n, int a);

    //destructor
    ~Boy(){
        cout << "Boy constructing..." << endl;
    }

    //member function
    void Print();
    void VisitGirl(Girl &girl);
    friend void VisitBoyGirl(Boy &, Girl &);
};

Girl::Girl(string n, int a){
    name = n;
    age = a;
    cout << "Girl constructing..." << endl;
}

void Girl::Print(){
    cout << "Girl's name: " << name << endl;
    cout << "Girl's age: " << age << endl;
}

void Girl::VisitBoy(Boy &boy){
  cout << "Boy's name: " << boy.name << endl;
  cout << "Boy's age: " << boy.age << endl;
}

void VisitBoyGirl(Boy &boy, Girl &girl){
  cout << "Boy's name: " << boy.name << endl;
  cout << "Boy's age: " << boy.age << endl;
  cout << "Girl's name: " << girl.name << endl;
  cout << "Girl's age: " << girl.age << endl;
}

Boy::Boy(string n, int a) : name(n), age(a){
    cout << "Boy constructing..." << endl;
}

void Boy::Print(){
    cout << "Boy's name: " << name << endl;
    cout << "Boy's age: " << age << endl;
}

void Boy::VisitGirl(Girl &girl){
  cout << "Girl's name: " << girl.name << endl;
  cout << "Girl's age: " << girl.age << endl;
}


int main(){
    Girl g1 = Girl("Lucy", 10);
    Boy b1 = Boy("Mike", 11);

    // g1.Print();
    // b1.Print();

    // g1.VisitBoy(b1);
    // b1.VisitGirl(g1);

    VisitBoyGirl(b1, g1);

    return 0;
}