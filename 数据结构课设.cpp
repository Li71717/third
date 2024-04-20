#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define max 50//这个迷宫最大规格为50*50

int book[max][max] = { 0 };//记录迷宫中的某个点是否已经走过

int intr;//入口所在行
int intc;//入口所在列
int outr;//出口所在行
int outc;//出口所在列

//迷宫问题每个格子能走的四个方向
int nextstep[4][2] = {
				   {0,1},//向右走
				   {1,0},//向下走
				   {0,-1},//向左走
				   {-1,0} //向上走
};

//迷宫的各类信息
typedef struct maze
{
	int row;//行
	int column;//列
	int record[max][max];//迷宫的位置的信息
}*Mz;
Mz initialize;

//dfs算法所需的各种条件如下

int minstep = 999;//从入口到出口的最短路径

int sk = 0;//这两个数据在深度优先遍历中代表着目前已有多少个栈已经产生
int sr = 0;

int sg = 0;//用来记录走出迷宫的路径条数

int st = 0;//用来记录符合条件的走出迷宫的路径条数

int temp1 = -1;//这两个整形数据用来记录暂时从队列中输出的数据
int temp2 = -1;

//用栈来存储我走出迷宫的路线
typedef struct Link
{
	int rx;//行坐标
	int ry;//列坐标
	int rw;//只会在record3中起作用它用来记录这个到达出口的路径长度
	struct Link* next;
}Link, * LK;
typedef LK Lstack;
Lstack record2[max * max * max * max];//在dfs算法中储存每个节点对应的属于自己的栈
Lstack record3[max * max * max * max];//用来存储那些符合条件的走出迷宫的栈
Lstack temp;//用它来实现两个栈数据的转移，在Ctrl函数中应用
Lstack tempp;//用它来正序输出从出口到入口的路线，在DD函数中应用

//栈的初始化
void creat(Lstack& L)
{
	L = (Lstack)malloc(sizeof(Link));
	L = NULL;
}

//入栈
void push(Lstack& L, int x, int y)
{
	Link* p;
	p = (Lstack)malloc(sizeof(Link));
	p->rx = x;
	p->ry = y;
	p->next = L;
	L = p;
}

//出栈
int pop(Lstack& L)
{
	if (L == NULL)
	{
		return 0;
	}
	Link* p;
	p = L;
	temp1 = p->rx;
	temp2 = p->ry;
	L = L->next;
	free(p);
	return 1;
}

//栈的便利，在刚开始写dfs中为了看到某个栈经过变化后所对应的各个节点数据。在本次实际的迷宫问题中，不会运行
void BL(Lstack s)
{
	Link* p = s;
	while (p != NULL)
	{
		cout << '(' << p->rx << ',' << p->ry << ')' << "->";
		p = p->next;
	}
	cout << "Only FAYN" << endl;
}

//栈的便利2(使用rw的作用)，在找到能走出迷宫的路径后，对符合要求的路径进行标记
void BLL(Lstack& s, int x)
{
	Link* p = s;
	while (p != NULL)
	{
		p->rw = x;
		p = p->next;
	}
}

//栈的销毁
void destory(Lstack& s)
{
	Link* p;
	while (s != NULL)
	{
		p = s;
		s = s->next;
		free(p);
	}
}

//栈的复制，通过Lstack temp这个中转站进行两个栈的数据复制
void Ctrl(Lstack c, Lstack& d)
{
	int x, y;
	Link* e;
	e = c;
	while (e != NULL)
	{
		x = e->rx;
		y = e->ry;
		push(temp, x, y);
		e = e->next;
	}
	while (temp != NULL)
	{
		x = temp->rx;
		y = temp->ry;
		push(d, x, y);
		temp = temp->next;
	}
}

//颠倒得到正序路径，通过Lstack tempp将得到的走出迷宫的路径进行逆序
void DD(Lstack s)
{
	int x, y;
	Link* p;
	p = s;
	while (p != NULL)
	{
		x = p->rx;
		y = p->ry;
		push(tempp, x, y);
		p = p->next;
	}
}

