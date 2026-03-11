// 8*8亚马逊棋，由LEAF所作
// version2.5，完善了悔棋+多存档功能，完全改好了输入模块使输入处理精准高效
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <queue>
using namespace std;

// 定义基础参量
const int grid_black = 1;// 黑子表示为1
const int grid_white = 2;// 白子表示为2
const int OBSTACLE = 3;// 障碍表示为3
int color = 0;// 我所执子颜色（1为黑，2为白，棋盘状态亦同）
int botColor = 0;// bot的颜色
int gameRound = 1;// 游戏轮次
int undoRound = -1;// 悔棋轮次
bool canUndo = false;// 当前可否悔棋
vector<vector<int>> gridInfo(8 , vector<int> (8 , 0));// 先x后y，记录棋盘状态，未被占据为0
vector<vector<int>> gridUndo(8 , vector<int> (8 , 0));// 悔棋暂存数组
vector<int> dx = {-1 , -1 , -1 , 0 , 0 , 1 , 1 , 1};// 8个方向
vector<int> dy = {-1 , 0 , 1 , -1 , 1 , -1 , 0 , 1};// 8个方向
struct Move {// 结构体打包一次行动
    int x0, y0;// 起点
    int x1, y1;// 终点
    int x2, y2;// 障碍位置
};
random_device rd;
mt19937 gen(rd());// 随机数生成引擎
vector<vector<double>> spec = {// 随对局更改的估价函数参数
    {0.5 , 1.2 , 0.8} ,
    {1.5 , 0.5 , 0.3} , 
    {2.0 , 0.1 , 0.0}
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

// 函数声明
bool inMap(int x , int y);// 函数1：inMap判断是否在地图内
vector<Move> canMove(int color , const vector<vector<int>> &table);// 函数2：canMove遍历求解所有可动的位置
int randomNum();// 函数3：生成1-10000随机整数
void newGame();// 函数4：新游戏，初始化棋盘状态
void fileIn();// 函数5：存盘
void fileOut();// 函数6：读盘
void menu();// 函数7：菜单
void singleTurnHuman();// 函数8：人类进行单轮对局
void singleTurnBot();// 函数9：bot进行单轮对局
void colorChoice();// 函数10：随机选棋子颜色
void gameCycle();// 函数11：回合循环轮替，避免递归过深
bool endGame();// 函数12：游戏结束的判定
double evaluate(const vector<vector<int>> &table , int botColor , int round);// 函数13：评估函数中控模块
int QueenMove(const vector<vector<int>> &table , int botColor);// 函数14：QueenMove模块
int KingMove(const vector<vector<int>> &table , int botColor);// 函数15：KingMove模块
int position(const vector<vector<int>> &table , int botColor);// 函数16：位置价值模块
void Undo();// 函数17：悔棋功能
    
// 函数1：inMap判断是否在地图内
bool inMap(int x , int y){
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
		return false;
	return true;
}

// 函数2：canMove遍历求解所有可动的位置
vector<Move> canMove(int color , const vector<vector<int>> &table) {// 带入色号检查，黑子1，白子2；双变量便于搜索时不干扰现有棋盘
    vector<Move> moves;    
    for (int x0 = 0 ; x0 < 8 ; x0 ++) {// 找到所有己方棋子(基于己方棋子行动)
        for (int y0 = 0 ; y0 < 8 ; y0 ++) {
            if (table[x0][y0] != color) continue;

            for (int dir = 0 ; dir < 8 ; dir ++) {// 枚举移动目标位置
                for (int step = 1 ; step < 8 ; step ++) {
                    int x1 = x0 + dx[dir] * step;
                    int y1 = y0 + dy[dir] * step;
                    if (!inMap(x1 , y1) || table[x1][y1] != 0)
                        break; // 转换枚举方向，到此为止

                    for (int dir2 = 0 ; dir2 < 8 ; dir2++) {// 枚举障碍放置位置
                        for (int step2 = 1 ; step2 < 8 ; step2 ++) {
                            int x2 = x1 + dx[dir2] * step2;
                            int y2 = y1 + dy[dir2] * step2;
                            if (!inMap(x2 , y2)) break; // 转换枚举方向，到此为止(先判防止越界)
                            if (table[x2][y2] == 0 || (x2 == x0 && y2 == y0)) {// 障碍可以放在空位或自己的起点
                                moves.push_back({x0 , y0 , x1 , y1 , x2 , y2});// 加入可能的移动
                            }
                            if (table[x2][y2] != 0 && !(x2 == x0 && y2 == y0))
                                break;// 转换枚举方向，到此为止
                        }
                    }
                }
            }
        }
    }
    return moves;
}

// 函数3：生成1-10000随机整数
int randomNum(){
    static uniform_int_distribution<> dis(1, 10000);
    return dis(gen);
}

// 函数4：新游戏，初始化棋盘状态
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
    colorChoice();// 调用随机黑白函数
    gameCycle();// 选好棋子后进入循环
}

