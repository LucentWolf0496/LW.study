#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int arrivalTimes[20];
    for (int i = 0; i < n; i++) {
        cin >> arrivalTimes[i];
    }
    
    // 按到达时间排序
    sort(arrivalTimes, arrivalTimes + n);
    
    int startTime = 60; // 9:00是第60分钟（从8:00开始算）
    int endTime = 180;  // 11:00是第180分钟
    int count = 0;
    int currentTime = startTime; // 当前就诊时间
    
    for (int i = 0; i < n; i++) {
        // 如果病人到达时间晚于当前就诊时间，更新当前就诊时间
        if (arrivalTimes[i] > currentTime) {
            currentTime = arrivalTimes[i];
        }
        
        // 检查是否能看完这个病人
        if (currentTime < endTime && currentTime + 10 <= endTime) {
            count++;
            currentTime += 10;
        } else {
            // 如果当前时间已经接近结束，后面的病人都看不了了
            break;
        }
    }
    
    cout << count << endl;
    return 0;
}