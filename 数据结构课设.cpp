#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define max 50//����Թ������Ϊ50*50

int book[max][max] = { 0 };//��¼�Թ��е�ĳ�����Ƿ��Ѿ��߹�

int intr;//���������
int intc;//���������
int outr;//����������
int outc;//����������

//�Թ�����ÿ���������ߵ��ĸ�����
int nextstep[4][2] = {
				   {0,1},//������
				   {1,0},//������
				   {0,-1},//������
				   {-1,0} //������
};

//�Թ��ĸ�����Ϣ
typedef struct maze
{
	int row;//��
	int column;//��
	int record[max][max];//�Թ���λ�õ���Ϣ
}*Mz;
Mz initialize;

//dfs�㷨����ĸ�����������

int minstep = 999;//����ڵ����ڵ����·��

int sk = 0;//������������������ȱ����д�����Ŀǰ���ж��ٸ�ջ�Ѿ�����
int sr = 0;

int sg = 0;//������¼�߳��Թ���·������

int st = 0;//������¼�����������߳��Թ���·������

int temp1 = -1;//��������������������¼��ʱ�Ӷ��������������
int temp2 = -1;

//��ջ���洢���߳��Թ���·��
typedef struct Link
{
	int rx;//������
	int ry;//������
	int rw;//ֻ����record3����������������¼���������ڵ�·������
	struct Link* next;
}Link, * LK;
typedef LK Lstack;
Lstack record2[max * max * max * max];//��dfs�㷨�д���ÿ���ڵ��Ӧ�������Լ���ջ
Lstack record3[max * max * max * max];//�����洢��Щ�����������߳��Թ���ջ
Lstack temp;//������ʵ������ջ���ݵ�ת�ƣ���Ctrl������Ӧ��
Lstack tempp;//��������������ӳ��ڵ���ڵ�·�ߣ���DD������Ӧ��

//ջ�ĳ�ʼ��
void creat(Lstack& L)
{
	L = (Lstack)malloc(sizeof(Link));
	L = NULL;
}

//��ջ
void push(Lstack& L, int x, int y)
{
	Link* p;
	p = (Lstack)malloc(sizeof(Link));
	p->rx = x;
	p->ry = y;
	p->next = L;
	L = p;
}

//��ջ
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

//ջ�ı������ڸտ�ʼдdfs��Ϊ�˿���ĳ��ջ�����仯������Ӧ�ĸ����ڵ����ݡ��ڱ���ʵ�ʵ��Թ������У���������
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

//ջ�ı���2(ʹ��rw������)�����ҵ����߳��Թ���·���󣬶Է���Ҫ���·�����б��
void BLL(Lstack& s, int x)
{
	Link* p = s;
	while (p != NULL)
	{
		p->rw = x;
		p = p->next;
	}
}

//ջ������
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

//ջ�ĸ��ƣ�ͨ��Lstack temp�����תվ��������ջ�����ݸ���
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

//�ߵ��õ�����·����ͨ��Lstack tempp���õ����߳��Թ���·����������
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

