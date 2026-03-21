#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 

class CHugeInt {
private:
    char num[210];
public:
    CHugeInt(const char* s) {
        strcpy(num, s);
    }
    CHugeInt(int n) {
        if (n == 0) strcpy(num, "0");
        else{
            char tmp[20];
            sprintf(tmp, "%d", n);
            strcpy(num, tmp);
        }
    }
    CHugeInt(const CHugeInt & s) {
        strcpy(num, s.num);
    }
    CHugeInt& operator=(const CHugeInt& other) {
        strcpy(num, other.num);
        return *this;
    }

    friend CHugeInt operator+(const CHugeInt& a, const CHugeInt& b) {
        char res[210] = {0};
        int i = strlen(a.num) - 1;
        int j = strlen(b.num) - 1;
        int carry = 0, k = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0){
                sum += a.num[i] - '0';
                i --;
            }
            if (j >= 0){
                sum += b.num[j] - '0';
                j --;
            }
            carry = sum / 10;
            res[k] = sum % 10 + '0';
            k ++;
        }
        for (int t = 0; t < k / 2; t ++) {
            char tmp = res[t];
            res[t] = res[k - 1 - t];
            res[k - 1 - t] = tmp;
        }
        res[k] = '\0';
        return CHugeInt(res);
    }
    friend CHugeInt operator+(const CHugeInt& a, int b) {
        return a + CHugeInt(b);
    }
    friend CHugeInt operator+(int a, const CHugeInt& b) {
        return CHugeInt(a) + b;
    }

    CHugeInt& operator+=(int n) {
        *this = *this + n;
        return *this;
    }
    CHugeInt& operator++() {
        *this += 1;
        return *this;
    }
    CHugeInt operator++(int) {
        CHugeInt tmp = *this;
        ++*this;
        return tmp;
    }

    friend ostream& operator<<(ostream& os, const CHugeInt& h) {
        os << h.num;
        return os;
    }
};

int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}