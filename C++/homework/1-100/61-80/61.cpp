#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string s;
    cin >> s;
    stringstream ss1(s);
    char x;
    int i = 0;
    while (ss1 >> x){
        if (!isdigit(x))
            s[i] = ' ';
        i ++;
    }
    stringstream ss2(s);
    int temp = 0;
    vector<int> result;
    while (ss2 >> temp){
        result.push_back(temp);
    }
    int sum = result.size();
    for (int i = 1 ; i < sum ; i ++){
        for (int j = 0 ; j < sum - i ; j ++){
            if(result[j] > result[j + 1]){
                int x = result[j];
                result[j] = result[j + 1];
                result[j + 1] = x;
            }
        }
    }
    if (result.size() == 0){
        cout << 0 << endl;
        return 0;
    }
    cout << result[0];
    for (int i = 1 ; i < sum ; i ++){
        cout << "," << result[i];
    }
    cout << endl;
    return 0;
}