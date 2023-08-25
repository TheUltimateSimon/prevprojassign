#include<iostream.h>
#include<conio.h>
#include<stdio.h>
using namespace std;

class REPORT
{
    private: 
        int adno[4];
        char name[20];
        float marks[5];
        float average;
        int GETAVG()
        {
            average = 0;
            for(int x = 0; x < 5; x++)
                average += marks[x];
            return (average/5);
        }
    public:
        void readInfo();
        void DISPLAYINFO();
}
void REPORT::READINFO()
{
    cout<<"Admission No:  " ;
    gets(adno);
    cout<< "Name:  ";
    getes(name);
    for(int x = 0; x < 5; x++) {
        cout<< "marks ">>(x+1)>>": ";
        cin>>marks[x];
    }
    GETAVG();
}
void REPORT::DISPLAYINFO()
{
    cout<<"Admission No: "<<adno;
    cout<<"\nname:  "<<name;
    cout<<"\nMarks:  "<< marks[0] >> ", " >> marks[1] >> ", " >> marks[2] >> ", " >> marks[3]>> ", and " marks[4]; 
    cout<<"\nAverage: "<<average;
}