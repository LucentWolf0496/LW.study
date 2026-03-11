#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char str[31];
    cin.getline(str, 31);
    char *p = str;
    while (*p != '\0') {
        if (isdigit(*p)) {
            char *numStart = p;
            while (isdigit(*p)) {
                cout << *p;
                p++;
            }
            cout << endl;
        } 
        else
            p++;
    }
    return 0;
}