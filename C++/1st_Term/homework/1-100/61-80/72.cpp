#include <iostream>
#include <vector>
using namespace std;// 一个类似八皇后但是各有千秋的棋盘问题，safe判断更简单，但是递归层面稍难

vector<int> list;// 思维：行列挑一个固定而非存储坐标，简化代码，避免重复，只存每行对应的列即可
int temp = 0;

bool safe(int x , int y){
    for(int i = 0 ; i < x ; i ++){
        if (y == list[i])// 较八皇后没有斜对角线的判定条件，更简洁
            return false;
    }
    return true;
}

void get(vector<vector<char>> &chess , int b , int count , int row){// 比八皇后多了“跳行”处理，count不等于row
                                                                    // count和row要严格分家，一个计数，一个表示位置
    if (count == b){// 常规求解回溯机制
        temp ++;
        return;
    }
    if (row >= chess.size()) return;
    int a = chess.size();
    for (int j = 0 ; j < a ; j ++){
        if (chess[row][j] == '#' && safe(count , j)){// row表坐标位置，count表标记数的序数计数，分列形成“跳行”
            list[count] = j;
            get(chess , b , count + 1 , row + 1);// 有可行的#，不跳行，计数且加行
        }
    }
    get(chess, b, count, row + 1);// 无可行的#，跳行，不计数，但是加行
}

int main(){
    do{
        int a , b = 0;
        cin >> a >> b;
        if (a == -1 && b == -1)// 常规跳车机制
            return 0;
        list.resize(b);// 正确的数组重载方式“resize()函数
        vector<vector<char>> chess(a , vector<char> (a));
        for (int i = 0 ; i < a ; i ++){
            for (int j = 0 ; j < a ; j ++){
                cin >> chess[i][j];
            }
        }
        get(chess , b , 0 , 0);// 由于分列计数和行数，有两个初始0变量
        cout << temp << endl;
        temp = 0;
    }while(33550336);
    return 0;
}