#include <cstdio>
#include <cstring>
#include <windows.h>
#include <iostream>
using namespace std;

string Org_Formula;//�û���������⹫ʽ
string Simp_Formula;//���û���������⹫ʽ��->��<->ת��Ϊ>��~
string Suffix_Formula;//���򻯺��ʽ��ת��Ϊ��׺���ʽ
string PCNF;//����ȡ��ʽ
string PDNF;//����ȡ��ʽ
char ch[15] = "()PQRST!&|-><";//���û������ʽ�Ӽ�ʱ��Ҫ�����

int p, q, r, s, t;//forѭ����ӡ��ֵ��ʱʹ��
int a, b, res;//�߼�����ʱʹ�ã�����a==1, b==0������And��������ȡ���������ʱ��resΪ0��
int v = 0;
int var_cnt;//�����û�����ı����ĸ�����������ͬ�ı����ĸ������ظ�����һ����

//��һ������ģ��ջ
class  Stack
{
public:
    Stack(int mSize)
    {
        maxtop = mSize - 1; //maxtopΪst�����±����ֵ��mSizeΪst����Ԫ�ظ���
        st = new char[mSize];//��̬�ڴ����
        top = -1;
    }
    ~Stack()//�����������ͷ�st[]�ڴ�
    {
        delete[] st;
    }

    bool Push(char x)//ģ����ջ
    {
        if (top == maxtop)//���ջ���������false
            return false;
        st[++top] = x;
        return true;
    }
    bool Pop()
    {
        if (top == -1)
            return false;
        top--;//ģ���ջ
        return true;
    }
    char Top()
    {
        return st[top];//ģ��ȡջ��Ԫ��
    }
private:
    int top;
    char* st;
    int maxtop;
};

void Not();//������
void And();//��ȡ����
void Or();//��ȡ����
void If();//��������
void Iif();//˫��������
void count_varcnt(); //�����û�����ı����ĸ�����������ͬ�ı����ĸ������ظ�����һ����
void InputANDjudge_formula();// �û���������⹫ʽ�����м�飬������쳣���룬������棬����������
bool Jude_canin(char);//�ж�������ܷ���ջ
void Change_to_sufexp();//�����������⹫ʽת��Ϊ��׺���ʽ
void Calculate();//�����߼�����
void Print();//��ӡ���
void Not_Not(char);//�ж��Ƿ�Ϊ������
void Switch_Operator(char);//��������ȼ����ж��ܷ��ջ
bool Enh_Robustness();//��ǿ����³����
Stack Simp_stack(200);//����һ�������Simp_stack

