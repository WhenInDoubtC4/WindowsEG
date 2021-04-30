#pragma once

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QBoxLayout>
#include <QKeyEvent>
#include <QClipboard>
#include <QtMath>
#include <QRandomGenerator>

#include "App.h"
#include "Control/NotepadControl.h"
#include "System.h"
#include "Apps/MessageBox.h"

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

protected:
	virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
	Ui::Notepad* _ui = nullptr;
	QMainWindow* _uiWidget = nullptr;
	QBoxLayout* _uiLayout = nullptr;

private slots:
	void pasteText();
	void deleteSelection();
};

