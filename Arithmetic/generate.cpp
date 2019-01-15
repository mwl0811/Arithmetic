#include "stdafx.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<string>
#include<fstream>
#include"operation.h"
using namespace std;


void Operation::Generate(int mode, int N)
{
	int repeat;
	char ch[5] = { '+','-','*','/','^' };
	srand((unsigned)time(NULL));    //初始化随机数种子
	for (int i = 0; i < N; i++)
	{
		char str[50];   //存放一行计算式
		char sym[11];  //符号保存
		int num[11];   //数字保存
		int symbolnum;   //符号个数
		int bracket1[3], bracket2[3];   //符号随机加的位置
		symbolnum = (rand() % 10) + 1;
		//printf("%d", symbolnum);
		for (int j = 0; j <= symbolnum; j++)
		{
			int symbol;
			if (sym[j - 1] == '^')   //为避免多次乘方而导致结果过大
			{
				if (num[j - 1] == 0)
				{
					num[j] = (rand() % 50) + 1;
				}
				else
				{
					num[j] = (rand() % 4);   //乘方后的数字小于等于3
				}
				symbol = (rand() % 4);   //不再生成乘方
			}
			else if (sym[j - 1] == '/')
			{
				symbol = (rand() % 5);
				num[j] = (rand() % 50) + 1;
			}
			else
			{
				symbol = (rand() % 5);
				num[j] = (rand() % 50);
			}
			sym[j] = ch[symbol];
		}
		sym[symbolnum] = '=';
		int btemp = 0;
		if (symbolnum >= 2)
		{
			btemp = (rand() % 4);   //加括号的个数0-3个
			for (int j = 0; j < btemp; j++)
			{
				do
				{
					bracket1[j] = (rand() % (symbolnum - 1));
					bracket2[j] = (rand() % (symbolnum - bracket1[j] - 1)) + bracket1[j] + 2;
				} while (sym[bracket1[j] - 1] == '^' || sym[bracket1[j] - 1] == '/' || sym[bracket2[j]] == '^');
				//乘方的情况下不加括号，防止过大
				//除法后不加括号，防止除数为0的情况
			}
			for (int j = 0; j < btemp; j++)
			{
				for (int k = 0; k < btemp; k++)
				{
					if (bracket1[j] == bracket2[k])
					{
						bracket1[j] = 20;
						bracket2[k] = 20;   //设置一个较大的数，使同一数字两旁括号其不输出
					}
				}
			}
			for (int j = 0; j < btemp; j++)
			{
				for (int k = j + 1; k < btemp; k++)
				{
					if (bracket1[j] == bracket1[k])
					{
						for (int m = 0; m < btemp; m++)
						{
							for (int n = m + 1; n < btemp; n++)
							{
								if (bracket2[m] == bracket2[n])
								{
									if (bracket1[k] != 20 && bracket2[n] != 20)
									{
										bracket1[k] = 20;
										bracket2[n] = 20;   //删除重复括号
									}
								}
							}
						}
					}
				}
			}
		}
		int len = 0;
		for (int j = 0; j <= symbolnum; j++)
		{
			for (int k = 0; k < btemp; k++)
			{
				if (bracket1[k] == j)
				{

					str[len] = '(';
					len++;
				}
			}
			if (num[j] <= 9 && num[j] >= 0)
			{
				str[len] = num[j] + '0';
				len++;
			}
			else
			{
				str[len] = num[j] / 10 + '0'; len++;
				str[len] = num[j] % 10 + '0'; len++;
			}
			for (int k = 0; k < btemp; k++)
			{
				if (bracket2[k] == j)
				{
					str[len] = ')';
					len++;
				}
			}
			if (mode == 2 && sym[j] == '^')
			{
				str[len] = '*'; len++;
				str[len] = '*'; len++;
			}
			else
			{
				str[len] = sym[j]; len++;
			}
		}
		str[len] = '\0';
		//printf("%s", str);
		//solve(str, out);
		repeat = solve(str);
		if (repeat == 1)
			N++;

	}
}