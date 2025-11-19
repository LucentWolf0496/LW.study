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
    string s1;
    get(s1 , t1);
    int a = t1.size();
    for (int i = 1 ; i < a ; i ++){
        for (int j = 0 ; j < a - i ; j ++){
            if (t1[j] < t1[j + 1]){
                int temp = t1[j];
                t1[j] = t1[j + 1];
                t1[j + 1] = temp;
            }
        }
    }
    int result = t1[0] - t1[t1.size() - 1];
    cout << a << endl;
    cout << result << endl;
    return 0;
}