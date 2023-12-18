#include <iostream>
using namespace std;
class Cover {
	int input; //��������
	int num; //��������
	int part_num; //ƫ������
	int nums[100]; //ȫ������
	int part[1000][2]; //ƫ���ϵ
	void count_num(); //������ȡ
	void partial_order(); //ƫ���ж�
	void cover_relation(); //��ס�ж�
	bool find(int a, int b, int n);
	void bool_(); //���ж�
public:
	Cover(int p) {
		input = p;
		num = 0;
		part_num = 0;
	}
	void cover() {
		count_num();
		partial_order();
		cover_relation();
		bool_();
	}
};

int main() {
	int n;
	cout << "��������" << endl;
	cin >> n;
	Cover c(n);
	c.cover();
}

void Cover::count_num() {
	for (int i = 1; i <= input; i++) {
		if (input % i == 0) {
			num++;
			nums[num - 1] = i;
		}
	}
}

void Cover::partial_order() {
	cout << "ƫ���ϵ��";
	for (int i = 0; i<num; i++) {
		for (int j = i; j<num; j++) {
			if (nums[j] % nums[i] == 0) {
				part[part_num][0] = nums[i];
				part[part_num][1] = nums[j];
				part_num++;
				cout << "<" << nums[i] << "," << nums[j] << ">";
			}
		}
	}
	cout << endl;
}

void Cover::cover_relation() {
	cout << "��ס��ϵ��";
	int part_n[1000];
	for (int i = 0; i<part_num; i++) {
		for (int j = 0; j<part_num; j++) {
			if (part[i][1] == part[j][0]) {
				for (int k = 0; k<part_num; k++) {
					if ((part[k][0] == part[i][0]) && (part[k][1] == part[j][1]) && (k != j) &&
					(k != i))
					part_n[k] = -1;
				}
			}
		}
	}	
	for (int i = 0; i<part_num; i++) {
		if (part_n[i] != -1 && part[i][0] != part[i][1])
		cout << "<" << part[i][0] << "," << part[i][1] << ">";
	}
	cout << endl;
}

bool Cover::find(int a, int b, int n)
{
	int temp;
	if (a < b)
	{
		temp = a;
		a = b;
		b = temp;
	}
	int p = a, q = b, r = 0, min, max;
	r = p%q;
	while (r)
	{
		p = q;
		q = r;
		r = p%q;
	}
	min = a*b / q;
	max = q;
	if (min == n&&max == 1)
		return true;
	else
		return false;
}

void Cover::bool_() {
	bool b[100];
	for (int i = 0; i < num; i++){
		for (int j = i; j < num; j++) {
			if (find(nums[i], nums[j], input)) {
				b[i] = true;
				b[j] = true;
				break;
			}
		}
	}
	int flag = 1;
	for (int i = 0; i < num; i++)
		if (!b[i])
			flag = 0;
	if (flag) {
		cout << "���в���" << endl;
	}
	else {
		cout << "�����в���" << endl;
	}
}
