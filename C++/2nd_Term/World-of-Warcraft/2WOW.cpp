// version2思路：使用类的继承和派生来表达这些武士各自的特点
// 本程序有两种类，第一种是全局变量中定义的基类，用于记录每一种武士的基本情况：HP和个数，并且提供相关基类函数
// 第二种是全局变量只定义数组，需要后续加入元素的派生类，数组里面装的是具体的武士个体对象，有各自的编号、武器以及特色数值
// 需要注意的是num这一元素对于二者有不同的含义！！！
// Caution！！本程序中基类小写首字母，派生类大写首字母！！注意区分
// Given-Order:dragon、ninja、iceman、lion、wolf
// Red-Order:iceman、lion、wolf、ninja、dragon
// Blue-Order:lion、dragon、ninja、iceman、wolf
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

vector<string> weaponList = {"sword" , "bomb" , "arrow"};// 武器顺序

class Warrior{// 基类，用于记录每种武士的基本情况
    private:
        int HP;
        string name;
        int num;// 这个num数值对于不同对象含义不同
                // 对于派生类生成武士个体对象：第几个某类武士
                // 对于基类记录对象：有几个某类武士
    public:
        Warrior(){}
        Warrior(int n , string x){HP = n; name = x; num = 0;}
        void setInfo(int n , string x , int m){HP = n; name = x; num = m;}
        int getHP(){return HP;}
        string getName(){return name;}
        void add(){num ++;}
        int getNum(){return num;}
};

// 下为五个派生类，用于生成五种具体的武士，注意区分基类和派生类对象的【含义&作用】之区别
class Dragon: public Warrior{
    private:
        int weapon;
        float morale;
        int caseNum;// 武士对象的编号（仅针对派生类生成武士个体对象，不针对基类记录对象）
    public:
        Dragon(){  };
        Dragon(int n , string x , int m , int HPleft , int time){
            Warrior::setInfo(n , x , m);// 调用基类中的函数去设置基类的private量
            caseNum = time + 1;
            weapon = caseNum % 3;
            morale = (HPleft + 0.0) / n;
        };
        void output(){
            cout << "It has a " << weaponList[weapon] << ",and it's morale is " << fixed << setprecision(2) << morale << endl;
        };                                                          // 不加fixed是总保留位数，加fixed是保留小数位数————细节
};

class Ninja: public Warrior{
    private:
        int weapon1;
        int weapon2;
        int caseNum;
    public:
        Ninja(){  };
        Ninja(int n , string x , int m , int time){
            Warrior::setInfo(n , x , m);
            caseNum = time + 1;
            weapon1 = caseNum % 3;
            weapon2 = (caseNum + 1) % 3;
        }
        void output(){
            cout << "It has a " << weaponList[weapon1] << " and a " << weaponList[weapon2] << endl;
        };
};

class Iceman: public Warrior{
    private:
        int weapon;
        int caseNum;
    public:
        Iceman(){  };
        Iceman(int n , string x , int m , int time){
            Warrior::setInfo(n , x , m);
            caseNum = time + 1;
            weapon = caseNum % 3;
        }
        void output(){
            cout << "It has a " << weaponList[weapon] << endl;
        };
};

class Lion: public Warrior{
    private:
        int loyalty;
        int caseNum;
    public:
        Lion(){  };
        Lion(int n , string x , int m , int HPleft , int time){
            Warrior::setInfo(n , x , m);
            caseNum = time + 1;
            loyalty = HPleft;
        }
        void output(){
            cout << "It's loyalty is " << loyalty << endl;
        };
};

class Wolf: public Warrior{
    private:
        int caseNum;
    public:
        Wolf(){  };
        Wolf(int n , string x , int m , int time){
            Warrior::setInfo(n , x , m);
            caseNum = time + 1;
        }
        void output(){  };
};

Warrior dragon , ninja , iceman , lion , wolf;// 基类下的五个对象，存储五种武士的基本信息
// 五个派生类数组，存储具体到每一个的武士信息
vector<Dragon> Dragonlist;
vector<Ninja> Ninjalist;
vector<Iceman> Icemanlist;
vector<Lion> Lionlist;
vector<Wolf> Wolflist;

