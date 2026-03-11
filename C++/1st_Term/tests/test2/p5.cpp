#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> num1(n , 0);
    vector<int> num2(n , 0);
    for (int i = 0 ; i < n ; i ++){
        cin >> num1[i];
    }
    for (int i = 0 ; i < n ; i ++){
        cin >> num2[i];
    }

    int count1 = 0;
    int count2 = 0;
    for (int i = 0 ; i < n ; i ++){
        if (num1[i] == 0)
            count1 ++;
    }
    for (int i = 0 ; i < n ; i ++){
        if (num2[i] == 0)
            count2 ++;
    }
    if (count1 != count2){
        cout << -1 << endl;
        return 0;
    }

    vector<int> zero;
    vector<int> one;
    for (int i = 0 ; i < n ; i ++){
        if (num1[i] == 1 && num2[i] == 0)
            one.push_back(i);
        else if (num1[i] == 0 && num2[i] == 1)
            zero.push_back(i);
    }

    int result = 0;
    for (int i = 0 ; i < zero.size() ; i ++){
        result += abs(zero[i] - one[i]);
    }
    cout << result << endl;
    return 0;
}