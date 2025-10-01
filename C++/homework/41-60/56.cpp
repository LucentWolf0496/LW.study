#include <iostream>
#include <vector>
using namespace std;

int main(){
    struct book{// 结构体方便通过作者名字反过来搜索书籍编号
        int num;
        string name;
    };
    int n = 0;
    cin >> n;// 不能忘记cin >>
    vector<book> list;
    vector<int> count(26);// 通过将大写字符减去大A将字符转为数码，于是可通过count数组计数
    for (int i = 1 ; i <= n ; i ++){
        int temp1;
        string temp2;
        cin >> temp1 >> temp2;
        list.push_back({temp1 , temp2});// 使用push_back借用vector动态数组的力量
    }
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < list[i].name.size() ; j ++){
            count[list[i].name[j] - 'A'] ++;// 直接运算将大写字符转为count数组对应的序数
        }
    }
    int temp = 0;
    char per;
    for (int i = 0 ; i < 26 ; i ++){
        if (count[i] > temp){
            temp = count[i];
            per = i + 'A';// 对temp和per的不断更新，保证最大
        }
    }
    cout << per << endl;
    cout << temp << endl;
    vector<int> result;
    for (int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < list[i].name.size() ; j ++){
            if (list[i].name[j] == per){
                result.push_back(list[i].num);// 借用结构体反过来搜索含有per的书籍编号
            }
        }
    }
    for (int i = 0 ; i < result.size() ; i ++){
        cout << result[i] << endl;
    }
    return 0;
}