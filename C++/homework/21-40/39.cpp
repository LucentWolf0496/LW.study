#include <iostream>
#include <vector>
using namespace std;

int main(){
    int k = 0;
    cin >> k;
    for (int i = 1 ; i <= k ; i ++){
        int m = 0 , n = 0 , sum = 0;
        cin >> m >> n;
        vector<vector<int>> num(m , vector<int>(n));
        for (int m1 = 0 ; m1 < m ; m1 ++){
            for (int m2 = 0 ; m2 < n ; m2 ++){
                int temp = 0;
                cin >> temp;
                num[m1][m2] = temp;
            }
        }
        if (m == 1){
            for (int m2 = 0 ; m2 < n ; m2 ++){
                sum += num[0][m2];
            }
            cout << sum << endl;
        }
        else if (m != 1 && n == 1){// 除错：仅1行或者1列需要抓出来讨论
            for (int t = 0 ; t < m ; t ++){
                sum += num[t][0];
            }
            cout << sum << endl;
        }
        else{
            for (int m2 = 0 ; m2 < n ; m2 ++){
                sum += num[0][m2];
                sum += num[m - 1][m2];
            }
            for (int t = 1 ; t < m - 1 ; t ++){
                sum += num[t][0];
                sum += num[t][n - 1];
            }
            cout << sum << endl;
        }
    }
    return 0;
}