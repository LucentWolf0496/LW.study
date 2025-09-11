//1st example of the book
//use num 0~3 to represent the 4 people
//who is the one who went into Tsinghua University?
#include <iostream>
using namespace std;

int main()
{
    int g = 0;
    for (int k = 0; k < 4; k = k + 1)
    {
        if(((k != 0) + (k == 2) + (k == 3) + (k != 3)) == 3)
        {
            cout << "the one who went into Tsinghua University is : " << char('A' + k) << endl;
            g = 1;
        }
    }
    if (g == 0)
    {
       cout << "no answer!" << endl;
    }
    return 0;
}