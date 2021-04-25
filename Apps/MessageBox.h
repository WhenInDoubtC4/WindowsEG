#pragma once

#include <QObject>

#include "App.h"

constexpr int BUTTON_MIN_WIDTH = 80;

namespace Ui
{
	class MessageBox;
}

class MessageBox : public App
{
	Q_OBJECT

public:
	enum messageBoxType
	{
		INFO,
		WARNING,
		ERROR
	};
	Q_ENUM(messageBoxType)

	enum messageBoxButtonSet
	{
		OK,
		OK_CANCEL,
		YES_NO,
		CUSTOM
	};
	Q_ENUM(messageBoxButtonSet)

	MessageBox(messageBoxType type = messageBoxType::INFO, const QString& title = "", const QString& text = ">:(", messageBoxButtonSet buttonSet = messageBoxButtonSet::OK_CANCEL);
	~MessageBox();

	QList<QPushButton*>* getButtons();

private:
	Ui::MessageBox* _ui = nullptr;

	QList<QPushButton*> _buttons;
};

