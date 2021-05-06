#include "WindowTitleBar.h"
#include "ui_WindowTitleBar.h"

WindowTitleBar::WindowTitleBar(QWidget* parent, QMdiSubWindow* parentWindow, buttons buttonSet) : QWidget(parent)
  , _ui(new Ui::WindowTitleBar)
  , _window(parentWindow)
{	
	_ui->setupUi(this);
	setStyleSheet("background: transparent");

	QObject::connect(_ui->closeButton, &QPushButton::released, this, &WindowTitleBar::onCloseButtonPressed);

	switch (buttonSet)
	{
		case WindowTitleBar::buttons::CLOSE_ONLY:
			//Do nothing - close button set by deafault
			break;
		case WindowTitleBar::buttons::NORMAL:
		{
			_minMaxButton = new QPushButton();
			_minMaxButton->setMaximumSize(SYSTEM_BUTTON_SIZE, SYSTEM_BUTTON_SIZE);
			_minMaxButton->setIcon(QIcon(":/Resources/Style/Assets/Icon-Max.png"));
			_ui->horizontalLayout->insertWidget(2, _minMaxButton, 0, Qt::AlignRight);

			auto spacer = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Maximum);
			_ui->horizontalLayout->insertItem(3, spacer);

			_hideButton = new QPushButton();
			_hideButton->setMaximumSize(SYSTEM_BUTTON_SIZE, SYSTEM_BUTTON_SIZE);
			_hideButton->setIcon(QIcon(":/Resources/Style/Assets/Icon-Hide.png"));
			_ui->horizontalLayout->insertWidget(2, _hideButton);

			QObject::connect(_minMaxButton, &QPushButton::released, this, &WindowTitleBar::onMinMaxButtonPressed);
			QObject::connect(_hideButton, &QPushButton::released, this, &WindowTitleBar::onHideButtonPressed);

			break;
		}
	}
}

WindowTitleBar::~WindowTitleBar()
{
	delete _minMaxButton;
	delete _hideButton;
	delete _ui;
}

void WindowTitleBar::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);

	QColor backgroundColor = QColor(128, 128, 128);
	if (_isFocused) backgroundColor = QColor(0, 0, 128);

	painter.setPen(Qt::blue);
	painter.fillRect(0, 0, width(), height(), QBrush(backgroundColor));
}

void WindowTitleBar::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);

	if (event->button() == Qt::LeftButton)
	{
		_mouseButtonDown = true;
		_capturedMouseGlobalPosition = event->globalPos();
		_capturedWindowGlobalPosition = _window->pos();
	}
}

void WindowTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);

	if (event->button() == Qt::LeftButton) _mouseButtonDown = false;
}

void WindowTitleBar::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);

	if (!_mouseButtonDown) return;

	_window->move(event->globalPos() - _capturedMouseGlobalPosition + _capturedWindowGlobalPosition);
}

void WindowTitleBar::onCloseButtonPressed()
{
	emit requestClose();
}

void WindowTitleBar::onMinMaxButtonPressed()
{
	if (!_window->isMaximized())
	{
		_normalWindowMinimumSize = _window->minimumSizeHint();
		_window->showMaximized();
		_minMaxButton->setIcon(QIcon(":/Resources/Style/Assets/Icon-Restore.png"));
	}
	else
	{
		_window->adjustSize();
		_window->setMinimumSize(_normalWindowMinimumSize);
		_window->showNormal();
		_minMaxButton->setIcon(QIcon(":/Resources/Style/Assets/Icon-Max.png"));
	}
}

void WindowTitleBar::onHideButtonPressed()
{
	_window->showMinimized();
}

void WindowTitleBar::setTitle(const QString& title)
{
	_ui->titleLabel->setText(title);
}

void WindowTitleBar::setFocused(const bool focused)
{
	_isFocused = focused;
	update();
}
