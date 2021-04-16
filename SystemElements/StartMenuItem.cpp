#include "StartMenuItem.h"

StartMenuItem::StartMenuItem(QWidget* parent) : QWidget(parent)
{
	setMouseTracking(true);
}

void StartMenuItem::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);

	auto painter = new QPainter(this);

	if (_hovered) painter->fillRect(0, 0, width(), height(), QBrush(QColor(0, 0, 128)));

	delete  painter;
}

void StartMenuItem::setHovered(const bool hovered)
{
	_hovered = hovered;

	repaint();
}

void StartMenuItem::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);

	emit leave();
}
