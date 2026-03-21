#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;
// Given-Order:dragon、ninja、iceman、lion、wolf
// Red-Order:iceman、lion、wolf、ninja、dragon
// Blue-Order:lion、dragon、ninja、iceman、wolf
class Warrior{
    private:
        int HP;
        string name;
        int num;
    public:
        Warrior(){}
        Warrior(int n , string x){HP = n; name = x; num = 0;}
        int getHP(){return HP;}
        string getName(){return name;}
        void add(){num ++;}
        int getNum(){return num;}
};

Warrior dragon , ninja , iceman , lion , wolf;

void takeStep(int &HP , int time , int &round , bool &stop , vector<Warrior> &order , int color){
                                                    // 这里要对order数组取引用，否则只是浅拷贝，num无法累计增加
    string side = (color == 0 ? "red" : "blue");
    bool checkStep = false;
    for (int i = 0 ; i < 5 ; i ++){
        int roundx = (round + i) % 5;
        if (HP >= order[roundx].getHP()){
            checkStep = true;
            order[roundx].add();
            cout << setw(3) << setfill('0') << time << " " << side << " " << order[roundx].getName() << " " << time + 1 << " ";
            cout << "born with strength " << order[roundx].getHP() << "," << order[roundx].getNum() << " " << order[roundx].getName();
            cout << " in " << side << " headquarter" << endl;
            HP -= order[roundx].getHP();
            round = (roundx + 1) % 5;
            break;
        }
    }
    if (!checkStep){
        stop = true;
        cout << setw(3) << setfill('0') << time << " " << side << " headquarter stops making warriors" << endl;
    }
}

int main(){
    int caseNum = 0;
    cin >> caseNum;
    for (int i = 1 ; i <= caseNum ; i ++){
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
        dragon = Warrior(HPlist[0] , "dragon");
        ninja = Warrior(HPlist[1] , "ninja");
        iceman = Warrior(HPlist[2] , "iceman");
        lion = Warrior(HPlist[3] , "lion");
        wolf = Warrior(HPlist[4] , "wolf");
        vector<Warrior> redOrder = {iceman , lion , wolf , ninja , dragon};
        vector<Warrior> blueOrder = {lion , dragon , ninja , iceman , wolf};
        while(!Rstop || !Bstop){
            if (!Rstop) takeStep(RHP , time , Rround , Rstop , redOrder , 0);
            if (!Bstop) takeStep(BHP , time , Bround , Bstop , blueOrder , 1);
            time ++;
        }
    }
}