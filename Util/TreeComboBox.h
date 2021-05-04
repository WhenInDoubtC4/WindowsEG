#pragma once

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QTreeView>
#include <QFileSystemModel>

class TreeComboBox : public QComboBox
{
	Q_OBJECT
public:
	TreeComboBox(QWidget* parent = nullptr);

protected:
	virtual void showEvent(QShowEvent *e) override;

private:
	QFileSystemModel* model = nullptr;
	QTreeView* tw = nullptr;
};
