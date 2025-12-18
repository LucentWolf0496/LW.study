#include <vector>
#include <iostream>
using namespace std;

vector<int> dx = {1 , 0 , -1 , 0};
vector<int> dy = {0 , 1 , 0 , -1};

int main(){
    int n = 0;
    cin >> n;
    vector<vector<int>> table(n , vector<int>(n));
    vector<vector<int>> flu(n , vector<int>(n , false));
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> table[i][j];
        }
    }
    int a , b;
    cin >> a >> b;
    flu[a][b] = true;
    int date;
    cin >> date;
    for (int d = 0 ; d < date ; d ++){
        vector<vector<int>> temp(n , vector<int>(n , false));
        for (int i = 0 ; i < n ; i ++){
            for (int j = 0 ; j < n ; j ++){
                if (!flu[i][j]){
                    if (table[i][j] == 0){
                        for (int x = 0 ; x < 4 ; x ++){
                            int nx = i + dx[x];
                            int ny = j + dy[x];
                            if (nx >= 0 && nx < n && ny >= 0 && ny < n){
                                if (flu[nx][ny] && table[nx][ny] == 0){
                                    temp[i][j] = true;
                                    break;
                                }
                            }
                        }
                    }
                    else if (table[i][j] == 1){
                        int count = 0;
                        for (int x = 0 ; x < 4 ; x ++){
                            int nx = i + dx[x];
                            int ny = j + dy[x];
                            if (nx >= 0 && nx < n && ny >= 0 && ny < n){
                                if (flu[nx][ny] && table[nx][ny] == 0)
                                    count ++;
                            }
                        }
                        if (count == 4)
                            temp[i][j] = true;
                    }
                }
            }
        }
        for (int i = 0 ; i < n ; i ++){
            for (int j = 0 ; j < n ; j ++){
                if (temp[i][j])
                    flu[i][j] = true;
            }
        }
    }
    int result = 0;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            if (flu[i][j])
                result ++;
        }
    }
    cout << result;
}