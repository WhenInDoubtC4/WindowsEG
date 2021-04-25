#include "App.h"

#include <QDebug>

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

	QObject::connect(_taskbarElement, &TaskbarElement::clicked, this, &App::onTaskbarElementPressed);

	return _taskbarElement;
}

void App::close()
{
	_taskbarElement->deleteLater();
	deleteLater();
}

void App::onTaskbarElementPressed()
{
	if (isMinimized())
	{
		showNormal();
	}

	//Make sure it stays checked
	_taskbarElement->setChecked(true);
}
