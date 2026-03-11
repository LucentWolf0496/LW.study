#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Complex {
private:
    double r, i;
public:
    Complex() : r(0), i(0) {}
    Complex& operator=(const char* s) {
        const char* plusPos = strchr(s, '+');
        if (plusPos) {
            char realPart[20];
            size_t realLen = plusPos - s;
            strncpy(realPart, s, realLen);
            realPart[realLen] = '\0';
            r = atof(realPart);
            const char* iStart = plusPos + 1;
            const char* iEnd = strchr(iStart, 'i');
            if (iEnd) {
                char imagPart[20];
                size_t imagLen = iEnd - iStart;
                strncpy(imagPart, iStart, imagLen);
                imagPart[imagLen] = '\0';
                i = atof(imagPart);
            }
        }
        return *this;
    }

    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
};

int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}