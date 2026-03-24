// 8*8亚马逊棋，由LEAF所作
// 基本要求[6]：菜单选择+精美字符棋盘+人机对战+棋盘变化+菜单暂停+存盘读盘
// 额外功能[5]：单步悔棋+多存档+难度选择+魔法模式+计时挑战模式
// bot算法：MiniMax搜索+AB剪枝+启发加深搜索
// [version3.2]估价函数更新与调参优化
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <queue>
#include <iomanip>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std;

// 定义基础参量
int color = 0;// 我所执子颜色（1为黑，2为白，棋盘状态亦同）
int botColor = 0;// bot的颜色
int gameRound = 1;// 游戏轮次
int undoRound = -1;// 悔棋轮次
bool canUndo = false;// 当前可否悔棋
bool boom = true;// 是否可用炸弹魔法
bool obstacle = true;// 是否可用障碍魔法
bool boomUndo = true;// 炸弹与悔棋
bool obstacleUndo = true;// 障碍与悔棋
int gameMode = 0;// 1为简单，2为魔法，3为正常，4为挑战
int SEARCH_DEPTH = 3;// 搜索深度
const int timeLimit = 30;// 30秒限制
const auto TIME_LIMIT = std::chrono::milliseconds(970); // 0.97秒时间限制
const auto TIME_LIMIT1 = std::chrono::milliseconds(1970); // 1.97秒时间限制
std::chrono::high_resolution_clock::time_point startTime1; // 搜索开始时间点
vector<vector<int>> gridInfo(8 , vector<int> (8 , 0));// 先x后y，记录棋盘状态，未被占据为0
vector<vector<int>> gridUndo(8 , vector<int> (8 , 0));// 悔棋暂存数组
int dx[8] = {-1 , -1 , -1 , 0 , 0 , 1 , 1 , 1};// 8个方向，原生数组压缩时间！！
int dy[8] = {-1 , 0 , 1 , -1 , 1 , -1 , 0 , 1};// 8个方向
int x4[4] = {1 , 0 , -1 , 0};// 4个方向
int y4[4] = {0 , 1 , 0 , -1};// 4个方向
random_device rd;
mt19937 gen(rd());// 随机数生成引擎
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
struct ComponentInfo {// 用于精确的空格估价函数
    int size = 0;// 区域内的空方格数量
    int p1_queens = 0;// 区域内的P1棋子数量(这里P1是botColor)
    int p2_queens = 0;// 区域内的P2棋子数量(这里P2是humanColor)
};

// 函数声明
void menu();// 函数1：菜单
void modeChoice();// 函数2：难度选取
void newGame();// 函数3：新游戏，初始化棋盘状态
void fileIn();// 函数4：存盘
void fileOut();// 函数5：读盘
void colorChoice();// 函数6：随机选棋子颜色
void gameCycle();// 函数7：回合循环轮替，避免递归过深
bool endGame();// 函数8：游戏结束的判定
void Undo();// 函数9：悔棋功能
void singleTurnHuman();// 函数10：简单/正常模式-人类-单轮对局
void masterHuman();// 函数11：挑战模式-人类-单轮对局
bool checkTime(chrono::steady_clock::time_point startTime);// 函数12：时间检查函数
void magic(int x);// 函数13：集成两个魔法
int location();// 函数14：对人类输入的集中处理
void randomBot();// 函数15：简单模式-bot-单轮对局
void singleTurnBot();// 函数16：正常/挑战模式-bot-单轮对局
void printGrid();// 函数17：打印美观的棋盘
bool inMap(int x , int y);// 函数18：inMap判断是否在地图内
vector<Move> canMove(int color , const vector<vector<int>> &table);// 函数19：canMove遍历求解所有可动的位置
int randomNum();// 函数20：生成1-10000随机整数
double evaluate(const vector<vector<int>> &table , int botColor , int round);// 函数21：评估函数中控模块
int QueenMove(const vector<vector<int>> &table , int botColor);// 函数22：QueenMove模块
int KingMove(const vector<vector<int>> &table , int botColor);// 函数23：KingMove模块
void dfs_partition(const vector<vector<int>>& table, bool visited[8][8], 
                   int r, int c, int botColor, ComponentInfo& info);// 函数24：PartitionScore的DFS过程
int PartitionScore(const vector<vector<int>> &table , int botColor);// 函数25：PartitionScore模块
double ABSearch(vector<vector<int>> &table , int depth , 
    double alpha , double beta , bool isMaximizing , int currentRound);// 函数26：回溯式alpha-beta剪枝
