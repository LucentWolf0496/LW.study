#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

int main(){
    do{
        string s;
        cin >> s;
        int sum = 0, count = 0;
        bool check = false;
        vector<int> result(32 , 0);
        if ((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))
            return 0;
        if (s[0] == '-'){
            check = true;
            s.erase(0 , 1);
        }
        if (s == "2147483648")// 为了规避进位，必须特考int的下界
            cout << "10000000000000000000000000000000" << endl;// 特殊情况跳过，直接输出特考
        for (int i = s.size() - 1 ; i >= 0 ; i --){
            int temp = s[i] - '0';
            sum += temp * pow(10 , s.size() - i - 1);
        }
        if (sum == 0){
            for (int i = 0 ; i < 32 ; i ++){
                cout << result[i];
            }
            cout << endl;
        }
        else if (sum > 0){
            if (check)
                sum -= 1;
            while (sum > 0){
                int temp = sum % 2;
                result[31 - count] = temp;
                count ++;
                sum /= 2;
            }
            if (check){
                for (int i = 0 ; i < 32 ; i ++){
                    if (result[i] == 0)
                        result[i] = 1;
                    else if (result[i] == 1)
                        result[i] = 0;
                }
            }
            for (int i = 0 ; i < 32 ; i ++){
                cout << result[i];
            }
            cout << endl;
        }
    }while (20230831);
}