#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"

#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QGridLayout>
#include <QPoint>

class Calculator : public QWidget
{
	Q_OBJECT

public:
	Calculator(QWidget *parent = Q_NULLPTR);
protected:

	//按钮
	QPushButton* button_0;
	QPushButton* button_1;
	QPushButton* button_2;
	QPushButton* button_3;
	QPushButton* button_4;
	QPushButton* button_5;
	QPushButton* button_6;
	QPushButton* button_7;
	QPushButton* button_8;
	QPushButton* button_9;
	QPushButton* button_plus;		//	+
	QPushButton* button_minus;		//	-
	QPushButton* button_multiply;	//	*
	QPushButton* button_devide;		//	/
	QPushButton* button_equal;		//	=
	QPushButton* button_clear;		//	CE
	QPushButton* button_clearAll;	//	C
	QPushButton* button_square;		//	x^2
	QPushButton* button_cube;		//	x^3
	QPushButton* button_sq_root;	//	sqr
	QPushButton* button_reciprocal;	//	1/x
	QPushButton* button_x_Y;		//	x^y
	QPushButton* button_10_X;		//	10^x
	QPushButton* button_Exp;		//	Exp
	QPushButton* button_lg;			//	lg
	QPushButton* button_ln;			//	ln
	QPushButton* button_sin;		//	sin
	QPushButton* button_cos;		//	cos
	QPushButton* button_tan;		//	tan
	QPushButton* button_opp;		//	+/-
	QPushButton* button_00;			//	00
	QPushButton* button_decpoint;	//	.
	QPushButton* button_Mod;		//	Mod
	QPushButton* button_Lsh;		//	Lsh
	QPushButton* button_Rsh;		//	Rsh
	QPushButton* button_RoL;		//	RoL
	QPushButton* button_RoR;		//	RoR
	QPushButton* button_Or;			//	Or
	QPushButton* button_Xor;		//	Xor
	QPushButton* button_Not;		//	Not
	QPushButton* button_And;		//	And
	QPushButton* button_backspace;	//	<-
	QPushButton* button_factorial;	//	n!
	QPushButton* button_left;		//	(
	QPushButton* button_right;		//	)

	//输出文本框
	QLineEdit* lineEdit;

	//处理按钮点击信号的槽函数
	void button_0_clicked();
	void button_1_clicked();
	void button_2_clicked();
	void button_3_clicked();
	void button_4_clicked();
	void button_5_clicked();
	void button_6_clicked();
	void button_7_clicked();
	void button_8_clicked();
	void button_9_clicked();
	void button_plus_clicked();
	void button_minus_clicked();
	void button_multiply_clicked();
	void button_devide_clicked();
	void button_equal_clicked();
	void button_clear_clicked();
	void button_clearAll_clicked();
	void button_square_clicked();
	void button_cube_clicked();
	void button_sq_root_clicked();
	void button_reciprocal_clicked();
	void button_x_Y_clicked();
	void button_10_X_clicked();
	void button_Exp_clicked();
	void button_lg_clicked();
	void button_ln_clicked();
	void button_sin_clicked();
	void button_cos_clicked();
	void button_tan_clicked();
	void button_opp_clicked();
	void button_00_clicked();
	void button_decpoint_clicked();
	void button_Mod_clicked();
	void button_Lsh_clicked();
	void button_Rsh_clicked();
	void button_RoL_clicked();
	void button_RoR_clicked();
	void button_Or_clicked();
	void button_Xor_clicked();
	void button_Not_clicked();
	void button_And_clicked();
	void button_backspace_clicked();
	void button_factorial_clicked();
	void button_left_clicked();
	void button_right_clicked();
private:
	Ui::CalculatorClass ui;

	//数据成员
};
