#include "Calculator.h"
#include <stdexcept>
#include <iostream>
//#include <vector>
#include <QVector>
//#include <stack>
#include <QStack>
#include <regex>
#include <cmath>
#include <map>
#include <queue>

#define PI 3.14159265 
#define e 2.71828182845

#define DevideByZero 0			//除以零
#define InvalidInput 1			//非法输入
#define BracketsWrong 2			//括号顺序错误
#define Brackets 3				//有括号算式
#define NoBrackets 4			//无括号算式
#define NeedBrackets 5			//需要补充括号
#define Method 6				//有括号方法
#define ZWSMethod 7				//无括号方法

#define ElseDeal 8				//其他方法
#define NBandED 9				//5+8

static int Brackets_counter = 0;		//左括号-右括号计数器
static int Left_counter = 0;			//左括号计数器

using namespace std;

vector<string> Split(string str) {
	vector<string> temp_VecStr;
	regex reg_dig("[[:digit:].]");
	string temp_str, temp_str1, temp_str2, temp_str3;

	temp_str = str;

	for (auto i = temp_str.begin(); i != temp_str.end(); ++i) {
		temp_str2 = *i;

		if (regex_search(temp_str2, reg_dig)) {
			temp_str1 += temp_str2;

			auto p = i;

			if (++p == temp_str.end()) {
				temp_VecStr.push_back(temp_str1);
				temp_str1.clear();
			}
			--p;

			if (++p != temp_str.end()) {
				--p;
				temp_str2 = *(++p);

				if (!regex_search(temp_str2, reg_dig)) {
					temp_VecStr.push_back(temp_str1);
					temp_str1.clear();
				}
			}
		}
		else {
			if (temp_str2 == "+" || temp_str2 == "-" || temp_str2 == "*" || temp_str2 == "/" || temp_str2 == "(" || temp_str2 == "%") {
				temp_VecStr.push_back(temp_str2);

				auto p = i;
				if (++p != temp_str.end()) {
					--p;

					temp_str3 = *(++p);
					if (temp_str3 == "-") {
						temp_str1 += temp_str3;

						if (++p != temp_str.end()) {
							auto p1 = p;
							temp_str3 = *p1;
							for (; regex_search(temp_str3, reg_dig) && p1 != temp_str.end(); ++p1, ++i) {
								temp_str3 = *p1;
								if (regex_search(temp_str3, reg_dig)) {
									temp_str1 += temp_str3;
								}
							}
							temp_VecStr.push_back(temp_str1);
							temp_str1.clear();
							if (regex_search(temp_str3, reg_dig)) {
								++i;
							}
						}
					}
				}
			}
			else {
				temp_VecStr.push_back(temp_str2);
			}
		}
	}

	return temp_VecStr;
}

QStack<string> Postfix_Expression(vector<string> temp_VecStr) {
	QStack<string> temp_QStackSymbol, temp_QStackExp, temp_QStack1, temp_QStack2;
	regex reg_dig("[[:digit:].]+");
	string temp_str;

	for (auto &i : temp_VecStr) {
		temp_str = i;

		if (regex_search(temp_str, reg_dig)) {
			temp_QStackExp.push(temp_str);
		}

		if (temp_str == "(") {
			temp_QStackSymbol.push(temp_str);
		}

		if (temp_str == ")") {
			while (temp_QStackSymbol.top() != "(") {
				temp_QStackExp.push(temp_QStackSymbol.top());
				temp_QStackSymbol.pop();
			}
			temp_QStackSymbol.pop();
		}

		if (temp_str == "+" || temp_str == "-") {
			if (!temp_QStackSymbol.empty()) {
				if (temp_QStackSymbol.top() == "+" || temp_QStackSymbol.top() == "-" || temp_QStackSymbol.top() == "*" || temp_QStackSymbol.top() == "/" || temp_QStackSymbol.top() == "%") {
					while (!temp_QStackSymbol.empty() && temp_QStackSymbol.top() != "(") {
						temp_QStackExp.push(temp_QStackSymbol.top());
						temp_QStackSymbol.pop();
					}
					temp_QStackSymbol.push(temp_str);
				}
				else {
					temp_QStackSymbol.push(temp_str);
				}
			}
			else {
				temp_QStackSymbol.push(temp_str);
			}
		}

		if (temp_str == "%") {
			if (!temp_QStackSymbol.empty()) {
				if (temp_QStackSymbol.top() == "*" || temp_QStackSymbol.top() == "/" || temp_QStackSymbol.top() == "%") {
					while (!temp_QStackSymbol.empty() && temp_QStackSymbol.top() != "(" && temp_QStackSymbol.top() != "+" && temp_QStackSymbol.top() != "-") {
						temp_QStackExp.push(temp_QStackSymbol.top());
						temp_QStackSymbol.pop();
					}
					temp_QStackSymbol.push(temp_str);
				}
				else {
					temp_QStackSymbol.push(temp_str);
				}
			}
			else {
				temp_QStackSymbol.push(temp_str);
			}
		}

		if (temp_str == "*" || temp_str == "/") {
			if (!temp_QStackSymbol.empty()) {
				if (temp_QStackSymbol.top() == "*" || temp_QStackSymbol.top() == "/") {
					while (!temp_QStackSymbol.empty() && temp_QStackSymbol.top() != "(" && temp_QStackSymbol.top() != "+" && temp_QStackSymbol.top() != "-") {
						temp_QStackExp.push(temp_QStackSymbol.top());
						temp_QStackSymbol.pop();
					}
					temp_QStackSymbol.push(temp_str);
				}
				else {
					temp_QStackSymbol.push(temp_str);
				}
			}
			else {
				temp_QStackSymbol.push(temp_str);
			}
		}
	}

	while (!temp_QStackSymbol.empty()) {
		temp_QStackExp.push(temp_QStackSymbol.top());
		temp_QStackSymbol.pop();
	}

	while (!temp_QStackExp.empty()) {
		temp_QStack1.push(temp_QStackExp.top());
		temp_QStack2.push(temp_QStackExp.top());
		temp_QStackExp.pop();
	}

	while (!temp_QStack2.empty()) {
		temp_QStack2.top();
		temp_QStack2.pop();
	}

	return temp_QStack1;
}

