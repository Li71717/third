#include <stdio.h>
#include <stdbool.h>

#define ROW 5
#define COL 5

// 定义迷宫示例
int maze[ROW][COL] = {
    {0, 0, 0, 0, 0},
    {1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0}
};

// 定义坐标结构体
typedef struct {
    int x;
    int y;
} Coordinate;

// 定义栈结构体
typedef struct {
    Coordinate data[ROW * COL];
    int top;
} Stack;

// 初始化栈
void initStack(Stack* s) {
    s->top = -1;
}

// 入栈操作
void push(Stack* s, Coordinate c) {
    s->top++;
    s->data[s->top] = c;
}

// 出栈操作
Coordinate pop(Stack* s) {
    Coordinate c = s->data[s->top];
    s->top--;
    return c;
}

// 判断栈是否为空
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// 判断坐标是否越界或者为墙体
bool isValid(int x, int y) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL && maze[x][y] == 0);
}

// 深度优先遍历算法
bool dfs(int x, int y, Coordinate end, bool visited[ROW][COL], Stack* path) {
    Coordinate cur = { x, y };
    // 如果当前位置为终点，则返回true
    if (cur.x == end.x && cur.y == end.y) {
        push(path, cur);
        return true;
    }
    // 如果当前位置越界、为墙体或者已经访问过，则返回false
    if (!isValid(cur.x, cur.y) || visited[cur.x][cur.y]) {
        return false;
    }
    // 标记当前位置为已访问
    visited[cur.x][cur.y] = true;
    // 将当前位置加入路径
    push(path, cur);
    // 深度优先遍历当前位置的四个邻居
    if (dfs(x + 1, y, end, visited, path) || dfs(x - 1, y, end, visited, path) ||
        dfs(x, y + 1, end, visited, path) || dfs(x, y - 1, end, visited, path)) {
        return true;
    }
    // 如果当前位置无法到达终点，则将当前位置出栈
    pop(path);
    return false;
}

int main() {
    // 定义起点和终点
    Coordinate start = { 0, 0 };
    Coordinate end = { 4, 4 };

    // 定义路径栈
    Stack path_dfs;
    initStack(&path_dfs);

    // 初始化访问标记数组
    bool visited[ROW][COL] = { false };

    // 使用深度优先遍历算法寻找最短路径
    dfs(start.x, start.y, end, visited, &path_dfs);

    // 输出最短路径长度
    printf("深度优先遍历最短路径长度：%d\n", path_dfs.top + 1);

    // 输出最短路径
    printf("深度优先遍历最短路径：\n");
    while (!isEmpty(&path_dfs)) {
        Coordinate cur = pop(&path_dfs);
        printf("(%d, %d) ", cur.x, cur.y);
    }
    printf("\n");

    return 0;
}
/*
首先，我们定义了迷宫示例maze，用一个二维数组表示迷宫的布局。其中，0代表可以通过的通路，1代表墙体或障碍物。
我们定义了一个坐标结构体Coordinate，用来表示迷宫中的坐标位置，包含了x和y两个成员变量。
接着定义了一个栈结构体Stack，其中包含一个Coordinate类型的数组作为栈的数据存储，以及一个整型变量top表示栈顶指针。
initStack函数用于初始化栈，将栈顶指针top设置为-1。
push函数用于将元素入栈，栈顶指针top递增，并将元素存入对应位置。
pop函数用于将栈顶元素出栈，栈顶指针top递减，并返回出栈的元素。
isEmpty函数用于判断栈是否为空，如果栈顶指针top为-1，则说明栈为空。
isValid函数用于判断给定坐标是否在迷宫范围内且为通路。
dfs函数是深度优先遍历算法的实现。它采用递归的方式搜索从起点到终点的路径，并使用栈记录路径。具体实现为：首先检查当前位置是否为终点，如果是则返回true；然后检查当前位置是否越界、为墙体或者已经访问过，如果是则返回false；接着标记当前位置为已访问，并将其加入路径栈；然后深度优先遍历当前位置的四个邻居，如果有一个邻居可以到达终点，则返回true；如果当前位置无法到达终点，则将当前位置出栈并返回false。
在main函数中，我们定义了起点和终点的坐标，以及一个用于记录路径的栈path_dfs。
初始化了一个二维数组visited，用于记录每个位置是否已经访问过。
调用dfs函数进行深度优先遍历，找到从起点到终点的路径。
输出最短路径的长度，即栈path_dfs的元素个数加1。
输出最短路径，通过依次出栈路径栈中的元素来得到路径坐标，并输出。
*/