// 函数5：存盘
void fileIn(){
    string n;
    while(true){// 实现多个存档
        cout << "这是存盘程序，你可以将目前的对局存到3个存档中" << endl;
        cout << "请输入1-3选择你要存档的位置，注意存档会覆盖原有信息" << endl;
        getline(cin , n);
        if (n != "1" && n != "2" && n != "3"){
            cout << "无效输入，已返回！" << endl;
            continue;
        }
        else
            break;
    }
    if (n == "1"){
        ofstream fout("preserved1.txt");// 相对地址，便于移植，但不会显示在Amazons文件夹
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fout << gridInfo[i][j] << " ";
            }
            fout << endl;
        }
        fout << color << endl;
        fout << botColor << endl;
        fout << gameRound << endl;// 存盘存储棋盘、黑白、轮次、模式后就可以随时调用
        fout << canUndo << endl;
        fout << undoRound << endl;// 补充存盘悔棋相关信息
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fout << gridUndo[i][j] << " ";
            }
            fout << endl;
        }
        fout.close();
    }
    else if (n == "2"){
        ofstream fout("preserved2.txt");
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fout << gridInfo[i][j] << " ";
            }
            fout << endl;
        }
        fout << color << endl;
        fout << botColor << endl;
        fout << gameRound << endl;
        fout << canUndo << endl;
        fout << undoRound << endl;
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fout << gridUndo[i][j] << " ";
            }
            fout << endl;
        }
        fout.close();
    }
    else if (n == "3"){
        ofstream fout("preserved3.txt");
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fout << gridInfo[i][j] << " ";
            }
            fout << endl;
        }
        fout << color << endl;
        fout << botColor << endl;
        fout << gameRound << endl;
        fout << canUndo << endl;
        fout << undoRound << endl;
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fout << gridUndo[i][j] << " ";
            }
            fout << endl;
        }
        fout.close();
    }
    cout << "存盘成功，游戏暂停" << endl;
    exit(0);// 存盘后退出程序，相当于暂停
}