double Evaluation(QStack<string> temp_QStackExp) {
	auto temp_num1 = 0.0, temp_num2 = 0.0;
	regex reg_dig("[[:digit:].]+");
	QStack<double> temp_QStackNum;
	string temp_str;

	try {
		while (!temp_QStackExp.empty()) {
			temp_str = temp_QStackExp.top();

			if (regex_search(temp_str, reg_dig)) {
				temp_QStackNum.push(stod(temp_str));
				temp_QStackExp.pop();
			}

			if (temp_str == "+") {
				if (!temp_QStackNum.empty()) {
					temp_num1 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_num2 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_QStackNum.push(temp_num1 + temp_num2);
					temp_QStackExp.pop();
				}
				else {
					throw runtime_error("!");
				}
			}

			if (temp_str == "-") {
				if (!temp_QStackNum.empty()) {
					temp_num1 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_num2 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_QStackNum.push(temp_num2 - temp_num1);
					temp_QStackExp.pop();
				}
				else {
					throw runtime_error("!");
				}
			}

			if (temp_str == "%") {
				if (!temp_QStackNum.empty()) {
					temp_num1 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_num2 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_QStackNum.push(fmod(temp_num2, temp_num1));
					temp_QStackExp.pop();
				}
				else {
					throw runtime_error("!");
				}
			}

			if (temp_str == "*") {
				if (!temp_QStackNum.empty()) {
					temp_num1 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_num2 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_QStackNum.push(temp_num1 * temp_num2);
					temp_QStackExp.pop();
				}
				else {
					throw runtime_error("!");
				}
			}

			if (temp_str == "/") {
				if (!temp_QStackNum.empty()) {
					temp_num1 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_num2 = temp_QStackNum.top();
					temp_QStackNum.pop();
					temp_QStackNum.push(temp_num2 / temp_num1);
					temp_QStackExp.pop();
				}
				else {
					throw runtime_error("!");
				}
			}
		}
	}

	catch (runtime_error &err) {
		cerr << err.what() << endl;
		return Evaluation(Postfix_Expression(Split("!")));
	}

	temp_QStackNum.top();

	return temp_QStackNum.top();
}

string calculate(string str)
{
	struct node
	{
		double number;
		char op;
		bool flag;
	};
	QStack<node> operator_QStack; // 操作符栈
	queue<node> last_expression_QStack;// 后缀表达式队列
	map<char, int> calculate_map; //char-int类型map
	double temp_num;
	node temp_node;
	calculate_map['+'] = calculate_map['-'] = 1;
	calculate_map['*'] = calculate_map['/'] = 2;
	calculate_map['('] = calculate_map[')'] = 3;
	int index[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, }; int c = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if ((str[i] == '/' || str[i] == '*' || str[i] == '+' || str[i] == '-' || str[i] == '(') && str[i + 1] == '-')
		{
			index[c++] = i + 2;
			str[i + 1] = ' ';
		}
		if (str[0] == '-')
		{
			index[c++] = 1;
			str[0] = ' ';
		}

	}
	/*for (int i = 0; i < 10; i++)
	{
	cout << index[i] << " ";
	}
	cout << endl;
	for (int k = 0; k < str.length(); k++)
	{
	cout << str[k] << " ";
	}
	cout << endl;*/
	for (int i = 0; i < str.length();)
	{
		/*if (str[i] == '(')
		cout << 0.1 << endl;
		if (str[i] == ')')
		cout << 7 << endl;
		if (str[i] == '*')
		cout << 8 << endl;*/
		////////////////////////////////////////////////////////////
		if (str[i] == ' ')
		{
			i++;
			continue;
		}
		else if (str[i] >= '0'&&str[i] <= '9')
		{
			int flag1 = 1;
			for (int j = 0; j<10; j++)
			{
				if (i == index[j])
				{
					flag1 = -1; break;
				}

			}
			int j;
			for (j = i; str[j] != '/' &&str[j] != '*' &&str[j] != '+' && str[j] != '-'&&str[j] != ')'&&str[j] != '('&&j<str.length(); j++)
			{

			}
			temp_node.flag = 1;

			temp_node.number = (flag1)*stod(str.substr(i, j - i));
			i = j;
			last_expression_QStack.push(temp_node);
		}
		else
		{
			/*temp_node.flag = 0;
			while (!operator_QStack.empty() && calculate_map[str[i]] <= calculate_map[operator_QStack.top().op])
			{
			last_expression_QStack.push(operator_QStack.top());
			operator_QStack.pop();
			}
			temp_node.op = str[i];
			operator_QStack.push(temp_node);
			i++;*/
			/////////////////////////////////////////////////////////////////////////////////////
			//cout << 1 << endl;
			if (str[i] == '(')
			{
				temp_node.flag = 0;
				temp_node.op = str[i];
				operator_QStack.push(temp_node);
				i++;
			}
			else if (str[i] == ')')
			{
				while (!operator_QStack.empty())
				{
					if (operator_QStack.top().op != '(')
					{
						last_expression_QStack.push(operator_QStack.top());

					}
					operator_QStack.pop();

				}

				/*if (!operator_QStack.empty())
				{
				operator_QStack.pop(); cout << 666 << endl;
				}*/

				i++;
			}
			else
			{

				while (!operator_QStack.empty() && calculate_map[str[i]] <= calculate_map[operator_QStack.top().op])
				{

					last_expression_QStack.push(operator_QStack.top());
					operator_QStack.pop();
				}
				temp_node.flag = 0;
				temp_node.op = str[i];
				operator_QStack.push(temp_node);
				i++;
			}

		}
	}

	while (!operator_QStack.empty())
	{
		///cout << "222" << endl;
		//cout << operator_QStack.top().op << endl;
		last_expression_QStack.push(operator_QStack.top());
		operator_QStack.pop();
	}
	//////////////////////////////////////////////////
	/*while (!last_expression_QStack.empty())
	{
	cout << (last_expression_QStack.front().flag ? last_expression_QStack.front().number : (char)(last_expression_QStack.front().op)) << " ";
	last_expression_QStack.pop();
	}*/
	///////////////////////////////////////////////
	double temp1; double temp2;
	node cur; node temp;
	while (!last_expression_QStack.empty())
	{

		cur = last_expression_QStack.front();
		last_expression_QStack.pop();
		if (cur.flag == 1) operator_QStack.push(cur);
		else
		{

			temp2 = operator_QStack.top().number;

			operator_QStack.pop();

			temp1 = operator_QStack.top().number;
			operator_QStack.pop();

			temp.flag = true;
			if (cur.op == '+') temp.number = temp1 + temp2;
			else if (cur.op == '-') temp.number = temp1 - temp2;
			else if (cur.op == '*') temp.number = temp1 * temp2;
			else if (cur.op == '/') {
				if (temp2 == 0)
					return "inf";
				else
					temp.number = temp1 / temp2;
			}
			//else cout << "fuck" << endl;
			operator_QStack.push(temp);


		}
	}
	return std::to_string(operator_QStack.top().number);
}

