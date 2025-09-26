#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<vector<int>> blog(n , vector<int>(22 , 0));
    for (int i = 0 ; i < n ; i ++){// 优化输入模块，防止换行影响，对每行前两个元素单独输入赋值
        int a = 0 , k = 0;
        cin >> a >> k;
        blog[i][0] = a;
        blog[i][1] = k;
        for (int j = 2 ; j < k + 2 ; j ++){
            cin >> blog[i][j];
        }
    }
    vector<int> people(100 , 0);
    int temp = 0;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 2 ; j < 22 ; j ++){
            temp = blog[i][j];
            people[temp] += 1;
        }
    }
    int temp1 = 0 , temp2 = 0 , temp3 = 0;
    for (int i = 1 ; i < 100 ; i ++){
        if (people[i] > temp1){
            temp1 = people[i];
            temp2 = i;
        }
    }
    cout << temp2 << endl;
    vector<int> popular;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 2 ; j < 22 ; j ++){
            if (blog[i][j] == temp2){
                popular.push_back(blog[i][0]);
                break;
            }
        }
    } 
    for (int i = 0 ; i < popular.size() ; i ++){
        for (int j = i + 1 ; j < popular.size() ; j ++){// 在size不确定的时候都直接用size
            if (popular[j] == popular[i]){
                popular.erase(popular.begin() + j);// 除错，擦去重复值，便于后续排序
                j --;
            }
        }
    }
    int sum = popular.size();// size确定之后再赋值
    for (int i = 1 ; i < sum ; i ++){
        for (int j = 0 ; j < sum - i ; j ++){
            if (popular[j] > popular[j + 1]){
                temp3 = popular[j];
                popular[j] = popular[j + 1];
                popular[j + 1] = temp3;
            }
        }
    }
    cout << popular[0];
    for (int i = 1 ; i < sum ; i ++){
        cout << " " << popular[i];
    }
    cout << endl;
    return 0;
}