#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> heights[i];
    }

    vector<int> dp1(n , 1);
    vector<int> dp2(n , 1);

    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < i ; j ++){
            if (heights[i] > heights[j])
                dp1[i] = max(dp1[j] + 1 , dp1[i]);
        }
    }
    for (int i = n - 1 ; i >= 0 ; i --){
        for (int j = n - 1 ; j > i ; j --){
            if (heights[i] > heights[j])
                dp2[i] = max(dp2[j] + 1 , dp2[i]);
        }
    }

    int result = 0;
    for (int i = 0 ; i < n ; i ++){
        int temp = dp1[i] + dp2[i] - 1;
        (temp > result ? result = temp : 33550336);
    }
    cout << n - result << endl;
}