# 链表与结构体

## 写在开头

讲义中的题目都是从易到难排序的。请不要因为我花括号不换行就骂我变态。我提交代码的时候用的是`c++`，会用到一些比如`bool`类型之类的东西，希望大家能自己转换（`bool`型直接改成`int`型就可以通过编译了）。

**我代码里面的注释不是废话，不要直接跳过了，它们是讲义的一部分！**

**我代码里面的注释不是废话，不要直接跳过了，它们是讲义的一部分！**

**我代码里面的注释不是废话，不要直接跳过了，它们是讲义的一部分！**

## 结构体

先从结构体开始讲吧。为什么需要结构体呢？按我的理解就是将几个数据绑定在一起，方便各种操作。同时，使用结构体还可以提升代码可读性，可以创建一些抽象程度更高的东西（比如`Student`结构体）。

```c++
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
```

### 题目1：小白鼠排队——结构体基础

> 题目：N只小白鼠(1 < N < 100)，每只鼠头上戴着一顶有颜色的帽子。现在称出每只白鼠的重量，要求按照白鼠重量从大到小的顺序输出它们头上帽子的颜色。帽子的颜色用“red”，“blue”等字符串来表示。不同的小白鼠可以戴相同颜色的帽子。白鼠的重量用整数表示。
>
> 输入：输入第一行为一个整数N，表示小白鼠的数目。
> 下面有N行，每行是一只白鼠的信息。第一个为不大于100的正整数，表示白鼠的重量；第二个为字符串，表示白鼠的帽子颜色，字符串长度不超过10个字符。白鼠的重量各不相同。
>
> 输出：N行，按照白鼠的重量从大到小的顺序输出白鼠的帽子颜色，每行一个颜色。`printf("%s\n",colour);`

直接上代码

```c++
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
```

这里就展示了结构体的基础使用：定义结构体，之后把它当作一种普通的数据类型来使用就好了。我这边就用简单的冒泡排序了，反正也不会超时。

### 题目2：学生排序——结构体基础

> 题目：输入学生记录的内容，根据平时作业（百分制，占总成绩的15%），期中考试（百分制，占总成绩的15%），实验题（百分制，占总成绩的10%），期末考试（百分制，占总成绩的60%），求出每个学生的总成绩，并按总成绩由高到低排序输出记录。再将其中女同学的记录输出。
>
> 输入：输入第一行是学生的人数n（1 <= n <= 100)
> 接下来有n行，每行对应一个学生的信息，每行包含以空格分开的以下字段：
> （学生学号 姓名 年龄 性别 平时成绩 期中成绩 实验题 期末成绩）学生学号、姓名不超过9个字符，并且不包含空格；性别是一个字符'F'（女生）或'M'（男生）；平时成绩、期中成绩、实验题、期末成绩均为[0, 100]之间的浮点数。
>
> 输出：`printf("%-10s%-10s%2d %c %6.2f\n", id, name, age, sex, finalGrade);`~~文字是苍白的。~~

题目已经给出了学生的结构体：

```c++
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
```

~~感觉把这两道题放在一起是为了告诉我们：“学生就是小白鼠”。~~

说起来其实就是把上一题的小白鼠换成学生，然后修改一下对应的比较函数就好了。这里比较函数比较麻烦~~（烂双关）~~，重点讲解一下。

```c++
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
    while (sa[i] != 0 && sb[i] != 0) {//跳转到第一个不相同的字符
        if (sa[i] == sb[i]) {
            i++;
            continue;
        }
        break;
    }
    return sa[i] > sb[i];//比较，这句其实可以写在while循环里面，替换break语句
}
```

首先要注意的是浮点数相同的判断。由于浮点数计算并不是完全准确的因此在最后比较结果的时候也需要考虑误差，我们这边就设置一个允许的误差范围，两数相减小于这个误差就认为两数相等，即`fabs(a - b) < 1e-6`.

然后是字典序的比较。有的编译器在`strcmp`函数里面的确是会比较字符串的字典序，但是这东西好像在c语言规范里面是没有规定的，所以我们得自己写一个，比较方法其实也不是很麻烦。要比较两个字符的字典序其实比较两个字符的`ascii`码即可，`ascii`码小者字典序靠前。对于字符串的话，比较第一组不相同的字符即可。

