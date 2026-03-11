// 8*8亚马逊棋，由LEAF所作
// version1，搭建好基础模块，采用随机数算法过渡
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
using namespace std;

// 定义基础参量
const int grid_black = 1;// 黑子表示为1
const int grid_white = 2;// 白子表示为2
const int OBSTACLE = 3;// 障碍表示为3
int color = 0; // 我所执子颜色（1为黑，2为白，棋盘状态亦同）
int botColor = 0; // bot的颜色
int gameRound = 1; // 游戏轮次
vector<vector<int>> gridInfo(8 , vector<int> (8 , 0));// 先x后y，记录棋盘状态，未被占据为0
vector<int> dx = {-1 , -1 , -1 , 0 , 0 , 1 , 1 , 1};// 8个方向
vector<int> dy = {-1 , 0 , 1 , -1 , 1 , -1 , 0 , 1};// 8个方向
struct Move {// 结构体打包一次行动
    int x0, y0; // 起点
    int x1, y1; // 终点
    int x2, y2; // 障碍位置
};
random_device rd;
mt19937 gen(rd());// 随机数生成引擎

// 函数声明
bool inMap(int x, int y);            // 函数1：inMap判断是否在地图内
vector<Move> canMove(int color);     // 函数2：canMove遍历求解所有可动的位置
int randomNum();                     // 函数3：生成1-10000随机整数
void newGame();                      // 函数4：新游戏，初始化棋盘状态
void fileIn();                       // 函数5：存盘
void fileOut();                      // 函数6：读盘
void menu();                         // 函数7：菜单
void singleTurnHuman();              // 函数8：人类进行单轮对局
void singleTurnBot();                // 函数9：bot进行单轮对局
void colorChoice();                  // 函数10：随机选棋子颜色
void gameCycle();                    // 函数11：回合循环轮替，避免递归过深
bool endGame();                      // 函数12：游戏结束的判定
    
// 函数1：inMap判断是否在地图内
bool inMap(int x, int y){
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
            gridInfo[i][j] = 0;
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
    colorChoice();
    gameCycle();
}

// 函数5：存盘
void fileIn(){
    ofstream fout("preserved.txt");
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            fout << gridInfo[i][j] << " ";
        }
        fout << endl;
    }
    fout << color << endl;
    fout << botColor << endl;
    fout << gameRound << endl;
    fout.close();
    exit(0);
}

// 函数6：读盘
void fileOut(){
    ifstream fin("preserved.txt");
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
            fin >> gridInfo[i][j];
        }
    }
    fin >> color;
    fin >> botColor;
    fin >> gameRound;
    if (color == 0){
        cout << "暂无存档，读盘失败，返回菜单！" << endl;
        menu();
        return;
    }
    fin.close();
    gameCycle();
}

