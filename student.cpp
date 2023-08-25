#include<iostream.h>
#include<conio.h>
#include<stdio.h>
using namespace std;

class Student {
    private:
        int admno;
        char sname[20];
        float eng, math, science;
        float total;
        float ctotal()
        {
            return eng + math +science;
        }
    public:
        void takeData()
        {
            cout<<"Enter admission number ";
            cin>> admno;
            cout<<"Enter student name " ;
            gets(sname);
            cout<< "Enter marks in english, math, science ";
            cin>>eng>>math>>science;
        }
        void showData()
        {
            cout<<"Admission number "<<admno;
            cout<<"\nStudent name "<<sname;
            cout<<"\nEnglish "<<eng;
            cout<<"\nMath "<<math;
            cout<<"\nScience "<<science;
            cout<<"\nTotal "<<total;
        }
    
};
int main()
{
    student student;
	student.takeData();
	student.showData();
	return 0;
}