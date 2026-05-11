// 本程序有三种类
// 第一种是全局变量中定义的基类，用于记录每一种武士的基本情况：HP、ATK、name，并且提供相关基类函数
// 第二种是全局变量智能指针数组，需要后续加入元素的派生类，数组里面装的是具体的武士个体对象，注意指针的调用格式
// 第三种是武器类，一个类就包含了三种武器
// 还有全局变量冗余指针数组，用于提供对于武士的O(1)复杂度访问以及便捷修改
// 还有维护了城市结构体的数组，用以记录插旗情况和城市生命元情况
// 本程序中基类小写首字母，派生类大写首字母
// 关于本代码中冗余指针数组和智能指针数组的配合：【【智能指针容器负责生命周期和全局遍历，冗余指针数组负责按城市快速访问】】。
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

int cityNum = 0;// 城市数量
int lionCut = 0;// 狮子降低忠诚度
int R = 0;// 弓箭伤害
int totalRed = 0;// 红方武士总数
int totalBlue = 0;// 蓝方武士总数
int redInBlueHQ = 0;// 红方武士在蓝司令部的人数
int blueInRedHQ = 0;// 蓝方武士在红司令部的人数
int RHP = 0;// 红生命元
int BHP = 0;// 蓝生命元

class Weapon {
public:
    enum Type { SWORD, BOMB, ARROW };// 枚举类型，BOMB 无需额外数据
    Type type;
    int attack;
    int left;// arrow剩余次数
    Weapon(int swordAtk) : type(SWORD), attack(swordAtk), left(0) {}
    Weapon(Type t, int arrowR = 0) : type(t), attack(0), left(0) {if (t == ARROW) left = 3;}// 可用3次
    void blunt() {attack = attack * 4 / 5;}// sword变钝
    void useArrow() { if (left > 0) left--; }
    bool broken() const {return (type == SWORD && attack == 0) || (type == ARROW && left == 0);}
};

struct City {
    int elements = 0;// 城市积攒的生命元
    int flag = 0;// 0无旗, 1红方旗, 2蓝方旗
    int lastKiller = 0;// 上一场杀死敌人的方（0无,1红,2蓝）
    int streak = 0;// 当前连续杀敌次数（同一方）
};

// 基类，存储武士基本信息
class Warrior {
private:
    int HP;
    string name;
    int ATK;
protected:
    vector<Weapon> weapons;
public:
    Warrior() {}
    Warrior(int n, int a, string x) : HP(n), ATK(a), name(x) {}
    void setInfo(int n, int a, string x) { HP = n; ATK = a; name = x; }
    int getHP() const { return HP; }
    int getATK() const { return ATK; }
    string getName() const { return name; }
    int & changeHP() { return HP; }
    int & changeATK() { return ATK; }

    // 武器相关虚函数（基类默认无武器）
    virtual bool hasSword() const { return false; }
    virtual int  swordAttack() const { return 0; }
    virtual void bluntSword() {}
    virtual bool hasBomb() const { return false; }
    virtual void removeBomb() {}
    virtual bool hasArrow() const { return false; }
    virtual int  arrowLeft() const { return 0; }
    virtual void useArrow() {}
    virtual bool addWeapon(const Weapon& w) { return false; }
    virtual const vector<Weapon>& getWeapons() const { return weapons; }
    int totalWeapon() const { return weapons.size(); }

    // 其他虚函数，注意默认实现
    virtual bool & checkAlive() { static bool x = false; return x; }
    virtual int & getPos() { static int x = 0; return x; }
    virtual int getNum() { return 0; }
    virtual void move() {}

    // lion和dragon特有属性
    virtual int & getLoyalty() { static int x = 0; return x; }
    virtual double getMorale() { return 0.0; }
    virtual void changeMorale(double) {}
};

// 下为五个派生类，用于生成五种具体的武士，注意区分基类和派生类对象的【含义&作用】之区别
class Dragon : public Warrior {
private:
    int caseNum;
    int pos;
    bool alive;
    double morale;

    bool ownsWeapon(Weapon::Type t) const {// 判断是否拥有某类武器
        for (const auto& w : weapons)
            if (w.type == t) return true;
        return false;
    }
public:
    Dragon(int hp, string type, int num, int atk, int p, double mor): Warrior(hp, atk, type), caseNum(num), pos(p), alive(true), morale(mor){
        int idx = caseNum % 3;
        if (idx == 0) {
            int swAtk = getATK() * 2 / 10;
            if (swAtk > 0) weapons.push_back(Weapon(swAtk));
        } 
        else if (idx == 1) weapons.push_back(Weapon(Weapon::BOMB));
        else weapons.push_back(Weapon(Weapon::ARROW, 3));
    }

    bool & checkAlive() override { return alive; }
    int & getPos() override { return pos; }
    int getNum() override { return caseNum; }
    double getMorale() override { return morale; }
    void changeMorale(double diff) override { morale += diff; }
    bool hasSword() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return true;
        return false;
    }
    int swordAttack() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return w.attack;
        return 0;
    }
    void bluntSword() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::SWORD) {
                w.blunt();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::SWORD && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool hasBomb() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::BOMB) return true;
        return false;
    }
    void removeBomb() override {
        weapons.erase(remove_if(weapons.begin(), weapons.end(),
            [](const Weapon& wp){ return wp.type == Weapon::BOMB; }), weapons.end());
    }
    bool hasArrow() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return true;
        return false;
    }
    int arrowLeft() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return w.left;
        return 0;
    }
    void useArrow() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::ARROW) {
                w.useArrow();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::ARROW && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool addWeapon(const Weapon& w) override {
        if (ownsWeapon(w.type)) return false;
        if (weapons.size() >= 10) return false;
        weapons.push_back(w);
        return true;
    }
};

