#include <iostream>
using namespace std;

int step = 1;// 记得初始化步数变量step
void move(int , char , char , char);// 函数声明，不需要点名参数名字，只需要说明变量类型

int main(){
    int n;
    cin >> n;
    move(n , 'A' , 'B' , 'C');// 将n个从小到大放置的盘子从A柱移到C柱，以B柱空置辅助。单引号对应char类型！ 
    cout << "step is " << step - 1 << endl;
    return 0;                        
}

void move(int m , char p , char q , char r){// 可以用void，因为输出也在move子函数之中，调用后主函数结束
    if (m == 1){
        cout << "[" << "step" << step << "]" << "move 1# from " << p << " to " << r << endl;
        step ++;
    }
    else{
        move(m - 1 , p , r , q);// 关键！！先将前m-1个从p到q，以r为空置，再直接输出将底座m从p到r
        cout << "[" << "step" << step << "]" << "move " << m << "# from " << p << " to " << r << endl;
        step ++;// 勿漏将底座从p到r的步数增加！
        move(m - 1 , q , p , r);// 最后将前m-1个从q到r的底座上，以p为空置
    }
}