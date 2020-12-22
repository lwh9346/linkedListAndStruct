#include <stdio.h>

struct node {
    node *next;
    int value;
};

int main() {
    //创建链表
    int n;
    scanf("%d", &n);
    node *head = new node;
    head->next = NULL;
    node *end = head;
    for (int i = 0; i < n; i++) {
        node *tmp = new node;
        tmp->next = NULL;
        scanf("%d", &tmp->value);
        end->next = tmp;
        end = tmp;
    }
    //删除元素，检测下一个节点是为了避免删除根节点造成的麻烦
    int numberToDelete;
    scanf("%d", &numberToDelete);
    node *tmp = head;
    while (tmp->next != NULL) {
        if (tmp->next->value == numberToDelete) {
            node *d = tmp->next;
            tmp->next = tmp->next->next;
            delete (d);
            continue;
        }
        tmp = tmp->next;
    }
    //输出
    tmp = head->next;
    while (tmp != NULL) {
        printf("%d", tmp->value);
        printf(tmp->next == NULL ? "\n" : " ");
        tmp = tmp->next;
    }
    //回收内存
    while (head != NULL) {
        tmp = head;
        head = head->next;
        delete (tmp);
    }
}