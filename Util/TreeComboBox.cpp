#include "TreeComboBox.h"

#include <QDebug>

TreeComboBox::TreeComboBox(QWidget* parent) : QComboBox(parent)
  , _treeWidget(new QTreeWidget())
{
	setView(_treeWidget);
	setModel(_treeWidget->model());
	_treeWidget->setHeaderHidden(true);

	auto i1 = new QTreeWidgetItem();
	auto iw = new ListIcon(QPixmap(":/Resources/Style/Assets/Icons/Warning.ico"), "AAAA");


	_treeWidget->addTopLevelItem(i1);
	_treeWidget->setItemWidget(i1, 0, iw);
}

TreeComboBox::~TreeComboBox()
{
	delete _treeWidget;
}
