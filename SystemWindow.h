#pragma once

#include <QMainWindow>

#include "Control/GlobalControl.h"
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

protected:
	virtual void paintEvent(QPaintEvent* event) override;

private:
	Ui::SystemWindow* _ui;

	GlobalControl* _globalControl = nullptr;

	SystemMdiArea* _mdiArea = nullptr;
	SystemTaskbar* _taskbar = nullptr;
};

