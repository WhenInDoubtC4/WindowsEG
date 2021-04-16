#pragma once

#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

constexpr int WIDTH = 170;

class TaskbarElement : public QPushButton
{
	Q_OBJECT
public:
	TaskbarElement(const QString& text, const QPixmap* icon = nullptr);
	~TaskbarElement();

private:
	QHBoxLayout* _layout = nullptr;
	QLabel* _iconLabel = nullptr;
	QLabel* _textLabel = nullptr;
};

