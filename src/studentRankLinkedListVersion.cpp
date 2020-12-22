/*
这就很尴尬了
我一开始写作业的时候把标题“结构体与链表”看成了“数据结构与链表”
认为所有作业都是拿链表写的
结果就是这次作业写的极为痛苦
现在我把它们都改掉了，就留下这一题给大家看看吧
*/

#include <math.h>
#include <stdio.h>

struct Student {
    Student *next;
    char id[10];
    char name[10];
    int age;
    char sex;              // 性别 'F' 或 'M'
    double homeworkGrade;  // 平时作业
    double midExamGrade;   // 期中成绩
    double practiceGrade;  // 实验题
    double finalExamGrade; // 期末成绩
    double finalGrade;     // 总成绩
};

//A>B?
bool compareGrade(Student *A, Student *B) {
    double a = A->finalGrade;
    double b = B->finalGrade;
    if (fabs(a - b) < 1e-6) {
        char *sa = A->id;
        char *sb = B->id;
        int i = 0;
        while (sa[i] != 0 && sb[i] != 0) {
            if (sa[i] == sb[i]) {
                i++;
                continue;
            }
            break;
        }
        return sa[i] < sb[i];
    }
    return a > b;
}

int main() {
    int n;
    Student *head = NULL;
    Student *tail = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        Student *s = new Student;
        scanf("%s %s %d %c %lf %lf %lf %lf",
              &s->id, &s->name, &s->age, &s->sex,
              &s->homeworkGrade, &s->midExamGrade,
              &s->practiceGrade, &s->finalExamGrade);
        s->next = NULL;
        s->finalGrade = 0.15 * s->homeworkGrade + 0.15 * s->midExamGrade + 0.1 * s->practiceGrade + 0.6 * s->finalExamGrade;
        if (tail == NULL) {
            head = s;
            tail = s;
            continue;
        }
        if (compareGrade(s, head)) {
            s->next = head;
            head = s;
            continue;
        }
        if (compareGrade(tail, s)) {
            tail->next = s;
            tail = s;
            continue;
        }
        Student *stuptr = head;
        while (stuptr->next != NULL) {
            if (compareGrade(stuptr, s) && compareGrade(s, stuptr->next)) {
                s->next = stuptr->next;
                stuptr->next = s;
                break;
            }
            stuptr = stuptr->next;
        }
    }
    Student *stuptr = head;
    while (stuptr != NULL) {
        printf("%-10s%-10s%2d %c %6.2f\n", stuptr->id, stuptr->name, stuptr->age, stuptr->sex, stuptr->finalGrade);
        stuptr = stuptr->next;
    }
    stuptr = head;
    while (stuptr != NULL) {
        if (stuptr->sex == 'F') {
            printf("%-10s%-10s%2d %c %6.2f\n", stuptr->id, stuptr->name, stuptr->age, stuptr->sex, stuptr->finalGrade);
        }
        stuptr = stuptr->next;
    }
}