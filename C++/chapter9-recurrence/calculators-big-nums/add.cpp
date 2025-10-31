#include <iostream>
#include <string>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int x = 0 ; x < n ; x ++){
        string s1 , s2 , temp1;
        cin >> s1;
        cin >> s2;
        if (s1.size() <= s2.size()){
            temp1 = s1;
            s1 = s2;
            s2 = temp1;
        }
        int next = 0;
        int j = s2.size() - 1;
        for (int i = s1.size() - 1 ; i >= 0 && j >= 0 ; i --, j--){// 记得将字符转为数字
            int temp = (s2[j] - '0') + (s1[i] - '0') + next;// 不要搞过于复杂的索引
            next = temp / 10;
            s1[i] = '0' + (temp % 10);
        }
        for (int i = s1.size() - s2.size() - 1 ; i >= 0 ; i --){
            int temp = 0;
            temp = s1[i] - '0' + next;
            next = temp / 10;
            s1[i] = '0' + temp % 10;
        }
        while (next > 0){
            s1.insert(0 , 1 , '0' + (next % 10));
            next /= 10;
        }
        if (s1 == "0")
            cout << s1 << endl;
        else{
            int check = 0;
            while (s1[check] == '0'){
                check ++;
            }
            s1.erase(0 , check);
            cout << s1 << endl;
        }
    }
    return 0;
}