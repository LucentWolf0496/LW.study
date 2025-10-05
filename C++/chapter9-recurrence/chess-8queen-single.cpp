#include <iostream>
#include <vector>
using namespace std;

vector<int> row;
vector<int> line;
void f(int x , int y , int z){
    int count = 1 , check = 0;
    row.push_back(x);
    line.push_back(y);
    for (int i = 1 ; i <= z ; i ++){
        for (int j = 1 ; j <= z ; j ++){
            for (int m = 0 ; m < row.size() ; m ++){
                if (i != row[m] && j != line[m] && abs(i - row[m]) != abs(j - line[m]))
                    check ++;
            }
            if (check == row.size()){
                row.push_back(i);
                line.push_back(j);
                count ++;
            }
            check = 0;
        }
    }
    if (count == 8){// 贪心算法，找到一种可能之后不继续回溯找，无法遍历所有情况，只找到极少“理想情况”
        for (int i = 0 ; i < 8 ; i ++){// 应用递归实现回溯算法
            cout << row[i] << "-" << line[i] << endl;
        }
        cout << endl;
    }
    row.clear();
    line.clear();
    if (x == 8 && y == 8)
        return;
    else if (x < 8 && y == 8)
        f(x + 1 , 1 , 8);
    else
        f(x , y + 1 , 8);
}


int main(){
    f(1 , 1 , 8);
    return 0;
}