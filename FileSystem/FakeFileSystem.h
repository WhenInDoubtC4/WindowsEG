#pragma once

#include <QObject>
#include <QJsonObject>

#include "App.h"
#include "Apps/MessageBox.h"

//Copied from stack overflow, no idea what the hell this does but it works
constexpr unsigned int hash(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (hash(str, h+1) * 33) ^ str[h];
}

class FakeFileSystem : public QObject
{
	Q_OBJECT
public:
	static App* jsonObjectToApp(const QJsonObject& object);

private:
	FakeFileSystem(QObject *parent = nullptr);

	template<typename E>
	static E extractEnum(QJsonValue jsonString);
};

