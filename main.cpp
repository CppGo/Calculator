#include "Cal01.h"
#include "Calculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//Cal01 w;
	//w.show();
	Calculator c;
	c.show();
	return a.exec();
}
