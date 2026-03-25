// version3对战更新：高度利用【多态】以及【智能指针】来对基类/不同派生类秩序井然地分层处理！！！
// 本程序有两种类，第一种是全局变量中定义的基类，用于记录每一种武士的基本情况：HP、ATK、name，并且提供相关基类函数
// 第二种是全局变量智能指针数组，需要后续加入元素的派生类，数组里面装的是具体的武士个体对象，注意指针的调用格式
// 本程序中基类小写首字母，派生类大写首字母
// weapon:sword0-bomb1-arrow2
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <memory>
using namespace std;

int cityNum = 0;
int lionCut = 0;

class Warrior{// 基类，用于记录每种武士的基本情况
    private:
        int HP;
        string name;
        int ATK;
    public:
        Warrior(){  }
        Warrior(int n , int a , string x){HP = n; ATK = a; name = x;}
        void setInfo(int n , int a , string x){HP = n; ATK = a; name = x;}
        int getHP(){return HP;}
        int getATK(){return ATK;}
        string getName(){return name;}
        virtual bool & checkAlive(){static bool x = 0; return x;}// 这个非常好，直接标记死亡，根本不用担心指针内存释放，智能指针超赞
        virtual int & getLoyalty(){static int x = 0; return x;}// 虚设return防止报错
        virtual int & getPos(){static int x = 0; return x;}
        virtual int getNum(){return 0;}
        virtual void move(){33550336;}
        int & changeHP(){return HP;}
        virtual int getSword(){return 0;}
        virtual int getBomb(){return 0;}
        virtual int getArrow(){return 0;}
};

// 下为五个派生类，用于生成五种具体的武士，注意区分基类和派生类对象的【含义&作用】之区别
class Dragon: public Warrior{
    private:
        vector<int> weapon;
        int caseNum;// 武士对象的编号
        int pos;
        bool alive;
    public:
        Dragon(){  }
        Dragon(int n , string x , int time , int a , int p){
            Warrior::setInfo(n , a , x);// 调用基类中的函数去设置基类的private量
            weapon.assign(4 , 0);// 0为sword，1为bomb，2为没用过的arrow，3为用过的arrow
            caseNum = time + 1;
            weapon[caseNum % 3] = 1;
            pos = p;
            alive = true;
        }
        bool & checkAlive() override {return alive;} 
        int & getPos() override {return pos;}
        int getNum() override {return caseNum;}
        int getSword() override {return weapon[0];}
        int getBomb() override {return weapon[1];}
        int getArrow() override {return weapon[2] + weapon[3];}
};

class Ninja: public Warrior{
    private:
        vector<int> weapon;
        int caseNum;
        int pos;
        bool alive;
    public:
        Ninja(){  }
        Ninja(int n , string x , int time , int a , int p){
            Warrior::setInfo(n , a , x);
            weapon.assign(4 , 0);
            caseNum = time + 1;
            weapon[caseNum % 3] = 1;
            weapon[(caseNum + 1) % 3] = 1;
            pos = p;
            alive = true;
        }
        bool & checkAlive() override {return alive;} 
        int & getPos() override {return pos;}
        int getNum() override {return caseNum;}
        int getSword() override {return weapon[0];}
        int getBomb() override {return weapon[1];}
        int getArrow() override {return weapon[2] + weapon[3];}
};

class Iceman: public Warrior{
    private:
        vector<int> weapon;
        int caseNum;
        int pos;
        bool alive;
    public:
        Iceman(){  }
        Iceman(int n , string x , int time , int a , int p){
            Warrior::setInfo(n , a , x);
            weapon.assign(4 , 0);
            caseNum = time + 1;
            weapon[caseNum % 3] = 1;
            pos = p;
            alive = true;
        }
        bool & checkAlive() override {return alive;} 
        int & getPos() override {return pos;}
        int getNum() override {return caseNum;}
        void move() override {
            int cutHP = getHP() / 10;
            changeHP() = getHP() - cutHP;
        }
        int getSword() override {return weapon[0];}
        int getBomb() override {return weapon[1];}
        int getArrow() override {return weapon[2] + weapon[3];}
};

class Lion: public Warrior{
    private:
        vector<int> weapon;
        int loyalty;
        int caseNum;
        int pos;
        bool alive;
    public:
        Lion(){  }
        Lion(int n , string x , int HPleft , int time , int a , int p){
            Warrior::setInfo(n , a , x);
            weapon.assign(4 , 0);
            caseNum = time + 1;
            loyalty = HPleft;
            weapon[caseNum % 3] = 1;
            pos = p;
            alive = true;
            cout << "Its loyalty is " << loyalty << endl;
        }
        bool & checkAlive() override {return alive;} 
        int & getLoyalty() override {return loyalty;}
        int & getPos() override {return pos;}
        int getNum() override {return caseNum;}
        void move() override {getLoyalty() -= lionCut;}
        int getSword() override {return weapon[0];}
        int getBomb() override {return weapon[1];}
        int getArrow() override {return weapon[2] + weapon[3];}
};