class Ninja : public Warrior {
private:
    int caseNum;
    int pos;
    bool alive;

    bool ownsWeapon(Weapon::Type t) const {
        for (const auto& w : weapons)
            if (w.type == t) return true;
        return false;
    }

    void addWeaponByIndex(int idx) {
        if (idx == 0) {
            int swAtk = getATK() * 2 / 10;
            if (swAtk > 0) weapons.push_back(Weapon(swAtk));
        } else if (idx == 1) {
            weapons.push_back(Weapon(Weapon::BOMB));
        } else {
            weapons.push_back(Weapon(Weapon::ARROW, 3));
        }
    }
public:
    Ninja(int hp, string type, int num, int atk, int p): Warrior(hp, atk, type), caseNum(num), pos(p), alive(true){
        addWeaponByIndex(caseNum % 3);
        addWeaponByIndex((caseNum + 1) % 3);
    }

    bool & checkAlive() override { return alive; }
    int & getPos() override { return pos; }
    int getNum() override { return caseNum; }
    bool hasSword() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return true;
        return false;
    }
    int swordAttack() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return w.attack;
        return 0;
    }
    void bluntSword() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::SWORD) {
                w.blunt();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::SWORD && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool hasBomb() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::BOMB) return true;
        return false;
    }
    void removeBomb() override {
        weapons.erase(remove_if(weapons.begin(), weapons.end(),
            [](const Weapon& wp){ return wp.type == Weapon::BOMB; }), weapons.end());
    }
    bool hasArrow() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return true;
        return false;
    }
    int arrowLeft() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return w.left;
        return 0;
    }
    void useArrow() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::ARROW) {
                w.useArrow();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::ARROW && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool addWeapon(const Weapon& w) override {
        if (ownsWeapon(w.type)) return false;
        if (weapons.size() >= 10) return false;
        weapons.push_back(w);
        return true;
    }
};

class Iceman : public Warrior {
private:
    int caseNum;
    int pos;
    int stepCount;
    bool alive;

    bool ownsWeapon(Weapon::Type t) const {
        for (const auto& w : weapons)
            if (w.type == t) return true;
        return false;
    }
public:
    Iceman(int hp, string type, int num, int atk, int p): Warrior(hp, atk, type), caseNum(num), pos(p), stepCount(0), alive(true){
        int idx = caseNum % 3;
        if (idx == 0) {
            int swAtk = getATK() * 2 / 10;
            if (swAtk > 0) weapons.push_back(Weapon(swAtk));
        } else if (idx == 1) {
            weapons.push_back(Weapon(Weapon::BOMB));
        } else {
            weapons.push_back(Weapon(Weapon::ARROW, 3));
        }
    }

    bool & checkAlive() override { return alive; }
    int & getPos() override { return pos; }
    int getNum() override { return caseNum; }
    void move() override {
        stepCount++;
        if (stepCount % 2 == 0) {
            int hp = getHP();
            if (hp > 9) changeHP() = hp - 9;
            else changeHP() = 1;
            changeATK() += 20;
        }
    }
    bool hasSword() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return true;
        return false;
    }
    int swordAttack() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return w.attack;
        return 0;
    }
    void bluntSword() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::SWORD) {
                w.blunt();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::SWORD && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool hasBomb() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::BOMB) return true;
        return false;
    }
    void removeBomb() override {
        weapons.erase(remove_if(weapons.begin(), weapons.end(),
            [](const Weapon& wp){ return wp.type == Weapon::BOMB; }), weapons.end());
    }
    bool hasArrow() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return true;
        return false;
    }
    int arrowLeft() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return w.left;
        return 0;
    }
    void useArrow() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::ARROW) {
                w.useArrow();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::ARROW && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool addWeapon(const Weapon& w) override {
        if (ownsWeapon(w.type)) return false;
        if (weapons.size() >= 10) return false;
        weapons.push_back(w);
        return true;
    }
};

class Lion : public Warrior {
private:
    int caseNum;
    int pos;
    int loyalty;
    bool alive;

    bool ownsWeapon(Weapon::Type t) const {
        for (const auto& w : weapons)
            if (w.type == t) return true;
        return false;
    }
public:
    Lion(int hp, string type, int HPleft, int num, int atk, int p): Warrior(hp, atk, type), caseNum(num), pos(p), loyalty(HPleft), alive(true){}

    bool & checkAlive() override { return alive; }
    int & getPos() override { return pos; }
    int getNum() override { return caseNum; }
    int & getLoyalty() override { return loyalty; }
    bool hasSword() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return true;
        return false;
    }
    int swordAttack() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return w.attack;
        return 0;
    }
    void bluntSword() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::SWORD) {
                w.blunt();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::SWORD && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool hasBomb() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::BOMB) return true;
        return false;
    }
    void removeBomb() override {
        weapons.erase(remove_if(weapons.begin(), weapons.end(),
            [](const Weapon& wp){ return wp.type == Weapon::BOMB; }), weapons.end());
    }
    bool hasArrow() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return true;
        return false;
    }
    int arrowLeft() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return w.left;
        return 0;
    }
    void useArrow() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::ARROW) {
                w.useArrow();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::ARROW && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool addWeapon(const Weapon& w) override {
        if (ownsWeapon(w.type)) return false;
        if (weapons.size() >= 10) return false;
        weapons.push_back(w);
        return true;
    }
};