void Calculator::ERROR(int condition)
{
	switch (condition)
	{
	case DevideByZero:
		output = "Cannot divede by zero";
		down->setText(output);
		break;
	case InvalidInput:
		output = "Invalid input";
		down->setText(output);
		break;
	case BracketsWrong:
		output = "Brackets Wrong";
		down->setText(output);
		break;
	default:
		output = "Default Error";
		down->setText(output);
		break;
	}
	Buttons_Disabled();
}

int Calculator::per_judge(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(' || str[i] == ')')
		{
			if (str.find("()") != -1)
				return InvalidInput;//出现()会报错
			int left = 0;
			int right = 0;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == '(')
					left++;
				else if (str[i] == ')')
					right++;
				if (right > left)
					return BracketsWrong; //error(右括号在左括号前面）
			}
			if (right < left)
			{
				Brackets_counter = left - right;
				if (str[0] == '-')
					return NBandED;
				return NeedBrackets;//补充右括号
			}
			if (std::to_string(Evaluation(Postfix_Expression(Split(str)))) == "inf")
				return DevideByZero;//除以零
			if (str[0] == '-')
				return ElseDeal;//既有括号第一个又是减号
			return Brackets;  // 没有error 有括号  用它的方法
		}
	}
	if (calculate(str) == "inf")
		return DevideByZero;//除以零
	return NoBrackets;// 没有error 没括号   用我的方法
}

