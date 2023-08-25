#include<iostream.h>
#include<conio.h>
#include<stdio.h>
using namespace std;

class batsman {
    private:
        char bcode[4];
        char bname[20];
        int innings, notouts, runs;
        int batavg;
        void calcavg()
        {
            batavg = runs/(innings - notouts);
        }
    public:
        void takeData()
        {
            cout<<"Enter bat code: ";
            gets(bcode);
            cout<<"Enter name " ;
            gets(bname);
            cout<< "Enter his innings, non-outs, and runs ";
            cin>>innings>>notouts>>runs;
            calcavg();
        }
        void showData()
        {
            cout<<"Bat code "<<bcode;
            cout<<"\nname "<<bname;
            cout<<"\nInnings "<<innings;
            cout<<"\nnot outs "<<notouts;
            cout<<"\nruns "<<runs;
            cout<<"\nTotal "<<batavg;
        }
}