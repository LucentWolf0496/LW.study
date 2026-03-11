#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    vector<double> num;
    int n = 0;
    double sum = 0 , sum1 = 0;
    cin >> n;
    for (int i = 1 ; i <= n ; i ++)
    {
        double m = 0.0;
        cin >> m;
        num.push_back(m);// 添加元素规避vector没有声明，利用vector的动态变化性质！
        sum += num[i - 1];
    }
    double e = (sum + 0.0) / n;
    for (int i = 1 ; i <= n ; i ++)
    {
        num[i - 1] = (num[i - 1] - e) * (num[i - 1] - e);
        sum1 += num[i - 1];
    }
    double d = (sum1 + 0.0) / n;
    cout << fixed << setprecision(5) << e << " " << fixed << setprecision(5) << d << endl;
    return 0;
}