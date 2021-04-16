#pragma once

#include <QMainWindow>

#include "System.h"
#include "SystemElements/SystemMdiArea.h"
#include "SystemElements/SystemTaskbar.h"

namespace Ui
{
	class SystemWindow;
}

class SystemWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SystemWindow(QWidget* parent = nullptr);
	~SystemWindow();

private:
	Ui::SystemWindow* _ui;

	SystemMdiArea* _mdiArea = nullptr;
	SystemTaskbar* _taskbar = nullptr;
};

