#include <iostream>
using namespace std;
class Vehicle
{
  protected:
    int MaxSpeed;
    int Weight;

  public:
    Vehicle(int m, int w)
    {
        MaxSpeed = m;//1
        Weight = w;//2
        cout << "Constructing Vehicle...\n";
    }
    ~Vehicle()
    {
        cout << "Destructing Vehicle...\n";
    }
    void Run(){
        cout << "The Vehicle is running!\n";
    }
    void Stop(){
        cout << "Please stop running!\n";
    }
    void Show(){
        cout << "Its maxspeed is: " << MaxSpeed << endl;
        cout << "Its weight is: " << Weight << endl;
    }
};

class Bicycle: public Vehicle{
  protected:
    int Height;
  public:
    Bicycle(int m, int w, int h):Vehicle(m , w){//3
        Height = h;//4
        cout << "Constructing Bicycle...\n";
    }
    ~Bicycle(){
        cout << "Destructing Bicycle...\n";
    }
    void Show(){
        Vehicle::Show();//5
        cout << "Its height is: " << Height << endl;//6
    }
};

// class Car: public Vehicle{
//   protected:
//     int SeatNum;
//   public: 
//   //Here textbook gave it protected, but constructors or destructor must be public, otherwise they cannot be called outside the class!!!
//   //So, I make the followings as public.
//     Car(int m, int w, int s):Vehicle(m,w){ //8
//         SeatNum = s;//9
//         cout << "Constructing Car...\n";
//     }
//     ~Car(){
//         cout << "Destructing Car...\n";
//     }
//     void Show(){
//         Vehicle::Show();//10
//         cout << "Its seatnum is: " << SeatNum << endl;//11
//     }

// };

// class MotorCycle : public Bicycle, public Car{
//   public:
//     MotorCycle(int m, int w, int h, int s):Bicycle(m,w,h),Car(m,w,s){//14
//         cout << "Constructing MotorCycle...\n";
//     }
//     ~MotorCycle(){
//         cout << "Destructing MotorCycle...\n";
//     }
//     void Show(){
//         cout << "Its maxspeed is: " << MaxSpeed << endl; //wrong
//         cout << "Its weight is: " << Weight << endl; // wrong
//         cout << "Its height is: " << Height << endl;
//         cout << "Its seatnum is: " << SeatNum << endl;
//     }
// };

int main(){
    Bicycle b(30, 20, 1);//7,12
    b.Run();
    b.Stop();
    b.Show();

//     //cannot be compiled if made protected
//     Car c(100, 2000, 5);//13
//     c.Run();
//     c.Stop();
//     c.Show();
//     return 0;
}

// int main(){
//     MotorCycle mc(80, 100, 2, 2); //15
//     mc.Run(); // wrong
//     mc.Stop(); // wrong
//     mc.Show();
//     return 0;
// }