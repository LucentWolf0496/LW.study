#include <iostream>
#include <string>
#include <vector>
using namespace std;

void f(string &s , vector<int> &num , char b , char g){
    bool stop = false;
    if (s.size() == 0)// 退出机制，连续return回主函数
        stop = true;
    if (stop)
        return;
    for (int i = 0 ; i < s.size() - 1 ; i ++){
        if (s[i] == b && s[i + 1] == g){
            cout << num[i] << " " << num[i + 1] << endl;
            s.erase(i , 2);
            num.erase(num.begin() + i);// string只能单个擦除，就要注意序数变化问题！！
            num.erase(num.begin() + i);// 注意：！！在上一个erase之后序数发生变化，这里仍然要擦第i个。因为后续序数都-1！！
            f(s , num , b , g);// 递归
        }
    }
}

int main(){
    string s;
    cin >> s;
    char b = s[0];
    char g = s[s.size() - 1];
    vector<int> num(s.size());
    for (int i = 0 ; i < s.size() ; i ++){
        num[i] = i;
    }
    f(s , num , b , g);
}