Calculator::Calculator(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);

	//初始化数据成员
	current_Num = 0;
	answer = 0;

	output = "0";//初始化为0
	to_solve = "";

	mark_occupy = false;

	decp = false;
	decp_counter = 1;
	zeros = false;

	Error = false;

	//初始化部件对象指针
	button_0 = new QPushButton("0");
	button_1 = new QPushButton("1");
	button_2 = new QPushButton("2");
	button_3 = new QPushButton("3");
	button_4 = new QPushButton("4");
	button_5 = new QPushButton("5");
	button_6 = new QPushButton("6");
	button_7 = new QPushButton("7");
	button_8 = new QPushButton("8");
	button_9 = new QPushButton("9");
	button_plus = new QPushButton("+");
	button_minus = new QPushButton("-");
	button_multiply = new QPushButton(QString::fromWCharArray(L"×"));
	button_devide = new QPushButton("/");
	button_equal = new QPushButton("=");
	button_clear = new QPushButton("CE");
	button_clearAll = new QPushButton("C");
	button_square = new QPushButton("x^2");
	button_cube = new QPushButton("x^3");
	button_sq_root = new QPushButton("sqr");
	button_reciprocal = new QPushButton("1/x");
	button_e = new QPushButton("e");
	button_10_X = new QPushButton("10^x");
	button_Exp = new QPushButton("Exp");
	button_lg = new QPushButton("lg");
	button_ln = new QPushButton("ln");
	button_sin = new QPushButton("sin");
	button_cos = new QPushButton("cos");
	button_tan = new QPushButton("tan");
	button_opp = new QPushButton("+/-");
	button_00 = new QPushButton("00");
	button_decpoint = new QPushButton(".");
	button_PI = new QPushButton("PI");
	button_arcsin = new QPushButton("sin^-1");
	button_arccos = new QPushButton("cos^-1");
	button_arctan = new QPushButton("tan^-1");
	button_backspace = new QPushButton("<-");
	button_factorial = new QPushButton("n!");
	button_left = new QPushButton("(");
	button_right = new QPushButton(")");


	up = new QLineEdit;
	down = new QLineEdit("0");

	//禁止编辑文本框
	up->setReadOnly(true);
	down->setReadOnly(true);
	//设置最长输入长度
	up->setMaxLength(150);
	down->setMaxLength(150);
	//设置向右对齐
	up->setAlignment(Qt::AlignRight);
	down->setAlignment(Qt::AlignRight);
	//设置固定大小
	up->setFixedSize(700, 35);
	down->setFixedSize(700, 35);

	button_0->setFixedSize(80, 80);
	button_1->setFixedSize(80, 80);
	button_2->setFixedSize(80, 80);
	button_3->setFixedSize(80, 80);
	button_4->setFixedSize(80, 80);
	button_5->setFixedSize(80, 80);
	button_6->setFixedSize(80, 80);
	button_7->setFixedSize(80, 80);
	button_8->setFixedSize(80, 80);
	button_9->setFixedSize(80, 80);
	button_plus->setFixedSize(80, 80);
	button_minus->setFixedSize(80, 80);
	button_multiply->setFixedSize(80, 80);
	button_devide->setFixedSize(80, 80);
	button_equal->setFixedSize(80, 80);
	button_clear->setFixedSize(80, 80);
	button_clearAll->setFixedSize(80, 80);
	button_square->setFixedSize(80, 80);
	button_cube->setFixedSize(80, 80);
	button_sq_root->setFixedSize(80, 80);
	button_reciprocal->setFixedSize(80, 80);
	button_e->setFixedSize(80, 80);
	button_10_X->setFixedSize(80, 80);
	button_Exp->setFixedSize(80, 80);
	button_lg->setFixedSize(80, 80);
	button_ln->setFixedSize(80, 80);
	button_sin->setFixedSize(80, 80);
	button_cos->setFixedSize(80, 80);
	button_tan->setFixedSize(80, 80);
	button_opp->setFixedSize(80, 80);
	button_00->setFixedSize(80, 80);
	button_decpoint->setFixedSize(80, 80);
	button_PI->setFixedSize(80, 80);
	button_arcsin->setFixedSize(80, 80);
	button_arccos->setFixedSize(80, 80);
	button_arctan->setFixedSize(80, 80);
	button_backspace->setFixedSize(80, 80);
	button_factorial->setFixedSize(80, 80);
	button_left->setFixedSize(80, 80);
	button_right->setFixedSize(80, 80);

	//网格布局
	QGridLayout *Grid = new QGridLayout;
	Grid->addWidget(up, 1, 1, 1, 9, Qt::Alignment());
	Grid->addWidget(down, 2, 1, 1, 9, Qt::Alignment());
	//六个参数的含义
	//部件指针, 所在行, 所在列, 占用行数, 占用列数, 对齐方式
	Grid->addWidget(button_square, 3, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_e, 7, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_sin, 3, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_cos, 3, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_tan, 3, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_clearAll, 3, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_clear, 3, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_backspace, 3, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_devide, 3, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_cube, 4, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_10_X, 6, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_lg, 5, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_ln, 5, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_opp, 5, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_7, 4, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_8, 4, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_9, 4, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_multiply, 4, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_sq_root, 5, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_Exp, 6, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_PI, 7, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_4, 5, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_5, 5, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_6, 5, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_minus, 5, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_reciprocal, 7, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_factorial, 7, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_left, 6, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_right, 6, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_1, 6, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_2, 6, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_3, 6, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_plus, 6, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_arcsin, 4, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_arccos, 4, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_arctan, 4, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_0, 7, 5, Qt::Alignment());
	Grid->addWidget(button_00, 7, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_decpoint, 7, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_equal, 7, 8, 1, 1, Qt::Alignment());

	//把Grid布局设置给当前创建的对象
	this->setLayout(Grid);

	//让最大化按钮灰显
	this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);

	//画面美化
	Beautiful();

	//实现连接函数
	connect(button_0, SIGNAL(clicked(bool)), this, SLOT(button_0_clicked()));
	connect(button_1, SIGNAL(clicked(bool)), this, SLOT(button_1_clicked()));
	connect(button_2, SIGNAL(clicked(bool)), this, SLOT(button_2_clicked()));
	connect(button_3, SIGNAL(clicked(bool)), this, SLOT(button_3_clicked()));
	connect(button_4, SIGNAL(clicked(bool)), this, SLOT(button_4_clicked()));
	connect(button_5, SIGNAL(clicked(bool)), this, SLOT(button_5_clicked()));
	connect(button_6, SIGNAL(clicked(bool)), this, SLOT(button_6_clicked()));
	connect(button_7, SIGNAL(clicked(bool)), this, SLOT(button_7_clicked()));
	connect(button_8, SIGNAL(clicked(bool)), this, SLOT(button_8_clicked()));
	connect(button_9, SIGNAL(clicked(bool)), this, SLOT(button_9_clicked()));
	connect(button_plus, SIGNAL(clicked(bool)), this, SLOT(button_plus_clicked()));
	connect(button_minus, SIGNAL(clicked(bool)), this, SLOT(button_minus_clicked()));
	connect(button_multiply, SIGNAL(clicked(bool)), this, SLOT(button_multiply_clicked()));
	connect(button_devide, SIGNAL(clicked(bool)), this, SLOT(button_devide_clicked()));
	connect(button_equal, SIGNAL(clicked(bool)), this, SLOT(button_equal_clicked()));
	connect(button_clear, SIGNAL(clicked(bool)), this, SLOT(button_clear_clicked()));
	connect(button_clearAll, SIGNAL(clicked(bool)), this, SLOT(button_clearAll_clicked()));
	connect(button_square, SIGNAL(clicked(bool)), this, SLOT(button_square_clicked()));
	connect(button_cube, SIGNAL(clicked(bool)), this, SLOT(button_cube_clicked()));
	connect(button_sq_root, SIGNAL(clicked(bool)), this, SLOT(button_sq_root_clicked()));
	connect(button_reciprocal, SIGNAL(clicked(bool)), this, SLOT(button_reciprocal_clicked()));
	connect(button_e, SIGNAL(clicked(bool)), this, SLOT(button_e_clicked()));
	connect(button_10_X, SIGNAL(clicked(bool)), this, SLOT(button_10_X_clicked()));
	connect(button_Exp, SIGNAL(clicked(bool)), this, SLOT(button_Exp_clicked()));
	connect(button_lg, SIGNAL(clicked(bool)), this, SLOT(button_lg_clicked()));
	connect(button_ln, SIGNAL(clicked(bool)), this, SLOT(button_ln_clicked()));
	connect(button_sin, SIGNAL(clicked(bool)), this, SLOT(button_sin_clicked()));
	connect(button_cos, SIGNAL(clicked(bool)), this, SLOT(button_cos_clicked()));
	connect(button_tan, SIGNAL(clicked(bool)), this, SLOT(button_tan_clicked()));
	connect(button_opp, SIGNAL(clicked(bool)), this, SLOT(button_opp_clicked()));
	connect(button_00, SIGNAL(clicked(bool)), this, SLOT(button_00_clicked()));
	connect(button_decpoint, SIGNAL(clicked(bool)), this, SLOT(button_decpoint_clicked()));
	connect(button_PI, SIGNAL(clicked(bool)), this, SLOT(button_PI_clicked()));
	connect(button_arcsin, SIGNAL(clicked(bool)), this, SLOT(button_arcsin_clicked()));
	connect(button_arccos, SIGNAL(clicked(bool)), this, SLOT(button_arccos_clicked()));
	connect(button_arctan, SIGNAL(clicked(bool)), this, SLOT(button_arctan_clicked()));
	connect(button_backspace, SIGNAL(clicked(bool)), this, SLOT(button_backspace_clicked()));
	connect(button_factorial, SIGNAL(clicked(bool)), this, SLOT(button_factorial_clicked()));
	connect(button_left, SIGNAL(clicked(bool)), this, SLOT(button_left_clicked()));
	connect(button_right, SIGNAL(clicked(bool)), this, SLOT(button_right_clicked()));
}

