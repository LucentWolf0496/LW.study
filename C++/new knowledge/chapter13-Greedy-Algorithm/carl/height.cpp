// 身高重新排列————保证有解
// 贪心法：先排序，后按顺序插入值，由于保证有解，于是就从身高大到小、前有人数小到大插值
// 这样就能保证正确了，举例子推一推也是一样的
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

static bool check(vector<int> &a , vector<int> &b){
    if (a[0] > b[0]) return true;
    if (a[0] < b[0]) return false;
    if (a[0] == b[0]) return a[1] < b[1];
    return -1;
}

int main(){
    int n = 0;
    cin >> n;
    vector<vector<int>> people(n , vector<int> (2 , 0));
    for (int i = 0 ; i < n ; i ++){
        cin >> people[i][0] >> people[i][1];
    }
    sort(people.begin() , people.end() , check);
    vector<vector<int>> result;
    for (int i = 0 ; i < n ; i ++){
        result.insert(result.begin() + people[i][1] , people[i]);
    }
    for (int i = 0 ; i < n ; i ++){
        cout << result[i][0] << " " << people[i][1] << endl;
    }
    return 0;
}