//������ȱ��������Թ�����������̽���ҵ��������߳�����Թ���·��
int turn = 0;//�տ�ʼ���Թ���ʱ����һ��ת�۵�
void dfs(int x, int y, int step)
{
	creat(record2[sk]);//��������ڵ��Ӧ��ջ
	if (turn == 0)
	{
		push(record2[sk++], x, y);//��ڵ�ǰ�沢û�нڵ㣬�ʲ������ջ������ڶ�Ӧ��ջ���и��ƣ����Զ������ֱ�ӽ�����Ӧ�Ľڵ���Ϣ������ջ
		turn = 1;
	}
	else
	{
		Ctrl(record2[sr++], record2[sk]);//����ڵ��ǰ��һ��������һ���ڵ㣬�ʽ����ϸ�����ջ����Ϣ���и���
		push(record2[sk++], x, y);//��������ڵ��Ӧ�Ľڵ���Ϣ
	}
	if (x == outr && y == outc)//�ҵ��˳���
	{
		sg++;//���߳��Թ���·��+1
		if (step <= minstep)//�ж��Ƿ���Ҫ�ı����·���ĳ���
		{
			minstep = step;
			creat(record3[st]);
			Ctrl(record2[sk - 1], record3[st]);//���������Ļ��ͽ������߳��Թ���ջ����
			BLL(record3[st], step);//����Ӧ�����·�����ȵ�ֵ���������߳��Թ���ջ��ȫ���Ա
			st++;
		}
		//��Ȼ�ҵ����߳��Թ���·�����Ǿͽ������
		cout << "Finding Something->";
		DD(record2[sk - 1]);//sk-1����Ϊ�����ߵ����ڵ�ʱ���ڽ����ڵ���Ϣ��������ջ��sk������++���������Բ�û��record2[sk]ջ�������������ڣ�ͨ��DD�������˴�·������ֵ��Lstack tempp;
		while (1)
		{
			if (pop(tempp))
			{
				cout << '(' << temp1 << ',' << temp2 << ')' << "->";//���·��
			}
			else break;
		}
		cout << "You" << endl;
		destory(tempp);	//����
		return;
	}
	
	//ö��4���߷�
	int rx, ry, k;
	for (int k = 0; k < 4; k++)
	{
		//������һ���������
		rx = x + nextstep[k][0];
		ry = y + nextstep[k][1];

		//�жϴ˵��Ƿ�Խ�磬Խ���������һ������ĳ���
		if (rx >= initialize->row || rx < 0 || ry >= initialize->column || ry < 0)
		{
			continue;
		}

		//�жϸõ��Ƿ�Ϊ�ϰ�������Ѿ���·����
		if (initialize->record[rx][ry] == 0 && book[rx][ry] == 0)
		{
			book[rx][ry] = 2;//������Ѿ��߹�
			dfs(rx, ry, step + 1);//������һ����
			book[rx][ry] = 0;//���Խ�����ȡ�������ı��
			destory(record2[--sk]);//��Ȼ����������Ѿ��ڻ����г��Թ�������ڵ��ȫ���߷�����ô�ͽ�����Ӧ��ջɾ��
			sr--;
		}
	}
	return;
}

//bfs�㷨����ĸ�����������

//�Թ��ĸ�����Ϣ
struct note
{
	int bx;//������
	int by;//������
	int bf;//��¼���
	int bs;//��¼·������
};

struct print_way
{
	int px;//������
	int	py;//������
};

