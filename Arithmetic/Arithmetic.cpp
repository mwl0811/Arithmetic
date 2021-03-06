// arithmetic_wm.cpp: 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<string>
#include<iostream>
#include"operation.h"
using namespace std;

int main(int argc, char *argv[])
{
	Operation M;
	int flag = 0;
	if (argc == 3 && (argv[2][0] == '1' || argv[2][0] == '2') && strlen(argv[2]) == 1)
	{
		int num = 0;
		int len = strlen(argv[1]);
		for (int i = 0; i < len; i++)
		{
			if (isdigit(argv[1][i]))
				num = num * 10 + (argv[1][i] - '0');  //输入的是数字
			else
			{
				flag = 1;
				break;
			}
		}
		if (num > 1000)
		{
			cout << "The number of questions is too large!" << endl;
			return 2;
		}
		int mode = argv[2][0] - '0';//模式选择

		if (flag == 0)
		{
			M.Generate(mode, num);
			M.judge();
		}

	}
	else
	{
		flag = 1;
	}

	if (flag == 1)
	{
		cout << "Please check your input!" << endl;
		cout << "Just input like this: Arithmetic.exe N mode" << endl;
		cout << "N means the number of questions, mode means the power." << endl;
		cout << "mode=1:^   mode=2:**" << endl;
		return 1;
	}
	if (M.checknum == 1)
	{
		return 3;
	}
}