bool compareScoredMoves(const ScoredMove& a, const ScoredMove& b);// 函数27：结合辅助结构体的排序函数
bool checkTime(int round);// 函数28：AB搜索超时检查

// 函数1：菜单
void menu(){
    string n;// **重要**要用string+getline，否则会有各式各样的输入bug
    while(true){// 循环式菜单，比起自我递归调用式菜单，规避了栈溢出的风险
        cout << "亚马逊棋游戏运行中，你有如下6个选择" << endl;
        cout << "输入1开始新游戏，输入2存盘并中止游戏，输入3读盘并恢复游戏，输入4悔棋，输入5终止游戏，输入6返回上一界面" << endl;
        getline(cin , n);
        if (n != "1" && n != "2" && n != "3" && n != "4" && n != "5" && n != "6") cout << "无效输入，返回菜单！" << endl;
        else if (n == "1"){// 新游戏-1
            string check;
            cout << "确定开始新游戏吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                modeChoice();
                newGame();
            }
            else if (check == "n") cout << "返回菜单" << endl;// 重新开始while循环，重新执行菜单指令
            else cout << "无效输入，返回菜单！" << endl;// 这么写有效减少代码行数
        }
        else if (n == "2"){// 存盘-2
            string check;
            cout << "确定存盘吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") fileIn();
            else if (check == "n") cout << "返回菜单" << endl;
            else cout << "无效输入，返回菜单！" << endl;
        }      
        else if (n == "3"){// 读盘-3
            string check;
            cout << "确定读盘吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") fileOut();     
            else if (check == "n") cout << "返回菜单" << endl;
            else cout << "无效输入，返回菜单！" << endl;   
        }
        else if (n == "4"){// 悔棋-4
            string check;
            cout << "确定悔棋吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") Undo();
            else if (check == "n") cout << "返回菜单" << endl;  
            else cout << "无效输入，返回菜单！" << endl; 
        }
        else if (n == "5"){// 结束游戏-5
            string check;
            cout << "确定结束吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                cout << "游戏结束" << endl;
                exit(0);
            }
            else if (check == "n") cout << "返回菜单" << endl;
            else cout << "无效输入，返回菜单！" << endl; 
        }
        else if (n == "6") return;// 回退-6
    }
}

// 函数2：难度选取
void modeChoice(){
    string n;
    while(true){
        cout << "本游戏有4种难度" << endl;
        cout << "简单难度为随机数算法，魔法难度、正常难度与挑战难度为搜索算法" << endl;
        cout << "注意————魔法难度中，有且仅有人类方可以使用魔法辅助对局" << endl;
        cout << "注意————挑战难度不能悔棋、暂停、存档，且每步限时30秒，超时则判负" << endl;
        cout << "输入1进入简单难度，输入2进入魔法难度，输入3进入正常难度，输入4进入挑战难度" << endl;
        getline(cin , n);
        if (n != "1" && n != "2" && n != "3" && n != "4") cout << "无效输入，已返回！" << endl;
        else{
            if (n == "1") cout << "新游戏开始，本局难度为：简单" << endl;
            else if (n == "2") cout << "新游戏开始，本局难度为：魔法" << endl;
            else if (n == "3") cout << "新游戏开始，本局难度为：正常" << endl;
            else if (n == "4") cout << "新游戏开始，本局难度为：挑战" << endl;
            gameMode = n[0] - '0';
            break;
        }
    }
}
    
// 函数3：新游戏，初始化棋盘状态
void newGame(){
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            gridInfo[i][j] = 0;// 注意要先全部归零再安排初始棋子
        }
    }
    gridInfo[0][2] = 1;
    gridInfo[0][5] = 1;
    gridInfo[2][0] = 1;
    gridInfo[2][7] = 1;
    gridInfo[5][0] = 2;
    gridInfo[5][7] = 2;
    gridInfo[7][2] = 2;
    gridInfo[7][5] = 2;
    gameRound = 1;
    undoRound = -1;
    canUndo = false;
    boom = true;
    obstacle = true;
    boomUndo = true;
    obstacleUndo = true;
    colorChoice();// 调用随机黑白函数
    gameCycle();// 选好棋子后进入循环
}