void takeStep(int &HP , int time , int &round , bool &stop , vector<Warrior> &order , int color){
                                                    // 这里要对order数组取引用，否则只是浅拷贝，num无法累计增加
    string side = (color == 0 ? "red" : "blue");
    bool checkStep = false;// 结束判据符号
    for (int i = 0 ; i < 5 ; i ++){
        int roundx = (round + i) % 5;// 一一尝试
        if (HP >= order[roundx].getHP()){
            checkStep = true;// 成功建造，不必结束
            order[roundx].add();// 基类对象数目加一，表明该种武士数目加一
            cout << setw(3) << setfill('0') << time << " " << side << " " << order[roundx].getName() << " " << time + 1 << " ";
            cout << "born with strength " << order[roundx].getHP() << "," << order[roundx].getNum() << " " << order[roundx].getName();
            cout << " in " << side << " headquarter" << endl;
            HP -= order[roundx].getHP();// 消耗生命元

            string tmpstr = order[roundx].getName();// 对每一个武士的个性化处理如下
            if (tmpstr == "dragon"){
                Dragon temp(order[roundx].getHP() , "dragon" , order[roundx].getNum() , HP , time);
                temp.output();
                Dragonlist.push_back(temp);
            }
            else if (tmpstr == "ninja"){
                Ninja temp(order[roundx].getHP() , "ninja" , order[roundx].getNum() , time);
                temp.output();
                Ninjalist.push_back(temp);
            }
            else if (tmpstr == "iceman"){
                Iceman temp(order[roundx].getHP() , "iceman" , order[roundx].getNum() , time);
                temp.output();
                Icemanlist.push_back(temp);
            }
            else if (tmpstr == "lion"){
                Lion temp(order[roundx].getHP() , "lion" , order[roundx].getNum() , HP , time);
                temp.output();
                Lionlist.push_back(temp);
            }
            else if (tmpstr == "wolf"){
                Wolf temp(order[roundx].getHP() , "wolf" , order[roundx].getNum() , time);
                temp.output();
                Wolflist.push_back(temp);
            }

            round = (roundx + 1) % 5;// 轮次增加
            break;// 尝试建造成功，退出循环，随后退出函数
        }
    }
    if (!checkStep){
        stop = true;// 终止某方建造过程
        cout << setw(3) << setfill('0') << time << " " << side << " headquarter stops making warriors" << endl;
    }
}

int main(){
    int caseNum = 0;
    cin >> caseNum;
    for (int i = 1 ; i <= caseNum ; i ++){
        Dragonlist.clear();// 新一轮循环清除记录的武士信息
        Ninjalist.clear();
        Icemanlist.clear();
        Lionlist.clear();
        Wolflist.clear();
        cout << "Case:" << i << endl;
        int totalHP = 0;
        cin >> totalHP;
        int RHP = totalHP;
        int Rround = 0;
        bool Rstop = false;
        int BHP = totalHP;
        int Bround = 0;
        bool Bstop = false;
        vector<int> HPlist(5);
        for (int j = 0 ; j < 5 ; j ++) {cin >> HPlist[j];}
        int time = 0;
        dragon = Warrior(HPlist[0] , "dragon");// 基类对象初始化：记录HP与名称，设置数目为0
        ninja = Warrior(HPlist[1] , "ninja");
        iceman = Warrior(HPlist[2] , "iceman");
        lion = Warrior(HPlist[3] , "lion");
        wolf = Warrior(HPlist[4] , "wolf");
        vector<Warrior> redOrder = {iceman , lion , wolf , ninja , dragon};
        vector<Warrior> blueOrder = {lion , dragon , ninja , iceman , wolf};
        while(!Rstop || !Bstop){// stop标志会在函数中通过传引用来改变，从而确定循环终止
            if (!Rstop) takeStep(RHP , time , Rround , Rstop , redOrder , 0);
            if (!Bstop) takeStep(BHP , time , Bround , Bstop , blueOrder , 1);
            time ++;
        }
    }
    return 0;
}