#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(){
    string s;
    int n;
    cin >> s >> n;
    int cycle = 2 * n - 2;
    vector<vector<char>> table(n , vector<char> (1001, ' '));
    if (n == 1){
        cout << s << endl;
        return 0;
    }
    for (int i = 0 ; i < s.size() ; i ++){
        int a = i / cycle;
        int b = i % cycle;
        if (b < n) table[b][(n - 1) * a] = s[i];
        else table[2 * n - 2 - b][(n - 1) * a + b - n + 1] = s[i];
    }
    string result = "";
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < 1001 ; j ++){
            if (table[i][j] != ' ')
                result.push_back(table[i][j]);
        }
    }
    cout << result;
}