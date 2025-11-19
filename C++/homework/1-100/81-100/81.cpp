#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int x = 0 ; x < n ; x ++){
        cin.ignore();
        vector<string> sum(3);
        vector<float> result(3 , 0.0);
        vector<bool> check(3 , false);

        cout << "Problem #" << x + 1 << endl;
        string s;
        getline(cin , s);

        for (int i = 0 ; i < s.size() - 1 ; i ++){
            if (s[i] == 'I' && s[i + 1] == '='){
                int j = i + 2;
                check[0] = true;
                while (s[j] != 'A'){
                    sum[0].push_back(s[j]);
                    j ++;
                }
            }

            else if (s[i] == 'U' && s[i + 1] == '='){
                int j = i + 2;
                check[1] = true;
                while (s[j] != 'V'){
                    sum[1].push_back(s[j]);
                    j ++;
                }
            }

            else if (s[i] == 'P' && s[i + 1] == '='){
                int j = i + 2;
                check[2] = true;
                while (s[j] != 'W'){
                    sum[2].push_back(s[j]);
                    j ++;
                }
            }
        }

        for (int i = 0 ; i < 3 ; i ++){
            if (!check[i]) continue;
            float temp = 1.0;// 初态一定为1，不然就会乘以0。。。。。
                             // 不过很重要的一点是学会了调试！一个一个在关键节点测试输出从而判断问题，是个进步~
            float get = 0.0;
            for (int j = 0 ; j < sum[i].size() ; j ++){
                if (sum[i][j] == 'm'){
                    temp = 0.001;
                    sum[i][j] = ' ';
                }
                else if (sum[i][j] == 'k'){
                    temp = 1000;
                    sum[i][j] = ' ';
                }
                else if (sum[i][j] == 'M'){
                    temp = 1000000;
                    sum[i][j] = ' ';
                }
            }

            stringstream ss(sum[i]);
            ss >> get;
            result[i] = get * temp;
        }

        if (check[0] && check[1]){
            cout << "P=" << fixed << setprecision(2) << result[0] * result[1] << "W" << endl;
        }
        else if (check[0] && check[2]){
            cout << "U=" << fixed << setprecision(2) << result[2] / (0.0 + result[0]) << "V" << endl;
        }
        else if (check[1] && check[2]){
            cout << "I=" << fixed << setprecision(2) << result[2] / (0.0 + result[1]) << "A" << endl;
        }

        if (x != n - 1)
            cout << endl;
    }
}