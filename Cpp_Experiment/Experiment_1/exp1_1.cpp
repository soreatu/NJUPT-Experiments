#include<iostream>
using namespace std;

class Time{
  private:
    int Hour;
    int Minute;
    int Second;
  public:
    //constructor
    // Time() = default;
    Time(int h=0, int m=0, int s=0);
    Time(const Time &t);

    //destructor
    ~Time();

    //member function
    void ChangeTime(int h, int m, int s);
    int GetHour();
    int GetMinute();
    int GetSecond();
    void PrintTime();

    void IncreaseOneSecond();
};

Time::Time(int h, int m, int s){
    cout << "Constructing...";
    Hour = h;
    Minute = m;
    Second = s;
    cout << Hour << ":" << Minute << ":" << Second << endl;
}

Time::Time(const Time &t){
    cout << "Copy constructing..." << endl;
    long secs = t.Hour * 3600 + t.Minute * 60 + t.Second;
    Second = static_cast<int>(secs % 60);
    secs = (secs - Second)/60;
    Minute = static_cast<int>(secs % 60);
    secs = (secs - Minute) / 60;
    Hour = static_cast<int>(secs);
}

Time::~Time(){
    cout << "Destructing..." << Hour << ":" << Minute << ":" << Second << endl;
}

void Time::ChangeTime(int h, int m, int s){
    long secs = h * 3600 + m * 60 + s;
    Second = static_cast<int>(secs % 60);
    secs = (secs - Second)/60;
    Minute = static_cast<int>(secs % 60);
    secs = (secs - Minute) / 60;
    Hour = static_cast<int>(secs);
}

int Time::GetHour(){
    return Hour;
}

int Time::GetMinute(){
    return Minute;
}

int Time::GetSecond(){
    return Second;
}

void Time::PrintTime(){
    cout << "Time is: " << Hour << ":" << Minute << ":" << Second << endl;
}

void Time::IncreaseOneSecond(){
    long secs = Hour * 3600 + Minute * 60 + Second + 1;
    Second = static_cast<int>(secs % 60);
    secs = (secs - Second)/60;
    Minute = static_cast<int>(secs % 60);
    secs = (secs - Minute) / 60;
    Hour = static_cast<int>(secs);
}

void f(Time t){
    t.PrintTime();
}

int main(){
    Time t1 = Time();
    Time t2 = Time(2);
    Time t3 = Time(3, 50);
    Time t4 = Time(4, 59, 59);

    t1.PrintTime();
    t2.PrintTime();
    t3.PrintTime();
    t4.PrintTime();

    t1.ChangeTime(2, 3, 14);
    cout << t1.GetHour() << ":" << t1.GetMinute() << ":" << t1.GetSecond() << endl;

    t4.IncreaseOneSecond();
    // f(t4);

    cout << t1.Hour << ":" << t1.Minute << ":" << t1.Second << endl;
    return 0;
}
