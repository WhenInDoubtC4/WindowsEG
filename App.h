#pragma once

#include <QMetaEnum>

#include "SystemElements/SystemSubWindow.h"
#include "SystemElements/TaskbarElement.h"

class App : public SystemSubWindow
{
public:
	App(WindowTitleBar::buttons defaultButtonSet = WindowTitleBar::buttons::NORMAL);
	~App();

	TaskbarElement* createTaskbarElement();

public slots:
	void closeApp();

protected:
	QString taskbarTitle;
	QPixmap* taskbarIcon = nullptr;
	bool taskbarAllowGrouping;

private:
	TaskbarElement* _taskbarElement;

private slots:
	void onTaskbarElementPressed();
};

