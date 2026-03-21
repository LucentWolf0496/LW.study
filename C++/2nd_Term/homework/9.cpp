#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point() { };
// 在此处补充你的代码
    friend istream & operator>>(istream & is , Point & x0){
        is >> x0.x >> x0.y;
        return is;
    }
    friend ostream & operator<<(ostream & os , Point & x0){
        os << x0.x << "," << x0.y;
        return os;
    }
}; 
int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}