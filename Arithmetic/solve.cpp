#include"stdafx.h"
#include<iostream>
#include<cmath>
#include"operation.h"

using namespace std;


//判断是否为括号
bool Operation::isPra(char c)
{
	if (c == '(' || c == ')')
		return true;
	else
		return false;
}

//获得符号的优先性
int Operation::getPri(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 0;	//如果是加减，返回0
		break;
	case '*':
	case '/':
		return 1;	//如果是乘除，返回1
		break;
	case '^':
		return 2;   //如果是乘方，返回2
		break;
	case '(':
	case ')':
		return -1;  //注意，这里将括号设为最低优先级，因此括号不会被弹出，除非遇到右括号
		break;
	}
}

//判断符号的优先性
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
			//弹出所有元素直到遇到左括号
			while (coll2.top() != '(')
			{
				char ch = coll2.top();
				coll3.push_back(ch);
				coll2.pop();
			}
			//将与其匹配的左括号弹出
			coll2.pop();
		}
	}
	else
	{
		char sym = coll2.top();
		//比较两符号的优先性
		if (getPri(c) <= getPri(sym))
		{
			coll2.pop();
			coll3.push_back(sym);
			//递归调用check,比较当前符号c与下一个栈顶符号的优先性
			check(c, coll2, coll3);
		}
		else
		{
			//如果c比栈顶符号优先级大，那将c压入coll2(操作符栈）中
			coll2.push(c);
		}
	}
}

//从coll1中取出元素，分配元素到coll2和coll3中
//coll1中缀表达式，coll2操作符，coll3后缀表达式
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
			if ((!coll1.empty() && !isdigit(coll1.front())) || coll1.empty())//由于一个数字不一定只有一位长，故整个数字结尾加空格
				coll3.push_back(' ');
		}
		else
		{
			char d = 0;
			if (!coll1.empty())
				d = coll1.front();

			if (c == '*'&&d == '*')   //**转换为^
			{
				coll1.pop_front();
				coll2.push('^');
			}
			else
				check(c, coll2, coll3);//调用check函数，针对不同情况作出不同操作
		}

	}

	//如果输入结束，将coll2的元素全部弹出，加入后缀表达式中
	while (!coll2.empty())
	{
		char c = coll2.top();
		coll3.push_back(c);
		coll2.pop();
	}
}

//计算后缀表达式
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


		//如果是操作数，压入栈中
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
		else	 //如果是操作符，从栈中弹出元素进行计算
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
	deque<char> coll1;  //盛放中缀表达式
	stack<char> coll2;  //盛放操作符
	deque<char> coll3;	//盛放后缀表达式
	stack<double>coll4;	//计算后缀表达式的辅助容器

						//string str = "25/27**0-(48/21-4)+37-25/34+28*30";
	for (int i = 0; i != str.size() - 1; i++)
	{
		coll1.push_back(str[i]);
	}

	//从coll中取出元素，分配元素到coll2和coll3中
	allocate(coll1, coll2, coll3);

	//输出后缀表达式
	/*while (!coll3.empty())
	{
	char c = coll3.front();
	coll3.pop_front();
	cout << c;
	}
	cout << endl;*/


	//计算后缀表达式
	calculate(coll3, coll4);

	//	cout << "计算结果为:" << coll4.top() << endl;

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
		syb = 0;//初始值为正数
		cout << str << endl;
		cout << "Your answer:";
		cin >> as;
		int flag = 1;
		int dot = 0;

		//处理输入结果
		if (as[0] == '-')//负数
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

		//计算输入的最终结果
		if (flag == 1)
			final_ans = as1;
		else if (flag == 2)
			final_ans = as1 + as2 / pow(10, dot);
		else if (flag == 3)
			final_ans = as1 / as2;

		if (syb == 1)
			final_ans = 0 - final_ans;

		//判断输入结果是否正确
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
	cout << "正确数：" << right_num << endl;
	cout << "错误数：" << wrong_num << endl;
}
