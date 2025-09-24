#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

void get(string &x , vector<int> &t){// 加&修正为传递引用，否则只会传值，不会对主函数造成影响！！
    getline(cin , x);
    for (char& c : x){
        if(!isdigit(c)){
            c = ' ';
        }
    }
    stringstream ss(x);
    int num;
    while(ss >> num){
        t.push_back(num);
    }
}

int main(){
    vector<int> t1;
    vector<int> t2;
    string s1 , s2;
    get(s1 , t1);
    get(s2 , t2);
    int num = t1.size();
    int count = 0 , temp = 0;
    for (int i = 0 ; i < 1000 ; i ++){
        for (int j = 0 ; j < num ; j ++){
            if (i >= t1[j] && i < t2[j]){
                temp ++;
            }
        }
        if (temp > count){
            count = temp;
        }
        temp = 0;// 注意对中间暂存量temp清零！！！
    }
    cout << num << " " << count << endl;
}