#include <iostream>
#include <vector>
using namespace std;

int main(){
    do{
        int n = 0;
        cin >> n;
        if (n == 0){
            return 0;// 简单退出机制
        }
        vector<vector<int>> matrix(n , vector<int>(n));//自动初始化，不需要人工清除，写vector真开心！
        for (int i = 0 ; i < n ; i ++){
            for (int j = 0 ; j < n ; j ++){
                int temp = 0;
                cin >> temp;
                matrix[i][j] = temp;
            }
        }
        vector<int> row;
        vector<int> line;
        for (int i = 0 ; i < n ; i ++){
            int sum = 0;
            for (int j = 0 ; j < n ; j ++){
                sum += matrix[i][j];  
            }
            row.push_back(sum);
        }
        for (int j = 0 ; j < n ; j ++){
            int sum = 0;
            for (int i = 0 ; i < n ; i ++){
                sum += matrix[i][j];
            }
            line.push_back(sum);
        }
        vector<int> row1;
        vector<int> line1;
        int countr = 0 , countl = 0;
        for (int i = 0 ; i < n ; i ++){
            if (row[i] % 2 == 1){
                countr ++;
                row1.push_back(i);
            }
        }
        for (int i = 0 ; i < n ; i ++){
            if (line[i] % 2 == 1){
                countl ++;
                line1.push_back(i);
            }
        }
        if (countr == 0 && countl == 0){
            cout << "OK" << endl;
        }
        else if (countr == 1 && countl == 1){
            cout << "Change bit (" << row1[0] + 1 << "," << line1[0] + 1 << ")" << endl;
            // 细节+1，因为输出是一基的，但是数组里面序号是零基的
        }
        else{
            cout << "Corrupt" << endl;
        }
    }
    while (true);
}