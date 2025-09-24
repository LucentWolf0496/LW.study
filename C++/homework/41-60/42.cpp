#include <iostream>
#include <vector>
using namespace std;

int main(){
    struct student{
        int id;
        float score;
    };
    int n = 0 , k = 0;
    cin >> n >> k;
    vector<student> list(n);
    for (int i = 0 ; i < n ; i ++){
        int temp1 = 0.0;
        float temp2 = 0.0;
        cin >> temp1 >> temp2;
        list[i] = {temp1 , temp2};// 使用push_back一样可行
    }
    for (int i = 1 ; i < n ; i ++){
        for (int j = 0 ; j < n - i ; j ++){
            if (list[j].score < list[j + 1].score){
                student temp = list[j];// 对student类型变量使用temp！直接按分数对student变量排序！
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    cout << list[k - 1].id << " " << list[k - 1].score << endl;
    return 0;
}