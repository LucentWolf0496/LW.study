// version3对战更新：高度利用【多态】以及【智能指针】来对基类/不同派生类秩序井然地分层处理！！！
// 本程序有两种类，第一种是全局变量中定义的基类，用于记录每一种武士的基本情况：HP、ATK、name，并且提供相关基类函数
// 第二种是全局变量智能指针数组，需要后续加入元素的派生类，数组里面装的是具体的武士个体对象，注意指针的调用格式
// 还有全局变量冗余指针数组，用于提供对于武士的O(1)复杂度访问以及便捷修改
// 本程序中基类小写首字母，派生类大写首字母
// 关于本代码中冗余指针数组和智能指针数组的配合：【【智能指针容器负责生命周期和全局遍历，冗余指针数组负责按城市快速访问】】。
// 冗余指针（Warrior*）和智能指针（unique_ptr<Warrior>）指向的是同一个对象。
// 通过冗余指针调用对象的成员函数来修改对象的状态，会直接作用到该对象上。
// 智能指针容器中存储的对象也会同步改变，因为它们共享同一块内存。
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
        virtual int & getSword(){static int x = 0; return x;}
        virtual int & getBomb(){static int x = 0; return x;}
        virtual int & getArrow1(){static int x = 0; return x;}
        virtual int & getArrow2(){static int x = 0; return x;}
        virtual int & getArrow3(){static int x = 0; return x;}
        virtual int totalWeapon(){return 0;}
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
            weapon.assign(5 , 0);// 0为sword，1为bomb，2为没用过的arrow，3为用过的arrow
            caseNum = time + 1;
            weapon[caseNum % 3] = 1;
            pos = p;
            alive = true;
        }
        bool & checkAlive() override {return alive;} 
        int & getPos() override {return pos;}
        int getNum() override {return caseNum;}
        int & getSword() override {return weapon[0];}
        int & getBomb() override {return weapon[1];}
        int & getArrow1() override {return weapon[2];}// 没用过的arrow
        int & getArrow2() override {return weapon[3];}// 用过的arrow
        int & getArrow3() override {return weapon[4];}// 新产生的用过的arrow
        int totalWeapon() override {return weapon[0] + weapon[1] + weapon[2] + weapon[3] + weapon[4];}
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
            weapon.assign(5 , 0);
            caseNum = time + 1;
            weapon[caseNum % 3] = 1;
            weapon[(caseNum + 1) % 3] = 1;
            pos = p;
            alive = true;
        }
        bool & checkAlive() override {return alive;} 
        int & getPos() override {return pos;}
        int getNum() override {return caseNum;}
        int & getSword() override {return weapon[0];}
        int & getBomb() override {return weapon[1];}
        int & getArrow1() override {return weapon[2];}// 没用过的arrow
        int & getArrow2() override {return weapon[3];}// 用过的arrow
        int & getArrow3() override {return weapon[4];}// 新产生的用过的arrow
        int totalWeapon() override {return weapon[0] + weapon[1] + weapon[2] + weapon[3] + weapon[4];}
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
            weapon.assign(5 , 0);
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
        int & getSword() override {return weapon[0];}
        int & getBomb() override {return weapon[1];}
        int & getArrow1() override {return weapon[2];}// 没用过的arrow
        int & getArrow2() override {return weapon[3];}// 用过的arrow
        int & getArrow3() override {return weapon[4];}// 新产生的用过的arrow
        int totalWeapon() override {return weapon[0] + weapon[1] + weapon[2] + weapon[3] + weapon[4];}
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
            weapon.assign(5 , 0);
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
        int & getSword() override {return weapon[0];}
        int & getBomb() override {return weapon[1];}
        int & getArrow1() override {return weapon[2];}// 没用过的arrow
        int & getArrow2() override {return weapon[3];}// 用过的arrow
        int & getArrow3() override {return weapon[4];}// 新产生的用过的arrow
        int totalWeapon() override {return weapon[0] + weapon[1] + weapon[2] + weapon[3] + weapon[4];}
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
            weapon.assign(5 , 0);
            caseNum = time + 1;
            pos = p;
            alive = true;
        }
        bool & checkAlive() override {return alive;} 
        int & getPos() override {return pos;}
        int getNum() override {return caseNum;}
        int & getSword() override {return weapon[0];}
        int & getBomb() override {return weapon[1];}
        int & getArrow1() override {return weapon[2];}// 没用过的arrow
        int & getArrow2() override {return weapon[3];}// 用过的arrow
        int & getArrow3() override {return weapon[4];}// 新产生的用过的arrow
        int totalWeapon() override {return weapon[0] + weapon[1] + weapon[2] + weapon[3] + weapon[4];}
};