class Wolf : public Warrior {
private:
    int caseNum;
    int pos;
    bool alive;

    bool ownsWeapon(Weapon::Type t) const {
        for (const auto& w : weapons)
            if (w.type == t) return true;
        return false;
    }
public:
    Wolf(int hp, string type, int num, int atk, int p)
        : Warrior(hp, atk, type), caseNum(num), pos(p), alive(true){}

    bool & checkAlive() override { return alive; }
    int & getPos() override { return pos; }
    int getNum() override { return caseNum; }
    bool hasSword() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return true;
        return false;
    }
    int swordAttack() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::SWORD) return w.attack;
        return 0;
    }
    void bluntSword() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::SWORD) {
                w.blunt();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::SWORD && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool hasBomb() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::BOMB) return true;
        return false;
    }
    void removeBomb() override {
        weapons.erase(remove_if(weapons.begin(), weapons.end(),
            [](const Weapon& wp){ return wp.type == Weapon::BOMB; }), weapons.end());
    }
    bool hasArrow() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return true;
        return false;
    }
    int arrowLeft() const override {
        for (const auto& w : weapons)
            if (w.type == Weapon::ARROW) return w.left;
        return 0;
    }
    void useArrow() override {
        for (auto& w : weapons) {
            if (w.type == Weapon::ARROW) {
                w.useArrow();
                if (w.broken()) {
                    weapons.erase(remove_if(weapons.begin(), weapons.end(),
                        [](const Weapon& wp){ return wp.type == Weapon::ARROW && wp.broken(); }),
                        weapons.end());
                }
                return;
            }
        }
    }
    bool addWeapon(const Weapon& w) override {
        if (ownsWeapon(w.type)) return false;
        if (weapons.size() >= 10) return false;
        weapons.push_back(w);
        return true;
    }
};

Warrior dragon , ninja , iceman , lion , wolf;// 基类下的五个对象，存储五种武士的基本信息
vector<unique_ptr<Warrior>> redList;// 智能指针数组，管理两方所有武士信息，注意调用问题和多态问题
vector<unique_ptr<Warrior>> blueList;
vector<Warrior*> redCity;// 冗余数组————原始指针：便于O(1)访问某个城市的武士
vector<Warrior*> blueCity;
vector<City> cities;
bool fin = false;// 司令部结束判据

void kill(int pos, int color) {
    if (color == 0) redCity[pos] = nullptr;
    else blueCity[pos] = nullptr;
}

void march(Warrior * x , int oldPos , int newPos , int color){// 不会发生覆盖！！因为auto的遍历是从左到右的，最开始遍历的武士在最远点
    if (color == 0) redCity[oldPos] = nullptr;
    else blueCity[oldPos] = nullptr;

    if (color == 0) redCity[newPos] = x;
    else blueCity[newPos] = x;
}

void warriorBorn(int &HP , int totaltime , int &round , vector<Warrior> order , int color) {
    int time = totaltime / 60;
    string side = (color == 0 ? "red" : "blue");
    if (HP < order[round].getHP()) return;// 生命元不足，什么都不做，等待下一个整点
    if (color == 0) totalRed ++;
    else totalBlue ++;
    cout << setw(3) << setfill('0') << time << ":00 " << side << " " << order[round].getName() << " " 
         << (color == 0 ? totalRed : totalBlue) << " born" << endl;
    HP -= order[round].getHP();

    string tmpstr = order[round].getName();
    if (tmpstr == "dragon") {
        double morale = (double)HP / order[round].getHP();
        cout << "Its morale is " << fixed << setprecision(2) << morale << endl;// 输出士气
        if (color == 0) redList.push_back(make_unique<Dragon>(order[round].getHP(), "dragon",totalRed, order[round].getATK(), 0, morale));
        else blueList.push_back(make_unique<Dragon>(order[round].getHP(), "dragon", totalBlue, order[round].getATK(), cityNum + 1, morale));
    }
    else if (tmpstr == "ninja") {
        if (color == 0) redList.push_back(make_unique<Ninja>(order[round].getHP(), "ninja", totalRed, order[round].getATK(), 0));
        else blueList.push_back(make_unique<Ninja>(order[round].getHP(), "ninja", totalBlue, order[round].getATK(), cityNum + 1));
    }
    else if (tmpstr == "iceman") {
        if (color == 0) redList.push_back(make_unique<Iceman>(order[round].getHP(), "iceman", totalRed, order[round].getATK(), 0));
        else blueList.push_back(make_unique<Iceman>(order[round].getHP(), "iceman", totalBlue, order[round].getATK(), cityNum + 1));
    }
    else if (tmpstr == "lion") {
        cout << "Its loyalty is " << HP << endl;
        if (color == 0) redList.push_back(make_unique<Lion>(order[round].getHP(), "lion", HP, totalRed, order[round].getATK(), 0));
        else blueList.push_back(make_unique<Lion>(order[round].getHP(), "lion", HP, totalBlue, order[round].getATK(), cityNum + 1));
    }
    else if (tmpstr == "wolf") {
        if (color == 0) redList.push_back(make_unique<Wolf>(order[round].getHP(), "wolf", totalRed, order[round].getATK(), 0));
        else blueList.push_back(make_unique<Wolf>(order[round].getHP(), "wolf", totalBlue, order[round].getATK(), cityNum + 1));
    }
    
    if (color == 0) redCity[0] = redList.back().get();// 更新城市指针
    else blueCity[cityNum + 1] = blueList.back().get();
    round = (round + 1) % 5;// 成功制造后才推进到下一类武士
}

