#pragma once

#include <QMainWindow>
#include <QObject>
#include <QWidget>

namespace Ui
{
	class InternetExplorerUI;
}

class InternetExplorerUI : public QMainWindow
{
	Q_OBJECT
public:
	explicit InternetExplorerUI(QWidget* parent = nullptr);

private:
	Ui::InternetExplorerUI* _ui = nullptr;

};