int main()
{
    while (1)
    {
        do
        {
            InputANDjudge_formula();//����⵽�û��Ƿ�����ʱ�����û��ٴ�����
        } while (!Enh_Robustness());
        if (Org_Formula == "Over")//�û�����Over�ɽ�������
        {
            cout << "\\\\*^o^*// ллʹ�� \\\\*^o^*//" << endl;
            system("pause");
            return 0;
        }

        count_varcnt();//������û�����ı����ĸ���
        Change_to_sufexp();//�����������⹫ʽת��Ϊ�沨�����ʽ
        Print();//��ӡ
    }
    return 0;
}
void InputANDjudge_formula()
{
    char str1[100] = { 0 }, str2[100]; //str1Ϊ����ʽ�ӣ�str2Ϊ������ʽ�ӣ�����������ʽ�Ӹ���Simp_Formula
    int cnt = 0;
    cout << "���������⹫ʽ:(����Over�ɽ�������)" << endl;
    gets(str1); //�ɻ󣺽�str1, str2��Ϊȫ�ֱ�����������   Ҫ��gets(),��Ȼ³���Բ�ǿ
    for (int i = 0; i < strlen(str1);)//���û���������⹫ʽ��->��<->ת����>��<
    {
        if (str1[i] == '-') { str2[cnt++] = '>'; i += 2; }
        else if (str1[i] == '<') { str2[cnt++] = '~'; i += 3; }
        else { str2[cnt++] = str1[i]; i += 1; }
    }
    str2[cnt++] = '\0';//��Ҫ�����ַ������Ͻ�����Ƿ�
    Org_Formula = str1;// ԭʼ����
    Simp_Formula = str2; // �����зǡ���ȡ����ȡ�Ĺ�ʽ
}
bool Enh_Robustness()
{
    bool Rob = true;
    if (Org_Formula == "Over")
        return true;
    for (int i = 0; i < Org_Formula.length(); i++)
    {
        if (strchr(ch, Org_Formula[i]) == nullptr)
        {
            cout << "�����쳣�������Ƿ��пո�Сд�ֻ�Ƿ��ַ�" << endl << endl;
            Org_Formula = "";
            return false;
        }
    }
    return Rob;
}
void count_varcnt()
{
    int Count = 0;
    bool P = true, Q = true, R = true, S = true, T = true;
    for (int i = 0; i < Simp_Formula.length(); i++)
    {
        if (Simp_Formula[i] == 'P' && P) { Count++; P = !P; }
        else if (Simp_Formula[i] == 'Q' && Q) { Count++; Q = !Q; }
        else if (Simp_Formula[i] == 'R' && R) { Count++; R = !R; }
        else if (Simp_Formula[i] == 'S' && S) { Count++; S = !S; }
        else if (Simp_Formula[i] == 'T' && T) { Count++; T = !T; }
        else  continue;
    }
    var_cnt = Count;
}
bool Jude_canin(char out)//
{
    char in = Simp_stack.Top();
    int i, o;
    switch (in)
    {
    case '#':i = 0; break;
    case '(':i = 1; break;
    case '~':i = 3; break;
    case '>':i = 5; break;
    case '|':i = 7; break;
    case '&':i = 9; break;
    case '!':i = 11; break;
    case ')':i = 12; break;
    }
    switch (out)
    {
        //case '#':o = 0; break;
    case '(':o = 12; break;
    case '~':o = 2; break;
    case '>':o = 4; break;
    case '|':o = 6; break;
    case '&':o = 8; break;
    case '!':o = 10; break;
    case ')':o = 1; break;
    }
    if (i < o) { return true; }
    else { return false; }
}
void Change_to_sufexp()
{
    string Tmp = "";// ��ʱ�Ŀ��ַ���
    Simp_stack.Push('#');
    for (int i = 0; i < Simp_Formula.length(); i++)
    {
        if (Simp_Formula[i] == 'P' || Simp_Formula[i] == 'Q' || Simp_Formula[i] == 'R' || Simp_Formula[i] == 'S')
        {
            Tmp = Tmp + Simp_Formula[i];
            continue;
        }
        if (Jude_canin(Simp_Formula[i]))
            Simp_stack.Push(Simp_Formula[i]);
        else if (Simp_Formula[i] == ')')
        {
            while (Simp_stack.Top() != '(')
            {
                Tmp = Tmp + Simp_stack.Top();
                Simp_stack.Pop();
            }
            Simp_stack.Pop();
        }
        else
        {
            do
            {
                Tmp = Tmp + Simp_stack.Top();
                Simp_stack.Pop();
            } while (!Jude_canin(Simp_Formula[i]));
            Simp_stack.Push(Simp_Formula[i]);
        }
    }
    while (Simp_stack.Top() != '#')
    {
        Tmp = Tmp + Simp_stack.Top();
        Simp_stack.Pop();
    }
    Simp_stack.Pop();
    Suffix_Formula = Tmp;
}
void Calculate()
{
    if (var_cnt == 2) //������Ԫ
    {
        for (int i = 0; i < Suffix_Formula.length(); i++)
        {
            if (Suffix_Formula[i] == 'P' || Suffix_Formula[i] == 'Q')
            {
                v = Suffix_Formula[i] == 'P' ? p : q;
                Simp_stack.Push(v);
                continue;
            }
            Not_Not(Suffix_Formula[i]);
            Switch_Operator(Suffix_Formula[i]);
        }
    }
    if (var_cnt == 3) //������Ԫ
    {
        for (int i = 0; i < Suffix_Formula.length(); i++)
        {
            if (Suffix_Formula[i] == 'P' || Suffix_Formula[i] == 'Q' || Suffix_Formula[i] == 'R')
            {
                v = Suffix_Formula[i] == 'P' ? p : Suffix_Formula[i] == 'Q' ? q : r;
                Simp_stack.Push(v);
                continue;
            }
            Not_Not(Suffix_Formula[i]);
            Switch_Operator(Suffix_Formula[i]);
        }
    }
    if (var_cnt == 4) //�ĸ���Ԫ
    {
        for (int i = 0; i < Suffix_Formula.length(); i++)
        {

            if (Suffix_Formula[i] == 'P' || Suffix_Formula[i] == 'Q' || Suffix_Formula[i] == 'R' || Suffix_Formula[i] == 'S')
            {
                v = Suffix_Formula[i] == 'P' ? p : Suffix_Formula[i] == 'Q' ? q : Suffix_Formula[i] == 'R' ? r : s;
                Simp_stack.Push(v);
                continue;
            }
            Not_Not(Suffix_Formula[i]);
            Switch_Operator(Suffix_Formula[i]);
        }
    }
    if (var_cnt == 5) //�����Ԫ
    {
        for (int i = 0; i < Suffix_Formula.length(); i++)
        {
            if (Suffix_Formula[i] == 'P' || Suffix_Formula[i] == 'Q' || Suffix_Formula[i] == 'R' || Suffix_Formula[i] == 'S' || Suffix_Formula[i] == 'T')
            {
                v = Suffix_Formula[i] == 'P' ? p : Suffix_Formula[i] == 'Q' ? q : Suffix_Formula[i] == 'R' ? r : Suffix_Formula[i] == 'S' ? s : t;
                Simp_stack.Push(v);
                continue;
            }
            Not_Not(Suffix_Formula[i]);
            Switch_Operator(Suffix_Formula[i]);
        }
    }
}
void Print()
{
    if (var_cnt == 2)
    {
        cout << "��ֵ������" << endl;
        cout << "P\t" << "Q\t" << Org_Formula << endl;
        for (p = 1; p >= 0; p--)
        {
            for (q = 1; q >= 0; q--)
            {
                Calculate();
                if (res == 1)
                    PDNF = PDNF + "(" + (p == 1 ? "P" : "��P") + "��" + (q == 1 ? "Q" : "��Q") + ")" + "��";
                else
                    PCNF = PCNF + "(" + (p == 0 ? "P" : "��P") + "��" + (q == 0 ? "Q" : "��Q") + ")" + "��";
                cout << p << "\t" << q << "\t" << res << endl;
            }
        }
    }
    if (var_cnt == 3)
    {
        cout << "��ֵ������" << endl;
        cout << "P\t" << "Q\t" << "R\t" << Org_Formula << endl;
        for (p = 1; p >= 0; p--)
        {
            for (q = 1; q >= 0; q--)
            {
                for (r = 1; r >= 0; r--)
                {
                    Calculate();
                    if (res == 1)
                        PDNF = PDNF + "(" + (p == 1 ? "P" : "��P") + "��" + (q == 1 ? "Q" : "��Q") + "��" + (r == 1 ? "R" : "��R") + ")" + "��";
                    else
                        PCNF = PCNF + "(" + (p == 0 ? "P" : "��P") + "��" + (q == 0 ? "Q" : "��Q") + "��" + (r == 0 ? "R" : "��R") + ")" + "��";
                    cout << p << "\t" << q << "\t" << r << "\t" << res << endl;
                }
            }
        }
    }
    if (var_cnt == 4)
    {
        cout << "��ֵ������" << endl;
        cout << "P\t" << "Q\t" << "R\t" << "S\t" << Org_Formula << endl;
        for (p = 1; p >= 0; p--)
        {
            for (q = 1; q >= 0; q--)
            {
                for (r = 1; r >= 0; r--)
                {
                    for (s = 1; s >= 0; s--)
                    {
                        Calculate();
                        if (res == 1)
                            PDNF = PDNF + "(" + (p == 1 ? "P" : "��P") + "��" + (q == 1 ? "Q" : "��Q") + "��" + (r == 1 ? "R" : "��R") + "��" + (s == 1 ? "R" : "��R") + ")" + "��";
                        else
                            PCNF = PCNF + "(" + (p == 0 ? "P" : "��P") + "��" + (q == 0 ? "Q" : "��Q") + "��" + (r == 0 ? "R" : "��R") + "��" + (s == 0 ? "R" : "��R") + ")" + "��";
                        cout << p << "\t" << q << "\t" << r << "\t" << s << "\t" << res << endl;
                    }
                }
            }
        }
    }
    if (var_cnt == 5)
    {
        cout << "��ֵ������" << endl;
        cout << "P\t" << "Q\t" << "R\t" << "S\t" << "T\t" << Org_Formula << endl;
        for (p = 1; p >= 0; p--)
        {
            for (q = 1; q >= 0; q--)
            {
                for (r = 1; r >= 0; r--)
                {
                    for (s = 1; s >= 0; s--)
                    {
                        for (t = 1; t >= 0; t--)
                        {
                            Calculate();
                            if (res == 1)
                                PDNF = PDNF + "(" + (p == 1 ? "P" : "��P") + "��" + (q == 1 ? "Q" : "��Q") + "��" + (r == 1 ? "R" : "��R") + "��" + (s == 1 ? "R" : "��R") + ")" + "��";
                            else
                                PCNF = PCNF + "(" + (p == 0 ? "P" : "��P") + "��" + (q == 0 ? "Q" : "��Q") + "��" + (r == 0 ? "R" : "��R") + "��" + (s == 0 ? "R" : "��R") + ")" + "��";
                            cout << p << "\t" << q << "\t" << r << "\t" << s << "\t" << t << "\t" << res << endl;
                        }
                    }
                }
            }
        }
    }

    if (PDNF.length() == 0)
    {
        cout << "����ȡ��ʽ������" << endl;
    }
    else
    {
        PDNF.erase(PDNF.length() - 2);
        cout << "����ȡ��ʽΪ��" << PDNF << endl << endl;
    }
    if (PCNF.length() == 0)
        cout << "����ȡ��ʽ������" << endl;
    else
    {
        PCNF.erase(PCNF.length() - 2);
        cout << "����ȡ��ʽΪ��" << PCNF << endl << endl;
    }
    PDNF = "";
    PCNF = "";
}