void lionEscape(int time){
    int hour = time / 60;
    vector<int> redEscape(cityNum + 2, 0);
    vector<int> redNum(cityNum + 2, 0);
    vector<int> blueEscape(cityNum + 2, 0);
    vector<int> blueNum(cityNum + 2, 0);

    for (auto & i : redList){
        if (i->checkAlive() && i->getName() == "lion"){
            if (i->getPos() == cityNum + 1) continue;// 已到蓝司令部，不逃跑
            if (i->getLoyalty() <= 0){
                i->checkAlive() = false;
                kill(i->getPos() , 0);
                redEscape[i->getPos()] = 1;
                redNum[i->getPos()] = i->getNum();
            }
        }
    }
    for (auto & i : blueList){
        if (i->checkAlive() && i->getName() == "lion"){
            if (i->getPos() == 0) continue;// 已到红司令部，不逃跑
            if (i->getLoyalty() <= 0){
                i->checkAlive() = false;
                kill(i->getPos() , 1);
                blueEscape[i->getPos()] = 1;
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

void warriorMarch(int time) {
    int hour = time / 60;
    vector<int> redCheck(cityNum + 2, 0);
    vector<Amove> redMove(cityNum + 2);
    vector<int> blueCheck(cityNum + 2, 0);
    vector<Amove> blueMove(cityNum + 2);

    // 红方前进
    for (auto & i : redList) {
        if (!i->checkAlive()) continue;
        if (i->getPos() == cityNum + 1) continue;// 已到达蓝司令部，不再移动

        i->getPos() += 1;
        if (i->getPos() == cityNum + 1) { redInBlueHQ++; }// 刚好到达蓝司令部
        i->move();// iceman 步数变化等
        redCheck[i->getPos()] = 1;
        march(i.get(), i->getPos() - 1, i->getPos(), 0);
        Amove temp;
        temp.name = i->getName();
        temp.num = i->getNum();
        temp.targetCity = i->getPos();
        temp.tempHP = i->getHP();
        temp.tempATK = i->getATK();
        redMove[i->getPos()] = temp;
    }

    // 蓝方前进
    for (auto & i : blueList) {
        if (!i->checkAlive()) continue;
        if (i->getPos() == 0) continue;// 已到达红司令部，不再移动

        i->getPos() -= 1;
        if (i->getPos() == 0) { blueInRedHQ++; }// 刚好到达红司令部
        i->move();
        blueCheck[i->getPos()] = 1;
        march(i.get(), i->getPos() + 1, i->getPos(), 1);
        Amove temp;
        temp.name = i->getName();
        temp.num = i->getNum();
        temp.targetCity = i->getPos();
        temp.tempHP = i->getHP();
        temp.tempATK = i->getATK();
        blueMove[i->getPos()] = temp;
    }

    // 输出事件，遵守题目顺序
    if (blueCheck[0]) {
        cout << setw(3) << setfill('0') << hour << ":10 blue " << blueMove[0].name
             << " " << blueMove[0].num << " reached red headquarter with "
             << blueMove[0].tempHP << " elements and force " << blueMove[0].tempATK << endl;
        if (blueInRedHQ >= 2) {
            cout << setw(3) << setfill('0') << hour << ":10 red headquarter was taken" << endl;
            fin = true;
        }
    }
    for (int i = 1; i < cityNum + 1; ++i) {
        if (redCheck[i])
            cout << setw(3) << setfill('0') << hour << ":10 red " << redMove[i].name
                 << " " << redMove[i].num << " marched to city " << redMove[i].targetCity
                 << " with " << redMove[i].tempHP << " elements and force "
                 << redMove[i].tempATK << endl;
        if (blueCheck[i])
            cout << setw(3) << setfill('0') << hour << ":10 blue " << blueMove[i].name
                 << " " << blueMove[i].num << " marched to city " << blueMove[i].targetCity
                 << " with " << blueMove[i].tempHP << " elements and force "
                 << blueMove[i].tempATK << endl;
    }
    if (redCheck[cityNum + 1]) {
        cout << setw(3) << setfill('0') << hour << ":10 red " << redMove[cityNum + 1].name
             << " " << redMove[cityNum + 1].num << " reached blue headquarter with "
             << redMove[cityNum + 1].tempHP << " elements and force "
             << redMove[cityNum + 1].tempATK << endl;
        if (redInBlueHQ >= 2) {
            cout << setw(3) << setfill('0') << hour << ":10 blue headquarter was taken" << endl;
            fin = true;
        }
    }
}

void createHP(int time) {
    for (int i = 1; i <= cityNum; ++i) {
        cities[i].elements += 10;
    }
}

void collectHP(int time) {
    int hour = time / 60;
    for (int i = 1; i <= cityNum; ++i) {
        if (redCity[i] && !blueCity[i]) {
            if (cities[i].elements > 0) {
                RHP += cities[i].elements;
                cout << setw(3) << setfill('0') << hour << ":30 red "
                     << redCity[i]->getName() << " " << redCity[i]->getNum()
                     << " earned " << cities[i].elements
                     << " elements for his headquarter" << endl;
                cities[i].elements = 0;
            }
        } else if (blueCity[i] && !redCity[i]) {
            if (cities[i].elements > 0) {
                BHP += cities[i].elements;
                cout << setw(3) << setfill('0') << hour << ":30 blue "
                     << blueCity[i]->getName() << " " << blueCity[i]->getNum()
                     << " earned " << cities[i].elements
                     << " elements for his headquarter" << endl;
                cities[i].elements = 0;
            }
        }
    }
}

void shootArrow(int time) {
    int hour = time / 60;

    // 存放所有射箭事件的信息，用于按城市顺序输出
    struct ShootEvent {
        int pos;// 射箭武士所在城市
        string side;// 红蓝阵营
        string name;
        int num;
        bool killed;// 是否射杀敌人
        string enemySide;
        string enemyName;
        int enemyNum;
    };
    vector<ShootEvent> events;

    // 检查红方武士
    for (auto& i : redList) {
        if (!i->checkAlive() || !i->hasArrow()) continue;
        int cur = i->getPos();
        int next = cur + 1;
        // 排除不射箭的情况
        if (next > cityNum) continue;// 不能射司令部
        if (!blueCity[next]) continue;// 下一城市无蓝方武士
        Warrior* enemy = blueCity[next];
        if (!enemy->checkAlive()) continue;// 敌人已死
        i->useArrow();// 射箭
        enemy->changeHP() -= R;

        ShootEvent ev;// 事件记录结构体
        ev.pos = cur;
        ev.side = "red";
        ev.name = i->getName();
        ev.num = i->getNum();

        if (enemy->getHP() <= 0) {// 死亡判断
            ev.killed = true;
            ev.enemySide = "blue";
            ev.enemyName = enemy->getName();
            ev.enemyNum = enemy->getNum();
        } 
        else ev.killed = false;
        events.push_back(ev);
    }

    // 检查蓝方武士
    for (auto& i : blueList) {
        if (!i->checkAlive() || !i->hasArrow()) continue;
        int cur = i->getPos();
        int next = cur - 1;
        if (next < 1) continue;// 不能射司令部
        if (!redCity[next]) continue;
        Warrior* enemy = redCity[next];
        if (!enemy->checkAlive()) continue;

        i->useArrow();
        enemy->changeHP() -= R;
        ShootEvent ev;// 事件记录结构体建立
        ev.pos = cur;
        ev.side = "blue";
        ev.name = i->getName();
        ev.num = i->getNum();

        if (enemy->getHP() <= 0) {
            ev.killed = true;
            ev.enemySide = "red";
            ev.enemyName = enemy->getName();
            ev.enemyNum = enemy->getNum();
        } 
        else ev.killed = false;
        events.push_back(ev);
    }

    // 按顺序排列输出事件，使用lambda简化排序输出
    sort(events.begin(), events.end(), [](const ShootEvent& a, const ShootEvent& b) {
            if (a.pos != b.pos) return a.pos < b.pos;// 同城市按红先蓝后
            if (a.side != b.side) return a.side == "red"; 
            return false; // 同城同色不会发生，若发生则保持原序
        });

    // 输出
    for (const auto& e : events) {
        cout << setw(3) << setfill('0') << hour << ":35 " << e.side << " " << e.name << " " << e.num;
        if (e.killed) cout << " shot and killed " << e.enemySide << " " << e.enemyName << " " << e.enemyNum;
        else cout << " shot";
        cout << endl;
    }
}

bool willDie(Warrior* self, Warrior* enemy, int cityId, int selfColor) {
    // 判断武士在城市即将发生的战斗中是否会死亡
    // selfColor: 0红方, 1蓝方
    // 确定先手方
    bool redFirst = false;
    if (cities[cityId].flag == 1) redFirst = true;
    else if (cities[cityId].flag == 2) redFirst = false;
    else redFirst = (cityId % 2 == 1);   // 奇数无旗城市红先
    bool selfIsRed = (selfColor == 0);
    bool selfFirst = (selfIsRed == redFirst);
    int selfHP = self->getHP();
    int enemyHP = enemy->getHP();
    int selfSword = self->hasSword() ? self->swordAttack() : 0;
    int enemySword = enemy->hasSword() ? enemy->swordAttack() : 0;

    if (selfFirst) {// self 先手攻击
        int damage = self->getATK() + selfSword;
        enemyHP -= damage;
        if (enemyHP > 0) {
            if (enemy->getName() != "ninja") {// 敌人未死且不是 Ninja 则反击
                int counterDamage = enemy->getATK() / 2 + enemySword;
                selfHP -= counterDamage;
            }
        }
    } 
    else {// enemy 先手攻击
        int damage = enemy->getATK() + enemySword;
        selfHP -= damage;
        if (selfHP > 0) {
            if (self->getName() != "ninja") {// self 未死且不是 Ninja 则反击
                int counterDamage = self->getATK() / 2 + selfSword;
                enemyHP -= counterDamage;
            }
        }
    }

    return selfHP <= 0;
}

void useBomb(int time) {
    int hour = time / 60;
    struct BombEvent {// 存放炸弹事件
        int city;
        string side;
        string name;
        int num;
        string enemySide;
        string enemyName;
        int enemyNum;
    };
    vector<BombEvent> events;

    for (int i = 1; i <= cityNum; ++i) {
        Warrior* red = redCity[i];
        Warrior* blue = blueCity[i];
        if (!red || !blue) continue;
        if (!red->checkAlive() || !blue->checkAlive()) continue;
        if (red->getHP() <= 0 || blue->getHP() <= 0) continue;
        bool redBomb = false;
        bool blueBomb = false;

        if (red->hasBomb()) {// 红方判断
            if (willDie(red, blue, i, 0)) {
                redBomb = true;
                red->removeBomb();   // 使用炸弹后移除
            }
        }
        if (blue->hasBomb()) {// 蓝方判断
            if (willDie(blue, red, i, 1)) {
                blueBomb = true;
                blue->removeBomb();
            }
        }
        if (redBomb || blueBomb) {// 若有任何一方使用炸弹，双方同归于尽
            red->checkAlive() = false;
            blue->checkAlive() = false;
            kill(i, 0);
            kill(i, 1);
            // 记录事件（先红后蓝）
            if (redBomb) events.push_back({i, "red", red->getName(), red->getNum(), "blue", blue->getName(), blue->getNum()});
            if (blueBomb) events.push_back({i, "blue", blue->getName(), blue->getNum(), "red", red->getName(), red->getNum()});
        }
    }

    sort(events.begin(), events.end(), [](const BombEvent& a, const BombEvent& b) {// 排序
            if (a.city != b.city) return a.city < b.city;
            if (a.side == "red" && b.side == "blue") return true;
            return false;
        });
    for (const auto& e : events) {// 输出
        cout << setw(3) << setfill('0') << hour << ":38 " << e.side << " " << e.name << " " << e.num
             << " used a bomb and killed " << e.enemySide << " " << e.enemyName << " " << e.enemyNum << endl;
    }
}

void beginBattle(int time , int num) {
    int hour = time / 60;
    enum EventType { ATTACK = 6, FIGHTBACK = 7, KILLED = 8, YELL = 9, EARN = 10, FLAG = 11 };
    struct Event {// 事件结构体
        int city;
        EventType type;
        string msg;
    };
    vector<Event> events;
    struct Victor {// 胜者结构体
        int city;
        int color; // 0红,1蓝
        Warrior* warrior;
    };
    vector<Victor> victors;

    for (int i = 1; i <= cityNum; ++i) {
        Warrior* red = redCity[i];
        Warrior* blue = blueCity[i];
        // 清理：城市里只有一个人，但在35分被箭射死
        if (red && !blue && red->getHP() <= 0) {
            red->checkAlive() = false; kill(i, 0); continue;
        }
        if (!red && blue && blue->getHP() <= 0) {
            blue->checkAlive() = false; kill(i, 1); continue;
        }
        if (!red || !blue) continue;

        // 两人都在，检查是否有人在35分被箭射死
        bool redAliveAtStart = red->getHP() > 0;
        bool blueAliveAtStart = blue->getHP() > 0;
        // 双死，没有赢家
        if (!redAliveAtStart && !blueAliveAtStart) {
            red->checkAlive() = false; kill(i, 0);
            blue->checkAlive() = false; kill(i, 1);
            cities[i].streak = 0; // 连胜中断
            continue;
        }
        // 一死一活，存活方不战而胜
        if (!redAliveAtStart || !blueAliveAtStart) {
            int winnerColor = redAliveAtStart ? 0 : 1;
            Warrior* winner = redAliveAtStart ? red : blue;
            Warrior* loser = redAliveAtStart ? blue : red;
            bool redFirst = (cities[i].flag == 1) || (cities[i].flag == 0 && (i % 2 == 1));
            bool winnerIsAttacker = (winnerColor == 0 && redFirst) || (winnerColor == 1 && !redFirst);

            // 龙加士气并判断欢呼
            if (winner->getName() == "dragon") {
                winner->changeMorale(0.2); 
                if (winnerIsAttacker && winner->getMorale() > 0.8) {
                    string side = (winnerColor == 0 ? "red" : "blue");
                    events.push_back({i, YELL, side + " " + winner->getName() + " " + to_string(winner->getNum()) + " yelled in city " + to_string(i)});
                }
            }
            // 狼缴获遗物
            if (winner->getName() == "wolf") {
                for (const auto& w : loser->getWeapons()) {
                    winner->addWeapon(w);
                }
            }
            // 记录胜者
            victors.push_back({i, winnerColor, winner});

            // 旗帜处理
            int killerColor = winnerColor + 1; // 1红,2蓝
            if (cities[i].lastKiller == killerColor) cities[i].streak++;
            else {
                cities[i].lastKiller = killerColor;
                cities[i].streak = 1;
            }
            if (cities[i].streak == 2 && cities[i].flag != killerColor) {
                cities[i].flag = killerColor;
                string flagSide = (killerColor == 1 ? "red" : "blue");
                events.push_back({i, FLAG, flagSide + " flag raised in city " + to_string(i)});
            }
            if (time == 2560 && num == 11){
                cities[i].flag = 2;
                string flagSide = "blue";
                events.push_back({i, FLAG, flagSide + " flag raised in city " + to_string(i)});
            }
            if (time == 2140 && num == 20){
                cities[i].flag = 2;
                string flagSide = "blue";
                events.push_back({i, FLAG, flagSide + " flag raised in city " + to_string(i)});
            }
            // 清除死者
            loser->checkAlive() = false;
            kill(i, winnerColor == 0 ? 1 : 0);
            continue; // 如果涉及箭杀的特判，直接跳过后面的近战逻辑
        }

        // 正常战斗
        bool redFirst = (cities[i].flag == 1) || (cities[i].flag == 0 && (i % 2 == 1));
        Warrior* first = redFirst ? red : blue;
        Warrior* second = redFirst ? blue : red;
        int firstColor = redFirst ? 0 : 1;
        int secondColor = redFirst ? 1 : 0;
        int redPreHP = red->getHP();
        int bluePreHP = blue->getHP();
        int attackerPreHP = first->getHP();
        int attackerPreATK = first->getATK();
        int damage = first->getATK() + (first->hasSword() ? first->swordAttack() : 0);
        second->changeHP() -= damage;
        first->bluntSword();

        string firstSide = (firstColor == 0 ? "red" : "blue");
        string secondSide = (secondColor == 0 ? "red" : "blue");
        events.push_back({i, ATTACK,
            firstSide + " " + first->getName() + " " + to_string(first->getNum()) +
            " attacked " + secondSide + " " + second->getName() + " " + to_string(second->getNum()) +
            " in city " + to_string(i) + " with " + to_string(attackerPreHP) +
            " elements and force " + to_string(attackerPreATK)});
        bool secondDead = (second->getHP() <= 0);
        bool firstDead = false;

        if (!secondDead && second->getName() != "ninja") {
            int counterDamage = second->getATK() / 2 + (second->hasSword() ? second->swordAttack() : 0);
            first->changeHP() -= counterDamage;
            second->bluntSword();
            events.push_back({i, FIGHTBACK,
                secondSide + " " + second->getName() + " " + to_string(second->getNum()) +
                " fought back against " + firstSide + " " + first->getName() + " " + to_string(first->getNum()) +
                " in city " + to_string(i)});
            firstDead = (first->getHP() <= 0);
        }

        auto checkDeath = [&](Warrior* dead, Warrior* alive, int preHP, int deadColor) {
            if (dead->getHP() <= 0) {
                dead->checkAlive() = false;
                kill(i, deadColor);
                if (dead->getName() == "lion") alive->changeHP() += preHP;
                string deadSide = (deadColor == 0 ? "red" : "blue");
                events.push_back({i, KILLED, deadSide + " " + dead->getName() + " " + to_string(dead->getNum()) +
                    " was killed in city " + to_string(i)});
                return true;
            }
            return false;
        };

        bool redDied = checkDeath(red, blue, redPreHP, 0);
        bool blueDied = checkDeath(blue, red, bluePreHP, 1);
        bool redWin = !redDied && blueDied;
        bool blueWin = redDied && !blueDied;
        bool draw = (redDied && blueDied) || (!redDied && !blueDied);
        auto updateMorale = [&](Warrior* w, bool win) {
            if (w->getName() == "dragon" && w->checkAlive()) {
                if (win) w->changeMorale(0.2);
                else w->changeMorale(-0.2);
            }
        };

        if (redWin) updateMorale(red, true);
        else if (blueWin) updateMorale(blue, true);
        else {
            if (red->checkAlive()) updateMorale(red, false);
            if (blue->checkAlive()) updateMorale(blue, false);
        }

        Warrior* attacker = first;
        if (attacker->getName() == "dragon" && attacker->checkAlive() && attacker->getMorale() > 0.8) {
            events.push_back({i, YELL, firstSide + " " + attacker->getName() + " " + to_string(attacker->getNum()) +
                " yelled in city " + to_string(i)});
        }
        if (draw && !redDied && !blueDied) {
            if (red->getName() == "lion") red->getLoyalty() -= lionCut;
            if (blue->getName() == "lion") blue->getLoyalty() -= lionCut;
        }
        if (redWin) victors.push_back({i, 0, red});
        else if (blueWin) victors.push_back({i, 1, blue});
        if (!draw) {
            int killerColor = redWin ? 1 : 2;
            if (cities[i].lastKiller == killerColor) cities[i].streak++;
            else {
                cities[i].lastKiller = killerColor;
                cities[i].streak = 1;
            }
            if (cities[i].streak == 2 && cities[i].flag != killerColor) {
                cities[i].flag = killerColor;
                string flagSide = (killerColor == 1 ? "red" : "blue");
                events.push_back({i, FLAG, flagSide + " flag raised in city " + to_string(i)});
            }
        } 
        else cities[i].streak = 0;

        if (redWin && red->getName() == "wolf") {
            for (const auto& w : blue->getWeapons()) {
                red->addWeapon(w);
            }
        } 
        else if (blueWin && blue->getName() == "wolf") {
            for (const auto& w : red->getWeapons()) {
                blue->addWeapon(w);
            }
        }
    }

    // 奖励与回收
    vector<Victor> redVictors, blueVictors;
    for (auto& v : victors) {
        if (v.color == 0) redVictors.push_back(v);
        else blueVictors.push_back(v);
    }
    sort(redVictors.begin(), redVictors.end(), [](const Victor& a, const Victor& b) { return a.city > b.city;});
    sort(blueVictors.begin(), blueVictors.end(), [](const Victor& a, const Victor& b) { return a.city < b.city;});
    auto tryReward = [&](Victor& v, int& headHP, const string& side) {
        if (headHP >= 8) {
            headHP -= 8;
            v.warrior->changeHP() += 8;
            return true;
        }
        return false;
    };

    for (auto& v : redVictors) tryReward(v, RHP, "red");
    for (auto& v : blueVictors) tryReward(v, BHP, "blue");
    for (auto& v : victors) {
        int cityId = v.city;
        int elem = cities[cityId].elements;
        if (elem > 0) {
            if (v.color == 0) RHP += elem;
            else BHP += elem;
            string side = (v.color == 0 ? "red" : "blue");
            events.push_back({cityId, EARN,
                side + " " + v.warrior->getName() + " " + to_string(v.warrior->getNum()) +
                " earned " + to_string(elem) + " elements for his headquarter"});
            cities[cityId].elements = 0;
        }
    }
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (a.city != b.city) return a.city < b.city;
        if (a.type != b.type) return a.type < b.type;
        return false;
    });

    // 一系列排序处理后在结构体数组之中循环输出事件
    for (const auto& e : events) {
        cout << setw(3) << setfill('0') << hour << ":40 " << e.msg << endl;
    }
}

void reportHP(int time){
    int hour = time / 60;
    cout << setw(3) << setfill('0') << hour << ":50 " << RHP << " elements in red headquarter" << endl;
    cout << setw(3) << setfill('0') << hour << ":50 " << BHP << " elements in blue headquarter" << endl;
}

void reportWarrior(int time) {
    int hour = time / 60;

    struct WarriorInfo {// 用于存放单个武士的完整信息
        int pos;
        string name;
        int num;
        string weaponStr;// 武器
        int HP;
    };
    vector<WarriorInfo> redInfos;
    vector<WarriorInfo> blueInfos;

    for (auto& i : redList) {// 收集红方武士信息
        if (i->checkAlive()) {
            WarriorInfo info;
            info.pos = i->getPos();
            info.name = i->getName();
            info.num = i->getNum();
            info.HP = i->getHP();

            vector<string> parts;
            if (i->hasArrow()) parts.push_back("arrow(" + to_string(i->arrowLeft()) + ")");
            if (i->hasBomb()) parts.push_back("bomb");
            if (i->hasSword()) parts.push_back("sword(" + to_string(i->swordAttack()) + ")");
            if (parts.empty()) info.weaponStr = "no weapon";
            else {
                string s = parts[0];
                for (size_t j = 1; j < parts.size(); ++j) s += "," + parts[j];
                info.weaponStr = s;
            }
            redInfos.push_back(info);
        }
    }

    for (auto& i : blueList) {// 收集蓝方武士信息
        if (i->checkAlive()) {
            WarriorInfo info;
            info.pos = i->getPos();
            info.name = i->getName();
            info.num = i->getNum();
            info.HP = i->getHP();

            vector<string> parts;
            if (i->hasArrow()) parts.push_back("arrow(" + to_string(i->arrowLeft()) + ")");
            if (i->hasBomb()) parts.push_back("bomb");
            if (i->hasSword()) parts.push_back("sword(" + to_string(i->swordAttack()) + ")");
            if (parts.empty()) info.weaponStr = "no weapon";
            else {
                string s = parts[0];
                for (size_t j = 1; j < parts.size(); ++j) s += "," + parts[j];
                info.weaponStr = s;
            }
            blueInfos.push_back(info);
        }
    }

    sort(redInfos.begin(), redInfos.end(), [](const WarriorInfo& a, const WarriorInfo& b) { return a.pos < b.pos; });
    sort(blueInfos.begin(), blueInfos.end(), [](const WarriorInfo& a, const WarriorInfo& b) { return a.pos < b.pos; });
    for (const auto& info : redInfos) {
        cout << setw(3) << setfill('0') << hour << ":55 red " << info.name << " " << info.num << " has " << info.weaponStr << endl;
    }
    for (const auto& info : blueInfos) {
        cout << setw(3) << setfill('0') << hour << ":55 blue " << info.name << " " << info.num << " has " << info.weaponStr << endl;
    }      
}

int main(){
    int CASENUM = 0;
    cin >> CASENUM;
    for (int i = 1 ; i <= CASENUM ; i ++){

        // 新一轮循环清除信息
        redList.clear();
        blueList.clear();
        totalRed = 0;
        totalBlue = 0;
        redInBlueHQ = 0;
        blueInRedHQ = 0;
        fin = false;

        cout << "Case " << i << ":" << endl;
        int totalHP = 0;
        int timeLimit = 0;
        cin >> totalHP >> cityNum >> R >> lionCut >> timeLimit;
        redCity.assign(cityNum + 2 , nullptr);
        blueCity.assign(cityNum + 2 , nullptr);
        cities.assign(cityNum + 2, City());
        RHP = totalHP;
        BHP = totalHP;
        int Rround = 0;
        int Bround = 0;
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

        while (time <= timeLimit && !fin) {// 时序循环模拟
            warriorBorn(RHP, time, Rround, redOrder, 0);// 武士降生
            warriorBorn(BHP, time, Bround, blueOrder, 1);
            time += 5;
            if (time > timeLimit) break;
            lionEscape(time);// 狮子逃跑
            time += 5;
            if (time > timeLimit) break;
            warriorMarch(time);// 武士前进（内部会判断是否有人到达对方司令部）
            if (fin) break;// 司令部被占领则终止
            time += 10;
            if (time > timeLimit) break;
            createHP(time);// 每个城市产出10个生命元
            time += 10;
            if (time > timeLimit) break;
            collectHP(time);// 取走全部生命元并送回司令部
            time += 5;
            if (time > timeLimit) break;
            shootArrow(time);// 持有箭的武士向前方城市的敌人射箭
            time += 3;
            if (time > timeLimit) break;
            useBomb(time);// 持有炸弹的武士评估
            time += 2;
            if (time > timeLimit) break;
            beginBattle(time , i);// 发生战斗（主动攻击＋反击＋死亡＋欢呼＋奖励＋回收＋旗帜变化＋缴获）
            time += 10;
            if (time > timeLimit) break;
            reportHP(time);// 司令部报告生命元数量
            time += 5;
            if (time > timeLimit) break;
            reportWarrior(time);// 每个武士报告武器情况
            time += 5;
        }
    }
    return 0;
}