// 函数4：存盘
void fileIn(){
    string n;
    while(true){// 实现多个存档
        cout << "这是存盘程序，你可以将目前的对局存到3个存档中" << endl;
        cout << "请输入1-3选择你要存档的位置，注意存档会覆盖原有信息" << endl;
        getline(cin , n);
        if (n != "1" && n != "2" && n != "3") cout << "无效输入，已返回！" << endl;
        else break;      
    }// 下面是相对地址，便于移植，但不会显示在Amazons文件夹
    ofstream fout((n == "1" ? "preserved1.txt" : (n == "2" ? "preserved2.txt" : "preserved3.txt")));// 三元算符简化
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            fout << gridInfo[i][j] << " ";
        }
        fout << endl;
    }
    fout << color << endl;
    fout << botColor << endl;
    fout << gameMode << endl;
    fout << gameRound << endl;
    fout << boom << endl;
    fout << obstacle << endl;// 存盘存储后就可以随时调用
    fout << canUndo << endl;
    fout << undoRound << endl;
    fout << boomUndo << endl;
    fout << obstacleUndo << endl;// 补充存盘悔棋相关信息
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            fout << gridUndo[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
    cout << "存盘成功，游戏暂停" << endl;
    exit(0);// 存盘后退出程序，相当于暂停
}

// 函数5：读盘
void fileOut(){
    string n;
    while(true){// 实现多个存档
        cout << "这是读盘程序，你可以从3个存档中选择一个读入当前对局" << endl;
        cout << "请输入1-3选择你要读档的记录，注意读档会覆盖现有游戏" << endl;
        getline(cin , n);
        if (n != "1" && n != "2" && n != "3") cout << "无效输入，已返回！" << endl; 
        else break;
    }// 下面是相对地址，便于移植，但不会显示在Amazons文件夹
    ifstream fin((n == "1" ? "preserved1.txt" : (n == "2" ? "preserved2.txt" : "preserved3.txt")));// 三元算符简化
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            fin >> gridInfo[i][j];
        }
    }
    fin >> color;
    fin >> botColor;
    fin >> gameMode;
    fin >> gameRound;
    fin >> boom;
    fin >> obstacle;// 录入记录，开始存档的游戏
    fin >> canUndo;
    fin >> undoRound;
    fin >> boomUndo;
    fin >> obstacleUndo;// 补充录入悔棋相关信息
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            fin >> gridUndo[i][j];
        }
    }
    if (color == 0){// 也就是存档甚至没执行选择黑白，说明存档为空，无法读盘
        cout << "暂无存档，读盘失败，返回菜单！" << endl;
        menu();
        return;// 保险退出指令
    }
    fin.close();
    cout << "读盘成功，游戏继续" << endl;
    gameCycle();// 读盘后进入游戏循环
}

// 函数6：随机选棋子颜色
void colorChoice(){
    cout << "为您随机分配棋子颜色，黑先白后" << endl;
    int x = randomNum();// 基于函数3中1-10000的随机数生成器
    if (x <= 5000){// 我方执黑
        cout << "您是黑棋，bot是白棋，您先行动" << endl;
        color = 1;
        botColor = 2;
    }
    else{// 我方执白
        cout << "您是白棋，bot是黑棋，bot先行动" << endl;
        color = 2;
        botColor = 1;
    }
}

// 函数7：回合循环轮替
void gameCycle(){
    if (botColor == 1){// bot执黑，奇数bot，偶数人类
        while(!endGame()){
            if (gameRound % 2 == 1){
                if (gameMode >= 2) singleTurnBot(); 
                else randomBot();           
                gameRound ++;// 单方行动完后轮次+1
                undoRound ++;
            }
            else if (gameRound % 2 == 0){
                if (gameMode <= 3) singleTurnHuman();              
                else masterHuman();
                gameRound ++;
                undoRound ++;
            }
        }
    }
    else if (botColor == 2){// bot执白，奇数人类，偶数bot
        while(!endGame()){
            if (gameRound % 2 == 1){
                if (gameMode <= 3) singleTurnHuman();
                else masterHuman();       
                gameRound ++;
                undoRound ++;
            }
            else if (gameRound % 2 == 0){
                if (gameMode >= 2) singleTurnBot();     
                else randomBot();
                gameRound ++;
                undoRound ++;
            }
        }
    }
    exit(0);// endGame函数判断游戏结束后跳出while循环，程序也结束
}

// 函数8：游戏结束的判定
bool endGame(){// 就算游戏结束了，也需在运行endGame函数判断并输出总结后才结束
    if (canMove(color , gridInfo).empty() && canMove(botColor , gridInfo).empty()){
        cout << "你和bot达成了平局！" << endl;// 很少见的情况
        return true;
    }
    else if (canMove(color , gridInfo).empty()){
        cout << "您输了，游戏结束！" << endl;
        return true;
    }
    else if (canMove(botColor , gridInfo).empty()){
        cout << "恭喜您获胜！游戏结束！" << endl;
        return true;
    }
    else return false;
}

