#include <iostream>
#include <string>
using namespace std;

string multiply(string x , int y){
    string result;
    int next = 0;
    for (int i = x.size() - 1 ; i >= 0 ; i --){
        int num = x[i] - '0';
        num = num * y + next;
        next = num / 10;
        num = num % 10;
        char temp = '0' + num;
        result.push_back(temp);
    }

    while(next > 0){
        char temp = next % 10 + '0';
        result.push_back(temp);
        next /= 10;
    }

    string result1;
    for (int i = result.size() - 1 ; i >= 0 ; i --){
        result1.push_back(result[i]);
    }

    return result1;
}

bool check(string x , string y){
    if(x.size() != y.size())
        return false;
    else{
        int size = x.size();
        string yy = y + y;
        for (int i = 0 ; i < size ; i ++){
            if (x == yy.substr(i , size))
                return true;
        }
        return false;
    }
}

int main(){
    string temp;
    while(cin >> temp){
        cout << temp << ' ';
        bool thu = true;

        for (int i = 1 ; i <= temp.size() ; i ++){
            if (!check(temp , multiply(temp , i))){
                thu = false;
                cout << "is not cyclic" << endl;
                break;
            }
        }

        if (thu){
            cout << "is cyclic" << endl;
        }
    }

    return 0;
}