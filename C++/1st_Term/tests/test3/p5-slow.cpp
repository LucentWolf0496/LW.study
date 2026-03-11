#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    int result = 0;
    for (int i = 0 ; i < n ; i ++){
        for (int j = list[i] ; j >= 1 ; j --){
            int max = j;
            int temp = max;
            for (int k = i + 1 ; k < n ; k ++){
                if (list[k] >= max)
                    temp += max;
                else
                    break;
            }
            if (temp > result)
                result = temp;
        }
    }
    cout << result;
    return 0;
}