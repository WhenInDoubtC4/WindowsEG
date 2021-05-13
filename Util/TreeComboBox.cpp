#include "TreeComboBox.h"

#include <QDebug>

TreeComboBox::TreeComboBox(QWidget* parent) : QComboBox(parent)
  , _treeWidget(new QTreeWidget())
  , _fileSystem(new QDir())
{
	setView(_treeWidget);
	setModel(_treeWidget->model());
	_treeWidget->setHeaderHidden(true);

	_fileSystem->setPath("/Users/adam/Desktop/Dev/qt_windowsExtremelyGoodEdition/FakeFileSystemRoot/_rootDrive");

	//Add top level items
	QList<QFileInfo> topLevelEntries = _fileSystem->entryInfoList();
	for (QFileInfo entry : qAsConst(topLevelEntries))
	{
		if (!entry.isDir() || entry.baseName() == QString()) continue;

		auto icon = new ListIcon(QPixmap(":/Resources/Style/Assets/Icons/Warning.ico"), entry.baseName(), this);
		icon->setCorrespondingPath(_fileSystem->path() + "/" + entry.baseName());
		icon->setAsComboBoxElement();
		auto item = new QTreeWidgetItem();
		_treeWidget->addTopLevelItem(item);
		_treeWidget->setItemWidget(item, 0, icon);
		item->setExpanded(true);

		addChildren(item);
	}

	QObject::connect(_treeWidget, &QTreeWidget::itemPressed, [=](QTreeWidgetItem* item, int col)
	{
		auto pressedIcon = dynamic_cast<ListIcon*>(_treeWidget->itemWidget(item, col));
		if (!pressedIcon) return;
		emit openPath(pressedIcon->getCorrespondingPath());
	});
}

TreeComboBox::~TreeComboBox()
{
	delete _fileSystem;
	delete _treeWidget;
}

void TreeComboBox::paintEvent(QPaintEvent* e)
{
	QComboBox::paintEvent(e);

	QPainter painter(this);
}

void TreeComboBox::addChildren(QTreeWidgetItem* topLevelItem)
{
	ListIcon* rootIcon = dynamic_cast<ListIcon*>(_treeWidget->itemWidget(topLevelItem, 0));
	QDir root(rootIcon->getCorrespondingPath());

	for (QFileInfo& entry : root.entryInfoList(QDir::Dirs))
	{
		if (entry.baseName() == QString()) continue;

		auto icon = new ListIcon(QPixmap(":/Resources/Style/Assets/Icons/Warning.ico"), entry.baseName(), this);
		icon->setCorrespondingPath(root.path() + "/" + entry.baseName());
		icon->setAsComboBoxElement();
		auto item = new QTreeWidgetItem(topLevelItem);
		_treeWidget->setItemWidget(item, 0, icon);
		item->setExpanded(true);

		//Check if it has any subdirs
		QDir subDir(root.path() + "/" + entry.baseName());
		if (subDir.entryList(QDir::Dirs).size() > 0) addChildren(item);
	}
}
