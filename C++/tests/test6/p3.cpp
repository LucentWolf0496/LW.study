#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int m , n;
    cin >> m >> n;
    vector<string> list1(m);
    vector<int> list2(m);
    for (int i = 0 ; i < m ; i ++){
        cin >> list1[i];
        if (list1[i] == "JUMP") cin >> list2[i];
        else list2[i] = 0;
    }
    int now = 0;
    for (int i = 0 ; i < n - 1 ; i ++){
        if (list1[now] == "JUMP") now += list2[now];
        else if (list1[now] == "NEXT") now ++;
        else break;
    }
    cout << now + 1;
}