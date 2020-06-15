#include "exdeath.hh"

#include <QApplication>

int main(int argc, char **argv) {
	QApplication *app = new QApplication(argc, argv);
	Exdeath *win = new Exdeath();

	win->show();

	return app->exec();
}