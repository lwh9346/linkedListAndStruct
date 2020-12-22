#include <stdio.h>
#include <string.h>

struct Mouse {
    int weight;
    char colour[11];
};

// compareMouse returns true if a<b
bool compareMouse(Mouse a, Mouse b) { return a.weight < b.weight; }

int main() {
    int n;
    scanf("%d", &n);
    Mouse m[100];
    for (int i = 0; i < n; i++) {
        scanf("%d%s", &m[i].weight, &m[i].colour);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compareMouse(m[j], m[j + 1])) {
                Mouse tmp = m[j];
                m[j] = m[j + 1];
                m[j + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%s\n", m[i].colour);
    }
}