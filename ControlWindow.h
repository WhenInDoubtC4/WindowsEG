#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

#include "SystemWindow.h"
#include "Control/GlobalControl.h"
#include "Control/NotepadControl.h"
#include "Control/InternetExplorerControl.h"

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

	GlobalControl* _globalControl = nullptr;
};
