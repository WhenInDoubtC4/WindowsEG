#include "App.h"

App::App(WindowTitleBar::buttons defaultButtonSet) : SystemSubWindow(defaultButtonSet)
{
	QObject::connect(this, &App::focusChanged, [=](bool isFocused)
	{
		_taskbarElement->setChecked(isFocused);
	});

	QObject::connect(getTitleBar(), &WindowTitleBar::requestClose, this, &App::close);
}

TaskbarElement* App::createTaskbarElement()
{
	_taskbarElement = new TaskbarElement(taskbarTitle, taskbarIcon);

	return _taskbarElement;
}

void App::close()
{
	_taskbarElement->deleteLater();
	deleteLater();
}