class Wolf: public Warrior{
    private:
        vector<int> weapon;
        int caseNum;
        int pos;
        bool alive;
    public:
        Wolf(){  }
        Wolf(int n , string x , int time , int a , int p){
            Warrior::setInfo(n , a , x);
            weapon.assign(4 , 0);
            caseNum = time + 1;
            pos = p;
            alive = true;
        }
        bool & checkAlive() override {return alive;} 
        int & getPos() override {return pos;}
        int getNum() override {return caseNum;}
        int getSword() override {return weapon[0];}
        int getBomb() override {return weapon[1];}
        int getArrow() override {return weapon[2] + weapon[3];}
};

Warrior dragon , ninja , iceman , lion , wolf;// 基类下的五个对象，存储五种武士的基本信息
vector<unique_ptr<Warrior>> redList;// 智能指针数组，管理两方所有武士信息，注意调用问题和多态问题
vector<unique_ptr<Warrior>> blueList;
bool fin = false;// 司令部结束判据

void warriorBorn(int &HP , int totaltime , int &round , bool &stop , vector<Warrior> order , int color){
    int time = totaltime / 60;// 小时时间
    string side = (color == 0 ? "red" : "blue");
    bool checkStep = false;// 结束判据符号
    if (HP >= order[round].getHP()){
        checkStep = true;// 成功建造，不必结束

        cout << setw(3) << setfill('0') << time << ":00 " << side << " " << order[round].getName() << " " << time + 1 << " born" << endl;
        HP -= order[round].getHP();// 消耗生命元

        string tmpstr = order[round].getName();// 对每一个武士的个性化处理如下
        if (tmpstr == "dragon"){
            if(color == 0) redList.push_back(make_unique<Dragon>(order[round].getHP() , "dragon" , time , order[round].getATK() , 0));
            else blueList.push_back(make_unique<Dragon>(order[round].getHP() , "dragon" , time , order[round].getATK() , cityNum + 1));
        }
        else if (tmpstr == "ninja"){
            if (color == 0) redList.push_back(make_unique<Ninja>(order[round].getHP() , "ninja" , time , order[round].getATK() , 0));
            else blueList.push_back(make_unique<Ninja>(order[round].getHP() , "ninja" , time , order[round].getATK() , cityNum + 1));
        }
        else if (tmpstr == "iceman"){
            if (color == 0) redList.push_back(make_unique<Iceman>(order[round].getHP() , "iceman" , time , order[round].getATK() , 0));
            else blueList.push_back(make_unique<Iceman>(order[round].getHP() , "iceman" , time , order[round].getATK() , cityNum + 1));
        }
        else if (tmpstr == "lion"){
            if (color == 0) redList.push_back(make_unique<Lion>(order[round].getHP() , "lion" , HP , time , order[round].getATK() , 0));
            else blueList.push_back(make_unique<Lion>(order[round].getHP() , "lion" , HP , time , order[round].getATK() , cityNum + 1));
        }
        else if (tmpstr == "wolf"){
            if (color == 0) redList.push_back(make_unique<Wolf>(order[round].getHP() , "wolf" , time , order[round].getATK() , 0));
            else blueList.push_back(make_unique<Wolf>(order[round].getHP() , "wolf" , time , order[round].getATK() , cityNum + 1));
        }
        round = (round + 1) % 5;// 轮次增加
    }
    if (!checkStep) stop = true;// 终止某方建造过程
}

void lionEscape(int time){
    int hour = time / 60;
    vector<bool> redEscape(cityNum + 2 , false);
    vector<int> redNum(cityNum + 2 , 0);
    vector<bool> blueEscape(cityNum + 2 , false);
    vector<int> blueNum(cityNum + 2 , 0);

    for (auto & i : redList){
        if (i->checkAlive() && i->getName() == "lion"){
            if (i->getLoyalty() <= 0){
                i->checkAlive() = false;
                redEscape[i->getPos()] = true;
                redNum[i->getPos()] = i->getNum();
            }
        }
    }
    for (auto & i : blueList){
        if (i->checkAlive() && i->getName() == "lion"){
            if (i->getLoyalty() <= 0){
                i->checkAlive() = false;
                blueEscape[i->getPos()] = true;
                blueNum[i->getPos()] = i->getNum();
            }
        }
    }

    for (int i = 0 ; i < cityNum + 2 ; i ++){
        if (redEscape[i]) cout << setw(3) << setfill('0') << hour << ":05 red lion " << redNum[i] << " ran away" << endl;
        if (blueEscape[i]) cout << setw(3) << setfill('0') << hour << ":05 blue lion " << blueNum[i] << " ran away" << endl;
    }
}

