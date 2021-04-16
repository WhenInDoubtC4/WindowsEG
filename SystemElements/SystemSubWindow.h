#pragma once

#include <QObject>
#include <QWidget>
#include <QMdiSubWindow>

#include "WindowTitleBar.h"

namespace Ui
{
	class SystemSubWindow;
}

class SystemSubWindow : public QMdiSubWindow
{
	Q_OBJECT

public:
	SystemSubWindow(WindowTitleBar::buttons buttonSet = WindowTitleBar::buttons::NORMAL);
	~SystemSubWindow();

	QWidget* getContentPlaceholder() const;
	WindowTitleBar* getTitleBar() const;

protected:
	virtual void focusInEvent(QFocusEvent* focusInEvent) override;
	virtual void focusOutEvent(QFocusEvent* focusOutEvent) override;

private:
	Ui::SystemSubWindow* _ui = nullptr;
	QWidget* _uiContainer = nullptr;

	WindowTitleBar* _titleBar = nullptr;

private slots:
	virtual void onCloseRequested();

signals:
	void focusChanged(bool focused);
};