上面这段代码里面我用的流程控制技巧叫做提前退出，如果两数不相等就直接返回大小关系，提前结束函数，避免一大堆`if-else`嵌套，对于提升代码可读性有很大的帮助。

剩下的代码和小白鼠的差不多，就是输出有点麻烦，题目里面给的是`iostream`的输出代码，我这边贴一下用`stdio.h`的输出代码。

```c++
printf("%-10s%-10s%2d %c %6.2f\n", s[i].id, s[i].name, s[i].age, s[i].sex, s[i].finalGrade);
```

## 链表

链表是比较基础的一种数据结构，掌握了几个技巧之后也不是很难了。

### 题目1：统计学生信息

> 题目：包括若干行，每一行都是一个学生的信息，如：`00630018 zhouyan m 20 10.0 28#460`输入的最后以"end"结束，要求将这些行倒序输出。

这题主要就是考察最基本的链表创建和读取，没什么难点，直接开始写就是了。

```c++
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
```

这里检测`end`的代码还是用了之前说的提前退出的做法。

遍历链表中的元素有个套路，代码如下：

```c++
Node *tmp = head;
while (tmp != NULL) {
	// 随便干点啥
    foo(tmp);
    bar(tmp);
    // 移向下一个节点
    tmp = tmp->next;
}
```

### 题目2：删除数组中的元素——数组删改

> 题目：给定N个整数，将这些整数中与M相等的删除。
>
> 输入：输入包含3行：第一行是一个整数n(1<=n<=200000)，代表数组中元素的个数。第二行包含n个整数，代表数组中的n个元素。每个整数之间用空格分隔；每个整数的取值在32位有符号整数范围以内。第三行是一个整数k，代表待删除元素的值（k的取值也在32位有符号整数范围内）。
>
> 输出：将数组内所有待删除元素删除以后，输出数组内的剩余元素的值，每个整数之间用空格分隔。

我在群里看同学代码还有自己写代码的时候发现了几个问题：第一个是不加头节点导致链表各种操作变得极为复杂，第二个是不懂得保存尾指针导致给链表增加元素变得麻烦且效率低下。

这里建议大家都用有头节点的链表，这样头指针所指向的节点就不会是`NULL`了，删除链表存放了数据的第一个节点时也不需要特别讨论了，可以让代码简洁很多。没有头指针的情况下，如果要删除第一个节点，你就得特别讨论，修改头指针而不是上一个节点（因为没有上一个节点），这两个东西类型不一样，你得单独写一下代码，就麻烦死了。有了头节点之后你就可以把第一个有数据的节点当成普通节点来看待了。

创建链表的时候要声明一个指向链表尾部的指针，添加新节点就直接添加到链表尾部，并且更新一下这个指向尾部的指针。不要每次都沿着链表一步步爬下去找链表尾部，麻烦得很还效率低下。

创建链表的代码如下，加入了一个头节点。

```c++
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
```

接下来是删除元素：

```c++
int numberToDelete;
scanf("%d", &numberToDelete);
node *tmp = head;
while (tmp->next != NULL) {
    if (tmp->next->value == numberToDelete) {
        node *d = tmp->next;
        tmp->next = tmp->next->next;
        delete (d);// 别忘了删除元素的时候回收内存
        continue;
    }
    tmp = tmp->next;
}
```

这是有头节点的情况，判断每个节点下一个节点就好了（为什么不删除当前节点？因为当前节点你不好删，你不知道当前节点的上一个节点是谁，也就没法修改它的`link`了）。如果没有头节点的话代码就会变得很恶心，我已经删掉了，有热心同学的话可以贡献一下自己的代码，和我这个比较一下。

输出部分跟第一题一个套路，不过因为有了头节点，所以我们输出以及检测的都是下一个节点（也可以一开始就给`tmp`赋值为`head->next`，这样更简洁，我这里就不修改了，给大家做一个反面教材，改过的代码在`src`里）。