//深度优先遍历整个迷宫，并能在试探中找到所有能走出这个迷宫的路径
int turn = 0;//刚开始走迷宫的时候是一个转折点
void dfs(int x, int y, int step)
{
	creat(record2[sk]);//创建这个节点对应的栈
	if (turn == 0)
	{
		push(record2[sk++], x, y);//入口的前面并没有节点，故不会存在栈来让入口对应的栈进行复制，所以对于入口直接将它对应的节点信息进行入栈
		turn = 1;
	}
	else
	{
		Ctrl(record2[sr++], record2[sk]);//这个节点的前面一定存在着一个节点，故将它上个结点的栈内信息进行复制
		push(record2[sk++], x, y);//存入这个节点对应的节点信息
	}
	if (x == outr && y == outc)//找到了出口
	{
		sg++;//能走出迷宫的路径+1
		if (step <= minstep)//判断是否需要改变最短路径的长度
		{
			minstep = step;
			creat(record3[st]);
			Ctrl(record2[sk - 1], record3[st]);//符合条件的话就将本次走出迷宫的栈存入
			BLL(record3[st], step);//将对应的最短路径长度的值赋给本次走出迷宫的栈的全体成员
			st++;
		}
		//既然找到了走出迷宫的路径，那就将它输出
		cout << "Finding Something->";
		DD(record2[sk - 1]);//sk-1是因为我们走到出口的时候在将出口的信息放入它的栈后，sk进行了++，但很明显并没有record2[sk]栈，它根本不存在，通过DD函数将此次路径逆序赋值给Lstack tempp;
		while (1)
		{
			if (pop(tempp))
			{
				cout << '(' << temp1 << ',' << temp2 << ')' << "->";//输出路径
			}
			else break;
		}
		cout << "You" << endl;
		destory(tempp);	//销毁
		return;
	}
	
	//枚举4种走法
	int rx, ry, k;
	for (int k = 0; k < 4; k++)
	{
		//计算下一个点的坐标
		rx = x + nextstep[k][0];
		ry = y + nextstep[k][1];

		//判断此点是否越界，越界则进行下一个方向的尝试
		if (rx >= initialize->row || rx < 0 || ry >= initialize->column || ry < 0)
		{
			continue;
		}

		//判断该点是否为障碍物或者已经在路径中
		if (initialize->record[rx][ry] == 0 && book[rx][ry] == 0)
		{
			book[rx][ry] = 2;//这个点已经走过
			dfs(rx, ry, step + 1);//尝试下一个点
			book[rx][ry] = 0;//尝试结束，取消这个点的标记
			destory(record2[--sk]);//既然这个点我们已经在回溯中尝试过了这个节点的全部走法，那么就将它对应的栈删除
			sr--;
		}
	}
	return;
}

//bfs算法所需的各种条件如下

//迷宫的各类信息
struct note
{
	int bx;//行坐标
	int by;//列坐标
	int bf;//记录深度
	int bs;//记录路径长度
};

struct print_way
{
	int px;//行坐标
	int	py;//列坐标
};

