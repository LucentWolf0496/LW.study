#include <iostream>
using namespace std;

int main() {
    // 定义四个湖的排名变量：dongting, hongze, poyang, tai
    for (int dt = 1; dt <= 4; dt++) {
        for (int hz = 1; hz <= 4; hz++) {
            for (int py = 1; py <= 4; py++) {
                for (int t = 1; t <= 4; t++) {
                    // 确保排名互不相同
                    if (dt != hz && dt != py && dt != t && hz != py && hz != t && py != t) {
                        // 计算每个人说对的数量
                        int A_correct = (dt == 1) + (hz == 4) + (py == 3);
                        int B_correct = (hz == 1) + (dt == 4) + (py == 2) + (t == 3);
                        int C_correct = (hz == 4) + (dt == 3);
                        int D_correct = (py == 1) + (t == 4) + (hz == 2) + (dt == 3);
                        
                        // 检查是否每个人恰好说对了一个
                        if (A_correct == 1 && B_correct == 1 && C_correct == 1 && D_correct == 1) {
                            // 输出从大到小的顺序
                            cout << "四大淡水湖从大到小的顺序是：" << endl;
                            
                            // 找出排名为1的湖（最大）
                            if (dt == 1) cout << "1. 洞庭湖" << endl;
                            else if (hz == 1) cout << "1. 洪泽湖" << endl;
                            else if (py == 1) cout << "1. 鄱阳湖" << endl;
                            else if (t == 1) cout << "1. 太湖" << endl;
                            
                            // 找出排名为2的湖
                            if (dt == 2) cout << "2. 洞庭湖" << endl;
                            else if (hz == 2) cout << "2. 洪泽湖" << endl;
                            else if (py == 2) cout << "2. 鄱阳湖" << endl;
                            else if (t == 2) cout << "2. 太湖" << endl;
                            
                            // 找出排名为3的湖
                            if (dt == 3) cout << "3. 洞庭湖" << endl;
                            else if (hz == 3) cout << "3. 洪泽湖" << endl;
                            else if (py == 3) cout << "3. 鄱阳湖" << endl;
                            else if (t == 3) cout << "3. 太湖" << endl;
                            
                            // 找出排名为4的湖（最小）
                            if (dt == 4) cout << "4. 洞庭湖" << endl;
                            else if (hz == 4) cout << "4. 洪泽湖" << endl;
                            else if (py == 4) cout << "4. 鄱阳湖" << endl;
                            else if (t == 4) cout << "4. 太湖" << endl;
                            
                            return 0; // 找到答案后直接退出
                        }
                    }
                }
            }
        }
    }
    
    cout << "没有找到符合条件的排名！" << endl;
    return 0;
}