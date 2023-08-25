#include<iostream.h>
#include<conio.h>
#include<stdio.h>
using namespace std;
class TEST
{
    private:
        int TestCode;
        string description;
        int noCandiate;
        int CenterReqD;
        void CALCNTR()
        {
            CenterReqD = (noCandiate / 100 + 1);
        }
    public:
        void SCHEDULE()
        {
            cout<<"enter the description: " ;
            gets(description);
            cout<< "Enter his test code and his candiate no. ";
            cin>>TestCode>>noCandiate;
            CALCNTR();
        }
        void DISPTEST()
        {
            cout<<"Test Code: "<<Test Code;
            cout<<"\nCandiate Number:  "<<noCandiate;
            cout<<"\nDescription "<<description;
            cout<<"\nCenters required "<<CenterReqD;
        }
}