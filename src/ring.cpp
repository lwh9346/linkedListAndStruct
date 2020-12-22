#include <stdio.h>

struct ringNode {
    ringNode *previous;
    ringNode *next;
    int id;
};

bool requiredNumber(int i) {
    if (i % 7 == 0) {
        return true;
    }
    while (i > 0) {
        if (i % 10 == 7) {
            return true;
        }
        i /= 10;
    }
    return false;
}

int main() {
    int n;
    scanf("%d", &n);
    ringNode *ringBegin = NULL;
    ringNode *ringEnd = NULL;
    for (int i = 0; i < n; i++) {
        ringNode *rn = new ringNode;
        rn->next = NULL;
        rn->id = i + 1;
        if (ringBegin == NULL) {
            ringBegin = rn;
            ringEnd = rn;
            continue;
        }
        ringEnd->next = rn;
        rn->previous = ringEnd;
        ringEnd = rn;
    }
    ringEnd->next = ringBegin;
    ringBegin->previous = ringEnd;
    int num = 1;
    while (true) {
        if (ringBegin->next == ringBegin) {
            printf("%d\n", ringBegin->id);
            break;
        }
        if (requiredNumber(num)) {
            printf("%d\n", ringBegin->id);
            ringBegin->previous->next = ringBegin->next;
            ringBegin->next->previous = ringBegin->previous;
        }
        ringBegin = ringBegin->next;
        num++;
    }
}