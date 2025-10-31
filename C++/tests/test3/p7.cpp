#include <iostream>
#include <vector>
using namespace std;

int main(){
    struct bio{
        int num;
        double z;
    };
    int n = 0;
    cin >> n;
    vector<bio> list;
    for (int i = 0 ; i < n ; i ++){
        int a , b , c;
        cin >> a >> b >> c;
        double d = c / (b + 0.0);
        list.push_back({a , d});
    }
    for (int i = 1 ; i < n ; i ++){
        for (int j = 0 ; j < n - i ; j ++){
            if (list[j].z > list[j + 1].z){
                bio temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    int number = 0;
    double cha = list[1].z - list[0].z;
    for (int i = 1 ; i < n - 1 ; i ++){
        if (list[i + 1].z - list[i].z > cha){
            cha = list[i + 1].z - list[i].z;
            number = i;
        }
    }
    cout << n - (number + 1) << endl;
    for (int i = number + 1 ; i < n ; i ++){
        cout << list[i].num << endl;
    }
    cout << number + 1 << endl;
    for (int i = 0 ; i <= number ; i ++){
        cout << list[i].num << endl;
    }
    return 0;
}