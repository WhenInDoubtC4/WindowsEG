#include "ControlWindow.h"
#include "ui_ControlWindow.h"

ControlWindow::ControlWindow(QWidget* parent): QMainWindow(parent)
  , _ui(new Ui::ControlWindow)
  , _systemWindow(new SystemWindow())
{
	_ui->setupUi(this);

	//Create system window
	_systemWindow->show();
#if defined(_WIN32)
	_systemWindow->activateWindow();
#elif defined(__APPLE__)
	_systemWindow->raise();
#endif
}

ControlWindow::~ControlWindow()
{
	delete _ui;
	delete _systemWindow;
}

