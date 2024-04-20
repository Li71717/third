#include <stdio.h>
#include <stdbool.h>

#define ROW 5
#define COL 5

// �����Թ�ʾ��
int maze[ROW][COL] = {
    {0, 0, 0, 0, 0},
    {1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0}
};

// ��������ṹ��
typedef struct {
    int x;
    int y;
} Coordinate;

// ����ջ�ṹ��
typedef struct {
    Coordinate data[ROW * COL];
    int top;
} Stack;

// ��ʼ��ջ
void initStack(Stack* s) {
    s->top = -1;
}

// ��ջ����
void push(Stack* s, Coordinate c) {
    s->top++;
    s->data[s->top] = c;
}

// ��ջ����
Coordinate pop(Stack* s) {
    Coordinate c = s->data[s->top];
    s->top--;
    return c;
}

// �ж�ջ�Ƿ�Ϊ��
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// �ж������Ƿ�Խ�����Ϊǽ��
bool isValid(int x, int y) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL && maze[x][y] == 0);
}

// ������ȱ����㷨
bool dfs(int x, int y, Coordinate end, bool visited[ROW][COL], Stack* path) {
    Coordinate cur = { x, y };
    // �����ǰλ��Ϊ�յ㣬�򷵻�true
    if (cur.x == end.x && cur.y == end.y) {
        push(path, cur);
        return true;
    }
    // �����ǰλ��Խ�硢Ϊǽ������Ѿ����ʹ����򷵻�false
    if (!isValid(cur.x, cur.y) || visited[cur.x][cur.y]) {
        return false;
    }
    // ��ǵ�ǰλ��Ϊ�ѷ���
    visited[cur.x][cur.y] = true;
    // ����ǰλ�ü���·��
    push(path, cur);
    // ������ȱ�����ǰλ�õ��ĸ��ھ�
    if (dfs(x + 1, y, end, visited, path) || dfs(x - 1, y, end, visited, path) ||
        dfs(x, y + 1, end, visited, path) || dfs(x, y - 1, end, visited, path)) {
        return true;
    }
    // �����ǰλ���޷������յ㣬�򽫵�ǰλ�ó�ջ
    pop(path);
    return false;
}

int main() {
    // ���������յ�
    Coordinate start = { 0, 0 };
    Coordinate end = { 4, 4 };

    // ����·��ջ
    Stack path_dfs;
    initStack(&path_dfs);

    // ��ʼ�����ʱ������
    bool visited[ROW][COL] = { false };

    // ʹ��������ȱ����㷨Ѱ�����·��
    dfs(start.x, start.y, end, visited, &path_dfs);

    // ������·������
    printf("������ȱ������·�����ȣ�%d\n", path_dfs.top + 1);

    // ������·��
    printf("������ȱ������·����\n");
    while (!isEmpty(&path_dfs)) {
        Coordinate cur = pop(&path_dfs);
        printf("(%d, %d) ", cur.x, cur.y);
    }
    printf("\n");

    return 0;
}
/*
���ȣ����Ƕ������Թ�ʾ��maze����һ����ά�����ʾ�Թ��Ĳ��֡����У�0�������ͨ����ͨ·��1����ǽ����ϰ��
���Ƕ�����һ������ṹ��Coordinate��������ʾ�Թ��е�����λ�ã�������x��y������Ա������
���Ŷ�����һ��ջ�ṹ��Stack�����а���һ��Coordinate���͵�������Ϊջ�����ݴ洢���Լ�һ�����ͱ���top��ʾջ��ָ�롣
initStack�������ڳ�ʼ��ջ����ջ��ָ��top����Ϊ-1��
push�������ڽ�Ԫ����ջ��ջ��ָ��top����������Ԫ�ش����Ӧλ�á�
pop�������ڽ�ջ��Ԫ�س�ջ��ջ��ָ��top�ݼ��������س�ջ��Ԫ�ء�
isEmpty���������ж�ջ�Ƿ�Ϊ�գ����ջ��ָ��topΪ-1����˵��ջΪ�ա�
isValid���������жϸ��������Ƿ����Թ���Χ����Ϊͨ·��
dfs������������ȱ����㷨��ʵ�֡������õݹ�ķ�ʽ��������㵽�յ��·������ʹ��ջ��¼·��������ʵ��Ϊ�����ȼ�鵱ǰλ���Ƿ�Ϊ�յ㣬������򷵻�true��Ȼ���鵱ǰλ���Ƿ�Խ�硢Ϊǽ������Ѿ����ʹ���������򷵻�false�����ű�ǵ�ǰλ��Ϊ�ѷ��ʣ����������·��ջ��Ȼ��������ȱ�����ǰλ�õ��ĸ��ھӣ������һ���ھӿ��Ե����յ㣬�򷵻�true�������ǰλ���޷������յ㣬�򽫵�ǰλ�ó�ջ������false��
��main�����У����Ƕ����������յ�����꣬�Լ�һ�����ڼ�¼·����ջpath_dfs��
��ʼ����һ����ά����visited�����ڼ�¼ÿ��λ���Ƿ��Ѿ����ʹ���
����dfs��������������ȱ������ҵ�����㵽�յ��·����
������·���ĳ��ȣ���ջpath_dfs��Ԫ�ظ�����1��
������·����ͨ�����γ�ջ·��ջ�е�Ԫ�����õ�·�����꣬�������
*/