Calculator::~Calculator()
{
}

std::string Calculator::Delete_zeros(std::string str)
{
	//str是double转string，所以必定有小数点.
	int i;
	for (i = str.length() - 1; i >= 0; --i)
	{
		if (str[i] == '.')
			break;
		if (str[i] != '0')
		{
			str = str.substr(0, i + 1);
			return str;
		}
	}
	return str.substr(0, i);
}

double Calculator::Solve(QString str, int choice)
{
	if (choice == Method)
		return Evaluation(Postfix_Expression(Split(str.toStdString())));
	else if (choice == ZWSMethod)
		return stod(Delete_zeros((calculate(str.toStdString()))));
	else
		return 0;
}

void Calculator::Buttons_Disabled()
{
	button_0->setDisabled(true);
	button_1->setDisabled(true);
	button_2->setDisabled(true);
	button_3->setDisabled(true);
	button_4->setDisabled(true);
	button_5->setDisabled(true);
	button_6->setDisabled(true);
	button_7->setDisabled(true);
	button_8->setDisabled(true);
	button_9->setDisabled(true);
	button_plus->setDisabled(true);
	button_minus->setDisabled(true);
	button_multiply->setDisabled(true);
	button_devide->setDisabled(true);
	button_equal->setDisabled(true);
	//button_clear->setDisabled(true);
	//button_clearAll->setDisabled(true);
	button_square->setDisabled(true);
	button_cube->setDisabled(true);
	button_sq_root->setDisabled(true);
	button_reciprocal->setDisabled(true);
	button_e->setDisabled(true);
	button_10_X->setDisabled(true);
	button_Exp->setDisabled(true);
	button_lg->setDisabled(true);
	button_ln->setDisabled(true);
	button_sin->setDisabled(true);
	button_cos->setDisabled(true);
	button_tan->setDisabled(true);
	button_opp->setDisabled(true);
	button_00->setDisabled(true);
	button_decpoint->setDisabled(true);
	button_PI->setDisabled(true);
	button_arcsin->setDisabled(true);
	button_arccos->setDisabled(true);
	button_arctan->setDisabled(true);
	button_backspace->setDisabled(true);
	button_factorial->setDisabled(true);
	button_left->setDisabled(true);
	button_right->setDisabled(true);
}

void Calculator::Buttons_Enabled()
{
	button_0->setEnabled(true);
	button_1->setEnabled(true);
	button_2->setEnabled(true);
	button_3->setEnabled(true);
	button_4->setEnabled(true);
	button_5->setEnabled(true);
	button_6->setEnabled(true);
	button_7->setEnabled(true);
	button_8->setEnabled(true);
	button_9->setEnabled(true);
	button_plus->setEnabled(true);
	button_minus->setEnabled(true);
	button_multiply->setEnabled(true);
	button_devide->setEnabled(true);
	button_equal->setEnabled(true);
	//button_clear->setEnabled(true);
	//button_clearAll->setEnabled(true);
	button_square->setEnabled(true);
	button_cube->setEnabled(true);
	button_sq_root->setEnabled(true);
	button_reciprocal->setEnabled(true);
	button_e->setEnabled(true);
	button_10_X->setEnabled(true);
	button_Exp->setEnabled(true);
	button_lg->setEnabled(true);
	button_ln->setEnabled(true);
	button_sin->setEnabled(true);
	button_cos->setEnabled(true);
	button_tan->setEnabled(true);
	button_opp->setEnabled(true);
	button_00->setEnabled(true);
	button_decpoint->setEnabled(true);
	button_PI->setEnabled(true);
	button_arcsin->setEnabled(true);
	button_arccos->setEnabled(true);
	button_arctan->setEnabled(true);
	button_backspace->setEnabled(true);
	button_factorial->setEnabled(true);
	button_left->setEnabled(true);
	button_right->setEnabled(true);
}

void Calculator::button_decpoint_clicked()
{
	if (decp)//按过小数点再按就冇事发生
		return;
	if (!zeros && current_Num == 0)//如果当前数字为0且想要连续输入0
	{
		output = "0.";
		zeros = true;
	}
	else if (zeros)
	{
		return;
	}
	else
	{
		output += ".";
	}
	down->setText(output);
	//
	decp = true;
}

