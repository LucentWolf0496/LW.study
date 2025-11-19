#include <iostream>
#include <string>
using namespace std;

int main(){// 除以13的大数除法，模拟竖式运算
    string s;
    cin >> s;
    string result;
    int sum = 0;
    while (s.size() >= 3){
        int a = 0 , b = 0 , c = 0 , temp = 0;
        a = s[0] - '0';
        b = s[1] - '0';
        c = s[2] - '0';
        sum = 10 * a + b;
        if (sum >= 13){
            temp = sum / 13;
            result.push_back(temp + '0');
            sum %= 13;
            if (sum == 0){
                s.erase(0 , 2);
                result.push_back('0');
            }
            else if (sum >= 1 && sum <= 9){
                s.erase(0 , 1);
                s[0] = sum;
            }
            else if (sum >= 10){
                int x = sum % 10;
                s[0] = 1;
                s[1] = x;
            }
        }
        else if (sum < 13){
            sum = 100 * a + 10 * b + c;
            temp = sum / 13;
            if (result.size() != 0)
                result.push_back('0');
            result.push_back(temp + '0');
            sum %= 13;
            s.erase(0 , 1);
            if (sum == 0){
                s.erase(0 , 2);
                result.push_back('0');
            }
            else if (sum >= 1 && sum <= 9){
                s.erase(0 , 1);
                s[0] = sum;
            }
            else if (sum >= 10){
                int x = sum % 10;
                s[0] = 1;
                s[1] = x;
            }
        }
    }
    if (s.size() == 2){
        int d = s[0] - '0';
        int e = s[1] - '0';
        int sum1 = 10 * d + e;
        if (sum1 < 13){
            result.push_back('0');
            sum = sum1;
        }
        else if (sum1 >= 13){
            result.push_back('0' + sum1 / 13);
            sum = sum1 % 13;
        }
    }
    else if (s.size() == 1){
        int f = s[0] - '0';
        sum = f;
    }
    else if (s.size() == 0){
        sum = 0;
    }
    cout << result << endl;
    cout << sum << endl;
    return 0;
}