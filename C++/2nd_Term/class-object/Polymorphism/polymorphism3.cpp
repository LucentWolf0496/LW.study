#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

class CShape {
    public:
        virtual double Area() = 0; //纯虚函数
        virtual void PrintInfo() = 0;
}; 

class CRectangle:public CShape {
    public:
        int w,h;        
        virtual double Area();
        virtual void PrintInfo();
};

class CCircle:public CShape  {
    public:
        int r;        
        virtual double Area();
        virtual void PrintInfo();
};

class CTriangle:public CShape  {
    public:
        int a,b,c;        
        virtual double Area();
        virtual void PrintInfo();
};

double CRectangle::Area()  {    
	return w * h;  
}

void CRectangle::PrintInfo()  {
    cout << "Rectangle:" << Area() << endl;
}

double CCircle::Area()  {
    return 3.14 * r * r ;
}

void CCircle::PrintInfo()  {
    cout << "Circle:" << Area() << endl;
}

double CTriangle::Area()  {
    double p = ( a + b + c) / 2.0;
    return sqrt(p * ( p - a)*(p- b)*(p - c));
}

void CTriangle::PrintInfo()  {
    cout << "Triangle:" << Area() << endl;   
}

CShape * pShapes[100];

bool MyCompare(CShape * s1, CShape * s2) { 	
    return s1->Area() < s2->Area();  	
}

// 用基类指针数组存放指向各种派生类对象的指针，然后遍历该数组，就能对各个派生类对象做各种操作，是很常用的做法
// 如果添加新的几何形体，比如五边形，则只需要从CShape派生出CPentagon,以及在main中的switch语句中增加一个case，其余部分不变！
int main()
{   
    int i; int n;
    CRectangle * pr; CCircle * pc; CTriangle * pt;
    cin >> n;
    for( i = 0;i < n;i ++ ) {
        char c;
        cin >> c;
        switch(c) {
            case 'R':
                pr = new CRectangle();
                cin >> pr->w >> pr->h;
                pShapes[i] = pr;                
                break;
	        case 'C':
                pc  = new CCircle();
                cin >> pc->r;
                pShapes[i] = pc;
                break;
            case 'T':
                pt = new CTriangle();
                cin >> pt->a >> pt->b >> pt->c;
                pShapes[i] = pt;                
                break;
        } 
    }
    sort(pShapes,pShapes + n,MyCompare);
    for( i = 0;i <n;i ++) {
        pShapes[i]->PrintInfo(); 
        delete pShapes[i];
    }
    return 0;
}
