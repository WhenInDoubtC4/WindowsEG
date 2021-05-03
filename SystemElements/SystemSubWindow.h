#pragma once

#include <QObject>
#include <QWidget>
#include <QMdiSubWindow>
#include <QMenu>
#include <QGridLayout>
#include <QSizeGrip>

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

	void enableFrameResize();

	void attachTo(SystemSubWindow* window);
	void detach();

protected:
	virtual void focusInEvent(QFocusEvent* focusInEvent) override;
	virtual void focusOutEvent(QFocusEvent* focusOutEvent) override;
	virtual bool eventFilter(QObject* watched, QEvent* event) override;
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void showEvent(QShowEvent* showEvent) override;

private:
	Ui::SystemSubWindow* _ui = nullptr;
	QWidget* _uiContainer = nullptr;

	WindowTitleBar* _titleBar = nullptr;

	bool _isFocusSetUp = false;
	bool _ignoreUnfocusOnce = false;

	QGridLayout* _resizeGripLayout = nullptr;
	QList<QSizeGrip*> _resizeGrips;

	SystemSubWindow* _attachedWindow = nullptr;

private slots:
	virtual void onCloseRequested();

signals:
	void focusChanged(bool focused);
};

