#include <iostream>
using namespace std;

// 节目链表结构
struct ActList {
    char ActName[20];    // 节目名
    char director[20];   // 主持人
    int Mtime;          // 节目时长（分钟）
    ActList *next;      // 下一个节点指针
};

ActList *head;          // 链表头指针

// 创建链表函数
ActList *Create() {
    ActList *p = NULL;  // 指向待插入节点
    ActList *q = NULL;  // 指向当前最后一个节点
    head = NULL;        // 初始为空链表
    int time;
    
    cout << "输入节目时长：";
    cin >> time;
    
    while (time != 0) {
        p = new ActList;        // 分配新节点内存
        p->Mtime = time;        // 设置节目时长
        
        cout << "输入节目名称：";
        cin >> p->ActName;
        
        cout << "输入主持人：";
        cin >> p->director;
        
        // 插入到链表
        if (head == NULL) {
            head = p;           // 第一个节点
        } else {
            q->next = p;        // 插入到末尾
        }
        q = p;                  // 更新末尾指针
        
        cout << "输入节目时长：";
        cin >> time;
    }
    
    // 设置链表结束标志
    if (head != NULL) {
        q->next = NULL;
    }
    
    return head;
}

// 显示链表函数
void displayList(ActList *head) {
    cout << "显示节目列表\n";
    while (head != NULL) {
        cout << head->Mtime << endl
             << head->ActName << endl
             << head->director << endl
             << endl;
        head = head->next;
    }
}

int main() {
    displayList(Create());
    return 0;
}