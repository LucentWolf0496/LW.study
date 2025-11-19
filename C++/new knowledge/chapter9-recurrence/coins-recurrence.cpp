#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct coins{
    int a;// 1角
    int b;// 2角
    int c;// 5角
};

void f5(int x , int a , int b , int c , vector<coins> &list , bool check){
    if (check)// 好用的递归退出机制，连环return即可满足条件退出
        return;
    list.push_back({a , b , c});
    while(a >= 2){
        a -= 2;
        b += 1;
        list.push_back({a , b , c});// 记得这里的结果也要导入！！
    }
    x -= 5;
    if (x < 0)
        check = true;
    f5(x , x , 0 , c + 1 , list , check);
}

int main(){
    int n = 0;
    cin >> n;
    vector<coins> list;
    bool check = false;
    f5 (n , n , 0 , 0 , list , check);
    int count = 0;
    for (int i = 0 ; i < list.size() ; i ++){
        count ++;
        cout << setfill('0') << setw(3) << count;
        cout << setfill(' ') 
             << setw(12) << list[i].a 
             << setw(12) << list[i].b 
             << setw(12) << list[i].c
             << endl;
    }
}