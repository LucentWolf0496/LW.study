#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int main() {// 直接输出补码，笑死
    string s;
    while (cin >> s) {
        if ((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))
            break;
            
        int num = stoi(s);
        bitset<32> binary(num);
        cout << binary << endl;
    }
    return 0;
}