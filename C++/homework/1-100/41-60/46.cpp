#include <iostream>
#include <vector>
using namespace std;

float f(float a1 , float b1 , float a2 , float b2 , float a3 , float b3){
    float check = (a2 - a1) * (b3 - b1) - (b2 - b1) * (a3 - a1);
    return check;
}

int main(){
    vector<float> num(8);
    while (cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4] >> num[5] >> num[6] >> num[7]) {
        // 模板：对输入流持续读取直到结束
        struct pair{
            float x1;
            float y1;
            float x2;
            float y2;
        };
        vector<pair> t;
        // 小心！应该在循环内部定义vector才会被初始化
        // 如果在外面定义会导致数据堆积，影响下一循环
        // 注意暂存量的及时在循环内！！！清除！！！
        for (int i = 0 ; i < 8 ; i += 2){
            t.push_back({num[i] , num[i + 1] , num[(i + 2) % 8] , num[(i + 3) % 8]});
        }
        vector<float> check;
        for (int i = 0 ; i < 4 ; i ++){
            for (int j = 0 ; j < 2 ; j ++){
                int s = i * 2 + 4 + j * 2;
                float temp = f(t[i].x1 , t[i].y1 , t[i].x2 , t[i].y2 , num[s % 8] , num[(s + 1) % 8]);
                check.push_back(temp);
            }
        }
        int terminal = 0;
        for (int i = 0 ; i < 8 ; i += 2){
            if ((check[i] < 0 && check[i + 1] < 0) || (check[i] > 0 && check[i + 1] > 0))
                terminal ++;
        }
        if (terminal == 4)
            cout << "yes" << endl;
        else if (terminal != 4)
            cout << "no" << endl;
    }
    return 0;
}