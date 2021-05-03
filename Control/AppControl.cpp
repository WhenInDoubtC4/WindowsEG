#include "AppControl.h"

AppControl::AppControl() : QObject()
{

}

QList<QList<QWidget*>>& AppControl::getControlItemsList()
{
	return _controlItems[this];
}

void AppControl::setupControlWidgets(QTreeWidget* treeWidget, const QString& title)
{
	auto frame = new QFrame();

	auto titleLayout = new QHBoxLayout(frame);

	auto resetButton = new QPushButton("Reset");
	auto activeButton = new QPushButton("Active");
	activeButton->setCheckable(true);

	QObject::connect(resetButton, &QPushButton::clicked, [=]
	{
		resetToDefault();
	});

	QObject::connect(activeButton, &QPushButton::clicked, [=](bool checked)
	{
		_isConfigActive = checked;
	});

	titleLayout->addWidget(new QLabel(title));
	titleLayout->addStretch();
	titleLayout->addWidget(resetButton, 0, Qt::AlignRight);
	titleLayout->addWidget(activeButton, 0, Qt::AlignRight);

	auto rootItem = new QTreeWidgetItem();
	treeWidget->addTopLevelItem(rootItem);
	treeWidget->setItemWidget(rootItem, 0, frame);
	rootItem->setFirstColumnSpanned(true);

	for (row row : qAsConst(_controlItems[this]))
	{
		auto childItem = new QTreeWidgetItem();
		rootItem->addChild(childItem);

		int index = 0;
		for (QWidget* widget : qAsConst(row))
		{
			treeWidget->setItemWidget(childItem, index++, widget);
		}
	}
}

QJsonDocument AppControl::saveAll()
{
	QJsonObject saveData;
	for (AppControl* instance : qAsConst(_instances))
	{
		instance->setSaveData(saveData);
	}

	return QJsonDocument(saveData);
}

void AppControl::loadAll(QJsonDocument& jsonDocument)
{
	QJsonObject rootObject = jsonDocument.object();

	for (AppControl* instance : qAsConst(_instances))
	{
		instance->load(rootObject);
	}
}

QList<QString> AppControl::jsonToStringList(const QJsonValueRef& jsonValue)
{
	QList<QString> stringList;
	for (QVariant& element : jsonValue.toArray().toVariantList())
	{
		stringList << qvariant_cast<QString>(element);
	}
	return stringList;
}

bool AppControl::isConfigActive()
{
	return _isConfigActive;
}
