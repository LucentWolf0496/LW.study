#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int p = 1 ; p <= n ; p ++){
        string s;
        cin >> s;
        cout << s << endl;
        vector<int> left;
        vector<int> right;
        for (int i = 0 ; i < s.size() ; i ++){
            if (s[i] == '(')
                left.push_back(i);
            else if (s[i] == ')')
                right.push_back(i);
        }
        for (int i = left.size() - 1 ; i >= 0 ; i --){
            for (int j = 0 ; j < right.size() ; j ++){
                if (left[i] < right[j]){
                    left.erase(left.begin() + i);
                    right.erase(right.begin() + j);
                    break;
                }
            }
        }
        string result(s.size() , ' ');
        for (int i = 0 ; i < left.size() ; i ++){
            result[left[i]] = '$';
        }
        for (int i = 0 ; i < right.size() ; i ++){
            result[right[i]] = '?';
        }
        cout << result << endl;
    }
    return 0;
}