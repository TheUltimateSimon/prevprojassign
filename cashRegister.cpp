#include<iostream>
#include<conio.h>
using namespace std;
class cashRegister
{
    private: 
        int cashOnHand;
    public:
        cashRegister();
        cashRegister(int);
        int getCurrentBalance();
        void acceptAmount(int amountReceived);
};
cashRegister:: cashRegister()
{
    cashOnHand = 500;
}
cashRegister:: cashRegister(int cash)
{
    cashOnHand = cash;
}
int cashRegister:: getCurrentBalance()
{
    return cashOnHand;
}
void cashRegister:: acceptAmount(int cash)
{
    cashOnHand += cash;
}

class dispenserType
{
    private:
        int numberOfItems;
        int cost;
    public:
        dispenserType();
        dispenserType(int, int);
        int getNoItems();
        int getCost();
        void makeSale();
};
dispenserType:: dispenserType()
{
    numberOfItems = 50;
    cost = 50;
}
dispenserType:: dispenserType(int x, int y)
{
    numberOfItems = x;
    cost = y;
}
int dispenserType:: getNoItems()
{
    return numberOfItems;
}
int dispenserType:: getCost()
{
    return cost;
}
void dispenserType:: makeSale()
{
    numberOfItems--;
}
void showselection();
void sellProduct(dispenserType& product, cashRegister& cRegister);
int main()
{
    cashRegister cRegister(500);
    dispenserType candy(10, 20);
    dispenserType chips(50, 35);
    dispenserType gum(69, 65);
    dispenserType cookies(100, 100);
    int choice;
    showselection();
    cin >> choice;
    while(choice != 5)
    {
        if(choice == 1)
        {
            sellProduct(candy, cRegister);
        }
        else if(choice == 2)
        {
            sellProduct(chips, cRegister);
        }
        else if(choice == 3)
        {
            sellProduct(gum, cRegister);
        }
        else if(choice == 4)
        {
            sellProduct(cookies, cRegister);
        }
        else if(choice > 5 || choice <= 0)
        {
            cout<<"That isn't a choice";
        }
        showselection();
        cin >> choice;
    }
    int balance = cRegister.getCurrentBalance();
    getch();
}
void showselection()
{
    cout<<"Candy Shop. Here are your selection!" << endl;
    cout<<"1.Candy   2.Chips   3.Gum   4.Cookies   5.Exit" <<endl;
    cout<<"Enter the number corresponding to the item you want" << endl;
}
void sellProduct(dispenserType& product, cashRegister& cRegister)
{
    if(product.getNoItems() > 0)
    {
        int input1, input2;
        cout<< "The cost for this product is " << product.getCost() << " cents. Please put the amount you want to enter" << endl;
        cin >> input1;
        if(input1 < product.getCost())
        {
            cout<< "Not enough! You're still need another " << product.getCost() << "cents. Please another amount: " << endl;
            cin >> input2;
            input1 += input2;
        }
        if(input1 >= product.getCost())
        {
            cRegister.acceptAmount(product.getCost());
            product.makeSale();
            cout << "Here's your item!" << endl;
        }
        else
            cout <<"Not enough after the 2nd amount! So here is what you deposited back. " << endl;
    }
    else {
        cout << "Item is sold out!" << endl;
    }
}