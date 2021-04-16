#pragma once

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QtMath>

#include "DesktopIcon.h"

class Desktop : public QWidget
{
	Q_OBJECT
public:
	explicit Desktop(QWidget *parent = nullptr);

	void addIcon(DesktopIcon* icon);

protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dragMoveEvent(QDragMoveEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;

private:
	struct iconCell
	{
		//Layout position may not be actual position!!
		QPoint layoutPosition = QPoint(-1, -1);
		DesktopIcon* icon;
	};

	void layOut();
	QRect findNearestGrid(const QPoint& position) const;
	bool isGridCellOccupied(const QRect& gridCell, DesktopIcon* icon) const;

	QRect _margins = QRect(8, 8, 8, 8);
	QList<QRect> _grid;
	int _hSpacing = 0;
	int _vSpacing = 0;
	QList<iconCell> _icons;
};

