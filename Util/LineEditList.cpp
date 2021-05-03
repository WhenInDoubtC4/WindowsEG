#include "LineEditList.h"

#include <QDebug>

LineEditList::LineEditList(QList<QString> items, QWidget* parent) : QWidget(parent)
  , _layout(new QVBoxLayout(this))
  , _listWidget(new QListWidget())
  , _addItemFrame(new QFrame())
  , _addItemLayout(new QHBoxLayout(_addItemFrame))
  , _addItemLineEdit(new QLineEdit("New item"))
  , _addItemButton(new QPushButton("Add"))
{
	_layout->setMargin(0);
	_layout->setSpacing(0);
	_layout->addWidget(_listWidget);
	_layout->addWidget(_addItemFrame);
	_addItemLayout->setMargin(0);
	_addItemLayout->addWidget(_addItemLineEdit);
	_addItemLayout->addWidget(_addItemButton);

	addFromStringList(items);

	QObject::connect(_addItemButton, &QPushButton::pressed, [=]()
	{
		addItem(_addItemLineEdit->text());
	});
}

void LineEditList::clear()
{
	for (int i = _listWidget->count() - 1; i >= 0; i--)
	{
		delete _listWidget->takeItem(i);
	}
	_fields.clear();
}

void LineEditList::addItem(const QString& text)
{
	auto frame = new QFrame();
	auto layout = new QHBoxLayout(frame);
	layout->setMargin(2);

	auto lineEdit = new QLineEdit(text);
	auto removeButton = new QPushButton("Remove");

	_fields << lineEdit;

	layout->addWidget(lineEdit);
	layout->addWidget(removeButton);

	auto newItem = new QListWidgetItem();
	_listWidget->addItem(newItem);
	_listWidget->setItemWidget(newItem, frame);
	newItem->setSizeHint(frame->sizeHint());

	QObject::connect(removeButton, &QPushButton::pressed, [=]()
	{
		int index = _listWidget->row(newItem);
		delete _listWidget->takeItem(index);
		_fields.takeAt(index);
	});
}

void LineEditList::addFromStringList(const QList<QString> stringList)
{
	for (QString item : qAsConst(stringList)) addItem(item);
}

QList<QString> LineEditList::getTextInAllFields() const
{
	QList<QString> text;
	for (QLineEdit* field : qAsConst(_fields)) text << field->text();
	return text;
}

QString LineEditList::selectRandom() const
{
	QList<QString> text = getTextInAllFields();
	int index = QRandomGenerator::global()->bounded(text.size());
	return text[index];
}
