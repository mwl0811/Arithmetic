#include"stdafx.h"
#include<iostream>
#include<cmath>
#include"operation.h"

using namespace std;


//�ж��Ƿ�Ϊ����
bool Operation::isPra(char c)
{
	if (c == '(' || c == ')')
		return true;
	else
		return false;
}

//��÷��ŵ�������
int Operation::getPri(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 0;	//����ǼӼ�������0
		break;
	case '*':
	case '/':
		return 1;	//����ǳ˳�������1
		break;
	case '^':
		return 2;   //����ǳ˷�������2
		break;
	case '(':
	case ')':
		return -1;  //ע�⣬���ｫ������Ϊ������ȼ���������Ų��ᱻ��������������������
		break;
	}
}

//�жϷ��ŵ�������
void Operation::check(char c, stack<char>& coll2, deque<char>& coll3)
{
	if (coll2.empty())
	{
		coll2.push(c);
		return;
	}

	if (isPra(c))
	{
		if (c == '(')
			coll2.push(c);
		else   //c==')'
		{
			//��������Ԫ��ֱ������������
			while (coll2.top() != '(')
			{
				char ch = coll2.top();
				coll3.push_back(ch);
				coll2.pop();
			}
			//������ƥ��������ŵ���
			coll2.pop();
		}
	}
	else
	{
		char sym = coll2.top();
		//�Ƚ������ŵ�������
		if (getPri(c) <= getPri(sym))
		{
			coll2.pop();
			coll3.push_back(sym);
			//�ݹ����check,�Ƚϵ�ǰ����c����һ��ջ�����ŵ�������
			check(c, coll2, coll3);
		}
		else
		{
			//���c��ջ���������ȼ����ǽ�cѹ��coll2(������ջ����
			coll2.push(c);
		}
	}
}

//��coll1��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3��
//coll1��׺���ʽ��coll2��������coll3��׺���ʽ
void Operation::allocate(deque<char>& coll1, stack<char>& coll2, deque<char>& coll3)
{
	while (!coll1.empty())
	{
		char c;
		c = coll1.front();
		coll1.pop_front();

		if (c >= '0'&&c <= '9')
		{
			coll3.push_back(c);
			if ((!coll1.empty() && !isdigit(coll1.front())) || coll1.empty())//����һ�����ֲ�һ��ֻ��һλ�������������ֽ�β�ӿո�
				coll3.push_back(' ');
		}
		else
		{
			char d = 0;
			if (!coll1.empty())
				d = coll1.front();

			if (c == '*'&&d == '*')   //**ת��Ϊ^
			{
				coll1.pop_front();
				coll2.push('^');
			}
			else
				check(c, coll2, coll3);//����check��������Բ�ͬ���������ͬ����
		}

	}

	//��������������coll2��Ԫ��ȫ�������������׺���ʽ��
	while (!coll2.empty())
	{
		char c = coll2.top();
		coll3.push_back(c);
		coll2.pop();
	}
}

//�����׺���ʽ
void Operation::calculate(deque<char>& coll3, stack<double>& coll4)
{
	double num = 0;
	while (!coll3.empty())
	{
		int flag = 0;
		char c = coll3.front();
		coll3.pop_front();

		char d = 0;
		if (!coll3.empty())
			d = coll3.front();
		else
		{
			flag = 1;
		}


		//����ǲ�������ѹ��ջ��
		if (c >= '0'&&c <= '9')
		{
			num = num * 10 + c - '0';
			if ((d == ' '&&flag == 0) || flag == 1)
			{
				coll4.push(num);
				num = 0;
				if (flag == 0)
					coll3.pop_front();
			}

		}
		else	 //����ǲ���������ջ�е���Ԫ�ؽ��м���
		{

			double op1 = coll4.top();
			coll4.pop();
			double op2 = coll4.top();
			coll4.pop();
			switch (c)
			{
			case '+':
				coll4.push(op2 + op1);
				break;
			case '-':
				coll4.push(op2 - op1);
				break;
			case '*':
				coll4.push(op2*op1);
				break;
			case '/':
				coll4.push(op2 / op1);
				break;
			case '^':
				coll4.push(pow(op2, op1));
				break;
			}
		}
	}
}

int Operation::solve(string str)
{
	int repeat = 0;
	deque<char> coll1;  //ʢ����׺���ʽ
	stack<char> coll2;  //ʢ�Ų�����
	deque<char> coll3;	//ʢ�ź�׺���ʽ
	stack<double>coll4;	//�����׺���ʽ�ĸ�������

						//string str = "25/27**0-(48/21-4)+37-25/34+28*30";
	for (int i = 0; i != str.size() - 1; i++)
	{
		coll1.push_back(str[i]);
	}

	//��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3��
	allocate(coll1, coll2, coll3);

	//�����׺���ʽ
	/*while (!coll3.empty())
	{
	char c = coll3.front();
	coll3.pop_front();
	cout << c;
	}
	cout << endl;*/


	//�����׺���ʽ
	calculate(coll3, coll4);

	//	cout << "������Ϊ:" << coll4.top() << endl;

	int flag = 0;
	for (int i = 0; i<ansnum; i++)
		if (coll4.top() == ans[i])
		{
			flag = 1;
			repeat = 1;
			break;
		}
	if (flag == 0)
	{
		ans[ansnum] = coll4.top();
		out << ansnum + 1 << ". " << str << endl;
		ansnum++;
	}
	coll1.clear();
	coll3.clear();
	while (!coll2.empty())
		coll2.pop();
	while (!coll4.empty())
		coll4.pop();

	return repeat;
}
void Operation::judge()
{
	string as;
	char syb;
	ifstream problem;
	double as1, as2;
	double final_ans;
	problem.open("question.txt");
	string str;
	int num = 0, wrong_num = 0, right_num = 0;
	while (getline(problem, str))
	{
		as1 = 0;
		as2 = 0;
		final_ans = 0;
		syb = 0;//��ʼֵΪ����
		cout << str << endl;
		cout << "Your answer:";
		cin >> as;
		int flag = 1;
		int dot = 0;

		//����������
		if (as[0] == '-')//����
		{
			syb = 1;
		}

		for (int i = 0; i < as.length(); i++)
		{
			if (i == 0 && syb == 1)
				continue;
			if (as[i] <= '9'&&as[i] >= '0'&&flag == 1)
				as1 = as1 * 10 + (as[i] - '0');
			else if (as[i] == '.')
				flag = 2;
			else if (as[i] <= '9'&&as[i] >= '0'&&flag == 2)
			{
				as2 = as2 * 10 + (as[i] - '0');
				dot++;
			}
			else if (as[i] == '/')
				flag = 3;
			else if (as[i] <= '9'&&as[i] >= '0'&&flag == 3)
				as2 = as2 * 10 + (as[i] - '0');
			else
			{
				flag = 0;
				break;
			}

		}

		//������������ս��
		if (flag == 1)
			final_ans = as1;
		else if (flag == 2)
			final_ans = as1 + as2 / pow(10, dot);
		else if (flag == 3)
			final_ans = as1 / as2;

		if (syb == 1)
			final_ans = 0 - final_ans;

		//�ж��������Ƿ���ȷ
		if (flag == 0 || final_ans != ans[num])
		{
			cout << "wrong!" << endl;
			wrong_num++;
		}
		else
		{
			cout << "right!" << endl;
			right_num++;
		}
		num++;
	}
	cout << "��ȷ����" << right_num << endl;
	cout << "��������" << wrong_num << endl;
}
