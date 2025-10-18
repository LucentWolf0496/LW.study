#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    for (int x = 0 ; x < n ; x ++){
        string s;
        cin >> s;
        vector<int> list(26 , 0);
        for (int i = 0 ; i < s.size() ; i ++){
            list[s[i] - 'a'] ++;
        }
        int temp = 0;
        for (int i = 0 ; i < 26 ; i ++){
            if (list[i] > temp)
                temp = list[i];
        }
        for (int i = 0 ; i < 26 ; i ++){
            if (list[i] == temp){
                char res = 'a' + i;
                cout << res << " " << temp << endl;
                break;
            }
        }
    }
}