#include "InternetExplorerControl.h"

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
