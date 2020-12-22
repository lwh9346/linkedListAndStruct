#include <math.h>
#include <stdio.h>
#include <string.h>

struct Student {
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

//A<B?
bool compareGrade(Student *A, Student *B) {
    double a = A->finalGrade;
    double b = B->finalGrade;
    if (fabs(a - b) > 1e-6) {
        return a < b;
    }
    //这里有同学可能会说strcmp其实可以比较字典序
    //但是这依赖于具体编译器实现，属于未定义行为，不应该使用
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
    return sa[i] > sb[i];
}

int main() {
    int n;
    scanf("%d", &n);
    Student s[100];
    for (int i = 0; i < n; i++) {
        scanf("%s %s %d %c %lf %lf %lf %lf",
              &s[i].id, &s[i].name, &s[i].age, &s[i].sex,
              &s[i].homeworkGrade, &s[i].midExamGrade,
              &s[i].practiceGrade, &s[i].finalExamGrade);
        s[i].finalGrade = 0.15 * s[i].homeworkGrade + 0.15 * s[i].midExamGrade + 0.1 * s[i].practiceGrade + 0.6 * s[i].finalExamGrade;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compareGrade(&s[j], &s[j + 1])) {
                Student tmp;
                memcpy(&tmp, &s[j], sizeof(Student));
                memcpy(&s[j], &s[j + 1], sizeof(Student));
                memcpy(&s[j + 1], &tmp, sizeof(Student));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%-10s%-10s%2d %c %6.2f\n", s[i].id, s[i].name, s[i].age, s[i].sex, s[i].finalGrade);
    }
    for (int i = 0; i < n; i++) {
        if (s[i].sex == 'F') {
            printf("%-10s%-10s%2d %c %6.2f\n", s[i].id, s[i].name, s[i].age, s[i].sex, s[i].finalGrade);
        }
    }
}