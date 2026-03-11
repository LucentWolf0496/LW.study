// 区间问题综合————反正都会用预排序+贪心，审题看怎么排序/怎么贪心
// 这个字符串分割问题就是贪心套上了皮套，但要注意细节，要去包含最后一段区间，并且要维护curmin变量
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

static bool check(vector<int> a , vector<int> b){
    return a[0] < b[0];
}

int main(){
    string s;
    cin >> s;
    vector<vector<int>> table(26 , vector<int>(2 , -1));
    for (int i = 0 ; i < s.size() ; i ++){
        int temp = s[i] - 'a';
        if (table[temp][0] == -1) table[temp][0] = i;
        table[temp][1] = i;
    }
    sort(table.begin() , table.end() , check);
    int curmin = 0;
    int curmax = 0;
    int temp = 0;
    vector<int> result;
    for (int i = 0 ; i < 26 ; i ++){
        if (table[i][0] == -1) continue;
        if ((i == 0 && table[i][0] != -1) || (table[i - 1][0] == -1 && table[i][0] != -1)) curmax = table[i][1];
        if (table[i][0] <= curmax) curmax = max(curmax , table[i][1]);
        else{
            result.push_back(curmax - curmin + 1);
            curmin = table[i][0];
            curmax = table[i][1];
        }
    }
    result.push_back(s.size() - curmin);
    for (int i = 0 ; i < result.size() ; i ++){
        cout << result[i] << " ";
    }
    return 0;
}