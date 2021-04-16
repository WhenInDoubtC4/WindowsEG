#pragma once

#include <QMainWindow>

#include "SystemWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class ControlWindow;
}
QT_END_NAMESPACE

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
