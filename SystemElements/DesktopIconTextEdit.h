#pragma once

#include <QTextEdit>
#include <QObject>
#include <QWidget>
#include <QKeyEvent>

class DesktopIconTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	DesktopIconTextEdit(QWidget* parent = nullptr);

protected:
	virtual void focusOutEvent(QFocusEvent* e) override;
	virtual void keyPressEvent(QKeyEvent* e) override;

signals:
	void focusOut();
	void enterPressed();
};

