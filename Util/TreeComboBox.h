#pragma once

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QTreeWidget>

#include "SystemElements/ListIcon.h"

class TreeComboBox : public QComboBox
{
	Q_OBJECT
public:
	TreeComboBox(QWidget* parent = nullptr);
	~TreeComboBox();

private:
	QTreeWidget* _treeWidget = nullptr;
};
