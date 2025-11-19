#include <iostream>
using namespace std;

struct TREE{
    int data;
    struct TREE *L, *R;    //TREE 结构指针
};

//函数 insert，将结点插入二叉树
void insert(TREE *&pRoot, TREE *pNode){
    if (pRoot == NULL) {//如果根结点为空
     pRoot = pNode;    //将结点 pNode 插入根结点
    }
    else {//根结点不为空
        //如果 pNode 结点数据小于等于根结点数据
        if (pNode->data <= pRoot->data)
            insert(pRoot->L, pNode);    //插入左子树
        else    //pNode 结点数据大于根结点数据
            insert(pRoot->R, pNode);    //插入右子树
    }
}

//输出二叉树内容
void print(TREE *pRoot){
    if (pRoot == NULL)    //根或子树根结点为空
        return;
    print(pRoot->L);    //输出左子树内容
    cout << pRoot->data << endl;    //输出数据
    print(pRoot->R);    //输出右子树内容
}

int main(){
    struct TREE *pRoot = NULL, *pNode = NULL;
    cout << "请输入待插入结点的数据\n";
    cout << "如果输入-1 表示插入过程结束\n";
    int temp;
    cin >> temp;
    while (temp != -1){
        //为待插入结点分配内存单元
        pNode = new TREE;
        pNode->data = temp;    //将 temp 赋值给 pNode 结点的数据域
        pNode->L = NULL;    //将 pNode 结点的左右指针域置为空
        pNode->R = NULL;
        insert(pRoot, pNode);    //将 pNode 结点插入到根为 pRoot 的树中
        cout << "请输入待插入结点的数据\n";
        cout << "如果输入-1 表示插入过程结束\n";
        cin >> temp;
    }
    if (pRoot == NULL)    //如果根结点为空
        cout << "这是一棵空树。\n";
    else    //根结点不为空
        print(pRoot);    //输出二叉树内容
    return 0;
}