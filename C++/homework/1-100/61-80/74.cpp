#include <iostream>
#include <string>
using namespace std;

int main(){
    string s1 , s2 , s3;
    getline(cin , s1);
    getline(cin , s2);
    getline(cin , s3);
    s1.push_back(' ');// 补充空格是为了更准确判断“单词”，因为单词全部由空格分隔
    s1.insert(0 , 1 , ' ');// 在索引0处插入长度为1的' '
    for (int i = 0 ; i < s1.size() - s2.size() + 1 ; i ++){
        bool check = true;
        for (int j = 0 ; j < s2.size() ; j ++){
            if (s1[i + j] != s2[j])
                check = false;
        }
        if (s1[i + s2.size()] != ' ' || s1[i - 1] != ' ')
            check = false;
        if (check){
            for (int j = 0 ; j < s2.size() ; j ++){
                s1.erase(i , 1);
            }
            for (int j = s3.size() - 1 ; j >= 0 ; j --){
                s1.insert(i , 1 , s3[j]);
            }
            i = i - s2.size() + s3.size();
        }
    }
    s1.erase(s1.size() - 1 , 1);
    s1.erase(0 , 1);
    cout << s1 << endl;
}