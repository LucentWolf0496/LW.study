#include <iostream>
using namespace std;

struct monkey {
    int num;            // 猴子编号
    monkey *next;       // 下一个猴子指针
};

monkey *head, *tail;    // 链表头和尾指针

// 创建循环链表
void create(int nn) {
    int i;
    monkey *p, *q;
    
    p = new monkey;
    p->num = 1;
    p->next = NULL;
    head = p;
    q = p;
    
    // 创建剩余猴子节点
    for (i = 2; i <= nn; i++) {
        p = new monkey;
        p->num = i;
        q->next = p;    // 连接到链表尾部
        q = p;
        p->next = NULL;
    }
    
    tail = q;
    tail->next = head;  // 形成循环链表
}

// 选择猴王函数
void select(int mm) {
    int x = 0;
    monkey *p, *q;
    q = tail;           // q指向尾节点
    
    do {
        p = q->next;    // p指向要处理的节点
        x = x + 1;
        
        if (x % mm == 0) {  // 需要删除的节点
            cout << "被删掉的猴子号为" << p->num << "号\n";
            q->next = p->next;  // 删除p节点
            delete p;
            p = NULL;
        } else {
            q = p;      // 移动到下一个节点
        }
    } while (q != q->next);  // 只剩一个节点时结束
    
    head = q;           // 剩下的就是猴王
}

int main() {
    int n, m;
    head = NULL;
    
    cout << "请输入猴子数\n";
    cin >> n;
    
    cout << "请输入间隔m\n";
    cin >> m;
    
    create(n);          // 创建循环链表
    select(m);          // 选择猴王
    cout << "猴王是" << head->num << "号\n";
    
    delete head;        // 释放最后一个节点
    return 0;
}