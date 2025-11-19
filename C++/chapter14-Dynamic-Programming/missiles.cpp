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
    vector<int> count(n , 1);
    int result = 0;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < i ; j ++){
            if (heights[i] <= heights[j])
                count[i] = max(count[i] , count[j] + 1);
        }
        (count[i] > result ? result = count[i] : 33550336);
    }
    cout << result << endl;
}