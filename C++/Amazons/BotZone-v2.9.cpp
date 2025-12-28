// 单层评估搜索算法NeiKos_496
#include <iostream>
#include <string>
#include <vector>
#include <queue>
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
vector<vector<double>> spec = {// 随对局更改的估价函数参数
    {10.0 ,  1.0  , 3.0} ,
    {3.0  ,  5.0  , 1.0} , 
    {0.5  , 100.0 , 0.0}
};
vector<vector<int>> valuePos = {// 估价函数中位置价值所用数组
    {1 , 2 , 3 , 4 , 4 , 3 , 2 , 1} ,
    {2 , 3 , 4 , 5 , 5 , 4 , 3 , 2} ,
    {3 , 4 , 5 , 6 , 6 , 5 , 4 , 3} ,
    {4 , 5 , 6 , 7 , 7 , 6 , 5 , 4} ,
    {4 , 5 , 6 , 7 , 7 , 6 , 5 , 4} ,
    {3 , 4 , 5 , 6 , 6 , 5 , 4 , 3} ,
    {2 , 3 , 4 , 5 , 5 , 4 , 3 , 2} ,
    {1 , 2 , 3 , 4 , 4 , 3 , 2 , 1}
};
struct bfs{// 用于KingMove中的bfs求解过程
    int x;
    int y;
    int dis;
};
int rx0 , ry0 , rx1 , ry1 , rx2 , ry2;

// 函数声明
void singleTurnBot();// 函数1：正常/挑战模式-bot-单轮对局
bool inMap(int x , int y);// 函数2：inMap判断是否在地图内
vector<Move> canMove(int color , const vector<vector<int>> &table);// 函数3：canMove遍历求解所有可动的位置
double evaluate(const vector<vector<int>> &table , int botColor , int round);// 函数4：评估函数中控模块
int QueenMove(const vector<vector<int>> &table , int botColor);// 函数5：QueenMove模块
int KingMove(const vector<vector<int>> &table , int botColor);// 函数6：KingMove模块
int position(const vector<vector<int>> &table , int botColor);// 函数7：位置价值模块
void newGame();// 函数8：新游戏，初始化棋盘状态

// 函数1：bot-单轮对局
void singleTurnBot(){
    vector<Move> possibleMoves = canMove(botColor , gridInfo);// 虚设canMove得到的数组，避免多次调用canMove函数，大大节省时间
    int n = possibleMoves.size();// 直接用成品数组，防止多次调用
    Move bestMove = {0 , 0 , 0 , 0 , 0 , 0};
    double bestValue = -10000.0;// 设负值求最大价值，选最优策略
    for (int i = 0 ; i < n ; i ++){// 对所有可行移动进行枚举
        vector<vector<int>> tempTable = gridInfo;// 虚设棋盘，完成单层搜索，使得评估函数对移动后的虚设棋盘评估
        Move Amove = possibleMoves[i];
        tempTable[Amove.x0][Amove.y0] = 0;
        tempTable[Amove.x1][Amove.y1] = botColor;
        tempTable[Amove.x2][Amove.y2] = 3;// 移动后就得到了待评估的————移动后的虚设棋盘
        double tempValue = evaluate(tempTable, botColor, gameRound + 1);// 记得+1轮次用于评估
        if (tempValue > bestValue){// 更新得到估价函数最大走法，这是bot行动后基于bot的最大估价情形，估价函数也基于bot情况展开
            bestValue = tempValue;
            bestMove = Amove;
        }
    }
    rx0 = bestMove.x0;
    ry0 = bestMove.y0;
    rx1 = bestMove.x1;
    ry1 = bestMove.y1;
    rx2 = bestMove.x2;
    ry2 = bestMove.y2;
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

// 函数4：评估函数中控模块
double evaluate(const vector<vector<int>> &table , int botColor , int round){// 对于虚设棋盘+bot色号+轮次，进行基于bot的估价计算，保证bot行动最优
    int sum1 = QueenMove(table , botColor);// QueenMove：bot射线形移动直到遇到障碍，所能比人类多占位置的能力（最直接表征）
    int sum2 = KingMove(table , botColor);// KingMove：bot走周边8格bfs，到所有格子步数比人类小的程度的量化表征（机动性）
    int sum3 = position(table , botColor);// position：bot和人类棋子靠近棋盘中央的量化表征（经验结论）
    // 随轮次变化，QueenMove权重递增，KingMove和position递减
    if (round >= 1 && round <= 8) return sum1 * spec[0][0] + sum2 * spec[0][1] + sum3 * spec[0][2];
    else if (round >= 9 && round <= 24) return sum1 * spec[1][0] + sum2 * spec[1][1] + sum3 * spec[1][2];
    else return sum1 * spec[2][0] + sum2 * spec[2][1] + sum3 * spec[2][2];
}

// 函数5：QueenMove模块
int QueenMove(const vector<vector<int>> &table , int botColor){// 射线8方向遍历
    int color = 3 - botColor;
    vector<vector<bool>> canHuman(8 , vector<bool>(8 , false));
    vector<vector<bool>> canBot(8 , vector<bool>(8 , false));
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            if (table[i][j] != botColor) continue;// 找到bot棋子色号
            for (int dir = 0 ; dir < 8 ; dir ++) {
                for (int step = 1 ; step < 8 ; step ++) {// for循环+break机制，和while等价
                    int x = i + dx[dir] * step;
                    int y = j + dy[dir] * step;
                    if (!inMap(x , y) || table[x][y] != 0) break;// 先判断越界后标定canBot的值，由于inMap在前，故不会越界
                    canBot[x][y] = true;
                }
            }
        }
    }
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            if (table[i][j] != color) continue;// 找到人类棋子色号
            for (int dir = 0 ; dir < 8 ; dir ++) {
                for (int step = 1 ; step < 8 ; step ++) {// for循环+break机制，和while等价
                    int x = i + dx[dir] * step;
                    int y = j + dy[dir] * step;
                    if (!inMap(x , y) || table[x][y] != 0) break;// 先判断越界后标定canBot的值，由于inMap在前，故不会越界     
                    canHuman[x][y] = true;
                }
            }
        }
    }
    int result = 0;
    for (int i = 0 ; i < 8 ; i ++){// 更好的权重多样化处理：bot单占+3，人类单占-3，公用+1
        for (int j = 0 ; j < 8 ; j ++){
            if (canBot[i][j] && !canHuman[i][j]) result += 3;  
            else if (canHuman[i][j] && !canBot[i][j]) result -= 3;           
            else if (canBot[i][j] && canHuman[i][j]) result ++;
        }
    }
    return result;
}

