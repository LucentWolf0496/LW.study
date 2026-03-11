#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
    int a , b;
    string s;
    cin >> a >> s >> b;
    int sum = 0;
    string result;
    for (int i = 0 ; i < s.size() ; i ++){
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 'a' + 'A';// 改小为大
        int temp = 0;
        temp = s[i] - '0';
        if (temp > 9)
            temp -= 7;// 小心ASC II码中数字并不和大写字母直接连接，大写字母也不和小写字母直接连接
                      // 中间分别隔了7/6个其他字符，应注意改写
        sum += temp * pow(a , s.size() - i - 1);
    }
    if (sum == 0){
        cout << 0 << endl;
        return 0;
    }
    while(sum > 0){
        char temp;
        temp = '0' + sum % b;
        if (temp > '9')
            temp += 7;
        sum /= b;
        result.push_back(temp);
    }
    for (int i = 0 ; i < result.size() - i ; i ++){
        char temp = result[i];
        result[i] = result[result.size() - i - 1];
        result[result.size() - i - 1] = temp;
    }
    cout << result << endl;
    return 0;
}