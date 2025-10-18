#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> p1 = {31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
vector<int> p2 = {31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};

bool check(int year){
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        return true;
    else
        return false;
}

int get (int year , int month , int day){
    int count = 0 , sum = 0;
    for (int i = 2000 ; i < year ; i ++){
        if (check(i))
            count ++;
    }
    sum += (year - 2000) * 365 + count;

    if (check(year)){
        for (int i = 0 ; i < month - 1 ; i ++){
            sum += p2[i];
        }
        sum += day;
    }
    else{
        for (int i = 0 ; i < month - 1 ; i ++){
            sum += p1[i];
        }
        sum += day;
    }

    return (sum + 5) % 7; // 微调减去1
}

int main(){
    int n = 0;
    cin >> n;
    for (int i = 0 ; i < n ; i ++){
        int year , month , day;
        char temp;
        string num;
        cin >> year >> temp >> month >> temp >> day >> num;

        int date = get(year , month , day);
        char check = num[5];

        if (date == 1 && (check == '1' || check == '6'))
            cout << "yes" << endl;
        else if (date == 2 && (check == '2' || check == '7'))
            cout << "yes" << endl;
        else if (date == 3 && (check == '3' || check == '8'))
            cout << "yes" << endl;
        else if (date == 4 && (check == '4' || check == '9'))
            cout << "yes" << endl;
        else if (date == 5 && (check == '5' || check == '0' || check >= 'A'))
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}