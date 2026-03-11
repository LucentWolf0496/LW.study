#include <iostream>
#include <vector>
using namespace std;// 不用bfs，感染模式是按照天数结算，bfs队列式结算使日期混乱，不符合逻辑！！

vector<int> dx = {1 , 0 , -1 , 0};
vector<int> dy = {0 , 1 , 0 , -1};

int main(){
    int n = 0;
    cin >> n;
    vector<vector<int>> people(n , vector<int>(n));// 就用二维数组加标记即可，最多用单层bfs标记一下check！！！
    vector<pair<int , int>> infected;
    vector<vector<bool>> flu(n , vector<bool>(n , false));
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j ++){
            cin >> people[i][j];
        }
    }
    int a = 0 , b = 0;
    cin >> a >> b;
    int d = 0;
    cin >> d;

    flu[a][b] = true;
    infected.push_back({a , b});

    for (int x = 0 ; x < d ; x ++){
        vector<pair<int , int>> check;// check对每天都要更新！！！这是针对每天的临时数组
        vector<vector<bool>> thu(n , vector<bool>(n , false));// 且check数组需要去重（其实就是用单层bfs找出check？）
        for (int i = 0 ; i < infected.size() ; i ++){
            if (people[infected[i].first][infected[i].second] == 0){
                for (int j = 0 ; j < 4 ; j ++){
                    int nx = infected[i].first + dx[j];
                    int ny = infected[i].second + dy[j];
                    if (nx >= 0 && ny >= 0 && nx < n && ny < n){// 记得先判断数组边界
                        if (!flu[nx][ny] && !thu[nx][ny]){// thu数组用于去重
                            check.push_back({nx , ny});
                            thu[nx][ny] = true;
                        }
                    }
                }
            }
        }

        for (int i = 0 ; i < check.size() ; i ++){// infected在check之中添加，check去重之后infected就不用担心重复
            if (people[check[i].first][check[i].second] == 0){
                for (int j = 0 ; j < 4 ; j ++){
                    int nx = check[i].first + dx[j];
                    int ny = check[i].second + dy[j];
                    if (nx >= 0 && ny >= 0 && nx < n && ny < n){// 记得先判断数组边界
                        if (flu[nx][ny] && people[nx][ny] != 1){
                            infected.push_back({check[i].first , check[i].second});
                            break;
                        }
                    }
                }
            }
            else{
                int count = 0;
                for (int j = 0 ; j < 4 ; j ++){
                    int nx = check[i].first + dx[j];
                    int ny = check[i].second + dy[j];
                    if (nx >= 0 && ny >= 0 && nx < n && ny < n){// 记得先判断数组边界
                        if (flu[nx][ny] && people[nx][ny] != 1)
                            count ++;
                    }
                }
                if (count == 4)
                    infected.push_back({check[i].first , check[i].second});
            }
        }

        for (int i = 0 ; i < infected.size() ; i ++){// 将当日感染者标记到flu（布尔型），infected由于check去重，无需再去重
            flu[infected[i].first][infected[i].second] = true;
        }
    }

    cout << infected.size() << endl;
}