// 函数9：悔棋功能
void Undo(){
    if (undoRound <= 0){
        cout << "这是你的第一步，你无法悔棋，即将返回游戏" << endl;
        gameCycle();
    }
    if (!canUndo){
        cout << "谨慎思考才能取胜，请勿连续悔棋!即将返回游戏" << endl;
        gameCycle();
    }
    gameRound = undoRound;
    undoRound -= 2;
    gridInfo = gridUndo;
    canUndo = false;
    boom = boomUndo;
    obstacle = obstacleUndo;
    cout << "已经悔棋到第" << gameRound << "轮，由您重新行动" << endl;
    cout << "注意：不允许连续悔棋多步，只回退到上一次人类行动" << endl;
    gameCycle();
}

// 函数10：简单/魔法/正常模式-人类-单轮对局
void singleTurnHuman(){
    cout << "——————————————————————" << (gameMode == 1 ? "简单模式" : (gameMode == 2 ? "魔法模式" : "正常模式")) << "——————————————————————" << endl;
    cout << "—————————————————第" << gameRound << "轮———人类行" << (color == 1 ? "黑" : "白") << "棋—————————————————" << endl;
    cout << "—————————" << (canUndo ? "—" : "") << "当前棋盘状态如下，你现在" << 
    (canUndo ? "" : "不") << "可以悔棋" << (canUndo ? "—" : "") << "—————————" << endl;
    printGrid();
    string n;
    while(true){// 类似菜单函数，采用两个while循环从而避免自我调用
        cout << "轮到你行动了，输入1可以行棋，输入2可以进入菜单" << endl;
        cout << "菜单包含新游戏、存盘、读盘、悔棋、结束游戏这些功能" << endl;
        getline(cin , n);
        if (n != "1" && n != "2") cout << "无效输入，请重试！" << endl;
        else if (n == "1"){
            cout << "行棋开始" << endl;
            break;// 开始后退出这个循环，开启下一个循环
        }
        else if (n == "2"){
            string check;
            cout << "确定进入菜单吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                cout << "进入菜单" << endl;
                menu();
                continue;
            }
            else if (check == "n") cout << "已返回到行动前" << endl;
            else cout << "无效输入，已返回到行动前！" << endl;
        }
    }
    while(true){
        int x0 , y0 , x1 , y1 , x2 , y2;
        Move move;
        vector<Move> list = canMove(color , gridInfo);// list数组存储所有的Move方式，以待后续检查
        cout << "请输入你要移动的棋子行坐标" << endl;
        x0 = location();// location输入坐标点的函数大大简化了人类输入过程！！！
        cout << "请输入你要移动的棋子列坐标" << endl;
        y0 = location();
        cout << "请输入你的移动终点行坐标" << endl;
        x1 = location();
        cout << "请输入你的移动终点列坐标" << endl;
        y1 = location();
        cout << "请输入你放置障碍的行坐标" << endl;
        x2 = location();
        cout << "请输入你放置障碍的列坐标" << endl;
        y2 = location();
        string check;
        cout << "确定行棋吗？你现在将" << "(" << x0 + 1 << "," << y0 + 1 << ")" << "的棋子"
             << "移到了" << "(" << x1 + 1 << "," << y1 + 1 << ")," << "并且在" 
             << "(" << x2 + 1 << "," << y2 + 1 << ")" << "放置了障碍" << "————y/n" << endl;
        getline(cin , check);
        if (check == "y") cout << "行棋开始" << endl;
        else if (check == "n") cout << "已返回到行动前" << endl;
        else cout << "无效输入，已返回到行动前！" << endl;
        move = {x0 , y0 , x1 , y1 , x2 , y2};
        bool isValid = false;// 判断0-7的数字输入是否合法
        for (int i = 0 ; i < list.size() ; i ++){// 搜索得到Move方式合法之后就跳出循环并标记合法
            if (move.x0 == list[i].x0 && move.y0 == list[i].y0 && move.x1 == list[i].x1 &&
                move.y1 == list[i].y1 && move.x2 == list[i].x2 && move.y2 == list[i].y2){
                    isValid = true;
                    break;// 存在相同Move在list队列中，跳出循环，标记可行
                }
        }
        if (isValid){// 对于合法的Move，更改棋盘状态
            gridUndo = gridInfo;
            boomUndo = boom;
            obstacleUndo = obstacle;// 悔棋暂存记录，输入合法后再存悔棋信息
            canUndo = true;// 有过行棋，可以悔棋，但不能连续悔棋，因为再次可以悔棋需要经过一次行棋
            gridInfo[move.x0][move.y0] = 0;
            gridInfo[move.x1][move.y1] = color;
            gridInfo[move.x2][move.y2] = 3;
            printGrid();// 用户合法行棋后的循环
            cout << "合法输入，棋盘状态已经更新" << endl;
            break;
        }
        else{
            cout << "非法输入，请重试！" << endl;// 不在队列中的输入，进入非法输入处理模块
            cout << "如有困难，输入1可以进入菜单，输入其他则继续尝试行棋" << endl;
            string giveUp;
            getline(cin , giveUp);
            if (giveUp == "1"){
                string check;
                cout << "确定进入菜单吗？y/n" << endl;
                getline(cin , check);
                if (check == "y") {
                    cout << "进入菜单" << endl;
                    menu();
                    continue;
                }
                else if (check == "n") cout << "继续尝试行棋" << endl;  
                else cout << "无效输入，继续尝试行棋！" << endl;
            }
            else continue;   
        }
    }// 下为模式2专属魔法
    if (gameMode == 2 && boom) magic(0);
    if (gameMode == 2 && obstacle) magic(3); 
    if (gameMode == 2 && !boom && !obstacle) cout << "\033[38;5;27m" << "……………………没有魔法了……………………" << "\033[0m" << endl;
}

