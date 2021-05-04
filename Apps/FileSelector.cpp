#include "FileSelector.h"
#include "ui_FileSelector.h"

FileSelector::FileSelector() : App(WindowTitleBar::buttons::CLOSE_ONLY)
  , _ui(new Ui::FileSelector)
{
	_ui->setupUi(getContentPlaceholder());

//	model.setRootPath("");
//	model.setFilter(QDir::AllDirs);

//	_ui->treeView->setStyleSheet("");

//	_ui->treeView->setModel(&model);
//	_ui->treeView->setRootIndex(model.index(QDir::cleanPath("")));
//	_ui->treeView->show();
}

FileSelector::~FileSelector()
{
	delete _ui;
}
