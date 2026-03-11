#include <iostream>
#include <string>
using namespace std;

// 数组题目总是要尤其小心索引！！！！！
// 高精度运算消灭索引干扰：设置前导‘0’保证一次完工，不需要弯弯绕绕的索引序数

string add(string x , string y){
    if (x.size() < y.size()){
        string temp = x;
        x = y;
        y = temp;
    }
    while (y.size() < x.size()){
        y = "0" + y;
    }

    int next = 0;
    string result , result1;
    for (int i = x.size() - 1 ; i >= 0 ; i --){
        int tx = x[i] - '0';
        int ty = y[i] - '0';
        int num = tx + ty + next;
        next = num / 10;
        char temp = '0' + num % 10;
        result.push_back(temp);
    }
    while(next > 0){
        char temp = '0' + next % 10;
        result.push_back(temp);
        next /= 10;
    }

    for (int i = result.size() - 1 ; i >= 0 ; i --){
        result1.push_back(result[i]);
    }
    return result1;
}

string sub(string x , string y){
    if (x == y)
        return "0";
    bool negative = false;
    if (x.size() < y.size() || (x.size() == y.size() && x < y)){
        string temp = x;
        x = y;
        y = temp;
        negative = true;
    }
    while (y.size() < x.size()){
        y = "0" + y;
    }

    int next = 0;
    string result , result1;
    for (int i = x.size() - 1 ; i >= 0 ; i --){
        int tx = x[i] - '0';
        int ty = y[i] - '0';
        int num = tx - ty + next;
        if (num < 0){
            num += 10;
            next = -1;
        }
        else
            next = 0;
        char temp = '0' + num % 10;
        result.push_back(temp);
    }

    for (int i = result.size() - 1 ; i >= 0 ; i --){
        result1.push_back(result[i]);
    }
    while(result1[0] == '0'){
        result1 = result1.substr(1);
    }
    if (negative)
        result1 = "-" + result1;
    return result1;
}

int main(){
    int n = 0;
    cin >> n;
    for (int i = 0 ; i < n ; i ++){
        string a , b;
        cin >> a >> b;
        if (a[0] == '+')
            a = a.substr(1);
        if (b[0] == '+')
            b = b.substr(1);
        
        if (a[0] != '-' && b[0] != '-')
            cout << sub(a , b) << endl;
        else if (a[0] == '-' && b[0] != '-'){
            a = a.substr(1);
            cout << "-" << add(a , b) << endl;
        }
        else if (a[0] != '-' && b[0] == '-'){
            b = b.substr(1);
            cout << add(a , b) << endl;
        }
        else if (a[0] == '-' && b[0] == '-'){
            a = a.substr(1);
            b = b.substr(1);
            cout << sub(b , a) << endl;
        }
    }
    return 0;
}