#include "SystemSubWindow.h"
#include "ui_SystemSubWindow.h"

#include <QDebug>

SystemSubWindow::SystemSubWindow(WindowTitleBar::buttons buttonSet)
	: _ui(new Ui::SystemSubWindow)
	, _uiContainer(new QWidget(this))
	, _titleBar(new WindowTitleBar(this, this, buttonSet))
{

	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_DeleteOnClose);
	layout()->addWidget(_uiContainer);

	_ui->setupUi(_uiContainer);
	_ui->windowFrame->setProperty("outset", true);
	_ui->titlebarPlaceholder->addWidget(_titleBar);

	QObject::connect(_titleBar, &WindowTitleBar::requestClose, this, &SystemSubWindow::onCloseRequested);
}

SystemSubWindow::~SystemSubWindow()
{
	delete _ui;
	delete _uiContainer;
}

void SystemSubWindow::onCloseRequested()
{
	deleteLater();
}

QWidget* SystemSubWindow::getContentPlaceholder() const
{
	return _ui->content;
}

WindowTitleBar* SystemSubWindow::getTitleBar() const
{
	return _titleBar;
}

void SystemSubWindow::focusInEvent(QFocusEvent* focusInEvent)
{
	QMdiSubWindow::focusInEvent(focusInEvent);

	if (!_isFocusSetUp)
	{
		_isFocusSetUp = true;
		for (auto childWidget : findChildren<QWidget*>()) childWidget->installEventFilter(this);

		//Menus
		for (auto childMenu : findChildren<QMenu*>())
		{
			QObject::connect(childMenu, &QMenu::aboutToShow, [=]()
			{
				_ignoreUnfocusOnce = true;
			});
		}
	}

	_titleBar->setFocused(true);
	emit focusChanged(true);
}

void SystemSubWindow::focusOutEvent(QFocusEvent* focusOutEvent)
{
	QMdiSubWindow::focusOutEvent(focusOutEvent);

	if (_ignoreUnfocusOnce)
	{
		_ignoreUnfocusOnce = false;
		return;
	}

	_titleBar->setFocused(false);
	emit focusChanged(false);
}

bool SystemSubWindow::eventFilter([[maybe_unused]] QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::FocusIn)
	{	
		_titleBar->setFocused(true);
		emit focusChanged(true);
	}

	if (event->type() == QEvent::FocusOut)
	{
		if (_ignoreUnfocusOnce)
		{
			_ignoreUnfocusOnce = false;
			return false;
		}

		_titleBar->setFocused(false);
		emit focusChanged(false);
	}

	return false;
}
