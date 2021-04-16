#pragma once

#include <QMetaEnum>

#include "SystemElements/SystemSubWindow.h"
#include "SystemElements/TaskbarElement.h"

class App : public SystemSubWindow
{
public:
	App(WindowTitleBar::buttons defaultButtonSet = WindowTitleBar::buttons::NORMAL);

	TaskbarElement* createTaskbarElement();

	void close();

protected:
	QString taskbarTitle;
	QPixmap* taskbarIcon = nullptr;
	bool taskbarAllowGrouping;

private:
	TaskbarElement* _taskbarElement;
};