Warrior dragon , ninja , iceman , lion , wolf;// 基类下的五个对象，存储五种武士的基本信息
vector<unique_ptr<Warrior>> redList;// 智能指针数组，管理两方所有武士信息，注意调用问题和多态问题
vector<unique_ptr<Warrior>> blueList;
vector<Warrior*> redCity;// 冗余数组————原始指针：便于O(1)访问某个城市的武士
vector<Warrior*> blueCity;
bool fin = false;// 司令部结束判据

void kill(int pos , int color){// 原始指针冗余数组的动态处理：武士死亡与前进
    if (color == 0) redCity[pos] = nullptr;
    else blueCity[pos] = nullptr;
}

void march(Warrior * x , int oldPos , int newPos , int color){// 不会发生覆盖！！因为auto的遍历是从左到右的，最开始遍历的武士在最远点
    if (color == 0) redCity[oldPos] = nullptr;
    else blueCity[oldPos] = nullptr;

    if (color == 0) redCity[newPos] = x;
    else blueCity[newPos] = x;
}

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
        if (color == 0) redCity[0] = redList.back().get();// 注意色号判别
        else blueCity[cityNum + 1] = blueList.back().get();
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
                kill(i->getPos() , 0);
                redEscape[i->getPos()] = true;
                redNum[i->getPos()] = i->getNum();
            }
        }
    }
    for (auto & i : blueList){
        if (i->checkAlive() && i->getName() == "lion"){
            if (i->getLoyalty() <= 0){
                i->checkAlive() = false;
                kill(i->getPos() , 1);
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
            march(i.get() , i->getPos() - 1 , i->getPos() , 0);// unique_ptr::get() 返回智能指针所管理的原始指针，但不转移所有权
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
            march(i.get() , i->getPos() + 1 , i->getPos() , 1);
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

struct Awolf{// 其实没用，但其实简化之后区别也不大，因为还是要写两个大if分支…………
    bool canGet;
    int wolfNum;
    int swordNum = 0;
    int bombNum = 0;
    int arrowNum = 0;
    string enemyName;
    int enemyNum;
    int cityNum;
};

void wolfGet(int time){// 可以简化！！因为wolf的抢夺没有东西交错，不像行进和狮子逃跑一样可能交错，且行进还需要考虑不覆盖问题
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
            Awolf temp;
            temp.enemyName = i->getName();
            temp.enemyNum = i->getNum();
            temp.cityNum = i->getPos();
            temp.wolfNum = blueCity[i->getPos()]->getNum();
            int oldNum = blueCity[i->getPos()]->getSword() + blueCity[i->getPos()]->getBomb()
            + blueCity[i->getPos()]->getArrow1() + blueCity[i->getPos()]->getArrow2();// blueCity[i->getPos()]就是目标蓝狼
            if (oldNum == 10) temp.canGet = false;
            else{
                if (i->getSword()){
                    temp.canGet = true;
                    if (i->getSword() + oldNum <= 10){
                        blueCity[i->getPos()]->getSword() += i->getSword();
                        temp.swordNum = i->getSword();
                        i->getSword() = 0;
                    }
                    else{
                        int cut = 0;
                        cut = 10 - oldNum;
                        blueCity[i->getPos()]->getSword() += cut;
                        i->getSword() -= cut;
                        temp.swordNum = cut;
                    }
                }
                else if (i->getBomb()){
                    temp.canGet = true;
                    if (i->getBomb() + oldNum <= 10){
                        blueCity[i->getPos()]->getBomb() += i->getBomb();
                        temp.bombNum = i->getBomb();
                        i->getBomb() = 0;
                    }
                    else{
                        int cut = 0;
                        cut = 10 - oldNum;
                        blueCity[i->getPos()]->getBomb() += cut;
                        i->getBomb() -= cut;
                        temp.bombNum = cut;
                    }
                }
                else if (i->getArrow1() || i->getArrow2()){
                    temp.canGet = true;
                    if (i->getArrow1() + oldNum >= 10){
                        int cut = 0;
                        cut = 10 - oldNum;
                        blueCity[i->getPos()]->getArrow1() += cut;
                        i->getArrow1() -= cut;
                        temp.arrowNum = cut;
                    }
                    else if (i->getArrow1() + oldNum < 10 && i->getArrow1() + i->getArrow2() + oldNum >= 10){
                        blueCity[i->getPos()]->getArrow1() += i->getArrow1();
                        temp.arrowNum += i->getArrow1();
                        int tempNum = oldNum + i->getArrow1();
                        i->getArrow1() = 0;
                        int cut = 0;
                        cut = 10 - tempNum;
                        blueCity[i->getPos()]->getArrow2() += cut;
                        i->getArrow2() -= cut;
                        temp.arrowNum += cut;
                    }
                    else{
                        blueCity[i->getPos()]->getArrow1() += i->getArrow1();
                        blueCity[i->getPos()]->getArrow2() += i->getArrow2();
                        temp.arrowNum = i->getArrow1() + i->getArrow2();
                        i->getArrow1() = 0;
                        i->getArrow2() = 0;
                    }
                }
                else temp.canGet = false;
            }
            blueAct[i->getPos()] = temp;
        }
    }
    for (auto & i : blueList){
        if (i->checkAlive() && redWolf[i->getPos()]){// 红狼抢蓝色武士，装进红狼行动
            Awolf temp;
            temp.enemyName = i->getName();
            temp.enemyNum = i->getNum();
            temp.cityNum = i->getPos();
            temp.wolfNum = redCity[i->getPos()]->getNum();
            int oldNum = redCity[i->getPos()]->getSword() + redCity[i->getPos()]->getBomb()
            + redCity[i->getPos()]->getArrow1() + redCity[i->getPos()]->getArrow2();// redCity[i->getPos()]就是目标红狼
            if (oldNum == 10) temp.canGet = false;
            else{
                if (i->getSword()){
                    temp.canGet = true;
                    if (i->getSword() + oldNum <= 10){
                        redCity[i->getPos()]->getSword() += i->getSword();
                        temp.swordNum = i->getSword();
                        i->getSword() = 0;
                    }
                    else{
                        int cut = 0;
                        cut = 10 - oldNum;
                        redCity[i->getPos()]->getSword() += cut;
                        i->getSword() -= cut;
                        temp.swordNum = cut;
                    }
                }
                else if (i->getBomb()){
                    temp.canGet = true;
                    if (i->getBomb() + oldNum <= 10){
                        redCity[i->getPos()]->getBomb() += i->getBomb();
                        temp.bombNum = i->getBomb();
                        i->getBomb() = 0;
                    }
                    else{
                        int cut = 0;
                        cut = 10 - oldNum;
                        redCity[i->getPos()]->getBomb() += cut;
                        i->getBomb() -= cut;
                        temp.bombNum = cut;
                    }
                }
                else if (i->getArrow1() || i->getArrow2()){
                    temp.canGet = true;
                    if (i->getArrow1() + oldNum >= 10){
                        int cut = 0;
                        cut = 10 - oldNum;
                        redCity[i->getPos()]->getArrow1() += cut;
                        i->getArrow1() -= cut;
                        temp.arrowNum = cut;
                    }
                    else if (i->getArrow1() + oldNum < 10 && i->getArrow1() + i->getArrow2() + oldNum >= 10){
                        redCity[i->getPos()]->getArrow1() += i->getArrow1();
                        temp.arrowNum += i->getArrow1();
                        int tempNum = oldNum + i->getArrow1();
                        i->getArrow1() = 0;
                        int cut = 0;
                        cut = 10 - tempNum;
                        redCity[i->getPos()]->getArrow2() += cut;
                        i->getArrow2() -= cut;
                        temp.arrowNum += cut;
                    }
                    else{
                        redCity[i->getPos()]->getArrow1() += i->getArrow1();
                        redCity[i->getPos()]->getArrow2() += i->getArrow2();
                        temp.arrowNum = i->getArrow1() + i->getArrow2();
                        i->getArrow1() = 0;
                        i->getArrow2() = 0;
                    }
                }
                else temp.canGet = false;
            }
            redAct[i->getPos()] = temp;
        }
    }

    for (int i = 0 ; i < cityNum + 2 ; i ++){
        if (redWolf[i] && redAct[i].canGet){
            cout << setw(3) << setfill('0') << hour << ":35 red wolf " << redAct[i].wolfNum << " took ";
            if (redAct[i].swordNum) cout << redAct[i].swordNum << " sword from blue ";
            else if (redAct[i].bombNum) cout << redAct[i].bombNum << " bomb from blue ";
            else cout << redAct[i].arrowNum << " arrow from blue ";
            cout << redAct[i].enemyName << " " << redAct[i].enemyNum << " in city " << redAct[i].cityNum << endl;
        }
        if (blueWolf[i] && blueAct[i].canGet){
            cout << setw(3) << setfill('0') << hour << ":35 blue wolf " << blueAct[i].wolfNum << " took ";
            if (blueAct[i].swordNum) cout << blueAct[i].swordNum << " sword from red ";
            else if (blueAct[i].bombNum) cout << blueAct[i].bombNum << " bomb from red ";
            else cout << blueAct[i].arrowNum << " arrow from red ";
            cout << blueAct[i].enemyName << " " << blueAct[i].enemyNum << " in city " << blueAct[i].cityNum << endl;
        }
    }
}

void weaponGet(Warrior* win, Warrior* lose) {
    int winTotal = win->getSword() + win->getBomb() + win->getArrow1() + win->getArrow2();
    if (winTotal == 10) return;
    int cap = 10 - winTotal;

    int swordCnt = lose->getSword();
    if (swordCnt > 0) {
        int take = min(swordCnt, cap);
        win->getSword() += take;
        lose->getSword() -= take;
        cap -= take;
        if (cap == 0) return;
    }

    int bombCnt = lose->getBomb();
    if (bombCnt > 0) {
        int take = min(bombCnt, cap);
        win->getBomb() += take;
        lose->getBomb() -= take;
        cap -= take;
        if (cap == 0) return;
    }

    int arrow1Cnt = lose->getArrow1();
    int arrow2Cnt = lose->getArrow2();
    if (arrow1Cnt > 0 || arrow2Cnt > 0) {
        int take1 = min(arrow1Cnt, cap);
        if (take1 > 0) {
            win->getArrow1() += take1;
            lose->getArrow1() -= take1;
            cap -= take1;
        }
        if (cap > 0 && arrow2Cnt > 0) {
            int take2 = min(arrow2Cnt, cap);
            win->getArrow2() += take2;
            lose->getArrow2() -= take2;
        }
    }
}

void weaponUse(Warrior * attack , Warrior * passive , int & round){
    if (round >= attack->totalWeapon()) round = 0;
    
    if (round < attack->getSword()){
        passive->changeHP() -= attack->getATK() * 2 / 10;
    }
    else if (round < attack->getSword() + attack->getBomb()){
        round --;
        attack->getBomb() --;
        int cut1 = attack->getATK() * 4 / 10;
        int cut2 = cut1 * 5 / 10;
        passive->changeHP() -= cut1;
        if (attack->getName() != "ninja") attack->changeHP() -= cut2;
    }
    else if (round < attack->getSword() + attack->getBomb() + attack->getArrow2()){
        round --;
        attack->getArrow2() --;
        passive->changeHP() -= attack->getATK() * 3 / 10;
    }
    else if (round < attack->getSword() + attack->getBomb() + attack->getArrow2() + attack->getArrow1()){
        round --;
        attack->getArrow1() --;
        attack->getArrow3() ++;
        passive->changeHP() -= attack->getATK() * 3 / 10;
    }
    else{
        round --;
        attack->getArrow3() --;
        passive->changeHP() -= attack->getATK() * 3 / 10;
    }

    if (attack->getHP() <= 0) attack->checkAlive() = false;
    if (passive->getHP() <= 0) passive->checkAlive() = false;
}

void singleWar(Warrior * first , Warrior * second , int city) {
    int Fround = 0, Sround = 0;
    while (first->checkAlive() && second->checkAlive()) {
        bool canFirstChange = (first->getBomb() > 0) || (first->getArrow1() > 0) || (first->getArrow3() > 0) ||
                              (first->getArrow2() > 0) || (first->getSword() > 0 && first->getATK() * 2 / 10 > 0);
        bool canSecondChange = (second->getBomb() > 0) || (second->getArrow1() > 0) || (second->getArrow3() > 0) ||
                               (second->getArrow2() > 0) || (second->getSword() > 0 && second->getATK() * 2 / 10 > 0);
        if (!canFirstChange && !canSecondChange) break;

        if (first->totalWeapon() > 0) {
            weaponUse(first , second , Fround);
            if (first->totalWeapon() != 0) Fround = (Fround + 1) % first->totalWeapon();
        }
        if (!first->checkAlive() || !second->checkAlive()) break;
        if (second->totalWeapon() > 0) {
            weaponUse(second , first , Sround);
            if (second->totalWeapon() != 0) Sround = (Sround + 1) % second->totalWeapon();
        }
    }

    first->getArrow2() += first->getArrow3();
    first->getArrow3() = 0;
    second->getArrow2() += second->getArrow3();
    second->getArrow3() = 0;
}

void decideWar(Warrior * red , Warrior * blue , int city , int hour){
    Warrior * first = nullptr;
    Warrior * second = nullptr;

    if (city % 2 == 0){        
        first = blue;
        second = red;  
        singleWar(first , second , city);
    }
    else{
        first = red;
        second = blue;
        singleWar(first , second , city);
    }

    if (!red->checkAlive() && !blue->checkAlive()) cout << setw(3) << setfill('0') << hour << ":40 both red "
    << red->getName() << " " << red->getNum() << " and blue " << blue->getName() << " " << blue->getNum() <<
    " died in city " << city << endl;

    else if (red->checkAlive() && blue->checkAlive()){
        cout << setw(3) << setfill('0') << hour << ":40 both red "
        << red->getName() << " " << red->getNum() << " and blue " << blue->getName() << " " << blue->getNum() <<
        " were alive in city " << city << endl;
        if (red->getName() == "dragon") cout << setw(3) << setfill('0') << hour << ":40 red dragon "
        << red->getNum() << " yelled in city " << city << endl;
        if (blue->getName() == "dragon") cout << setw(3) << setfill('0') << hour << ":40 blue dragon "
        << blue->getNum() << " yelled in city " << city << endl;
    }

    else if (red->checkAlive() && !blue->checkAlive()){
        cout << setw(3) << setfill('0') << hour << ":40 red " << red->getName() << " " << red->getNum()
        << " killed blue " << blue->getName() << " " << blue->getNum() << " in city " << city << " remaining "
        << red->getHP() << " elements" << endl;
        if (red->getName() == "dragon") cout << setw(3) << setfill('0') << hour << ":40 red dragon "
        << red->getNum() << " yelled in city " << city << endl;
        weaponGet(red , blue);
    }

    else{
        cout << setw(3) << setfill('0') << hour << ":40 blue " << blue->getName() << " " << blue->getNum()
        << " killed red " << red->getName() << " " << red->getNum() << " in city " << city << " remaining "
        << blue->getHP() << " elements" << endl;
        if (blue->getName() == "dragon") cout << setw(3) << setfill('0') << hour << ":40 blue dragon "
        << blue->getNum() << " yelled in city " << city << endl;
        weaponGet(blue , red);
    }

    if (!red->checkAlive()) kill(city , 0);
    if (!blue->checkAlive()) kill(city , 1);
}

void beginWars(int time){// 包含dragon的欢呼，ninja使用bomb不会让自己受伤
    int hour = time / 60;
    for (int i = 0 ; i < cityNum + 2; i ++){// 战斗和狼抢夺这两个事件没有东西交错的问题，只需要扫一遍城市就好了！！！
        if (redCity[i] && blueCity[i]) decideWar(redCity[i] , blueCity[i] , i , hour);
    }
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
            temp.arrowNum = i->getArrow1() + i->getArrow2();
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
            temp.arrowNum = i->getArrow1() + i->getArrow2();
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
        cout << "Case " << i << ":" << endl;// ???????
        int totalHP = 0;
        int timeLimit = 0;
        cin >> totalHP >> cityNum >> lionCut >> timeLimit;
        redCity.assign(cityNum + 2 , nullptr);
        blueCity.assign(cityNum + 2 , nullptr);
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