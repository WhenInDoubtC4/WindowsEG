#include "InternetExplorerControl.h"

#include <QDebug>

InternetExplorerControl::InternetExplorerControl()
{
	CONSTRUCT_ONCE

	_a = new QLineEdit("Something");
	_b = new QLineEdit("Something");

	auto row1 = QList<QWidget*>{}
			<< new QLabel("REEEEEEEE")
			<< _a;

	auto row2 = QList<QWidget*>{}
			<< new QLabel("1BBBBBBBBBB")
			<< _b;

	getControlItemsList() << row1 << row2;
}

void InternetExplorerControl::updateConfigData(QByteArray& data)
{
	QDataStream stream(&data, QIODevice::WriteOnly);
	stream << _a->text() << _b->text();
}
