#include "old_Calculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	old_Calculator w;
	w.show();
	return a.exec();
}
