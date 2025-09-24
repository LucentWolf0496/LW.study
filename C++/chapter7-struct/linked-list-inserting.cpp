#include <iostream>
using namespace std;

// 数字链表结构
struct numST {
    int num;            // 整型数据
    numST *next;        // 下一个节点指针
};

// 有序插入函数
void insert(numST *&pHead, numST *pNode) {
    // 情况1：链表为空
    if (pHead == NULL) {
        pHead = pNode;
        return;
    }
    
    // 情况2：插入到链表头部
    if (pNode->num <= pHead->num) {
        pNode->next = pHead;
        pHead = pNode;
        return;
    }
    
    // 情况3：在链表中查找插入位置
    numST *r = pHead;           // 前驱指针
    numST *q = pHead->next;     // 当前指针
    
    while (q != NULL) {
        if (pNode->num > q->num) {
            r = q;
            q = q->next;
        } else {
            break;              // 找到插入位置
        }
    }
    
    // 执行插入操作
    r->next = pNode;
    pNode->next = q;
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
    numST *pMHead = NULL;       // 链表头指针
    numST *pMMode = NULL;       // 待插入节点
    
    // 创建初始链表：5->10->15->NULL
    pMHead = new numST;
    pMHead->next = new numST;
    pMHead->next->next = new numST;
    
    pMHead->num = 5;
    pMHead->next->num = 10;
    pMHead->next->next->num = 15;
    pMHead->next->next->next = NULL;
    
    // 创建待插入节点
    pMMode = new numST;
    pMMode->num = 12;
    pMMode->next = NULL;
    
    // 插入并显示结果
    insert(pMHead, pMMode);
    print(pMHead);
    
    return 0;
}