#include <QCoreApplication>
#include "setsumei.hpp"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	SelfBot b; //SelfBot's constructor will take over from here.
	Q_UNUSED(b); //Suppress the warning about b being unused.
	return a.exec();
}