// 函数6：KingMove模块
int KingMove(const vector<vector<int>> &table , int botColor){
    int color = 3 - botColor;
    int result = 0;
    vector<vector<int>> minBot(8 , vector<int>(8 , 100));
    vector<vector<int>> minHuman(8 , vector<int>(8 , 100));// bot和人类到达最短步数，初始化足够大的100方便后续比较
    vector<vector<bool>> visitedBot(8 , vector<bool>(8 , false));
    vector<vector<bool>> visitedHuman(8 , vector<bool>(8 , false));// bot和人类是否经历了某个方格
    queue<bfs> bot;
    queue<bfs> human;
    for (int i = 0 ; i < 8 ; i ++){// 找出bot和人类的4个棋子从而初始化队列
        for (int j = 0 ; j < 8 ; j ++){
            if (table[i][j] == botColor) bot.push({i , j , 0});         
            else if (table[i][j] == color) human.push({i , j , 0});
        }
    }
    while(!bot.empty()){// 常规bfs模板，队列为空则停止，对bot和human分别标定后存数组
        int x = bot.front().x;
        int y = bot.front().y;
        int dis = bot.front().dis;
        bot.pop();
        for (int i = 0 ; i < 8 ; i ++){
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (inMap(tx , ty)){// 注意先检查越界！！！
                if (table[tx][ty] == 0 && !visitedBot[tx][ty]){
                    visitedBot[tx][ty] = true;
                    minBot[tx][ty] = dis + 1;
                    bot.push({tx , ty , dis + 1});
                }
            }
        }
    }
    while(!human.empty()){
        int x = human.front().x;
        int y = human.front().y;
        int dis = human.front().dis;
        human.pop();
        for (int i = 0 ; i < 8 ; i ++){
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (inMap(tx , ty)){// 注意先检查越界！！！
                if (table[tx][ty] == 0 && !visitedHuman[tx][ty]){
                    visitedHuman[tx][ty] = true;
                    minHuman[tx][ty] = dis + 1;
                    human.push({tx , ty , dis + 1});
                }
            }
        }
    }
    for (int i = 0 ; i < 8 ; i ++){// 利用bfs记录求得KingMove权重
        for (int j = 0 ; j < 8 ; j ++){
            if (table[i][j] != 0) continue;
            if (minBot[i][j] < minHuman[i][j]) result ++;          
            else if (minBot[i][j] > minHuman[i][j]) result --;
        }
    }
    return result;
}

// 函数7：位置价值模块
int position(const vector<vector<int>> &table , int botColor){
    int color = 3 - botColor;
    int result = 0;
    for (int i = 0 ; i < 8 ; i ++){// 该函数相对较为简单，根据全局变量中的位置-价值数组即可得出
        for (int j = 0 ; j < 8 ; j ++){
            if (table[i][j] == botColor) result += valuePos[i][j];
            else if (table[i][j] == color) result -= valuePos[i][j];    
        }
    }
    return result;
}

// 函数8：新游戏，初始化棋盘状态
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