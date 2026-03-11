#include <iostream>
using namespace std;

struct numST {
    int num;
    numST *next;
};

// 删除指定数值的节点
void del(numST *&pHead, int num) {
    numST *p = NULL, *q = NULL;
    
    if (pHead == NULL) return;  // 空链表直接返回
    
    p = pHead;
    
    // 情况1：删除头节点
    if (p->num == num) {
        pHead = p->next;
        delete p;
        return;
    }
    
    q = p->next;
    
    // 遍历查找要删除的节点
    while (q != NULL) {
        if (q->num == num) {    // 找到要删除的节点
            p->next = q->next;
            delete q;
            return;
        }
        
        if (q->num > num) {     // 数值已超过，说明不存在
            return;
        }
        
        p = q;
        q = q->next;
    }
}

// 释放整个链表内存
void release(numST *&pHead) {
    numST *p = NULL, *q = NULL;
    p = pHead;
    
    while (p != NULL) {
        q = p->next;    // 保存下一个节点
        delete p;       // 删除当前节点
        p = q;          // 移动到下一个节点
    }
    
    pHead = NULL;       // 重要！将链表置为空
}

// 显示链表函数
void print(numST *pHead) {
    int k = 0;
    numST *r = pHead;
    
    while (r != NULL) {
        cout.width(2);
        k = k + 1;
        cout << k << " ; " << r->num << endl;
        r = r->next;
    }
}

int main() {
    numST *pMHead = NULL;
    
    // 创建测试链表：5->10->15->NULL
    pMHead = new numST;
    pMHead->next = new numST;
    pMHead->next->next = new numST;
    
    pMHead->num = 5;
    pMHead->next->num = 10;
    pMHead->next->next->num = 15;
    pMHead->next->next->next = NULL;
    
    cout << "原链表：" << endl;
    print(pMHead);
    
    // 删除数值为10的节点
    del(pMHead, 10);
    cout << "删除后链表：" << endl;
    print(pMHead);
    
    // 释放链表内存
    release(pMHead);
    
    return 0;
}