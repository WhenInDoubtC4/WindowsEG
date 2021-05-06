#include "SystemWindow.h"
#include "ui_SystemWindow.h"

#include "Apps/MessageBox.h"
#include "SystemElements/DesktopIcon.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "FileSystem/FakeFileSystem.h"

#include "Apps/Run.h"
#include "Apps/Notepad.h"
#include "Apps/FileSelector.h"

SystemWindow::SystemWindow(QWidget* parent) :QMainWindow(parent)
  , _ui(new Ui::SystemWindow)
  , _mdiArea(new SystemMdiArea())
  , _taskbar(new SystemTaskbar(this))
{
	_ui->setupUi(this);

	QFile stylesheetFile(":/Resources/Style/Main.css");
	stylesheetFile.open(QFile::ReadOnly);
	QString stylesheet = QLatin1String(stylesheetFile.readAll());
	setStyleSheet(stylesheet);

	_ui->MDIAreaPlaceholder->addWidget(_mdiArea);

	_ui->taskbarPlaceholder->addWidget(_taskbar);

	System::init(_mdiArea, _taskbar);

	auto icon = new DesktopIcon(nullptr, "Something");
	auto icon2 = new DesktopIcon(nullptr, "Longer title");
	auto icon3 = new DesktopIcon(nullptr, "Really long title");
	auto icon4 = new DesktopIcon(nullptr, "Title");
	auto icon5 = new DesktopIcon(nullptr, "Untitled");
	System::addIconToDesktop(icon);
	System::addIconToDesktop(icon2);
	System::addIconToDesktop(icon3);
	System::addIconToDesktop(icon4);
	System::addIconToDesktop(icon5);

	auto r = new Run();
	System::runApp(r);

	auto runapp = new Notepad();
	System::runApp(runapp);

//	auto filedialog = new FileSelector();
//	System::runApp(filedialog);
}

SystemWindow::~SystemWindow()
{
	delete _ui;
}
