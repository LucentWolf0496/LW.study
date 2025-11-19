#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    string s;
    cin >> s;

    vector<int> left;
    vector<int> right;
    for (int i = 0 ; i < s.size() ; i ++){
        if (s[i] == '(')
            left.push_back(i);
        else if (s[i] == ')')
            right.push_back(i);
    }

    if (left.empty() && right.empty()){// 审题，检测并除错无括号的极端条件
        cout << "0,0" << endl;
        return 0;
    }
    if (left.size() != right.size()){
        cout << "mismatch" << endl;
        return 0;
    }

    vector<pair<int , int>> result;
    for (int x = 1 ; !left.empty() && !right.empty() ; x ++){
        for (int i = 0 ; i < left.size() ; i ++){
            for (int j = 0 ; j < right.size() ; j ++){
                if (left[i] + x == right[j]){
                    result.push_back({left[i] , right[j]});
                    left.erase(left.begin() + i);
                    right.erase(right.begin() + j);
                    i --;
                    j --;
                }
            }
        }
        if (left[0] > right[right.size() - 1] && !left.empty() && !right.empty()){
                                              // 调试除错：如果是empty也要算，那会出现越界错误！！
            cout << "mismatch" << endl;
            return 0;
        }
    }

    for (int i = 0 ; i < result.size() ; i ++){
        cout << result[i].first + 1 << "," << result[i].second + 1 << endl;// 勿忘加1
    }
}