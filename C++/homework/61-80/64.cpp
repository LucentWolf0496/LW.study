#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool f(string x , string y){
    if (x.size() == y.size()){
        for(int i = 0 ; i < y.size() ; i ++){
            if (x[i] == y[i]) continue;
            if (x[i] > y[i])
                return true;
            else if (x[i] < y[i])
                return false;
        }
        return false;
    }
    if (x.size() > y.size()){
        for(int i = 0 ; i < y.size() ; i ++){
            if (x[i] == y[i]) continue;
            if (x[i] > y[i])
                return true;
            else if (x[i] < y[i])
                return false;
        }
        return true;
    }
    if (x.size() < y.size()){
        for(int i = 0 ; i < x.size() ; i ++){
            if (x[i] == y[i]) continue;
            if (x[i] > y[i])
                return true;
            else if (x[i] < y[i])
                return false;
        }
        return false;
    }
}

int main(){
    int n = 0;
    cin >> n;
    vector<string> list;
    for (int i = 0 ; i < n ; i ++){
        string s;
        cin >> s;
        for (int j = 0 ; j < s.size() ; j ++){
            if (s[j] >= 'A' && s[j] <= 'Z')
                s[j] = s[j] - 'A' + 'a';
            else if (s[j] >= 'a' && s[j] <= 'z')
                s[j] = s[j] - 'a' + 'A';
        }
        for (int j = 0 ; j < s.size() - j ; j ++){
            char temp = s[j];
            s[j] = s[s.size() - 1 - j];
            s[s.size() - 1 - j] = temp;
        }
        for (int j = 0 ; j < s.size() ; j ++){// 审题：加密循环左移，解密需要右移！！！
            if((s[j] >= 'a' && s[j] <= 'w') || (s[j] >= 'A' && s[j] <= 'W'))// 解密右移！！！
                s[j] = s[j] + 3;
            else
                s[j] = s[j] - 23;
        }
        list.push_back(s);
    }
    for (int j = 1 ; j < list.size() ; j ++){
        for (int k = 0 ; k < list.size() - j ; k ++){
            if(f(list[k] , list[k + 1])){
                string temp = list[k];
                list[k] = list[k + 1];
                list[k + 1] = temp;
            }
        }
    }
    for (int j = 0 ; j < list.size() ; j ++){
        cout << list[j] << endl;
    }
}