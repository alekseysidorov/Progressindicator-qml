#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "progressindicator.h"

#include <QDebug>

#include <QtDeclarative>
#include <QDebug>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	app.setApplicationName("Bundle generator demo");
	app.setApplicationVersion("1");
	app.setOrganizationName("sauron");
	app.setOrganizationDomain("http://co-de.org");
	qmlRegisterType<ProgressIndicatorBase>("demo.org", 1, 0, "ProgressIndicatorBase");

	QmlApplicationViewer viewer;
	if (QIcon::themeName().isEmpty())
		QIcon::setThemeName("oxygen");

	viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
	viewer.setMainQmlFile(QLatin1String("qml/indicator/main.qml"));
	//viewer.setMinimumSize(300, 400);
	viewer.showExpanded();
	return app.exec();
}
