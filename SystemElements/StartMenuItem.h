#pragma once

#include <QObject>
#include <QWidget>
#include <QPainter>

class StartMenuItem : public QWidget
{
	Q_OBJECT
public:
	explicit StartMenuItem(QWidget* parent = nullptr);

	void setHovered(const bool hovered);

protected:
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;

private:
	bool _hovered = false;

signals:
	void leave();
};