// 函数6：读盘
void fileOut(){
    string n;
    while(true){// 实现多个存档
        cout << "这是读盘程序，你可以从3个存档中选择一个读入当前对局" << endl;
        cout << "请输入1-3选择你要读档的记录，注意读档会覆盖现有游戏" << endl;
        getline(cin , n);
        if (n != "1" && n != "2" && n != "3"){
            cout << "无效输入，已返回！" << endl;
            continue;
        }
        else
            break;
    }
    if (n == "1"){
        ifstream fin("preserved1.txt");// 相对地址，便于移植，但不会显示在Amazons文件夹
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fin >> gridInfo[i][j];
            }
        }
        fin >> color;
        fin >> botColor;
        fin >> gameRound;// 录入记录，开始存档的游戏
        fin >> canUndo;
        fin >> undoRound;// 补充录入悔棋相关信息
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
    }
    else if (n == "2"){
        ifstream fin("preserved2.txt");
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fin >> gridInfo[i][j];
            }
        }
        fin >> color;
        fin >> botColor;
        fin >> gameRound;
        fin >> canUndo;
        fin >> undoRound;
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fin >> gridUndo[i][j];
            }
        }
        if (color == 0){
            cout << "暂无存档，读盘失败，返回菜单！" << endl;
            menu();
            return;
        }
        fin.close();
    }
    else if (n == "3"){
        ifstream fin("preserved3.txt");
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fin >> gridInfo[i][j];
            }
        }
        fin >> color;
        fin >> botColor;
        fin >> gameRound;
        fin >> canUndo;
        fin >> undoRound;
        for (int i = 0 ; i < 8 ; i ++){
            for (int j = 0 ; j < 8 ; j ++){
                fin >> gridUndo[i][j];
            }
        }
        if (color == 0){
            cout << "暂无存档，读盘失败，返回菜单！" << endl;
            menu();
            return;
        }
        fin.close();
    }
    cout << "读盘成功，游戏继续" << endl;
    gameCycle();// 读盘后进入游戏循环
}

// 函数7：菜单
void menu(){
    string n;// **要用string+getline，否则会有各式各样的输入bug
    while(true){// 循环式菜单，比起自我递归调用式菜单，规避了栈溢出的风险
        cout << "亚马逊棋游戏运行中，你有如下5个选择" << endl;
        cout << "输入1开始新游戏，输入2存盘并中止游戏，输入3读盘并恢复游戏，输入4悔棋，输入5终止游戏" << endl;
        getline(cin , n);
        if (n != "1" && n != "2" && n != "3" && n != "4" && n != "5"){
            cout << "无效输入，返回菜单！" << endl;
            continue;
        }
        else if (n == "1"){// 新游戏-1
            string check;
            cout << "确定开始新游戏吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                cout << "新游戏开始!" << endl;
                newGame();
            }
            else if (check == "n"){
                cout << "返回菜单" << endl;
                continue;// 也就是重新开始while循环，重新执行菜单指令
            }
            else{
                cout << "无效输入，返回菜单！" << endl;
                continue;
            }
        }
        else if (n == "2"){// 存盘-2
            string check;
            cout << "确定存盘吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                fileIn();
            }
            else if (check == "n"){
                cout << "返回菜单" << endl;
                continue;
            }
            else{
                cout << "无效输入，返回菜单！" << endl;
                continue;
            }
        }      
        else if (n == "3"){// 读盘-3
            string check;
            cout << "确定读盘吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                fileOut();
            }
            else if (check == "n"){
                cout << "返回菜单" << endl;
                continue;
            }
            else{
                cout << "无效输入，返回菜单！" << endl;
                continue;
            }
        }
        else if (n == "4"){// 悔棋-4
            string check;
            cout << "确定悔棋吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                Undo();
            }
            else if (check == "n"){
                cout << "返回菜单" << endl;
                continue;
            }
            else{
                cout << "无效输入，返回菜单！" << endl;
                continue;
            }
        }
        else if (n == "5"){// 结束游戏-5
            string check;
            cout << "确定结束吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                cout << "游戏结束" << endl;
                exit(0);
            }
            else if (check == "n"){
                cout << "返回菜单" << endl;
                continue;
            }
            else{
                cout << "无效输入，返回菜单！" << endl;
                continue;
            }
        }
    }
}

