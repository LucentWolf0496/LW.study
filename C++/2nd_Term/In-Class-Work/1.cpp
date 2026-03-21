// 本代码关键：
// ++运算符要先保存自己，之后再变化，最后返回原有的值
#include <iostream>
using namespace std;
class CType{
    private:
        int num;
    public:
		CType(){}
        void setvalue(int x){num = x;}
		CType(const CType& x){num = x.num;}
		CType operator++(int){// 返回临时变量，执行增加操作，所以是不取引用的
			CType temp(*this);// 保存旧值
			num = num * num;
			return temp;
		}
		friend ostream& operator <<(ostream & os , CType x){
			os << x.num;
			return os;
		}
};
int main(int argc, char* argv[]) {
	CType obj;
	int n;		
	cin >> n;
	while(n){
		obj.setvalue(n);
		cout << obj++ << " " << obj << endl;
		cin >> n;
	}
	return 0;
}