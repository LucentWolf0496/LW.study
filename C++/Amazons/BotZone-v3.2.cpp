// 多层排序+剪枝+启发加深+限时
// bot代号：NeiKos_33550336————以此致敬Mr.Phainon
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

// 定义基础参量
int color = 0;// 我所执子颜色（1为黑，2为白，棋盘状态亦同）
int botColor = 0;// bot的颜色
int gameRound = 1;// 游戏轮次
int SEARCH_DEPTH = 3;// 搜索深度
const auto TIME_LIMIT = std::chrono::milliseconds(970); // 0.97秒时间限制
const auto TIME_LIMIT1 = std::chrono::milliseconds(1970); // 1.97秒时间限制
std::chrono::high_resolution_clock::time_point startTime; // 搜索开始时间点
vector<vector<int>> gridInfo(8 , vector<int> (8 , 0));// 先x后y，记录棋盘状态，未被占据为0
vector<int> dx = {-1 , -1 , -1 , 0 , 0 , 1 , 1 , 1};// 8个方向
vector<int> dy = {-1 , 0 , 1 , -1 , 1 , -1 , 0 , 1};// 8个方向
struct Move {// 结构体打包一次行动
    int x0, y0;// 起点
    int x1, y1;// 终点
    int x2, y2;// 障碍位置
};
struct ScoredMove {// 辅助结构体：打包Move和分数，便于排序
    Move move;
    double score;
};
vector<vector<double>> spec = {// 随对局更改的估价函数参数
    {20.0 , 1.0   , 0.5 } ,
    {5.0  , 15.0  , 10.0} , 
    {0.5  , 100.0 , 20.0}
};
struct bfs{// 用于KingMove中的bfs求解过程
    int x;
    int y;
    int dis;
};
struct ComponentInfo {
    int size = 0;// 区域内的空方格数量
    int p1_queens = 0;// 区域内的 P1 棋子数量 (这里 P1 = botColor)
    int p2_queens = 0;// 区域内的 P2 棋子数量 (这里 P2 = humanColor)
};
int rx0 , ry0 , rx1 , ry1 , rx2 , ry2;

// 函数声明
void singleTurnBot();// 函数1：正常/挑战模式-bot-单轮对局
bool inMap(int x , int y);// 函数2：inMap判断是否在地图内
bool checkTime(int round);// 函数3：AB搜索超时检查
vector<Move> canMove(int color , const vector<vector<int>> &table);// 函数4：canMove遍历求解所有可动的位置
double evaluate(const vector<vector<int>> &table , int botColor , int round);// 函数5：评估函数中控模块
int QueenMove(const vector<vector<int>> &table , int botColor);// 函数6：QueenMove模块
int KingMove(const vector<vector<int>> &table , int botColor);// 函数7：KingMove模块
void dfs_partition(const vector<vector<int>>& table, vector<vector<bool>>& visited, 
                   int r, int c, int botColor, ComponentInfo& info);// 函数8：PartitionScore的DFS过程
int PartitionScore(const vector<vector<int>> &table , int botColor);// 函数9：PartitionScore模块
double ABSearch(vector<vector<int>> &table, int depth, 
    double alpha, double beta, bool isMaximizing, int currentRound);// 函数10：未加排序的回溯式alpha-beta剪枝
bool compareScoredMoves(const ScoredMove& a, const ScoredMove& b);// 函数11：结合辅助结构体的排序函数
void newGame();// 函数12：新游戏，初始化棋盘状态