struct Amove{
    string name;
    int num;
    int targetCity;
    int tempHP;
    int tempATK;
};

void warriorMarch(int time){// 包含了司令部结束综合判断：一头一尾，0 & N+1号城市
    int hour = time / 60;
    vector<bool> redCheck(cityNum + 2 , false);
    vector<Amove> redMove(cityNum + 2);
    vector<bool> blueCheck(cityNum + 2 , false);
    vector<Amove> blueMove(cityNum + 2);

    for (auto & i : redList){
        if (i->checkAlive()){
            i->getPos() += 1;
            if (i->getPos() == cityNum + 1) fin = true;
            i->move();
            redCheck[i->getPos()] = true;
            Amove temp;
            temp.name = i->getName();
            temp.num = i->getNum();
            temp.targetCity = i->getPos();
            temp.tempHP = i->getHP();
            temp.tempATK = i->getATK();
            redMove[i->getPos()] = temp;
        }
    }
    for (auto & i : blueList){
        if (i->checkAlive()){
            i->getPos() -= 1;
            if (i->getPos() == 0) fin = true;
            i->move();
            blueCheck[i->getPos()] = true;
            Amove temp;
            temp.name = i->getName();
            temp.num = i->getNum();
            temp.targetCity = i->getPos();
            temp.tempHP = i->getHP();
            temp.tempATK = i->getATK();
            blueMove[i->getPos()] = temp;
        }
    }

    if (blueCheck[0]){
        cout << setw(3) << setfill('0') << hour << ":10 blue " << blueMove[0].name <<
        " " << blueMove[0].num << " reached red headquarter with " << blueMove[0].tempHP
        << " elements and force " << blueMove[0].tempATK << endl;
        cout << setw(3) << setfill('0') << hour << ":10 red headquarter was taken" << endl;
    }
    for (int i = 1 ; i < cityNum + 1 ; i ++){
        if (redCheck[i]) cout << setw(3) << setfill('0') << hour << ":10 red " << redMove[i].name <<
        " " << redMove[i].num << " marched to city " << redMove[i].targetCity << " with " << redMove[i].tempHP
        << " elements and force " << redMove[i].tempATK << endl;
        if (blueCheck[i]) cout << setw(3) << setfill('0') << hour << ":10 blue " << blueMove[i].name <<
        " " << blueMove[i].num << " marched to city " << blueMove[i].targetCity << " with " << blueMove[i].tempHP
        << " elements and force " << blueMove[i].tempATK << endl;
    }
    if (redCheck[cityNum + 1]){
        cout << setw(3) << setfill('0') << hour << ":10 red " << redMove[cityNum + 1].name <<
        " " << redMove[cityNum + 1].num << " reached blue headquarter with " << redMove[cityNum + 1].tempHP
        << " elements and force " << redMove[cityNum + 1].tempATK << endl;
        cout << setw(3) << setfill('0') << hour << ":10 blue headquarter was taken" << endl;
    }
}

struct Awolf{
    bool canGet;
    int wolfNum;
    int swordNum;
    int bombNum;
    int arrowNum;
    string enemyName;
    int enemyNum;
    int cityNum;
};

void wolfGet(int time){
    int hour = time / 60;
    vector<bool> redWolf(cityNum + 2 , false);
    vector<Awolf> redAct(cityNum + 2);
    vector<bool> blueWolf(cityNum + 2 , false);
    vector<Awolf> blueAct(cityNum + 2);

    for (auto & i : redList){
        if (i->checkAlive() && i->getName() == "wolf") redWolf[i->getPos()] = true;
    }
    for (auto & i : blueList){
        if (i->checkAlive() && i->getName() == "wolf") blueWolf[i->getPos()] = true;
    }
    for (int i = 0 ; i < cityNum + 2 ; i ++){
        if (redWolf[i] && blueWolf[i]){
            redWolf[i] = false;
            blueWolf[i] = false;
        }
    }
    for (auto & i : redList){
        if (i->checkAlive() && blueWolf[i->getPos()]){// 蓝狼抢红色武士，装进蓝狼行动
// 如何高效获取指定城市的武士？
// 方法一：维护位置指针数组（推荐）
// 方法二：临时遍历（简单，适用于小数据）(我是新手我选这个XD)
// 待施工
        }
    }
    for (auto & i : blueList){
        if (i->checkAlive() && redWolf[i->getPos()]){// 红狼抢蓝色武士，装进红狼行动

        }
    }

    for (int i = 0 ; i < cityNum + 2 ; i ++){
        if (redWolf[i]) continue;
        if (blueWolf[i]) continue;
    }
}

void beginWars(int time){// 包含dragon的欢呼，一定要检查Alive状况！！！！！！！
    int hour = time / 60;
// 待施工
}

