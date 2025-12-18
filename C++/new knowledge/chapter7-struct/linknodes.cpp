#include <iostream>
using namespace std;

struct LinkNode {
    int value;
    LinkNode* next;
    LinkNode(int val = 0) : value(val), next(nullptr) {}
};

LinkNode* CreateLinkList() {
    int m;
    cin >> m;
    LinkNode* head = nullptr;
    LinkNode* tail = nullptr;
    for (int i = 0; i < m; i++) {
        int val;
        cin >> val;
        LinkNode* newNode = new LinkNode(val);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

LinkNode* MergeLinkList(LinkNode* a, LinkNode* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    LinkNode* head = nullptr;
    LinkNode* current = nullptr;
    if (a->value <= b->value) {
        head = a;
        a = a->next;
    } else {
        head = b;
        b = b->next;
    }
    current = head;
    while (a != nullptr && b != nullptr) {
        if (a->value <= b->value) {
            current->next = a;
            a = a->next;
        } else {
            current->next = b;
            b = b->next;
        }
        current = current->next;
    }
    if (a != nullptr) {
        current->next = a;
    } else {
        current->next = b;
    }
    return head;
}

void DisplayLinkList(LinkNode* linklist) {
    LinkNode* current = linklist;
    bool first = true;
    while (current != nullptr) {
        if (!first) {
            cout << " ";
        }
        cout << current->value;
        current = current->next;
        first = false;
    }
    cout << endl;
}

void DestroyLinkList(LinkNode* linklist) {
    LinkNode* current = linklist;
    while (current != nullptr) {
        LinkNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

int main() {
    LinkNode* list1 = CreateLinkList();
    LinkNode* list2 = CreateLinkList();
    LinkNode* mergedList = MergeLinkList(list1, list2);
    DisplayLinkList(mergedList);
    DestroyLinkList(mergedList);
    return 0;
}