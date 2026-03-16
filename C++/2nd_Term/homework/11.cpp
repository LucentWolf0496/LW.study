#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 

class CHugeInt {
private:
    char num[210]; // 存储数字字符串，无前导0
public:
    // 从字符串构造，去除前导0
    CHugeInt(const char* s) {
        while (*s == '0') ++s;
        if (*s == '\0')
            strcpy(num, "0");
        else
            strcpy(num, s);
    }
    // 从int构造
    CHugeInt(int n) {
        if (n == 0) {
            strcpy(num, "0");
        } else {
            char tmp[20];
            sprintf(tmp, "%d", n);
            strcpy(num, tmp);
        }
    }
    // 拷贝构造
    CHugeInt(const CHugeInt& other) {
        strcpy(num, other.num);
    }
    // 赋值运算符
    CHugeInt& operator=(const CHugeInt& other) {
        if (this != &other) {
            strcpy(num, other.num);
        }
        return *this;
    }
    // 加法：CHugeInt + CHugeInt
    friend CHugeInt operator+(const CHugeInt& a, const CHugeInt& b) {
        char res[210] = {0};
        int i = strlen(a.num) - 1;
        int j = strlen(b.num) - 1;
        int carry = 0, k = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a.num[i--] - '0';
            if (j >= 0) sum += b.num[j--] - '0';
            carry = sum / 10;
            res[k++] = sum % 10 + '0';
        }
        // 反转
        for (int t = 0; t < k / 2; ++t) {
            char tmp = res[t];
            res[t] = res[k - 1 - t];
            res[k - 1 - t] = tmp;
        }
        res[k] = '\0';
        return CHugeInt(res);
    }
    // 加法：CHugeInt + int
    friend CHugeInt operator+(const CHugeInt& a, int b) {
        return a + CHugeInt(b);
    }
    // 加法：int + CHugeInt
    friend CHugeInt operator+(int a, const CHugeInt& b) {
        return CHugeInt(a) + b;
    }
    // += 运算符
    CHugeInt& operator+=(int n) {
        *this = *this + n;
        return *this;
    }
    // 前置++
    CHugeInt& operator++() {
        *this += 1;
        return *this;
    }
    // 后置++
    CHugeInt operator++(int) {
        CHugeInt tmp = *this;
        ++*this;
        return tmp;
    }
    // 输出
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