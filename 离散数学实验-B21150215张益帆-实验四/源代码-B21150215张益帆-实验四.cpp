#include<iostream>
#include<cstdlib>
#include<ctime>
#define N 10
using namespace std;

void generateAdj(int n);
void findPath(int v,int n);
void judge(int n);

int adj[N][N];
int index = 0;
int m = 0;    //����
int path[N] = { 0 };  //��¼·��
int vis[N][N] = { 0 };   //��¼���Ƿ��߹�

int main()
{
	int n;
	cout << "�����������:";
	cin >> n;
	generateAdj(n);
	judge(n);
	return 0;
}

void generateAdj(int n)  //�����ڽӾ���
{
	srand((int)time(0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			adj[i][j] = adj[j][i] = rand() % 2;     //�Գ��������
		}
		adj[i][i] = 0;
	}
	cout << "������ɵ��ڽӾ���Ϊ��"<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout<<adj[i][j]<<' ';
		}
		cout << '\n';
	}
}

void findPath(int v,int n)
{
	if (index == m+1)
	{
		cout << path[0];
		for (int i = 1; i < index; i++)
		{
			cout << "->" << path[i];
		}
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (adj[v][i] == 1 && vis[v][i] == 0)   //�б߲���û�߹�
		{
			vis[v][i] = vis[i][v] = 1;
			path[index++] = i+1;
			findPath(i,n);	//�ݹ���·
		}
	}
}

void judge(int n)
{
	int tmp[N][N] = { 0 };
	int b[N][N] = { 0 };
	int a[N][N] = { 0 };
	int deg[N] = { 0 };   //��¼ÿ�����Ķ���
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = b[i][j] = adj[i][j];
		}
	}
	for (int t = 1; t < n; t++)
	{
		for (int i = 0; i < n; i++)   
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					tmp[i][j] += a[i][k] * adj[k][j];   //����˷�
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				a[i][j] = tmp[i][j];
				b[i][j] += a[i][j];
				tmp[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (b[i][j] == 0)
			{
				cout << "��ͼ���ǰ�ŷ��ͼҲ����ŷ��ͼ��" << endl;
				return;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			deg[i] += adj[i][j];			
		}
		if (deg[i] % 2 != 0)  //����������Ľ�����
		{
			cnt += 1;
		}
		m += deg[i];
	}
	m = (int)(m / 2);  //������� 
	if (cnt == 0)
	{
		cout << "��ͼ��ŷ��ͼ��"<<endl;
		cout << "һ��ŷ����·Ϊ��" << endl;
		path[index++] = 1;
		findPath(0,n);
		return;
	}
	if (cnt == 2)
	{
		cout << "��ͼ�ǰ�ŷ��ͼ��"<<endl;
		cout << "һ��ŷ��·Ϊ��" << endl;
		for (int i = 0; i < n; i++)
		{
			if (deg[i] % 2 != 0)  //���������㿪ʼ��·
			{
				path[index++] = i+1;
				findPath(i,n);
				break;
			}
		}
		return;
	}
	cout<< "��ͼ���ǰ�ŷ��ͼҲ����ŷ��ͼ��"<<endl;
}
