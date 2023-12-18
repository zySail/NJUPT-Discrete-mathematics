#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

int num; //�����С
const int N = 10; //������
int matrix[N][N];
//memset(matrix, 0 , sizeof(matrix));

void input(){
    cout << "�������ϵ�����С : " << endl;
    cin >> num;
    cout << "�������ϵ���� : " << endl;
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            cin >> matrix[i][j];    
        }
    }
}

void output()
{
	cout << "��ϵ���� : " << endl;
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

void reflexivity()//�ж��Է���
{
	int count = 0;
	for (int i = 0; i < num; i++){
		if (matrix[i][i] == 1){
			count++;
		}
	}
	if (count == num){
		cout << "�����Է���" << endl;
	}
	else{
		cout << "�������Է���" << endl;
	}
}

void irreflexivity(){//�жϷ��Է���
	int count = 0;
	for (int i = 0; i < num; i++){
		if (matrix[i][i] == 1){
			count++;
		}
	}
	if (count != num){
		cout << "���㷴�Է���" << endl;
	}
	else{
		cout << "�����㷴�Է���" << endl;
	}	
}

void symmetry()//�ж϶Գ���
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
		cout << "����Գ���" << endl;
	}
	else
	{
		cout << "������Գ���"<< endl;
	}
}


void assymmetry(){//�жϷ��Գ���
	int count = 0;
	for (int i = 0; i < num - 1; i++)
		for (int j = 0; j < num - i; j++){
			if ((i != j) && (matrix[i][j] == matrix[j][i])){
				count++;
			}			
		}
	if (count != num * (num - 1) / 2){ 
		cout << "���㷴�Գ���" << endl;
	}
	else
	{
		cout << "�����㷴�Գ���"<< endl;
	}
}


void transtivity()//�жϴ�����
{
	int flag = 1;
	for(int i = 0; i < num; i++){
		for(int j = 0; j < num; j++){ //�������� 
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
		cout << "���㷴������" << endl;
	}
	else{
		cout << "�����㷴������" << endl;
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