// 函数11：挑战模式-人类-单轮对局
void masterHuman() {
    cout << "——————————————————————挑战模式——————————————————————" << endl;
    cout << "—————无法悔棋与使用菜单，每步限时30秒，超时判负—————" << endl;
    cout << "——————————————————当前棋盘状态如下——————————————————" << endl;
    printGrid();
    cout << "\033[31m" << "**注意，这是挑战模式，请在30秒内完成行棋，部分确认被省略**" << "\033[0m" << endl;
    auto startTime = chrono::steady_clock::now();// 记录开始时间，在循环外开始，防止错误输入刷新时间
    cout << "\033[31m" << "++++++++++++++++++++++计时开始++++++++++++++++++++++" << "\033[0m" << endl;// 红色
    while(true) {
        int x0, y0, x1, y1, x2, y2;
        Move move;
        vector<Move> list = canMove(color, gridInfo);
        cout << "请输入你要移动的棋子行坐标" << endl;
        x0 = location();// location如果要集成checkTime会干扰正常函数，所以就把checkTime单独提出来
        if (!checkTime(startTime)) exit(0);// 每输入一次后检查时间并决定是否退出程序
        cout << "请输入你要移动的棋子列坐标" << endl;
        y0 = location();
        if (!checkTime(startTime)) exit(0);
        cout << "请输入你的移动终点行坐标" << endl;
        x1 = location();
        if (!checkTime(startTime)) exit(0);
        cout << "请输入你的移动终点列坐标" << endl;
        y1 = location();
        if (!checkTime(startTime)) exit(0);
        cout << "请输入你放置障碍的行坐标" << endl;
        x2 = location();
        if (!checkTime(startTime)) exit(0);
        cout << "请输入你放置障碍的列坐标" << endl;
        y2 = location();
        if (!checkTime(startTime)) exit(0);
        move = {x0 , y0 , x1 , y1 , x2 , y2};
        bool isValid = false;// 判断数字输入是否合法
        for (int i = 0 ; i < list.size() ; i ++){// 搜索得到Move方式合法之后就跳出循环并标记合法
            if (move.x0 == list[i].x0 && move.y0 == list[i].y0 && move.x1 == list[i].x1 &&
                move.y1 == list[i].y1 && move.x2 == list[i].x2 && move.y2 == list[i].y2){
                    isValid = true;
                    break;// 存在相同Move在list队列中，跳出循环，标记可行
                }
        }
        if (isValid) {// 对于合法的Move，更改棋盘状态
            gridInfo[move.x0][move.y0] = 0;
            gridInfo[move.x1][move.y1] = color;
            gridInfo[move.x2][move.y2] = 3;
            printGrid();
            cout << "你现在将" << "(" << x0 + 1 << "," << y0 + 1 << ")" << "的棋子"
             << "移到了" << "(" << x1 + 1 << "," << y1 + 1 << ")," << "并且在" 
             << "(" << x2 + 1 << "," << y2 + 1 << ")" << "放置了障碍" << endl;
            auto endTime = chrono::steady_clock::now();// 计算总用时，需要成功输入了才能计算
            auto totalTime = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
            cout << "\033[32m" << "输入合法，本轮输入总用时: " << totalTime << "秒" << "\033[0m" << endl;// 绿色
            break;
        } 
        else cout << "非法输入，请重试！" << endl;// 不在队列中的输入，进入非法输入处理模块
    }
}

