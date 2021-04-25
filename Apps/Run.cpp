#include "Run.h"
#include "ui_Run.h"

#include <QDebug>

Run::Run(QString* defaultValue, bool showHistory) : App(WindowTitleBar::buttons::CLOSE_ONLY)
  , _ui(new Ui::Run)
{
	_ui->setupUi(getContentPlaceholder());

	taskbarTitle = "Run";
	getTitleBar()->setTitle("Run");

	if (defaultValue) _ui->comboBox->setCurrentText(*defaultValue);

	adjustSize();
}

void Run::resizeEvent(QResizeEvent* event)
{
	App::resizeEvent(event);

	move(System::getMdiAreaGeometry().bottomLeft() - QPoint(0, sizeHint().height()));
}

Run::~Run()
{
	delete _ui;
}