// 函数8：人类进行单轮对局
void singleTurnHuman(){
    cout << "——————————————第" << gameRound << "轮——人类行" << (color == 1 ? "黑" : "白") << "棋——————————————" << endl;
    cout << "当前棋盘状态如下" << endl;
    for (int i = 0 ; i < 8 ; i ++){// 打印棋盘，方便玩家继续刚读盘的游戏，让玩家的思考更便捷
        for (int j = 0 ; j < 8 ; j ++){
           cout << gridInfo[i][j] << " ";
        }
        cout << endl;
    }
    bool actionCheck = false;// 循环1结束信号
    bool chessCheck = false;// 循环2结束信号
    string n;
    while(!actionCheck){// 类似菜单函数，采用两个while循环从而避免自我调用
        cout << "轮到你行动了，输入1可以行棋，输入2可以进入菜单" << endl;
        cout << "菜单包含新游戏、存盘、读盘、悔棋、结束游戏5个功能" << endl;
        getline(cin , n);
        if (n != "1" && n != "2"){
            cout << "无效输入，请重试！" << endl;
            continue;
        }
        else if (n == "1"){
            cout << "行棋开始" << endl;
            actionCheck = true;// 开始后退出这个循环，开启下一个循环
        }
        else if (n == "2"){
            string check;
            cout << "确定进入菜单吗？y/n" << endl;
            getline(cin , check);
            if (check == "y") {
                actionCheck = true;
                cout << "进入菜单" << endl;
                menu();
                return;// 保险返回语句
            }
            else if (check == "n"){
                cout << "已返回到行动前" << endl;
                continue;
            }
            else{
                cout << "无效输入，已返回到行动前！" << endl;
                continue;
            }
        }
    }
    gridUndo = gridInfo;// 悔棋暂存记录，决定行棋后再存悔棋信息
    canUndo = true;// 有过行棋，可以悔棋，但不能连续悔棋，因为再次可以悔棋需要经过一次行棋
    while(!chessCheck){
        string x0 , y0 , x1 , y1 , x2 , y2;
        Move move;
        vector<Move> list = canMove(color , gridInfo);// list数组存储所有的Move方式，以待后续检查
        cout << "请输入你要移动的棋子行坐标" << endl;
        getline(cin , x0);
        if (x0[0] < '0' || x0[0] > '7' || x0.size() >= 2 || x0.empty()){
            cout << "非法输入，请重试" << endl;
            continue;
        }
        cout << "请输入你要移动的棋子列坐标" << endl;
        getline(cin , y0);
        if (y0[0] < '0' || y0[0] > '7' || y0.size() >= 2 || y0.empty()){
            cout << "非法输入，请重试" << endl;
            continue;
        }
        cout << "请输入你的移动终点行坐标" << endl;
        getline(cin , x1);
        if (x1[0] < '0' || x1[0] > '7' || x1.size() >= 2 || x1.empty()){
            cout << "非法输入，请重试" << endl;
            continue;
        }
        cout << "请输入你的移动终点列坐标" << endl;
        getline(cin , y1);
        if (y1[0] < '0' || y1[0] > '7' || y1.size() >= 2 || y1.empty()){
            cout << "非法输入，请重试" << endl;
            continue;
        }
        cout << "请输入你放置障碍的行坐标" << endl;
        getline(cin , x2);
        if (x2[0] < '0' || x2[0] > '7' || x2.size() >= 2 || x2.empty()){
            cout << "非法输入，请重试" << endl;
            continue;
        }
        cout << "请输入你放置障碍的列坐标" << endl;
        getline(cin , y2);
        if (y2[0] < '0' || y2[0] > '7' || y2.size() >= 2 || y2.empty()){
            cout << "非法输入，请重试" << endl;
            continue;
        }
        string check;
        cout << "确定行棋吗？你现在将" << "(" << x0 << "," << y0 << ")" << "的棋子"
             << "移到了" << "(" << x1 << "," << y1 << ")," << "并且在" 
             << "(" << x2 << "," << y2 << ")" << "放置了障碍" << "————y/n" << endl;
        getline(cin , check);
        if (check == "y") {
            cout << "行棋开始" << endl;
        }
        else if (check == "n"){
            cout << "已返回到行动前" << endl;
            continue;
        }
        else{
            cout << "无效输入，已返回到行动前！" << endl;
            continue;
        }
        move = {x0[0] - '0' , y0[0] - '0' , x1[0] - '0' , y1[0] - '0' , x2[0] - '0' , y2[0] - '0'};
        bool isValid = false;// 判断0-7的数字输入是否合法
        for (int i = 0 ; i < list.size() ; i ++){// 搜索得到Move方式合法之后就跳出循环并标记合法
            if (move.x0 == list[i].x0 && move.y0 == list[i].y0 && move.x1 == list[i].x1 &&
                move.y1 == list[i].y1 && move.x2 == list[i].x2 && move.y2 == list[i].y2){
                    isValid = true;
                    break;// 存在相同Move在list队列中，跳出循环，标记可行
                }
        }
        if (isValid){// 对于合法的Move，更改棋盘状态
            gridInfo[move.x0][move.y0] = 0;
            gridInfo[move.x1][move.y1] = color;
            gridInfo[move.x2][move.y2] = 3;
            chessCheck = true;// Move合法，跳出循环
            for (int i = 0 ; i < 8 ; i ++){
                for (int j = 0 ; j < 8 ; j ++){
                    cout << gridInfo[i][j] << " ";
                }
                cout << endl;
            }// 输出用户行棋之后的棋盘
            cout << "合法输入，棋盘状态已经更新" << endl;
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
                    actionCheck = true;
                    cout << "进入菜单" << endl;
                    menu();
                    return;
                }
                else if (check == "n"){
                    cout << "继续尝试行棋" << endl;
                    continue;// 重新开始第二个while循环，也就是再尝试行棋过程
                }
                else{
                    cout << "无效输入，继续尝试行棋！" << endl;
                    continue;
                }
            }
            else
                continue;
        }
    }
}

