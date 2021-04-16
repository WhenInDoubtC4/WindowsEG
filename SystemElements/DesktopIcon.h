#pragma once

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QMenu>

#include "SystemElements/DesktopIconTextEdit.h"

namespace Ui
{
	class DesktopIcon;
}

const std::function<void(bool)> _emptySlot = []([[maybe_unused]] bool empty){};

class DesktopIcon : public QWidget
{
	Q_OBJECT
public:
	explicit DesktopIcon(QWidget* parent = nullptr, const QString& title = "Title", QPixmap* icon = nullptr);
	~DesktopIcon();

	void setSelected(bool selected);

	void drop();

	void rename(bool rename = true);

	inline static QSize staticMaxSize;
	inline static QString mimeType = "desktop-icon";

	std::function<void(bool)>
	openActionSlot				= _emptySlot,
	cutActionSlot				= _emptySlot,
	copyActionSlot				= _emptySlot,
	createShortcutActionSlot	= _emptySlot,
	deleteActionSlot			= _emptySlot,
	renameActionSlot			= _emptySlot,
	propertiesActionSlot		= _emptySlot;

protected:
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void focusOutEvent(QFocusEvent* event) override;

private:
	Ui::DesktopIcon* _ui = nullptr;

	bool _dragStarted = false;
	QPoint _capturedMousePosition;
	QPoint _initalPosition;
	bool _ignoreUnfocusOnce = false;

private slots:
	void showContextMenu(const QPoint& pos);

signals:
	void onOpened();
};

inline QDataStream& operator>>(QDataStream& stream, DesktopIcon*& icon)
{
	qulonglong ptr;
	stream >> ptr;
	icon = reinterpret_cast<DesktopIcon*>(ptr);
	return stream;
}
