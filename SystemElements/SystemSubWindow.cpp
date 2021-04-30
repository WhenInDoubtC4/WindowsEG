#include "SystemSubWindow.h"
#include "ui_SystemSubWindow.h"

SystemSubWindow::SystemSubWindow(WindowTitleBar::buttons buttonSet) : QMdiSubWindow(nullptr, Qt::FramelessWindowHint)
	, _ui(new Ui::SystemSubWindow)
	, _uiContainer(new QWidget(this))
	, _titleBar(new WindowTitleBar(this, this, buttonSet))
{
	setAttribute(Qt::WA_DeleteOnClose);
	layout()->addWidget(_uiContainer);

	_ui->setupUi(_uiContainer);
	_ui->windowFrame->setProperty("outset", true);
	_ui->titlebarPlaceholder->addWidget(_titleBar);

	QObject::connect(_titleBar, &WindowTitleBar::requestClose, this, &SystemSubWindow::onCloseRequested);
}

SystemSubWindow::~SystemSubWindow()
{
	while(!_resizeGrips.isEmpty()) delete _resizeGrips.takeLast();
	delete _titleBar;
	delete _uiContainer;
	delete _ui;
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

void SystemSubWindow::enableFrameResize()
{
	_resizeGripLayout = new QGridLayout();

	for(int i = 0; i < 4; i++)
	{
		auto grip = new QSizeGrip(this);
		grip->setFixedSize(10, 10);
		_resizeGrips << grip;
	}
	_resizeGripLayout->addWidget(_resizeGrips[0], 0, 0, Qt::AlignTop | Qt::AlignLeft);
	_resizeGripLayout->addWidget(_resizeGrips[1], 0, 2, Qt::AlignTop | Qt::AlignRight);
	_resizeGripLayout->addWidget(_resizeGrips[2], 2, 0, Qt::AlignBottom | Qt::AlignLeft);
	_resizeGripLayout->addWidget(_resizeGrips[3], 2, 2, Qt::AlignBottom | Qt::AlignRight);
}

void SystemSubWindow::resizeEvent(QResizeEvent* event)
{
	QMdiSubWindow::resizeEvent(event);

	//Unorthodox solution
	if (!_resizeGripLayout) return;
	_resizeGripLayout->setGeometry(QRect(QPoint(0, 0), size()));
}

void SystemSubWindow::attachTo(SystemSubWindow* window)
{
	if (_attachedWindow) throw std::runtime_error("Already attached to a different window");

	QObject::connect(this, &QMdiSubWindow::destroyed, [=]()
	{
		_attachedWindow = nullptr;
		window->setDisabled(false);
		window->setFocus();
	});

	_attachedWindow = window;
	window->setDisabled(true);
}

void SystemSubWindow::showEvent(QShowEvent* showEvent)
{
	if (_attachedWindow) move(_attachedWindow->geometry().center() - QRect(QPoint(0, 0), size()).center());

	QMdiSubWindow::showEvent(showEvent);
}