```c++
tmp = head;// 把临时指针重置一下
while (tmp->next != NULL) {
    printf("%d", tmp->next->value);
    printf(tmp->next->next == NULL ? "\n" : " ");
    tmp = tmp->next;
}
```

提一句三元运算符`A?B:C`，如果`A`为`true`那么值等于`B`，否则等于`C`。

最后是回收内存。

```c++
while (head != NULL) {
    tmp = head;
    head = head->next;
    delete (tmp);
}
```

不回收内存会导致“内存泄漏”，有兴趣的同学可以自行百度（Google）。

### 题目3：窗口管理——链表元素的移动

> **描述**
>
> Windows 操作系统需要管理很多窗口，每个窗口都占据屏幕上的一个矩形区域。窗口的区域可以相互重叠，此时，上层的窗口会把下层的窗口遮挡住。一个窗口没有被其他任何窗口遮挡住的部分称为"可见区域"。
>
> 同时，Windows 还要响应用户的鼠标事件。如果用户在某个窗口的"可见区域"上单击鼠标，系统就要把这个事件通知对应的窗口。同时，如果该窗口目前不在最上层，就要"激活"它，使它成为最上层的窗口，而其他窗口间的遮挡关系则不受影响。如果鼠标点击没有落在任何窗口的区域内，则认为用户点击了"桌面"，所有窗口的遮挡关系都不会变化。
>
> 你的任务就是模拟 Windows 的这个工作过程。
>
> 为了描述窗口的区域，需要引入"屏幕坐标系"的概念，屏幕坐标系的原点在屏幕的左上角，其坐标为(0, 0)，然后从左向右 x 的值递增，从上向下 y 的值递增。显然，屏幕的右下角具有最大的(x, y)坐标值。
>
> 因此，窗口的区域可以用一个四元组 (x, y, w, h) 表示。其中，x 和 y 表示窗口的左上角在"屏幕坐标系"中的坐标，而 w 和 h 则分别表示窗口的宽度和高度。类似"屏幕坐标系"，对于每个窗口，我们都可以定义一个"窗口坐标系"，该窗口的左上角在对应"窗口坐标系"中的坐标为(0, 0)，而其右下角在"窗口坐标系"中的坐标则为 (w-1, h-1)。
>
> 例如，一个窗口的区域为 (2, 3, 2, 3) ，则表示它在"屏幕坐标系"上占据了 (2, 3), (3, 3), (2, 4), (3, 4), (2, 5), (3, 5) 这 6 个点，而在它的"窗口坐标系"则包括 (0, 0), (1, 0), (1, 0), (1, 1), (2, 0), (2, 1) 这 6 个点。
>
> **输入**
>
> 输入数据的第一行是两个正整数 n 和 m，表示共有 n 个窗口和 m 次鼠标点击操作（n <= 1000, m <= 10000）。
>
> 接下去的 n 行依次表示 n 窗口，每行有 5 个整数 id, x, y, w, h。其中，id 是这个窗口的标识；x, y, w, h 分别表示该窗口在"屏幕坐标系"中的坐标、宽度和高度。这 n 个窗口是严格按照遮挡顺序给出的，例如第 1 个给出的窗口位于最顶层，而第 n 个给出的窗口位于最底层。
>
> 接下去的 m 行依次表示 m 次鼠标点击，每行有 2 个整数 x 和 y，表示点击时鼠标在"屏幕坐标系"中的坐标。
>
> **输出**
>
> 你的输出应该有 m 行，每行都对应输入数据中的一次鼠标点击。如果该鼠标点击没有落在任何窗口的区域内，则只需输出"desktop!"即可。
>
> 否则，对于每次点击，要输出三个整数：id, x, y，分别表示被点击的窗口标识、点击时鼠标在该窗口的"窗口坐标系"中的 (x, y) 坐标。

这题比较坑的一点就是判断是否点击到窗口，`x`和`x+w`构成的是左闭右开的区间，`y`同理。

创建链表部分我下一题里面会讲，这里主要讲一下对于点击事件的处理。

