#pragma once

#include <QObject>
#include <QWidget>
#include <QMainWindow>

class SystemMainWindow : public virtual QMainWindow
{
	Q_OBJECT
public:
	explicit SystemMainWindow(QWidget *parent = nullptr);

signals:

};

