#include<iostream>
#include<conio.h>
using namespace std;
class Rectangle
{
    private:
        int length;
        int width;
    public:
        void setLength(float len);
        void setWidth(float wid);
        float perimeter();
        float area();
        void show();
        int sameArea(Rectangle other);
};
void Rectangle::setLength(float len)
{
    this->length = len;
}
void Rectangle::setWidth(float wid)
{
    this->width = wid;
}
float Rectangle::perimeter() 
{
    return (2*width)  + (2*length);
}
float Rectangle::area()
{
    return (width*length);
}
void Rectangle::show()
{
     cout << "Length: " << length << " Width: " << width <<endl;
}
int Rectangle::sameArea(Rectangle other)
{
    int area = this->area();
    if(other.area() == area)
        return 1;
    else    
        return 0;
}
int main()
{
    Rectangle first, second;
    first.setLength(5);
    first.setWidth(2.5);
    second.setLength(5);
    second.setWidth(18.9);
    first.show();
    second.show();
    cout << "Perimeter of first rectangle: " << first.perimeter() << endl;
    cout << "Area of first rectangle: " << first.area() <<endl;
    cout << "Perimeter of second rectangle: " << second.perimeter()<<endl;
    cout << "Area of second rectangle: " << second.area()<<endl;
    if(first.sameArea(second) == 1)
        cout << "These rectangle have the same area"<<endl;
    else 
        cout << "These rectangle do not have the same area"<<endl;
    first.setLength(15);
    first.setWidth(6.3);
    cout << "Perimeter of first rectangle: " << first.perimeter()<<endl;
    cout << "Area of first rectangle: " << first.area()<<endl;
    cout << "Perimeter of second rectangle: " << second.perimeter()<<endl;
    cout << "Area of second rectangle: " << second.area()<<endl;
    if(first.sameArea(second) == 1)
        cout << "These rectangle have the same area"<<endl;
    else 
        cout << "These rectangle do not have the same area"<<endl;
    return 0;
}