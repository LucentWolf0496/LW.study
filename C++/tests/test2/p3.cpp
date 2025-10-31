#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n = 0 , x = 0;
    cin >> n >> x;
    vector<int> count(10 , 0);
    for (int i = 1 ; i <= n ; i ++){
        int m = i;
        while(m != 0){
            int temp = m % 10;
            count[temp] ++;
            m /= 10;
        }
    }
    cout << count[x] << endl;
    return 0;
}