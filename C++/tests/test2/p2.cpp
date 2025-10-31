#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    if (n == 0){
        cout << "None" << endl;
        return 0;
    }
    vector<int> list(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> list[i];
    }
    for (int i = 0 ; i < n ; i ++){
        int count = 0;
        for (int j = 0 ; j < i ; j ++){
            if (list[j] < list[i])
                count ++;
        }
        for (int j = i + 1 ; j < n ; j ++){
            if (list[j] < list[i])
                count ++;
        }
        cout << count << endl;
    }
    return 0;
}