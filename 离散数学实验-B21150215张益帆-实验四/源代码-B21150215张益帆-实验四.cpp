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
int m = 0;    //边数
int path[N] = { 0 };  //记录路径
int vis[N][N] = { 0 };   //记录边是否被走过

int main()
{
	int n;
	cout << "请输入结点个数:";
	cin >> n;
	generateAdj(n);
	judge(n);
	return 0;
}

void generateAdj(int n)  //生成邻接矩阵
{
	srand((int)time(0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			adj[i][j] = adj[j][i] = rand() % 2;     //对称随机生成
		}
		adj[i][i] = 0;
	}
	cout << "随机生成的邻接矩阵为："<<endl;
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
		if (adj[v][i] == 1 && vis[v][i] == 0)   //有边并且没走过
		{
			vis[v][i] = vis[i][v] = 1;
			path[index++] = i+1;
			findPath(i,n);	//递归找路
		}
	}
}

void judge(int n)
{
	int tmp[N][N] = { 0 };
	int b[N][N] = { 0 };
	int a[N][N] = { 0 };
	int deg[N] = { 0 };   //记录每个结点的度数
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
					tmp[i][j] += a[i][k] * adj[k][j];   //矩阵乘法
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
				cout << "该图不是半欧拉图也不是欧拉图。" << endl;
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
		if (deg[i] % 2 != 0)  //计算奇度数的结点个数
		{
			cnt += 1;
		}
		m += deg[i];
	}
	m = (int)(m / 2);  //计算边数 
	if (cnt == 0)
	{
		cout << "该图是欧拉图。"<<endl;
		cout << "一条欧拉回路为：" << endl;
		path[index++] = 1;
		findPath(0,n);
		return;
	}
	if (cnt == 2)
	{
		cout << "该图是半欧拉图。"<<endl;
		cout << "一条欧拉路为：" << endl;
		for (int i = 0; i < n; i++)
		{
			if (deg[i] % 2 != 0)  //从奇度数结点开始找路
			{
				path[index++] = i+1;
				findPath(i,n);
				break;
			}
		}
		return;
	}
	cout<< "该图不是半欧拉图也不是欧拉图。"<<endl;
}
