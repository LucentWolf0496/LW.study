#include<bits/stdc++.h>
using namespace std;

const int maxN = 1000+5;

int TimeTable[maxN] = {};
int Peo = 0;

void get(string &x, vector<int> &t, int v){
    getline(cin, x);
    for(char& c : x) if(!isdigit(c)) c = ' ';
    stringstream ss(x);
    int num;
    while(ss >> num){
        TimeTable[num] += v;
        if(v == 1) Peo++;
    }
}

int main(){
    int cur = 0, maxcur = -1;
    vector<int> t1, t2;
    string s1, s2;
    get(s1, t1, 1); get(s2, t2, -1);
    cout<<Peo<<" ";
    for(int i = 0; i < maxN ; i++){
        cur += TimeTable[i];
        if(cur > maxcur) maxcur = cur;
    }
    cout<<maxcur;
    return 0;
}