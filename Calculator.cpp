#include "Calculator.h"
#include <stdexcept>
#include <iostream>
//#include <vector>
#include <QVector>
#include <string>
//#include <stack>
#include <QStack>
#include <regex>
#include <cmath>
#define PI 3.14159265 
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

Calculator::Calculator(QWidget *parent)

	: QWidget(parent)

{

	//ui.setupUi(this);



	//初始化数据成员

	current_Num = 0;

	answer = 0;



	output = "";

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

	button_multiply = new QPushButton("*");

	button_devide = new QPushButton("/");

	button_equal = new QPushButton("=");

	button_clear = new QPushButton("CE");

	button_clearAll = new QPushButton("C");

	button_square = new QPushButton("x^2");

	button_cube = new QPushButton("x^3");

	button_sq_root = new QPushButton("sqr");

	button_reciprocal = new QPushButton("1/x");

	button_x_Y = new QPushButton("x^y");

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

	button_Mod = new QPushButton("Mod");

	button_Lsh = new QPushButton("Lsh");

	button_Rsh = new QPushButton("Rsh");

	button_RoL = new QPushButton("RoL");

	button_RoR = new QPushButton("RoR");

	button_Or = new QPushButton("Or");

	button_Xor = new QPushButton("Xor");

	button_Not = new QPushButton("Not");

	button_And = new QPushButton("And");

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

	up->setFixedSize(800, 35);

	down->setFixedSize(800, 35);



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

	button_x_Y->setFixedSize(80, 80);

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

	button_Mod->setFixedSize(80, 80);

	button_Lsh->setFixedSize(80, 80);

	button_Rsh->setFixedSize(80, 80);

	button_RoL->setFixedSize(80, 80);

	button_RoR->setFixedSize(80, 80);

	button_Or->setFixedSize(80, 80);

	button_Xor->setFixedSize(80, 80);

	button_Not->setFixedSize(80, 80);

	button_And->setFixedSize(80, 80);

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

	Grid->addWidget(button_x_Y, 3, 2, 1, 1, Qt::Alignment());

	Grid->addWidget(button_sin, 3, 3, 1, 1, Qt::Alignment());

	Grid->addWidget(button_cos, 3, 4, 1, 1, Qt::Alignment());

	Grid->addWidget(button_tan, 3, 5, 1, 1, Qt::Alignment());

	Grid->addWidget(button_clearAll, 3, 6, 1, 1, Qt::Alignment());

	Grid->addWidget(button_clear, 3, 7, 1, 1, Qt::Alignment());

	Grid->addWidget(button_backspace, 3, 8, 1, 1, Qt::Alignment());

	Grid->addWidget(button_devide, 3, 9, 1, 1, Qt::Alignment());

	Grid->addWidget(button_cube, 4, 1, 1, 1, Qt::Alignment());

	Grid->addWidget(button_10_X, 4, 2, 1, 1, Qt::Alignment());

	Grid->addWidget(button_lg, 4, 3, 1, 1, Qt::Alignment());

	Grid->addWidget(button_ln, 4, 4, 1, 1, Qt::Alignment());

	Grid->addWidget(button_opp, 4, 5, 1, 1, Qt::Alignment());

	Grid->addWidget(button_7, 4, 6, 1, 1, Qt::Alignment());

	Grid->addWidget(button_8, 4, 7, 1, 1, Qt::Alignment());

	Grid->addWidget(button_9, 4, 8, 1, 1, Qt::Alignment());

	Grid->addWidget(button_multiply, 4, 9, 1, 1, Qt::Alignment());

	Grid->addWidget(button_sq_root, 5, 1, 1, 1, Qt::Alignment());

	Grid->addWidget(button_Exp, 5, 2, 1, 1, Qt::Alignment());

	Grid->addWidget(button_Mod, 5, 3, 1, 1, Qt::Alignment());

	Grid->addWidget(button_Xor, 5, 4, 1, 1, Qt::Alignment());

	Grid->addWidget(button_Or, 5, 5, 1, 1, Qt::Alignment());

	Grid->addWidget(button_4, 5, 6, 1, 1, Qt::Alignment());

	Grid->addWidget(button_5, 5, 7, 1, 1, Qt::Alignment());

	Grid->addWidget(button_6, 5, 8, 1, 1, Qt::Alignment());

	Grid->addWidget(button_minus, 5, 9, 1, 1, Qt::Alignment());

	Grid->addWidget(button_reciprocal, 6, 1, 1, 1, Qt::Alignment());

	Grid->addWidget(button_factorial, 6, 2, 1, 1, Qt::Alignment());

	Grid->addWidget(button_left, 6, 3, 1, 1, Qt::Alignment());

	Grid->addWidget(button_right, 6, 4, 1, 1, Qt::Alignment());

	Grid->addWidget(button_And, 6, 5, 1, 1, Qt::Alignment());

	Grid->addWidget(button_1, 6, 6, 1, 1, Qt::Alignment());

	Grid->addWidget(button_2, 6, 7, 1, 1, Qt::Alignment());

	Grid->addWidget(button_3, 6, 8, 1, 1, Qt::Alignment());

	Grid->addWidget(button_plus, 6, 9, 1, 1, Qt::Alignment());

	Grid->addWidget(button_Lsh, 7, 1, 1, 1, Qt::Alignment());

	Grid->addWidget(button_Rsh, 7, 2, 1, 1, Qt::Alignment());

	Grid->addWidget(button_RoL, 7, 3, 1, 1, Qt::Alignment());

	Grid->addWidget(button_RoR, 7, 4, 1, 1, Qt::Alignment());

	Grid->addWidget(button_Not, 7, 5, 1, 1, Qt::Alignment());

	Grid->addWidget(button_0, 7, 6, Qt::Alignment());

	Grid->addWidget(button_00, 7, 7, 1, 1, Qt::Alignment());

	Grid->addWidget(button_decpoint, 7, 8, 1, 1, Qt::Alignment());

	Grid->addWidget(button_equal, 7, 9, 1, 1, Qt::Alignment());



	//把Grid布局设置给当前创建的对象

	this->setLayout(Grid);



	//让最大化按钮灰显

	this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);



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

	connect(button_x_Y, SIGNAL(clicked(bool)), this, SLOT(button_x_Y_clicked()));

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

	connect(button_Mod, SIGNAL(clicked(bool)), this, SLOT(button_Mod_clicked()));

	connect(button_Lsh, SIGNAL(clicked(bool)), this, SLOT(button_Lsh_clicked()));

	connect(button_Rsh, SIGNAL(clicked(bool)), this, SLOT(button_Rsh_clicked()));

	connect(button_RoL, SIGNAL(clicked(bool)), this, SLOT(button_RoL_clicked()));

	connect(button_RoR, SIGNAL(clicked(bool)), this, SLOT(button_RoR_clicked()));

	connect(button_Or, SIGNAL(clicked(bool)), this, SLOT(button_Or_clicked()));

	connect(button_Xor, SIGNAL(clicked(bool)), this, SLOT(button_Xor_clicked()));

	connect(button_Not, SIGNAL(clicked(bool)), this, SLOT(button_Not_clicked()));

	connect(button_And, SIGNAL(clicked(bool)), this, SLOT(button_And_clicked()));

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



