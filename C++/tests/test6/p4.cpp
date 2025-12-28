#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(){
    string s;
    getline(cin , s);
    int n = s.size();
    int result = 0;
    vector<int> init(1000 , 0);
    vector<int> check(1000 , 0);
    for (int i = 0 ; i < n ; i ++){
        int temp = 0;
        int start = i;
        int p = 0;
        while(start < n){
            p = s[start] - '0' + 100;
            check[p] ++;
            if (check[p] >= 2) break;
            temp ++;
            start ++;
        }
        if (temp > result) result = temp;
        check = init;
    }
    cout << result;
}