#include "SQLiteViewer.h"
#include <QtWidgets\QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SQLiteViewer w;
	w.show();
	return a.exec();
}
