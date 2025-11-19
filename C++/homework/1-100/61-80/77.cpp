#include <iostream>
#include <string>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int x = 0 ; x < n ; x ++){
        cin.ignore();// 在合适的位置处理输入流换行符
        string s1 , s2;
        getline(cin , s1);
        getline(cin , s2);
        int array = 0;
        for (int i = 0 ; i < s2.size() ; i ++){
            int temp1 = s1[s1.size() - 1 - i] - '0';
            int temp2 = s2[s2.size() - 1 - i] - '0';
            temp1 = temp1 - temp2 + array;
            if (temp1 < 0){
                temp1 += 10;
                array = -1;
            }
            else
                array = 0;
            s1[s1.size() - 1 - i] = '0' + temp1;
        }
        for (int i = 0 ; i < s1.size() - s2.size() ; i ++){
            if (array < 0){
                int temp1 = s1[s1.size() - s2.size() - i - 1] - '0';
                temp1 = temp1 + array;
                if (temp1 < 0){
                    temp1 += 10;
                    array = -1;
                }
                else
                    array = 0;
                s1[s1.size() - s2.size() - i - 1] = '0' + temp1;
            }
            else
                break;
        }
        while (s1[0] == 0){
            s1.erase(0 , 1);
        }
        cout << s1 << endl;
    }
}