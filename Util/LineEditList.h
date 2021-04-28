#pragma once

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>

class LineEditList : public QWidget
{
	Q_OBJECT
public:
	LineEditList(QList<QString> items = {}, QWidget* parent = nullptr);

	void clear();

	void addItem(const QString& text);
	void addFromStringList(const QList<QString> stringList);

	QList<QString> getTextInAllFields() const;

private:
	QVBoxLayout* _layout = nullptr;
	QListWidget* _listWidget = nullptr;
	QFrame* _addItemFrame = nullptr;
	QHBoxLayout* _addItemLayout = nullptr;
	QLineEdit* _addItemLineEdit = nullptr;
	QPushButton* _addItemButton = nullptr;

	QList<QLineEdit*> _fields;
};
