#include "SystemMdiArea.h"
#include "ui_SystemMdiArea.h"

SystemMdiArea::SystemMdiArea() : QMdiArea()
	, _ui(new Ui::SystemMdiArea)
{
	_ui->setupUi(viewport());

	setOption(QMdiArea::DontMaximizeSubWindowOnActivation);
}

SystemMdiArea::~SystemMdiArea()
{
	delete _ui;
}

Desktop* SystemMdiArea::getDesktop() const
{
	return _ui->desktopWidget;
}
