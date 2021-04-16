#include "SystemSubWindow.h"
#include "ui_SystemSubWindow.h"

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

	_titleBar->setFocused(true);
	emit focusChanged(true);
}

void SystemSubWindow::focusOutEvent(QFocusEvent* focusOutEvent)
{
	QMdiSubWindow::focusOutEvent(focusOutEvent);

	_titleBar->setFocused(false);
	emit focusChanged(false);
}