void reportHP(int time , int RHP , int BHP){
    int hour = time / 60;
    cout << setw(3) << setfill('0') << hour << ":50 " << RHP << " elements in red headquarter" << endl;
    cout << setw(3) << setfill('0') << hour << ":50 " << BHP << " elements in blue headquarter" << endl;
}

struct report{
    string name;
    int num;
    int swordNum;
    int bombNum;
    int arrowNum;
    int HP;
};

void reportWarrior(int time){
    int hour = time / 60;
    vector<bool> redCheck(cityNum + 2 , false);
    vector<report> redItem(cityNum + 2);
    vector<bool> blueCheck(cityNum + 2 , false);
    vector<report> blueItem(cityNum + 2);

    for (auto & i : redList){
        if (i->checkAlive()){
            redCheck[i->getPos()] = true;
            report temp;
            temp.name = i->getName();
            temp.num = i->getNum();
            temp.swordNum = i->getSword();
            temp.bombNum = i->getBomb();
            temp.arrowNum = i->getArrow();
            temp.HP = i->getHP();
            redItem[i->getPos()] = temp;
        }
    }
    for (auto & i : blueList){
        if (i->checkAlive()){
            blueCheck[i->getPos()] = true;
            report temp;
            temp.name = i->getName();
            temp.num = i->getNum();
            temp.swordNum = i->getSword();
            temp.bombNum = i->getBomb();
            temp.arrowNum = i->getArrow();
            temp.HP = i->getHP();
            blueItem[i->getPos()] = temp;
        }
    }

    for (int i = 0 ; i < cityNum + 2 ; i ++){
        if (redCheck[i]) cout << setw(3) << setfill('0') << hour << ":55 red " << redItem[i].name << " " << redItem[i].num
        << " has " << redItem[i].swordNum << " sword " << redItem[i].bombNum << " bomb " << redItem[i].arrowNum <<
        " arrow and " << redItem[i].HP << " elements" << endl;
        if (blueCheck[i]) cout << setw(3) << setfill('0') << hour << ":55 blue " << blueItem[i].name << " " << blueItem[i].num
        << " has " << blueItem[i].swordNum << " sword " << blueItem[i].bombNum << " bomb " << blueItem[i].arrowNum <<
        " arrow and " << blueItem[i].HP << " elements" << endl;
    }
}

int main(){
    int CASENUM = 0;
    cin >> CASENUM;
    for (int i = 1 ; i <= CASENUM ; i ++){
        redList.clear();// 新一轮循环清除记录的武士信息
        blueList.clear();
        fin = false;
        cout << "Case:" << i << endl;
        int totalHP = 0;
        int timeLimit = 0;
        cin >> totalHP >> cityNum >> lionCut >> timeLimit;
        int RHP = totalHP;
        int Rround = 0;
        bool Rstop = false;
        int BHP = totalHP;
        int Bround = 0;
        bool Bstop = false;
        vector<int> HPlist(5);
        vector<int> ATKlist(5);
        for (int j = 0 ; j < 5 ; j ++) {cin >> HPlist[j];}
        for (int j = 0 ; j < 5 ; j ++) {cin >> ATKlist[j];}
        int time = 0;
        dragon = Warrior(HPlist[0] , ATKlist[0] , "dragon");// 基类对象初始化：记录HP与名称，设置数目为0
        ninja = Warrior(HPlist[1] , ATKlist[1] , "ninja");
        iceman = Warrior(HPlist[2] , ATKlist[2] , "iceman");
        lion = Warrior(HPlist[3] , ATKlist[3] , "lion");
        wolf = Warrior(HPlist[4] , ATKlist[4] , "wolf");
        vector<Warrior> redOrder = {iceman , lion , wolf , ninja , dragon};
        vector<Warrior> blueOrder = {lion , dragon , ninja , iceman , wolf};
        while(time <= timeLimit && !fin){
            if (!Rstop) warriorBorn(RHP , time , Rround , Rstop , redOrder , 0);// stop标志会在函数中通过传引用来改变
            if (!Bstop) warriorBorn(BHP , time , Bround , Bstop , blueOrder , 1);// 从而确定终止
            time += 5;
            if (time > timeLimit) break;
            lionEscape(time);
            time += 5;
            if (time > timeLimit) break;
            warriorMarch(time);
            if (fin) break;
            time += 25;
            if (time > timeLimit) break;
            wolfGet(time);
            time += 5;
            if (time > timeLimit) break;
            beginWars(time);
            time += 10;
            if (time > timeLimit) break;
            reportHP(time , RHP , BHP);
            time += 5;
            if (time > timeLimit) break;
            reportWarrior(time);
            time += 5;
            if (time > timeLimit) break;
        }
    }
    return 0;
}