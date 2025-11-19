#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    struct patient{
        string id;
        int old;
    };
    vector<patient> list1;
    vector<patient> list2;
    for (int i = 0 ; i < n ; i ++){
        string s;
        int n;
        cin >> s >> n;
        if (n >= 60)
            list1.push_back({s , n});
        else
            list2.push_back({s , n});
    }
    for (int i = 1 ; i < list1.size() ; i ++){
        for (int j = 0 ; j < list1.size() - i ; j ++){
            if (list1[j].old < list1[j + 1].old){
                patient temp = list1[j];
                list1[j] = list1[j + 1];
                list1[j + 1] = temp;
            }
        }
    }
    for (int i = 0 ; i < list1.size() ; i ++){
        cout << list1[i].id << endl;
    }
    for (int i = 0 ; i < list2.size() ; i ++){
        cout << list2[i].id << endl;
    }
    return 0;
}
