//it is an optimized logic game based on the former one
//it include the various logical calculations like and or not
//it is also based on a framework of "for" loop
//There are 6 best students in a high school and some of them went to Tsinghua University
//the people who went to this university are following some rules, which will be expressed by the code
//let's see who went to Tsinghua University!
#include <iostream>
using namespace std;

int main()
{
    int thu = 0;
    int rule1 = 0;
    int rule2 = 0;
    int rule3 = 0;
    int rule4 = 0;
    int rule5 = 0;
    int rule6 = 0;
    for (int a = 0 ; a <= 1 ; a = a + 1)
        for (int b = 0 ; b <= 1 ; b = b + 1)
            for (int c = 0 ; c <= 1 ; c = c + 1)
                for (int d = 0 ; d <= 1 ; d = d + 1)
                    for (int e = 0 ; e <= 1 ; e = e + 1)
                        for (int f = 0 ; f <= 1 ; f = f + 1)
                        {
                            rule1 = a || b;
                            rule2 = !(a && d);
                            rule3 = (a && e) || (a && f) || (e && f);
                            rule4 = (b && c) || (!b && !c);
                            rule5 = (c && !d) || (!c && d);
                            rule6 = d || (!d && !e);
                            if (rule1 + rule2 + rule3 + rule4 + rule5 + rule6 == 6)
                            {
                                thu = 1;
                                cout << "A: " << (a == 0 ? "didn't go " : "surely went " ) << "to Tsinghua University." << endl;
                                cout << "B: " << (b == 0 ? "didn't go " : "surely went " ) << "to Tsinghua University." << endl;
                                cout << "C: " << (c == 0 ? "didn't go " : "surely went " ) << "to Tsinghua University." << endl;
                                cout << "D: " << (d == 0 ? "didn't go " : "surely went " ) << "to Tsinghua University." << endl;
                                cout << "E: " << (e == 0 ? "didn't go " : "surely went " ) << "to Tsinghua University." << endl;
                                cout << "F: " << (f == 0 ? "didn't go " : "surely went " ) << "to Tsinghua University." << endl;
                            }
                        }
    if (thu == 0)
    {
        cout << "Everyone went to Peking University!!!" << endl;
    }
    else
    {
        cout << "There were some students who went to Tsinghua University!!!" << endl;
        cout << "Why weren't you all in Peking University???" << endl;
    }
    return 0;
}