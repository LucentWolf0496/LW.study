#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    vector<int> num;
    for (int i = 1 ; i <= n ; i ++)
    {
        int m = 0;
        cin >> m;
        num.push_back(m);
    }
    for (int i = 0 ; i < num.size() ; i ++)
    {
        int k = num[i];
        for (int j = i + 1 ; j < num.size() ; j ++)
        {
            if (num[j] == k)
            {
                num.erase(num.begin() + j);
                j -= 1;// 处理关键点：如果擦去了某个元素，可能下一位还要擦去，要在原位再判断，故使用j -= 1
            }
        }
    }
    cout << num[0];
    for (int i = 1 ; i < num.size() ; i ++)
    {
        cout << " " << num[i];
    }
    cout << endl;
    return 0;
}