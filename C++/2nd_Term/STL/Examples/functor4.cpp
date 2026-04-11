#include <iostream>
#include <iterator>
using namespace std;

class MyLess{
public:    
    bool operator() (int a1 , int a2){
        if((a1 % 10) < (a2 % 10))
            return true;
        else
            return false;
    }
};

template <class T, class Pred>
T MyMax( T * p, int n, Pred myless){
    T tmpmax = p[0];
    for( int i = 1;i < n;i ++ )
        if( myless(tmpmax,p[i]))
            tmpmax = p[i];
    return tmpmax;                         
};

bool MyCompare(int a1,int a2){
   if( ( a1 % 10 ) < (a2%10) )
       return false;
   else 
        return true;  
}

int main(){
    int a[] = {35,7,13,19,12};
    cout << MyMax(a,5,MyLess()) << endl;
    cout << MyMax(a,5,MyCompare) << endl;    
    return 0;   
}