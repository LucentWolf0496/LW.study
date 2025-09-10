//this calculator is for 3 variables based on the former one
//Beacuse it is a code for distributing gifts with 3 levels of prices
//The number of the 3 kinds of gifts should obey certain rules for the goal of the activity
#include <iostream>
using namespace std;
int main()
{
    cout << "welcome. the budget is 5000 Yuan. " << endl;
    cout << "the price of a bag is 100 Yuan,a Tshirt is 50 Yuan and a notebook is 10 Yuan." << endl;
    cout << "and you should put the number of the gifts in a certain order to suit the need of the activivy." << endl;
    float total = 0.0;
    float bagprice = 100.0;
    float Tshirtprice = 50.0;
    float notebookprice = 10.0;
    float bagnum = 0.0;
    float Tshirtnum = 0.0;
    float notebooknum = 0.0;
    cout << "enter the bag number:";
    cin >> bagnum;
    cout << "enter the Tshirt number:";
    cin >> Tshirtnum;
    cout << "enter the notebook number:";
    cin >> notebooknum;
    total = bagprice * bagnum + Tshirtprice * Tshirtnum + notebookprice * notebooknum;
    if (total < 5000)
    {
        if (bagnum*3 < Tshirtnum && Tshirtnum*3 < notebooknum)
        {
            cout << "the number of these gifts are suitable." << endl;
            cout << "you should pay me " << total << "Yuan. " << endl;
        }
        else
        {
            cout << "the number of the gifts are not suitable." << endl;
            cout << "please lower the number of bags or Tshirts or increase the number of notebooks." << endl;
        }
    }
    else 
    {
        cout << "the total price is higher than the budget!" << endl;
    }
    return 0;
}