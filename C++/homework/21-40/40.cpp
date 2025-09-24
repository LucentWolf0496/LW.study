#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int f1(int x){
    int a , b , c , d;
    a = x / 1000;
    x %= 1000;
    b = x / 100;
    x %= 100;
    c = x / 10;
    x %= 10;
    d = x;
    int sum = a + b + c + d;
    return sum;
}

int main(){
    int m = 0 , n = 0 , k = 0;
    char x1 , x2;
    string s;
    getline(cin , s);
    stringstream ss(s);
    ss >> m >> x1 >> n >> x2 >> k;
    vector<int> temp1;
    for (int i = m + 1 ; i <= n - 1 ; i ++){
        if (f1(i) % k == 0){
            temp1.push_back(i);
        }
    }
    int count = 1;
    vector<int> temp2;
    do{
        for (int i = 0 ; i < temp1.size() ; i ++){
            if (f1(temp1[i]) / k == count){
                temp2.push_back(temp1[i]);
                temp1.erase(temp1.begin() + i);
                i --;
            }
        }
        cout << temp2[0];
        for (int i = 1 ; i < temp2.size() ; i ++){
            cout << "," << temp2[i];
        }
        cout << endl;
        temp2.clear();
        count ++;
    }while (temp1.size() != 0);// 反复强化vector相关函数书写规范！！
    return 0;
}