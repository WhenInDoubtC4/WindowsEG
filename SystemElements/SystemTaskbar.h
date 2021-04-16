#pragma once

#include <QWidget>
#include <QMenu>
#include <QTimer>
#include <QTime>

#include "SystemElements/StartMenu.h"
#include "SystemElements/TaskbarElement.h"

using namespace std::chrono_literals;

namespace Ui
{
	class SystemTaskbar;
}

class SystemTaskbar : public QWidget
{
	Q_OBJECT
public:
	explicit SystemTaskbar(QWidget* parent = nullptr);
	~SystemTaskbar();

	void addTaskbarElement(TaskbarElement* element);

private slots:
	void onStartButtonPressed();
	void updateClock();

private:
	Ui::SystemTaskbar* _ui = nullptr;
	QTimer* _clockTimer = nullptr;
};

