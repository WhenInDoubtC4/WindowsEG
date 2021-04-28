#include "ControlWindow.h"
#include "ui_ControlWindow.h"

ControlWindow::ControlWindow(QWidget* parent): QMainWindow(parent)
{
	//Make sure controls are registered befor anything else is created
	AppControl::registerControlClass<NotepadControl>();
	AppControl::registerControlClass<InternetExplorerControl>();

	_ui = new Ui::ControlWindow;
	_systemWindow = new SystemWindow();
	_ui->setupUi(this);

	AppControl::getInstance<NotepadControl>()->setupControlWidgets(_ui->treeWidget, "Notepad");
	AppControl::getInstance<InternetExplorerControl>()->setupControlWidgets(_ui->treeWidget, "Internet Explorer");

	//Create system window
	_systemWindow->show();
#if defined(_WIN32)
	_systemWindow->activateWindow();
#elif defined(__APPLE__)
	_systemWindow->raise();
#endif

	QObject::connect(_ui->action_file_saveConfig, &QAction::triggered, [=]()
	{
		QString fileName = QFileDialog::getSaveFileName(this, "Save config", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/config", "JSON (*.json);;All files (*)");
		QFile file(fileName);
		file.open(QIODevice::WriteOnly);
		QJsonDocument json = AppControl::saveAll();
		file.write(json.toJson());
		file.close();
	});

	QObject::connect(_ui->action_file_loadConfig, &QAction::triggered, [=]()
	{
		QString fileName = QFileDialog::getOpenFileName(this, "Load config", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), "JSON (*.json);;All files (*)");
		QFile file(fileName);
		file.open(QIODevice::ReadOnly);
		QJsonParseError parseError;
		QJsonDocument json = QJsonDocument::fromJson(file.readAll(), &parseError);
		file.close();

		if (json.isNull())
		{
			QMessageBox::critical(this, "Failed to open file", "JSON parse error: " + parseError.errorString(), QMessageBox::Ok, QMessageBox::Ok);
			return;
		}

		AppControl::loadAll(json);
	});
}

ControlWindow::~ControlWindow()
{
	delete _ui;
	delete _systemWindow;
}
