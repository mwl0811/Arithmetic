#pragma once
#include"stdafx.h"
#include<string>
#include<stack>
#include<deque>
#include<fstream>
using namespace std;
class Operation
{
private:
	ofstream out;
	double ans[2000] = { 0 };
	int ansnum = 0;
public:
	int checknum = 0;
	Operation()
	{
		out.open("question.txt");
		ansnum = 0;
	}
	int solve(string str);
	void Generate(int mode, int N);
	bool isPra(char c);
	int getPri(char c);
	void check(char c, stack<char>& coll2, deque<char>& coll3);
	void allocate(deque<char>& coll1, stack<char>& coll2, deque<char>& coll3);
	void calculate(deque<char>& coll3, stack<double>& coll4);
	void judge();
	double getans()
	{
		return ans[0];
	}

};