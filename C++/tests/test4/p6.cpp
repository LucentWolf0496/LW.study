#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool check(vector<int> num){
    if (num.size() == 1 || num.size() == 2)
        return true;
    sort(num.begin() , num.end());
    int d = num[1] - num[0];
    int n = num.size();
    for (int i = 0 ; i < n - 1 ; i ++){
        if (num[i + 1] - num[i] != d)
            return false;
    }
    return true;
}

int main(){
    int t = 0;
    cin >> t;
    for (int i = 0 ; i < t ; i ++){
        int n = 0;
        cin >> n;
        vector<int> list(n);
        for (int j = 0 ; j < n ; j ++){
            cin >> list[j];
        }
        int count = 0;
        for (int j = 1 ; j <= n - 1 ; j ++){
            vector<int> list1(j);
            vector<int> list2(n - j);
            for (int k = 0 ; k < j ; k ++){
                list1[k] = list[k];
            }
            for (int k = 0 ; k < n - j ; k ++){
                list2[k] = list[j + k];
            }
            if (check(list1) && check(list2))
                count ++;
        }
        cout << count << endl;
    }
    return 0;
}