// 函数9：bot进行单轮对局
void singleTurnBot(){
    cout << "——————————————第" << gameRound << "轮——bot行" << (botColor == 1 ? "黑" : "白") << "棋——————————————" << endl;
    vector<Move> possibleMoves = canMove(botColor , gridInfo);// 虚设canMove得到的数组，避免多次调用canMove函数，大大节省时间
    int n = possibleMoves.size();// 直接用成品数组，防止多次调用
    Move bestMove;
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
    gridInfo[bestMove.x0][bestMove.y0] = 0;
    gridInfo[bestMove.x1][bestMove.y1] = botColor;
    gridInfo[bestMove.x2][bestMove.y2] = 3;// 基于bestMove更改全局现有棋盘
    cout << "bot行动完毕，将" << "(" << bestMove.x0 << "," << bestMove.y0 << ")" << "的棋子"
         << "移到了" << "(" << bestMove.x1 << "," << bestMove.y1 << ")," << "并且在" 
         << "(" << bestMove.x2 << "," << bestMove.y2 << ")" << "放置了障碍" << endl;
    for (int i = 0 ; i < 8 ; i ++){// 输出bot行动后的棋盘
        for (int j = 0 ; j < 8 ; j ++){
           cout << gridInfo[i][j] << " ";
        }
        cout << endl;
    }
}

// 函数10：随机选棋子颜色
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

// 函数11：回合循环轮替
void gameCycle(){
    if (botColor == 1){// bot执黑，奇数bot，偶数人类
        while(!endGame()){
            if (gameRound % 2 == 1){
                singleTurnBot();
                gameRound ++;// 单方行动完后轮次+1
                undoRound ++;
            }
            else if (gameRound % 2 == 0){
                singleTurnHuman();
                gameRound ++;
                undoRound ++;
            }
        }
    }
    else if (botColor == 2){// bot执白，奇数人类，偶数bot
        while(!endGame()){
            if (gameRound % 2 == 1){
                singleTurnHuman();
                gameRound ++;
                undoRound ++;
            }
            else if (gameRound % 2 == 0){
                singleTurnBot();
                gameRound ++;
                undoRound ++;
            }
        }
    }
    exit(0);// endGame函数判断游戏结束后跳出while循环，程序也结束
}