void Not_Not(char c)//���ܣ��ж�������Ƿ�Ϊ����Ϊʲô�أ���Ϊ����ǣ�����ֻ��ȡһ��Ԫ��
{                   //����Ļ��ұ���ȡ����Ԫ�ز��ܼ���
    if (c != '!')
    {
        a = Simp_stack.Top();
        Simp_stack.Pop();
        b = Simp_stack.Top();
        Simp_stack.Pop();
    }
}

//ѡ��Ҫ����������
void Switch_Operator(char c)
{
    switch (c)
    {
    case '~':Iif(); break;
    case '>':If(); break;
    case '|':Or(); break;
    case '&':And(); break;
    case '!':Not(); break;
    }
}

//���У�����
void Not()
{
    a = Simp_stack.Top();
    Simp_stack.Pop();
    res = (a == 1 ? 0 : 1);   //һ��Ҫע���ǵ��ں�
    Simp_stack.Push(res);
}

//���к�ȡ����
void And()
{
    res = a * b;
    Simp_stack.Push(res);
}

//������ȡ����
void Or()
{
    res = (a + b == 0) ? 0 : 1;
    Simp_stack.Push(res);
}

//������������
void If()
{
    res = (b == 1 && a == 0) ? 0 : 1;
    Simp_stack.Push(res);
}

//����˫��������
void Iif()
{
    res = (a == b ? 1 : 0);
    Simp_stack.Push(res);
}