```c++
struct Window
{
    Window *next;
    int id;
    int x;
    int y;
    int w;
    int h;
};

Window *handleMouseClickEvent(Window *wptr, int x, int y)
{
    Window *top = wptr;
    Window *up = NULL;//上一个窗口，加这个东西是因为我没有用头节点
    while (wptr != NULL)
    {
        if (wptr->x <= x && wptr->y <= y && wptr->x + wptr->w > x && wptr->y + wptr->h > y) //点到了
        {
            printf("%d %d %d\n", wptr->id, x - wptr->x, y - wptr->y);
            if (up == NULL) //是顶部节点则不需要调换顺序
            {
                return top;
            }
            up->next = wptr->next;
            wptr->next = top;
            return wptr;
        }
        up = wptr;
        wptr = wptr->next;
    }
    printf("desktop!\n");
    return top;
}
```

先记录一下顶部节点和上一个节点（加这个东西是因为我没有用头节点）。要是点到了，不管三七二十一，先打印出需要的结果再说。如果这个节点就是顶部节点，那就直接返回它（返回链表），不是的话就把这个节点作为新的顶部节点，返回；没点到的话就去到下一层，直到碰到桌面。这里我没有用提前退出和头节点的技巧，导致代码的缩进深度超过了3层，达到了4层，影响了代码可读性，大家可以试着修改一下（利用了提前退出的代码见`src`）。

创建没有头节点的链表的方法见代码，不管需要说明的是我并不推荐这样做。

### 题目4：数字7游戏——循环链表

> 题目：元旦晚会上，有n个学生围坐成一圈，开始玩一种数字7游戏。围坐成一圈的学生按顺时针顺序编号，第一个学生的编号为1，最后一个学生的编号为n。第一个学生从1开始报数，按顺时针方向，下一个学生接着报下一个数。每当有学生报出来的数是7的倍数，或者是一个含有数字7的数时，则该学生出列退出游戏，下一个学生接着报下一个数。当剩下最后一个学生时，这个学生要为大家表演一个节目。
>
> 输入：一个整数，学生人数。
>
> 输出：每行一个整数，表示该回合被踢出队列的学生编号。

这个其实是改了一下规则的约瑟夫游戏。我代码里面用了双向链表，方便删除数组元素。由于是循环链表，所以就不加入头节点了（没有必要）。

首先创建一个循环链表（我这里用的是双向链表）。最后一步记得把头尾相接。

```c++
struct ringNode {
    ringNode *previous;
    ringNode *next;
    int id;
};

int main() {
    int n;
    scanf("%d", &n);
    ringNode *ringBegin = NULL;
    ringNode *ringEnd = NULL;
    for (int i = 0; i < n; i++) {
        ringNode *rn = new ringNode;
        rn->next = NULL;
        rn->id = i + 1;
        if (ringBegin == NULL) { // 由于没有头节点，需要判断一下头指针是否为空指针
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
    ...;
}
```

然后是判断是否为满足条件的数字的函数，我有见过有同学用字符串来写的，问题也不是很大。

```c++
bool requiredNumber(int i) {
    if (i % 7 == 0) { // 是否能被7整除
        return true;
    }
    while (i > 0) { // 是否含有7，做法就是不断地取出每一位来比较
        if (i % 10 == 7) {
            return true;
        }
        i /= 10;
    }
    return false; // 不满足条件就false了
}
```

接下来是报数删除小朋友部分。

```c++
int num = 1;
while (true) {
    if (ringBegin->next == ringBegin) { // 如果首尾相接，说明只剩一个节点了，输出走人
        printf("%d\n", ringBegin->id);
        break;
    }
    if (requiredNumber(num)) { // 报到了就输出，踢掉
        printf("%d\n", ringBegin->id);
        ringBegin->previous->next = ringBegin->next;
        ringBegin->next->previous = ringBegin->previous;
    }
    ringBegin = ringBegin->next; // 依题意，不管有没有报到都要挪到下一个人
    num++; // 报数
}
```

完整代码见`src`文件夹。

## 总结

这次作业里，我用到了三种链表形式：带头节点的单向链表、不带头节点的单向链表、不带头结点的双向循环链表。同学们可以通过这几种不同的链表形式体会一下差异，理解一下我为什么推荐使用带有头节点的链表。