void Calculator::button_0_clicked()
{
	if (decp)//有小数点
	{
		output += "0";

		current_Num += 0 * pow(10, -decp_counter);

		decp_counter++;//小数点位数增加
	}
	else//无小数点
	{
		if (current_Num == 0)
		{
			output = "0";
		}
		else
		{
			output += "0";
		}
		current_Num = current_Num * 10;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_1_clicked()
{
	if (decp)
	{
		output += "1";

		current_Num += 1 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "1";
		}
		else
		{
			output += "1";
		}
		current_Num = current_Num * 10 + 1;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_2_clicked()
{
	if (decp)
	{
		output += "2";

		current_Num += 2 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "2";
		}
		else
		{
			output += "2";
		}
		current_Num = current_Num * 10 + 2;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_3_clicked()
{
	if (decp)
	{
		output += "3";

		current_Num += 3 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "3";
		}
		else
		{
			output += "3";
		}
		current_Num = current_Num * 10 + 3;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_4_clicked()
{
	if (decp)
	{
		output += "4";

		current_Num += 4 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "4";
		}
		else
		{
			output += "4";
		}
		current_Num = current_Num * 10 + 4;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_5_clicked()
{
	if (decp)
	{
		output += "5";

		current_Num += 5 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "5";
		}
		else
		{
			output += "5";
		}
		current_Num = current_Num * 10 + 5;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_6_clicked()
{
	if (decp)
	{
		output += "6";

		current_Num += 6 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "6";
		}
		else
		{
			output += "6";
		}
		current_Num = current_Num * 10 + 6;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_7_clicked()
{
	if (decp)
	{
		output += "7";

		current_Num += 7 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "7";
		}
		else
		{
			output += "7";
		}
		current_Num = current_Num * 10 + 7;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_8_clicked()
{
	if (decp)
	{
		output += "8";

		current_Num += 8 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "8";
		}
		else
		{
			output += "8";
		}
		current_Num = current_Num * 10 + 8;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_9_clicked()
{
	if (decp)
	{
		output += "9";

		current_Num += 9 * pow(10, -decp_counter);

		decp_counter++;
	}
	else
	{
		if (current_Num == 0)
		{
			output = "9";
		}
		else
		{
			output += "9";
		}
		current_Num = current_Num * 10 + 9;
	}
	down->setText(output);
	//
	mark_occupy = false;
}

void Calculator::button_plus_clicked()
{
	if (mark_occupy)//如果正在连续输入运算符
	{
		to_solve.chop(1);//从尾部删除1个字符
		to_solve += '+';
		up->setText(to_solve);
		return;
	}
	if (to_solve.length() > 1 && to_solve[to_solve.length() - 1] == ')')
	{

	}
	else
	{
		to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	//将当前数字及符号压入上方算式
	to_solve += "+";
	up->setText(to_solve);
	//可能用不到的副本
	QString temp = to_solve.left(to_solve.length() - 1);
	//计算之前先进行判断
	switch (per_judge(to_solve.left(to_solve.length() - 1).toStdString()))
	{
	case DevideByZero:
		ERROR(DevideByZero);
		return;
		break;
	case InvalidInput:
		ERROR(InvalidInput);
		return;
		break;
	case BracketsWrong:
		ERROR(BracketsWrong);
		return;
		break;
	case NeedBrackets:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		answer = Solve(temp, Method);
		break;
	case NoBrackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), ZWSMethod);
		break;
	case Brackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), Method);
		break;
	case ElseDeal:
		temp.prepend("0");
		answer = Solve(temp, Method);
		break;
	case NBandED:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		temp.prepend('0');
		answer = Solve(temp, Method);
		break;
	}
	//当前数字归零
	current_Num = 0;
	//
	output = QString::fromStdString(Delete_zeros(std::to_string(answer)));
	down->setText(output);
	//
	mark_occupy = true;
	decp = false;
	decp_counter = 1;
	zeros = false;
}

void Calculator::button_minus_clicked()
{
	if (mark_occupy)
	{
		to_solve.chop(1);//从尾部删除1个字符
		to_solve += '-';
		up->setText(to_solve);
		return;
	}
	if (to_solve.length() > 1 && to_solve[to_solve.length() - 1] == ')')
	{

	}
	else
	{
		to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	//将当前数字及符号压入上方算式
	to_solve += "-";
	up->setText(to_solve);
	//可能用不到的副本
	QString temp = to_solve.left(to_solve.length() - 1);
	//计算之前先进行判断
	switch (per_judge(to_solve.left(to_solve.length() - 1).toStdString()))
	{
	case DevideByZero:
		ERROR(DevideByZero);
		return;
		break;
	case InvalidInput:
		ERROR(InvalidInput);
		return;
		break;
	case BracketsWrong:
		ERROR(BracketsWrong);
		return;
		break;
	case NeedBrackets:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		answer = Solve(temp, Method);
		break;
	case NoBrackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), ZWSMethod);
		break;
	case Brackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), Method);
		break;
	case ElseDeal:
		temp.prepend("0");
		answer = Solve(temp, Method);
		break;
	case NBandED:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		temp.prepend('0');
		answer = Solve(temp, Method);
		break;
	}
	//当前数字归零
	current_Num = 0;
	//
	output = QString::fromStdString(Delete_zeros(std::to_string(answer)));
	down->setText(output);
	//
	mark_occupy = true;
	decp = false;
	decp_counter = 1;
	zeros = false;
}

void Calculator::button_multiply_clicked()
{
	if (mark_occupy)
	{
		to_solve.chop(1);//从尾部删除1个字符
		to_solve += '*';
		up->setText(to_solve);
		return;
	}
	if (to_solve.length() > 1 && to_solve[to_solve.length() - 1] == ')')
	{

	}
	else
	{
		to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	//将当前数字及符号压入上方算式
	to_solve += "*";
	up->setText(to_solve);
	//可能用不到的副本
	QString temp = to_solve.left(to_solve.length() - 1);
	//计算之前先进行判断
	switch (per_judge(to_solve.left(to_solve.length() - 1).toStdString()))
	{
	case DevideByZero:
		ERROR(DevideByZero);
		return;
		break;
	case InvalidInput:
		ERROR(InvalidInput);
		return;
		break;
	case BracketsWrong:
		ERROR(BracketsWrong);
		return;
		break;
	case NeedBrackets:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		answer = Solve(temp, Method);
		break;
	case NoBrackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), ZWSMethod);
		break;
	case Brackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), Method);
		break;
	case ElseDeal:
		temp.prepend("0");
		answer = Solve(temp, Method);
		break;
	case NBandED:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		temp.prepend('0');
		answer = Solve(temp, Method);
		break;
	}
	//当前数字归零
	current_Num = 0;
	//
	output = QString::fromStdString(Delete_zeros(std::to_string(answer)));
	down->setText(output);
	//
	mark_occupy = true;
	decp = false;
	decp_counter = 1;
	zeros = false;
}

void Calculator::button_devide_clicked()
{
	if (mark_occupy)
	{
		to_solve.chop(1);//从尾部删除1个字符
		to_solve += '/';
		up->setText(to_solve);
		return;
	}
	if (to_solve.length() > 1 && to_solve[to_solve.length() - 1] == ')')
	{

	}
	else
	{
		to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	//将当前数字及符号压入上方算式
	to_solve += "/";
	up->setText(to_solve);
	//可能用不到的副本
	QString temp = to_solve.left(to_solve.length() - 1);
	//计算之前先进行判断
	switch (per_judge(to_solve.left(to_solve.length() - 1).toStdString()))
	{
	case DevideByZero:
		ERROR(DevideByZero);
		return;
		break;
	case InvalidInput:
		ERROR(InvalidInput);
		return;
		break;
	case BracketsWrong:
		ERROR(BracketsWrong);
		return;
		break;
	case NeedBrackets:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		answer = Solve(temp, Method);
		break;
	case NoBrackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), ZWSMethod);
		break;
	case Brackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), Method);
		break;
	case ElseDeal:
		temp.prepend("0");
		answer = Solve(temp, Method);
		break;
	case NBandED:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		temp.prepend('0');
		answer = Solve(temp, Method);
		break;
	}
	//当前数字归零
	current_Num = 0;
	//
	output = QString::fromStdString(Delete_zeros(std::to_string(answer)));
	down->setText(output);
	//
	mark_occupy = true;
	decp = false;
	decp_counter = 1;
	zeros = false;
}

