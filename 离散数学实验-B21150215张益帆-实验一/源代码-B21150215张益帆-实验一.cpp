#include <cstdio>
#include <cstring>
#include <windows.h>
#include <iostream>
using namespace std;

string Org_Formula;//用户输入的命题公式
string Simp_Formula;//将用户输入的命题公式中->和<->转化为>和~
string Suffix_Formula;//将简化后的式子转化为后缀表达式
string PCNF;//主合取范式
string PDNF;//主析取范式
char ch[15] = "()PQRST!&|-><";//把用户输入的式子简化时需要该语句

int p, q, r, s, t;//for循环打印真值表时使用
int a, b, res;//逻辑运算时使用，比如a==1, b==0传到了And（）（合取函数）里，这时候res为0；
int v = 0;
int var_cnt;//计算用户输入的变量的个数（各不相同的变量的个数，重复的算一个）

//用一个类来模拟栈
class  Stack
{
public:
    Stack(int mSize)
    {
        maxtop = mSize - 1; //maxtop为st数组下标最大值，mSize为st数组元素个数
        st = new char[mSize];//动态内存分配
        top = -1;
    }
    ~Stack()//析构函数，释放st[]内存
    {
        delete[] st;
    }

    bool Push(char x)//模拟入栈
    {
        if (top == maxtop)//如果栈溢出，返回false
            return false;
        st[++top] = x;
        return true;
    }
    bool Pop()
    {
        if (top == -1)
            return false;
        top--;//模拟出栈
        return true;
    }
    char Top()
    {
        return st[top];//模拟取栈顶元素
    }
private:
    int top;
    char* st;
    int maxtop;
};

void Not();//非运算
void And();//合取运算
void Or();//析取运算
void If();//条件运算
void Iif();//双条件运算
void count_varcnt(); //计算用户输入的变量的个数（各不相同的变量的个数，重复的算一个）
void InputANDjudge_formula();// 用户输入的命题公式并进行检查，如果有异常输入，输出警告，并重新输入
bool Jude_canin(char);//判断运算符能否入栈
void Change_to_sufexp();//将处理后的命题公式转化为后缀表达式
void Calculate();//进行逻辑运算
void Print();//打印结果
void Not_Not(char);//判断是否为！运算
void Switch_Operator(char);//运算符优先级，判断能否进栈
bool Enh_Robustness();//增强程序鲁棒性
Stack Simp_stack(200);//构造一个类对象，Simp_stack

