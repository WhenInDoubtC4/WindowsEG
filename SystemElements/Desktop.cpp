#include "Desktop.h"
#include <QDebug>

Desktop::Desktop(QWidget* parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setFocusPolicy(Qt::ClickFocus);
	setAcceptDrops(true);
}

void Desktop::addIcon(DesktopIcon* icon)
{
	if (!icon->parent()) icon->setParent(this);

	iconCell cell;
	cell.icon = icon;
	_icons << cell;
}

void Desktop::layOut()
{
	//Invalidate icon positions and grid
	for (iconCell& icon : _icons) icon.layoutPosition = QPoint(-1, -1);
	_grid.clear();

	QSize iconSize = DesktopIcon::staticMaxSize;
	QRect activeRect = QRect(_margins.left(), _margins.top(), size().width() - _margins.right(), size().height() - _margins.height());
	int gridCount = qFloor(activeRect.width() / (iconSize.width() + _hSpacing)) * qFloor(activeRect.height() / (iconSize.height() + _vSpacing));

	int dx = activeRect.x();
	int dy = activeRect.y();

	for (int i = 0; i < gridCount; i++)
	{
		int nextY = dy + iconSize.height() + _vSpacing;

		//Overflow
		if (nextY - _vSpacing > activeRect.height())
		{
			dx += iconSize.width() + _hSpacing;
			dy = activeRect.x();
			nextY = dy + iconSize.height() + _vSpacing;
		}

		_grid << QRect(dx, dy, iconSize.width(), iconSize.height());
		dy = nextY;
	}

	//Position icons
	for (iconCell& icon : _icons)
	{
		if (icon.layoutPosition != QPoint(-1, -1)) continue;

		//Find first free grid cell
		for (QRect gridCell : qAsConst(_grid))
		{
			//Check if position is free
			bool isTaken = false;
			for (iconCell& otherIcon : _icons)
			{
				if (otherIcon.layoutPosition == gridCell.topLeft())
				{
					isTaken = true;
					break;
				}
			}

			//If position is free, move icon and get out
			if (!isTaken)
			{
				int freeSpaceX = iconSize.width() - icon.icon->sizeHint().width();

				icon.layoutPosition = gridCell.topLeft();
				icon.icon->setGeometry(QRect(icon.layoutPosition + QPoint(qFloor(freeSpaceX / 2), 0), icon.icon->sizeHint()));
				break;
			}
		}
	}

	//No free position found, that's a problem
	//TODO: Maybe do something here?
}

QRect Desktop::findNearestGrid(const QPoint& position) const
{
	QRect nearestGrid = QRect(-1, -1, 0, 0);
	int minDistance = -1;
	for (QRect gridCell : _grid)
	{
		int distance = QPoint(position - gridCell.center()).manhattanLength();

		if (distance < minDistance || minDistance < 0)
		{
			minDistance = distance;
			nearestGrid = gridCell;
		}
	}

	return nearestGrid;
}

bool Desktop::isGridCellOccupied(const QRect& gridCell, DesktopIcon* icon) const
{
	for (iconCell cell : _icons)
	{
		if (gridCell.contains(cell.icon->geometry().center()) && cell.icon != icon) return true;
	}

	return false;
}

void Desktop::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	layOut();
}

void Desktop::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);

	auto painter = new QPainter(this);

	painter->fillRect(0, 0, width(), height(), QBrush(QColor(0, 128, 0)));

	delete painter;
}

void Desktop::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat(DesktopIcon::mimeType)) event->accept();
	else event->ignore();
}

void Desktop::dragMoveEvent(QDragMoveEvent* event)
{
	QWidget::dragMoveEvent(event);

	if (!event->mimeData()->hasFormat(DesktopIcon::mimeType))
	{
		event->ignore();
		return;
	}

	QByteArray iconData = event->mimeData()->data(DesktopIcon::mimeType);
	QDataStream iconDataStream(&iconData, QIODevice::ReadOnly);
	DesktopIcon* icon = nullptr;
	iconDataStream >> icon;

	if (!icon)
	{
		event->ignore();
		return;
	}

	event->accept();
	icon->move(event->pos() - QPoint(qFloor(icon->width() / 2), qFloor(icon->height() / 2)));
}

void Desktop::dropEvent(QDropEvent* event)
{
	if (!event->mimeData()->hasFormat(DesktopIcon::mimeType))
	{
		event->ignore();
		return;
	}

	QByteArray iconData = event->mimeData()->data(DesktopIcon::mimeType);
	QDataStream iconDataStream(&iconData, QIODevice::ReadOnly);
	DesktopIcon* icon = nullptr;
	QPoint originalPosition;
	iconDataStream >> icon >> originalPosition;

	if (!icon)
	{
		event->ignore();
		return;
	}

	event->accept();

	int freeSpace = DesktopIcon::staticMaxSize.width() - icon->size().width();
	QRect nearestRect = findNearestGrid(event->pos());
	if (isGridCellOccupied(nearestRect, icon))
	{
		//Move back to original position
		icon->setGeometry(QRect(originalPosition, icon->sizeHint()));
		icon->drop();
		return;
	}

	icon->setGeometry(QRect(nearestRect.topLeft() + QPoint(qFloor(freeSpace / 2), 0), icon->sizeHint()));
	icon->drop();
}
