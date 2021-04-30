#pragma once

#include <QObject>
#include <QLineEdit>

#include "AppControl.h"

class InternetExplorerControl : public AppControl
{
	Q_OBJECT
private:
	APP_CONTROL
	InternetExplorerControl();

	QLineEdit* _a = nullptr;
	QLineEdit* _b = nullptr;
};

