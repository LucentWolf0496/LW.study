// 本代码关键：
// 1.繁而不难的分数运算类，不需要使用gcd，其实由于题设简化直接判断余数为0与否即可！
// 2.深化思维，去好好区分“带有this指针，通常返回*this解引用后的对象”的成员函数，和需要完整传递参数的全局函数
#include <iostream>
using namespace std;

class Fraction
{
    int num, den;
public:
    Fraction(){};
    Fraction(int x):num(x){ }
    Fraction(int x , int y):num(x) , den(y){ }
    operator float(){
        float temp = num / (den + 0.0);
        return temp;
    }
    friend ostream & operator<<(ostream& os , Fraction x){
        os << x.num << "/" << x.den;
        return os;
    }
    Fraction (const Fraction & x){
        num = x.num;
        den = x.den;
    }
    Fraction & operator*=(Fraction x){
        if (den % x.num == 0){// 用于进行约分处理的求余数运算检查
            den /= x.num;
            return *this;
        }
        num = num * x.num;
        return *this;
    }
    Fraction & operator/=(Fraction x){
        if (num % x.num == 0){
            num /= x.num;
            return *this;// 返回类型为该类对象的成员函数，return *this
        }
        den = den * x.num;
        return *this;
    }
    friend Fraction operator*(Fraction x , Fraction y){
        Fraction temp(x.num * y.num , x.den * y.den);
        return temp;
    }
    friend Fraction operator/(Fraction x , Fraction y){// 仔细处理乘除法的上下关系
        Fraction temp;
        if (x.num % y.num == 0){
            temp.num = x.num / y.num;
            temp.den = x.den;
        }
        else {
            temp.num = x.num;
            temp.den = x.den * y.num;
        }
        return temp;
    }
};
 
int main() {
	int a,b,c;
	cin >> a >> b >> c;
    Fraction f(a, b), g(c);// 此处g一定为整数，简化运算，不需要公约数
	f *= g;
	cout << f << endl;
	f /= g;
	cout << f << endl;
	f = f * f;
	cout << f << endl;
	f = f / g;
	cout << f << endl;
	cout << (float) f << endl;
    return 0;
}