void Calculator::button_equal_clicked()
{
	//上方输出算式
	if (to_solve.length() > 1 && to_solve[to_solve.length() - 1] == ')')
	{

	}
	else
	{
		to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	to_solve += "=";
	up->setText(to_solve);
	//可能用不到的副本
	QString temp = to_solve.left(to_solve.length() - 1);
	//计算之前先进行判断
	switch (per_judge(to_solve.left(to_solve.length() - 1).toStdString()))
	{
	case DevideByZero:
		ERROR(DevideByZero);
		return;
		break;
	case InvalidInput:
		ERROR(InvalidInput);
		return;
		break;
	case BracketsWrong:
		ERROR(BracketsWrong);
		return;
		break;
	case NeedBrackets:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		answer = Solve(temp, Method);
		break;
	case NoBrackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), ZWSMethod);
		break;
	case Brackets:
		answer = Solve(to_solve.left(to_solve.length() - 1), Method);
		break;
	case ElseDeal:
		temp.prepend('0');
		answer = Solve(temp, Method);
		break;
	case NBandED:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		temp.prepend('0');
		answer = Solve(temp, Method);
		break;
	}
	output = QString::fromStdString(Delete_zeros(std::to_string(answer)));
	down->setText(output);
	//让所有按钮灰显
	Buttons_Disabled();
	Error = true;
}

void Calculator::button_clear_clicked()
{
	current_Num = 0;
	output = "0";
	down->setText(output);
	mark_occupy = false;//相当于把当前数字置零
	decp = false;
	decp_counter = 1;
	zeros = false;
	Buttons_Enabled();
	if (Error == true)
	{
		to_solve = "";
		up->setText(to_solve);
		Error = false;
	}
}

void Calculator::button_clearAll_clicked()
{
	current_Num = 0;
	output = "0";
	down->setText(output);
	mark_occupy = false;
	decp = false;
	decp_counter = 1;
	zeros = false;
	Buttons_Enabled();
	Error = false;
	//清空所有算式
	to_solve = "";
	up->setText(to_solve);
	//清空左括号
	Left_counter = 0;
	button_left->setText("(");
}

void Calculator::button_backspace_clicked()
{
	if (output == "0" || !zeros && current_Num == 0)//显示为0就不用处理
		return;
	if (output.length() == 1)//长度为1就置零
	{
		output = "0";
		current_Num = 0;
	}
	else if (output[output.length() - 1] == '.')
	{
		//如果退了小数点，则当前数字不是小数
		output.chop(1);//从尾部截去一个字符
		decp = false;
		decp_counter = 1;
		zeros = false;
	}
	else if (decp)//如果是小数
	{
		double last = output[output.length() - 1].digitValue();
		decp_counter--;
		current_Num -= last * pow(10, -decp_counter);
		output.chop(1);
	}
	else//如果是整数
	{
		output.chop(1);
		current_Num = (int)current_Num / 10;
	}
	down->setText(output);
}

