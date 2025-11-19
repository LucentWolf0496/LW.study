#include <iostream>
#include <vector>
using namespace std;
// 核心：dp单调栈
// 一次维护单调栈保证寻找边界时规避暴力循环

// 数组题目总是要尤其小心索引！！！！！

int main(){
    int n = 0;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0 ; i < n ; i ++){
        cin >> heights[i];
    }
    vector<int> left(n , -1);
    vector<int> right(n , n);
    vector<int> stack;

    for (int i = 0 ; i < n ; i ++){
        int temp = i;
        while(!stack.empty() && heights[stack.back()] >= heights[i]){
            right[stack.back()] = i;
            stack.pop_back();
        }
        left[i] = (stack.empty() ? -1 : stack.back());
        stack.push_back(i);
    }

    int result = 0;
    for (int i = 0 ; i < n ; i ++){
        int temp = heights[i] * (right[i] - left[i] - 1);
        if (temp > result)
            result = temp;
    }
    cout << result << endl;
}