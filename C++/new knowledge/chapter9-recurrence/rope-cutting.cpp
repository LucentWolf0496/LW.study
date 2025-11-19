#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int total = 0;
    cin >> total;
    vector<int> parts;
    int part = 0;
    long long result = 0;// 数据爆炸的时候，不妨试试long long？
                         // tips：使用<climits>头文件的LLONG_MAX可以用于求最小值
    while(cin >> part){
        parts.push_back(part);
    }
    
    sort(parts.begin() , parts.end());// <algorithm>头文件下的排序函数

    while(!parts.empty()){
        result += parts[0] + parts[1];
        int temp = parts[0] + parts[1];
        parts.erase(parts.begin());
        parts.erase(parts.begin());
        if (!parts.empty()){
            if (temp <= parts[0])
                parts.insert(parts.begin() , temp);
            else if (temp >= parts[parts.size() - 1])
                parts.push_back(temp);
            else{
                for (int i = 0 ; i < parts.size() - 1 ; i ++){
                    if (temp >= parts[i] && temp <= parts[i + 1]){
                        parts.insert(parts.begin() + i + 1 , temp);
                        break;
                    }
                }
            }
        }
    }

    cout << result << endl;
}