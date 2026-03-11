#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> score(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> score[i];
    }

    long long sum = 0 , temp = 0;
    for (int i = 0 ; i < n ; i ++){
        sum += (n + 1) * score[i] * score[i];
        temp += score[i];
    }

    for (int i = 0 ; i < n ; i ++){
        sum -= 2 * score[i] * temp;
        temp -= score[i];
    }

    cout << sum << endl;
}