double Calculator::Solve(QString str)

{

	return Evaluation(Postfix_Expression(Split(str.toStdString())));

	//return 0;

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

	button_x_Y->setDisabled(true);

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

	button_Mod->setDisabled(true);

	button_Lsh->setDisabled(true);

	button_Rsh->setDisabled(true);

	button_RoL->setDisabled(true);

	button_RoR->setDisabled(true);

	button_Or->setDisabled(true);

	button_Xor->setDisabled(true);

	button_Not->setDisabled(true);

	button_And->setDisabled(true);

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

	button_x_Y->setEnabled(true);

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

	button_Mod->setEnabled(true);

	button_Lsh->setEnabled(true);

	button_Rsh->setEnabled(true);

	button_RoL->setEnabled(true);

	button_RoR->setEnabled(true);

	button_Or->setEnabled(true);

	button_Xor->setEnabled(true);

	button_Not->setEnabled(true);

	button_And->setEnabled(true);

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

	//将当前数字及符号压入上方算式

	to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));

	to_solve += "+";

	up->setText(to_solve);

	//显示数字为上方算式暂时的答案

	answer = Solve(to_solve.left(to_solve.length() - 1));

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

	//将当前数字及符号压入上方算式

	to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));

	to_solve += "-";

	up->setText(to_solve);

	//显示数字为上方算式暂时的答案

	answer = Solve(to_solve.left(to_solve.length() - 1));

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

	//将当前数字及符号压入上方算式

	to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));

	to_solve += "*";

	up->setText(to_solve);

	//显示数字为上方算式暂时的答案

	answer = Solve(to_solve.left(to_solve.length() - 1));

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

	//将当前数字及符号压入上方算式

	to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));

	to_solve += "/";

	up->setText(to_solve);

	//显示数字为上方算式暂时的答案

	answer = Solve(to_solve.left(to_solve.length() - 1));

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

	to_solve += QString::fromStdString(Delete_zeros(std::to_string(current_Num)));

	to_solve += "=";

	up->setText(to_solve);

	//下方输出结果

	answer = Solve(to_solve.left(to_solve.length() - 1));

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

}



