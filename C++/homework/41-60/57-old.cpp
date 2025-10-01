#include <iostream>
#include <string>
using namespace std;

int main(){
    int n = 0 , check = 0;
    string s1 = "000000000000000000000000000000000000001";// 较劣，需要手动补充0和擦去0，不如insert补0
    cin >> n;
    for (int i = 1 ; i <= n ; i ++){
        for (int j = 0 ; j < s1.size() ; j ++){
            s1[j] = '0' + (s1[j] - '0') * 2;
        }
        for (int j = s1.size() - 1 ; j >= 1 ; j --){
            if (s1[j] > '9'){
                s1[j] -= 10;
                s1[j - 1] ++;
            }
        }
    }
    for (int i = 0 ; i < s1.size() ; i ++){
        if (s1[i] != '0'){
            check = i;
            break;
        }
    }
    s1.erase(0 , check);
    cout << s1 << endl;
    return 0;
}