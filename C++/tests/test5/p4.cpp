#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main(){
    string s;
    cin >> s;
    if (s[0] >= '0' && s[0] <= '9'){
        int n = s.size();
        int num = 0;
        for (int i = 0 ; i < n ; i ++){
            int temp = s[i] - '0';
            num += temp * pow(10 , n - i - 1);
        }
        string result = "";
        for (int i = 0 ; i < num / 1000 ; i ++){
            result += "M";
        }
        num %= 1000;
        int test3 = num / 100;
        if (test3 == 9)
            result += "CM";
        else if (test3 == 8)
            result += "DCCC";
        else if (test3 == 7)
            result += "DCC";
        else if (test3 == 6)
            result += "DC";
        else if (test3 == 5)
            result += "D";
        else if (test3 == 4)
            result += "CD";
        else if (test3 == 3)
            result += "CCC";
        else if (test3 == 2)
            result += "CC";
        else if (test3 == 1)
            result += "C";
        num %= 100;
        int test2 = num / 10;
        if (test2 == 9)
            result += "XC";
        else if (test2 == 8)
            result += "LXXX";
        else if (test2 == 7)
            result += "LXX";
        else if (test2 == 6)
            result += "LX";
        else if (test2 == 5)
            result += "L";
        else if (test2 == 4)
            result += "XL";
        else if (test2 == 3)
            result += "XXX";
        else if (test2 == 2)
            result += "XX";
        else if (test2 == 1)
            result += "X";
        num %= 10;
        int test1 = num;
        if (test1 == 9)
            result += "IX";
        else if (test1 == 8)
            result += "VIII";
        else if (test1 == 7)
            result += "VII";
        else if (test1 == 6)
            result += "VI";
        else if (test1 == 5)
            result += "V";
        else if (test1 == 4)
            result += "IV";
        else if (test1 == 3)
            result += "III";
        else if (test1 == 2)
            result += "II";
        else if (test1 == 1)
            result += "I";
        cout << result;
    }
    else{
        int result = 0;
        while(s[0] == 'M'){
            s.erase(0 , 1);
            result += 1000;
        }
        if (s[0] == 'C' && s[1] == 'M'){
            s.erase(0 , 2);
            result += 900;
        }
        if (s[0] == 'C' && s[1] == 'D'){
            s.erase(0 , 2);
            result += 400;
        }
        if (s[0] == 'D'){
            s.erase(0 , 1);
            result += 500;
        }
        while(s[0] == 'C'){
            s.erase(0 , 1);
            result += 100;
        }
        if (s[0] == 'X' && s[1] == 'C'){
            s.erase(0 , 2);
            result += 90;
        }
        if (s[0] == 'X' && s[1] == 'L'){
            s.erase(0 , 2);
            result += 40;
        }
        if (s[0] == 'L'){
            s.erase(0 , 1);
            result += 50;
        }
        while(s[0] == 'X'){
            s.erase(0 , 1);
            result += 10;
        }
        if (s[0] == 'I' && s[1] == 'X'){
            s.erase(0 , 2);
            result += 9;
        }
        if (s[0] == 'I' && s[1] == 'V'){
            s.erase(0 , 2);
            result += 4;
        }
        if (s[0] == 'V'){
            s.erase(0 , 1);
            result += 5;
        }
        while(s[0] == 'I'){
            s.erase(0 , 1);
            result += 1;
        }
        cout << result;
    }
}