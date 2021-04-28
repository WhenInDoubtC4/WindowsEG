#include "AppControl.h"

#include <QDebug>

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
	auto applyButton = new QPushButton("Apply");

	QObject::connect(applyButton, &QPushButton::pressed, [=]()
	{
		QByteArray data;
		updateConfigData(data);
		emit configApplied(data);

		qDebug() << "Applied data:" << data;
	});

	QObject::connect(activeButton, &QPushButton::toggled, [=](bool checked)
	{
		QByteArray data;
		updateConfigData(data);
		emit configToggled(checked);
		emit configApplied(data);
	});

	titleLayout->addWidget(new QLabel(title));
	titleLayout->addStretch();
	titleLayout->addWidget(resetButton, 0, Qt::AlignRight);
	titleLayout->addWidget(activeButton, 0, Qt::AlignRight);
	titleLayout->addWidget(applyButton, 0, Qt::AlignRight);

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

QList<QString> AppControl::toStringList(const QJsonValueRef& jsonValue)
{
	QList<QString> stringList;
	for (QVariant& element : jsonValue.toArray().toVariantList())
	{
		stringList << qvariant_cast<QString>(element);
	}
	return stringList;
}
