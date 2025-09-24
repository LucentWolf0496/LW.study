#include <iostream>
#include <vector>
using namespace std;

int main(){
    struct result{
        int a;
        int b;
        int c;
    };
    vector<result> list;
    vector<vector<int>> num(5 , vector<int>(5));
    for (int i = 0 ; i < 5 ; i ++){
        for (int j = 0 ; j < 5 ; j ++){
            int temp = 0;
            cin >> temp;
            num[i][j] = temp;
        }
    }
    for (int i = 0 ; i < 5 ; i ++){
        for (int j = 0 ; j < 5 ; j ++){
            int x1 = 0 , x2 = 0;
            for (int l = 0 ; l < 5 ; l ++){
                if (num[i][j] >= num[i][l]){
                    x1 ++;
                }
                if (num[i][j] <= num[l][j]){
                    x2 ++;
                }
            }
            if (x1 == 5 && x2 == 5){
                list.push_back({i , j , num[i][j]});
            }
        }
    }
    if (list.size() == 0){
        cout << "not found" << endl;
    }
    else{
        for (int i = 0 ; i < list.size() ; i ++){
            cout << list[i].a + 1 << " " << list[i].b + 1 << " " << list[i].c << endl;
            // 不要忘了加一！辨析题目一基和数组零基的区别！！
        }
    }
    return 0;
}