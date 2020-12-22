#include <stdio.h>
#include <string.h>

struct studentInfo {
    studentInfo *next;
    char info[64];
};

int main() {
    studentInfo *root = NULL;
    char tmp[64];
    while (true) {
        gets(tmp);
        if (strcmp(tmp, "end") == 0) {
            break;
        }
        studentInfo *s = new studentInfo;
        strcpy(s->info, tmp);
        s->next = root;
        root = s;
    }
    studentInfo *sp = root;
    while (sp != NULL) {
        printf("%s\n", sp->info);
        sp = sp->next;
    }
}