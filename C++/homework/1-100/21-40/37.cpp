#include <iostream>
#include <vector>
using namespace std;

int main()// 使用结构数组版本的逻辑推理问题，懒得在输出的时候if，但是前置工作需要细致准备
{
    struct per{
        char name;
        int weight;
    };
    per z , q , s , l;
    z.name = 'z' ; q.name = 'q' ; s.name = 's' ; l.name = 'l' ; 
    for (int z1 = 1 ; z1 <= 5 ; z1 ++){
        for (int q1 = 1 ; q1 <= 5 ; q1 ++){
            if (q1 == z1) continue;
            for (int s1 = 1 ; s1 <= 5 ; s1 ++){
                if (s1 == q1 || s1 == z1) continue;
                for (int l1 = 1 ; l1 <= 5 ; l1 ++){
                    if (l1 == s1 || l1 == q1 || l1 == z1) continue;
                    bool cc1 = (z1 + q1 == s1 + l1);
                    bool cc2 = (z1 + l1 > s1 + q1);
                    bool cc3 = (z1 + s1 < q1);
                    if (cc1 && cc2 && cc3){
                        z.weight = z1 ; q.weight = q1 ; s.weight = s1 ; l.weight = l1 ; 
                    }
                }
            }
        }
    }
    per people[4] = {z , q , s ,l};// 要先给数组内的per类元素都赋好值，才能去建构per类数组
    for (int i = 1 ; i <= 3 ; i ++){
        for (int j = 0 ; j <= 3 - i ; j ++){
            if (people[j].weight < people[j + 1].weight){
                per temp = people[j];
                people[j] = people[j + 1];
                people[j + 1] = temp;// 对per类元素冒泡排序，temp也应该是per类变量
            }
        }
    }
    for (int i = 1 ; i <= 4 ; i ++){
        cout << people[i - 1].name << " " << people[i - 1].weight * 10 << endl;
    }
    return 0;// 审题：1.不大于50可以为50，2.记得乘以10！！！
}