int main()
{
    while (1)
    {
        do
        {
            InputANDjudge_formula();//当检测到用户非法输入时，让用户再次输入
        } while (!Enh_Robustness());
        if (Org_Formula == "Over")//用户输入Over可结束程序
        {
            cout << "\\\\*^o^*// 谢谢使用 \\\\*^o^*//" << endl;
            system("pause");
            return 0;
        }

        count_varcnt();//计算出用户输入的变量的个数
        Change_to_sufexp();//将处理后的命题公式转化为逆波兰表达式
        Print();//打印
    }
    return 0;
}
void InputANDjudge_formula()
{
    char str1[100] = { 0 }, str2[100]; //str1为输入式子，str2为处理后的式子，并将处理后的式子赋给Simp_Formula
    int cnt = 0;
    cout << "请输入命题公式:(输入Over可结束程序)" << endl;
    gets(str1); //疑惑：将str1, str2改为全局变量后程序出错   要用gets(),不然鲁棒性不强
    for (int i = 0; i < strlen(str1);)//将用户输入的命题公式中->和<->转换成>和<
    {
        if (str1[i] == '-') { str2[cnt++] = '>'; i += 2; }
        else if (str1[i] == '<') { str2[cnt++] = '~'; i += 3; }
        else { str2[cnt++] = str1[i]; i += 1; }
    }
    str2[cnt++] = '\0';//重要，给字符串加上结束标记符
    Org_Formula = str1;// 原始输入
    Simp_Formula = str2; // 仅含有非、和取、析取的公式
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
            cout << "输入异常，请检查是否有空格，小写抑或非法字符" << endl << endl;
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
    string Tmp = "";// 临时的空字符串
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
    if (var_cnt == 2) //二个变元
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
    if (var_cnt == 3) //三个变元
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
    if (var_cnt == 4) //四个变元
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
    if (var_cnt == 5) //五个变元
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
        cout << "真值表如下" << endl;
        cout << "P\t" << "Q\t" << Org_Formula << endl;
        for (p = 1; p >= 0; p--)
        {
            for (q = 1; q >= 0; q--)
            {
                Calculate();
                if (res == 1)
                    PDNF = PDNF + "(" + (p == 1 ? "P" : "┐P") + "∧" + (q == 1 ? "Q" : "┐Q") + ")" + "∨";
                else
                    PCNF = PCNF + "(" + (p == 0 ? "P" : "┐P") + "∨" + (q == 0 ? "Q" : "┐Q") + ")" + "∧";
                cout << p << "\t" << q << "\t" << res << endl;
            }
        }
    }
    if (var_cnt == 3)
    {
        cout << "真值表如下" << endl;
        cout << "P\t" << "Q\t" << "R\t" << Org_Formula << endl;
        for (p = 1; p >= 0; p--)
        {
            for (q = 1; q >= 0; q--)
            {
                for (r = 1; r >= 0; r--)
                {
                    Calculate();
                    if (res == 1)
                        PDNF = PDNF + "(" + (p == 1 ? "P" : "┐P") + "∧" + (q == 1 ? "Q" : "┐Q") + "∧" + (r == 1 ? "R" : "┐R") + ")" + "∨";
                    else
                        PCNF = PCNF + "(" + (p == 0 ? "P" : "┐P") + "∨" + (q == 0 ? "Q" : "┐Q") + "∨" + (r == 0 ? "R" : "┐R") + ")" + "∧";
                    cout << p << "\t" << q << "\t" << r << "\t" << res << endl;
                }
            }
        }
    }
    if (var_cnt == 4)
    {
        cout << "真值表如下" << endl;
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
                            PDNF = PDNF + "(" + (p == 1 ? "P" : "┐P") + "∧" + (q == 1 ? "Q" : "┐Q") + "∧" + (r == 1 ? "R" : "┐R") + "∧" + (s == 1 ? "R" : "┐R") + ")" + "∨";
                        else
                            PCNF = PCNF + "(" + (p == 0 ? "P" : "┐P") + "∨" + (q == 0 ? "Q" : "┐Q") + "∨" + (r == 0 ? "R" : "┐R") + "∨" + (s == 0 ? "R" : "┐R") + ")" + "∧";
                        cout << p << "\t" << q << "\t" << r << "\t" << s << "\t" << res << endl;
                    }
                }
            }
        }
    }
    if (var_cnt == 5)
    {
        cout << "真值表如下" << endl;
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
                                PDNF = PDNF + "(" + (p == 1 ? "P" : "┐P") + "∧" + (q == 1 ? "Q" : "┐Q") + "∧" + (r == 1 ? "R" : "┐R") + "∧" + (s == 1 ? "R" : "┐R") + ")" + "∨";
                            else
                                PCNF = PCNF + "(" + (p == 0 ? "P" : "┐P") + "∨" + (q == 0 ? "Q" : "┐Q") + "∨" + (r == 0 ? "R" : "┐R") + "∨" + (s == 0 ? "R" : "┐R") + ")" + "∧";
                            cout << p << "\t" << q << "\t" << r << "\t" << s << "\t" << t << "\t" << res << endl;
                        }
                    }
                }
            }
        }
    }

    if (PDNF.length() == 0)
    {
        cout << "主析取范式不存在" << endl;
    }
    else
    {
        PDNF.erase(PDNF.length() - 2);
        cout << "主析取范式为：" << PDNF << endl << endl;
    }
    if (PCNF.length() == 0)
        cout << "主合取范式不存在" << endl;
    else
    {
        PCNF.erase(PCNF.length() - 2);
        cout << "主合取范式为：" << PCNF << endl << endl;
    }
    PDNF = "";
    PCNF = "";
}

void Not_Not(char c)//功能：判断运算符是否为！，为什么呢？因为如果是！，我只需取一个元素
{                   //否则的话我必须取两个元素才能计算
    if (c != '!')
    {
        a = Simp_stack.Top();
        Simp_stack.Pop();
        b = Simp_stack.Top();
        Simp_stack.Pop();
    }
}

//选择要计算的运算符
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

//进行！运算
void Not()
{
    a = Simp_stack.Top();
    Simp_stack.Pop();
    res = (a == 1 ? 0 : 1);   //一定要注意是等于号
    Simp_stack.Push(res);
}

//进行合取运算
void And()
{
    res = a * b;
    Simp_stack.Push(res);
}

//进行析取运算
void Or()
{
    res = (a + b == 0) ? 0 : 1;
    Simp_stack.Push(res);
}

//进行条件运算
void If()
{
    res = (b == 1 && a == 0) ? 0 : 1;
    Simp_stack.Push(res);
}

//进行双条件运算
void Iif()
{
    res = (a == b ? 1 : 0);
    Simp_stack.Push(res);
}

