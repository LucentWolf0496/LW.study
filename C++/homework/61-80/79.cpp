#include <iostream>
#include <vector>
using namespace std;

int get(int x , int y , vector<vector<int>> table){
    int result = 0;
    int i = 0 , j = 0;
    int temp = table[0].size();

    while (table[x + i][y] == 0){
        while (table[x + i][y + j] == 0){
            j ++;
            if (y + j >= table[0].size())
                break;
        }
        i ++;
        if (j < temp)
            temp = j;
        else
            j = temp;// 这里需要取矩形宽度的最小值，使用temp加以记录，否则可能在里面包住1
        if (i * j > result)
            result = i * j;
        j = 0;
        if (x + i >= table.size())
            break;
    }

    return result;
}

int main(){
    int m , n;
    cin >> m >> n;
    vector<vector<int>> table(m , vector<int> (n));
    for (int i = 0 ; i < m ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> table[i][j];
        }
    }

    int result = 0;
    for (int i = 0 ; i < m ; i ++){
        for (int j = 0 ; j < n ; j ++){
            if (table[i][j] == 1) continue;
            int temp = get(i , j , table);
            if (temp > result)
                result = temp;
        }
    }

    cout << result << endl;
}