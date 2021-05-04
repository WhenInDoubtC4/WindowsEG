#pragma once

#include <QObject>
#include <QWidget>

#include "App.h"

namespace Ui
{
	class FileSelector;
}

class FileSelector : public App
{
	Q_OBJECT
public:
	FileSelector();
	~FileSelector();

private:
	Ui::FileSelector* _ui = nullptr;
};

