#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct item{
    string patient;
    string doctor;
    int time;// 治疗时间
    int trail;// 签到次数
    int time222;// 签到时间
    int time333;// 挂号时间
};

int main(){
    int t = 0;
    cin >> t;
    cin.ignore();
    vector<string> list(t);
    vector<item> appointment;
    vector<item> registered;// 按时队列
    vector<item> laters;// 迟到队列
    int now;
    for (int i = 0 ; i < t ; i ++){
        getline(cin , list[i]);
        stringstream ss(list[i]);
        int hour;
        int minute;
        string command;
        string per1;
        string per2;
        int hourx = 0;
        int minutex = 0; 
        ss >> hour >> minute >> command >> per1 >> per2 >> hourx >> minutex;
        now = hour * 60 + minute;
        int apptime = hourx * 60 + minutex;
        if (command == "appointment"){
            item temp = {per1 , per2 , apptime , 0 , 0 , now};
            appointment.push_back(temp);
        }
        else if (command == "register"){
            bool ok = false;
            for (int j = 0 ; j < appointment.size() ; j ++){
                if (per1 != appointment[j].patient) continue;
                if (per1 == appointment[j].patient){
                    if (appointment[j].trail == 1) break;
                    if (now < appointment[j].time - 60) break;
                    else if (now >= appointment[j].time - 60 && now <= appointment[j].time){
                        ok = true;
                        cout << "Success" << endl;
                        appointment[j].trail = 1;
                        appointment[j].time222 = now;
                        registered.push_back(appointment[j]);
                        break;
                    }
                    else{
                        ok = true;
                        cout << "Success" << endl;
                        appointment[j].trail = 1;
                        appointment[j].time222 = now;
                        laters.push_back(appointment[j]);
                        break;
                    }
                }
            }
            if (!ok) cout << "Fail" << endl;
        }
        else if (command == "query"){
            bool ok = false;
            bool needlate = true;
            int besttime = 11111;
            int besttime222 = 11111;
            int besttime333 = 11111;
            int index = 0;
            for (int j = 0 ; j < registered.size() ; j ++){
                if (per1 != registered[j].doctor) continue;
                if (per1 == registered[j].doctor){
                    ok = true;
                    needlate = false;
                    if (registered[j].time < besttime){
                        besttime = registered[j].time;
                        besttime333 = registered[j].time333;
                        index = j;
                    }
                    else if (besttime == registered[j].time){
                        if (registered[j].time333 < besttime333){
                            besttime333 = registered[j].time333;
                            index = j;
                        }
                    }
                }
            }
            if (!needlate){
                item selected = registered[index];
                registered.erase(registered.begin() + index);
                string aaa = selected.patient;
                cout << aaa[0];
                for (int j = 1 ; j < aaa.size() - 1 ; j ++){
                    cout << '*';
                }
                cout << aaa[aaa.size() - 1] << endl; 
            }
            if (needlate && !laters.empty()){
                bool sb = true;// SBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSBSB
                for (int j = 0 ; j < laters.size() ; j ++){
                    if (per1 != laters[j].doctor) continue;
                    if (per1 == laters[j].doctor){
                        ok = true;
                        sb = false;
                        if (laters[j].time222 < besttime222){
                            besttime222 = laters[j].time222;
                            index = j;
                        }
                    }
                }
                if (!sb){
                    item selected = laters[index];
                    laters.erase(laters.begin() + index);
                    string aaa = selected.patient;
                    cout << aaa[0];
                    for (int j = 1 ; j < aaa.size() - 1 ; j ++){
                        cout << '*';
                    }
                    cout << aaa[aaa.size() - 1] << endl;
                }
            }
            if (!ok) cout << "No patient" << endl;
        }
    }
}