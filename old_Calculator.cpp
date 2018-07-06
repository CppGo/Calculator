#include "old_Calculator.h"

old_Calculator::old_Calculator(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//初始化变量
	current_Num = 0;
	saved_Num = 0;
	answer = 0;
	output = "";

	mark = false;
	mark_occupy = false;

	decp = false;
	decp_counter = 1;

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

	lineEdit = new QLineEdit("0");

	//禁止编辑文本框
	lineEdit->setReadOnly(true);

	lineEdit->setAlignment(Qt::AlignRight);
	lineEdit->setMaxLength(15);

	//设置固定大小
	lineEdit->setFixedSize(800, 70);

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
	Grid->addWidget(lineEdit, 1, 1, 1, 9, Qt::Alignment());
	//六个参数的含义
	//部件指针, 所在行, 所在列, 占用行数, 占用列数, 对齐方式
	Grid->addWidget(button_square, 2, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_x_Y, 2, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_sin, 2, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_cos, 2, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_tan, 2, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_clearAll, 2, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_clear, 2, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_backspace, 2, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_devide, 2, 9, 1, 1, Qt::Alignment());
	Grid->addWidget(button_cube, 3, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_10_X, 3, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_lg, 3, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_ln, 3, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_opp, 3, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_7, 3, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_8, 3, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_9, 3, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_multiply, 3, 9, 1, 1, Qt::Alignment());
	Grid->addWidget(button_sq_root, 4, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_Exp, 4, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_Mod, 4, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_Xor, 4, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_Or, 4, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_4, 4, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_5, 4, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_6, 4, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_minus, 4, 9, 1, 1, Qt::Alignment());
	Grid->addWidget(button_reciprocal, 5, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_factorial, 5, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_left, 5, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_right, 5, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_And, 5, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_1, 5, 6, 1, 1, Qt::Alignment());
	Grid->addWidget(button_2, 5, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_3, 5, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_plus, 5, 9, 1, 1, Qt::Alignment());
	Grid->addWidget(button_Lsh, 6, 1, 1, 1, Qt::Alignment());
	Grid->addWidget(button_Rsh, 6, 2, 1, 1, Qt::Alignment());
	Grid->addWidget(button_RoL, 6, 3, 1, 1, Qt::Alignment());
	Grid->addWidget(button_RoR, 6, 4, 1, 1, Qt::Alignment());
	Grid->addWidget(button_Not, 6, 5, 1, 1, Qt::Alignment());
	Grid->addWidget(button_0, 6, 6, Qt::Alignment());
	Grid->addWidget(button_00, 6, 7, 1, 1, Qt::Alignment());
	Grid->addWidget(button_decpoint, 6, 8, 1, 1, Qt::Alignment());
	Grid->addWidget(button_equal, 6, 9, 1, 1, Qt::Alignment());
	
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

old_Calculator::~old_Calculator()
{
}

std::string old_Calculator::Delete_zeros(std::string str)
{
	int counter = 0;
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == '.')
			counter++;
	}
	if (counter == 0)
		return str;
	for (int i = str.length() - 1; i >= 0; --i)
	{
		if (str[i] != '0')
		{
			str = str.substr(0, i);
			return str;
		}
	}
}

void old_Calculator::button_0_clicked()
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
	lineEdit->setText(output);
	mark_occupy = false;
}

void old_Calculator::button_1_clicked()
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
	lineEdit->setText(output);
	mark_occupy = false;
}

void old_Calculator::button_plus_clicked()
{
	//按下运算符后，立马进行运算
	if (mark_occupy)//如果正在连续输入运算符
	{
		sign = '+';
		return;
	}
	if (mark)//之前有运算符未处理
	{
		switch (sign)//处理之前的运算
		{
		case '+':
			saved_Num += current_Num;
			current_Num = 0;
			break;
		case '-':
			saved_Num -= current_Num;
			current_Num = 0;
			break;
		default:
			break;
		}
		mark = true;//需要输入等于号才能为false
		sign = '+';
	}
	else//之前没有运算符未处理
	{
		saved_Num = current_Num;
		current_Num = 0;

		mark = true;
		sign = '+';
	}
	output = QString::fromStdString(Delete_zeros(std::to_string(saved_Num)));
	lineEdit->setText(output);
	mark_occupy = true;
}

void old_Calculator::button_minus_clicked()
{
	//按下运算符后，立马进行运算
	if (mark_occupy)//如果正在连续输入运算符
	{
		sign = '-';
		return;
	}
	if (mark)//之前有运算符未处理
	{
		switch (sign)//处理之前的运算
		{
		case '+':
			saved_Num += current_Num;
			current_Num = 0;
			break;
		case '-':
			saved_Num -= current_Num;
			current_Num = 0;
			break;
		default:
			break;
		}
		mark = true;//需要输入等于号才能为false
		sign = '-';
	}
	else//之前没有运算符未处理
	{
		saved_Num = current_Num;
		current_Num = 0;

		mark = true;
		sign = '-';
	}
	output = QString::fromStdString(Delete_zeros(std::to_string(saved_Num)));
	lineEdit->setText(output);
	mark_occupy = true;
}

void old_Calculator::button_equal_clicked()
{
	if (mark)
	{
		switch (sign)
		{
		case '+':
			answer = current_Num + saved_Num;
			break;
		case '-':
			answer = saved_Num - current_Num;
			break;
		default:
			break;
		}
	}
	saved_Num = 0;
	current_Num = answer;

	output = QString::fromStdString(Delete_zeros(std::to_string(answer)));
	lineEdit->setText(output);
	mark_occupy = false;
	mark = false;
}