void Calculator::button_backspace_clicked()

{

	if (output == "0")//显示为0就不用处理

		return;

	if (output.length() == 1)//长度为1就置零

	{

		output = "0";

		current_Num /= 10;

	}

	else if (output[output.length() - 1] == '.')

	{

		//如果退了小数点，则当前数字不是小数

		output.chop(1);//从尾部截去一个字符

		decp = 0;

		decp_counter = 1;

		zeros = false;

	}

	else

	{

		output.chop(1);//从尾部截去一个字符

	}

	down->setText(output);

}



void Calculator::button_00_clicked()

{



}



void Calculator::button_opp_clicked()

{



}

void Calculator::button_cube_clicked()
{
	current_Num = pow(current_Num, 3);	
	output=QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	down->setText(output);
}

void Calculator::button_sq_root_clicked()
{
	if (current_Num < 0)
	{
		//ERROR(0);
		return;
	}
	else
	{
		current_Num = pow(current_Num, 0.5);
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	down->setText(output);
}

void Calculator::button_square_clicked()
{
	current_Num = pow(current_Num, 2);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	down->setText(output);
}

void Calculator::button_sin_clicked()
{
	current_Num = sin(current_Num/180*PI);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	down->setText(output);
}

void Calculator::button_cos_clicked()
{
	current_Num = cos(current_Num/180*PI);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	down->setText(output);
}

void Calculator::button_tan_clicked()
{
	if ((fmod(current_Num, 360) == 90) || (fmod(current_Num, 360) == 270))
	{
		//ERROR(0);
		return;
	}
	else
	{
		current_Num = tan(current_Num / 180 * PI);
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	down->setText(output);
}

void Calculator::button_Exp_clicked()
{
	current_Num = exp(current_Num);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	down->setText(output);
}

void Calculator::button_ln_clicked()
{
	if (current_Num < 0)
	{
		//ERROR(0);
		return;
	}
	else
	{
		current_Num = log(current_Num);
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	down->setText(output);
}

void Calculator::button_lg_clicked()
{
	if (current_Num < 0)
	{
		//ERROR(0);
		return;
	}
	else
	{
		current_Num = log10(current_Num);
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	down->setText(output);
}

void Calculator::button_10_X_clicked()
{
	current_Num = pow(10, current_Num);
	output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	down->setText(output);
}

void Calculator::button_reciprocal_clicked()
{
	if (current_Num == 0)
	{
		//ERROR(0);
		return;
	}
	else
	{
		current_Num = 1.0/current_Num;
		output = QString::fromStdString(Delete_zeros(std::to_string(current_Num)));
	}
	down->setText(output);
}


