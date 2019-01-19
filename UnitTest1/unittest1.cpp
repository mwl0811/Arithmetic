#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Arithmetic/generate.cpp"
#include "../Arithmetic/solve.cpp"
#include "../Arithmetic/operation.h"
#include "../Arithmetic/Arithmetic.cpp"
#include <windows.h>
#include <cassert>
#include <cstring>
#include <set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		int argc;
		char **argv;


		UnitTest1()
		{
			argv = new char*[3];

			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "Arithmetic.exe");

			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "100");

			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "1");


		}

		TEST_METHOD(TestMethod1)//输入格式不正确
		{
			argc = 1;
			int result = main(argc, argv);
			//assert(result == 1);
		}

		TEST_METHOD(TestMethod2)   //输入数字过大
		{
			argc = 3;
			argv[1] = "100000";
			int result = main(argc, argv);
			//assert(result == 2);
		}

		TEST_METHOD(TestMethod3)  //检查输入模式1时是否使用的是"^"
		{
			argv[1] = "100";
			argv[2] = "1";
			int result = main(argc, argv);
			//assert(result == 3);
		}

		TEST_METHOD(TestMethod4)  //检查输入模式2时是否使用的是“**”
		{
			argv[1] = "100";
			argv[2] = "2";
			int result = main(argc, argv);
			//assert(result == 4);
		}

		TEST_METHOD(TestMethod5)//检查输入重复的四则运算题目，结果是否提示重新生成
		{
			Operation M;
			string str = "3+(2+1)=";
			string str2 = "1+2+3=";
			int result1 = M.solve(str);
			int result2 = M.solve(str2);
			assert((result1 != result2) == 1);
		}

		TEST_METHOD(TestMethod6)//检查输入带括号的四则运算题目，结果是否正确
		{
			Operation M;
			string str = "3+(2+1)=";
			int result1 = M.solve(str);
			double answer = M.getans();
			assert((answer == 6) == 1);
		}


		TEST_METHOD(TestMethod7)//检查输入带'^'四则运算题目，结果是否正确
		{
			Operation M;
			string str = "3^(2+1)=";
			int result1 = M.solve(str);
			double answer = M.getans();
			assert((answer == 27) == 1);
		}


		TEST_METHOD(TestMethod8)//检查输入带'**'型的乘方的四则运算题目，结果是否正确
		{
			Operation M;
			string str = "3**(2+1)=";
			int result1 = M.solve(str);
			double answer = M.getans();
			assert((answer == 27) == 1);
		}

		TEST_METHOD(TestMethod9)//检查输入复杂的四则运算题目，结果是否正确
		{
			Operation M;
			string str = "3**(2+1)/3*2=";
			int result1 = M.solve(str);
			double answer = M.getans();
			assert((answer == 18) == 1);
		}

		TEST_METHOD(TestMethod10)//检查结果不是整数的四则运算，结果是否正确
		{
			Operation M;
			string str = "3**(2+1)/4=";
			int result1 = M.solve(str);
			double answer = M.getans();
			assert((answer == 6.75) == 1);
		}

		TEST_METHOD(TestMethod11)//检查输入结果为真分数，判断是否正确
		{
			//judge()函数变形
			int judge = 0;
			char syb;
			double as1 = 0, as2 = 0;
			string as = "1/4";
			double answer = 0.25;
			double final_ans = 0;

			int flag = 1;
			int dot = 0;

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
			if (flag == 0 || final_ans != answer)
			{
				judge = 0;
			}
			else
			{
				judge = 1;
			}

			assert(judge == 1);
		}

		TEST_METHOD(TestMethod12)//检查输入结果为负数，判断是否正确
		{
			//judge()函数变形
			int judge = 0;
			char syb;
			double as1 = 0, as2 = 0;
			string as = "-3";
			double final_ans = 0;

			double answer = 0 - 3;

			int flag = 1;
			int dot = 0;

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
			if (flag == 0 || final_ans != answer)
			{
				judge = 0;
			}
			else
			{
				judge = 1;
			}

			assert(judge == 1);
		}
	};
}