#pragma once

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QDir>
#include <QtMath>

#include "SystemElements/ListIcon.h"

class FileExplorerTable : public QTableWidget
{
	Q_OBJECT
public:
	FileExplorerTable(QWidget* parent = nullptr);
	~FileExplorerTable();

	void setRoot(const QString& path, QDir::Filter filter = QDir::Filter());

	void cdUp();

protected:
	virtual void resizeEvent(QResizeEvent* event) override;

private:
	QDir* _fileSystem = nullptr;
	QString _path;
	QDir::Filter _filter;
	QList<ListIcon*> _icons;

	const int cellHeight = 20;

	void layout();
};

