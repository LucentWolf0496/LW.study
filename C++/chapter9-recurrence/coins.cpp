#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct coins{
    int a;// 1角
    int b;// 2角
    int c;// 5角
};

vector<int> temp(3);

void f2(int x , vector<coins> &list){
    for (int i = 0 ; i <= x / 2 ; i ++){
        temp[1] = i;
        temp[2] = x - i * 2;
        list.push_back({temp[2] , temp[1] , temp[0]});
    }
}

void f5(int x , vector<coins> &list){
    for (int i = 0 ; i <= x / 5 ; i ++){
        temp[0] = i;
        f2(x - i * 5 , list);
    }
}

int main(){
    int n = 0;
    cin >> n;
    vector<coins> list;
    f5 (n , list);
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