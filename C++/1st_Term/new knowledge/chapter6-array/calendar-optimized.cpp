#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> week = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    vector<int> year = {365, 366};
    vector<vector<int>> month = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, // 平年
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}  // 闰年
    };

    int days, dayofweek;
    while ((cin >> days) && days != -1) {
        dayofweek = days % 7;
        int current_year = 2000;
        int leap_year = (current_year % 4 == 0 && current_year % 100 != 0) || (current_year % 400 == 0);
        
        while (days >= year[leap_year]) {
            days -= year[leap_year];
            current_year++;
            leap_year = (current_year % 4 == 0 && current_year % 100 != 0) || (current_year % 400 == 0);
        }
        
        int current_month = 0;
        while (days >= month[leap_year][current_month]) {
            days -= month[leap_year][current_month];
            current_month++;
        }
        
        cout << current_year << "-" << current_month + 1 << "-" << days + 1 << " " << week[dayofweek] << endl;
    }
    
    return 0;
}