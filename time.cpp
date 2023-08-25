#include<iostream>
#include<conio.h>
using namespace std;
class Time
{
    private:
        int hour;
        int minute;
    public:
        void settime(int x, int y);
        void showTime();
        Time sum(Time t);
};
void Time:: settime(int x, int y)
{
    this->hour = x;
    this->minute = y;
}
void Time::showTime()
{
    cout<<hour<<":"<<minute;
}
Time Time:: sum(Time t)
{
    Time newT;
    newT.minute = minute + t.minute;
    newT.hour = 0;
    if(newT.minute >= 60)
    {
        newT.hour++;
        newT.minute -= 60;
    }
    newT.hour += (hour + t.hour);
    return newT;
}
int main()
{
    Time t1, t2, t3;
    t1.settime(5, 40);
    t2.settime(3, 59);
    t3 = t1.sum(t2);
    cout<<"\n Time 1 = ";
    t1.showTime();
	cout<<"\n Time 2 = ";
	t2.showTime();
	cout<<"\n Time 3 = ";
	t3.showTime();
    return 0;
}