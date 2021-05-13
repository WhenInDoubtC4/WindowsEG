#include "ControlWindow.h"
#include "ui_ControlWindow.h"

ControlWindow::ControlWindow(QWidget* parent): QMainWindow(parent)
  , _ui(new Ui::ControlWindow)
{
	//Make sure controls are registered before anything else is created
	_globalControl = AppControl::registerControlClass<GlobalControl>();
	AppControl::registerControlClass<NotepadControl>();
	AppControl::registerControlClass<InternetExplorerControl>();

	_ui->setupUi(this);
	_globalControl->setTextAACheckBox(_ui->textAACheckBox);

	AppControl::getInstance<NotepadControl>()->setupControlWidgets(_ui->treeWidget, "Notepad");
	AppControl::getInstance<InternetExplorerControl>()->setupControlWidgets(_ui->treeWidget, "Internet Explorer");

	//Create system window
	_systemWindow = new SystemWindow(this);
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

	QObject::connect(_ui->textAACheckBox, &QCheckBox::clicked, _systemWindow, static_cast<void(SystemWindow::*)()>(&SystemWindow::update));
}

ControlWindow::~ControlWindow()
{
	delete _systemWindow;
	delete _ui;
}