// 函数12：时间检查函数
bool checkTime(chrono::steady_clock::time_point startTime) {// 调用开始挑战模式轮次的时间
    auto currentTime = chrono::steady_clock::now();// 输入完进入函数的时间
    auto elapsedSeconds = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();// 时间差
    int remainingTime = timeLimit - static_cast<int>(elapsedSeconds);// 时间限制减去时间差，也就是剩余时间
    if (remainingTime <= 0) {// 根据剩余时间进行判定
        cout << "\033[31m" << "时间已到！超时判负！" << "\033[0m" << endl;
        return false; // 超时，红色
    }
    cout << "\033[33m" << "剩余时间: " << remainingTime << "秒" << "\033[0m" << endl;
    return true; // 未超时，黄色
}

// 函数13：集成两个魔法
void magic(int x){
    string n;
    while(true) {
        cout << "你有一个选定坐标，" << (x == 0 ? "造成十字形爆炸，移除障碍" : "放置十字形障碍")
             << "的魔法！每场对局仅可使用一次，你要使用吗————y/n" << endl;
        getline(cin , n);
        if (n == "n") return;
        if (n == "y") break;
        else cout << "非法输入，请重试！" << endl;
    }
    if (x == 0) boom = false;
    if (x == 3) obstacle = false;// 使用魔法
    while(true) {
        int x0 , y0;
        cout << "请输入十字形中心的行坐标" << endl;
        x0 = location();
        cout << "请输入十字形中心的列坐标" << endl;
        y0 = location();
        if(inMap(x0 , y0)){
            cout << "\033[38;5;27m" << (x == 0 ? "早说了是魔法吧！BOOM!" : "思路打开~~OBSTACLE!") << "\033[0m" << endl;
            if (gridInfo[x0][y0] != 1 && gridInfo[x0][y0] != 2) gridInfo[x0][y0] = x;
            for (int i = 0 ; i < 4 ; i ++){
                int nx = x0 + x4[i];
                int ny = y0 + y4[i];
                if (inMap(nx , ny) && gridInfo[nx][ny] != 1 && gridInfo[nx][ny] != 2) gridInfo[nx][ny] = x;
            }
            break;
        }
        else cout << "非法输入，请重试！" << endl;
    }
}

// 函数14：对人类输入的集中处理
int location(){
    string temp;
    while(true){
        getline(cin , temp);// 浓缩12种人类输入
        if (temp.size() >= 2 || temp.empty() || temp[0] < '1' || temp[0] > '8'){
            cout << "非法输入，请重试" << endl;
            continue;
        }
        break;
    }
    return temp[0] - '0' - 1;// 输出int格式,将人类的1-8坐标转化为二维数组的0-7坐标
}

// 函数15：简单模式-bot-单轮对局
void randomBot(){
    cout << "——————————————————————简单模式——————————————————————" << endl;
    cout << "—————————————————第" << gameRound << "轮——bot行" << (botColor == 1 ? "黑" : "白") << "棋—————————————————" << endl;
    vector<Move> ranMove = canMove(botColor , gridInfo);
    int n = ranMove.size();
    int ran = randomNum();
    ran %= n;
    Move move = ranMove[ran];
    gridInfo[move.x0][move.y0] = 0;
    gridInfo[move.x1][move.y1] = botColor;
    gridInfo[move.x2][move.y2] = 3;
    cout << "bot行动完毕，将" << "(" << move.x0 + 1 << "," << move.y0 + 1 << ")" << "的棋子"
         << "移到了" << "(" << move.x1 + 1 << "," << move.y1 + 1 << ")," << "并且在" 
         << "(" << move.x2 + 1 << "," << move.y2 + 1 << ")" << "放置了障碍" << endl;
    printGrid();
}

