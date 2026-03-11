#include <iostream>
#include <string>
#include <vector>
using namespace std;// 简单题注意细节！！！

int main(){
    int n = 0;
    cin >> n;
    vector<string> book(n);
    vector<string> info(n);
    vector<int> year(n , 0);
    vector<int> month(n , 0);
    vector<int> date(n , 0);
    for (int i = 0 ; i < n ; i ++){
        cin >> book[i] >> info[i];
        string datex;
        string monthx;
        string yearx;
        if (info[i][1] > '9' || info[i][1] < '0'){
            datex = info[i].substr(0 , 1);
            monthx = info[i].substr(4 , 3);
            yearx = info[i].substr(8 , 4);
        }
        else{
            datex = info[i].substr(0 , 2);
            monthx = info[i].substr(5 , 3);
            yearx = info[i].substr(9 , 4);
        }
        if (datex.size() == 1) date[i] += datex[0] - '0';
        else{
            date[i] += datex[1] - '0';
            date[i] += (datex[0] - '0') * 10;
        }
        year[i] = 1000 * (yearx[0] - '0') + 100 * (yearx[1] - '0') + 10 * (yearx[2] - '0') + (yearx[3] - '0');// 细节1：不要漏掉x
        if (monthx == "Jan") month[i] = 1;
        if (monthx == "Feb") month[i] = 2;
        if (monthx == "Mar") month[i] = 3;
        if (monthx == "Apr") month[i] = 4;
        if (monthx == "May") month[i] = 5;
        if (monthx == "Jun") month[i] = 6;
        if (monthx == "Jul") month[i] = 7;
        if (monthx == "Aug") month[i] = 8;
        if (monthx == "Sep") month[i] = 9;
        if (monthx == "Oct") month[i] = 10;
        if (monthx == "Nov") month[i] = 11;
        if (monthx == "Dec") month[i] = 12;
    }
    for (int i = 1 ; i < n ; i ++){
        for (int j = 0 ; j < n - i ; j ++){// 细节2：由于最后会颠倒，故冒泡排序过程就不需要颠倒，只需要严格比大小即可！！！
            if (year[j] < year[j + 1] || (year[j] == year[j + 1] && month[j] < month[j + 1]) || (year[j] == year[j + 1] && month[j] == month[j + 1] && date[j] < date[j + 1])){
                string temp = book[j];
                book[j] = book[j + 1];
                book[j + 1] = temp;
                int p = year[j];
                year[j] = year[j + 1];
                year[j + 1] = p;
                int q = month[j];
                month[j] = month[j + 1];
                month[j + 1] = q;
                int r = date[j];
                date[j] = date[j + 1];
                date[j + 1] = r;
            }
        }
    }
    for (int i = n - 1 ; i >= 0 ; i --){
        cout << book[i] << endl;
    }
}