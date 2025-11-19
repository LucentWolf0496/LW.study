#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main ()
{
    int n = 0;
    do{
    cin >> n;
    if (n == -1)
        return 0;// 根据题干编写的退出小机制
    int n1 = n , n2 = n1;
    int date = 6;
    int month = 1;
    int day = 1;
    string d = "";
    date = (n % 7 + 6) % 7;// 0-sunday ~
    if (date == 0)
        d = "Sunday";
    if (date == 1)
        d = "Monday";
    if (date == 2)
        d = "Tuesday";
    if (date == 3)
        d = "Wednesday";
    if (date == 4)
        d = "Thursday";
    if (date == 5)
        d = "Friday";
    if (date == 6)
        d = "Saturday";
    int count = 0;
    do
    {
        if ((count % 4 == 0 && count % 100 != 0) || count % 400 == 0)
        {
            count ++;
            n1 -= 366;
        }
        else
        {
            count ++;
            n1 -= 365;
        }
    }
    while (n1 > 0);
    int year = 1999 + count;
    n1 = n2;
    int sum = year - 2000;
    int run = 1 + sum / 4 - sum / 100 + sum / 400;
    int ping = count - run;
    int countx = year;
    if ((countx % 4 == 0 && countx % 100 != 0) || countx % 400 == 0)
    {
        int n3 = n1 - (run - 1) * 366 - ping * 365 + 1;
        if(n3 >= 1 && n3 <= 31)
        {
            month = 1;
            day = n3;
        }
        else if (n3 >= 32 && n3 <= 60)
        {
            month = 2;
            day = n3 - 31;
        }
        else if (n3 >= 61 && n3 <= 91)
        {
            month = 3;
            day = n3 - 60;
        }
        else if (n3 >= 92 && n3 <= 121)
        {
            month = 4;
            day = n3 - 91;
        }
        else if (n3 >= 122 && n3 <= 152)
        {
            month = 5;
            day = n3 - 121;
        }
        else if (n3 >= 153 && n3 <= 182)
        {
            month = 6;
            day = n3 - 152;
        }
        else if (n3 >= 183 && n3 <= 213)
        {
            month = 7;
            day = n3 - 182;
        }
        else if (n3 >= 214 && n3 <= 244)
        {
            month = 8;
            day = n3 - 213;
        }
        else if (n3 >= 245 && n3 <= 274)
        {
            month = 9;
            day = n3 - 244;
        }
        else if (n3 >= 275 && n3 <= 305)
        {
            month = 10;
            day = n3 - 274;
        }
        else if (n3 >= 306 && n3 <= 335)
        {
            month = 11;
            day = n3 - 305;
        }
        else if (n3 >= 336 && n3 <= 366)
        {
            month = 12;
            day = n3 - 335;
        }
    }
    else
    {
        int n3 = n1 - (ping - 1) * 365 - run * 366 + 1;
        if(n3 >= 1 && n3 <= 31)
        {
            month = 1;
            day = n3;
        }
        else if (n3 >= 32 && n3 <= 59)
        {
            month = 2;
            day = n3 - 31;
        }
        else if (n3 >= 60 && n3 <= 90)
        {
            month = 3;
            day = n3 - 59;
        }
        else if (n3 >= 91 && n3 <= 120)
        {
            month = 4;
            day = n3 - 90;
        }
        else if (n3 >= 121 && n3 <= 151)
        {
            month = 5;
            day = n3 - 120;
        }
        else if (n3 >= 152 && n3 <= 181)
        {
            month = 6;
            day = n3 - 151;
        }
        else if (n3 >= 182 && n3 <= 212)
        {
            month = 7;
            day = n3 - 181;
        }
        else if (n3 >= 213 && n3 <= 243)
        {
            month = 8;
            day = n3 - 212;
        }
        else if (n3 >= 244 && n3 <= 273)
        {
            month = 9;
            day = n3 - 243;
        }
        else if (n3 >= 274 && n3 <= 304)
        {
            month = 10;
            day = n3 - 273;
        }
        else if (n3 >= 305 && n3 <= 334)
        {
            month = 11;
            day = n3 - 304;
        }
        else if (n3 >= 335 && n3 <= 365)
        {
            month = 12;
            day = n3 - 334;
        }
    }
    cout << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day << " " << d << endl;
    }
    while (1);
    return 0;
}