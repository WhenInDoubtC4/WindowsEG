#include "FileSelector.h"
#include "ui_FileSelector.h"

FileSelector::FileSelector() : App(WindowTitleBar::buttons::CLOSE_ONLY)
  , _ui(new Ui::FileSelector)
{
	_ui->setupUi(getContentPlaceholder());

	_ui->tableWidget->setRoot("/Users/adam/Desktop/Dev/qt_windowsExtremelyGoodEdition/FakeFileSystemRoot/_rootDrive", QDir::AllEntries);

	QObject::connect(_ui->tableWidget, &FileExplorerTable::dirChanged, this, &App::setupFocusHandling);
	QObject::connect(_ui->cdUpButton, &QPushButton::pressed, _ui->tableWidget, &FileExplorerTable::cdUp);

	QObject::connect(_ui->pathComboBox, &TreeComboBox::openPath, _ui->tableWidget, &FileExplorerTable::cd);
}

FileSelector::~FileSelector()
{
	delete _ui;
}
