#include "TreeComboBox.h"

#include <QDebug>

TreeComboBox::TreeComboBox(QWidget* parent) : QComboBox(parent)
{
	tw = new QTreeView(this);
	model = new QFileSystemModel();
	tw->setHeaderHidden(true);

	model->setRootPath("/");
	model->setFilter(QDir::AllDirs);

	setView(tw);
	setModel(model);


	for (int i = 1; i < 4; i++) tw->hideColumn(i);
	tw->setRootIsDecorated(false);
}

void TreeComboBox::showEvent(QShowEvent *e)
{
	QComboBox::showEvent(e);

	tw->expandAll();
}
