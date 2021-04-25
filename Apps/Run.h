#pragma once

#include "App.h"
#include <QObject>

#include "System.h"

namespace Ui
{
	class Run;
}

class Run : public App
{
	Q_OBJECT
public:
	Run(QString* defaultValue = nullptr, bool showHistory = false);
	~Run();

protected:
	virtual void resizeEvent(QResizeEvent* event) override;

private:
	Ui::Run* _ui = nullptr;
};

