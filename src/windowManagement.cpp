#include <stdio.h>

struct Window {
    Window *next;
    int id;
    int x;
    int y;
    int w;
    int h;
};

Window *handleMouseClickEvent(Window *wptr, int x, int y) {
    Window *top = wptr;
    Window *up = NULL; //上一个窗口
    while (wptr != NULL) {
        if (!(wptr->x <= x && wptr->y <= y && wptr->x + wptr->w > x && wptr->y + wptr->h > y)) { //点到了
            up = wptr;
            wptr = wptr->next;
            continue;
        }
        printf("%d %d %d\n", wptr->id, x - wptr->x, y - wptr->y);
        if (up == NULL) { //是顶部节点则不需要调换顺序
            return top;
        }
        up->next = wptr->next;
        wptr->next = top;
        return wptr;
    }
    printf("desktop!\n");
    return top;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Window *head = NULL;
    Window *tail = NULL;
    for (int i = 0; i < n; i++) {
        Window *w = new Window;
        scanf("%d%d%d%d%d", &w->id, &w->x, &w->y, &w->w, &w->h);
        w->next = NULL;
        if (head == NULL) {
            head = w;
            tail = w;
            continue;
        }
        tail->next = w;
        tail = w;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        head = handleMouseClickEvent(head, x, y);
    }
}