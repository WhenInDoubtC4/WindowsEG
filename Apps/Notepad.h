#pragma once

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QBoxLayout>
#include <QClipboard>

#include "App.h"

#include "Control/NotepadControl.h"

namespace Ui
{
	class Notepad;
}

class Notepad : public App
{
	Q_OBJECT
public:
	Notepad();
	~Notepad();

private:
	Ui::Notepad* _ui = nullptr;
	QMainWindow* _uiWidget = nullptr;
	QBoxLayout* _uiLayout = nullptr;

private slots:
	void deleteSelection();

	void onConfigApplied(QByteArray& configData);
};

