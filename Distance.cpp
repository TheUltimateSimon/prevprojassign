#include<iostream>
#include<conio.h> 
using namespace std;
class Distance
{
    private:
        int feet;
        float inch;
    public:
        void set(int x, float y);
        void display();
        Distance add(Distance d);
};
void Distance:: set(int x, float y)
{
    this->feet = x;
    this->inch = y;
}
void Distance:: display()
{
    cout<<feet<<"\""<<inch;
 }
Distance Distance:: add(Distance d)
{
    Distance newD;
    newD.inch = inch + d.inch;
    newD.feet = 0;
    if(newD.inch > 12)
    {
        newD.inch++;
        newD.inch -= 12;
    }
    newD.feet += (feet+d.feet);
    return newD;
}
int main()
{
    Distance d1, d2, d3;
    d1.set(5, 11);
    d2.set(3, 5);
    d3 = d1.add(d2);
    cout<<"\n distance 1 is ";
    d1.display();
	cout<<"\n distance 2 is ";
	d2.display();
	cout<<"\n distance 3 is ";
	d3.display();
    return 0;
}