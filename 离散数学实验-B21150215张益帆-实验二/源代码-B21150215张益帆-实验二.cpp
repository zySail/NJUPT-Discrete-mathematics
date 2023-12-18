#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

int num; //矩阵大小
const int N = 10; //最大矩阵
int matrix[N][N];
//memset(matrix, 0 , sizeof(matrix));

void input(){
    cout << "请输入关系矩阵大小 : " << endl;
    cin >> num;
    cout << "请输入关系矩阵 : " << endl;
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            cin >> matrix[i][j];    
        }
    }
}

void output()
{
	cout << "关系矩阵 : " << endl;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void reflexivity()//判断自反性
{
	int count = 0;
	for (int i = 0; i < num; i++){
		if (matrix[i][i] == 1){
			count++;
		}
	}
	if (count == num){
		cout << "满足自反性" << endl;
	}
	else{
		cout << "不满足自反性" << endl;
	}
}

void irreflexivity(){//判断反自反性
	int count = 0;
	for (int i = 0; i < num; i++){
		if (matrix[i][i] == 1){
			count++;
		}
	}
	if (count != num){
		cout << "满足反自反性" << endl;
	}
	else{
		cout << "不满足反自反性" << endl;
	}	
}

void symmetry()//判断对称性
{
	int count = 0;
	for (int i = 0; i < num - 1; i++)
		for (int j = 0; j < num - i; j++){
			if ((i != j) && (matrix[i][j] == matrix[j][i])){
				count++;
			}			
		}
	//cout << "cout = " << count << endl;
	if (count == num * (num - 1) / 2){ 
		cout << "满足对称性" << endl;
	}
	else
	{
		cout << "不满足对称性"<< endl;
	}
}


void assymmetry(){//判断反对称性
	int count = 0;
	for (int i = 0; i < num - 1; i++)
		for (int j = 0; j < num - i; j++){
			if ((i != j) && (matrix[i][j] == matrix[j][i])){
				count++;
			}			
		}
	if (count != num * (num - 1) / 2){ 
		cout << "满足反对称性" << endl;
	}
	else
	{
		cout << "不满足反对称性"<< endl;
	}
}


void transtivity()//判断传递性
{
	int flag = 1;
	for(int i = 0; i < num; i++){
		for(int j = 0; j < num; j++){ //遍历矩阵 
			if(matrix[i][j] == 1){
				for(int k = 0; k < num; k++){
					if(matrix[j][k] == 1){
						if(matrix[i][k] != 1){
							flag = 0;
						}
					}
				}
			}
		}
	}
	if(flag == 1){
		cout << "满足反传递性" << endl;
	}
	else{
		cout << "不满足反传递性" << endl;
	}

}

int main(){
    input();
    output();
    reflexivity();
    irreflexivity(); 
    symmetry();
    assymmetry();
    transtivity(); 
    return 0;
}
