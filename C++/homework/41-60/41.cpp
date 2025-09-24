#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> num;
    for (int i = 0 ; i < n ; i ++){
        int temp = 0;
        cin >> temp;
        num.push_back(temp);// 谨记未初始化的vector动态数组需要用push_back添加元素！！！
    }
    int k = 0;
    cin >> k;
    for (int i = 0 ; i < num.size() ; i ++){// 使用size作为判据，在动态擦除的过程中更保险，不会出现未定义行为！！！
        if (num[i] == k){
            num.erase(num.begin() + i);
            i --;
        }
    }
    if (num.size() == 0){
        cout << endl;
    }
    cout << num[0];
    for (int i = 1 ; i < num.size() ; i ++){
        cout << " " << num[i];
    }
    return 0;
}