#include<iostream.h>
#include<conio.h>
#include<stdio.h>
using namespace std;

class Book
{
    private: 
        int BookNo;
        char bookTitle[20];
        float price;
        int totalCost(int N)
        {
            return (price * N);
        }
    public:
        void INPUT()
        {
            cout<<"Enter Book Title:  " ;
            gets(bookTitle);
            cout<< "Enter book No and price ";
            cin>>BookNo>>price;
        }
        void PURCHASE()
        {
            int N
            cout<<"Enter copies bought:  " ;
            cin>>N;
            cout<<"Total Cost is ">> totalCost(N);
        }
}