void Calculator::button_00_clicked()
{
	if (decp)//有小数点
	{
		output += "00";

		current_Num += 0 * pow(10, -decp_counter) + 0 * pow(10, -(++decp_counter));

		decp_counter++;//小数点位数增加
	}
	else//无小数点
	{
		if (current_Num == 0)
		{
			output = "0";
		}
		else
		{
			output += "00";
		}
		current_Num = current_Num * 100;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_opp_clicked()
{
	if (output[0] == '-')//如果是负数
	{
		current_Num = output.remove(0, 1).toDouble();//在output头删去负号
	}
	else//正数
	{
		current_Num = output.prepend("-").toDouble();//前拼接负号
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_cube_clicked()
{
	current_Num = pow(current_Num, 3);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_sq_root_clicked()
{
	if (current_Num < 0)
	{
		ERROR(InvalidInput);
		return;
	}
	else
	{
		current_Num = pow(current_Num, 0.5);
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_square_clicked()
{
	current_Num = pow(current_Num, 2);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_sin_clicked()
{
	current_Num = sin(current_Num / 180 * PI);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_cos_clicked()
{
	current_Num = cos(current_Num / 180 * PI);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_tan_clicked()
{
	if ((fmod(current_Num, 360) == 90) || (fmod(current_Num, 360) == 270))
	{
		ERROR(InvalidInput);
		return;
	}
	else
	{
		current_Num = tan(current_Num / 180 * PI);
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_Exp_clicked()
{
	current_Num = exp(current_Num);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}

	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_ln_clicked()
{
	if (current_Num < 0)
	{
		ERROR(InvalidInput);
		return;
	}
	else
	{
		current_Num = log(current_Num);
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_lg_clicked()
{
	if (current_Num < 0)
	{
		ERROR(InvalidInput);
		return;
	}
	else
	{
		current_Num = log10(current_Num);
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_10_X_clicked()
{
	current_Num = pow(10, current_Num);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_reciprocal_clicked()
{
	if (current_Num == 0)
	{
		ERROR(InvalidInput);
		return;
	}
	else
	{
		current_Num = 1.0 / current_Num;
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_factorial_clicked()
{
	if (current_Num < 0)
	{
		ERROR(InvalidInput);
		return;
	}
	else if (current_Num == 0)
	{
		output = QString::fromStdString(Delete_zeros(std::to_string(1)));
	}
	else
	{
		double total = 1;
		double i = current_Num;
		for (; i >= 1; i--)
		{
			if (i == current_Num)
			{
				total = current_Num;
			}
			else
			{
				total *= i;
			}
		}
		if (i != 0)
		{
			total *= (i*tgamma(i));
		}
		output = QString::fromStdString(Delete_zeros(std::to_string(total)));
		current_Num = total;
	}
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_e_clicked()
{
	current_Num = e;
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	down->setText(output);
	decp = true;
	decp_counter = 7;
	mark_occupy = false;
}

void Calculator::button_PI_clicked()
{
	current_Num = PI;
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	down->setText(output);
	decp = true;
	decp_counter = 7;
	mark_occupy = false;
}

void Calculator::button_arcsin_clicked()
{
	if (current_Num < -1 || current_Num > 1)
	{
		ERROR(InvalidInput);
		return;
	}
	else
	{
		current_Num = asin(current_Num) / PI * 180;
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_arccos_clicked()
{
	if (current_Num < -1 || current_Num > 1)
	{
		ERROR(InvalidInput);
		return;
	}
	else
	{
		current_Num = acos(current_Num) / PI * 180;
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_arctan_clicked()
{
	current_Num = atan(current_Num) / PI * 180;
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	if (current_Num == int(current_Num))
	{
		decp = false;
		decp_counter = 1;
	}
	else
	{
		decp = true;
		int i = 0;
		for (; Delete_zeros(std::to_string(current_Num))[i] != '.'; i++)
		{
		}
		int len = Delete_zeros(std::to_string(current_Num)).length() - i - 1;
		if (len >= 6) decp_counter = 7;
		else decp_counter = len + 1;
	}
	down->setText(output);
	mark_occupy = false;
}

void Calculator::button_left_clicked()
{
	if (to_solve.length() > 1 && to_solve[to_solve.length() - 1] == ')')
	{

	}
	else
	{
		to_solve += '(';
		Left_counter++;
	}
	//
	QString temp;
	if (Left_counter == 0)
	{
		temp = "(";
	}
	else
	{
		temp = "(" + QString::fromStdString(std::to_string(Left_counter));
	}
	button_left->setText(temp);
	up->setText(to_solve);
	//
	mark_occupy = false;//这里改为false
}

void Calculator::button_right_clicked()
{
	if (Left_counter == 0)//没有左括号时不能按右括号
		return;
	//将当前数字压入上方算式然后再补充右括号
	to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	//加上右括号
	to_solve += ')';
	up->setText(to_solve);
	Left_counter--;
	QString temp;
	if (Left_counter == 0)
	{
		temp = "(";
	}
	else
	{
		temp = "(" + QString::fromStdString(std::to_string(Left_counter));
	}
	button_left->setText(temp);
	//可能用不到的副本
	temp = to_solve;
	//计算之前先进行判断
	switch (per_judge(to_solve.toStdString()))
	{
	case DevideByZero:
		ERROR(DevideByZero);
		return;
		break;
	case InvalidInput:
		ERROR(InvalidInput);
		return;
		break;
	case BracketsWrong:
		ERROR(BracketsWrong);
		return;
		break;
	case NeedBrackets:
		for (int i = 0; i < Brackets_counter; ++i)
		{
			temp += ")";
		}
		answer = Solve(temp, Method);
		break;
	case NoBrackets:
		answer = Solve(to_solve, ZWSMethod);
		break;
	case Brackets:
		answer = Solve(to_solve, Method);
		break;
	}
	//当前数字归零
	current_Num = 0;
	//
	output = QString::fromStdString(Delete_zeros(std::to_string(answer)));
	down->setText(output);
	//
	mark_occupy = false;//这里改为false
	decp = false;
	decp_counter = 1;
	zeros = false;
}

void Calculator::Beautiful()
{
	button_0->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_1->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_2->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_3->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_4->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_5->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_6->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_7->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_8->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_9->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_00->setStyleSheet("QPushButton{background-color:white;\
		color: black;   border - radius: 10px;  border: 2px groove gray; \
		border - style: outset;}"
		"QPushButton:hover{background-color:gray; color: black;}"
		"QPushButton:pressed{background-color:silver;\
		border - style: inset; }"
	);
	button_0->setFont(QFont("0", 20, QFont::Bold));
	button_1->setFont(QFont("0", 20, QFont::Bold));
	button_2->setFont(QFont("0", 20, QFont::Bold));
	button_3->setFont(QFont("0", 20, QFont::Bold));
	button_4->setFont(QFont("0", 20, QFont::Bold));
	button_5->setFont(QFont("0", 20, QFont::Bold));
	button_6->setFont(QFont("0", 20, QFont::Bold));
	button_7->setFont(QFont("0", 20, QFont::Bold));
	button_8->setFont(QFont("0", 20, QFont::Bold));
	button_9->setFont(QFont("0", 20, QFont::Bold));
	button_00->setFont(QFont("0", 20, QFont::Bold));
	//button_decpoint->setFont(QFont("0", 12, QFont::Bold));
	button_clear->setFont(QFont("0", 14, QFont::Bold));
	button_clearAll->setFont(QFont("0", 14, QFont::Bold));
	button_backspace->setFont(QFont("0", 14, QFont::Bold));
	button_plus->setFont(QFont("0", 14, QFont::Black));
	button_minus->setFont(QFont("0", 14, QFont::Black));
	button_multiply->setFont(QFont("0", 14, QFont::Black));
	button_devide->setFont(QFont("0", 14, QFont::Black));
	button_equal->setFont(QFont("0", 14, QFont::Black));
}