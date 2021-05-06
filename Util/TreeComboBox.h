#pragma once

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QTreeWidget>
#include <QDir>
#include <QPainter>

#include "SystemElements/ListIcon.h"

class TreeComboBox : public QComboBox
{
	Q_OBJECT
public:
	TreeComboBox(QWidget* parent = nullptr);
	~TreeComboBox();

protected:
	virtual void paintEvent(QPaintEvent* e) override;

private:
	QTreeWidget* _treeWidget = nullptr;
	QDir* _fileSystem = nullptr;

	void addChildren(QTreeWidgetItem* topLevelItem);

signals:
	void openPath(const QString& path);
};