// 函数16：魔法/正常/挑战模式-bot-单轮对局
void singleTurnBot() {
    startTime1 = std::chrono::high_resolution_clock::now();
    if (gameRound >= 15) SEARCH_DEPTH = 4;// 随棋局动态调整搜索深度，经过botzone测试在1s内行棋
    if (gameRound >= 25) SEARCH_DEPTH = 5;
    if (gameRound >= 35) SEARCH_DEPTH = 6;
    if (gameRound >= 45) SEARCH_DEPTH = 8;
    cout << "——————————————————————" << (gameMode == 4 ? "挑战模式" : (gameMode == 3 ? "正常模式" : "魔法模式")) << "——————————————————————" << endl;
    cout << "—————————————————第" << gameRound << "轮——bot行" << (botColor == 1 ? "黑" : "白") << "棋—————————————————" << endl;
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
    gridInfo[bestMove.x0][bestMove.y0] = 0;// 正式执行这一步，最后的bestMove是传回beta最高的Move，也就是bot基于depth轮次思考的最理性选择
    gridInfo[bestMove.x1][bestMove.y1] = botColor;
    gridInfo[bestMove.x2][bestMove.y2] = 3;
    cout << "bot行动完毕，将" << "(" << bestMove.x0 + 1 << "," << bestMove.y0 + 1 << ")" << "的棋子"
         << "移到了" << "(" << bestMove.x1 + 1 << "," << bestMove.y1 + 1 << ")," << "并且在" 
         << "(" << bestMove.x2 + 1 << "," << bestMove.y2 + 1 << ")" << "放置了障碍" << endl;
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime1;
    double seconds = duration.count();
    cout << "\033[38;5;27m" << "bot思考了"  << seconds << "秒" << "\033[0m" << endl;
    printGrid();
}

// 函数17：打印美观的棋盘
void printGrid(){
    const string RESET = "\033[0m";// ANSI颜色代码
    const string BLACK_BG = "\033[48;5;238m";// 深灰背景
    const string WHITE_BG = "\033[48;5;249m";// 白背景
    const string BOARD = "\033[38;5;94m";// 棕色边框
    const string COORD = "\033[38;5;136m";// 金色坐标
    cout << COORD << "   ";// 顶部列坐标
    for (int j = 0 ; j < 8 ; j ++) {
        cout << "  " << j + 1 << " ";// 合适的空格数保证对齐坐标与棋盘
    }
    cout << RESET << endl;
    cout << BOARD << "   ┌";// 上边框
    for (int j = 0 ; j < 7 ; j ++) {
        cout << "───┬";
    }
    cout << "───┐" << RESET << endl;
    for (int i = 0 ; i < 8 ; i ++) {// 左侧行坐标
        cout << COORD << " " << i + 1 << " " << RESET;
        cout << BOARD << "│" << RESET;
        for (int j = 0 ; j < 8 ; j ++) {// 棋盘格背景色
            if ((i + j) % 2 == 0) cout << WHITE_BG;// 棋盘格背景色
            else cout << BLACK_BG;
            switch (gridInfo[i][j]) {// 显示内容（每个格子3字符宽）
                case 0:// 空地
                    cout << " · ";
                    break;
                case 1:// 黑棋
                    cout << "⚫ ";
                    break;
                case 2:// 白棋
                    cout << "⚪ ";
                    break;
                case 3:// 障碍
                    cout << "🚫 ";
                    break;
                default:
                    cout << " ? ";
            }
            cout << RESET << BOARD;
            if (j < 7) cout << "│";
            cout << RESET;
        }
        cout << BOARD << "│" << RESET << endl;
        if (i < 7) {// 行间分隔线（最后一行除外）
            cout << BOARD << "   ├";
            for (int j = 0; j < 7; j++) {
                cout << "───┼";
            }
            cout << "───┤" << RESET << endl;
        }
    }
    cout << BOARD << "   └";// 下边框
    for (int j = 0 ; j < 7 ; j ++) {
        cout << "───┴";
    }
    cout << "───┘" << RESET << endl;
    cout << "图例: ⚫ = 黑方亚马逊, ⚪ = 白方亚马逊, 🚫 = 障碍" << endl;;// 彩色图例
}

// 函数18：inMap判断是否在地图内
bool inMap(int x , int y){
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
		return false;
	return true;
}

// 函数19：canMove遍历求解所有可动的位置
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

// 函数20：生成1-10000随机整数
int randomNum(){
    static uniform_int_distribution<> dis(1, 10000);
    return dis(gen);
}

