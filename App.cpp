#include "App.h"

App::App(WindowTitleBar::buttons defaultButtonSet) : SystemSubWindow(defaultButtonSet)
{
	QObject::connect(this, &App::focusChanged, [=](bool isFocused)
	{
		_taskbarElement->setChecked(isFocused);
	});

	QObject::connect(getTitleBar(), &WindowTitleBar::requestClose, this, &App::closeApp);
}

App::~App()
{
}

TaskbarElement* App::createTaskbarElement()
{
	_taskbarElement = new TaskbarElement(taskbarTitle, taskbarIcon);

	QObject::connect(_taskbarElement, &TaskbarElement::clicked, this, &App::onTaskbarElementPressed);

	return _taskbarElement;
}

void App::closeApp()
{
	delete this;
}

void App::onTaskbarElementPressed()
{
	if (!isEnabled())
	{
		_taskbarElement->setChecked(false);
		return;
	}

	if (isMinimized()) showNormal();

	//Make sure it stays checked
	_taskbarElement->setChecked(true);
}
