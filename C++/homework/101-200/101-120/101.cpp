#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n ;
    cin >> n;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    sort(list.begin() , list.end());
    reverse(list.begin() , list.end());
    vector<vector<int>> dp(n , vector<int>(5001 , 1));
    int first = 0;
    int cha = 0;
    int size = 0;
    vector<int> check(5001 , 0);
    for (int i = 0 ; i < 5000 ; i ++){
        for (int j = i + 1 ; j < n ; j ++){
            check[list[i] - list[j]] ++;
        }
    }
    int num = 0;
    vector<int> aaa;
    for (int i = 0 ; i < 5001 ; i ++){
        if (check[i] >= 2){
            num ++;
            aaa.push_back(i);
        }
    }
    for (int p = 0 ; p < num && aaa[p] < 250 ; p ++){
        int i = aaa[p];
        int temp = 0;
        for (int j = 0 ; j < n ; j ++){
            for (int k = 0 ; k < j ; k ++){
                if (list[k] - list[j] == i){
                    dp[j][i] = max(dp[j][i] , dp[k][i] + 1);
                }
            }
            temp = max(temp , dp[j][i]);
        }
        if (temp >= size){
            size = temp;
            cha = i;
        }
    }
    for (int i = 0 ; i < n ; i ++){
        if (dp[i][cha] == size){
            first = i;
            break;
        }
    }
    first = list[first];
    if (size < 3){
        cout << "NO" << endl;
        return 0;
    }
    cout << first;
    for (int i = 1 ; i < size ; i ++){
        cout << "," << first + i * cha;
    }
    cout << endl;
    return 0;
}