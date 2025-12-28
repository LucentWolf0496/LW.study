// 随机数算法-NeiKos_28
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

// 定义基础参量
int color = 0;// 我所执子颜色（1为黑，2为白，棋盘状态亦同）
int botColor = 0;// bot的颜色
int gameRound = 1;// 游戏轮次
vector<vector<int>> gridInfo(8 , vector<int> (8 , 0));// 先x后y，记录棋盘状态，未被占据为0
vector<int> dx = {-1 , -1 , -1 , 0 , 0 , 1 , 1 , 1};// 8个方向
vector<int> dy = {-1 , 0 , 1 , -1 , 1 , -1 , 0 , 1};// 8个方向
struct Move {// 结构体打包一次行动
    int x0, y0;// 起点
    int x1, y1;// 终点
    int x2, y2;// 障碍位置
};
random_device rd;
mt19937 gen(rd());// 随机数生成引擎
int rx0 , ry0 , rx1 , ry1 , rx2 , ry2;

// 函数声明
void singleTurnBot();// 函数1：正常/挑战模式-bot-单轮对局
bool inMap(int x , int y);// 函数2：inMap判断是否在地图内
vector<Move> canMove(int color , const vector<vector<int>> &table);// 函数3：canMove遍历求解所有可动的位置
int randomNum();// 函数4：生成1-10000随机整数
void newGame();// 函数5：新游戏，初始化棋盘状态

// 函数1：bot-单轮对局
void singleTurnBot(){
    vector<Move> possibleMoves = canMove(botColor , gridInfo);// 虚设canMove得到的数组，避免多次调用canMove函数，大大节省时间
    int n = possibleMoves.size();// 直接用成品数组，防止多次调用
    int ran = randomNum();
    ran %= n;
    Move move = possibleMoves[ran];
    rx0 = move.x0;
    ry0 = move.y0;
    rx1 = move.x1;
    ry1 = move.y1;
    rx2 = move.x2;
    ry2 = move.y2;
    cout << ry0 << ' ' << rx0 << ' ' << ry1 << ' ' << rx1 << ' ' << ry2 << ' ' << rx2 << endl;
}

// 函数2：inMap判断是否在地图内
bool inMap(int x , int y){
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
		return false;
	return true;
}

// 函数3：canMove遍历求解所有可动的位置
vector<Move> canMove(int color , const vector<vector<int>> &table) {// 带入色号检查，黑子1，白子2；双变量便于搜索时不干扰现有棋盘
    vector<Move> moves;    
    for (int x0 = 0 ; x0 < 8 ; x0 ++) {// 找到所有己方棋子(基于己方棋子行动)
        for (int y0 = 0 ; y0 < 8 ; y0 ++) {
            if (table[x0][y0] != color) continue;

            for (int dir = 0 ; dir < 8 ; dir ++) {// 枚举移动目标位置
                for (int step = 1 ; step < 8 ; step ++) {
                    int x1 = x0 + dx[dir] * step;
                    int y1 = y0 + dy[dir] * step;
                    if (!inMap(x1 , y1) || table[x1][y1] != 0) break; // 转换枚举方向，到此为止

                    for (int dir2 = 0 ; dir2 < 8 ; dir2++) {// 枚举障碍放置位置
                        for (int step2 = 1 ; step2 < 8 ; step2 ++) {
                            int x2 = x1 + dx[dir2] * step2;
                            int y2 = y1 + dy[dir2] * step2;
                            if (!inMap(x2 , y2)) break; // 转换枚举方向，到此为止(先判防止越界)
                            if (table[x2][y2] == 0 || (x2 == x0 && y2 == y0)) moves.push_back({x0 , y0 , x1 , y1 , x2 , y2});
                            // 障碍可以放在空位或自己的起点,加入可能的移动
                            if (table[x2][y2] != 0 && !(x2 == x0 && y2 == y0)) break;// 转换枚举方向，到此为止
                        }
                    }
                }
            }
        }
    }
    return moves;
}

// 函数4：生成1-10000随机整数
int randomNum(){
    static uniform_int_distribution<> dis(1, 10000);
    return dis(gen);
}

// 函数5：新游戏，初始化棋盘状态
void newGame(){
    gridInfo[0][2] = 1;
    gridInfo[0][5] = 1;
    gridInfo[2][0] = 1;
    gridInfo[2][7] = 1;
    gridInfo[5][0] = 2;
    gridInfo[5][7] = 2;
    gridInfo[7][2] = 2;
    gridInfo[7][5] = 2;
    int tx0 , ty0 , tx1 , ty1 , tx2 , ty2;
    vector<Move> list;
    cin >> gameRound;
    cin >> ty0 >> tx0 >> ty1 >> tx1 >> ty2 >> tx2;
    if (ty0 == -1){
        color = 2;
        botColor = 1;
    }
    else{
        color = 1;
        botColor = 2;
        Move move = {tx0 , ty0 , tx1 , ty1 , tx2 , ty2};
        list.push_back(move);
    }
    for (int i = 0 ; i < 2 * gameRound - 2 ; i ++){
        cin >> ty0 >> tx0 >> ty1 >> tx1 >> ty2 >> tx2;
        Move move = {tx0 , ty0 , tx1 , ty1 , tx2 , ty2};
        list.push_back(move);
    }
    int n = list.size();
    int num = 0;
    for (int i = 0 ; i < n ; i ++){
        Move x = list[i];
        num ++;
        if (num % 2 == 1){
            gridInfo[x.x0][x.y0] = 0;
            gridInfo[x.x1][x.y1] = 1;
            gridInfo[x.x2][x.y2] = 3;
        }
        else if (num % 2 == 0){
            gridInfo[x.x0][x.y0] = 0;
            gridInfo[x.x1][x.y1] = 2;
            gridInfo[x.x2][x.y2] = 3;
        }
    }
    gameRound = gameRound * 2 - 2 + botColor;
}

// 主函数：启动器
int main(){
    newGame();
    singleTurnBot();
    return 0;
}