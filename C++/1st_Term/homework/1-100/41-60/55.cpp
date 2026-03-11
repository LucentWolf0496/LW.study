#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){  
    int n = 0;
    cin >> n;
    for (int i = 1 ; i <= n ; i ++){

        // 读取4个部分：整数x2 小数x2
        string s01 , s02;
        string s1 , s2 , s3 , s4 , temp0;
        int count = 0;
        cin >> s01;
        cin >> s02;
        for (int j = 0 ; j < s01.size() ; j ++){
            if (s01[j] == '.'){// 一定注意比较大小是==而不是=
                s1 = s01.substr(0 , j);
                s2 = s01.substr(j + 1);
                break;
            }
        }
        for (int j = 0 ; j < s02.size() ; j ++){
            if (s02[j] == '.'){
                s3 = s02.substr(0 , j);
                s4 = s02.substr(j + 1);
                break;
            }
        }

        // 改序，长前短后
        if (s1.size() < s3.size()){
            temp0 = s1;
            s1 = s3;
            s3 = temp0;
        }
        if (s2.size() < s4.size()){
            temp0 = s2;
            s2 = s4;
            s4 = temp0;
        }

        // 处理小数部分
        for (int j = s4.size() - 1 ; j > 0 ; j --){
            s2[j] = s4[j] + s2[j] - '0';// 一定记得减去'0'！！！！才能化成数字
            if (s2[j] > '9'){
                s2[j] = s2[j] - 10;
                s2[j - 1] ++;
            }
        }
        s2[0] = s2[0] + s4[0] - '0';// 各个地方都要减去'0'！！！
        if (s2[0] > '9'){
            s2[0] -= 10;
            count ++;
        }
        for (int j = s2.size() - 1 ; j >= 0 ; j --){// 后处理模块，清除小数部分最后的一串0
            if (s2[j] != '0')// 这里的'0'要加上单引号才表示字符
                break;
            s2.erase(j , 1);
        }

        // 处理整数部分
        int m = s1.size() , n = s3.size();
        s1[m - 1] += count;
        if (m > n){
            for (int j = n - 1 ; j >= 0 ; j --){
                s1[m - n + j] = s1[m - n + j] + s3[j] - '0';
            }
            for (int j = m - 1 ; j > 0 ; j --){
                if (s1[j] > '9'){
                    s1[j] -= 10;
                    s1[j - 1] ++;
                }
            }
            if (s1[0] <= '9'){
                cout << s1 << "." << s2 << endl;
            }
            else{
                s1[0] -= 10;
                cout << "1" << s1 << "." << s2 << endl;
            }
        }
        else if (m == n){
            for (int j = n - 1 ; j > 0 ; j --){
                s1[j] = s1[j] + s3[j] - '0';
                if (s1[j] > '9'){
                    s1[j] -= 10;
                    s1[j - 1] ++;
                }
            }
            s1[0] = s3[0] + s1[0] - '0';
            if (s1[0] <= '9'){
                cout << s1 << "." << s2 << endl;
            }
            else{
                s1[0] -= 10;
                cout << "1" << s1 << "." << s2 << endl;
            }
        }
    }
    return 0;
}