// 函数1：bot-单轮对局
void singleTurnBot(){
    startTime = std::chrono::high_resolution_clock::now();
    if (gameRound >= 15) SEARCH_DEPTH = 4;
    if (gameRound >= 25) SEARCH_DEPTH = 5;
    if (gameRound >= 35) SEARCH_DEPTH = 6;
    if (gameRound >= 45) SEARCH_DEPTH = 8;
    vector<Move> possibleMoves = canMove(botColor, gridInfo);
    int n = possibleMoves.size();
    Move bestMove;

    vector<ScoredMove> scoredMoves;// 实现初始根节点的升序，便于高效剪枝
    for (int i = 0 ; i < n ; i ++) {
        Move m = possibleMoves[i];
        gridInfo[m.x0][m.y0] = 0;// 模拟棋盘
        gridInfo[m.x1][m.y1] = botColor;
        gridInfo[m.x2][m.y2] = 3;
        double score = evaluate(gridInfo, botColor, gameRound + 1);// 评估分数
        gridInfo[m.x2][m.y2] = 0;// 回溯
        gridInfo[m.x1][m.y1] = 0;
        gridInfo[m.x0][m.y0] = botColor;
        scoredMoves.push_back({m, score});
    }
    sort(scoredMoves.begin(), scoredMoves.end(), compareScoredMoves);// 降序，先找bot分数最高的，提高beta下限

    double bestValue = -200000.0;// 极小极大初始化，下为排序后的AB剪枝的概述思路：为什么排序剪枝能卡出最优解？
    double alpha = -200000.0;// beta永远传入基础的2e5，而alpha总是目前递归出最高的beta，故可以导致beta在递归中迅速剪枝，除非有更优解！！
    double beta = 200000.0;// 为了这更优解，递归里面也要排序各个Move，否则最优解在递归里面又只会暴力随机遍历！！
    if (n > 0) bestMove = possibleMoves[0];// 搜索起点
    for (int i = 0 ; i < min(20 , n) ; i ++) {
        if(checkTime(gameRound)) break;
        Move Amove = scoredMoves[i].move;
        gridInfo[Amove.x0][Amove.y0] = 0;// 真实棋盘模拟一次bot行动，避免复制棋盘，加速！
        gridInfo[Amove.x1][Amove.y1] = botColor;
        gridInfo[Amove.x2][Amove.y2] = 3;
        double tempValue = ABSearch(gridInfo , SEARCH_DEPTH - 1 ,// 搜索深度逐轮次递减直到0返回叶子节点，首个传递都是false模拟人类行动
             alpha , beta , false , gameRound + 1);// 递归搜索，直接改gridInfo，传给递归的就是改过的
        gridInfo[Amove.x2][Amove.y2] = 0;// 回溯真实棋盘，准备尝试下一种走法
        gridInfo[Amove.x1][Amove.y1] = 0;
        gridInfo[Amove.x0][Amove.y0] = botColor;
        if (tempValue > bestValue) {
            bestValue = tempValue;
            bestMove = Amove;
        }
        alpha = max(alpha, tempValue);// 记得更新alpha————alpha和beta不断水涨船高的过程，最终逼出最优解，而排序则是加速器！！
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

// 函数3：AB搜索超时检查
bool checkTime(int round) {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime) >= (gameRound >= 3 ? TIME_LIMIT : TIME_LIMIT1);
}

// 函数4：canMove遍历求解所有可动的位置
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

// 函数5：评估函数中控模块
double evaluate(const vector<vector<int>> &table , int botColor , int round){// 对于虚设棋盘+bot色号+轮次，进行基于bot的估价计算，保证bot行动最优
    int sum1 = QueenMove(table , botColor);// QueenMove：bot射线形移动直到遇到障碍，所能比人类多占位置的能力（最直接表征）
    int sum2 = KingMove(table , botColor);// KingMove：bot走周边8格bfs，到所有格子步数比人类小的程度的量化表征（机动性）
    int sum3 = PartitionScore(table , botColor);
    // 随轮次变化，QueenMove权重递增，KingMove和position递减
    if (round >= 1 && round <= 6) return sum1 * spec[0][0] + sum2 * spec[0][1] + sum3 * spec[0][2];
    else if (round >= 7 && round <= 18) return sum1 * spec[1][0] + sum2 * spec[1][1] + sum3 * spec[1][2];
    else return sum1 * spec[2][0] + sum2 * spec[2][1] + sum3 * spec[2][2];
}

// 函数6：QueenMove模块
int QueenMove(const vector<vector<int>> &table , int botColor){// 射线8方向遍历
    int color = 3 - botColor;
    bool canHuman[8][8] = {false};
    bool canBot[8][8] = {false};// 原生数组栈内存比vector要快
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

// 函数7：KingMove模块
int KingMove(const vector<vector<int>> &table , int botColor){
    int color = 3 - botColor;
    int result = 0;
    int minBot[8][8];
    int minHuman[8][8];// 使用原生数组速度快
    for(int i = 0 ; i < 8 ; i ++) {// 初始化为 100，甚至可以省去visited数组，因为可以用100这个极大值表征visit情况
        for(int j = 0 ; j < 8 ; j ++) {
            minBot[i][j] = 100;
            minHuman[i][j] = 100;
        }
    }
    queue<bfs> bot;
    queue<bfs> human;
    for (int i = 0 ; i < 8 ; i ++){// 找出bot和人类的4个棋子从而初始化队列
        for (int j = 0 ; j < 8 ; j ++){
            if (table[i][j] == botColor){
                bot.push({i , j , 0});   
                minBot[i][j] = 0;
            }      
            else if (table[i][j] == color){
                human.push({i , j , 0});
                minHuman[i][j] = 0;
            }
        }
    }
    while(!bot.empty()){// 常规bfs模板，队列为空则停止，对bot和human分别标定后存数组
        bfs cur = bot.front();
        bot.pop();
        for (int i = 0 ; i < 8 ; i ++){
            int tx = cur.x + dx[i];
            int ty = cur.y + dy[i];
            if (inMap(tx , ty) && table[tx][ty] == 0){// 注意先检查越界！！！
                if (minBot[tx][ty] == 100){// 省去了visit数组
                    minBot[tx][ty] = cur.dis + 1;
                    bot.push({tx , ty , cur.dis + 1});
                }
            }
        }
    }
    while(!human.empty()){
        bfs cur = human.front();
        human.pop();
        for (int i = 0 ; i < 8 ; i ++){
            int tx = cur.x + dx[i];
            int ty = cur.y + dy[i];
            if (inMap(tx , ty) && table[tx][ty] == 0){// 注意先检查越界！！！
                if (minHuman[tx][ty] == 100){
                    minHuman[tx][ty] = cur.dis + 1;
                    human.push({tx , ty , cur.dis + 1});
                }
            }
        }
    }
    for (int i = 0 ; i < 8 ; i ++){// 利用bfs记录求得KingMove权重
        for (int j = 0 ; j < 8 ; j ++){
            if (table[i][j] != 0) continue;
            if (minBot[i][j] == 100 && minHuman[i][j] == 100) continue;
            if (minBot[i][j] < minHuman[i][j]) result ++;          
            else if (minBot[i][j] > minHuman[i][j]) result --;
        }
    }
    return result;
}

// 函数8：PartitionScore的DFS过程
void dfs_partition(const vector<vector<int>>& table , vector<vector<bool>>& visited , 
                   int r , int c , int botColor , ComponentInfo& info) {
    if (!inMap(r, c) || visited[r][c] || table[r][c] == 3) return;
    if (table[r][c] == 0) info.size ++;// 更新组件信息
    else if (table[r][c] == botColor) info.p1_queens ++;
    else info.p2_queens ++;
    visited[r][c] = true;
    for (int i = 0; i < 8; ++i) {// 沿王步 8 个方向递归搜索
        dfs_partition(table, visited, r + dx[i], c + dy[i], botColor, info);
    }
}

// 函数9：PartitionScore模块
int PartitionScore(const vector<vector<int>> &table , int botColor) {
    vector<vector<bool>> visited(8 , vector<bool>(8 , false));
    double total_score = 0.0;
    for (int r = 0 ; r < 8 ; ++ r) {
        for (int c = 0 ; c < 8 ; ++ c) {
            if (!visited[r][c] && table[r][c] <= 2) { // 检查是否为未访问的非箭格子
                ComponentInfo component;
                dfs_partition(table , visited , r , c , botColor , component);
                double component_score = 0.0;// 连通组件评分启发式
                int p1_q = component.p1_queens; // bot棋子数
                int p2_q = component.p2_queens; // human棋子数
                int area_size = component.size;
                // 独占区域
                if (p1_q > 0 && p2_q == 0) component_score = area_size * 1.0;// bot 独占：所有空方格计入 bot
                else if (p2_q > 0 && p1_q == 0) component_score = area_size * (-1.0); // human 独占：所有空方格计入 human
                // 竞争区域
                else if (p1_q > 0 && p2_q > 0) component_score = (double)(p1_q - p2_q) * area_size * 0.2;// 双方棋子在同一区域，给予低权重
                total_score += component_score;
            }
        }
    }
    return (int)round(total_score);
}

// 函数10：回溯式alpha-beta剪枝
double ABSearch(vector<vector<int>> &table , int depth , 
    double alpha , double beta , bool isMaximizing , int currentRound) {// isMaxmizing：是bot就最大bot分数，是人类就最小bot分数
    if (checkTime(gameRound)) return evaluate(gridInfo, botColor, currentRound);// 如果超时，立即返回当前局面的静态估价
    if (depth == 0) return evaluate(table , botColor , currentRound);// 截止条件
    int currentColor = (isMaximizing ? botColor : (3 - botColor));
    vector<Move> possibleMoves = canMove(currentColor, table);// 所有的棋盘都是基于gridInfo的传引用，避免复制浪费时间
    int n = possibleMoves.size();
    if (n == 0) return (isMaximizing ? -200000.0 : 200000.0);// 行动可能为0，取胜策略

    vector<ScoredMove> scoredMoves;
    for (int i = 0 ; i < n ; i ++) {// 实现排序
        Move m = possibleMoves[i];
        table[m.x0][m.y0] = 0;// 模拟行动
        table[m.x1][m.y1] = currentColor;
        table[m.x2][m.y2] = 3;
        double score = evaluate(table , botColor , currentRound + 1);// 评估分数       
        table[m.x2][m.y2] = 0;// 回溯
        table[m.x1][m.y1] = 0;
        table[m.x0][m.y0] = currentColor;
        scoredMoves.push_back({m, score});
    }//下为排序的分类讨论
    if (isMaximizing) {// Max 层降序，bot希望找到分数最高的走法
        sort(scoredMoves.begin() , scoredMoves.end() , compareScoredMoves);
    }
    else {// Min 层升序，人类希望找到bot分数最低的走法————时刻注意评估函数是刻画**bot的优势**
        sort(scoredMoves.begin() , scoredMoves.end() , compareScoredMoves);
        reverse(scoredMoves.begin() , scoredMoves.end());
    }

    if (isMaximizing) {// bot行动，让bot分数最大化
        double maxEval = -200000.0;// 虚设最小值取出最大值
        for (int i = 0 ; i < min(20 , n) ; i ++) {
            Move Amove = scoredMoves[i].move;
            table[Amove.x0][Amove.y0] = 0;// 模拟行动
            table[Amove.x1][Amove.y1] = currentColor;
            table[Amove.x2][Amove.y2] = 3;
            double eval = ABSearch(table , depth - 1 , alpha , beta , false , currentRound + 1);// 递归，isMaxmizing交替轮换
            table[Amove.x2][Amove.y2] = 0;// 回溯，不传棋盘，效率高
            table[Amove.x1][Amove.y1] = 0; 
            table[Amove.x0][Amove.y0] = currentColor;
            maxEval = max(maxEval , eval);// 更新与剪枝
            alpha = max(alpha , eval);// 更新
            if (beta <= alpha) {// 剪枝
                break; 
            }
        }
        return maxEval;
    }
    else {// 人类行动，让bot分数最小化
        double minEval = 200000.0;// 虚设最大值取出最小值
        for (int i = 0 ; i < min(20 , n) ; i ++) {
            Move Amove = scoredMoves[i].move;
            table[Amove.x0][Amove.y0] = 0;// 模拟行动
            table[Amove.x1][Amove.y1] = currentColor;
            table[Amove.x2][Amove.y2] = 3;
            double eval = ABSearch(table , depth - 1 , alpha , beta , true , currentRound + 1);// 递归
            table[Amove.x2][Amove.y2] = 0;// 回溯
            table[Amove.x1][Amove.y1] = 0;
            table[Amove.x0][Amove.y0] = currentColor;
            minEval = min(minEval , eval);// 更新与剪枝
            beta = min(beta , eval);// 更新
            if (beta <= alpha) {// 剪枝
                break;
            }
        }
        return minEval;
    }
}

// 函数11：结合辅助结构体的排序函数
bool compareScoredMoves(const ScoredMove& a, const ScoredMove& b) {
    return a.score > b.score;
}

// 函数12：新游戏，初始化棋盘状态
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