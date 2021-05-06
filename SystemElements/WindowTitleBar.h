#pragma once

#include <QWidget>
#include <QMdiSubWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QSpacerItem>

constexpr int SYSTEM_BUTTON_SIZE = 18;

namespace Ui
{
	class WindowTitleBar;
}

class WindowTitleBar : public QWidget
{
	Q_OBJECT
public:
	enum buttons
	{
		NORMAL,
		CLOSE_ONLY
	};
	Q_ENUM(buttons)

	explicit WindowTitleBar(QWidget* parent = nullptr, QMdiSubWindow* parentWindow = nullptr, buttons buttonSet = buttons::NORMAL);
	~WindowTitleBar();

	void setTitle(const QString& title);

	void setFocused(const bool focused);
	bool isFocused(){ return _isFocused; };

protected:
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;

private slots:
	void onCloseButtonPressed();
	void onMinMaxButtonPressed();
	void onHideButtonPressed();

private:
	Ui::WindowTitleBar* _ui = nullptr;

	QMdiSubWindow* _window = nullptr;

	bool _mouseButtonDown = false;
	QPoint _capturedMouseGlobalPosition;
	QPoint _capturedWindowGlobalPosition;

	QPushButton* _minMaxButton = nullptr;
	QPushButton* _hideButton = nullptr;

	bool _isFocused = false;

	QSize _normalWindowMinimumSize;

signals:
	void requestClose();
};