// 函数12：游戏结束的判定
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
        cout << "恭喜您获胜！" << endl;
        return true;
    }
    else
        return false;
}

// 函数13：评估函数中控模块
double evaluate(const vector<vector<int>> &table , int botColor , int round){// 对于虚设棋盘+bot色号+轮次，进行基于bot的估价计算，保证bot行动最优
    int sum1 = QueenMove(table , botColor);// QueenMove：bot射线形移动直到遇到障碍，所能比人类多占位置的能力（最直接表征）
    int sum2 = KingMove(table , botColor);// KingMove：bot走周边8格bfs，到所有格子步数比人类小的程度的量化表征（机动性）
    int sum3 = position(table , botColor);// position：bot和人类棋子靠近棋盘中央的量化表征（经验结论）
    if (round >= 1 && round <= 15){// 随轮次变化，QueenMove权重递增，KingMove和position递减
        return sum1 * spec[0][0] + sum2 * spec[0][1] + sum3 * spec[0][2];
    }
    else if (round >= 16 && round <= 35){
        return sum1 * spec[1][0] + sum2 * spec[1][1] + sum3 * spec[1][2];
    }
    else{
        return sum1 * spec[2][0] + sum2 * spec[2][1] + sum3 * spec[2][2];
    }
}

// 函数14：QueenMove模块
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
                    if (!inMap(x , y) || table[x][y] != 0)// 先判断越界后标定canBot的值，由于inMap在前，故不会越界
                        break;// 越界或者遇到障碍就停止遍历
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
                    if (!inMap(x , y) || table[x][y] != 0)// 先判断越界后标定canBot的值，由于inMap在前，故不会越界
                        break;// 越界或者遇到障碍就停止遍历
                    canHuman[x][y] = true;
                }
            }
        }
    }
    int result = 0;
    for (int i = 0 ; i < 8 ; i ++){// 更好的权重多样化处理：bot单占+3，人类单占-3，公用+1
        for (int j = 0 ; j < 8 ; j ++){
            if (canBot[i][j] && !canHuman[i][j])
                result += 3;
            else if (canHuman[i][j] && !canBot[i][j])
                result -= 3;
            else if (canBot[i][j] && canHuman[i][j])
                result ++;
        }
    }
    return result;
}

// 函数15：KingMove模块
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
            if (table[i][j] == botColor)
                bot.push({i , j , 0});
            else if (table[i][j] == color)
                human.push({i , j , 0});
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
            if (minBot[i][j] < minHuman[i][j])
                result ++;
            else if (minBot[i][j] > minHuman[i][j])
                result --;
        }
    }
    return result;
}

// 函数16：位置价值模块
int position(const vector<vector<int>> &table , int botColor){
    int color = 3 - botColor;
    int result = 0;
    for (int i = 0 ; i < 8 ; i ++){// 该函数相对较为简单，根据全局变量中的位置-价值数组即可得出
        for (int j = 0 ; j < 8 ; j ++){
            if (table[i][j] == botColor)
                result += valuePos[i][j];
            else if (table[i][j] == color)
                result -= valuePos[i][j];
        }
    }
    return result;
}

// 函数17：悔棋功能
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
    cout << "已经悔棋到第" << gameRound << "轮，由您重新行动" << endl;
    cout << "注意：不允许连续悔棋多步，只回退到上一次人类行动" << endl;
    gameCycle();
}

// 主函数：启动器
int main(){
    menu();// menu函数为本程序主控函数，集成各个功能！
    return 0;
}

// 吃完饭回来先写难度设置，分为三档，随机数/正式算法/挑战：正式算法+限时+无法悔棋/暂停（学一下计时）