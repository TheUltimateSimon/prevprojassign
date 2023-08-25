#include<iostream>
#include<conio.h>
using namespace std;
class complex
{
    private:
        int real;
        int imaginary;
    public:
        void set(float real, float imaginary);
        void display();
        complex sum(complex C);
};
void complex::set(float real, float imaginary)
{
    this->real = real;
    this->imaginary = imaginary;
}
void complex::display()
{
    cout<<real<<" + "<<imaginary << endl;
}
complex complex::sum(complex C)
{
    complex newC;
    newC.real = real + C.real;
    newC.imaginary = imaginary = C.imaginary;
    return newC;
}
int main()
{
    complex c1, c2, c3;
    c1.set(3.5, 2.3);
    c2.set(4.1, 4.2);
    c3 = c1.sum(c2);
    c1.display();
    c2.display();
    c3.display();
    return 0;
}