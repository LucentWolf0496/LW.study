#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    cin.ignore();
    vector<int> m1 = {31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
    vector<int> m2 = {31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
    for (int i = 1 ; i <= n ; i ++)
    {
        int hour = 0 , minute = 0 , second = 0 , day = 0 , month = 0 , year = 0;
        int mhour = 0 , mminute = 0 , msecond = 0 , mday = 0 , mmonth = 0 , myear = 0;
        string s;
        getline(cin , s);
        stringstream ss(s);
        int count = 0;
        string temp;
        while (ss >> temp && count < 6) 
        {
            try 
            {
                int num = stoi(temp);
                count++;
                switch(count) 
                {
                    case 1: hour = num; break;
                    case 2: minute = num; break;
                    case 3: second = num; break;
                    case 4: day = num; break;
                    case 5: month = num; break;
                    case 6: year = num; break;
                }
            } 
            catch (const invalid_argument& e) 
            {
                continue;
            } 
            catch (const out_of_range& e) 
            {
                continue;
            }
        }
        int x = (3600 * hour + 60 * minute + second) * 100000.0 / 86400;
        mhour = x / 10000;
        x %= 10000;
        mminute = x / 100;
        x %= 100;
        msecond = x;
        int county = 0 , countm = 0;
        for (int j = 2000 ; j <= year ; j ++)
        {
            if ((j % 4 == 0) && (j % 100 != 0) || (j % 400 == 0))
            {
                county ++;
                countm = 1;
            }
            else
                countm = 0;
        }
        int y = (year - 2000) * 365 + county + day;
        if (countm == 1)
        {
            for (int k = 0 ; k < month - 1 ; k ++)
            {
                y += m2[k];
            }
        }
        if (countm == 0)
        {
            for (int k = 0 ; k < month - 1 ; k ++)
            {
                y += m1[k];
            }
        }
        myear = y / 1000;
        y %= 1000;
        mmonth = y / 100;
        y %= 100;
        mday = y;
        cout << mhour << ":" << mminute << ":" << msecond << " " << mday << "." << mmonth << "." << myear << endl;
    }
    return 0;
}