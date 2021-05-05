#include "ListIcon.h"
#include "ui_ListIcon.h"

#include <QDebug>

ListIcon::ListIcon(const QPixmap& icon, const QString& title, QWidget* parent) : QWidget(parent)
  , _ui(new Ui::ListIcon)
{
	_ui->setupUi(this);

	_ui->iconLabel->setPixmap(icon);
	_ui->titleLabel->setText(title);

	setFocusPolicy(Qt::ClickFocus);
}

ListIcon::~ListIcon()
{
	delete _ui;
}

void ListIcon::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);

	qDebug() << _correspondingPath << "SHOW";
}

void ListIcon::mouseDoubleClickEvent(QMouseEvent* event)
{
	QWidget::mouseDoubleClickEvent(event);

	emit opened();
}
void ListIcon::focusOutEvent(QFocusEvent* event)
{
	QWidget::focusOutEvent(event);

	setSelected(false);

	qDebug() << _correspondingPath << "Focus out" << event->reason();
}

void ListIcon::focusInEvent(QFocusEvent* event)
{
	if (event->reason() != Qt::MouseFocusReason)
	{
		qDebug() << "Ignore this";
		event->ignore();
		return;
	}

	setSelected(true);

	//QWidget::focusInEvent(event);
	qDebug() << _correspondingPath << "Focus in" << event->reason();
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
