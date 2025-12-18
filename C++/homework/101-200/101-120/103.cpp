#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> table(4 , vector<int>(4));

int f(char x , char y){
    if (x == 'A' && y == 'A')
        return table[0][0];
    if ((x == 'A' && y == 'T') || (x == 'T' && y == 'A'))
        return table[0][1];
    if ((x == 'A' && y == 'C') || (x == 'C' && y == 'A'))
        return table[0][2];
    if ((x == 'A' && y == 'G') || (x == 'G' && y == 'A'))
        return table[0][3];
    if (x == 'T' && y == 'T')
        return table[1][1];
    if ((x == 'T' && y == 'C') || (x == 'C' && y == 'T'))
        return table[1][2];
    if ((x == 'T' && y == 'G') || (x == 'G' && y == 'T'))
        return table[1][3];
    if (x == 'C' && y == 'C')
        return table[2][2];
    if ((x == 'C' && y == 'G') || (x == 'G' && y == 'C'))
        return table[2][3];
    if (x == 'G' && y == 'G')
        return table[3][3];
}

int main(){
    int num1;
    cin >> num1;
    for (int p = 0 ; p < num1 ; p ++){
        cout << "Case #" << p + 1 << endl;
        int d = 0;
        for (int i = 0 ; i < 4 ; i ++){
            for (int j = 0 ; j < 4 ; j ++){
                cin >> table[i][j];
            }
        }
        cin >> d;
        int num2;
        cin >> num2;
        for (int q = 0 ; q < num2 ; q ++){
            string s1 , s2;
            cin >> s1 >> s2;
            if (s1.size() < s2.size()){
                string s = s1;
                s1 = s2;
                s2 = s;
            }
            int x = s1.size();
            int y = s2.size();
            
            vector<vector<int>> dp(x , vector<int>(y));
            cout << dp[x - 1][y - 1] << endl;
        } 
    }
}