//主函数
int main()
{
	string choice;

	initialize = (Mz)malloc(sizeof(maze));

	creat(temp);
	creat(tempp);

	cout << "来走个only belong for you own 的迷宫吧" << endl;
	cout << endl;
	cout << "请输入迷宫的行数:";
	cin >> initialize->row;
	cout << "请输入迷宫的列数:";
	cin >> initialize->column;
	cout << endl;
	cout << "请开始输入迷宫图吧" << endl;
	for (int i = 0; i < initialize->row; i++)
	{
		for (int j = 0; j < initialize->column; j++)
		{
			cin >> initialize->record[i][j];
			book[i][j] = 0;
		}
	}
	cout << endl;
	cout << "请输入这个迷宫的入口:";
	cin >> intr >> intc;
	cout << "请输入这个迷宫的出口:";
	cin >> outr >> outc;
	cout << endl;

	cout << "现在有两种way走出这个迷宫:" << endl;
	cout << "如果你想很详细的了解your迷宫，你可以选择输入'particular'." << endl;
	cout << "如果你想尽快走出迷宫，你可以选择输入'sketchy'." << endl;
	cout << "嘿嘿，别急着输入，如果你觉得小孩子才做选择的话，那'both'是你的绝配哦" << endl;
    
	while (1)
	{
		cout << endl << "请输入您的选择吧:";
		cin >> choice;
		if (choice == "particular" || choice == "both")
		{
			cout <<endl<< "Detailed maze path is as follows:";
			book[intr][intc] = 2;
			//开始走迷宫
			cout << endl << "找到的所有能走出迷宫的路径如下:" << endl;
			dfs(intr, intc, 1);
			cout << "共有" << sg << "条路径" << endl;

			//输出最短步数
			cout << endl << "走出迷宫的最少步数为:";
			cout << minstep - 1 << "步" << endl;

			//输出所有最短路径对应的路线
			int k = 0;
			cout << endl << "找到的所有最短路径如下:" << endl;
			for (int i = 0; i < st; i++)
			{
				if (record3[i]->rw == minstep)
				{
					k++;
					DD(record3[i]);
					cout << "The End Is->";
					while (1)
					{
						if (pop(tempp))
						{
							cout << '(' << temp1 << ',' << temp2 << ')' << "->";
						}
						else break;
					}
					cout << "Only FAYN" << endl;
					destory(tempp);
				}
			}
			cout << "共有" << k << "条路径" << endl;
			if (choice == "particular")
			{
				break;
			}
		}
		if (choice == "sketchy" || choice == "both")
		{
			if (choice == "both")
			{
				cout << "————————————————————————————————————————————————————————————";
			}
            cout << endl << "The path out of the maze is follows:";
			struct note bfs[2501];//按广度优先遍历时的顺序存储节点数据
			struct print_way LiMQ[100];//找到出口时进行回溯时存储节点位置信息
			int head;
			int tail;
			int tx, ty, flag;
			head = 1;
			tail = 1;
			bfs[tail].bx = intr;//存储入口的数据
			bfs[tail].by = intc;
			bfs[tail].bf = 0;
			bfs[tail].bs = 0;
			tail++;
			book[intr][intc] = 2;
			flag = 0;
			while (head < tail)
			{
				for (int i = 0; i < 4; i++)
				{
					//计算下一个点的坐标
					tx = bfs[head].bx + nextstep[i][0];
					ty = bfs[head].by + nextstep[i][1];

					//判断此点是否越界，越界则进行下一个方向的尝试
					if (tx < 0 || tx >= initialize->row || ty < 0 || ty >= initialize->column)
					{
						continue;
					}

					//判断该点是否为障碍物或者已经在路径中
					if (initialize->record[tx][ty] == 0 && book[tx][ty] == 0)
					{
						book[tx][ty] = 2;//这个点已经走过
						bfs[tail].bx = tx;//将这个节点的数据记录
						bfs[tail].by = ty;
						bfs[tail].bf = head;//记录这个节点的直接前驱
						bfs[tail].bs = bfs[head].bs + 1;//走到这个节点的步数
						tail++;
					}
					//找到出口跳出for循环
					if (tx == outr && ty == outc)
					{
						flag = 2;//改变标记
						break;
					}
				}
				//跳出while循环
				if (flag == 2)
				{
					break;
				}
				head++;
			}

			//输出最短步数
			cout << endl << "走出迷宫的最少步数为:";
			cout << bfs[tail - 1].bs << "步" << endl;
			cout << endl << "找到的最短路径如下:" << endl;
			int LL = 0;
			int QQ = 0;
			LiMQ[LL].px = outr;//记录出口信息
			LiMQ[LL].py = outc;
			initialize->record[outr][outc] = QQ++;//为"sketchy"特别准备的路线标记
			int MM = bfs[tail - 1].bf;//MM其实就是每个节点对应的head;
			//开始回溯
			while (MM != 0)
			{
				LL++;
				LiMQ[LL].px = bfs[MM].bx;
				LiMQ[LL].py = bfs[MM].by;
				initialize->record[LiMQ[LL].px][LiMQ[LL].py] = QQ++;
				MM = bfs[MM].bf;
			}
			//输出最短路径对应的路线
			cout << "The End Is->";
			for (int lyt = bfs[tail - 1].bs; lyt >= 0; lyt--)
			{
				cout << '(' << LiMQ[lyt].px << ',' << LiMQ[lyt].py << ')' << "->";
			}
			cout << "Only FAYN" << endl;
			//输出存在路线标记的迷宫
			cout << endl << "这么想走出迷宫的话就再帮帮你吧，按着脚下的数字走吧，数字是递减的哦，入口的的数字就是走出迷宫的最小步数" << endl;
			for (int lmq = 0; lmq < initialize->row; lmq++)
			{
				for (int Lmq = 0; Lmq < initialize->column; Lmq++)
				{
					cout << initialize->record[lmq][Lmq] << ' ';
					if (Lmq == initialize->column - 1)
					{
						cout << endl;
					}
				}
			}
			break;
		}
		//输入的选择不能正确匹配
		if (choice != "particular" && choice != "sketchy" && choice != "both")
		{
			cout<<endl << "输入的选择好像不对呢，请重新输入您的选择哦" << endl;
		}
	}
	cout << endl << "期待你喜欢自己的迷宫，每个人都有属于自己的路，希望你能在寻找迷宫出口的过程中也能在生活中找到真正的自己，下次再见！"<<endl;
	system("pause");
	return 0;
}

/*
7 7
0 1 0 0 0 0 0 
0 1 0 1 0 1 0
0 0 0 0 0 1 0
0 0 0 1 0 0 1
1 0 0 1 0 0 0
0 0 0 1 0 1 0
0 1 0 0 0 1 0
0 2
5 4
*/

//csp认证考试
