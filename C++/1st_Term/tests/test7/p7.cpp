#include <iostream>
#include <string>
#include <vector>
using namespace std;

string f(string x , string y){
    int m = x.size();
    int n = y.size();
    string final;
    vector<int> result(m + n , 0);
    for (int i = 0 ; i < m ; i ++){
        for (int j = 0 ; j < n ; j ++){
            int temp1 = x[m - i - 1] - '0';
            int temp2 = y[n - j - 1] - '0';
            result[i + j] += temp1 * temp2;
            while (result[i + j] >= 10){
                result[i + j] -= 10;
                result[i + j + 1] ++;
            }
        }
    }
    for (int i = 0 ; i < m + n ; i ++){
        char temp = '0' + result[m + n - i - 1];
        final.push_back(temp);
    }
    return final;
}

int main(){
    string s;
    int n;
    while (cin >> s >> n){
        int point = 0;
        for (int i = 0 ; i < s.size() ; i ++){
            if (s[i] != '.') point ++;
            if (s[i] == '.'){
                s.erase(point , 1);
                break;
            }
        }
        int size = s.size();
        point = size - point;
        string result = s;
        for (int i = 1 ; i <= n - 1 ; i ++){
            result = f(result , s);
        }
        int final = result.size();
        result.insert(final - n * point , ".");
        for (int i = 0 ; i < result.size() ; i ++){
            if (result[0] == '0') result.erase(0 , 1);
            else break;    
        }
        int final1 = result.size();
        for (int i = 0 ; i < final1 ; i ++){
            if (result[result.size() - 1] == '0') result.erase(result.size() - 1 , 1);
            else break;
        }
        if (result[result.size() - 1] == '.') result.erase(result.size() - 1 , 1);
        if (result.empty()) result = "0";
        cout << result << endl;
    }
    return 0;
}