// 函数7：菜单
void menu(){
    int n;
    while(true){
        cout << "亚马逊棋游戏运行中，你有如下4个选择" << endl;
        cout << "输入1开始新游戏，输入2存盘并中止游戏，输入3读盘并恢复游戏，输入4终止游戏" << endl;
        cin >> n;
        if (n != 1 && n != 2 && n != 3 && n != 4){
            cout << "无效输入，返回菜单！" << endl;
            continue;
        }
        else if (n == 1){
            char check;
            cout << "确定开始新游戏吗？y/n" << endl;
            cin >> check;
            if (check == 'y') {
                cout << "新游戏开始!" << endl;
                newGame();
            }
            else if (check == 'n'){
                cout << "返回菜单" << endl;
                continue;
            }
            else{
                cout << "无效输入，返回菜单！" << endl;
                continue;
            }
        }
        else if (n == 2){
            char check;
            cout << "确定存盘吗？y/n" << endl;
            cin >> check;
            if (check == 'y') {
                cout << "存盘成功，游戏暂停" << endl;
                fileIn();
            }
            else if (check == 'n'){
                cout << "返回菜单" << endl;
                continue;
            }
            else{
                cout << "无效输入，返回菜单！" << endl;
                continue;
            }
        }      
        else if (n == 3){
            char check;
            cout << "确定读盘吗？y/n" << endl;
            cin >> check;
            if (check == 'y') {
                cout << "读盘成功，游戏继续" << endl;
                fileOut();
            }
            else if (check == 'n'){
                cout << "返回菜单" << endl;
                continue;
            }
            else{
                cout << "无效输入，返回菜单！" << endl;
                continue;
            }
        }
        else if (n == 4){
            char check;
            cout << "确定结束吗？y/n" << endl;
            cin >> check;
            if (check == 'y') {
                cout << "游戏结束" << endl;
                exit(0);
            }
            else if (check == 'n'){
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
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
           cout << gridInfo[i][j] << " ";
        }
        cout << endl;
    }
    bool actionCheck = false;
    bool chessCheck = false;
    int n;
    while(!actionCheck){
        cout << "轮到你行动了，输入1可以行棋，输入2可以进入菜单" << endl;
        cout << "菜单包含新游戏、存盘、读盘、结束游戏4个功能" << endl;
        cin >> n;
        if (n != 1 && n != 2){
            cout << "无效输入，请重试！" << endl;
            continue;
        }
        else if (n == 1){
            cout << "行棋开始" << endl;
            actionCheck = true;
        }
        else if (n == 2){
            char check;
            cout << "确定进入菜单吗？y/n" << endl;
            cin >> check;
            if (check == 'y') {
                actionCheck = true;
                cout << "进入菜单" << endl;
                menu();
                return;
            }
            else if (check == 'n'){
                cout << "已返回到行动前" << endl;
                continue;
            }
            else{
                cout << "无效输入，已返回到行动前！" << endl;
                continue;
            }
        }
    }
    while(!chessCheck){
        int x0 , y0 , x1 , y1 , x2 , y2;
        Move move;
        vector<Move> list = canMove(color , gridInfo);
        cout << "请输入你要移动的棋子坐标" << endl;
        cin >> x0 >> y0;
        cout << "请输入你的移动终点坐标" << endl;
        cin >> x1 >> y1;
        cout << "请输入你放置障碍的坐标" << endl;
        cin >> x2 >> y2;
        char check;
        cout << "确定行棋吗？你现在将" << "(" << x0 << "," << y0 << ")" << "的棋子"
             << "移到了" << "(" << x1 << "," << y1 << ")," << "并且在" 
             << "(" << x2 << "," << y2 << ")" << "放置了障碍" << "————y/n" << endl;
        cin >> check;
        if (check == 'y') {
            cout << "行棋开始" << endl;
        }
        else if (check == 'n'){
            cout << "已返回到行动前" << endl;
            continue;
        }
        else{
            cout << "无效输入，已返回到行动前！" << endl;
            continue;
        }
        move = {x0 , y0 , x1 , y1 , x2 , y2};
        bool isValid = false;
        for (int i = 0 ; i < list.size() ; i ++){
            if (move.x0 == list[i].x0 && move.y0 == list[i].y0 && move.x1 == list[i].x1 &&
                move.y1 == list[i].y1 && move.x2 == list[i].x2 && move.y2 == list[i].y2){
                    isValid = true;
                    break;
                }
        }
        if (isValid){
            gridInfo[move.x0][move.y0] = 0;
            gridInfo[move.x1][move.y1] = color;
            gridInfo[move.x2][move.y2] = 3;
            chessCheck = true;
            for (int i = 0 ; i < 8 ; i ++){
                for (int j = 0 ; j < 8 ; j ++){
                    cout << gridInfo[i][j] << " ";
                }
                cout << endl;
            }
            cout << "合法输入，棋盘状态已经更新" << endl;
        }
        else{
            cout << "非法输入，请重试！" << endl;
            cout << "如有困难，输入1可以进入菜单，输入其他则继续尝试行棋" << endl;
            int giveUp;
            cin >> giveUp;
            if (giveUp == 1){
                char check;
                cout << "确定进入菜单吗？y/n" << endl;
                cin >> check;
                if (check == 'y') {
                    actionCheck = true;
                    cout << "进入菜单" << endl;
                    menu();
                    return;
                }
                else if (check == 'n'){
                    cout << "继续尝试行棋" << endl;
                    continue;
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
    int n = canMove(botColor , gridInfo).size();
    int ran = randomNum();
    ran %= n;
    Move move = canMove(botColor , gridInfo)[ran];
    gridInfo[move.x0][move.y0] = 0;
    gridInfo[move.x1][move.y1] = botColor;
    gridInfo[move.x2][move.y2] = 3;
    cout << "bot行动完毕，将" << "(" << move.x0 << "," << move.y0 << ")" << "的棋子"
         << "移到了" << "(" << move.x1 << "," << move.y1 << ")," << "并且在" 
         << "(" << move.x2 << "," << move.y2 << ")" << "放置了障碍" << endl;
    for (int i = 0 ; i < 8 ; i ++){
        for (int j = 0 ; j < 8 ; j ++){
           cout << gridInfo[i][j] << " ";
        }
        cout << endl;
    }
}

// 函数10：随机选棋子颜色
void colorChoice(){
    cout << "为您随机分配棋子颜色，黑先白后" << endl;
    int x = randomNum();
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
    if (botColor == 1){
        while(!endGame()){
            if (gameRound % 2 == 1){
                singleTurnBot();
                gameRound ++;
            }
            else if (gameRound % 2 == 0){
                singleTurnHuman();
                gameRound ++;
            }
        }
    }
    else if (botColor == 2){
        while(!endGame()){
            if (gameRound % 2 == 1){
                singleTurnHuman();
                gameRound ++;
            }
            else if (gameRound % 2 == 0){
                singleTurnBot();
                gameRound ++;
            }
        }
    }
    exit(0);
}

// 函数12：游戏结束的判定
bool endGame(){
    if (canMove(color , gridInfo).empty() && canMove(botColor , gridInfo).empty()){
        cout << "你和bot达成了平局！" << endl;
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

// 主函数：启动器
int main(){
    menu();
    return 0;
}