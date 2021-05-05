#include "FileSelector.h"
#include "ui_FileSelector.h"

FileSelector::FileSelector() : App(WindowTitleBar::buttons::CLOSE_ONLY)
  , _ui(new Ui::FileSelector)
{
	_ui->setupUi(getContentPlaceholder());

	_ui->tableWidget->setRoot("/Users/adam/Desktop/Dev/qt_windowsExtremelyGoodEdition/FakeFileSystemRoot/_rootDrive", QDir::AllEntries);
}

FileSelector::~FileSelector()
{
	delete _ui;
}
