#include "ListIcon.h"
#include "ui_ListIcon.h"

ListIcon::ListIcon(const QPixmap& icon, const QString& title, QWidget* parent) : QWidget(parent)
  , _ui(new Ui::ListIcon)
{
	_ui->setupUi(this);

	_ui->iconLabel->setPixmap(icon);
	_ui->titleLabel->setText(title);
}

ListIcon::~ListIcon()
{
	delete _ui;
}

void ListIcon::setAsComboBoxElement()
{
	_comboBoxElement = true;

	setAttribute(Qt::WA_TransparentForMouseEvents);
}

void ListIcon::mouseDoubleClickEvent(QMouseEvent* event)
{
	QWidget::mouseDoubleClickEvent(event);

	emit opened();
}

void ListIcon::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);

	if (_comboBoxElement) return;

	setFocus();
	setSelected(true);

	emit selected();
}

void ListIcon::focusOutEvent(QFocusEvent* event)
{
	QWidget::focusOutEvent(event);

	if (_comboBoxElement) return;
	setSelected(false);
}

void ListIcon::setSelected(bool selected)
{
	if (selected)
	{
		_ui->titleLabel->setStyleSheet("background: rgb(0, 0, 128); color: #ffffff;");
	}
	else
	{
		_ui->titleLabel->setStyleSheet("background: transparent; color: #000000;");
	}
}

QPixmap ListIcon::getIcon() const
{
	return _ui->iconLabel->pixmap(Qt::ReturnByValueConstant::ReturnByValue);
}
