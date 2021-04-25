#pragma once

#include <QMainWindow>

#include "SystemWindow.h"

namespace Ui
{
	class ControlWindow;
}

class ControlWindow : public QMainWindow
{
	Q_OBJECT

public:
	ControlWindow(QWidget* parent = nullptr);
	~ControlWindow();

private:
	Ui::ControlWindow* _ui = nullptr;

	SystemWindow* _systemWindow = nullptr;
};
