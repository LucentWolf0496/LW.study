// 友元————类与类之间的关联
// 1.友元函数:一个类的友元函数可以访问该类的私有成员.
// 2.友元类:如果A是B的友元类，那么A的成员函数可以访问B的私有成员。
// 友元类之间的关系不能传递，不能继承。
#include <iostream>
using namespace std;

class CCar ; //提前声明 CCar类，以便后面的CDriver类使用
class CDriver{
 	public:
	   void ModifyCar( CCar * pCar) ; //改装汽车 
};
class CCar{
 	  private:
		  int price;
      friend int MostExpensiveCar( CCar cars[], int total); //声明友元
      friend void CDriver::ModifyCar(CCar * pCar);	    //声明友元
};
void CDriver::ModifyCar( CCar * pCar) {
	pCar->price += 1000; //汽车改装后价值增加 
}
int MostExpensiveCar( CCar cars[],int total) {//求最贵汽车的价格
 	 int tmpMax = -1;
 	 for( int i = 0;i < total; ++i )
 	 	  if( cars[i].price > tmpMax)
 	 	  	  tmpMax = cars[i].price;
	 return tmpMax;
}
int main(){
	 return 0;
}