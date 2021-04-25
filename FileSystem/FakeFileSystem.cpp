#include "FakeFileSystem.h"

FakeFileSystem::FakeFileSystem(QObject *parent) : QObject(parent)
{

}

template<typename E>
E FakeFileSystem::extractEnum(QJsonValue jsonString)
{
	if (jsonString.isNull()) return static_cast<E>(0);

	return static_cast<E>(QMetaEnum::fromType<E>().keyToValue(jsonString.toString().toLocal8Bit().data()));
}

App* FakeFileSystem::jsonObjectToApp(const QJsonObject& object)
{
	if (object["type"].toString() != "app") return nullptr;

	QJsonObject appObject = object["app"].toObject();
	char* appType = appObject["type"].toString().toLocal8Bit().data();

	switch (hash(appType))
	{
		case hash("messageBox"):
			return new MessageBox(extractEnum<MessageBox::messageBoxType>(appObject["messageBoxType"]), appObject["messageBoxTitle"].toString(), appObject["messageBoxText"].toString(), extractEnum<MessageBox::messageBoxButtonSet>(appObject["messageBoxButtonSet"]));
			break;
	}

	return nullptr;
}