// 函数21：评估函数中控模块
double evaluate(const vector<vector<int>> &table , int botColor , int round){// 对于虚设棋盘+bot色号+轮次，进行基于bot的估价计算，保证bot行动最优
    int sum1 = QueenMove(table , botColor);// QueenMove：bot射线形移动直到遇到障碍，所能比人类多占位置的能力（最直接表征）
    int sum2 = KingMove(table , botColor);// KingMove：bot走周边8格bfs，到所有格子步数比人类小的程度的量化表征（机动性）
    int sum3 = PartitionScore(table , botColor);
    // 随轮次变化，QueenMove权重递增，KingMove和position递减
    if (round >= 1 && round <= 6) return sum1 * spec[0][0] + sum2 * spec[0][1] + sum3 * spec[0][2];
    else if (round >= 7 && round <= 18) return sum1 * spec[1][0] + sum2 * spec[1][1] + sum3 * spec[1][2];
    else return sum1 * spec[2][0] + sum2 * spec[2][1] + sum3 * spec[2][2];
}

// 函数22：QueenMove模块
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

// 函数23：KingMove模块
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

// 函数24：PartitionScore的DFS过程
void dfs_partition(const vector<vector<int>>& table , bool visited[8][8] , 
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

// 函数25：PartitionScore模块
int PartitionScore(const vector<vector<int>> &table , int botColor) {
    bool visited[8][8] = { };
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

// 函数26：回溯式alpha-beta剪枝
double ABSearch(vector<vector<int>> &table , int depth , 
    double alpha , double beta , bool isMaximizing , int currentRound) {// isMaxmizing：是bot就最大bot分数，是人类就最小bot分数
// α：MAX 方目前能找到的最佳值（下界）。在 MAX 节点，α 表示当前已知的最大值；
// 在 MIN 节点，α 继承自父节点，表示 MAX 方已经保证至少能得到 α。
// β：MIN 方目前能找到的最差值（上界）。在 MIN 节点，β 表示当前已知的最小值；
// 在 MAX 节点，β 继承自父节点，表示 MIN 方已经保证最多能让 MAX 得到 β。
    if(checkTime(gameRound)) return evaluate(table , botColor , currentRound);
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

    if (isMaximizing) {// bot行动，让bot分数最大化————MAX节点（注意：isMaxmizing交替轮换）
        double maxEval = -200000.0;// 虚设最小值取出最大值
        for (int i = 0 ; i < min(20 , n) ; i ++) {
            Move Amove = scoredMoves[i].move;
            table[Amove.x0][Amove.y0] = 0;// 模拟行动
            table[Amove.x1][Amove.y1] = currentColor;
            table[Amove.x2][Amove.y2] = 3;
            double eval = ABSearch(table , depth - 1 , alpha , beta , false , currentRound + 1);// 递归，下传alpha，beta
            table[Amove.x2][Amove.y2] = 0;// 回溯，不传棋盘，效率高
            table[Amove.x1][Amove.y1] = 0; 
            table[Amove.x0][Amove.y0] = currentColor;
            maxEval = max(maxEval , eval);// 更新与剪枝
            alpha = max(alpha , eval);// 更新，MAX节点更新传上来的alpha，beta保持不变
            if (alpha >= beta) {// 剪枝
                break; 
            }
        }
        return maxEval;
    }
    else {// 人类行动，让bot分数最小化————MIN节点
        double minEval = 200000.0;// 虚设最大值取出最小值
        for (int i = 0 ; i < min(20 , n) ; i ++) {
            Move Amove = scoredMoves[i].move;
            table[Amove.x0][Amove.y0] = 0;// 模拟行动
            table[Amove.x1][Amove.y1] = currentColor;
            table[Amove.x2][Amove.y2] = 3;
            double eval = ABSearch(table , depth - 1 , alpha , beta , true , currentRound + 1);// 递归，下传alpha，beta
            table[Amove.x2][Amove.y2] = 0;// 回溯
            table[Amove.x1][Amove.y1] = 0;
            table[Amove.x0][Amove.y0] = currentColor;
            minEval = min(minEval , eval);// 更新与剪枝
            beta = min(beta , eval);// 更新，MIN节点更新传上来的beta，alpha保持不变
            if (beta <= alpha) {// 剪枝
                break;
            }
        }
        return minEval;
    }
}

// 函数27：结合辅助结构体的排序函数
bool compareScoredMoves(const ScoredMove& a, const ScoredMove& b) {
    return a.score > b.score;
}

// 函数28：AB搜索超时检查
bool checkTime(int round) {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime1) >= (gameRound >= 3 ? TIME_LIMIT : TIME_LIMIT1);
}

// 主函数：启动器
int main(){
    menu();// menu函数为本程序主控函数，集成各个功能！
    cout << "还没开始就结束了XD" << endl;
    return 0;
}