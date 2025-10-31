#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    
    vector<int> st;  // 用vector模拟栈
    vector<int> left(n), right(n, n);
    int result = 0;
    
    // 一次遍历计算左右边界
    for (int i = 0; i < n; i++) {
        // 维护单调递增栈
        while (!st.empty() && heights[st.back()] >= heights[i]) {
            // 当前元素是栈顶元素的右边界
            right[st.back()] = i;
            st.pop_back();
        }
        // 栈顶元素是当前元素的左边界
        left[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    
    // 计算最大面积
    for (int i = 0; i < n; i++) {
        int width = right[i] - left[i] - 1;
        int area = heights[i] * width;
        if (area > result) {
            result = area;
        }
    }
    
    cout << result;
    return 0;
}