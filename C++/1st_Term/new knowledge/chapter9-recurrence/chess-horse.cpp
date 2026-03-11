#include <iostream>
using namespace std;

int count = 0;
void f(int x , int y , int z , int w){
    if (x >= 0 && y >= 0 && x <= z && y <= w){
        f(x - 1 , y - 2 , z , w);
        f(x - 2 , y - 1 , z , w);
        f(x - 2 , y + 1 , z , w);
        f(x - 1 , y + 2 , z , w);
    }
    if (x == 0 && y == 0)
        count += 1;
}

int main(){
    int x , y;
    cin >> x >> y;// 在x*y的棋盘上从左下角只能向右跳到右上角的可能情况数，半张8*4是37，整张8*9是28（楚河汉界）
    f(x , y , x , y);
    cout << count << endl;
    return 0;
}