//������
int main()
{
	string choice;

	initialize = (Mz)malloc(sizeof(maze));

	creat(temp);
	creat(tempp);

	cout << "���߸�only belong for you own ���Թ���" << endl;
	cout << endl;
	cout << "�������Թ�������:";
	cin >> initialize->row;
	cout << "�������Թ�������:";
	cin >> initialize->column;
	cout << endl;
	cout << "�뿪ʼ�����Թ�ͼ��" << endl;
	for (int i = 0; i < initialize->row; i++)
	{
		for (int j = 0; j < initialize->column; j++)
		{
			cin >> initialize->record[i][j];
			book[i][j] = 0;
		}
	}
	cout << endl;
	cout << "����������Թ������:";
	cin >> intr >> intc;
	cout << "����������Թ��ĳ���:";
	cin >> outr >> outc;
	cout << endl;

	cout << "����������way�߳�����Թ�:" << endl;
	cout << "����������ϸ���˽�your�Թ��������ѡ������'particular'." << endl;
	cout << "������뾡���߳��Թ��������ѡ������'sketchy'." << endl;
	cout << "�ٺ٣��������룬��������С���Ӳ���ѡ��Ļ�����'both'����ľ���Ŷ" << endl;
    
	while (1)
	{
		cout << endl << "����������ѡ���:";
		cin >> choice;
		if (choice == "particular" || choice == "both")
		{
			cout <<endl<< "Detailed maze path is as follows:";
			book[intr][intc] = 2;
			//��ʼ���Թ�
			cout << endl << "�ҵ����������߳��Թ���·������:" << endl;
			dfs(intr, intc, 1);
			cout << "����" << sg << "��·��" << endl;

			//�����̲���
			cout << endl << "�߳��Թ������ٲ���Ϊ:";
			cout << minstep - 1 << "��" << endl;

			//����������·����Ӧ��·��
			int k = 0;
			cout << endl << "�ҵ����������·������:" << endl;
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
			cout << "����" << k << "��·��" << endl;
			if (choice == "particular")
			{
				break;
			}
		}
		if (choice == "sketchy" || choice == "both")
		{
			if (choice == "both")
			{
				cout << "������������������������������������������������������������������������������������������������������������������������";
			}
            cout << endl << "The path out of the maze is follows:";
			struct note bfs[2501];//��������ȱ���ʱ��˳��洢�ڵ�����
			struct print_way LiMQ[100];//�ҵ�����ʱ���л���ʱ�洢�ڵ�λ����Ϣ
			int head;
			int tail;
			int tx, ty, flag;
			head = 1;
			tail = 1;
			bfs[tail].bx = intr;//�洢��ڵ�����
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
					//������һ���������
					tx = bfs[head].bx + nextstep[i][0];
					ty = bfs[head].by + nextstep[i][1];

					//�жϴ˵��Ƿ�Խ�磬Խ���������һ������ĳ���
					if (tx < 0 || tx >= initialize->row || ty < 0 || ty >= initialize->column)
					{
						continue;
					}

					//�жϸõ��Ƿ�Ϊ�ϰ�������Ѿ���·����
					if (initialize->record[tx][ty] == 0 && book[tx][ty] == 0)
					{
						book[tx][ty] = 2;//������Ѿ��߹�
						bfs[tail].bx = tx;//������ڵ�����ݼ�¼
						bfs[tail].by = ty;
						bfs[tail].bf = head;//��¼����ڵ��ֱ��ǰ��
						bfs[tail].bs = bfs[head].bs + 1;//�ߵ�����ڵ�Ĳ���
						tail++;
					}
					//�ҵ���������forѭ��
					if (tx == outr && ty == outc)
					{
						flag = 2;//�ı���
						break;
					}
				}
				//����whileѭ��
				if (flag == 2)
				{
					break;
				}
				head++;
			}

			//�����̲���
			cout << endl << "�߳��Թ������ٲ���Ϊ:";
			cout << bfs[tail - 1].bs << "��" << endl;
			cout << endl << "�ҵ������·������:" << endl;
			int LL = 0;
			int QQ = 0;
			LiMQ[LL].px = outr;//��¼������Ϣ
			LiMQ[LL].py = outc;
			initialize->record[outr][outc] = QQ++;//Ϊ"sketchy"�ر�׼����·�߱��
			int MM = bfs[tail - 1].bf;//MM��ʵ����ÿ���ڵ��Ӧ��head;
			//��ʼ����
			while (MM != 0)
			{
				LL++;
				LiMQ[LL].px = bfs[MM].bx;
				LiMQ[LL].py = bfs[MM].by;
				initialize->record[LiMQ[LL].px][LiMQ[LL].py] = QQ++;
				MM = bfs[MM].bf;
			}
			//������·����Ӧ��·��
			cout << "The End Is->";
			for (int lyt = bfs[tail - 1].bs; lyt >= 0; lyt--)
			{
				cout << '(' << LiMQ[lyt].px << ',' << LiMQ[lyt].py << ')' << "->";
			}
			cout << "Only FAYN" << endl;
			//�������·�߱�ǵ��Թ�
			cout << endl << "��ô���߳��Թ��Ļ����ٰ����ɣ����Ž��µ������߰ɣ������ǵݼ���Ŷ����ڵĵ����־����߳��Թ�����С����" << endl;
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
		//�����ѡ������ȷƥ��
		if (choice != "particular" && choice != "sketchy" && choice != "both")
		{
			cout<<endl << "�����ѡ����񲻶��أ���������������ѡ��Ŷ" << endl;
		}
	}
	cout << endl << "�ڴ���ϲ���Լ����Թ���ÿ���˶��������Լ���·��ϣ��������Ѱ���Թ����ڵĹ�����Ҳ�����������ҵ��������Լ����´��ټ���"<<endl;
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

//csp��֤����
