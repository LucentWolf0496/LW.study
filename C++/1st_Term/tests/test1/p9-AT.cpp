#include <iostream>
#include <vector>
using namespace std;// 更简单的代码，使用数组dp完成

int main(){
    int n = 0 , m = 0;
    cin >> n >> m;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    vector<bool> check(m , false);
    int count = 0 , result = 0;
    for (int i = 0 ; i < n ; i ++){
        if (!check[list[i] - 1]){// 更新过状态后就再也不管了
            check[list[i] - 1] = true;// 索引：记得-1
            count ++;
        }
        if (count == m){
            result ++;
            for (int j = 0 ; j < m ; j ++){
                check[j] = false;
            }
            count = 0;// 记得复位count
        }
    }
    cout << result + 1 << endl;// 记得输出+1
}