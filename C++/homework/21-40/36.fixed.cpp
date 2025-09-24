#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// 判断是否为闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 计算从2000年1月1日到给定日期的总天数
long long calculateTotalDays(int day, int month, int year) {
    vector<int> normalMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<int> leapMonths = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    long long totalDays = 0;
    
    // 计算从2000年到year-1年的总天数
    for (int y = 2000; y < year; y++) {
        totalDays += isLeapYear(y) ? 366 : 365;
    }
    
    // 计算当前年的天数
    vector<int>& currentYearMonths = isLeapYear(year) ? leapMonths : normalMonths;
    for (int m = 0; m < month - 1; m++) {
        totalDays += currentYearMonths[m];
    }
    totalDays += day - 1;  // 减去1因为1月1日是第0天
    
    return totalDays;
}

int main() {
    int n = 0;
    cin >> n;
    cin.ignore();
    
    for (int i = 0; i < n; i++) {
        int hour = 0, minute = 0, second = 0, day = 0, month = 0, year = 0;
        char colon1, colon2, dot1, dot2;  // 用于存储分隔符
        
        string line;
        getline(cin, line);
        stringstream ss(line);
        
        // 方法1：直接按照格式解析（推荐）
        ss >> hour >> colon1 >> minute >> colon2 >> second >> day >> dot1 >> month >> dot2 >> year;
        
        // 方法2：如果方法1有问题，可以使用替换法
        /*
        // 将非数字字符替换为空格
        for (char& c : line) {
            if (!isdigit(c)) {
                c = ' ';
            }
        }
        
        stringstream ss2(line);
        vector<int> numbers;
        int num;
        while (ss2 >> num) {
            numbers.push_back(num);
        }
        
        if (numbers.size() >= 6) {
            hour = numbers[0];
            minute = numbers[1];
            second = numbers[2];
            day = numbers[3];
            month = numbers[4];
            year = numbers[5];
        } else {
            cerr << "输入格式错误，需要6个整数" << endl;
            continue;
        }
        */
        
        // 时间转换：常规时间 → 特殊日历时间
        long long totalSecondsInDay = hour * 3600LL + minute * 60LL + second;
        long long specialSeconds = totalSecondsInDay * 100000LL / 86400LL;
        
        int mhour = specialSeconds / 10000;
        specialSeconds %= 10000;
        int mminute = specialSeconds / 100;
        int msecond = specialSeconds % 100;  // 修正：应该是 % 100，不是 %= 100
        
        // 日期转换：计算从2000年1月1日到给定日期的总天数
        long long totalDays = calculateTotalDays(day, month, year);
        
        // 特殊日历：1000天一年，100天一月
        int myear = totalDays / 1000;
        totalDays %= 1000;
        int mmonth = totalDays / 100 + 1;  // 月份从1开始
        int mday = totalDays % 100 + 1;    // 日期从1开始
        
        cout << mhour << ":" << mminute << ":" << msecond << " " 
             << mday << "." << mmonth << "." << myear << endl;
    }
    return 0;
}