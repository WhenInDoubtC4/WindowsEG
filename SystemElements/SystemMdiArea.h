#pragma once

#include <QMdiArea>
#include <QObject>
#include <QWidget>
#include <QPainter>

#include "Desktop.h"

namespace Ui
{
	class SystemMdiArea;
}

class SystemMdiArea : public QMdiArea
{
	Q_OBJECT
public:
	SystemMdiArea();
	~SystemMdiArea();

	Desktop* getDesktop() const;

private:
	Ui::SystemMdiArea* _ui = nullptr;
};

